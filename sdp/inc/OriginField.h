/*****************************************************************************
//	SDP Parser Classes
//
//	Origin Field Class
//
//	description:
//		represents SDP description origin field
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

#ifndef __ORIGIN_FIELD__H__
#define __ORIGIN_FIELD__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sdp_parser.h"
#include "common.h"
#include "Field.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	OriginField class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API OriginField : public Field
    /// An Origin represents the o= fields contained within a SessionDescription.
    /// 
    /// The Origin field identifies the originator of the session.
    /// 
    /// This is not necessarily the same entity who is involved in the session.
    /// 
    /// The Origin contains:
    ///   - the name of the user originating the session
    ///   - a unique session identifier
    ///   - a unique version for the session
    /// 
    /// These fields should uniquely identify the session.
    /// 
    /// The Origin also includes:
    ///   - the network type
    ///   - address type
    ///   - address of the originator
{
public:

	OriginField();
	/// Creates an empty OriginField.

	OriginField(const std::string & value);
	/// Creates a new OriginField according to the specified value string.

	OriginField(const std::string & username,
				const std::string & address,
				const std::string & networkType,
				const std::string & addressType);
	/// Creates a new OriginField with the specified username, address,
	///	type of network and type of address.

	OriginField(const OriginField & originField);
	/// Creates a copy of specified OriginField object.

	OriginField & operator=(const OriginField & originField);
	/// Copies the specified OriginField object.

	std::string getUsername() const;
	/// Gets the username.

	Poco::Int64 getSessionId() const;
	/// Gets the session ID.

	Poco::Int64 getSessionVersion() const;
	/// Gets the version of this session.

	std::string getAddress() const;
	/// Gets the address.

	std::string getNetworkType() const;
	/// Gets the type of network the address is using.

	std::string getAddressType() const;
	/// Gets the address type.


	static const std::string InterNetwork;
	/// The network type that describes the Internet.

	static const std::string IPv4;
	/// The address type for IPv4 addresses.

	static const std::string IPv6;
	/// The address type for IPv6 addresses.

private:

	void Init();
	/// Initializes internal object fields.

	std::string formatString(const std::string & username,
							 const std::string & address,
							 const std::string & networkType,
							 const std::string & addressType);
	/// Builds a value string representing the origin field  content.

	std::string			_userName;
	Poco::Int64			_sessionId;
	Poco::Int64			_sessionVersion;
	std::string			_address;
	std::string			_networkType;
	std::string			_addressType;
};

} //	namespace SDP

#endif	//	__ORIGIN_FIELD__H__

