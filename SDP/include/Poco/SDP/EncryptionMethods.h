/*****************************************************************************
//	SDP Parser Classes
//
//	Encryption Methods 
//
//	description:
//		represents a list of encryption methods defined in RFC 2327
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

#ifndef __ENCRYPTION_METHODS__H__
#define __ENCRYPTION_METHODS__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Poco/SDP/Common.h"

namespace Poco {
namespace SDP {

typedef struct SDP_API _EncryptionMethod
/// A structure of listed encryption methods.
{
	static const std::string None;
	 /// The encryption key is left untransformed.

	static const std::string Base64;
	/// The encryption key is Base64 encoded because it contains
	/// characters that are prohibited in SDP.

	static const std::string Uri;
	/// Specifies a URI at which the key can be found. Additional
	/// authentication may be required to obtain this key. The mime
	/// content-type of the reply constitutes the encoding for the key.

	static const std::string Prompt;
	/// Specifies that the user should be prompted for a key.

} EncryptionMethod;

} //	namespace SDP
} //	namespace Poco

#endif	//	__ENCRYPTION_METHODS__H__

