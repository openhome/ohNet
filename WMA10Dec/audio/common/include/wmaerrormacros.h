//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __WMAERRORMACROS_H
#define __WMAERRORMACROS_H

// *****************************************************
//                   Definitions
// *****************************************************
#ifdef _WIN32
#ifndef macintosh
#define PLATFORM_SPECIFIC_DEBUGINFRASTRUCTURE
#define PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING
#endif
#endif

#ifndef WMA_SUCCEEDED
#define WMA_SUCCEEDED(Status) ((WMARESULT)(Status) >= 0)
#endif  //WMA_SUCCEEDED(Status)
#ifndef WMA_FAILED
#define WMA_FAILED(Status)    ((WMARESULT)(Status) < 0)
#endif  //WMA_FAILED(Status)

#if defined(_DEBUG) && !defined(BUILD_IN_RTC_LCS_ENV)
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#if (!defined(_XBOX) && !defined(_NO_TRACERESULT_))

void TraceInfoHelper(const char *pszFile, int iLine, const char *pszFmt, ...);
WMARESULT MyOutputDbgStr(WMARESULT wmaReturn, const char *pszFmt, ...);

#else
INLINE void TraceInfoHelper( const char *pszFile, int iLine, const char *pszFmt, ...){}
INLINE WMARESULT MyOutputDbgStr(WMARESULT wmaReturn,const char *pszFmt, ...){ return wmaReturn; }
#endif

#ifdef __cplusplus
}
#endif  // __cplusplus

#ifdef WANT_TRACE_ONHOLD
// Tracing ONHOLD for decapp produces too many benign error messages.  But Wei-ge assures us that
// for wmadec_s, it can be useful.  If you want it, define the symbol above.
#define TraceResult(code)   MyOutputDbgStr((code), "%s(%d) : *** TRACE *** code = 0x%x!\n", \
                                    __FILE__, __LINE__, (code))
#else   // WANT_TRACE_ONHOLD
#define TraceResult(code)   ( ((code)==WMA_E_ONHOLD || (code)==WMA_OK) ?  (code) :              \
                                MyOutputDbgStr((code), "%s(%d) : *** TRACE *** code = 0x%x!\n", \
                                    __FILE__, __LINE__, (code)) )
#endif  // WANT_TRACE_ONHOLD

#define TraceError(code)    {   /* wmaFOOFOO to avoid naming collisions */                      \
                                WMARESULT wmaFOOFOO = (code);                                   \
                                if (WMA_FAILED(wmaFOOFOO))                                      \
                                    TraceResult(wmaFOOFOO);                                     \
                            }

#else   // _DEBUG

#define TraceResult(code)   (code)
#define TraceError(code)
#endif  // _DEBUG

extern void WMADebugMessage (const char*pszFmt, ...);

#define TRACEWMA_EXIT(wmaResult, action) \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                WMADebugMessage("TRACEWMA_EXIT @ %s:%d\n", __FILE__, __LINE__);\
                                {int dummy = TraceResult(wmaResult);}                           \
                                goto exit;                                                      \
                            } else {}
    
#define ASSERTWMA_EXIT(wmaResult, action) \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                int dummy;                                                      \
                                assert(WMAB_FALSE);                                             \
                                dummy = TraceResult(wmaResult);                                         \
                                goto exit;                                                      \
                            } else {}

#define CHECKWMA_EXIT(wmaResult) \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                int dummy = TraceResult(wmaResult);                                         \
                                goto exit;                                                      \
                            } else {}

#define TRACEWMA_RET(wmaResult, action) \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                return TraceResult(wmaResult);                                  \
                            } else {}

#define CHECKWMA_ALLOC(wmaResult, p) \
    if (NULL == p) \
    { \
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY); \
    }

#define CHECKWMA_FOPEN(wmaResult, p) \
    if (NULL == p) \
    { \
        TRACEWMA_EXIT(wmaResult, WMA_E_FILESTRMFILEIO); \
    }

#ifdef UNDER_CE

#include <windows.h>
// EXCEPTION_ACCESS_VIOLATION is not defined for some reason on SH4, so defining it here.
#ifndef EXCEPTION_ACCESS_VIOLATION
#define EXCEPTION_ACCESS_VIOLATION STATUS_ACCESS_VIOLATION
#endif 

#endif // UNDER_CE

#include "wmaassert.h"

#ifndef PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING
#define OUTPUT_DEBUG_STRING(sz) printf(sz)
#endif  // PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING

#endif // __WMAERRORMACROS_H
