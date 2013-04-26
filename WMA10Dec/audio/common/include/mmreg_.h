//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Revision History:

*************************************************************************/

#ifndef __MMREG__H
#define __MMREG__H

#ifndef __arm
#ifndef _XBOX
//#include <mmreg.h>
#endif
#endif

// ripped from mmreg.h

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_

#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack(push)
#pragma pack(2)
#endif

typedef struct tWAVEFORMATEX
{
    WORD    wFormatTag;        /* format type */
    WORD    nChannels;         /* number of channels (i.e. mono, stereo...) */
    DWORD   nSamplesPerSec;    /* sample rate */
    DWORD   nAvgBytesPerSec;   /* for buffer estimation */
    WORD    nBlockAlign;       /* block size of data */
    WORD    wBitsPerSample;    /* Number of bits per sample of mono data */
    WORD    cbSize;            /* The count in bytes of the size of
                                    extra information (after cbSize) */

} WAVEFORMATEX;

#if !defined(_Embedded_x86) && !defined(__arm)
#pragma pack(pop)
#endif

typedef WAVEFORMATEX       *PWAVEFORMATEX;
typedef WAVEFORMATEX NEAR *NPWAVEFORMATEX;
typedef WAVEFORMATEX FAR  *LPWAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */

#if !defined (_WAVEFORMATEXTENSIBLE_)
#include "wmawfxdefs.h"
#endif

#if !defined (UNDER_CE)

#if !defined (WAVE_FORMAT_WMAUDIO3)
// Must be older version of mmreg.h
#include "msaudiofmt.h"
#endif

#else

#undef WAVE_FORMAT_WMAVOICE9
#undef WAVE_FORMAT_WMAUDIO3

#include "msaudiofmt.h"
#endif //UNDER_CE


#endif // __MMREG__H
