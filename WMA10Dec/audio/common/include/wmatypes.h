//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    wmatypes.h

Abstract:

    Processor-specific data types.

Author:

    Kazuhito Koishida (kazukoi)       Jan 31, 2003

Revision History:

*************************************************************************/

#ifndef __WMATYPES_H
#define __WMATYPES_H

// ***************************************************
//           Platform-Specific typedefs
// ***************************************************
#ifndef DISABLE_OPT	// If this is defined, use the ANSI build

#ifdef __QNX__
#undef _M_IX86
#endif

#if defined(_M_IX86) && !defined(INTEGER_ENCODER)
//#ifdef __QNX__
//#define WMA_TARGET_QNX_X86
//#else
#define WMA_TARGET_X86
//#endif
#endif

#ifdef _M_AMD64
  #ifndef WMA_TARGET_WIN64
    #define WMA_TARGET_WIN64
  #endif
#endif

#ifdef _M_IA64
  #ifndef WMA_TARGET_WIN64
    #define WMA_TARGET_WIN64
  #endif
  #ifndef DISABLE_INTELFFT
    #define DISABLE_INTELFFT
  #endif 
#endif

#ifdef _MIPS_
#define WMA_TARGET_MIPS
#endif

#if defined(_SH3_) && !defined(_SH4_)
#define WMA_TARGET_SH3
#endif

#ifdef _SH4_
#define WMA_TARGET_SH4
#endif

#ifdef _Embedded_x86
#define WMA_TARGET_Embedded_x86
#endif

#ifdef S_SUNOS5
#define WMA_TARGET_S_SUNOS5
#endif

#ifdef _ARM_
#define WMA_TARGET_ARM
#endif

// It's often nice to be able to compare the output between optimized versions
// and the ANSI version, to verify that the optimizations are in sync. Alas,
// some optimizations sacrifice reproducibility for speed. The following #define allows
// us to disable those optimizations to verify the main algorithms.
//#define WMA_ANSI_COMPATIBILITY_MODE

#endif	// !DISABLE_OPT

#if defined(WMA_TARGET_WIN64)
#include "wmatypes_win64.h"
#elif defined(WMA_TARGET_X86)
#include "wmatypes_x86.h"
#elif defined(WMA_TARGET_QNX_X86)
#include "wmatypes_qnx_x86.h"
#elif defined(WMA_TARGET_MIPS)
#include "wmatypes_mips.h"
#elif defined(WMA_TARGET_SH3)
#include "wmatypes_sh3.h"
#elif defined(WMA_TARGET_SH4)
#include "wmatypes_sh4.h"
#elif defined(WMA_TARGET_ARM)
#include "wmatypes_arm.h"
#elif defined(WMA_TARGET_Embedded_x86)
#include "wmatypes_embedded_x86.h"
#elif defined(WMA_TARGET_S_SUNOS5)
#include "wmatypes_s_sunos5.h"
#elif defined(WMA_TARGET_MACOS)
#include "wmatypes_macos.h"
#else
#include "wmatypes_ansi.h"
#endif // platform specific #ifdefs


// **************************************************************************
// Overridable Compiler Directives
// **************************************************************************
#ifndef PLATFORM_SPECIFIC_INLINE
// This should hopefully work for most compilers. It works for VC
//#define INLINE __inline
#ifndef INLINE
#define INLINE extern inline
#else
#error INLINE already defined ***********************************************************************
#endif
#ifndef STATIC_INLINE
#define STATIC_INLINE static inline
#else
#error STATIC_INLINE already defined ***********************************************************************
#endif
#ifndef FORCEINLINE
#define FORCEINLINE extern inline
#else
#error FORCEINLINE already defined ***********************************************************************
#endif

#endif  // PLATFORM_SPECIFIC_INLINE


// ***************************************************
//            default fundamental typedefs
// ***************************************************
#ifndef PLATFORM_SPECIFIC_U64
typedef unsigned __int64 U64;
#endif
#ifndef PLATFORM_SPECIFIC_I64
typedef __int64 I64;
#endif

#ifndef PLATFORM_SPECIFIC_U32
typedef unsigned long int U32;
#define U32_MAX ((U32)0xffffffffu)
#endif
#ifndef PLATFORM_SPECIFIC_I32
typedef long int I32;
#define I32_MIN ((I32)0x80000000)
#define I32_MAX ((I32)0x7fffffff)
#endif

#ifndef PLATFORM_SPECIFIC_U16
typedef unsigned short U16;
#define U16_MAX ((I32)0x0000ffff)
#endif
#ifndef PLATFORM_SPECIFIC_I16
typedef short I16;
#define I16_MIN ((I32)0xffff8000)
#define I16_MAX ((I32)0x00007fff)
#endif

#ifndef PLATFORM_SPECIFIC_U8
typedef unsigned char U8;
#define U8_MAX ((I32)0x000000ff)
#endif
#ifndef PLATFORM_SPECIFIC_I8
typedef signed char I8;
#define I8_MIN ((I32)0xffffff80)
#define I8_MAX ((I32)0x0000007f)
#endif

#ifndef PLATFORM_SPECIFIC_F32
typedef float F32;
#endif
#ifndef PLATFORM_SPECIFIC_F64
typedef double F64;
#endif

// the following "UP" types are for using n-bit or native type, in case
// using native types might be faster.
#ifndef PLATFORM_SPECIFIC_I8UP
typedef int I8UP;
#endif

#ifndef PLATFORM_SPECIFIC_U8UP
typedef unsigned U8UP;
#endif

#ifndef PLATFORM_SPECIFIC_I16UP
typedef int I16UP;
#endif

#ifndef PLATFORM_SPECIFIC_U16UP
typedef unsigned U16UP;
#endif

#ifndef PLATFORM_SPECIFIC_I32UP
typedef int I32UP;
#endif

#ifndef PLATFORM_SPECIFIC_U32UP
typedef unsigned U32UP;
#endif

#ifndef PLATFORM_SPECIFIC_I64UP
#ifdef _WIN32
typedef __int64 I64UP;
#else
typedef int64_t I64UP;
#endif
#endif

#ifndef PLATFORM_SPECIFIC_U64UP
#ifdef _WIN32
typedef unsigned __int64 U64UP;
#else
typedef uint64_t U64UP;
# endif
#endif

#ifndef PLATFORM_SPECIFIC_F32UP
typedef float F32UP;
#endif
#ifndef PLATFORM_SPECIFIC_F64UP
typedef double F64UP;
#endif

#ifndef	PLATFORM_SPECIFIC_CBDATA
typedef void* CBDATA; // callback data parameter
#endif // PLATFORM_SPECIFIC_CBDATA

typedef double  Double;
typedef float   Float;
typedef void    Void;
typedef U32     UInt;
typedef I32     Int;
typedef I32     Bool; // In Win32, BOOL is an "int" == 4 bytes. Keep it this way to reduce problems.
typedef char    Char;

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef FAR
#define FAR
#endif

// define basic types
#ifdef _WIN32
typedef __int64         WMA_I64;
#else
typedef int64_t         WMA_I64;
#endif
typedef unsigned long   WMA_U32;
typedef long            WMA_I32;
typedef unsigned short  WMA_U16;
typedef short           WMA_I16;
typedef unsigned char   WMA_U8;
typedef WMA_I32         WMA_Bool;

typedef int WMARESULT;

#endif  // __WMATYPES_H
