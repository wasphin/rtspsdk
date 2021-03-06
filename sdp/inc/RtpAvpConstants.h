/*****************************************************************************
//	SDP Parser Classes
//
//	RTP/AVP Constants
//
//	description:
//		defines some constants that can be used when creating 
//		MediaFields with the RTP/AVP transport protocol
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

#ifndef __RTP_AVP_CONSTANTS__H__
#define __RTP_AVP_CONSTANTS__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sdp_parser.h"
#include "common.h"

namespace SDP {

typedef struct SDP_PARSER_API _RtpAvpConstants
/// This class defines some constants that can be used when creating MediaFields with the RTP/AVP
/// transport protocol.
{
	static const std::string RESERVED;
	/// An int greater than or equal to 0 and less than AVP_DEFINED_STATIC_MAX,
	/// but has not been assigned a value.

	static const std::string UNASSIGNED;
	/// Unassigned Payload type.
	/// An int greater than or equal to AVP_DEFINED_STATIC_MAX and less than
	/// AVP_DYNAMIC_MIN - currently unassigned.

	static const std::string DYNAMIC;
	/// Dynamic Payload type. 
	/// Any int less than 0 or greater than or equal to AVP_DYNAMIC_MIN

	static const std::string RTP_AVP;
	/// RTP/AVP Protocol

	static const std::string RTPMAP;
	/// RTP mapping attribute.
	/// 
	/// SDP is case-sensitive; RFC2327 specifies 'rtpmap' (all smallcap)

	static const std::string FMTP;
	/// RTP mapping attribute.

	static const std::string CONTROL;
	/// RTP attribute.

	static const int PCMU = 0;
	/// Static RTP/AVP payload type for the PCMU audio codec.

	static const int TENSIXTEEN = 1;
	/// Static RTP/AVP payload type for the TENSIXTEEN audio codec.

	static const int G726_32 = 2;
	/// Static RTP/AVP payload type for the G726_32 audio codec.

	static const int GSM = 3;
	/// Static RTP/AVP payload type for the GSM audio codec.

	static const int G723 = 4;
	/// Static RTP/AVP payload type for the G723 audio codec.

	static const int DVI4_8000 = 5;
	/// Static RTP/AVP payload type for the DVI4_8000 audio codec.

	static const int DVI4_16000 = 6;
	/// Static RTP/AVP payload type for the DVI4_16000 audio codec.

	static const int LPC = 7;
	/// Static RTP/AVP payload type for the LPC audio codec.

	static const int PCMA = 8;
	/// Static RTP/AVP payload type for the PCMA audio codec.

	static const int G722 = 9;
	/// Static RTP/AVP payload type for the G722 audio codec.

	static const int L16_2CH = 10;
	/// Static RTP/AVP payload type for the L16_2CH audio codec.

	static const int L16_1CH = 11;
	/// Static RTP/AVP payload type for the L16_1CH audio codec.

	static const int QCELP = 12;
	/// Static RTP/AVP payload type for QCELP audio codec.

	static const int CN = 13;
	/// Static RTP/AVP payload type for the CN audio codec.

	static const int MPA = 14;
	/// Static RTP/AVP payload type for the MPA audio codec.

	static const int G728 = 15;
	/// Static RTP/AVP payload type for the G728 audio codec.

	static const int DVI4_11025 = 16;
	/// Static RTP/AVP payload type for the DVI4_11025 audio codec

	static const int DVI4_22050 = 17;
	/// Static RTP/AVP payload type for the DVI4_22050 audio codec.

	static const int G729 = 18;
	/// Static RTP/AVP payload type for the G729 audio codec.

	static const int CN_DEPRECATED = 19;
	/// Static RTP/AVP payload type for the CN audio codec.

	static const int CELB = 25;
	/// Static RTP/AVP payload type for the CELB video codec.

	static const int JPEG = 26;
	/// Static RTP/AVP payload type for the JPEG video codec.

	static const int NV = 28;
	/// Static RTP/AVP payload type for the NV video codec.

	static const int H261 = 31;
	/// Static RTP/AVP payload type for the H261 video codec.

	static const int MPV = 32;
	/// Static RTP/AVP payload type for the MPV video codec.

	static const int MP2T = 33;
	/// Static RTP/AVP payload type for the MP2T video codec.

	static const int H263 = 34;
	/// Static RTP/AVP payload type for the H263 video codec.

	static const int AVP_DEFINED_STATIC_MAX = 35;
	/// Highest defined static payload type. This is (currently) 35.

	static const int AVP_DYNAMIC_MIN = -35;
	/// The minimum defined dynamic format value

	static const std::string avpTypeNames[AVP_DEFINED_STATIC_MAX];
	/// Names of AVP (Audio-Video Profile) payload types indexed on their static payload types.

	static const int avpClockRates[AVP_DEFINED_STATIC_MAX];
	/// Clock rates for various AVP payload types indexed by their static payload types.

	static const int avpChannels[AVP_DEFINED_STATIC_MAX];
	/// Channels per static type.

} RtpAvpConstants;

} //	namespace SDP

#endif	//	__RTP_AVP_CONSTANTS__H__

