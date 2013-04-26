//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef _WMA_LTRT_H
#define _WMA_LTRT_H
#include "wmabuffilt.h"
#include "pcmfmt.h"
#include "wmapcmacc.h"
#include "wmawfxdefs.h"

#ifdef TOMATIN_BUILD
#define ltrtDownmixZero ltrtDnmixZero
#define ltrtDownmixFree ltrtDnmixFree
#define ltrtDownmixInit ltrtDnmixInit
#define ltrtDownmix ltrtDnmix
#define ltrtDownmixInitBuf ltrtDnmixInitBuf
#define ltrtDownmixBufFloat ltrtDnmixBufFloat
#define ltrtDownmixInitBufPCM ltrtDnmixInitBufPCM
#define ltrtDownmixBufPCM ltrtDnmixBufPCM
#endif

#ifndef MCMASK_5DOT1
#define MCMASK_MONO   SPEAKER_FRONT_CENTER
#define MCMASK_STEREO (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)
#define MCMASK_THREE  (SPEAKER_FRONT_CENTER | MCMASK_STEREO)
#define MCMASK_BACK   (SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define MCMASK_QUAD   (MCMASK_STEREO | MCMASK_BACK)
#define MCMASK_5      (MCMASK_THREE | MCMASK_BACK)
#define MCMASK_5DOT1  (MCMASK_5 | SPEAKER_LOW_FREQUENCY)
#define MCMASK_6DOT1  (MCMASK_5DOT1 | SPEAKER_BACK_CENTER)
#define MCMASK_7DOT1  (MCMASK_5DOT1 | SPEAKER_SIDE_LEFT | SPEAKER_SIDE_RIGHT)
#endif

#define LTRT_SRC_CHANNELS (6)
#define LTRT_SRC_MASK (MCMASK_5DOT1)
#define LTRT_DST_CHANNELS (2)
#define LTRT_DST_MASK (MCMASK_STEREO)

typedef Float LtRtBufType;

typedef struct LtRtDownmix
{
    BufFilt m_bfSurround;
    BufDelay m_bfLeft, m_bfRight;

    DataType m_maxVal;
    CompType m_lostScale;
    CompType m_curGain;
    CompType m_attackCoeff, m_oneMinusAttackCoeff;
    CompType m_releaseCoeff, m_oneMinusReleaseCoeff;
    DataType m_xThresh;
    CompType m_yThresh;
    CompType m_xMaxVal;
    CompType m_quadScale;

    DataType *m_buf;
    Int m_bufSize;
    LtRtBufType *m_pfAuxBuf;    // used for float to/from int conversion

    WMAPCMAcc* m_pAcc;
    Float *m_fChanMtx;
    __bound Int m_cInChannels;
    Bool m_bCanFree;
    Float m_fLRGain, m_fCGain, m_fSGain, m_fLFEGain;
    Bool m_bOptMtx2to4chan;
    Bool m_bOptMtx5to8chan;
    Bool m_bNoSurround;
    WMARESULT (*m_pfnBufFilt) (BufFilt *pBufFilt, float *pInOutBuf, Int cLen);
    void *m_psChanMtx;
} LtRtDownmix;

#ifdef __cplusplus
extern "C" {
#endif

void ltrtDownmixZero(LtRtDownmix *pLtRtDownmix);
void ltrtDownmixFree(LtRtDownmix *pLtRtDownmix);
WMARESULT ltrtDownmixInit(LtRtDownmix *pLtRtDownmix, Int nHalfFilterLen,
                          Int samplingRate, DataType maxVal, Int bufSize);
WMARESULT ltrtDownmix(LtRtDownmix *pLtRtDownmix, Int len, Int *pnOut);

WMA_Bool ltrtDownmixInputFormatSupported(PCMFormat *pcmIn);

// APIs for LtRtBufType (float) I/O
WMARESULT ltrtDownmixInitBuf(LtRtDownmix *pLtRtDownmix, Int nHalfFilterLen,
                             Int samplingRate, DataType maxVal,
                             Int bufSize, PCMFormat *pcmIn);
void ltrtDownmixBufFloat(LtRtDownmix *pLtRtDownmix, Int cSamples,
                         LtRtBufType *bufIn, LtRtBufType *bufOut);

// APIs for U8 (PCM) I/O
WMARESULT ltrtDownmixInitBufPCM(LtRtDownmix *pLtRtDownmix,
                                Int nHalfFilterLen, Int samplingRate,
                                DataType maxVal, Int bufSize, PCMFormat *pcmIn);
void ltrtDownmixBufPCM(LtRtDownmix *pLtRtDownmix, Int cSamples, U8 *bufInPCM,
                       U8 *bufOutPCM);

#ifdef __cplusplus
}
#endif

#endif // _WMA_LTRT_H
