//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "macros.h"
#include "msaudio.h"
#include "msaudiodec.h"
#include "wmafmt.h"
#include "pcmfmt.h"

#include "wmatyps.h"
//#include "config.h"
#include "playropt.h"
#include "wmawfxdefs.h"

#include "wmaprodecS_api.h"

#ifndef _XBOX
#include "cpudetect.h"
#endif

WMARESULT WMAProRawDecNew (
    WMAProRawDecHandle* pphWMAProRawDec,
    void *pMemBuf, 
    const WMA_I32 iMemBufSize
){
    WMARESULT hr = WMA_OK;
    if ( NULL == pphWMAProRawDec ) {
        //assert(!"WMAProRawDecNew called with pphWMAProRawDec==NULL");
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
    }

    *pphWMAProRawDec = audecNew(pMemBuf, iMemBufSize);
    if (*pphWMAProRawDec == NULL)
        hr = WMA_E_FAIL;
exit:
    return hr;
}

WMARESULT WMAProRawDecInit (
    WMAProRawDecHandle phWMAProRawDec, 
    WMAFormat* pWMAFormat, 
    PCMFormat* pPCMFormat,
    WMAPlayerInfo *pPI, 
    WMAProRawDecState *paudecState,
    WMAProRawDecInitParams* pParams
){
    WMARESULT hr = WMA_OK;

    if ( NULL == pWMAFormat ) {
        //assert(!"WMAProRawDecInit called with pWMAFormat==NULL");
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
    }

#ifdef UNDER_CE 
    //Support only 16 bit and 24 bit input
    if ((pWMAFormat->nValidBitsPerSample != 16) && (pWMAFormat->nValidBitsPerSample != 24))
        return WMA_E_NOTSUPPORTED;
    
    //Support only 16 bit and 24 bit output
    if ((pPCMFormat->nValidBitsPerSample != 16) && (pPCMFormat->nValidBitsPerSample != 24))
        return WMA_E_NOTSUPPORTED;

    //turn off fex
//    pPI->nPlayerOpt |= PLAYOPT_IGNOREFREQEX;

#endif //UNDER_CE

    hr = audecInit(phWMAProRawDec, pWMAFormat, pPCMFormat, pPI, (audecState*)paudecState, (audecInitParams*)pParams);

/*
    We are not intended to release decoder object here. User should call WMAProRawDecDelete to release phWMAProRawDec
    whether this function failed or not.
 */
exit:
    return hr;
}

WMARESULT WMAProRawDecDelete (WMAProRawDecHandle phWMAProRawDec)
{
    if ( NULL != phWMAProRawDec )
        audecDelete(phWMAProRawDec);
    return WMA_OK;
}

WMARESULT WMAProRawDecReset (WMAProRawDecHandle phWMAProRawDec)
{
    if ( NULL == phWMAProRawDec ) {
        WMARESULT hr = 0;
        //assert(!"WMAProRawDecReset called with phWMAProRawDec==NULL");
        TRACEWMA_RET(hr, WMA_E_INVALIDARG);
    }
    return (audecReset(phWMAProRawDec));
}

WMARESULT WMAProRawDecInput (
    WMAProRawDecHandle phWMAProRawDec, 
    WMA_U8* pbIn, 
    WMA_U32 cbIn,
    WMA_Bool fNewPacket, 
    WMA_Bool fNoMoreInput,
    WMA_Bool fTime, 
    WMA_I64 rtTime,
    WMAProRawDecState* paudecState, 
    WMAProRawDecInputParams* pParams
){
    WMARESULT hr = WMA_OK;
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)phWMAProRawDec;

    //input buffer should not bigger than 1 packet each time 
    WMA_U32 cbInBits = cbIn*BITS_PER_BYTE;

    if ( NULL == paudec || NULL == paudec->pau ) {
        //assert(!"WMAProRawDecDecode called with phWMAProRawDec==NULL");
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
    }

   if (cbInBits > (WMA_U32)paudec->pau->m_cBitPacketLength)
        return WMA_E_INVALIDARG;

    hr = audecInput(phWMAProRawDec, pbIn, cbIn, fNewPacket, fNoMoreInput,
                    fTime, rtTime,
                    (audecState*)paudecState, (audecInputParams*)pParams);
exit:
    return hr;
}

   
WMARESULT WMAProRawDecDecode (
    WMAProRawDecHandle phWMAProRawDec, 
    WMA_U32* pcSamplesReady, 
    WMAProRawDecState* paudecState,
    WMAProRawDecDecodeParams* pParams
){
    WMARESULT hr = WMA_OK;
    if ( NULL == phWMAProRawDec ) {
        //assert(!"WMAProRawDecDecode called with phWMAProRawDec==NULL");
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
    }
    hr = audecDecode(phWMAProRawDec, pcSamplesReady, (audecState*)paudecState, (audecDecodeParams*)pParams);
exit:
    return hr;
}

WMARESULT WMAProRawDecGetPCM (
    WMAProRawDecHandle phWMAProRawDec, 
    WMA_U32 cSamplesRequested, 
    WMA_U32 *pcSamplesReturned,
    WMA_U8* pbDst, 
    WMA_U32 cbDstLength,
    WMA_U32* pcbDstUsed, 
    WMA_I64* prtTime, // time stamp (in 100ns) of 1st sample returned
    WMAProRawDecState *paudecState, 
    WMAPlayerInfo *pWmaPI,
    WMAProRawDecGetPCMParams* pParams
){
    WMARESULT hr = WMA_OK;

    if ( NULL == phWMAProRawDec || NULL == pWmaPI ) {
        //assert(!"WMAProRawDecGetPCM called with phWMAProRawDec==NULL || pWmaPI==NULL ");
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
    }

//turn off fex for ARM
#ifdef WMA_TARGET_ARM 
//    pWmaPI->nPlayerOpt |= PLAYOPT_IGNOREFREQEX;
#endif //WMA_TARGET_ARM


    hr = audecGetPCM(phWMAProRawDec, cSamplesRequested, pcSamplesReturned,
                     pbDst, cbDstLength, pcbDstUsed, prtTime,
                     (audecState*)paudecState, pWmaPI, (audecGetPCMParams*)pParams);
exit:
    return hr;
}


WMA_I32 WMAProGetSamplePerFrame (WMA_I32   cSamplePerSec, 
                                 WMA_U32   dwBitPerSec, 
                                 WMA_I32   iVersion,
                                 WMA_U16   wEncOpt
)
{
    return (msaudioGetSamplePerFrame (cSamplePerSec, dwBitPerSec, iVersion, wEncOpt));
}

WMA_U32  WMAProDefaultChannelMask(WMA_U32 nChannels)
{
    return (DefaultChannelMask(nChannels));
}

WMA_VOID WMAProWMAFormat2PCMFormat(WMAFormat* pSrc, PCMFormat* pDst)
{
    if ( NULL == pSrc || NULL == pDst ) {
        //assert(!"WMAProWMAFormat2PCMFormat called with pSrc==NULL || pDst==NULL ");
        return;
    }
    WMAFormat2PCMFormat(pSrc, pDst);
}
                                  
WMA_VOID WMAProWaveFormat2WMAFormat( WAVEFORMATEX* pSrc, WMAFormat* pDst )
{
    if ( NULL == pSrc || NULL == pDst ) {
        //assert(!"WMAProWMAFormat2PCMFormat called with pSrc==NULL || pDst==NULL ");
        return;
    }
    WaveFormat2WMAFormat(pSrc, pDst);
}

#ifdef UNDER_CE
WMA_VOID WMAProRawDecSetLtrtPlayerOptionsFromRegistryCE (
    WMAPlayerInfo *pPI
){
#if defined(WMA_TARGET_X86) && !defined(WMA_DISABLE_SSE1)
#if defined(UNDER_CE) && (UNDER_CE<500)
#else
    if (g_SupportSSE1())
    {
        DWORD dwMode, dwBufSize, dwQuality;

        prvGetRegistryLTRTSettings(&dwMode, &dwBufSize, &dwQuality);

        if (dwMode)
        {
            pPI->nPlayerOpt |= PLAYOPT_LTRT;

            dwBufSize = (dwBufSize < 1000) ? 1000 : dwBufSize;
            dwBufSize = (dwBufSize > 10000) ? 10000 : dwBufSize;
            pPI->iLtRtBufsize = dwBufSize;

            dwQuality = (dwQuality < 10) ? 10 : dwQuality;
            dwQuality = (dwQuality > 50) ? 50 : dwQuality;
            pPI->iLtRtQuality = dwQuality;
        }
    }
#endif
#endif
}
#endif