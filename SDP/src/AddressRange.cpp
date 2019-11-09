/*****************************************************************************
//	SDP Parser Classes
//
//	Address Range Class
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Poco/SDP/AddressRange.h"

//	PoCo headers
#include "Poco/NumberFormatter.h"
#include "Poco/Util/OptionException.h"

namespace Poco {
namespace SDP {

using std::string;

using Poco::NumberFormatter;
using Poco::Net::IPAddress;
using Poco::Util::InvalidArgumentException;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	AddressRange class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange :: AddressRange()
	: _address(IPAddress())
	, _numberOfAddresses(1)
	, _ttl(1)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange :: AddressRange(const IPAddress & address)
	: _address(address)
	, _numberOfAddresses(1)
	, _ttl(1)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange :: AddressRange(const IPAddress & address,
							 unsigned short ttl)
	: _address(address)
	, _numberOfAddresses(1)
	, _ttl(ttl)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange :: AddressRange(const Poco::Net::IPAddress & address,
							 unsigned int numberOfAddresses,
							 unsigned short ttl)
	: _address(address)
	, _numberOfAddresses(numberOfAddresses)
	, _ttl(ttl)
{
	if(numberOfAddresses < 1)
	{
		throw new InvalidArgumentException("AddressRange ctor - number of addresses must be greater than or equal to one.");
	}
	else
	{
		_numberOfAddresses = numberOfAddresses;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange :: AddressRange(const AddressRange & addressRange)
	: _address(addressRange._address)
	, _numberOfAddresses(addressRange._numberOfAddresses)
	, _ttl(addressRange._ttl)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AddressRange & AddressRange :: operator=(const AddressRange & addressRange)
{
	if(&addressRange != this)
	{
		_address = addressRange._address;
		_numberOfAddresses = addressRange._numberOfAddresses;
		_ttl = addressRange._ttl;
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline IPAddress AddressRange :: getAddress() const
{
	return _address;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline unsigned int AddressRange :: getNumberOfAddresses() const
{
	return _numberOfAddresses;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline unsigned short AddressRange :: getTTL() const
{
	return _ttl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::string AddressRange :: toString() const
{
	string str = _address.toString();
	if(0 == _ttl)
	{
		return str;
	}
	str += "/" + NumberFormatter::format(_ttl);
	if(1 == _numberOfAddresses)
	{
		return str;
	}
	str += "/" + NumberFormatter::format(_numberOfAddresses);

	return str;
}

} //	namespace SDP
} //	namespace Poco
