//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "wmatypes.h"
#include "wmawfxdefs.h"
#include "pcmfmt.h"

#if defined(_XBOX) || defined(VOLKANO)
#define DISABLEWMDSPLOGGING
#endif // _XBOX

#ifdef DISABLEWMDSPLOGGING
#define WMDSPLOGMSG(x,...)
#else
#include "wmdsplogging.h"
#endif

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(a) (sizeof(a)/sizeof((a)[0]))
#endif

//*****************************************************************************************
//
// DefaultChannelMask
//   Returns the most likely channel mask for the given number of channels.
//
//*****************************************************************************************
#define MCMASK_MONO   SPEAKER_FRONT_CENTER
#define MCMASK_STEREO (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)
#define MCMASK_THREE  (SPEAKER_FRONT_CENTER | MCMASK_STEREO)
#define MCMASK_BACK   (SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)
#define MCMASK_QUAD   (MCMASK_STEREO | MCMASK_BACK)
#define MCMASK_5      (MCMASK_THREE | MCMASK_BACK)
#define MCMASK_5DOT1  (MCMASK_5 | SPEAKER_LOW_FREQUENCY)
#define MCMASK_6DOT1  (MCMASK_5DOT1 | SPEAKER_BACK_CENTER)
#define MCMASK_7DOT1  (MCMASK_5DOT1 | SPEAKER_SIDE_LEFT | SPEAKER_SIDE_RIGHT)

static const int g_ChannelMasks[] =  { 0, MCMASK_MONO, MCMASK_STEREO,
MCMASK_THREE, MCMASK_QUAD, MCMASK_5, MCMASK_5DOT1, MCMASK_6DOT1, MCMASK_7DOT1 };

U32 DefaultChannelMask(U32 nChannels)
{
  if (nChannels >= SIZEOF_ARRAY(g_ChannelMasks)) return 0;
  return g_ChannelMasks[nChannels];
}

void WaveFormatEx2PCMFormat(WAVEFORMATEX* wfx, PCMFormat* pFormat) 
{
  pFormat->nSamplesPerSec = wfx->nSamplesPerSec;
  pFormat->nChannels = wfx->nChannels;
  if (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) 
  {
    WAVEFORMATEXTENSIBLE* wfex = (WAVEFORMATEXTENSIBLE*)wfx;
    pFormat->nChannelMask = wfex->dwChannelMask;
    pFormat->nValidBitsPerSample = wfex->Samples.wValidBitsPerSample;
    pFormat->cbPCMContainerSize = wfx->wBitsPerSample / 8;
    if (IS_KSDATAFORMAT_SUBTYPE_PCM(&wfex->SubFormat))
      pFormat->pcmData = PCMDataPCM;
    else if (IS_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(&wfex->SubFormat))
      pFormat->pcmData = PCMDataIEEE_FLOAT;
  } 
  else
  {
    pFormat->nChannelMask = DefaultChannelMask(wfx->nChannels);
    pFormat->nValidBitsPerSample = wfx->wBitsPerSample;
    pFormat->cbPCMContainerSize = (wfx->wBitsPerSample + 7) / 8;
    if (wfx->wFormatTag == WAVE_FORMAT_PCM)
      pFormat->pcmData = PCMDataPCM;
    else if (wfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT)
      pFormat->pcmData = PCMDataIEEE_FLOAT;
  }
}

void SetRedundantFields(WAVEFORMATEX* wfx) 
{
    wfx->nBlockAlign = wfx->nChannels * ((wfx->wBitsPerSample + 7) / 8);
    wfx->nAvgBytesPerSec = wfx->nBlockAlign * wfx->nSamplesPerSec;
}

// similar to DEFINE_WAVEFORMATEX_GUID() in ksmedia.h        
void FormatTag2GUID(U16 wFormatTag, GUID* pGUID)
{
    pGUID->Data1 = wFormatTag;
    pGUID->Data2 = 0x0000;
    pGUID->Data3 = 0x0010;
    pGUID->Data4[0] = 0x80;
    pGUID->Data4[1] = 0x00;
    pGUID->Data4[2] = 0x00;
    pGUID->Data4[3] = 0xaa;
    pGUID->Data4[4] = 0x00;
    pGUID->Data4[5] = 0x38;
    pGUID->Data4[6] = 0x9b;
    pGUID->Data4[7] = 0x71;
}

void PCMFormat2WaveFormatEx(PCMFormat* pFormat, 
                            WAVEFORMATEX* wfx)
{
    wfx->cbSize = 0;
    if (pFormat->pcmData == PCMDataPCM)
        wfx->wFormatTag = WAVE_FORMAT_PCM;
    else if (pFormat->pcmData == PCMDataIEEE_FLOAT)
        wfx->wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
    wfx->nChannels  = (U16)pFormat->nChannels;
    wfx->nSamplesPerSec  = pFormat->nSamplesPerSec;
    wfx->wBitsPerSample = (U16)pFormat->nValidBitsPerSample;
    SetRedundantFields(wfx);
}

void PCMFormat2WaveFormatExtensible(PCMFormat* pFormat,
                                    WAVEFORMATEXTENSIBLE* wfx)
{
    PCMFormat2WaveFormatEx(pFormat, &wfx->Format);
    wfx->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    wfx->Format.cbSize = 22;
    wfx->Samples.wValidBitsPerSample = wfx->Format.wBitsPerSample;
    wfx->Format.wBitsPerSample = (wfx->Format.wBitsPerSample + 7) & ~7;

    if ((pFormat->cbPCMContainerSize * 8) > wfx->Format.wBitsPerSample)
    {
        wfx->Format.wBitsPerSample = (U16)(pFormat->cbPCMContainerSize * 8);
    }

    if (pFormat->pcmData == PCMDataPCM)
        FormatTag2GUID(WAVE_FORMAT_PCM, &(wfx->SubFormat));
    else if (pFormat->pcmData == PCMDataIEEE_FLOAT)
        FormatTag2GUID(WAVE_FORMAT_IEEE_FLOAT, &(wfx->SubFormat));

    wfx->dwChannelMask = pFormat->nChannelMask;
    SetRedundantFields(&wfx->Format);
}

Bool NeedExtensible(U32 nBitsPerSample, U32 nChannels, U32 nChannelMask)
{
  return ((nChannels > 2) || 
          (nChannelMask != DefaultChannelMask(nChannels)) ||
          (nBitsPerSample > 16) || (nBitsPerSample & 0x07));
}

#define CHECK_COND(x) if (x) { WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_Error, #x " !"); return False; }

Bool ValidateWaveFormat(void* loginst, WAVEFORMATEX* wfx) 
{
  // Note that this is used for both compressed and uncompressed
  // Note also that WMA uses 0x7fffffXX for nAvgBytesPerSec for VBR
  U32 nMaxChannels, nMaxSamplesPerSec, nMaxBlockAlign;
  //nMaxChannels = 1024, nMaxSamplesPerSec = 1048576, nMaxBlockAlign = 16777216;
  nMaxChannels = 32, nMaxSamplesPerSec = 384000, nMaxBlockAlign = 1048576;
  //nMaxChannels = 2, nMaxSamplesPerSec = 48000, nMaxBlockAlign = 65536;

  WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
               "WAVEFORMATEX = {%hd, %hd, %d, %d, %hd, %hd, %hd}",
               wfx->wFormatTag, wfx->nChannels, wfx->nSamplesPerSec,
               wfx->nAvgBytesPerSec, wfx->nBlockAlign, wfx->wBitsPerSample, wfx->cbSize);

  CHECK_COND((wfx->nChannels <= 0) || (wfx->nChannels > nMaxChannels));
  CHECK_COND((wfx->nSamplesPerSec <= 0) || (wfx->nSamplesPerSec > nMaxSamplesPerSec));
  CHECK_COND((wfx->nBlockAlign <= 0) || (wfx->nBlockAlign > nMaxBlockAlign));
  CHECK_COND((wfx->wBitsPerSample > 64));
  return True;
}

Bool ValidatePCMFormat(void* loginst, PCMFormat* pFormat) 
{
    U32 nMaxChannels, nMaxSamplesPerSec;
    nMaxChannels = 32, nMaxSamplesPerSec = 384000;
    
    WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
        "PCMFormat = {%d, %d, %hd, %d, %d, %d}",
        pFormat->nSamplesPerSec, pFormat->nChannels, pFormat->nChannelMask, 
        pFormat->nValidBitsPerSample, pFormat->cbPCMContainerSize, pFormat->pcmData);

    CHECK_COND((pFormat->nSamplesPerSec <= 0) || (pFormat->nSamplesPerSec > nMaxSamplesPerSec));
    CHECK_COND((pFormat->nChannels <= 0) || (pFormat->nChannels > nMaxChannels));

    // Channel Mask
    if (pFormat->nChannelMask)
    {
        // Make sure number of 1's matches number of channels
        WMA_U32 cBits = 0;
        WMA_U32 nTmpMask = pFormat->nChannelMask;
        while (nTmpMask)
        {
            if (nTmpMask & 0x1)
                cBits++;
            nTmpMask >>= 1;
        }
        CHECK_COND(pFormat->nChannels != cBits);
    }
    CHECK_COND((pFormat->nValidBitsPerSample <= 0));
    CHECK_COND((pFormat->cbPCMContainerSize <= 0));
    CHECK_COND((pFormat->cbPCMContainerSize * 8) < pFormat->nValidBitsPerSample);
    CHECK_COND((pFormat->pcmData != PCMDataPCM) && (pFormat->pcmData != PCMDataIEEE_FLOAT));
    if (PCMDataIEEE_FLOAT == pFormat->pcmData)
    {
        CHECK_COND(pFormat->cbPCMContainerSize * 8 != pFormat->nValidBitsPerSample);
        CHECK_COND(pFormat->nValidBitsPerSample > 64);
        CHECK_COND(pFormat->nValidBitsPerSample % 32);
    }
    else if (PCMDataPCM == pFormat->pcmData)
    {
        CHECK_COND(pFormat->nValidBitsPerSample > 32);
    }
    else
    {
        CHECK_COND(1);
    }

    return True;
} // ValidatePCMFormat

Bool ValidatePCMFormatWMA(void* loginst, PCMFormat* pFormat)
{
    if (!ValidatePCMFormat(loginst, pFormat))
    {
        return False;
    }

    CHECK_COND(pFormat->cbPCMContainerSize > 4); // PCM format restriction specific to WMA codec

    return True;
}


Bool ValidateUncompressedFormat(void* loginst, WAVEFORMATEX* wfx) 
{
  CHECK_COND((wfx->wFormatTag != WAVE_FORMAT_PCM) &&
             (wfx->wFormatTag != WAVE_FORMAT_IEEE_FLOAT) &&
             (wfx->wFormatTag != WAVE_FORMAT_EXTENSIBLE));
  if (!ValidateWaveFormat(loginst, wfx)) return False;
  if (wfx->wBitsPerSample == 0) return False;
  if (wfx->wBitsPerSample & 7)  return False; // this is container size, should be multiples of 8
  CHECK_COND(wfx->wBitsPerSample / 8 * wfx->nChannels != wfx->nBlockAlign);
  CHECK_COND(wfx->nBlockAlign * wfx->nSamplesPerSec != wfx->nAvgBytesPerSec);
  if (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
    WAVEFORMATEXTENSIBLE* wfex = (WAVEFORMATEXTENSIBLE*) wfx;
    WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
                 "WAVEFORMATEXTENSIBLE = {%hd, %08X, %08X}",
                 wfex->Samples.wValidBitsPerSample, wfex->dwChannelMask, wfex->SubFormat.Data1);
    CHECK_COND(wfx->cbSize < sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX));
    CHECK_COND(wfex->Samples.wValidBitsPerSample > wfex->Format.wBitsPerSample); // This is the actual number of valid bits, should be <= container size
    CHECK_COND((wfex->SubFormat.Data1 != WAVE_FORMAT_PCM &&
        wfex->SubFormat.Data1 != WAVE_FORMAT_IEEE_FLOAT));
  }else {
    if (wfx->wFormatTag == WAVE_FORMAT_PCM) {
      CHECK_COND(NeedExtensible(wfx->wBitsPerSample, wfx->nChannels, DefaultChannelMask(wfx->nChannels)));
    } else if (wfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
      CHECK_COND((wfx->nChannels > 2) || (wfx->wBitsPerSample != 32));
    }
  }
  return True;
}

Bool PCMFormatEquivalent(PCMFormat* a, PCMFormat* b) 
{
    // not memcmp for fear of garbage in padding bytes
    return(a->nSamplesPerSec      == b->nSamplesPerSec) &&
          (a->nChannels           == b->nChannels) &&
          (a->nChannelMask        == b->nChannelMask) &&
          (a->nValidBitsPerSample == b->nValidBitsPerSample) &&
          (a->cbPCMContainerSize  == b->cbPCMContainerSize) &&
          (a->pcmData             == b->pcmData);
}

// for PCM input that has more than 2 channels but does not require WAVEFORMATEXTENSIBLE 
// for example multiple microphone input for Mic-array applications
// added by hongwang 9/19/03
Bool ValidateUncompressedFormatMA(void* loginst, WAVEFORMATEX* wfx) 
{
  CHECK_COND((wfx->wFormatTag != WAVE_FORMAT_PCM) &&
             (wfx->wFormatTag != WAVE_FORMAT_IEEE_FLOAT) &&
             (wfx->wFormatTag != WAVE_FORMAT_EXTENSIBLE));
  if (!ValidateWaveFormat(loginst, wfx)) return False;
  if (wfx->wBitsPerSample == 0) return False;
  if (wfx->wBitsPerSample & 7)  return False;
  CHECK_COND(wfx->wBitsPerSample / 8 * wfx->nChannels != wfx->nBlockAlign);
  CHECK_COND(wfx->nBlockAlign * wfx->nSamplesPerSec != wfx->nAvgBytesPerSec);
  if (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
    WAVEFORMATEXTENSIBLE* wfex = (WAVEFORMATEXTENSIBLE*) wfx;
    WMDSPLOGMSG(WMDSPCALLERINFO, loginst, WMDSPLogCat_Format, WMDSPLogLevel_OccasionalEvent,
                 "WAVEFORMATEXTENSIBLE = {%hd, %08X, %08X}",
                 wfex->Samples.wValidBitsPerSample, wfex->dwChannelMask, wfex->SubFormat.Data1);
    CHECK_COND(wfx->cbSize < sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX));
    CHECK_COND(wfex->Samples.wValidBitsPerSample > wfex->Format.wBitsPerSample);
    CHECK_COND((wfex->SubFormat.Data1 != WAVE_FORMAT_PCM &&
        wfex->SubFormat.Data1 != WAVE_FORMAT_IEEE_FLOAT));
  }else {
    if (wfx->wFormatTag == WAVE_FORMAT_PCM) {
      CHECK_COND( (wfx->wBitsPerSample != 16));
    } else if (wfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
      CHECK_COND((wfx->wBitsPerSample != 32));
    }
  }

  return True;
}

// Add channel mask validation additional to ValidateUncompressedFormat
Bool ValidateUncompressedFormatEx(void* loginst, WAVEFORMATEX* wfx) 
{
    CHECK_COND(!ValidateUncompressedFormat(loginst, wfx)); 

    // Check channel mask
    if (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) 
    {
        WMA_U32 uMask = ((WAVEFORMATEXTENSIBLE*)wfx)->dwChannelMask;
        if (uMask)
        {
            WMA_U32 uBits = 0;
            while(uMask)
            {
                if (uMask & 0x01) uBits++;
                uMask >>= 1;
            }
            CHECK_COND(uBits != wfx->nChannels);
        }
    }
    return True;
}
