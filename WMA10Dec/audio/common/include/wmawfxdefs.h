//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef _WMAWFXDEFS_H_
#define _WMAWFXDEFS_H_

#include "wmatyps.h"

#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct {          // size is 16
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

#endif // !GUID_DEFINED

#ifndef COMPILER_PACKALIGN
#ifndef PLATFORM_SPECIFIC_COMPILER_PACKALIGN
#define COMPILER_PACKALIGN(x)       pack(x)
#endif
#endif

#ifndef COMPILER_PACKALIGN_DEFAULT
#ifndef PLATFORM_SPECIFIC_COMPILER_PACKALIGN_DEFAULT
#define COMPILER_PACKALIGN_DEFAULT  pack()
#endif
#endif

#ifdef __arm
#define EMBARM_PACK __packed
#else
#define EMBARM_PACK
#endif

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_

#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack(1)
//#pragma COMPILER_PACKALIGN(1)
#endif

#if !defined (WINMMAPI)
EMBARM_PACK typedef struct 
{
    WMA_U16     wFormatTag;        /* format type */
    WMA_U16     nChannels;         /* number of channels (i.e. mono, stereo...) */
    WMA_U32     nSamplesPerSec;    /* sample rate */
    WMA_U32     nAvgBytesPerSec;   /* for buffer estimation */
    WMA_U16     nBlockAlign;       /* block size of data */
    WMA_U16     wBitsPerSample;    /* Number of bits per sample of mono data */
    WMA_U16     cbSize;            /* The count in bytes of the size of
                                * extra information (after cbSize) */
                               
} WAVEFORMATEX, *PWAVEFORMATEX, *LPWAVEFORMATEX;

typedef const WAVEFORMATEX *LPCWAVEFORMATEX;

#endif // WINMMAPI
#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack()
//#pragma COMPILER_PACKALIGN_DEFAULT
#endif
#endif /* _WAVEFORMATEX_ */

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack(1)
//#pragma COMPILER_PACKALIGN(1)
#endif
typedef struct
{
    WAVEFORMATEX Format;       /* The traditional wave file header */
    union {
        unsigned short wValidBitsPerSample; /* bits of precision */
        unsigned short wSamplesPerBlock;    /* valid if wBitsPerSample==0 */
        unsigned short wReserved;           /* If neither applies, set to zero */
    } Samples;
    unsigned long    dwChannelMask;        /* which channels are present in stream */
    GUID SubFormat;           /* specialization */
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack()
//#pragma COMPILER_PACKALIGN_DEFAULT
#endif
#endif /* _WAVEFORMATEXTENSIBLE_ */

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
#endif /* WAVE_FORMAT_PCM */

#ifndef WAVE_FORMAT_IEEE_FLOAT
#define  WAVE_FORMAT_IEEE_FLOAT 0x0003
#endif /* WAVE_FORMAT_IEEE_FLOAT */

#ifndef WAVE_FORMAT_EXTENSIBLE
#define WAVE_FORMAT_EXTENSIBLE 65534
#endif /* WAVE_FORMAT_EXTENSIBLE */

#ifndef _SPEAKER_POSITIONS_
#define _SPEAKER_POSITIONS_
/* Speaker Positions for dwChannelMask in WAVEFORMATEXTENSIBLE: from ksmedia.h */
#define SPEAKER_FRONT_LEFT              0x1
#define SPEAKER_FRONT_RIGHT             0x2
#define SPEAKER_FRONT_CENTER            0x4
#define SPEAKER_LOW_FREQUENCY           0x8
#define SPEAKER_BACK_LEFT               0x10
#define SPEAKER_BACK_RIGHT              0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER    0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER   0x80
#define SPEAKER_BACK_CENTER             0x100
#define SPEAKER_SIDE_LEFT               0x200
#define SPEAKER_SIDE_RIGHT              0x400
#define SPEAKER_TOP_CENTER              0x800
#define SPEAKER_TOP_FRONT_LEFT          0x1000
#define SPEAKER_TOP_FRONT_CENTER        0x2000
#define SPEAKER_TOP_FRONT_RIGHT         0x4000
#define SPEAKER_TOP_BACK_LEFT           0x8000
#define SPEAKER_TOP_BACK_CENTER         0x10000
#define SPEAKER_TOP_BACK_RIGHT          0x20000
#endif /* _SPEAKER_POSITIONS_ */

#define IS_KSDATAFORMAT_SUBTYPE_PCM(guid)\
    (((guid)->Data1       == 0x01) &&\
     ((guid)->Data2       == 0x00) &&\
     ((guid)->Data3       == 0x10) &&\
     ((guid)->Data4[0] == 0x80) &&\
     ((guid)->Data4[1] == 0x00) &&\
     ((guid)->Data4[2] == 0x00) &&\
     ((guid)->Data4[3] == 0xaa) &&\
     ((guid)->Data4[4] == 0x00) &&\
     ((guid)->Data4[5] == 0x38) &&\
     ((guid)->Data4[6] == 0x9b) &&\
     ((guid)->Data4[7] == 0x71))

#define COPY_KSDATAFORMAT_SUBTYPE_PCM(guid)\
     (guid)->Data1       = 0x01;\
     (guid)->Data2       = 0x00;\
     (guid)->Data3       = 0x10;\
     (guid)->Data4[0] = 0x80;\
     (guid)->Data4[1] = 0x00;\
     (guid)->Data4[2] = 0x00;\
     (guid)->Data4[3] = 0xaa;\
     (guid)->Data4[4] = 0x00;\
     (guid)->Data4[5] = 0x38;\
     (guid)->Data4[6] = 0x9b;\
     (guid)->Data4[7] = 0x71;

#define IS_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(guid)\
    (((guid)->Data1       == 0x03) &&\
     ((guid)->Data2       == 0x00) &&\
     ((guid)->Data3       == 0x10) &&\
     ((guid)->Data4[0] == 0x80) &&\
     ((guid)->Data4[1] == 0x00) &&\
     ((guid)->Data4[2] == 0x00) &&\
     ((guid)->Data4[3] == 0xaa) &&\
     ((guid)->Data4[4] == 0x00) &&\
     ((guid)->Data4[5] == 0x38) &&\
     ((guid)->Data4[6] == 0x9b) &&\
     ((guid)->Data4[7] == 0x71))

#define COPY_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(guid)\
     (guid)->Data1       = 0x03;\
     (guid)->Data2       = 0x00;\
     (guid)->Data3       = 0x10;\
     (guid)->Data4[0] = 0x80;\
     (guid)->Data4[1] = 0x00;\
     (guid)->Data4[2] = 0x00;\
     (guid)->Data4[3] = 0xaa;\
     (guid)->Data4[4] = 0x00;\
     (guid)->Data4[5] = 0x38;\
     (guid)->Data4[6] = 0x9b;\
     (guid)->Data4[7] = 0x71;

#define IS_WFXDATAFORMAT_PCM(wfxe) \
    (wfxe.Format.wFormatTag == WAVE_FORMAT_PCM || \
     (wfxe.Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE && \
      IS_KSDATAFORMAT_SUBTYPE_PCM(&wfxe.SubFormat)))

#define IS_WFXDATAFORMAT_IEEEFLOAT(wfxe) \
    (wfxe.Format.wFormatTag == WAVE_FORMAT_IEEE_FLOAT || \
     (wfxe.Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE && \
      IS_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(&wfxe.SubFormat)))

#define COPY_WFXDATAFORMAT_PCM(wfxe, ex) { \
    if (ex) { \
        wfxe.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE; \
        COPY_KSDATAFORMAT_SUBTYPE_PCM(&wfxe.SubFormat); \
    } else { \
        wfxe.Format.wFormatTag = WAVE_FORMAT_PCM; \
    } \
}

#define COPY_WFXDATAFORMAT_IEEEFLOAT(wfxe, ex) { \
    if (ex) { \
        wfxe.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE; \
        COPY_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(&wfxe.SubFormat); \
    } else { \
        wfxe.Format.wFormatTag = WAVE_FORMAT_IEEE_FLOAT; \
    } \
}

#if !defined (DSSPEAKER_5POINT1)
#define DSSPEAKER_5POINT1           0x00000006
#endif

#if !defined (DSSPEAKER_7POINT1)
#define DSSPEAKER_7POINT1           0x00000007
#endif


#endif /* _WMAWFXDEFS_H_ */

