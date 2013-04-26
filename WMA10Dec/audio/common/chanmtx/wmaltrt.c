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
#include "wmaltrt.h"
#include "wmachmtx.h"
#include "wmaassert.h"
#include "limits.h"

#ifndef _XBOX
#include "cpudetect.h"
#endif

#ifndef WMAB_FALSE
#define WMAB_FALSE False
#endif

//#ifdef __arm
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))
//#endif //__arm

#if defined(_SH4_)
#pragma warning(push)
#pragma warning(disable:4719)
#endif

#include "wmartmacros.h"
//#pragma AVRT_CODE_BEGIN

#define DELETE_ARRAY(ptr) if (ptr!=NULL) { auFree (ptr); ptr = NULL; }
#define DELETE_PTR(ptr) if (ptr!=NULL) { auFree (ptr); ptr = NULL; }

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define PI  3.1415926535897932384626433832795

void ltrtDownmixZero(LtRtDownmix *pLtRtDownmix)
{
    memset(pLtRtDownmix, 0, sizeof(LtRtDownmix));

    bufFiltZero(&pLtRtDownmix->m_bfSurround);
    bufDelayZero(&pLtRtDownmix->m_bfLeft);
    bufDelayZero(&pLtRtDownmix->m_bfRight);

    pLtRtDownmix->m_bCanFree = True;

    pLtRtDownmix->m_fLRGain = 1.0f;
    pLtRtDownmix->m_fCGain = 1.0f;
    pLtRtDownmix->m_fSGain = 1.0f;
    pLtRtDownmix->m_fLFEGain = 1.0f;
}

void ltrtDownmixFree(LtRtDownmix *pLtRtDownmix)
{
    if (True == pLtRtDownmix->m_bCanFree)
    {
        bufFiltFree(&pLtRtDownmix->m_bfSurround);
        bufDelayFree(&pLtRtDownmix->m_bfLeft);
        bufDelayFree(&pLtRtDownmix->m_bfRight);

        if (pLtRtDownmix->m_buf)
        {
            freeAligned(pLtRtDownmix->m_buf);
            pLtRtDownmix->m_buf = NULL;
        }
        DELETE_PTR(pLtRtDownmix->m_fChanMtx);
        DELETE_PTR(pLtRtDownmix->m_pfAuxBuf);
        DELETE_PTR(pLtRtDownmix->m_pAcc);
#if defined (WMA_TARGET_X86) && !defined(WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
        if (pLtRtDownmix->m_bOptMtx2to4chan || pLtRtDownmix->m_bOptMtx5to8chan)
        {
            freeAligned(pLtRtDownmix->m_psChanMtx);
            pLtRtDownmix->m_psChanMtx = NULL;
        }
#endif // UNDER_CE && UNDER_CE<500
#endif // WMA_TARGET_X86 && !WMA_DISABLE_SSE1
        ltrtDownmixZero(pLtRtDownmix);
    }
}

WMARESULT ltrtDownmixInit(LtRtDownmix *pLtRtDownmix, Int nHalfFilterLen, Int samplingRate,
                          DataType maxVal, Int bufSize)
{
    WMARESULT hr = WMA_OK;
    Double *firFilter = NULL;
    Double *hilbertKernal = NULL;
    Double *overallFilter = NULL;
    Int i, j, k, filterLen, filterLen2;
    Double cutoff;
    Double total, totalNoWindow;
    Double threeDb;
    Double fifteenDb;
    Double scale, trueScale, usedScale;
    float *pfChanMtxL, *pfChanMtxR, *pfChanMtxC, *pfChanMtxLF;
    float *pfChanMtxBL, *pfChanMtxBR;

    ltrtDownmixFree(pLtRtDownmix);
    pLtRtDownmix->m_bCanFree = False; // no more than one free per init

    if (bufSize > 10000000)
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }

    if(nHalfFilterLen > (INT_MAX-1)/4)
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }
    if(nHalfFilterLen > (INT_MAX-1)/2) // this is added to avoid prefast warning (will file a prefast bug on this)
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }
    filterLen = 2*nHalfFilterLen + 1;
    filterLen2 = 4*nHalfFilterLen + 1;

    firFilter = (Double*)auMalloc(filterLen2*sizeof(Double));
    CHECKWMA_ALLOC(hr, firFilter);

    hilbertKernal = (Double*)auMalloc(filterLen2*sizeof(Double));
    CHECKWMA_ALLOC(hr, hilbertKernal);

    overallFilter = (Double*)auMalloc(filterLen*sizeof(Double));
    CHECKWMA_ALLOC(hr, overallFilter);

#define SURR_CUTOFF (7000)

    cutoff = SURR_CUTOFF / samplingRate;
    if (cutoff > 0.5) cutoff = 0.5;

#define LESS_FILTER

#ifdef LESS_FILTER
    cutoff = 0.35;
#endif

    for (i=0, j=-2*nHalfFilterLen; i < filterLen2; i++, j++) {
        if (j != 0) {
            firFilter[i] = sin(2*j*PI*cutoff) / (2*j*PI*cutoff) / sqrt(2.0);
            hilbertKernal[i] = (2/PI) * (sin(PI*j/2)*sin(PI*j/2)) / j;
        } else {
            firFilter[i] = 1.0 / sqrt(2.0);
            hilbertKernal[i] = 0.0;
        }
    }

    // convolve
    total = 0.0;
    totalNoWindow = 0.0;
    for (i=0, j=-nHalfFilterLen; i < filterLen; i++, j++) {
        overallFilter[i] = 0.0;
        for (k = max(-2*nHalfFilterLen, j-2*nHalfFilterLen);
            k < min(2*nHalfFilterLen, j+2*nHalfFilterLen); k++) {
                overallFilter[i] +=
                    firFilter[k+2*nHalfFilterLen] * hilbertKernal[j-k+2*nHalfFilterLen];
            }
            // apply hamming window
            totalNoWindow += fabs(overallFilter[i]);
            overallFilter[i] *= (0.54 + 0.46*cos(2.0*PI*((Double)j/filterLen)));
            total += fabs(overallFilter[i]);
    }

#define INCL_SUBWOOFER

    threeDb = pow(10.0, (-3.0/20.0));
    fifteenDb = pow(10.0, (-15.0/20.0));
    scale = 0.0;
    scale += pLtRtDownmix->m_fLRGain;
    scale += pLtRtDownmix->m_fCGain*threeDb;
    scale += pLtRtDownmix->m_fSGain*threeDb*total*2.0;
#ifdef INCL_SUBWOOFER
    scale += pLtRtDownmix->m_fLFEGain*fifteenDb;
#endif
    scale = scale / 0.999; // just to be safe...
    // lie about the scale, this way lostScale gets incorporated into scales
    trueScale = scale;

#if 1
    scale = 0.0;
    scale += pLtRtDownmix->m_fLRGain;
    scale += pLtRtDownmix->m_fCGain*threeDb;
    scale += pLtRtDownmix->m_fSGain*threeDb;
    scale += pLtRtDownmix->m_fLFEGain*fifteenDb;
    usedScale = scale;
#endif

    for (i=0; i < filterLen; i++) { // surround is 3 dB drop
        overallFilter[i] *= 2.0*threeDb / scale;
    }

    pLtRtDownmix->m_lostScale = (CompType)(scale / usedScale);

    // Clipping stuff
    pLtRtDownmix->m_maxVal = maxVal;
    pLtRtDownmix->m_xMaxVal = max(pLtRtDownmix->m_maxVal, (CompType)((trueScale/scale*pLtRtDownmix->m_maxVal)+1));
    //xMaxVal = max(pLtRtDownmix->m_maxVal, (Int)(trueScale/scale * pLtRtDownmix->m_maxVal)+1);
#define THRESH (0.92f) // don't worry too much about clipping -- use time constants instead to smooth out gain
    pLtRtDownmix->m_yThresh = THRESH * pLtRtDownmix->m_maxVal;
    pLtRtDownmix->m_xThresh = (DataType)(pLtRtDownmix->m_yThresh / pLtRtDownmix->m_lostScale);
    pLtRtDownmix->m_yThresh = pLtRtDownmix->m_xThresh * pLtRtDownmix->m_lostScale;
    pLtRtDownmix->m_maxVal -= 10; // -10.0 for headroom
    //pLtRtDownmix->m_quadScale =
    //  (pLtRtDownmix->m_maxVal-pLtRtDownmix->m_yThresh)/(CompType)sqrt((CompType)(pLtRtDownmix->m_xMaxVal - pLtRtDownmix->m_xThresh));
    // inverted quadratic, faster computation, avoids sqrt(.)
    pLtRtDownmix->m_quadScale = (pLtRtDownmix->m_yThresh-pLtRtDownmix->m_maxVal)/((CompType)(pLtRtDownmix->m_xThresh-pLtRtDownmix->m_xMaxVal)*(CompType)(pLtRtDownmix->m_xThresh-pLtRtDownmix->m_xMaxVal));

    pLtRtDownmix->m_attackCoeff = (CompType)(1.0-exp(-2.2/(100.0/1000.0*samplingRate)));
    pLtRtDownmix->m_releaseCoeff = (CompType)(1.0-exp(-2.2/(500.0/1000.0*samplingRate)));
    pLtRtDownmix->m_oneMinusAttackCoeff = 1.0f - pLtRtDownmix->m_attackCoeff;
    pLtRtDownmix->m_oneMinusReleaseCoeff = 1.0f - pLtRtDownmix->m_releaseCoeff;

    pLtRtDownmix->m_curGain = pLtRtDownmix->m_lostScale;

#if 0
    {
        CompType gain =
            (pLtRtDownmix->m_yThresh+(CompType)sqrt(pLtRtDownmix->m_xMaxVal-pLtRtDownmix->m_xThresh)*pLtRtDownmix->m_quadScale)/pLtRtDownmix->m_xMaxVal;
        Int val = (Int)(gain*pLtRtDownmix->m_xMaxVal);
        assert(val<pLtRtDownmix->m_maxVal-5 && val >= pLtRtDownmix->m_maxVal-20);
    }
#endif

    // init surround filter
    hr = bufFiltInit(&pLtRtDownmix->m_bfSurround, overallFilter,
        -nHalfFilterLen, nHalfFilterLen, bufSize);
    if (WMA_FAILED(hr)) goto exit;

    // init delay left
    hr = bufDelayInit(&pLtRtDownmix->m_bfLeft, nHalfFilterLen);
    if (WMA_FAILED(hr)) goto exit;

    // init delay right
    hr = bufDelayInit(&pLtRtDownmix->m_bfRight, nHalfFilterLen);
    if (WMA_FAILED(hr)) goto exit;

    // Matrix will convert N channels to three. Two of the channels are only
    // delayed (in place). The third is FIR filtered (in place). A total of
    // three buffers is thus allocated. Each is m_bufSize samples (floats)
    // long and is padded to multiple of 4.
    if (bufSize > 100000 || bufSize <= 0)
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }
    bufSize = (bufSize + 3) >> 2 << 2;
    pLtRtDownmix->m_bufSize = bufSize;
    pLtRtDownmix->m_buf = (DataType*)mallocAligned(pLtRtDownmix->m_bufSize * 3 *
                                                   sizeof(DataType), 16);
    CHECKWMA_ALLOC(hr, pLtRtDownmix->m_buf);
    memset(pLtRtDownmix->m_buf, 0, pLtRtDownmix->m_bufSize * 3 * sizeof(DataType));

    // Consolidate matrix from 6 to 3 output channels and the same number of input
    // channels. Center & LF (if used) will be scaled and added to Left & Right.
    // Center will be replaced by the average of BL & BR. This will be used to
    // create the Surround channel. A flag (m_bNoSurround) is set if no Surround
    // channel is present (third row of matrix is all zero).
    pLtRtDownmix->m_bNoSurround = True;
    pfChanMtxL  = pLtRtDownmix->m_fChanMtx;
    pfChanMtxR  = pLtRtDownmix->m_fChanMtx + pLtRtDownmix->m_cInChannels;
    pfChanMtxC  = pLtRtDownmix->m_fChanMtx + 2 * pLtRtDownmix->m_cInChannels;
    pfChanMtxLF = pLtRtDownmix->m_fChanMtx + 3 * pLtRtDownmix->m_cInChannels;
    pfChanMtxBL = pLtRtDownmix->m_fChanMtx + 4 * pLtRtDownmix->m_cInChannels;
    pfChanMtxBR = pLtRtDownmix->m_fChanMtx + 5 * pLtRtDownmix->m_cInChannels;
    for (i = 0; i < pLtRtDownmix->m_cInChannels; i++)
    {
#ifdef INCL_SUBWOOFER
        *pfChanMtxL = *pfChanMtxL / (float)scale +
            *pfChanMtxC * (float)(threeDb / scale) +
            *pfChanMtxLF * (float)(fifteenDb / scale);
        *pfChanMtxR = *pfChanMtxR / (float)scale +
            *pfChanMtxC * (float)(threeDb / scale) +
            *pfChanMtxLF * (float)(fifteenDb / scale);
#else
        *pfChanMtxL = *pfChanMtxL / (float)scale +
            *pfChanMtxC * (float)(threeDb / scale);
        *pfChanMtxR = *pfChanMtxR / (float)scale +
            *pfChanMtxC * (float)(threeDb / scale);
#endif
        *pfChanMtxC = (*pfChanMtxBL + *pfChanMtxBR) / 2;
        if (*pfChanMtxC)
        {
            pLtRtDownmix->m_bNoSurround = False;
        }
        pfChanMtxL++;
        pfChanMtxR++;
        pfChanMtxC++;
        pfChanMtxLF++;
        pfChanMtxBL++;
        pfChanMtxBR++;
    }

    // create packed version of pfChanMtx when SSE1 is supported
#if defined (WMA_TARGET_X86) && !defined(WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
    if (pLtRtDownmix->m_bOptMtx2to4chan)
    {
        __m128 *ppsChanMtx;

        pfChanMtxL = pLtRtDownmix->m_fChanMtx;
        pLtRtDownmix->m_psChanMtx = mallocAligned(3 * sizeof(__m128), 16);
        ppsChanMtx = (__m128*)pLtRtDownmix->m_psChanMtx;
        for (i = 0; i < 3; i++)
        {
            *ppsChanMtx = _mm_setzero_ps();
            switch (pLtRtDownmix->m_cInChannels)
            {
            case 1:
                *ppsChanMtx++ = _mm_set_ps(0, 0, 0, *pfChanMtxL);
                pfChanMtxL++;
                break;
            case 2:
                *ppsChanMtx++ = _mm_set_ps(0, 0, *(pfChanMtxL + 1), *pfChanMtxL);
                pfChanMtxL += 2;
                break;
            case 3:
                *ppsChanMtx++ = _mm_set_ps(0, *(pfChanMtxL + 2),
                    *(pfChanMtxL + 1), *pfChanMtxL);
                pfChanMtxL += 3;
                break;
            case 4:
                *ppsChanMtx++ = _mm_loadu_ps(pfChanMtxL);
                pfChanMtxL += 4;
                break;
            }
        }
    }
    if (pLtRtDownmix->m_bOptMtx5to8chan)
    {
        __m128 *ppsChanMtx;

        pfChanMtxL = pLtRtDownmix->m_fChanMtx;
        pLtRtDownmix->m_psChanMtx = mallocAligned(6 * sizeof(__m128), 16);
        ppsChanMtx = (__m128*)pLtRtDownmix->m_psChanMtx;
        for (i = 0; i < 3; i++)
        {
            *ppsChanMtx++ = _mm_setzero_ps();
            *ppsChanMtx-- = _mm_setzero_ps();
            *ppsChanMtx++ = _mm_loadu_ps(pfChanMtxL);
            pfChanMtxL += 4;
            switch (pLtRtDownmix->m_cInChannels % 4)
            {
            case 1:
                *ppsChanMtx++ = _mm_set_ps(0, 0, 0, *pfChanMtxL);
                pfChanMtxL++;
                break;
            case 2:
                *ppsChanMtx++ = _mm_set_ps(0, 0, *(pfChanMtxL + 1), *pfChanMtxL);
                pfChanMtxL += 2;
                break;
            case 3:
                *ppsChanMtx++ = _mm_set_ps(0, *(pfChanMtxL + 2),
                    *(pfChanMtxL + 1), *pfChanMtxL);
                pfChanMtxL += 3;
                break;
            case 0:
                *ppsChanMtx++ = _mm_loadu_ps(pfChanMtxL);
                pfChanMtxL += 4;
                break;
            }
        }
    }
#endif // UNDER_CE && UNDER_CE<500
#endif // WMA_TARGET_X86 && !WMA_DISABLE_SSE1

exit:
    pLtRtDownmix->m_bCanFree = True;

    DELETE_ARRAY(firFilter);
    DELETE_ARRAY(hilbertKernal);
    DELETE_ARRAY(overallFilter);

    return hr;
}

WMA_Bool ltrtDownmixInputFormatSupported(PCMFormat *pcmIn)
{
    if (pcmIn->nChannels  < 2 || pcmIn->nChannels > 32)
    {
        return False;
    }
    return True;
}

WMARESULT ltrtDownmixInitBuf(LtRtDownmix *pLtRtDownmix,
                             Int nHalfFilterLen, Int samplingRate,
                             DataType maxVal, Int bufSize, PCMFormat *pcmIn)
{
    WMARESULT hr = WMA_OK;
    DataType temp;
    Float *pfChanMtx;
    Int iChDst, iCh;

    ltrtDownmixFree(pLtRtDownmix);
    pLtRtDownmix->m_bCanFree = False;
    if (!ltrtDownmixInputFormatSupported(pcmIn))
    {
        hr = WMA_E_INVALIDARG;
        goto exit;
    }

    pLtRtDownmix->m_cInChannels = pcmIn->nChannels;

    pLtRtDownmix->m_bOptMtx2to4chan = False;
    pLtRtDownmix->m_bOptMtx5to8chan = False;

    // conditional optimization settings
#if defined(WMA_TARGET_X86) && !defined (WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
    if (g_SupportSSE1())
    {
        pLtRtDownmix->m_pfnBufFilt = bufFilt_SSE;
        if (pLtRtDownmix->m_cInChannels > 2 && pLtRtDownmix->m_cInChannels <= 4)
        {
            pLtRtDownmix->m_bOptMtx2to4chan = True;
        }
        if (pLtRtDownmix->m_cInChannels > 4 && pLtRtDownmix->m_cInChannels <= 8)
        {
            pLtRtDownmix->m_bOptMtx5to8chan = True;
        }
    }
    else
#endif // UNDER_CE && UNDER_CE<500
#endif // WMA_TARGET_X86 && !WMA_DISABLE_SSE1
    {
        pLtRtDownmix->m_pfnBufFilt = bufFilt;
    }

    pLtRtDownmix->m_fChanMtx = (Float*)auMalloc(pLtRtDownmix->m_cInChannels * LTRT_SRC_CHANNELS *
        sizeof(Float));
    CHECKWMA_ALLOC(hr, pLtRtDownmix->m_fChanMtx);
    hr = SetMixFromChannelMaskF(pLtRtDownmix->m_cInChannels, LTRT_SRC_CHANNELS,
        pcmIn->nChannelMask, LTRT_SRC_MASK,
        pLtRtDownmix->m_fChanMtx);
    CHECKWMA_EXIT(hr);

    pfChanMtx = pLtRtDownmix->m_fChanMtx;
    for (iChDst=0; iChDst < LTRT_SRC_CHANNELS; iChDst++)
    {
        temp = (DataType)0;
        for (iCh = 0; iCh < pLtRtDownmix->m_cInChannels; iCh++)
        {
            temp += ABS(*pfChanMtx);
            pfChanMtx++;
        }
        switch (iChDst) {
    case 0: pLtRtDownmix->m_fLRGain = temp; break;
    case 1: pLtRtDownmix->m_fLRGain = max(pLtRtDownmix->m_fLRGain, temp); break;
    case 2: pLtRtDownmix->m_fCGain = temp; break;
    case 3: pLtRtDownmix->m_fLFEGain = temp; break;
    case 4: pLtRtDownmix->m_fSGain = temp / 2; break;
    case 5: pLtRtDownmix->m_fSGain += temp / 2; break;
        }
    }

    TRACEWMA_EXIT(hr, ltrtDownmixInit(pLtRtDownmix, nHalfFilterLen,
                  samplingRate, maxVal, bufSize));

exit:
    pLtRtDownmix->m_bCanFree = True;
    return hr;
}

WMARESULT ltrtDownmixInitBufPCM(LtRtDownmix *pLtRtDownmix,
                                Int nHalfFilterLen, Int samplingRate,
                                DataType maxVal, Int bufSize, PCMFormat *pcmIn)
{
    WMARESULT hr = WMA_OK;

    hr = ltrtDownmixInitBuf(pLtRtDownmix, nHalfFilterLen, samplingRate, maxVal,
                            bufSize, pcmIn);

    // allocate aux buffer
    pLtRtDownmix->m_pfAuxBuf = (LtRtBufType*)auMalloc(pLtRtDownmix->m_cInChannels
                                                      * bufSize * sizeof(LtRtBufType));
    CHECKWMA_ALLOC(hr, pLtRtDownmix->m_pfAuxBuf);

    // allocate WMAPCMAcc struct
    pLtRtDownmix->m_pAcc = (WMAPCMAcc*)auMalloc(sizeof(WMAPCMAcc));
    CHECKWMA_ALLOC(hr, pLtRtDownmix->m_pfAuxBuf);
    WMAPCMAccSetFormat(pLtRtDownmix->m_pAcc, pcmIn);
exit:
    return hr;
}

INLINE CompType ltrtGetCurGain(LtRtDownmix *pLtRtDownmix,
                               const DataType left, const DataType right)
{
    DataType maxCh = max(ABS(left), ABS(right));
    CompType gain;

    if (maxCh >= pLtRtDownmix->m_xThresh) {
#if 0
        gain =
            (pLtRtDownmix->m_yThresh + (CompType)sqrt((CompType)(maxCh - pLtRtDownmix->m_xThresh))*pLtRtDownmix->m_quadScale)/maxCh;
#else
        gain =
            (pLtRtDownmix->m_maxVal + (CompType)pLtRtDownmix->m_quadScale * (maxCh-pLtRtDownmix->m_xMaxVal)*(maxCh-pLtRtDownmix->m_xMaxVal))/maxCh;
#endif
    } else {
        gain = pLtRtDownmix->m_lostScale;
        if (gain == pLtRtDownmix->m_curGain) return gain; // optimization...
        if (ABS(gain-pLtRtDownmix->m_curGain) < 0.01f) return gain; // optimization...
    }
    //return gain;
    if (gain <= pLtRtDownmix->m_curGain) {
        pLtRtDownmix->m_curGain =
            pLtRtDownmix->m_attackCoeff * gain + pLtRtDownmix->m_oneMinusAttackCoeff * pLtRtDownmix->m_curGain;
    } else {
        pLtRtDownmix->m_curGain =
            pLtRtDownmix->m_releaseCoeff * gain + pLtRtDownmix->m_oneMinusReleaseCoeff * pLtRtDownmix->m_curGain;
    }
    if ((DataType)BF_ROUNDCD(maxCh * pLtRtDownmix->m_curGain) > pLtRtDownmix->m_maxVal) {
        pLtRtDownmix->m_curGain = (CompType)pLtRtDownmix->m_maxVal / maxCh;
    }
    return pLtRtDownmix->m_curGain;
}

WMARESULT ltrtDownmix(LtRtDownmix *pLtRtDownmix, Int len, Int *pnOut)
{
    WMARESULT hr = WMA_OK;
    Int i;
    Int nOut, nOutAll;
    CompType gain;
    float *pfLeft     = pLtRtDownmix->m_buf;
    float *pfRight    = pLtRtDownmix->m_buf + 1 * pLtRtDownmix->m_bufSize;
    float *pfSurround = pLtRtDownmix->m_buf + 2 * pLtRtDownmix->m_bufSize;

    ASSERTWMA_EXIT(hr, len <= pLtRtDownmix->m_bufSize ? WMA_OK : WMA_E_INVALIDARG);

    // surround filter (in place)
    hr = pLtRtDownmix->m_pfnBufFilt(&pLtRtDownmix->m_bfSurround, pfSurround, len);
    if (WMA_FAILED(hr)) goto exit;
    nOutAll = len;

    // delay left (in place)
    hr = bufDelay(&pLtRtDownmix->m_bfLeft, pfLeft, len, &nOut);
    if (WMA_FAILED(hr)) goto exit;
    assert(nOut == nOutAll);

    // delay right (in place)
    hr = bufDelay(&pLtRtDownmix->m_bfRight, pfRight, len, &nOut);
    if (WMA_FAILED(hr)) goto exit;
    assert(nOut == nOutAll);

    for (i = 0; i < nOut; i++)
    {
        *pfLeft += *pfSurround;
        *pfRight -= *pfSurround++;
        gain = ltrtGetCurGain(pLtRtDownmix, *pfLeft, *pfRight);
        *pfLeft = (DataType)BF_ROUNDCD(*pfLeft * gain);
        pfLeft++;
        *pfRight = (DataType)BF_ROUNDCD(*pfRight * gain);
        pfRight++;
    }

    if (pnOut) *pnOut = nOut;

exit:
    return hr;
}

// -----------------------------------------------------------------------------
// ltrtDownmixBuf - LTRT downmix a float buffer that has <= pLtRtDownmix->m_bufSize samples
// There are 4 cases
// A) any case where there is no surround - no downmixing done
// B) 2 to 4 channels - optimized using SSE1, 1x __m128 used for matrix multiply
// C) 5 to 8 channels - optimized using SSE1, 2x __m128 used for matrix multiply
// D) greater than 8 channels - general case, not optimized
//------------------------------------------------------------------------------
void ltrtDownmixBuf(LtRtDownmix *pLtRtDownmix, Int cSamples,
                    LtRtBufType *bufIn, LtRtBufType *bufOut)
{
    WMARESULT wmaResult;
    Int iSamples, iDst, iCh, nOut = 0;

    // case A
    if (pLtRtDownmix->m_bNoSurround)
    {
        float *pfChanMtx, total;
        Int iChDst;

        for (iSamples = 0; iSamples < cSamples; iSamples++)
        {
            pfChanMtx = pLtRtDownmix->m_fChanMtx;
            for (iChDst = 0; iChDst < 2; iChDst++)
            {
                total = 0;
                for (iCh = 0; iCh < pLtRtDownmix->m_cInChannels; iCh++)
                {
                    total += bufIn[iCh] * (*pfChanMtx++);
                }
                *bufOut++ = (LtRtBufType)total;
            }
            bufIn += pLtRtDownmix->m_cInChannels;
        }
    }
#if defined(WMA_TARGET_X86) && !defined (WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
    // case B
    else if (pLtRtDownmix->m_bOptMtx2to4chan)
    {
        __m128 data0, data1, total0, total1, total2, *ppsChanMtx;
        __declspec(align(16)) float res[4];
        float *pfLeft, *pfSurround;
        int iBufSize, iInChannels;

        // init ptrs
        pfLeft = pLtRtDownmix->m_buf;
        iBufSize = pLtRtDownmix->m_bufSize;
        iInChannels = pLtRtDownmix->m_cInChannels;
        pfSurround = pfLeft + 2 * iBufSize;

        for (iSamples = 0; iSamples < cSamples - 1; iSamples++)
        {
            // set the pointer to the N->3 conversion coefficients (one 128-bit
            // entry for each of the output channels - left, right, surround)
            ppsChanMtx = (__m128*)pLtRtDownmix->m_psChanMtx;

            // load the data
            data0 = _mm_loadu_ps(bufIn);

            // calculate the left channel and store
            total0 = _mm_mul_ps(data0, *ppsChanMtx++);

            // calculate the right channel and store
            total1 = _mm_mul_ps(data0, *ppsChanMtx++);

            // calculate the surround channel and store directly at filter input
            total2 = _mm_mul_ps(data0, *ppsChanMtx++);

            // Transpose a 3x4 matrix.
            // This is helpful for horizontal add and since _mm_hadd_ps is only
            // available in SSE3. The following lines convert:
            //
            // (total0 = A B C D)      (A E I J = total0)
            // (total1 = E F G H)  ==> (B F J I = total1)
            // (total2 = I J K L)  ==> (C G K L = data0)
            //                         (D H L K = data1)
            data0 = _mm_shuffle_ps(total1, total0, _MM_SHUFFLE(3, 2, 3, 2));
            data1 = _mm_shuffle_ps(total1, total0, _MM_SHUFFLE(1, 0, 1, 0));
            total0 = _mm_shuffle_ps(total2, data0, _MM_SHUFFLE(3, 1, 3, 2));
            total1 = _mm_shuffle_ps(total2, data0, _MM_SHUFFLE(2, 0, 2, 3));
            data0 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(3, 1, 1, 0));
            data1 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(2, 0, 0, 1));

            // sum the columns (across original totals)
            total1 = _mm_add_ps(total0, total1);
            total2 = _mm_add_ps(data0, data1);
            total0 = _mm_add_ps(total1, total2);
            _mm_store_ps(res, total0);

            // store outputs
            *pfSurround++ = res[1];
            *(pfLeft + iBufSize) = res[2];
            *pfLeft++ = res[3];

            // update in ptr
            bufIn += iInChannels;
        }

        // handle last sample separately to avoid SSE read past end of buffer
        for (; iSamples < cSamples; iSamples++)
        {
            DataType total;
            float *pfChanMtx;
            Int iChDst;

            // Collect samples into LtRtBuf
            pfChanMtx = pLtRtDownmix->m_fChanMtx;
            for (iChDst = 0; iChDst < 3; iChDst++)
            {
                total = 0;
                for (iCh = 0; iCh < pLtRtDownmix->m_cInChannels; iCh++)
                {
                    total += bufIn[iCh] * (*pfChanMtx++);
                }
                pLtRtDownmix->m_buf[iChDst * pLtRtDownmix->m_bufSize +  iSamples] = total;
            }
        }

        // Do LtRt processing
        wmaResult = ltrtDownmix(pLtRtDownmix, cSamples, &nOut);
        assert(wmaResult == WMA_OK);
        assert(nOut == cSamples);
        for (iDst = 0; iDst < nOut; iDst++)
        {
            for (iCh = 0; iCh < LTRT_DST_CHANNELS; iCh++)
            {
                *bufOut++ = (LtRtBufType)pLtRtDownmix->m_buf[iCh * pLtRtDownmix->m_bufSize + iDst];
            }
        }
    }
    // case C
    else if (pLtRtDownmix->m_bOptMtx5to8chan)
    {
        __m128 data0, data1, total0, total1, total2, temp, *ppsChanMtx;
        __declspec(align(16)) float res[4];
        float *pfLeft, *pfSurround;
        int iBufSize, iInChannels;

        // init ptrs
        pfLeft = pLtRtDownmix->m_buf;
        iBufSize = pLtRtDownmix->m_bufSize;
        iInChannels = pLtRtDownmix->m_cInChannels;
        pfSurround = pfLeft + 2 * iBufSize;

        for (iSamples = 0; iSamples < cSamples - 1; iSamples++)
        {
            // set the pointer to the N->3 conversion coefficients (two 128-bit
            // entries for each of the output channels - left, right, surround)         
            ppsChanMtx = (__m128*)pLtRtDownmix->m_psChanMtx;

            // load the data
            data0 = _mm_loadu_ps(bufIn);
            data1 = _mm_loadu_ps(bufIn + 4);

            // calculate the left channel
            total0 = _mm_mul_ps(data0, *ppsChanMtx++);
            temp = _mm_mul_ps(data1, *ppsChanMtx++);
            total0 = _mm_add_ps(total0, temp);

            // calculate the right channel
            total1 = _mm_mul_ps(data0, *ppsChanMtx++);
            temp = _mm_mul_ps(data1, *ppsChanMtx++);
            total1 = _mm_add_ps(total1, temp);

            // calculate the surround channel
            total2 = _mm_mul_ps(data0, *ppsChanMtx++);
            temp = _mm_mul_ps(data1, *ppsChanMtx++);
            total2 = _mm_add_ps(total2, temp);

            // Transpose a 3x4 matrix.
            // This is helpful for horizontal add and since _mm_hadd_ps is only
            // available in SSE3. The following lines convert:
            //
            // (total0 = A B C D)      (A E I J = total0)
            // (total1 = E F G H)  ==> (B F J I = total1)
            // (total2 = I J K L)  ==> (C G K L = data0)
            //                         (D H L K = data1)
            data0 = _mm_shuffle_ps(total1, total0, _MM_SHUFFLE(3, 2, 3, 2));
            data1 = _mm_shuffle_ps(total1, total0, _MM_SHUFFLE(1, 0, 1, 0));
            total0 = _mm_shuffle_ps(total2, data0, _MM_SHUFFLE(3, 1, 3, 2));
            total1 = _mm_shuffle_ps(total2, data0, _MM_SHUFFLE(2, 0, 2, 3));
            data0 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(3, 1, 1, 0));
            data1 = _mm_shuffle_ps(total2, data1, _MM_SHUFFLE(2, 0, 0, 1));

            // sum the columns (across original totals)
            total1 = _mm_add_ps(total0, total1);
            total2 = _mm_add_ps(data0, data1);
            total0 = _mm_add_ps(total1, total2);
            _mm_store_ps(res, total0);

            // store outputs
            *pfSurround++ = res[1];
            *(pfLeft + iBufSize) = res[2];
            *pfLeft++ = res[3];
            
            // update in ptr
            bufIn += iInChannels;
        }

        // handle last sample separately to avoid SSE read past end of buffer
        for (; iSamples < cSamples; iSamples++)
        {
            DataType total;
            float *pfChanMtx;
            Int iChDst;

            // Collect samples into LtRtBuf
            pfChanMtx = pLtRtDownmix->m_fChanMtx;
            for (iChDst = 0; iChDst < 3; iChDst++)
            {
                total = 0;
                for (iCh = 0; iCh < pLtRtDownmix->m_cInChannels; iCh++)
                {
                    total += bufIn[iCh] * (*pfChanMtx++);
                }
                pLtRtDownmix->m_buf[iChDst * pLtRtDownmix->m_bufSize + iSamples] = total;
            }
        }

        // Do LtRt processing
        wmaResult = ltrtDownmix(pLtRtDownmix, cSamples, &nOut);
        assert(wmaResult == WMA_OK);
        assert(nOut == cSamples);
        for (iDst = 0; iDst < nOut; iDst++)
        {
            for (iCh = 0; iCh < LTRT_DST_CHANNELS; iCh++)
            {
                *bufOut++ = (LtRtBufType)pLtRtDownmix->m_buf[iCh * pLtRtDownmix->m_bufSize + iDst];
            }
        }
    }
#endif // UNDER_CE && UNDER_CE<500
#endif // WMA_TARGET_X86 && !WMA_DISABLE_SSE1
    else
    // case D
    {
        DataType total;
        float *pfChanMtx;
        Int iChDst;

        for (iSamples = 0; iSamples < cSamples; iSamples++)
        {
            // Collect samples into LtRtBuf
            pfChanMtx = pLtRtDownmix->m_fChanMtx;
            for (iChDst = 0; iChDst < 3; iChDst++)
            {
                total = 0;
                for (iCh = 0; iCh < pLtRtDownmix->m_cInChannels; iCh++)
                {
                    total += bufIn[iCh] * (*pfChanMtx++);
                }
                pLtRtDownmix->m_buf[iChDst * pLtRtDownmix->m_bufSize + iSamples] = total;
            }
            bufIn += pLtRtDownmix->m_cInChannels;
        }

        // Do LtRt processing
        wmaResult = ltrtDownmix(pLtRtDownmix, cSamples, &nOut);
        assert(wmaResult == WMA_OK);
        assert(nOut == cSamples);
        for (iDst = 0; iDst < nOut; iDst++)
        {
            for (iCh = 0; iCh < LTRT_DST_CHANNELS; iCh++)
            {
                *bufOut++ = (LtRtBufType)pLtRtDownmix->m_buf[iCh * pLtRtDownmix->m_bufSize + iDst];
            }
        }
    }
}

// -----------------------------------------------------------------------------
// ltrtDownmixBufFloat - LTRT downmix a float buffer
// -----------------------------------------------------------------------------
void ltrtDownmixBufFloat(LtRtDownmix *pLtRtDownmix, Int cSamples,
                         LtRtBufType *bufIn, LtRtBufType *bufOut)
{
    int i = cSamples;

    while ( i > pLtRtDownmix->m_bufSize)
    {
        i -= pLtRtDownmix->m_bufSize;
        ltrtDownmixBuf(pLtRtDownmix, pLtRtDownmix->m_bufSize, bufIn, bufOut);
        bufIn += pLtRtDownmix->m_bufSize * pLtRtDownmix->m_cInChannels;
        bufOut += pLtRtDownmix->m_bufSize * LTRT_DST_CHANNELS;
    }
    if (i)
    {
        ltrtDownmixBuf(pLtRtDownmix, i, bufIn, bufOut);
    }
}

// -----------------------------------------------------------------------------
// ltrtDownmixBufPCM - LTRT downmix a PCM (U8) buffer
// -----------------------------------------------------------------------------
void ltrtDownmixBufPCM(LtRtDownmix *pLtRtDownmix, Int cSamples, U8 *bufInPCM,
                       U8 *bufOutPCM)
{
    WMA_U8 *pIn = (WMA_U8*)bufInPCM, *pOut = (WMA_U8*)bufOutPCM;
    int i = cSamples;

    while ( i > pLtRtDownmix->m_bufSize)
    {
        i -= pLtRtDownmix->m_bufSize;
        WMAPCMAccGetPCMMulti(pLtRtDownmix->m_pAcc, pIn, pLtRtDownmix->m_pfAuxBuf,
                             pLtRtDownmix->m_bufSize * pLtRtDownmix->m_cInChannels);
        ltrtDownmixBuf(pLtRtDownmix, pLtRtDownmix->m_bufSize,
                       pLtRtDownmix->m_pfAuxBuf, pLtRtDownmix->m_pfAuxBuf);
        WMAPCMAccPutPCMMulti(pLtRtDownmix->m_pAcc, pOut, pLtRtDownmix->m_pfAuxBuf,
                             pLtRtDownmix->m_bufSize * LTRT_DST_CHANNELS, 0);
        pIn += pLtRtDownmix->m_bufSize * pLtRtDownmix->m_cInChannels * pLtRtDownmix->m_pAcc->fmt.cbPCMContainerSize;
        pOut += pLtRtDownmix->m_bufSize * LTRT_DST_CHANNELS * pLtRtDownmix->m_pAcc->fmt.cbPCMContainerSize;
    }
    if (i)
    {
        WMAPCMAccGetPCMMulti(pLtRtDownmix->m_pAcc, pIn, pLtRtDownmix->m_pfAuxBuf, i * pLtRtDownmix->m_cInChannels);
        ltrtDownmixBuf(pLtRtDownmix, i, pLtRtDownmix->m_pfAuxBuf, pLtRtDownmix->m_pfAuxBuf);
        WMAPCMAccPutPCMMulti(pLtRtDownmix->m_pAcc, pOut, pLtRtDownmix->m_pfAuxBuf, i * LTRT_DST_CHANNELS, 0);
    }
}

#if defined(_SH4_)
#pragma warning(pop)
#endif
