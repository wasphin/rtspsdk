/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Header Stream classes
//
//	description:
//		a set of classes used for internal work with 
//		RTSP requests and responses headers
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


#ifndef __RTSP_HEADER_STREAM__H__
#define __RTSP_HEADER_STREAM__H__

#include <cstddef>
#include <istream>
#include <ostream>

#include "Poco/Net/Net.h"
#include "Poco/MemoryPool.h"

#include "rtsp_sdk.h"
#include "RTSPBasicStreamBuf.h"

namespace RTSP {


class RTSPSession;


class RTSP_SDK_API RTSPHeaderStreamBuf: public RTSPBasicStreamBuf
	/// This is the streambuf class used for reading from a RTSP header
	/// in a RTSPSession.
{
public:
	typedef RTSPBasicStreamBuf::openmode openmode;

	RTSPHeaderStreamBuf(RTSPSession& session, openmode mode);
	~RTSPHeaderStreamBuf();
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	RTSPSession& _session;
	bool         _end;
};


class RTSP_SDK_API RTSPHeaderIOS: public virtual std::ios
	/// The base class for RTSPHeaderInputStream.
{
public:
	RTSPHeaderIOS(RTSPSession& session, RTSPHeaderStreamBuf::openmode mode);
	~RTSPHeaderIOS();
	RTSPHeaderStreamBuf* rdbuf();

protected:
	RTSPHeaderStreamBuf _buf;
};


class RTSP_SDK_API RTSPHeaderInputStream: public RTSPHeaderIOS, public std::istream
	/// This class is for internal use by RTSPSession only.
{
public:
	RTSPHeaderInputStream(RTSPSession& session);
	~RTSPHeaderInputStream();

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


class RTSP_SDK_API RTSPHeaderOutputStream: public RTSPHeaderIOS, public std::ostream
	/// This class is for internal use by RTSPSession only.
{
public:
	RTSPHeaderOutputStream(RTSPSession& session);
	~RTSPHeaderOutputStream();

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


} // namespace RTSP


#endif // __RTSP_HEADER_STREAM__H__
