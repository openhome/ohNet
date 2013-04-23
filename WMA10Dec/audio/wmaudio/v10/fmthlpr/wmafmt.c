//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#if defined(SCRAMBLE_GLOBAL_SYMBOL_NAMES) || defined(UNDER_CE)
#include "scramble.h"
#endif

#include "wmatypes.h"
#include "wmawfxdefs.h"
#include "wmafmt.h"
#include "pcmfmt.h"

#if defined(macintosh)
#   include <string.h>
#endif

#if !defined(__arm) && !defined(macintosh)
#include <string.h>
#endif

#include "wmawintypes.h"
#include "configcommon.h"
#if !defined(_XBOX) && !defined(OPENHOME)
#include "wmdsplogging.h"
#else
#define WMDSPLOGMSG(a,...)
#endif

#define NOBITMAP
#define NEAR
#define FAR

#include "mmreg_.h"

#ifndef UNDER_CE
#include <assert.h>
#else
#define assert
#endif


void WaveFormat2WMAFormat(WAVEFORMATEX* wfx, WMAFormat* wmafmt)
{
    // Start with a clean slate
    memset(wmafmt, 0, sizeof(WMAFormat));
    wmafmt->wFormatTag      = wfx->wFormatTag;
    wmafmt->nSamplesPerSec  = wfx->nSamplesPerSec;      
    wmafmt->nChannels       = wfx->nChannels;           
    wmafmt->nAvgBytesPerSec = wfx->nAvgBytesPerSec;     
    wmafmt->nBlockAlign     = wfx->nBlockAlign;     

    if (wfx->wFormatTag == WAVE_FORMAT_MSAUDIO1)
    {
        MSAUDIO1WAVEFORMAT* msa1fmt = (MSAUDIO1WAVEFORMAT*)wfx;
        wmafmt->wEncodeOpt       = msa1fmt->wEncodeOptions;      
        wmafmt->nChannelMask = DefaultChannelMask(wmafmt->nChannels);
        wmafmt->nValidBitsPerSample = 16;
    } 
    else if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO2 ||
        wfx->wFormatTag == WAVE_FORMAT_WMAUDIO2_ES)
    {
        WMAUDIO2WAVEFORMAT* wma2fmt = (WMAUDIO2WAVEFORMAT*)wfx;
        wmafmt->wEncodeOpt       = wma2fmt->wEncodeOptions;      
        wmafmt->nChannelMask = DefaultChannelMask(wmafmt->nChannels);
        wmafmt->nValidBitsPerSample = 16;
    }
    else if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3 || 
        wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3_ES ||
        wfx->wFormatTag == WAVE_FORMAT_WMAUDIO_LOSSLESS)
    {
        WMAUDIO3WAVEFORMAT* wma3fmt = (WMAUDIO3WAVEFORMAT*)wfx;

        wmafmt->wEncodeOpt           = wma3fmt->wEncodeOptions;
        wmafmt->nChannelMask         = wma3fmt->dwChannelMask;
        wmafmt->nValidBitsPerSample  = wma3fmt->wValidBitsPerSample;
        wmafmt->wAdvancedEncodeOpt   = wma3fmt->wReserved3;
        wmafmt->dwAdvancedEncodeOpt2 = wma3fmt->dwReserved2;
    }
    else
    {
        // To keep prefix happy
        wmafmt->wEncodeOpt   = 0;      
        wmafmt->nChannelMask = DefaultChannelMask(wmafmt->nChannels);
        wmafmt->nValidBitsPerSample = 16;
    }
} // WaveFormat2WMAFormat

U32 WMAExtraDataSizeFromFormatTag(U16 wFormatTag) 
{
    if (wFormatTag == WAVE_FORMAT_MSAUDIO1)
        return sizeof(MSAUDIO1WAVEFORMAT);
    else if (wFormatTag == WAVE_FORMAT_WMAUDIO2)
        return sizeof(WMAUDIO2WAVEFORMAT);
    else if (wFormatTag == WAVE_FORMAT_WMAUDIO3 ||
        wFormatTag == WAVE_FORMAT_WMAUDIO_LOSSLESS)
        return sizeof(WMAUDIO3WAVEFORMAT);
    else
        return -1;
} // WMAExtraDataSizeFromFormatTag

// reverse engineer the config.c value based on the WAVEFORMATEX one
static U32 prvOfficialBitrate(U32 nAvgBytesPerSec) 
{
    U32 nBitsPerSec = nAvgBytesPerSec * 8;

    if (nBitsPerSec > 500) // don't try to round the "silence" mode bitrate
        nBitsPerSec = (nBitsPerSec + 500) / 1000 * 1000;
    return nBitsPerSec;
} // prvOfficialBitrate

void WMAFormat2WaveFormat(WMAFormat* pFormat, WAVEFORMATEX* wfx)
{
    wfx->wFormatTag = pFormat->wFormatTag;
    wfx->nChannels       = (U16)(pFormat->nChannels);
    wfx->nSamplesPerSec  = pFormat->nSamplesPerSec;
    wfx->nAvgBytesPerSec = pFormat->nAvgBytesPerSec;
    wfx->nBlockAlign     = (U16)(pFormat->nBlockAlign);
    wfx->wBitsPerSample  = (U16)(pFormat->nValidBitsPerSample);
    wfx->cbSize          = (U16)WMAExtraDataSizeFromFormatTag(wfx->wFormatTag) - sizeof(WAVEFORMATEX);

    if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3 || 
        wfx->wFormatTag == WAVE_FORMAT_WMAUDIO_LOSSLESS)
    {
        WMAUDIO3WAVEFORMAT* wfmt = (WMAUDIO3WAVEFORMAT*)wfx;
        wfmt->wValidBitsPerSample = (U16)pFormat->nValidBitsPerSample;
        wfmt->dwChannelMask       = pFormat->nChannelMask;
        wfmt->dwReserved1 = 0;
        wfmt->dwReserved2 = 0;
        wfmt->wEncodeOptions = pFormat->wEncodeOpt;
        wfmt->wReserved3 = 0;
        if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3)
        {
            wfmt->wReserved3  = pFormat->wAdvancedEncodeOpt;
            wfmt->dwReserved2 = pFormat->dwAdvancedEncodeOpt2;
        }
    }
    else if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO2)
    {
        WMAUDIO2WAVEFORMAT* wfmt = (WMAUDIO2WAVEFORMAT*)wfx;
        wfmt->dwSamplesPerBlock = MaxSamplesPerPacket(2, pFormat->nSamplesPerSec, prvOfficialBitrate(pFormat->nAvgBytesPerSec));
        wfmt->wEncodeOptions    = pFormat->wEncodeOpt;
        // Per BeckyW, neither Corona nor Zeusette uses this, so we can set it to anything.
        wfmt->dwSuperBlockAlign = 0; // used to come from prvPseudoSuperframeSize()
    } 
    else 
    {
        assert(!"unknown format tag");
    }
} // WMAFormat2WaveFormat

void WMAFormat2PartialWaveFormat(WMAFormat* pFormat, WAVEFORMATEX* wfx)
{
    wfx->wFormatTag = pFormat->wFormatTag;
    wfx->nChannels       = (U16)(pFormat->nChannels);
    wfx->nSamplesPerSec  = pFormat->nSamplesPerSec;
    wfx->nAvgBytesPerSec = pFormat->nAvgBytesPerSec;
    wfx->nBlockAlign     = (U16)(pFormat->nBlockAlign);
    wfx->wBitsPerSample  = (U16)(pFormat->nValidBitsPerSample);
    wfx->cbSize          = (U16)WMAExtraDataSizeFromFormatTag(wfx->wFormatTag) - sizeof(WAVEFORMATEX);

    if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3 || 
        wfx->wFormatTag == WAVE_FORMAT_WMAUDIO_LOSSLESS)
    {
        WMAUDIO3WAVEFORMAT* wfmt = (WMAUDIO3WAVEFORMAT*)wfx;
        wfmt->wValidBitsPerSample = (U16)pFormat->nValidBitsPerSample;
        wfmt->dwChannelMask       = pFormat->nChannelMask;
        wfmt->dwReserved1 = 0;
        wfmt->dwReserved2 = 0;
        wfmt->wEncodeOptions = pFormat->wEncodeOpt;
        wfmt->wReserved3 = 0;
        if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3)
        {
            wfmt->wReserved3  = pFormat->wAdvancedEncodeOpt;
            wfmt->dwReserved2 = pFormat->dwAdvancedEncodeOpt2;
        }
    } 
    else if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO2)
    {
        WMAUDIO2WAVEFORMAT* wfmt = (WMAUDIO2WAVEFORMAT*)wfx;
        wfmt->wEncodeOptions    = pFormat->wEncodeOpt;
    } 
    else 
    {
        assert(!"unknown format tag");
    }

} // WMAFormat2PartialWaveFormat

Void prvAdjustChannelForCx(U16 uAdvancedEncodeOpt,
                           U32 uAdvancedEncodeOpt2,
                           U16 iCodedCh, U16 *piOrigCh,
                           U32 uCodedChMask, U32 *puOrigChMask);

// creates default output format
void WMAFormat2PCMFormat(WMAFormat* pSrc, PCMFormat* pDst)
{
    pDst->nSamplesPerSec = pSrc->nSamplesPerSec;
    pDst->nChannels = pSrc->nChannels;
    pDst->nChannelMask = pSrc->nChannelMask;
    pDst->nValidBitsPerSample = pSrc->nValidBitsPerSample;
    pDst->cbPCMContainerSize = (pSrc->nValidBitsPerSample + 7) / 8; 
    pDst->pcmData = PCMDataPCM;
    if (WAVE_FORMAT_WMAUDIO3 == pSrc->wFormatTag)
    {
        U16 iCh = pSrc->nChannels;
        U32 uChMask = pSrc->nChannelMask;
        prvAdjustChannelForCx(pSrc->wAdvancedEncodeOpt,
                              pSrc->dwAdvancedEncodeOpt2,
                              iCh, &iCh, uChMask, &uChMask);
        pDst->nChannels = iCh;
        pDst->nChannelMask = uChMask;
    }
} // WMAFormat2PCMFormat

// This is used to compose a WMAFormat to pass to GetFormat() when only PCMFormat
// is available.  GetFormat() interprets non-0 values are preferences, so this
// function sets fields that are not in the PCMFormat to 0.  The caller is welcome
// to set them to non-0 after calling this function but before calling GetFormat()
// if it has preferences.
void PCMFormat2WMAFormat(PCMFormat* pSrc, WMAFormat* pDst)
{
    memset(pDst, 0, sizeof(WMAFormat));
    pDst->wFormatTag           = 0;         
    pDst->nChannels            = (WMA_U16)pSrc->nChannels;
    pDst->nSamplesPerSec       = pSrc->nSamplesPerSec;
    pDst->nAvgBytesPerSec      = 0;   
    pDst->nBlockAlign          = 0;
    pDst->nValidBitsPerSample  = (WMA_U16)pSrc->nValidBitsPerSample;
    pDst->nChannelMask         = pSrc->nChannelMask;
    pDst->wEncodeOpt           = 0;
} // PCMFormat2WMAFormat

#define CHECK_COND(x) if (x) { WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_Error, #x " !"); return False; }

WMA_Bool ValidateWMAWaveFormat(void* loginst, WMA_U8* pb, WMA_U32 cb) 
{
    WAVEFORMATEX* wfx = (WAVEFORMATEX*)pb;
    U32 cbFormat = WMAExtraDataSizeFromFormatTag(wfx->wFormatTag);

    // The GUIDs, if present should also be checked: TODO
    CHECK_COND(cb < sizeof(WAVEFORMATEX));
    CHECK_COND(cb > 1024);
    if (!ValidateWaveFormat(loginst, wfx)) return False; 
    CHECK_COND(cbFormat == -1);
    CHECK_COND(sizeof(WAVEFORMATEX) + wfx->cbSize < cbFormat);
    CHECK_COND(cb < cbFormat);
    CHECK_COND(wfx->wBitsPerSample > 32);
    if (wfx->wFormatTag == WAVE_FORMAT_MSAUDIO1) 
    {
        MSAUDIO1WAVEFORMAT* fmt = (MSAUDIO1WAVEFORMAT*)wfx;
        WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
                     "MSAUDIO1WAVEFORMAT extended data = {%hd, %04hX}",
                     fmt->wSamplesPerBlock, fmt->wEncodeOptions);
    } 
    else if (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO2) 
    {
        WMAUDIO2WAVEFORMAT* fmt = (WMAUDIO2WAVEFORMAT*)wfx;
        WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
                     "WMAUDIO2WAVEFORMAT extended data = {%d, %04hX, %d}",
                     fmt->dwSamplesPerBlock, fmt->wEncodeOptions, fmt->dwSuperBlockAlign);
    } 
    else if ((wfx->wFormatTag == WAVE_FORMAT_WMAUDIO3) || 
               (wfx->wFormatTag == WAVE_FORMAT_WMAUDIO_LOSSLESS)) 
    {
        WMAUDIO3WAVEFORMAT* fmt = (WMAUDIO3WAVEFORMAT*)wfx;
        WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
                     "WMAUDIO3WAVEFORMAT extended data = {%hu, %08X, %04hX, %08X, %08X, %04hX}",
                     fmt->wValidBitsPerSample, fmt->dwChannelMask, fmt->wEncodeOptions,
                     fmt->dwReserved1, fmt->dwReserved2, fmt->wReserved3);
    }

    return True;
} // ValidateWMAWaveFormat

