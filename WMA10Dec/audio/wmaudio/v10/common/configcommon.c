//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Std, WMA Pro, and WMA Lossless.
//*@@@---@@@@******************************************************************

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include "msaudio.h"
#include "wmafmt.h"

#if !defined (WAVE_FORMAT_MSAUDIO1)
#define WAVE_FORMAT_MSAUDIO1  0x0160
#endif
#if !defined (WAVE_FORMAT_MSAUDIO2)
#define WAVE_FORMAT_MSAUDIO2  0x0161
#endif
#if !defined (WAVE_FORMAT_MSAUDIO3)
#define WAVE_FORMAT_MSAUDIO3  0x0162
#endif
#if !defined (WAVE_FORMAT_WMAUDIO_LOSSLESS)
#define WAVE_FORMAT_WMAUDIO_LOSSLESS  0x0163
#endif
#if !defined (WAVE_FORMAT_WMASPDIF)
#define WAVE_FORMAT_WMASPDIF 0x164
#endif

I32 msaudioGetSamplePerFrameFromWMAFormat (WMAFormat *pWMAFormat)
{
    I32 iPCMSamplePerFrame = msaudioGetSamplePerFrame (
                                     pWMAFormat->nSamplesPerSec, 
                                     pWMAFormat->nAvgBytesPerSec * 8,
                                     prvVersionFromFormatTag(pWMAFormat->wFormatTag), 
                                     pWMAFormat->wEncodeOpt
                             );
    return iPCMSamplePerFrame;
       
}
//*****************************************************************************************
//
// msaudioGetSamplePerFrame
//
//*****************************************************************************************
I32 msaudioGetSamplePerFrame (Int   cSamplePerSec, 
                              U32   dwBitPerSec, 
                              Int   iVersion,
                              U16   wEncOpt)
{
    //return NEW samples coming into a frame; actual samples in a frame
    //should be * 2 due to 50% overlapping window
    I32 cSamplePerFrame;
    U32 dwBytesPerFrame;

    //don't know what to do
    if ((dwBitPerSec == 0 && iVersion < 3) || iVersion > 3 || cSamplePerSec <= 0)
        return 0;

    if (cSamplePerSec <= 8000)
        cSamplePerFrame = 512;
    else if (cSamplePerSec <= 11025)
        cSamplePerFrame = 512;
    else if (cSamplePerSec <= 16000) {
        cSamplePerFrame = 512;
    }
    else if (cSamplePerSec <= 22050) {
        cSamplePerFrame = 1024;
    }
    else if (cSamplePerSec <= 32000) {
        if(iVersion == 1)
            cSamplePerFrame = 1024;
        else
            cSamplePerFrame = 2048;
    }
    else if (cSamplePerSec <= 44100)
         cSamplePerFrame = 2048;
    else if (cSamplePerSec <= 48000)
        cSamplePerFrame = 2048;
    else if (cSamplePerSec <= 96000)
        cSamplePerFrame = 4096;
    else if (cSamplePerSec <= 192000)
        cSamplePerFrame = 8192;
    else
        cSamplePerFrame = 8192; // cap to 8192
    

    // Since V3 permits one frame spans over multiple packets, obsolete comments are removed.	

    if (iVersion == 3)
    {
#ifdef ENABLE_MULTIPLE_OF_160
        if (ENCOPT3_ADV_FRMSIZE_MOD_ON & wEncOpt)
        {
            // Multiples of 160
            U16 iFrmSizeModifier = ((wEncOpt & ENCOPT3_FRM_SIZE_MOD) >> 1) |
                ((wEncOpt & ENCOPT3_ADV_FRMSIZE_MOD_HIGH) >> 7);
            cSamplePerFrame = (iFrmSizeModifier + 1) * 160; // to avoid frame sizes of zero.
        }
        else
#endif
        {
            //Traditional sampling rate-based frame size multiplier
            U16 iFrmSizeModifier = wEncOpt & ENCOPT3_FRM_SIZE_MOD;
            if (iFrmSizeModifier == 2)
            {
                cSamplePerFrame *= 2;
            }
            else if (iFrmSizeModifier == 4)
            {
                cSamplePerFrame /= 2;
            }
            else if (iFrmSizeModifier == 6) 
            {
                cSamplePerFrame /= 4;
            }
        }
    }

    if (iVersion < 3)
    {
        dwBytesPerFrame = (U32) (((cSamplePerFrame*dwBitPerSec + cSamplePerSec/2)/cSamplePerSec + 7)/8);
        if ( dwBytesPerFrame==0 && (cSamplePerFrame*dwBitPerSec) == 0 )
        {
            // this can happen when garbage data sets dwBitsPerSec to a very large number
            // avoid an infinite loop below
            dwBitPerSec = cSamplePerSec;
            dwBytesPerFrame = (U32) (((cSamplePerFrame*dwBitPerSec + cSamplePerSec/2)/cSamplePerSec + 7)/8);
        }
        if (dwBytesPerFrame <= 1) // This condition is redundent, but we (hongwang, naveent, wchen) decided to keep as is to serve as a comment and to avoid regression. 
        {   //silence mode
            while (dwBytesPerFrame == 0)
            {
                cSamplePerFrame *= 2;           //save more bits; quartz can't take too big a value
                dwBytesPerFrame = (U32) (((cSamplePerFrame*dwBitPerSec + cSamplePerSec/2)/cSamplePerSec + 7)/8);
            }
        }
    }

    return cSamplePerFrame;
} // msaudioGetSamplePerFrame

//*****************************************************************************************
//
// MaxSamplesPerPacket
//   Returns the largest possible number of PCM samples that the decoder can produce
//   from a single compressed packet.  
//
//*****************************************************************************************
U32 MaxSamplesPerPacket(U32 ulVersion, U32 ulSamplingRate, U32 ulBitrate) {
   assert(ulVersion <= 2); // passing 0 for wEncOpt ok for ver < 3
   return (16 + 1) * msaudioGetSamplePerFrame(ulSamplingRate,ulBitrate, ulVersion, 0);
}

U32 prvVersionFromFormatTag(U16 wFormatTag) 
{
    U32 nVersion = 0;

    switch (wFormatTag)
    {
    case WAVE_FORMAT_MSAUDIO1:
        nVersion = 1;
        break;

    case WAVE_FORMAT_MSAUDIO2:              // WMA-Std
    case WAVE_FORMAT_WMAUDIO2_ES:           // WMA-Std over UES
        nVersion = 2;
        break;

    case WAVE_FORMAT_MSAUDIO3:              // WMA-Pro / WMA-Pro+
    case WAVE_FORMAT_WMAUDIO_LOSSLESS:      // WMA-Lsl
    case WAVE_FORMAT_WMASPDIF:              // WMA-Pro over S/PDIF
    case WAVE_FORMAT_WMAUDIO3_ES:           // WMA-Pro / WMA-Pro+ over UES 
    case WAVE_FORMAT_WMAUDIO_LOSSLESS_ES:   // WMA-Lsl over UES
        nVersion = 3;
        break;

    default:
        nVersion = 0;
        break;
    }
    return nVersion;
} // prvVersionFromFormatTag

Bool prvIsElementaryStream(U16 wFormatTag)
{
    if (WAVE_FORMAT_WMAUDIO2_ES         == wFormatTag ||
        WAVE_FORMAT_WMAUDIO3_ES         == wFormatTag ||
        WAVE_FORMAT_WMAUDIO_LOSSLESS_ES == wFormatTag)
    {
        return WMAB_TRUE;
    }
    else
    {
        return WMAB_FALSE;
    }
} // prvIsElementaryStream
