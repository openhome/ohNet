//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Std, WMA Pro, and WMA Lossless.
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    wmamalloc.c

Abstract:

    Memory allocation functions

Author:

    Wei-ge Chen (wchen) 11-March-1998

Revision History:


*************************************************************************/
#if !defined(_WIN32)
#if defined(__stdcall)
#undef __stdcall
#endif
#define __stdcall
#endif

#if !defined(__arm) && !defined(_XBOX) && defined(_WIN32)
#include "windows.h"
#endif

#include <string.h>

#include "wmacommon.h"
#include "wmamalloc.h"
#include "wmspecstring.h"
#include "limits.h"

#if defined(_XBOX)
#include <xtl.h>

#define WMA_XALLOC_ATTRIBS MAKE_XALLOC_ATTRIBUTES(  1,                            \
                                                    0,                            \
                                                    0,                            \
                                                    1,                            \
                                                    eXALLOCAllocatorId_XMV,       \
                                                    XALLOC_ALIGNMENT_16,          \
                                                    XALLOC_MEMPROTECT_READWRITE,  \
                                                    0,                            \
                                                    XALLOC_MEMTYPE_HEAP )

__forceinline LPVOID static malloc( size_t size ){ return XMemAlloc( size, WMA_XALLOC_ATTRIBS ); }
__forceinline   VOID static free  ( LPVOID ptr  ){		  XMemFree ( ptr , WMA_XALLOC_ATTRIBS ); }
#endif

// This macro is needed in common audio macros!
#if !defined (INLINE)
#define PLATFORM_SPECIFIC_INLINE
#if _MSC_VER >= 1200            /* VC6.0 == 1200, VC5.0 == 1100 */
#define INLINE __forceinline
#else  /* _MSC_VER */
#define INLINE __inline
#endif /* _MSC_VER */
#endif // INLINE

INLINE I32 LOG2(U32 i)
{   // returns n where n = log2(2^n) = log2(2^(n+1)-1)
    U32 iLog2 = 0;
    assert (i != 0);

    while ((i >> iLog2) > 1)
        iLog2++;

    return iLog2;
}


//*****************************************************************************************
//
// WANT_HEAP_MEASURE defines the memory tracing functions
// It doens't work with RT memory allocation for MF.
// Only serve for testing and looking for memory leak purposes.
//
//*****************************************************************************************


#if !defined(WANT_HEAP_MEASURE)

//*****************************************************************************************
//
// mallocAligned & freeAligned
// allocates a buffer of size bytes aligned to iAlignToBytes bytes.
//
//*****************************************************************************************
void *mallocAligned(size_t size, Int iAlignToBytes)
{
    void *retBuffer;
    void *buffer;
    size_t mask = -1;                                    //Initally set mask to 0xFFFFFFFF
    size_t bufsize;

    if(iAlignToBytes<0 || size > UINT_MAX - iAlignToBytes)
    {
        return NULL;
    }
    bufsize = size+iAlignToBytes;
    
    buffer = (void *)auMalloc(bufsize);        //allocate buffer + alignment bytes
    if(buffer == NULL || iAlignToBytes < 4) // 4 here is an overconstraint. 2 should be fine.
    {
        int dummy;
        if (buffer)
        {
            auFree(buffer);
            buffer = NULL;
        }

        dummy = TraceResult(WMA_E_OUTOFMEMORY);
        return NULL;
    }
    assert(iAlignToBytes > 0);
    assert(iAlignToBytes < 256);
    mask <<= LOG2(iAlignToBytes);                     //Generate mask to clear lsb's
    retBuffer = (void*)(((size_t)((U8*)buffer+iAlignToBytes))&mask);//Generate aligned pointer
    ((U8*)retBuffer)[-1] = (U8)((U8*)retBuffer-(U8*)buffer);//Write offset to newPtr-1
    return retBuffer;
} // mallocAligned

void freeAligned(void *ptr)
{
    U8* realBuffer = (U8*)ptr;
    U8 bytesBack;
    if (realBuffer == NULL) return; 
    bytesBack = ((U8*)ptr)[-1];      //Get offset to real pointer from -1 possition
    realBuffer -= bytesBack;    //Get original pointer address
    auFree(realBuffer);
} // freeAligned


// ----- Memory Allocation Functions -----
#ifdef STATIC_MEMALLOC
#include "wmartmacros.h"
// Global vars
AVRT_DATA static MEMALLOCSTATE    g_maState = MAS_DELETE;
AVRT_DATA static U8              *g_pBuffer = NULL;
AVRT_DATA static U32              g_nBufRemaining = 0;
AVRT_DATA static I32              g_iAllocCount = 0;

I32 auMallocGetCount(void)
{
    return g_iAllocCount;
}

Void prvUESGetGlobalBuf(U8 **pbuf, I32 *pBufSize)
{
    *pbuf = g_pBuffer;
    *pBufSize = g_nBufRemaining;
    return;
}
void auMallocSetState(const MEMALLOCSTATE maState, void *pBuf, const U32 nBufSize)
{
    switch (maState)
    {
        case MAS_ALLOCATE:
            assert(MAS_DELETE == g_maState);
            g_pBuffer = (U8 *) pBuf;
            g_nBufRemaining = nBufSize;
            g_maState = MAS_ALLOCATE;
            break;

        case MAS_LOCKED:
            assert(MAS_ALLOCATE == g_maState);
            g_maState = MAS_LOCKED;
            break;

        case MAS_DELETE:
            g_maState = MAS_DELETE;
            break;

        default:
            assert(0);
            break;
    }
} // auMallocSetState


void * __stdcall auMalloc(const size_t iSize)
{
    WMARESULT   wmaResult = WMA_OK;
    void       *pResult = NULL;

    switch (g_maState)
    {
        case MAS_ALLOCATE:

            if (NULL == g_pBuffer)
            {
                pResult = malloc(iSize);
                if (NULL == pResult)
                    wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            }
            else
            {
                if (iSize <= (U32) g_nBufRemaining)
                {
                    pResult = g_pBuffer;
                    g_pBuffer += iSize;
                    g_nBufRemaining -= iSize;
                }
                else
                {
                    wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
                    assert(0);
                }
            }

            g_iAllocCount += iSize;
            break;

        default:
            wmaResult = TraceResult(WMA_E_FAIL);
            assert(0); // We should only be called during allocation
            break;
    }

    return pResult;
} // auMalloc

void __stdcall auFree(void *pFree)
{
    assert(MAS_DELETE == g_maState);
    if (NULL == g_pBuffer)
        free(pFree);
}
#else   // STATIC_MEMALLOC

I32 auMallocGetCount(void)
{
    return 0;
}
Void prvUESGetGlobalBuf(U8 **pbuf, I32 *pBufSize)
{
}
void auMallocSetState(const MEMALLOCSTATE maState, void *pBuf, const U32 nBufSize)
{
}

#ifndef AUMALLOC_RT_HEAP

#if defined(WMAMALLOC_PRTMEM)
Int g_size;
#endif
void * __stdcall auMalloc(const size_t iSize)
{
#if defined(WMAMALLOC_PRTMEM)
    g_size += iSize;
#endif
    return malloc(iSize);
}


void __stdcall auFree(void *pFree)
{
    free(pFree);
}

#endif//AUMALLOC_RT_HEAP

#endif  // STATIC_MEMALLOC


#else //Implement Heap/Stack Tracing Functions
/*******************************************************************************************************
**  Implement wmv memallo and free and heap stack tracing functions.            
********************************************************************************************************/

I32 auMallocGetCount(void)
{
    return 0;
}
Void prvUESGetGlobalBuf(U8 **pbuf, I32 *pBufSize)
{
}
void auMallocSetState(const MEMALLOCSTATE maState, void *pBuf, const U32 nBufSize)
{
}


#endif //WANT_STACK_MEASURE

void* auCalloc(const size_t iSize)
{
    void *pv = auMalloc(iSize);
    if (pv)
        memset(pv, 0, (unsigned int)iSize);
    return pv;
}

void* callocAligned(size_t iSize, WMA_I32 iAlignToBytes)
{
    void *pv = mallocAligned(iSize, iAlignToBytes);
    if (pv)
        memset(pv, 0, (unsigned int)iSize);
    return pv;
}
