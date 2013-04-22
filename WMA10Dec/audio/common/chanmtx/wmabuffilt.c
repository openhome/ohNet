//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifdef SCRAMBLE_GLOBAL_SYMBOL_NAMES
#include "scramble.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wmacommon.h"
#include "wmspecstring.h"
#include "wmamalloc.h"
#include "wmabuffilt.h"


#if defined(_SH4_)
#pragma warning(push)
#pragma warning(disable:4719)
#endif

#include "wmartmacros.h"
//#pragma AVRT_CODE_BEGIN

#define DELETE_ARRAY(ptr) if (ptr!=NULL) { auFree (ptr); ptr = NULL; }
#define DELETE_PTR(ptr) if (ptr!=NULL) { auFree (ptr); ptr = NULL; }

// -----------------------------------------------------------------------------
// Filter functions
//------------------------------------------------------------------------------
void bufFiltZero(BufFilt *pBufFilt)
{
    memset(pBufFilt, 0, sizeof(BufFilt));
}

void bufFiltFree(BufFilt *pBufFilt)
{
    freeAligned(pBufFilt->m_filtCoeffs);
    pBufFilt->m_filtCoeffs = NULL;

    freeAligned(pBufFilt->m_dataBuf);
    pBufFilt->m_dataBuf = NULL;

    bufFiltZero(pBufFilt);
}

#define ABS(x) ((x) > 0 ? (x) : (-(x)))

WMARESULT bufFiltInit(BufFilt *pBufFilt, Double *coeffs, __in_bound Int startPos,
                      __in_bound Int endPos, Int cInputs)
{
    WMARESULT hr = WMA_OK;
    Int i, iLengthCoefPad, iLengthDataPad;

    assert(pBufFilt != NULL);

    bufFiltFree(pBufFilt);

    pBufFilt->m_iStartPos = startPos;

    if (ABS(pBufFilt->m_iStartPos) > 100000 || ABS(endPos) > 100000)
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }

    pBufFilt->m_iLength = endPos - pBufFilt->m_iStartPos + 1;

    if ( pBufFilt->m_iStartPos > 0 ) { hr = WMA_E_INVALIDARG;  goto exit; }
    if (pBufFilt->m_iLength - pBufFilt->m_iStartPos <= 0)
    { hr = WMA_E_INVALIDARG;  goto exit; }
    if ( pBufFilt->m_iLength <= 0 ) { hr = WMA_E_INVALIDARG;  goto exit; }

    // alloc coefs space; pad with zeros to multiple of 4
    iLengthCoefPad = (pBufFilt->m_iLength + 3) >> 2 << 2;
    pBufFilt->m_filtCoeffs = (CompType*)mallocAligned(iLengthCoefPad * sizeof(CompType), 16);
    CHECKWMA_ALLOC(hr, pBufFilt->m_filtCoeffs);
    memset(pBufFilt->m_filtCoeffs, 0, iLengthCoefPad * sizeof(CompType));

    // flip coefficients
    for (i = 0; i < pBufFilt->m_iLength; i++)
    {
        pBufFilt->m_filtCoeffs[pBufFilt->m_iLength-1-i] = (CompType)coeffs[i];
    }

    // zero the 2nd half (relying on anti-symmetry of filter)
    for (i = pBufFilt->m_iLength >> 1; i < iLengthCoefPad; i++)
    {
        pBufFilt->m_filtCoeffs[i] = 0;
    }

    // alloc data space; pad with zeros
    iLengthDataPad = (pBufFilt->m_iLength - 1 + cInputs) + 7;
    pBufFilt->m_dataBuf = (DataType*)mallocAligned(iLengthDataPad * sizeof(DataType), 16);
    CHECKWMA_ALLOC(hr, pBufFilt->m_dataBuf);
    memset(pBufFilt->m_dataBuf, 0, iLengthDataPad * sizeof(DataType));

    for (i = 0; i < iLengthDataPad; i++)
    {
        pBufFilt->m_dataBuf[i] = (DataType)0;
    }

    pBufFilt->m_curBufLen = pBufFilt->m_iLength - 1;

exit:
    return hr;
}

// -----------------------------------------------------------------------------
// bufFilt - filter buffer, unoptimized version when SSE1 is NOT supported
//------------------------------------------------------------------------------
WMARESULT bufFilt(BufFilt *pBufFilt, float *pInOutBuf, Int cLen)
{
    float *pOut = pInOutBuf, *pData0, *pData1, *pCoef, total;
    Int cCoef, i, j;

    assert(pBufFilt && pInOutBuf);

    memcpy(pBufFilt->m_dataBuf + pBufFilt->m_curBufLen, pInOutBuf, cLen * sizeof(float));

    // do filter
    cCoef = pBufFilt->m_iLength >> 1;
    for (i = 0; i < cLen; i++)
    {
        total = 0;
        pCoef = pBufFilt->m_filtCoeffs;
        pData0 = pBufFilt->m_dataBuf + i;
        pData1 = pBufFilt->m_dataBuf + i + pBufFilt->m_iLength - 1;
        for (j = 0; j < cCoef; j++)
        {
            total += (*pCoef++) * ((*pData0++) - (*pData1--));
        }
        *pOut++ = total;
    }

    // copy data history to the beginning of data buffer
    memmove(pBufFilt->m_dataBuf, pBufFilt->m_dataBuf + cLen,
            pBufFilt->m_curBufLen * sizeof(float));

    return WMA_OK;
}

#if defined (WMA_TARGET_X86) && !defined(WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
// -----------------------------------------------------------------------------
// bufFilt_SSE - filter buffer, optimized version when SSE1 is supported
//------------------------------------------------------------------------------
WMARESULT bufFilt_SSE(BufFilt *pBufFilt, float *pInOutBuf, Int cLen)
{
    __m128 total0, total1, total2, total3;
    __m128 coef, data0, data1, data2, data3;
    Int cData, cCoef;
    float *pOut = pInOutBuf, *pData0, *pData1, *pCoef, *pDataBuf;

    assert(pBufFilt && pInOutBuf);

    memcpy(pBufFilt->m_dataBuf + pBufFilt->m_curBufLen, pInOutBuf, cLen * sizeof(float));

    // do filter, 4 inputs at a time
    pDataBuf = pBufFilt->m_dataBuf;
    cData = cLen;
    for (; cData > 0; cData -= 4)
    {
        // init ptrs and zero accumulators
        cCoef = pBufFilt->m_iLength;
        pCoef = pBufFilt->m_filtCoeffs;
        total0 = _mm_setzero_ps();
        total1 = total0;
        total2 = total0;
        total3 = total0;
        pData0 = pDataBuf;
        pData1 = pDataBuf + cCoef - 4;
        pDataBuf += 4;

        // When accumulating filter outputs for 4 inputs, take advantage of
        // antisymmetrical coefficients: h(i) = -h(pBufFilt->m_curBufLen - i)
        // and the middle coefficient is always zero. Inputs from the back end
        // must be reversed before being subtracted from inputs from the front
        // end.
        for (; cCoef > 1; cCoef -= 8) 
        {
            // load 4 filter coefficients
            coef = _mm_load_ps(pCoef);

            // accumulate outputs 0, 1
            data0 = _mm_load_ps(pData0);
            data2 = _mm_loadu_ps(pData1);
            data1 = _mm_loadu_ps(pData0 + 1);
            data3 = _mm_loadu_ps(pData1 + 1);
            data2 = _mm_shuffle_ps(data2, data2, _MM_SHUFFLE(0, 1, 2, 3));
            data3 = _mm_shuffle_ps(data3, data3, _MM_SHUFFLE(0, 1, 2, 3));
            data0 = _mm_sub_ps(data0, data2);
            data1 = _mm_sub_ps(data1, data3);
            data0 = _mm_mul_ps(data0, coef);
            data1 = _mm_mul_ps(data1, coef);
            total0 = _mm_add_ps(total0, data0);    
            total1 = _mm_add_ps(total1, data1);    

            // accumulate outputs 2, 3
            data0 = _mm_loadu_ps(pData0 + 2);
            data2 = _mm_loadu_ps(pData1 + 2);
            data1 = _mm_loadu_ps(pData0 + 3);
            data3 = _mm_loadu_ps(pData1 + 3);
            data2 = _mm_shuffle_ps(data2, data2, _MM_SHUFFLE(0, 1, 2, 3));
            data3 = _mm_shuffle_ps(data3, data3, _MM_SHUFFLE(0, 1, 2, 3));
            data0 = _mm_sub_ps(data0, data2);
            data1 = _mm_sub_ps(data1, data3);
            data0 = _mm_mul_ps(data0, coef);
            data1 = _mm_mul_ps(data1, coef);
            total2 = _mm_add_ps(total2, data0);    
            total3 = _mm_add_ps(total3, data1);  

            // update ptrs
            pData0 += 4;
            pData1 -= 4;
            pCoef += 4;
        }

        // Transpose a 4x4 matrix.
        // This is helpful for horizontal add and since _mm_hadd_ps is only
        // available in SSE3. The following lines convert:
        //
        // (total0 = A B C D)      (M I E A = total1)
        // (total1 = E F G H)  ==> (N J F B = total0)
        // (total2 = I J K L)  ==> (O K G C = data0)
        // (total3 = M N O P)      (P L H D = data1)
        data0 = _mm_shuffle_ps(total2, total3, _MM_SHUFFLE(3, 2, 3, 2));
        data1 = _mm_shuffle_ps(total2, total3, _MM_SHUFFLE(1, 0, 1, 0));
        total3 = _mm_shuffle_ps(total0, total1, _MM_SHUFFLE(3, 2, 3, 2));
        total2 = _mm_shuffle_ps(total0, total1, _MM_SHUFFLE(1, 0, 1, 0));
        total1 = _mm_shuffle_ps(total3, data0, _MM_SHUFFLE(3, 1, 3, 1));
        total0 = _mm_shuffle_ps(total3, data0, _MM_SHUFFLE(2, 0, 2, 0));
        data0 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(3, 1, 3, 1));
        data1 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(2, 0, 2, 0));

        // sum the columns (across original totals)
        total3 = _mm_add_ps(total1, total0);
        total2 = _mm_add_ps(data0, data1);
        total0 = _mm_add_ps(total2, total3);

        // store outputs
        _mm_store_ps(pOut, total0);
        pOut += 4;
    }

    // copy data history to the beginning of data buffer
    memmove(pBufFilt->m_dataBuf, pBufFilt->m_dataBuf + cLen,
            pBufFilt->m_curBufLen * sizeof(float));

    return WMA_OK;
}
#endif // UNDER_CE && UNDER_CE<500
#endif // WMA_TARGET_X86 && !WMA_DISABLE_SSE1

// -----------------------------------------------------------------------------
// In place delay functions (no scaling)
//------------------------------------------------------------------------------
void bufDelayZero(BufDelay *pBufDelay)
{
    memset(pBufDelay, 0, sizeof(BufDelay));
}

void bufDelayFree(BufDelay *pBufDelay)
{
    DELETE_ARRAY(pBufDelay->m_dataBuf);
    DELETE_ARRAY(pBufDelay->m_endDataBuf);
    bufDelayZero(pBufDelay);
}

WMARESULT bufDelayInit(BufDelay *pBufDelay, Int delay)
{
    WMARESULT hr = WMA_OK;

    assert(pBufDelay != NULL);

    if (delay < 0 || delay > 100000) { hr = WMA_E_INVALIDARG;  goto exit; }

    bufDelayFree(pBufDelay);

    pBufDelay->m_iDelay = delay;

    pBufDelay->m_dataBuf = (DataType*)auMalloc(pBufDelay->m_iDelay * sizeof(DataType));
    CHECKWMA_ALLOC(hr, pBufDelay->m_dataBuf);
    memset(pBufDelay->m_dataBuf, 0, pBufDelay->m_iDelay * sizeof(DataType));

    pBufDelay->m_endDataBuf = (DataType*)auMalloc(pBufDelay->m_iDelay * sizeof(DataType));
    CHECKWMA_ALLOC(hr, pBufDelay->m_endDataBuf);
    memset(pBufDelay->m_endDataBuf, 0, pBufDelay->m_iDelay * sizeof(DataType));

    pBufDelay->m_curBufLen = pBufDelay->m_iDelay;

exit:
    return hr;
}

WMARESULT bufDelay(BufDelay *pBufDelay, float *in, Int inLen, Int *pOutLen)
{
    WMARESULT hr = WMA_OK;
    Int i, ptsToSave, ptsOut = 0, ptsDone = 0, ptsToGo = 0;
    DataType *pOut, *pBuf;

    assert(pBufDelay && in);

    ptsOut = inLen - pBufDelay->m_iDelay + pBufDelay->m_curBufLen;
    ptsOut = ((ptsOut < 0) ? 0 : ptsOut);

    if (ptsOut >= pBufDelay->m_curBufLen)
    {
        ptsToSave = inLen - ptsOut + pBufDelay->m_curBufLen;
        assert(ptsToSave == pBufDelay->m_iDelay);
    }
    else
    {
        ptsToSave = inLen;
    }
    assert(ptsToSave <= pBufDelay->m_iDelay);
    memcpy(pBufDelay->m_endDataBuf, in + inLen - ptsToSave, ptsToSave * sizeof(DataType));

    // first loop valid when ptsOut-1-i-delay >= 0
    //   or -i >= delay+1-ptsOut
    //       i <= -delay-1+ptsOut
    //       i < ptsOut-delay
    pOut = in + ptsOut - 1;
    if (ptsOut - pBufDelay->m_curBufLen >= 0) assert(pBufDelay->m_iDelay == pBufDelay->m_curBufLen);
    for (i = 0; i < ptsOut - pBufDelay->m_curBufLen; i++)
    {
        *pOut = *(pOut - pBufDelay->m_iDelay);
        pOut--;
    }
    ptsDone = ptsOut - pBufDelay->m_curBufLen;
    ptsDone = ((ptsDone < 0) ? 0 : ptsDone);
    ptsToGo = ptsOut - ptsDone;
    if (ptsDone > 0) assert(pBufDelay->m_curBufLen == ptsToGo);
    pBuf = pBufDelay->m_dataBuf + ptsToGo - 1;
    for (i = 0; i < ptsToGo; i++)
    {
        *pOut-- = *pBuf--;
    }
    assert(pOut + 1 == in);

    if (ptsOut >= pBufDelay->m_curBufLen)
    {
        memcpy(pBufDelay->m_dataBuf, pBufDelay->m_endDataBuf, ptsToSave * sizeof(DataType));
        pBufDelay->m_curBufLen = ptsToSave;
    }
    else
    {
        assert(ptsToSave == inLen);
        assert(pBufDelay->m_curBufLen - ptsOut + ptsToSave <= pBufDelay->m_iDelay);
        memmove(pBufDelay->m_dataBuf, pBufDelay->m_dataBuf + ptsOut,
            (pBufDelay->m_curBufLen - ptsOut) * sizeof(DataType));
        memcpy(pBufDelay->m_dataBuf + pBufDelay->m_curBufLen - ptsOut, pBufDelay->m_endDataBuf,
            ptsToSave * sizeof(DataType));
        pBufDelay->m_curBufLen = pBufDelay->m_curBufLen - ptsOut + ptsToSave;
        assert(pBufDelay->m_curBufLen <= pBufDelay->m_iDelay);
    }

    if (pOutLen) *pOutLen = ptsOut;

    return hr;
}

#if defined(_SH4_)
#pragma warning(pop)
#endif
