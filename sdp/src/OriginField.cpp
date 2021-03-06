/*****************************************************************************
//	SDP Parser Classes
//
//	Origin Field Class
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

//	PoCo headers
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Timestamp.h"

#include "OriginField.h"

using std::string;

using Poco::Int64;
using Poco::NumberParser;
using Poco::NumberFormatter;
using Poco::Timestamp;

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	OriginField class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Static members initialization 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const string OriginField :: InterNetwork		=	"IN";
const string OriginField :: IPv4				=	"IPv4";
const string OriginField :: IPv6				=	"IPv6";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OriginField :: OriginField()
	: Field("o", "")
	, _sessionId(0)
	, _sessionVersion(0)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OriginField :: OriginField(const string & value)
	: Field("o", value)
{
	Init();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OriginField :: OriginField(const std::string & userName,
						   const std::string & address,
						   const std::string & networkType,
						   const std::string & addressType)
	: Field("o", formatString(userName, address, networkType, addressType))
{
	Init();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OriginField :: OriginField(const OriginField & originField)
	: Field(originField)
	, _userName(originField._userName)
	, _sessionId(originField._sessionId)
	, _sessionVersion(originField._sessionVersion)
	, _address(originField._address)
	, _networkType(originField._networkType)
	, _addressType(originField._addressType)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OriginField & OriginField :: operator=(const OriginField & originField)
{
	if(&originField != this)
	{
		_userName = originField._userName;
		_sessionId = originField._sessionId;
		_sessionVersion = originField._sessionVersion;
		_address = originField._address;
		_networkType = originField._networkType;
		_addressType = originField._addressType;

		Field::operator=(originField);
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline string OriginField :: getUsername() const
{
	return _userName;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline Int64 OriginField :: getSessionId() const
{
	return _sessionId;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline Int64 OriginField :: getSessionVersion() const
{
	return _sessionVersion;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline string OriginField :: getAddress() const
{
	return _address;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline string OriginField :: getNetworkType() const
{
	return _networkType;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline string OriginField :: getAddressType() const
{
	return _addressType;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Private methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OriginField :: Init()
{
	StringVec parts = split(_value, ' ');
	_userName = parts[0];
	_sessionId = NumberParser::parse64(parts[1]);
	_sessionVersion = NumberParser::parse64(parts[2]);
	_networkType = parts[3];
	_addressType = parts[4];
	_address = parts[5];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string OriginField :: formatString(const std::string & username,
								   const std::string & address,
								   const std::string & networkType,
								   const std::string & addressType)
{
	/*	TODO: look better for current time measurement */
	string curTime =  NumberFormatter::format(Timestamp().utcTime());
	string str = username + " " +
				 curTime + " " +
				 curTime + " " + 
				 networkType + " " + 
				 addressType + " " +
				 address;

	return str;
}


} //	namespace SDP
