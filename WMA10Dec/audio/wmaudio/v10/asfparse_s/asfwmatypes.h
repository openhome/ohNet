//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*
 * wmatypes.h:
 * Copyright (C) ARM Limited 1999. All Rights Reserved.
 */

//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       wmatypes.h
//
//--------------------------------------------------------------------------

#ifndef WMATYPES_H
#define WMATYPES_H

#ifdef UNDER_CE
#define PACKED
#else

#ifdef _MSC_VER
#define USE_PACK_HEADERS
#define PACKED
#elif defined( WMA_TARGET_MACOS )
#define USE_PACK_HEADERS
#elif defined __arm
#define PACKED __packed
#else
#define __packed
//#define PACKED  __packed
#endif

#ifdef _Embedded_x86
#define PACKED
#endif

#ifdef USE_PACK_HEADERS
#pragma warning( push )
#pragma warning( disable : 4103 )
#include <pshpack1.h>
#pragma warning( pop )
#endif
#endif

/****************************************************************************/
#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif /* __cplusplus */
#endif /* NULL */

#if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC)
#define UNALIGNED __unaligned
#elif defined(_WIN32_WCE) && !defined(_M_IX86)
// WinCE inc\winnt.h defined this
#ifndef UNALIGNED
#define UNALIGNED __unaligned
#endif
#else
#ifndef UNALIGNED
#define UNALIGNED
#endif
#endif

#ifdef _Embedded_x86
#define FALSE 0
#define TRUE  1
#endif


/****************************************************************************/
#ifndef _BOOL_DEFINED
#define _BOOL_DEFINED
typedef long BOOL;
#endif /* _BOOL_DEFINED */

#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef unsigned char   BYTE;
#endif /* _BYTE_DEFINED */

#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef unsigned short  WORD;
#endif /* _WORD_DEFINED */

#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef unsigned long    DWORD; /* actually long, but this should be okay */
#endif /* _DWORD_DEFINED */

#if defined (_Embedded_x86) || defined (_MIPS_) || defined (UNDER_CE)
#pragma pack (1)
#endif

#ifndef _QWORD_DEFINED
#define _QWORD_DEFINED
typedef PACKED struct tQWORD
{
    DWORD   dwLo;
    DWORD   dwHi;

}   QWORD;
#endif /* _QWORD_DEFINED */


/****************************************************************************/
#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef PACKED struct tGUID
{
    DWORD   Data1;
    WORD    Data2;
    WORD    Data3;
    BYTE    Data4[ 8 ];

}   GUID;
#endif

/****************************************************************************/
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef PACKED struct tWAVEFORMATEX
{
    WORD    wFormatTag;         /* format type */
    WORD    nChannels;          /* number of channels (i.e. mono, stereo...) */
    DWORD   nSamplesPerSec;     /* sample rate */
    DWORD   nAvgBytesPerSec;    /* for buffer estimation */
    WORD    nBlockAlign;        /* block size of data */
    WORD    wBitsPerSample;     /* number of bits per sample of mono data */
    WORD    cbSize;             /* the count in bytes of the size of */

}   WAVEFORMATEX;
typedef const WAVEFORMATEX *LPCWAVEFORMATEX;

#endif // _WAVEFORMATEX_

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
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

#endif /* _WAVEFORMATEXTENSIBLE_ */

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
#endif /* WAVE_FORMAT_PCM */

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

// get definitions for  MSAUDIO1WAVEFORMAT etc from official place.
#include "mmreg_.h"

/****************************************************************************/
typedef PACKED struct tAsfXAcmAudioErrorMaskingData
{
    BYTE    span;
    WORD    virtualPacketLen;
    WORD    virtualChunkLen;
    WORD    silenceLen;
    BYTE    silence[1];

}   AsfXAcmAudioErrorMaskingData;


/****************************************************************************/
typedef PACKED struct tAsfXSignatureAudioErrorMaskingData
{
    DWORD maxObjectSize;
    WORD  chunkLen;
    WORD  signatureLen;
    BYTE  signature[1];

}   AsfXSignatureAudioErrorMaskingData;

#if defined (_Embedded_x86) || defined (_MIPS_)  || defined (UNDER_CE)
#pragma pack ()
#endif

/****************************************************************************/
typedef struct tPACKET_PARSE_INFO_EX
{
    BOOL fParityPacket;
    DWORD cbParseOffset;

    BOOL fEccPresent;
    BYTE bECLen;

    BYTE bPacketLenType;
    DWORD cbPacketLenTypeOffset;

    BYTE bPadLenType;
    BYTE bSequenceLenType;

    BOOL fMultiPayloads;

    BYTE bOffsetBytes;

    BYTE bOffsetLenType;

    DWORD cbPacketLenOffset;

    DWORD cbExplicitPacketLength; 

    DWORD cbSequenceOffset;
    
    DWORD dwSequenceNum; 

    DWORD cbPadLenOffset;
    DWORD cbPadding;

    DWORD dwSCR;
    WORD wDuration;

    BYTE bPayLenType;
    BYTE bPayBytes;
    DWORD cbPayLenTypeOffset;

    DWORD cPayloads;

}   PACKET_PARSE_INFO_EX;


/****************************************************************************/
typedef struct tPAYLOAD_MAP_ENTRY_EX
{
    WORD cbPacketOffset;
    WORD cbTotalSize;

    BYTE bStreamId;
    BYTE bObjectId;

    DWORD cbObjectOffset;
    DWORD cbObjectSize;
    DWORD msObjectPres;

    BYTE cbRepData;
    BYTE bJunk;
    WORD cbPayloadSize;
 // Added by Amit
    
//    BYTE bIsKeyFrame;
//    BYTE bFrameRate;
    WORD wBytesRead;
    WORD wTotalDataBytes;
    BYTE bSubPayloadState;
    BYTE bIsCompressedPayload;
    BYTE bNextSubPayloadSize;
    WORD wSubpayloadLeft;
    DWORD dwDeltaTime;
    WORD  wSubCount;    

}   PAYLOAD_MAP_ENTRY_EX;


#ifdef USE_PACK_HEADERS
#pragma warning( push )
#pragma warning( disable : 4103 )
#include <poppack.h>
#pragma warning( pop )
#endif

#endif  /* WMATYPES_H */
