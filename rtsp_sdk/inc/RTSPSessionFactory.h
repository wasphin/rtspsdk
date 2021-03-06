/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Client Sessions Factory Class
//
//	description:
//		represents RTSP client sessions factory
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


#ifndef __RTSP_SESSION_FACTORY__H__
#define __RTSP_SESSION_FACTORY__H__


#include "Poco/Net/Net.h"
#include "Poco/Mutex.h"
#include "Poco/URI.h"
#include "Poco/SingletonHolder.h"
#include "Poco/SharedPtr.h"
#include <map>

#include "rtsp_sdk.h"

namespace RTSP {



class RTSPSessionInstantiator;
class RTSPClientSession;



class RTSP_SDK_API RTSPSessionFactory
	/// A factory for RTSPClientSession objects.
	///
	/// Given a URI, this class creates a RTSPClientSession
	/// (for rtsp) for accessing the URI.
	///
	/// The actual work of creating the session is done by
	/// RTSPSessionInstantiator objects that must be registered
	/// with a RTSPSessionFactory.
{
public:
	RTSPSessionFactory();
		/// Creates the RTSPSessionFactory.

	RTSPSessionFactory(const std::string& proxyHost, Poco::UInt16 proxyPort);
		/// Creates the RTSPSessionFactory and sets the proxy host and port.

	~RTSPSessionFactory();
		/// Destroys the RTSPSessionFactory.

	void registerProtocol(const std::string& protocol, RTSPSessionInstantiator* pSessionInstantiator);
		/// Registers the session instantiator for the given protocol.
		/// The factory takes ownership of the SessionInstantiator.
		///
		/// A protocol can be registered more than once. However, only the instantiator
		/// that has been registered first is used. Also, for each call to
		/// registerProtocol(), a corresponding call to unregisterProtocol() must
		/// be made.

	void unregisterProtocol(const std::string& protocol);
		/// Removes the registration of a protocol.
		///
		/// Throws a NotFoundException if no instantiator has been registered
		/// for the given protocol.

	bool supportsProtocol(const std::string& protocol);
		/// Returns true if a session instantiator for the given protocol has been registered.

	RTSPClientSession* createClientSession(const Poco::URI& uri);
		/// Creates a client session for the given uri scheme. Throws exception if no factory is registered for the given scheme

	const std::string& proxyHost() const;
		/// Returns the proxy host, if one has been set, or an empty string otherwise.
		
	Poco::UInt16 proxyPort() const;
		/// Returns the proxy port number, if one has been set, or zero otherwise.

	void setProxy(const std::string& proxyHost, Poco::UInt16 proxyPort);
		/// Sets the proxy host and port number.

	static RTSPSessionFactory& defaultFactory();
		/// Returns the default RTSPSessionFactory.

private:
	struct InstantiatorInfo
	{
		RTSPSessionInstantiator* pIn;
		int cnt;
		InstantiatorInfo(RTSPSessionInstantiator* pInst);
			// no destructor!!! this is by purpose, don't add one!
	};


	RTSPSessionFactory(const RTSPSessionFactory&);
	RTSPSessionFactory& operator = (const RTSPSessionFactory&);
	
	typedef std::map<std::string, InstantiatorInfo> Instantiators;

	Instantiators _instantiators;
	std::string   _proxyHost;
	Poco::UInt16  _proxyPort;

	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
inline const std::string& RTSPSessionFactory::proxyHost() const
{
	return _proxyHost;
}


inline Poco::UInt16 RTSPSessionFactory::proxyPort() const
{
	return _proxyPort;
}

} // namespace RTSP

#endif // __RTSP_SESSION_FACTORY__H__
