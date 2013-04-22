//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    wmaerror.c

Abstract:

    Error handling functions

Author:

    Raymond Cheng (raych)       September 27, 1999

Revision History:


*************************************************************************/

#ifdef WMA_TARGET_ANSI
#include "ansiwin.h"
#else   // WMA_TARGET_ANSI

#ifndef _WIN32
#define _WIN32  // We need this when including windows.h
#endif  // !_WIN32

#ifndef __arm 
#ifdef _XBOX
#include <xtl.h>
#else
#include "windows.h"
#endif
#endif
#endif  // WMA_TARGET_ANSI

#include <stdio.h>
#include "wmacommon.h"
                
#ifdef PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING
#define OUTPUT_DEBUG_STRING(sz) OutputDebugString(sz)
#endif  // PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING

#if (!defined(_XBOX) && !defined(_NO_TRACERESULT_) && !defined(OPENHOME))

#if !defined(PLATFORM_SPECIFIC_DEBUGINFRASTRUCTURE) && defined(_DEBUG)
#include <stdarg.h>
void TraceInfoHelper(const char *pszFile, int iLine, const char *pszFmt, ...)
{
    char    sz[512];
    va_list vargs;
    Int     iCharsWritten;

    // Prepend file/line identifier and "*** INFO ***" to get attention
    iCharsWritten = sprintf(sz, "%s(%d) : *** INFO *** ", pszFile, iLine);

    va_start(vargs, pszFmt);
    iCharsWritten += vsprintf(sz + iCharsWritten, pszFmt, vargs);
    va_end(vargs);

    // Append a newline and print it!
    sprintf(sz + iCharsWritten, "\n");
    OUTPUT_DEBUG_STRING(sz);
}

WMARESULT MyOutputDbgStr(WMARESULT wmaReturn, const char *pszFmt, ...)
{
    char    sz[512];
    va_list vargs;

    va_start(vargs, pszFmt);
    vsprintf(sz, pszFmt, vargs);
    va_end(vargs);

    OUTPUT_DEBUG_STRING(sz);
    return wmaReturn;
}

#elif defined(PLATFORM_SPECIFIC_DEBUGINFRASTRUCTURE) && defined(_DEBUG)
#include <stdarg.h>
void TraceInfoHelper(const char *pszFile, int iLine, const char *pszFmt, ...)
{
    char    sz[512];
    va_list vargs;
    Int     iCharsWritten;

    // Prepend file/line identifier and "*** INFO ***" to get attention
    iCharsWritten = sprintf(sz, "%s(%d) : *** INFO *** ", pszFile, iLine);

    va_start(vargs, pszFmt);
    iCharsWritten += vsprintf(sz + iCharsWritten, pszFmt, vargs);
    va_end(vargs);

    // Append a newline and print it!
    sprintf(sz + iCharsWritten, "\n");
#if defined(_UNICODE) || defined(UNICODE)
    // let this do the string to unicode conversion
    MyOutputDbgStr(0,sz);
#else
    OUTPUT_DEBUG_STRING(sz);
#endif
}

WMARESULT MyOutputDbgStr(WMARESULT wmaReturn, const char *pszFmt, ...)
{
    TCHAR   sz[512];
    va_list vargs;
#if defined(_UNICODE) || defined(UNICODE)
    WCHAR wcsFmt[512];
    const WCHAR* pszFormat = wcsFmt;
    mbstowcs( wcsFmt, pszFmt, strlen(pszFmt)+1 );
#else
    const char* pszFormat = pszFmt;
#endif
    
    va_start(vargs, pszFmt);
    wvsprintf(sz, pszFormat, vargs);
    va_end(vargs);
    
    OUTPUT_DEBUG_STRING(sz);
    return wmaReturn;
}
#endif

#endif // !defined(_XBOX) && !defined(_NO_TRACERESULT_)
