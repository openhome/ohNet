//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __WMAFMT_H__
#define __WMAFMT_H__

#include "wmatyps.h"
#include "pcmfmt.h"

#ifndef __WMAFMT_COM_H__
#define __WMAFMT_COM_H__

// Place holder until msaudiofmt.h is updated
#if !defined (WAVE_FORMAT_WMAUDIO2_ES)
#define WAVE_FORMAT_WMAUDIO2_ES  0x0165
#endif
#if !defined (WAVE_FORMAT_WMAUDIO3_ES)
#define WAVE_FORMAT_WMAUDIO3_ES  0x0166
#endif
#if !defined (WAVE_FORMAT_WMAUDIO_LOSSLESS_ES)
#define WAVE_FORMAT_WMAUDIO_LOSSLESS_ES  0x0167
#endif


#pragma pack (push)
#pragma pack () // default
typedef struct _WMAFormat {
    WMA_U16 wFormatTag;
    WMA_U16 nChannels;
    WMA_U32 nSamplesPerSec;
    WMA_U32 nAvgBytesPerSec;
    WMA_U16 nBlockAlign;
    WMA_U16 nValidBitsPerSample;
    WMA_U32 nChannelMask;
    WMA_U16 wEncodeOpt;
    WMA_U16 wAdvancedEncodeOpt;
    WMA_U32 dwAdvancedEncodeOpt2;
} WMAFormat;

#pragma pack (pop)
#endif // __WMAFMT_COM_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward Declaration
typedef struct _WMAFormatInfo WMAFormatInfo;

#ifdef _WAVEFORMATEX_
void WaveFormat2WMAFormat(WAVEFORMATEX* wfx, WMAFormat* wmafmt);
void WMAFormat2WaveFormat(WMAFormat* wmafmt, WAVEFORMATEX* wfx);
#endif

  //void WMAFormatInfo2WaveFormat(WMAFormatInfo* pFormat, WAVEFORMATEX* wfx);
  //void WMAFormat2PartialWaveFormat(WMAFormat* pFormat, WAVEFORMATEX* wfx);
void WMAFormat2PCMFormat(WMAFormat* pSrc, PCMFormat* pDst);
void PCMFormat2WMAFormat(PCMFormat* pSrc, WMAFormat* pDst);
WMA_Bool ValidateWMAWaveFormat(void* loginst, WMA_U8* pb, WMA_U32 cb);
WMA_U32 WMAExtraDataSizeFromFormatTag(WMA_U16 wFormatTag);

#ifdef __cplusplus
}
#endif

#endif//__WMAFMT_H__

