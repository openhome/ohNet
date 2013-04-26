//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __PCMFMT_COM_H__
#define __PCMFMT_COM_H__

#include "wmatypes.h"

typedef enum _PCMData {
    PCMDataPCM        = 0,
    PCMDataIEEE_FLOAT = 1,
} PCMData;

#pragma pack (push)
#pragma pack () // default
typedef struct _PCMFormat {
    WMA_U32 nSamplesPerSec;               
    WMA_U32 nChannels;
    WMA_U32 nChannelMask;
    WMA_U32 nValidBitsPerSample;
    WMA_U32 cbPCMContainerSize;
    PCMData pcmData;
} PCMFormat;
#pragma pack (pop)

#endif//__PCMFMT_COM_H__

#ifndef __PCMFMT_H__
#define __PCMFMT_H__

#ifdef __cplusplus
extern "C" {
#endif

WMA_Bool ValidatePCMFormat (void* loginst, PCMFormat* pFormat);
WMA_Bool ValidatePCMFormatWMA (void* loginst, PCMFormat* pFormat);

#ifdef _WAVEFORMATEX_
void WaveFormatEx2PCMFormat(WAVEFORMATEX* wfx, PCMFormat* pFormat);
void PCMFormat2WaveFormatEx(PCMFormat* pFormat, WAVEFORMATEX* wfx);
WMA_Bool ValidateWaveFormat(void* loginst, WAVEFORMATEX* wfx);
WMA_Bool ValidateUncompressedFormat(void* loginst, WAVEFORMATEX* wfx);
WMA_Bool ValidateUncompressedFormatMA(void* loginst, WAVEFORMATEX* wfx);

// Add channel mask validation additional to ValidateUncompressedFormat
WMA_Bool ValidateUncompressedFormatEx(void* loginst, WAVEFORMATEX* wfx);

#ifdef _WAVEFORMATEXTENSIBLE_
void PCMFormat2WaveFormatExtensible(PCMFormat* pFormat, WAVEFORMATEXTENSIBLE* wfx);
#endif//_WAVEFORMATEXTENSIBLE_
#endif//_WAVEFORMATEX_

#ifdef GUID_DEFINED
void FormatTag2GUID(WMA_U16 wFormatTag, GUID* pGUID);
#endif

WMA_Bool NeedExtensible(WMA_U32 nBitsPerSample, WMA_U32 nChannels, WMA_U32 nChannelMask);
WMA_Bool PCMFormatEquivalent(PCMFormat*, PCMFormat*);
WMA_U32 DefaultChannelMask(WMA_U32 nChannels);

#ifdef __cplusplus
}
#endif

#endif//__PCMFMT_H__

