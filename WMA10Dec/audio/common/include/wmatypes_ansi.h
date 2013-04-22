//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    wmatypes_ansi.h

Abstract:

    ANSI-C data types.

Author:

    Kazuhito Koishida (kazukoi)       Jan 31, 2003

Revision History:


*************************************************************************/

#ifndef __WMATYPES_ANSI_H
#define __WMATYPES_ANSI_H

// Do the fundamental typedefs: {U|I}{8|16|32|64}
#ifdef NOINT64 

#include "int64.h"
#define PLATFORM_SPECIFIC_U64
typedef UINT64 U64;
#define PLATFORM_SPECIFIC_I64?
typedef INT64 I64;

#else
#ifdef __QNX__

#define PLATFORM_SPECIFIC_U64
typedef unsigned long long int U64;
#define PLATFORM_SPECIFIC_I64
typedef long long int I64;

#else
#ifdef macintosh

#define PLATFORM_SPECIFIC_U64
typedef unsigned long long U64;
#define PLATFORM_SPECIFIC_I64
typedef long long I64;

#else
#include <stdint.h>
#define PLATFORM_SPECIFIC_U64
typedef uint64_t U64;
#define PLATFORM_SPECIFIC_I64
typedef int64_t I64;

#ifdef UNICODE
typedef unsigned short  TCHAR;                  // From winnt.h and stdio.h
#else
typedef char            TCHAR;                  // From winnt.h
#endif  // UNICODE

#endif
#endif
#endif //NOINT64

#endif  //_WMATYPES_ANSI_H
