/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Client Sessions Factory Class
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


#include "Poco/Exception.h"
#include "RTSPSessionFactory.h"
#include "RTSPSessionInstantiator.h"


using Poco::SingletonHolder;
using Poco::FastMutex;
using Poco::NotFoundException;
using Poco::ExistsException;

namespace RTSP {

RTSPSessionFactory::RTSPSessionFactory():
	_proxyPort(0)
{
}


RTSPSessionFactory::RTSPSessionFactory(const std::string& proxyHost, Poco::UInt16 proxyPort):
	_proxyHost(proxyHost),
	_proxyPort(proxyPort)
{
}


RTSPSessionFactory::~RTSPSessionFactory()
{
	for (Instantiators::iterator it = _instantiators.begin(); it != _instantiators.end(); ++it)
	{
		delete it->second.pIn;
	}
}


void RTSPSessionFactory::registerProtocol(const std::string& protocol, RTSPSessionInstantiator* pSessionInstantiator)
{
	poco_assert_dbg(pSessionInstantiator);

	FastMutex::ScopedLock lock(_mutex);
	std::pair<Instantiators::iterator, bool> tmp = _instantiators.insert(make_pair(protocol, InstantiatorInfo(pSessionInstantiator)));
	if (!tmp.second) 
	{
		++tmp.first->second.cnt;
		delete pSessionInstantiator;
	}
}


void RTSPSessionFactory::unregisterProtocol(const std::string& protocol)
{
	FastMutex::ScopedLock lock(_mutex);
	
	Instantiators::iterator it = _instantiators.find(protocol);
	if (it != _instantiators.end())
	{
		if (it->second.cnt == 1)
		{
			delete it->second.pIn;
			_instantiators.erase(it);
		}
		else
		{
			--it->second.cnt;
		}
	}
	else
	{
		throw NotFoundException("No HTTPSessionInstantiator registered for", protocol);
	}
}


bool RTSPSessionFactory::supportsProtocol(const std::string& protocol)
{
	FastMutex::ScopedLock lock(_mutex);
	
	Instantiators::iterator it = _instantiators.find(protocol);
	return it != _instantiators.end();
}


RTSPClientSession* RTSPSessionFactory::createClientSession(const Poco::URI& uri)
{
	FastMutex::ScopedLock lock(_mutex);
	
	if (uri.isRelative()) throw Poco::UnknownURISchemeException("Relative URIs are not supported by RTSPSessionFactory.");

	Instantiators::iterator it = _instantiators.find(uri.getScheme());
	if (it != _instantiators.end())
	{
		it->second.pIn->setProxy(_proxyHost, _proxyPort);
		return it->second.pIn->createClientSession(uri);
	}
	else 
	{
		throw Poco::UnknownURISchemeException(uri.getScheme());
	}
}


void RTSPSessionFactory::setProxy(const std::string& host, Poco::UInt16 port)
{
	FastMutex::ScopedLock lock(_mutex);

	_proxyHost = host;
	_proxyPort = port;
}


RTSPSessionFactory& RTSPSessionFactory::defaultFactory()
{
	static SingletonHolder<RTSPSessionFactory> singleton;
	return *singleton.get();
}


RTSPSessionFactory::InstantiatorInfo::InstantiatorInfo(RTSPSessionInstantiator* pInst): pIn(pInst), cnt(1)
{
	poco_check_ptr (pIn);
}

} // namespace RTSP

