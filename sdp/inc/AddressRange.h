d/*****************************************************************************
//	SDP Parser Classes
//
//	Address Range Class
//
//	description:
//		describes a range of addresses
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

#ifndef __ADDRESS_RANGE__H__
#define __ADDRESS_RANGE__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//	PoCo headers
#include "Poco/Net/IPAddress.h"

#include "sdp_parser.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	AddressRange class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API AddressRange
	/// This class describes a range of addresses.
{
public:

	AddressRange();
	/// Instantiates a new empty AddressRange.

	AddressRange(const Poco::Net::IPAddress & address);
	/// Instantiates a new AddressRange with the unicast starting address.
	/// The default number of addresses is one, so this range is effectively one address.

	AddressRange(const Poco::Net::IPAddress & address, unsigned short ttl);
	/// Instantiates a new AddressRange with the multiciast starting address
	/// and the "time-to-live" parameter

	AddressRange(const Poco::Net::IPAddress & address,
				 unsigned int numberOfAddresses,
				 unsigned short ttl);
	/// Instantiates a new AddressRange with the multicast hierarchial starting address,
	/// the number of addresses in the range (must be greater than or equal to one) and
	/// the "time-to-live" parameter.

	AddressRange(const AddressRange & addressRange);
	/// Creates a copy of specified AddressRange object.

	AddressRange & operator=(const AddressRange & addressRange);
	/// Copies the specified AddressRange object. 

	Poco::Net::IPAddress getAddress() const;
	/// Gets the value of the starting address.

	unsigned int getNumberOfAddresses() const;
	/// Gets the number of ports in the range.

	unsigned short getTTL() const;
	/// Gets the "time-to-live" value.

	std::string toString() const;
	/// Converts an AddressRange to its string representation.
	
private:

	Poco::Net::IPAddress		_address;
	unsigned int				_numberOfAddresses;
	unsigned short				_ttl;

};

} //	namespace SDP

#endif	//	__ADDRESS_RANGE__H__