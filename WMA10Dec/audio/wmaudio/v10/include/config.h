//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "wmaenc.h"

// The XxxGetXxxXxx funstions below are used to enumerate supported parameter
// combinations.  ulIndex is a 0-based index, the funtions return FALSE if it
// is out of range.
//
// The XxxCheckXxxXxx functions return TRUE if the parameter combination is
// supported, FALSE otherwise.

typedef struct _CoefStream CoefStream;

#ifdef __cplusplus
extern "C" {
#endif

    // Using a value of 1 can lower the encoder latency by one frame than usual.
//#define CDELAYFRM_IF_CONSTRAINENCLATENCY 1
#define CDELAYFRM_IF_CONSTRAINENCLATENCY 2

   // Checks if the codec can encode this PCM at all (at at least some bitrate)
WMA_Bool CheckPCMParams(WMA_U32 ulSamplingRate, WMA_U32 ulChannels);
WMA_U32 DefaultChannelMask(WMA_U32 nChannels);

const extern WMA_U32 g_ulFormatSetFlag;
#define FORMATSET_FLAG_EUTIL 0x01
#define FORMATSET_FLAG_DMO   0x02
#define FORMATSET_FLAG_LOWDELAY   0x04
#define FORMATSET_FLAG_RTSPDIF    0x0100 // supports RTSPDIF mode

//  PLUSMODE_FLAG_FEXV1 not compatible with PLUSMODE_FLAG_CHEX
#define PLUSMODE_FLAG_FEXV1  0x01 //coding domain fex (v1).
#define PLUSMODE_FLAG_FEXV2  0x02 //recon+coding domain fex(v2).
#define PLUSMODE_FLAG_CHEX   0x04 //channel extension.
#define PLUSMODE_FLAG_CHEXLC 0x08 //channel extension, lower channel base
#define PLUSMODE_FLAG_FEXV3  0x10 //recon+coding domain fex(v3).

//
// For the GetXxxXxx functions, the entire WMAFormatInfo is an output parameter.
// For CheckFormat, the WAVEFORMATEX stuff is input and the miscellaneous fields
// at the end are output.
//

WMA_U32 FormatCount(WMA_U32 ulVersion, 
                    WMA_Bool fEnumerateLowDelayModes,
                    WMAEncFormatOpts* pOpts); // in

WMA_Bool EnumFormats(WMA_U32  ulVersion, 
                     WMA_Bool fEnumerateLowDelayModes, // in
                     WMAEncFormatOpts* pOpts, // in
                     WMA_U32 *pulIndex,         // in/out - see code
                     WMAFormatInfo* p);     // out

WMA_Bool EnumByPCM(WMA_U32 ulVersion, 
                   WMA_Bool fEnumerateLowDelayModes, // in
                   WMAEncFormatOpts* pOpts,   // in
                   PCMFormat* pPCM,         // in
                   WMA_U32 *pulIndex,           // in/out - see code
                   WMAFormatInfo* pFormat); // out

// If you know the sampling rate / channels AND the approximate bitrate you
// want, call GetFormat() to get the corresponding WMAFormatInfo parameters.
// Call PCMFormat2WMAFormat() to create the input WMAFormat struct, and
// set nBlockAlign/nAvgBytesPerSec/wFormatTag/wEncodeOpt as desired (leave them
// 0 if no preference).
// The output WMAFormat contained in WMAFormatInfo may differ from the input one.
WMA_Bool GetFormat(WMAFormat* pDesired,     // in
                   WMAEncFormatOpts* pOpts,   // in
                   WMA_Bool bWMAInSpeech,     // in
                   WMAFormatInfo* pFormat); // out

// This functions checks to see whether the specified format meets the 
// enclatency, declatency and preferred framesize specified by the user.
WMA_Bool prvCheckFormatForLatency(WMAFormatInfo*    pFormat, // in
                                  WMAEncFormatOpts* pOpts);   // in

#ifdef __cplusplus
}
#endif


#endif //__CONFIG_H__
