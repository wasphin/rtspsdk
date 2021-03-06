/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Request Message class
//
//	description:
//		represents RTSP request message
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


#ifndef __RTSP_REQUEST__H__
#define __RTSP_REQUEST__H__


#include "Poco/Net/Net.h"

#include "rtsp_sdk.h"
#include "RTSPMessage.h"

namespace RTSP {

class RTSP_SDK_API RTSPRequest: public RTSPMessage
	/// This class encapsulates an RTSP request
	/// message.
	///
	/// In addition to the properties common to
	/// all RTSP messages, a RTSP request has
	/// a method (e.g. DESCRIBE, SETUP, PLAY, etc.) and
	/// a request URI.
{
public:
	RTSPRequest();
		/// Creates an empty RTSP/1.0 RTSP request with no specified method.
		
	RTSPRequest(const std::string& version);
		/// Creates an empty RTSP request the given version 
		/// (for possible future protocol extensions; only RTSP/1.0 is available now).
		
	RTSPRequest(const std::string& method, const std::string& uri);
		/// Creates a RTSP/1.0 request with the given method and URI.

	RTSPRequest(const std::string& method, const std::string& uri, const std::string& version);
		/// Creates a RTSP request with the given method, URI and version.

	virtual ~RTSPRequest();
		/// Destroys the RTSPRequest.

	void setMethod(const std::string& method);
		/// Sets the method.

	const std::string& getMethod() const;
		/// Returns the method.

	void setURI(const std::string& uri);
		/// Sets the request URI.
		
	const std::string& getURI() const;
		/// Returns the request URI.

	bool hasCredentials() const;
		/// Returns true iff the request contains authentication
		/// information in the form of an Authorization header.
		
	void getCredentials(std::string& scheme, std::string& authInfo) const;
		/// Returns the authentication scheme and additional authentication
		/// information contained in this request.
		///
		/// Throws a NotAuthenticatedException if no authentication information
		/// is contained in the request.
		
	void setCredentials(const std::string& scheme, const std::string& authInfo);
		/// Sets the authentication scheme and information for
		/// this request.

	void write(std::ostream& ostr) const;
		/// Writes the HTTP request to the given
		/// output stream.

	void read(std::istream& istr);
		/// Reads the HTTP request from the
		/// given input stream.
	

	static const std::string RTSP_NONE;
	static const std::string RTSP_DESCRIBE;
	static const std::string RTSP_ANNOUNCE;
	static const std::string RTSP_GET_PARAMETER;
	static const std::string RTSP_OPTIONS;
	static const std::string RTSP_PAUSE;
	static const std::string RTSP_PLAY;
	static const std::string RTSP_RECORD;
	static const std::string RTSP_REDIRECT;
	static const std::string RTSP_SETUP;
	static const std::string RTSP_SET_PARAMETER;
	static const std::string RTSP_TEARDOWN;
	
	static const std::string AUTHORIZATION;

private:
	enum Limits
	{
		MAX_METHOD_LENGTH  = 32,
		MAX_URI_LENGTH     = 4096,
		MAX_VERSION_LENGTH = 8
	};
	
	std::string _method;
	std::string _uri;
	
	RTSPRequest(const RTSPRequest&);
	RTSPRequest& operator = (const RTSPRequest&);
};


//
// inlines
//
inline const std::string& RTSPRequest::getMethod() const
{
	return _method;
}


inline const std::string& RTSPRequest::getURI() const
{
	return _uri;
}

} // namespace RTSP

#endif // __RTSP_REQUEST__H__
