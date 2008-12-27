/*****************************************************************************
//	SDP Parser Classes
//
//	Connection Field Class
//
//	description:
//		represents SDP description connection field
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

#ifndef __CONNECTION_FIELD__H__
#define __CONNECTION_FIELD__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sdp_parser.h"
#include "common.h"
#include "Field.h"
#include "AddressRange.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ConnectionField class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API ConnectionField : public Field
    /// A Connection represents the c= field and identifies a network address on which media
    /// can be recieved.
    /// 
    /// The Connection the SessionDescription is mandatory if it is not present in all 
    /// MediaDescriptions.
{
public:

	ConnectionField();
	/// Creates an empty ConnectionField.

	ConnectionField(const std::string & value);
	/// Creates a new ConnectionField according to the specified value string.

	ConnectionField(const AddressRange & address);
	/// Creates a new ConnectionField according to the address of the connection.

	ConnectionField(const AddressRange & address,
					const std::string & networkType,
					const std::string & addressType);
	/// Creates a new ConnectionField according to the address of the connection,
	/// the network type and the address type.

	ConnectionField(const ConnectionField & connectionField);
	/// Creates a copy of specified ConnectionField object.

	ConnectionField & operator=(const ConnectionField & connectionField);
	/// Copies the specified ConnectionField object.

	AddressRange getAddress() const;
	/// Gets the address.

	std::string getAddressType() const;
	/// Gets the address type. Is either "IP4" or "IP6".

	std::string getNetworkType() const;
	/// Gets the network type. For this specification the value should
	/// always be "IN" for Internet.

	virtual std::string getValue() const;
	/// Gets the value portion of this field.


	static const std::string InterNetwork;
	/// Defines the constant for the Internet network type.

	static const std::string IPv4;
	/// Defines the constant for the IP version 4 network address type.

	static const std::string IPv6;
	/// Defines the constant for the IP version 6 network address type.

private:

	void Init();
	/// Initializes internal object fields.

	AddressRange		_address;
	std::string			_addressType;
	std::string			_networkType;

};

} //	namespace SDP

#endif	//	__CONNECTION_FIELD__H__

