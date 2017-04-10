///
/// \package astlib
/// \file Astlib.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

namespace astlib
{

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSON_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSON_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(ASTLIB_DLL)
	#if defined(ASTLIB_EXPORTS)
		#define ASTLIB_API __declspec(dllexport)
	#else
		#define ASTLIB_API __declspec(dllimport)
	#endif
#endif


#if !defined(ASTLIB_API)
	#if !defined(ASTLIB_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define ASTLIB_API __attribute__ ((visibility ("default")))
	#else
		#define ASTLIB_API
	#endif
#endif


#define ASTLIB_MAJOR 0x01
#define ASTLIB_MINOR 0x00
#define ASTLIB_PATCH 0x00

#define ASTLIB_VERSION ((ASTLIB_MAJOR<<16) | ASTLIB_MINOR<<8 | ASTLIB_PATCH)

} /* namespace astlib */

