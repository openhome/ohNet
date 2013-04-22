//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __CONFIGCOMMON_H__
#define __CONFIGCOMMON_H__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#ifndef _VIDEOONLY_
WMA_U32 MaxSamplesPerPacket(WMA_U32 ulVersion,
                            WMA_U32 ulSamplingRate,
                            WMA_U32 ulBitrate);

WMA_I32 msaudioGetSamplePerFrame (WMA_I32   cSamplePerSec, 
                              WMA_U32   dwBitPerSec, 
                              WMA_I32   iVersion,
                              WMA_U16   wEncOpt);

WMA_U32 prvVersionFromFormatTag(WMA_U16 wFormatTag);

WMA_Bool prvIsElementaryStream(WMA_U16 wFormatTag);

#endif

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif//__CONFIGCOMMON_H__
