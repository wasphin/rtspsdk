/*****************************************************************************
//	SDP Parser Classes
//
//	Time Repetition Field Class
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
#include "Poco/Timespan.h"
#include "Poco/Exception.h"

#include "NTPTime.h"
#include "TimeRepetitionField.h"

using std::string;

using Poco::Int64;
using Poco::NumberParser;
using Poco::NumberFormatter;
using Poco::Timespan;
using Poco::SyntaxException;

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	TimeRepetitionField class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeRepetitionField :: TimeRepetitionField()
	: Field("t", "")
{
}

TimeRepetitionField :: TimeRepetitionField(const string & value)
	: Field("t", value)
{
	StringVec parts = split(_value, ' ');
	try
	{
		Int64 ans = NumberParser::parse64(parts[0]);
		_interval = (0 != ans) ? NTPTime::getTimeSpan(ans) : NTPTime::getTimeSpan(parts[0]);

	}
	catch(SyntaxException &)
	{
	}

	try
	{
		Int64 ans = NumberParser::parse64(parts[1]);
		_activeTime = (0 != ans) ? NTPTime::getTimeSpan(ans) : NTPTime::getTimeSpan(parts[1]);

	}
	catch(SyntaxException &)
	{
	}

	for(int i = 2 ; i < parts.size() ; ++i)
	{
		try
		{
			Int64 ans = NumberParser::parse64(parts[i]);
			Timespan ts = (0 != ans) ? NTPTime::getTimeSpan(ans) : NTPTime::getTimeSpan(parts[i]);

		}
		catch(SyntaxException &)
		{
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeRepetitionField :: TimeRepetitionField(const Timespan & interval,
										   const Timespan & activeTime)
	: Field("t", formatString(interval, activeTime))
	, _interval(interval)
	, _activeTime(activeTime)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeRepetitionField :: TimeRepetitionField(const Timespan & interval,
										   const Timespan & activeTime,
										   const TimespanVec & offsets)
	: Field("t", formatString(interval, activeTime, offsets))
	, _interval(interval)
	, _activeTime(activeTime)
	, _offsets(offsets)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeRepetitionField :: TimeRepetitionField(const TimeRepetitionField & timeRepetitionField)
	: Field(timeRepetitionField)
	, _interval(timeRepetitionField._interval)
	, _activeTime(timeRepetitionField._activeTime)
	, _offsets(timeRepetitionField._offsets)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeRepetitionField & TimeRepetitionField :: operator=(const TimeRepetitionField & timeRepetitionField)
{
	if(&timeRepetitionField != this)
	{
		_interval = timeRepetitionField._interval;
		_activeTime = timeRepetitionField._activeTime;
		_offsets = timeRepetitionField._offsets;

		Field::operator=(timeRepetitionField);
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline Timespan TimeRepetitionField :: getInterval() const
{
	return _interval;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline Timespan TimeRepetitionField :: getActiveTime() const
{
	return _activeTime;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline TimespanVec TimeRepetitionField :: getOffsets() const
{
	return _offsets;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Private methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::string TimeRepetitionField :: formatString(const Poco::Timespan & interval,
												const Poco::Timespan & activeTime)
{
	string str = NumberFormatter::format(NTPTime::getNTPTime(interval)) + 
				" " + 
				NumberFormatter::format(NTPTime::getNTPTime(activeTime));

	return str;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::string TimeRepetitionField :: formatString(const Timespan & interval,
												const Timespan & activeTime,
												const TimespanVec & offests)
{
	string str = formatString(interval, activeTime);
	for(TimespanVec::iterator iter = _offsets.begin();
		_offsets.end() != iter;
		++iter)
	{
		str += " " + NumberFormatter::format(NTPTime::getNTPTime(*iter));
	}

	return str;
}

} //	namespace SDP