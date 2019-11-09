/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Client Session Class
//
//	revision of last commit:
//		$Rev$
//	author of last commit:
//		$Author$
//	date of last commit:
//		$Date$
//
//	created by Argenet {argenet@sibears.org}
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
******************************************************************************/

#include "Poco/RTSP/RTSPClientSession.h"
#include "Poco/RTSP/RTSPFixedLengthStream.h"
#include "Poco/RTSP/RTSPHeaderStream.h"
#include "Poco/RTSP/RTSPRequest.h"
#include "Poco/RTSP/RTSPResponse.h"
#include "Poco/RTSP/RTSPStream.h"

#include "Poco/CountingStream.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Net/NetException.h"

#include <iostream>

namespace Poco {
namespace RTSP {

using Poco::IllegalStateException;
using Poco::NumberFormatter;
using Poco::Net::MessageException;
using Poco::Net::NetException;

RTSPClientSession::RTSPClientSession():
	_port(RTSPSession::RTSP_PORT),
	_proxyPort(RTSPSession::RTSP_PORT),
//	_keepAliveTimeout(DEFAULT_KEEP_ALIVE_TIMEOUT, 0),
	_reconnect(false),
	_mustReconnect(false),
	_pRequestStream(NULL),
	_pResponseStream(NULL)
{
}


RTSPClientSession::RTSPClientSession(const StreamSocket& socket):
	RTSPSession(socket),
	_port(RTSPSession::RTSP_PORT),
	_proxyPort(RTSPSession::RTSP_PORT),
//	_keepAliveTimeout(DEFAULT_KEEP_ALIVE_TIMEOUT, 0),
	_reconnect(false),
	_mustReconnect(false),
	_pRequestStream(NULL),
	_pResponseStream(NULL)
{
}


RTSPClientSession::RTSPClientSession(const SocketAddress& address):
	_host(address.host().toString()),
	_port(address.port()),
	_proxyPort(RTSPSession::RTSP_PORT),
//	_keepAliveTimeout(DEFAULT_KEEP_ALIVE_TIMEOUT, 0),
	_reconnect(false),
	_mustReconnect(false),
	_pRequestStream(NULL),
	_pResponseStream(NULL)
{
}


RTSPClientSession::RTSPClientSession(const std::string& host, Poco::UInt16 port):
	_host(host),
	_port(port),
	_proxyPort(RTSPSession::RTSP_PORT),
//	_keepAliveTimeout(DEFAULT_KEEP_ALIVE_TIMEOUT, 0),
	_reconnect(false),
	_mustReconnect(false),
	_pRequestStream(NULL),
	_pResponseStream(NULL)
{
}


RTSPClientSession::~RTSPClientSession()
{
	delete _pRequestStream;
	delete _pResponseStream;
}


void RTSPClientSession::setHost(const std::string& host)
{
	if (!connected())
	{
		_host = host;
	}
	else
	{
		throw IllegalStateException("Cannot set the host for an already connected session");
	}
}


void RTSPClientSession::setPort(Poco::UInt16 port)
{
	if (!connected())
	{
		_port = port;
	}
	else
	{
		throw IllegalStateException("Cannot set the port number for an already connected session");
	}
}


void RTSPClientSession::setProxy(const std::string& host, Poco::UInt16 port)
{
	if (!connected())
	{
		_proxyHost = host;
		_proxyPort = port;
	}
	else
	{
		throw IllegalStateException("Cannot set the proxy host and port for an already connected session");
	}
}


void RTSPClientSession::setProxyHost(const std::string& host)
{
	if (!connected())
	{
		_proxyHost = host;
	}
	else
	{
		throw IllegalStateException("Cannot set the proxy host for an already connected session");
	}
}


void RTSPClientSession::setProxyPort(Poco::UInt16 port)
{
	if (!connected())
	{
		_proxyPort = port;
	}
	else
	{
		throw IllegalStateException("Cannot set the proxy port number for an already connected session");
	}
}

/* NB!
void RTSPClientSession::setKeepAliveTimeout(const Poco::Timespan& timeout)
{
	_keepAliveTimeout = timeout;
}
*/

std::ostream& RTSPClientSession::sendRequest(RTSPRequest& request)
{
	delete _pResponseStream;
	_pResponseStream = NULL;
	
	if (!connected())
	{
		reconnect();
	}

	Poco::UInt16 cSeq = getCSeq();
	request.set("CSeq", NumberFormatter::format(cSeq));
	++cSeq;
	setCSeq(cSeq);

	if (!_proxyHost.empty())
		request.setURI(getHostInfo() + request.getURI());

	if (request.getContentLength() != RTSPMessage::UNKNOWN_CONTENT_LENGTH)
	{
		Poco::CountingOutputStream cs;
		request.write(cs);
		_pRequestStream = new RTSPFixedLengthOutputStream(*this, request.getContentLength() + cs.chars());
		request.write(*_pRequestStream);
	}
	else
	{
		_pRequestStream = new RTSPOutputStream(*this);
		request.write(*_pRequestStream);
	}

	_lastRequest.update();
	return *_pRequestStream;
}


std::istream& RTSPClientSession::receiveResponse(RTSPResponse& response)
{
	delete _pRequestStream;
	_pRequestStream = NULL;

	do
	{
		response.clear();
		RTSPHeaderInputStream his(*this);
		try
		{
			response.read(his);
		}
		catch (MessageException&)
		{
			if (networkException())
				networkException()->rethrow();
			else
				throw;
		}
	}
	while (response.getStatus() == RTSPResponse::RTSP_CONTINUE);

	if (RTSPMessage::UNKNOWN_CONTENT_LENGTH != response.getContentLength())
	{
		_pResponseStream = new RTSPFixedLengthInputStream(*this, response.getContentLength());
	}
	else
	{
		_pResponseStream = new RTSPFixedLengthInputStream(*this, 0);
	}
		
	return *_pResponseStream;
}


int RTSPClientSession::write(const char* buffer, std::streamsize length)
{
	try
	{
		int rc = RTSPSession::write(buffer, length);
		_reconnect = false;
		return rc;
	}
	catch (NetException&)
	{
		if (_reconnect)
		{
			close();
			reconnect();
			int rc = RTSPSession::write(buffer, length);
			_reconnect = false;
			return rc;
		}
		else throw;
	}
}


void RTSPClientSession::reconnect()
{
	if (_proxyHost.empty())
	{
		SocketAddress addr(_host, _port);
		connect(addr);
	}
	else
	{
		SocketAddress addr(_proxyHost, _proxyPort);
		connect(addr);
	}
}


std::string RTSPClientSession::getHostInfo() const
{
	std::string result("rtsp://");
	result.append(_host);
	result.append(":");
	result.append(NumberFormatter::format(_port));
	return result;
}


void RTSPClientSession::deleteResponseStream()
{
	delete _pResponseStream;
	_pResponseStream = NULL;
}


void RTSPClientSession::deleteRequestStream()
{
	delete _pRequestStream;
	_pRequestStream = NULL;
}


void RTSPClientSession::setResponseStream(std::istream* pRespStream)
{
	poco_assert(NULL == _pResponseStream);
	_pResponseStream = pRespStream;
}


void RTSPClientSession::setRequestStream(std::ostream* pRequestStream)
{
	poco_assert (NULL == _pRequestStream);
	_pRequestStream = pRequestStream;
}

} //	namespace RTSP
} //	namespace Poco
