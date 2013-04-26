//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       msaudiofmt.h
//
//--------------------------------------------------------------------------

/* msaudiofmt.h */

#ifndef _MSAUDIO_FMT_H
#define _MSAUDIO_FMT_H

#ifndef RC_INVOKED              // from mmreg.h
#pragma pack(1)                 // Assume byte packing throughout
#endif  // RC_INVOKED

// ======================================================================
// Windows Media Audio (common)

#define MM_MSFT_ACM_WMAUDIO  39

#define WMAUDIO_BITS_PER_SAMPLE    16 // just an uncompressed size...
#define WMAUDIO_MAX_CHANNELS       2


// ======================================================================
// Windows Media Audio V1 (a.k.a. "MSAudio")

#define WAVE_FORMAT_MSAUDIO1  0x0160
#define MM_MSFT_ACM_MSAUDIO1  39

typedef struct msaudio1waveformat_tag {
    WAVEFORMATEX wfx;
    WORD         wSamplesPerBlock; // only counting "new" samples "= half of what will be used due to overlapping
    WORD         wEncodeOptions;
} MSAUDIO1WAVEFORMAT;

typedef MSAUDIO1WAVEFORMAT FAR  *LPMSAUDIO1WAVEFORMAT;

#define MSAUDIO1_BITS_PER_SAMPLE    WMAUDIO_BITS_PER_SAMPLE
#define MSAUDIO1_MAX_CHANNELS       WMAUDIO_MAX_CHANNELS
#define MSAUDIO1_WFX_EXTRA_BYTES    (sizeof(MSAUDIO1WAVEFORMAT) - sizeof(WAVEFORMATEX))


// ======================================================================
// Windows Media Audio V2

#define WAVE_FORMAT_WMAUDIO2  0x0161
#define MM_MSFT_ACM_WMAUDIO2  101

typedef struct wmaudio2waveformat_tag {
    WAVEFORMATEX wfx;
    DWORD        dwSamplesPerBlock; // only counting "new" samples "= half of what will be used due to overlapping
    WORD         wEncodeOptions;
    DWORD        dwSuperBlockAlign; // the big size...  should be multiples of wfx.nBlockAlign.
} WMAUDIO2WAVEFORMAT;

typedef WMAUDIO2WAVEFORMAT FAR  *LPWMAUDIO2WAVEFORMAT;

#define WMAUDIO2_BITS_PER_SAMPLE    WMAUDIO_BITS_PER_SAMPLE
#define WMAUDIO2_MAX_CHANNELS       WMAUDIO_MAX_CHANNELS
#define WMAUDIO2_WFX_EXTRA_BYTES    (sizeof(WMAUDIO2WAVEFORMAT) - sizeof(WAVEFORMATEX))

// ======================================================================
// Windows Media Audio V3

#ifndef _WAVEFORMATEXTENSIBLE_
// WAVEFORMATEXTENSIBLE is defined in mmreg.h, but only the latest versions of mmreg.h
// contain this definition. For example, VC6.0 SP3's default system includes don't
// have this definition in mmreg.h. To fix this, be sure VC's default system includes are
// overridden by the SDK_INC_PATH directory used by the command-line build. This is
// required for consistency, anyway.
#error *** Must define WAVEFORMATEXTENSIBLE from mmreg.h! See comments in file.
#endif // !_WAVEFORMATEXTENSIBLE_

#if !defined (WAVE_FORMAT_WMAUDIO_LOSSLESS)
#define WAVE_FORMAT_WMAUDIO_LOSSLESS  0x0163
#endif

#if !defined (WAVE_FORMAT_WMAUDIO3)
#define WAVE_FORMAT_WMAUDIO3  0x0162

typedef struct wmaudio3waveformat_tag {
  WAVEFORMATEX wfx;
  WORD         wValidBitsPerSample; // bits of precision 
  DWORD        dwChannelMask;       // which channels are present in stream 
  DWORD        dwReserved1;
  DWORD        dwReserved2;
  WORD         wEncodeOptions;
  WORD         wReserved3;
} WMAUDIO3WAVEFORMAT;

typedef WMAUDIO3WAVEFORMAT FAR *LPWMAUDIO3WAVEFORMAT;
#define WMAUDIO3_WFX_EXTRA_BYTES    (sizeof(WMAUDIO3WAVEFORMAT) - sizeof(WAVEFORMATEX))
#endif // WAVE_FORMAT_WMAUDIO3

// ======================================================================
// Windows Media Audio V3X

#if !defined (WAVE_FORMAT_WMAUDIO3X)
#define WAVE_FORMAT_WMAUDIO3X  0x0162

typedef struct wmaudio3Xwaveformat_tag {
  WAVEFORMATEXTENSIBLE wfx;
  DWORD        dwReserved1; // was dwSamplesPerBlock; 
  DWORD        dwReserved2; // was dwSuperBlockAlign; 
  WORD         wEncodeOptions;
  WORD         wOriginalBitDepth;
} WMAUDIO3XWAVEFORMAT;

typedef WMAUDIO3XWAVEFORMAT FAR *LPWMAUDIO3XWAVEFORMAT;
#define WMAUDIO3X_WFX_EXTRA_BYTES    (sizeof(WMAUDIO3XWAVEFORMAT) - sizeof(WAVEFORMATEX))
#endif // WAVE_FORMAT_WMAUDIO3X

// WMA Pro over SPDIF: Just use WAVEFORMATEX
#if !defined (WAVE_FORMAT_WMASPDIF)
#define WAVE_FORMAT_WMASPDIF 0x164
#endif

// ======================================================================
// Windows Media Audio Voice

#if !defined (WAVE_FORMAT_WMAUDIOVOICE9)
#define WAVE_FORMAT_WMAVOICE9   0x000A

#endif  // !WAVE_FORMAT_WMAUDIOVOICE9


#ifndef RC_INVOKED              // from mmreg.h
#pragma pack()                  // Revert to default packing
#endif  // RC_INVOKED

#endif /* !_MSAUDIO_FMT_H */
