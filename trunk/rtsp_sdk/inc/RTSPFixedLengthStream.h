/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Fixed Length Stream classes
//
//	description:
//		a set of classes used for internal work with 
//		RTSP requests and responses with fixed message length
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


#ifndef __RTSP_FIXED_LENGTH_STREAM__H__
#define __RTSP_FIXED_LENGTH_STREAM__H__

#include <cstddef>
#include <istream>
#include <ostream>

#include "Poco/Net/Net.h"

#include "rtsp_sdk.h"
#include "RTSPBasicStreamBuf.h"

namespace RTSP {


class RTSPSession;


class RTSP_SDK_API RTSPFixedLengthStreamBuf: public RTSPBasicStreamBuf
	/// This is the streambuf class used for reading and writing fixed-size
	/// RTSP message bodies.
	///
	/// At most a given number of bytes are read or written.
{
public:
	typedef RTSPBasicStreamBuf::openmode openmode;

	RTSPFixedLengthStreamBuf(RTSPSession& session, std::streamsize length, openmode mode);
	~RTSPFixedLengthStreamBuf();
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	RTSPSession&    _session;
	std::streamsize _length;
	std::streamsize _count;
};


class RTSP_SDK_API RTSPFixedLengthIOS: public virtual std::ios
	/// The base class for RTSPFixedLengthInputStream.
{
public:
	RTSPFixedLengthIOS(RTSPSession& session, std::streamsize length, RTSPFixedLengthStreamBuf::openmode mode);
	~RTSPFixedLengthIOS();
	RTSPFixedLengthStreamBuf* rdbuf();

protected:
	RTSPFixedLengthStreamBuf _buf;
};


class RTSP_SDK_API RTSPFixedLengthInputStream: public RTSPFixedLengthIOS, public std::istream
	/// This class is for internal use by RTSPSession only.
{
public:
	RTSPFixedLengthInputStream(RTSPSession& session, std::streamsize length);
	~RTSPFixedLengthInputStream();
	
	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


class RTSP_SDK_API RTSPFixedLengthOutputStream: public RTSPFixedLengthIOS, public std::ostream
	/// This class is for internal use by RTSPSession only.
{
public:
	RTSPFixedLengthOutputStream(RTSPSession& session, std::streamsize length);
	~RTSPFixedLengthOutputStream();

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


} // namespace RTSP


#endif // __RTSP_FIXED_LENGTH_STREAM__H__
