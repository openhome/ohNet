//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef __PLAYROPT_H__
#define __PLAYROPT_H__

// **************************************************************************
// Player Options
// **************************************************************************
#define PLAYOPT_HALFTRANSFORM      0x0002
#define PLAYOPT_PAD2XTRANSFORM     0x0008
#define PLAYOPT_DYNAMICRANGECOMPR  0x0080
#define PLAYOPT_LTRT               0x0100
#define PLAYOPT_IGNOREFREQEX       0x0200
#define PLAYOPT_IGNORECX           0x0400
// defines for WMAVoice
// in this CPU_RESOURCE field, 0 and 4 both equate to a 206 MHz StrongARM level of cpu performance.  
// Some future release may implement auomatic adaption for 0 but not for 4.
// 1 is suitable for an ARM7 or ARM9 implementation that runs at about 70 MHz.
// other CPU's should probably pass 0 but can try other values.
// the codec may apply higher levels of post processing for higher levels of this value which will result in higher quality.
// However, raising the number too far will cause the codec to try too complex post processing and result in stuttering audio.
#define PLAYOPT_CPU_RESOURCE_MASK   0x000F0000
#define PLAYOPT_CPU_RESOURCE_AUTO   0
#define PLAYOPT_CPU_RESOURCE(a) ((a)<<16)
#define PLAYOPT_CPU_RESOURCE_LOW    PLAYOPT_CPU_RESOURCE(2)
#define PLAYOPT_CPU_RESOURCE_NORMAL PLAYOPT_CPU_RESOURCE(8)

// **************************************************************************
// Dynamic Range Control settings
// **************************************************************************
#define WMA_DRC_HIGH 0
#define WMA_DRC_MED 1
#define WMA_DRC_LOW 2

// **************************************************************************
// Player Info Structure
// **************************************************************************

typedef struct _WMAPlayerInfo
{
    WMA_U16 nPlayerOpt;        // Bit fields based on above defines
    WMA_I32 *rgiMixDownMatrix; // Can be null to invoke defaults
    WMA_I32 iPeakAmplitudeRef;
    WMA_I32 iRmsAmplitudeRef;
    WMA_I32 iPeakAmplitudeTarget;
    WMA_I32 iRmsAmplitudeTarget;
    WMA_I16 nDRCSetting;       // Dynamic range control setting
    WMA_I32 iLtRtBufsize;
    WMA_I32 iLtRtQuality;
} WMAPlayerInfo;

#endif//__PLAYROPT_H__
