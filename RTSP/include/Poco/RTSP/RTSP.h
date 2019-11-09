//
// RTSP.h
//
// Library: RTSP
// Package: RTSP
// Module:  RTSP
//
// Basic definitions for the Poco RTSP library.
// This file must be the first file included by every other RTSP
// header file.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RTSP_RTSP_INCLUDED
#define RTSP_RTSP_INCLUDED

#include "Poco/Foundation.h"

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RTSP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RTSP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(RTSP_EXPORTS)
		#define RTSP_API __declspec(dllexport)
	#else
		#define RTSP_API __declspec(dllimport)
	#endif
#endif


#if !defined(RTSP_API)
	#if !defined(POCO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define RTSP_API __attribute__ ((visibility ("default")))
	#else
		#define RTSP_API
	#endif
#endif


//
// Automatically link RTSP library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(RTSP_EXPORTS)
		#pragma comment(lib, "PocoRTSP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // RTSP_RTSP_INCLUDED