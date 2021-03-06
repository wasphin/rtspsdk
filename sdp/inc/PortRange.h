/*****************************************************************************
//	SDP Parser Classes
//
//	Port Range Class
//
//	description:
//		describes a range of ports
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

#ifndef __PORT_RANGE__H__
#define __PORT_RANGE__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sdp_parser.h"
#include "common.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	PortRange class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API PortRange
	/// This class describes a range of ports.
{
public:

	PortRange();
	/// Instantiates a new empty AddressRange.

	PortRange(unsigned short firstPort);
	/// Instantiates a new PortRange with the specified first port
	/// and number of ports equal to one.

	PortRange(unsigned short firstPort, unsigned short numberOfPorts);
	/// Instantiates a new PortRange with the specified first port
	/// and number of ports.

	PortRange(const PortRange & portRange);
	/// Creates a copy of specified PortRange object.

	PortRange & operator=(const PortRange & portRange);
	/// Copies the specified PortRange object.

	unsigned short getFirstPort() const;
	/// Gets the first port in the range.

	void setFirstPort(unsigned short firstPort);
	/// Sets the first port in the range.

	unsigned short getNumberOfPorts() const;
	/// Gets the number of ports in the range.

	void setNumberOfPorts(unsigned short numberOfPorts);

	/// Sets the number of ports in the range.
	std::string toString() const;
	/// Converts a PortRange to it's string representation.

private:

	unsigned short		_firstPort;
	unsigned short		_numberOfPorts;

};

} //	namespace SDP

#endif	//	__PORT_RANGE__H__

