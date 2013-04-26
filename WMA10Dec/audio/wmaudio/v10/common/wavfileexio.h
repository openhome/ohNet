//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/* -------------------------------------------------------------------------
 *
 *  Microsoft Windows Media
 *
 *  Copyright (C) Microsoft Corporation, 1999 - 2000
 *
 *  File:       wavfileexio.h
 *              This is a variation of wavfileio that works with 
 *              WAVEFORMATEXTENSIBLE, rather than with WAVEFORMATEX. 
 *              Deals with both WAVE_FORMAT_PCM and WAVE_FORMAT_EXTENSIBLE 
 *              format types.
 *              It is aware of multi-channel, and > 16 bits/sample.
 *              Updates from wavfileio.h were made by Thumpudi Naveen
 *              1/31/2000.
 *              
 * ---------------------------------------------------------------------- */

#ifndef _WAV_FILE_EX_IO_H_
#define _WAV_FILE_EX_IO_H_
#if !defined(WMA_TARGET_MACOS) && !defined(__arm) && !defined(OPENHOME)
#    include <tchar.h>
#endif

#include "wmspecstring.h"

#ifdef __arm
#include "wmatypes_arm.h"
#endif

/* use this to turn off the use of mmio* calls */
#define WFIO_NO_WIN32 1

/* use this to control the endian-ness */
#ifdef BIG_ENDIAN
#define WFIO_LITTLE_ENDIAN 0
#else
#define WFIO_LITTLE_ENDIAN 1
#endif

#if WFIO_NO_WIN32

#include <stdio.h>
#include "wmatyps.h"
#include "wmawfxdefs.h"

#ifndef MMSYSERR_NOERROR
#define MMSYSERR_NOERROR     0
#endif
#ifndef MMSYSERR_ERROR       
#define MMSYSERR_ERROR       1
#endif
#ifndef MMSYSERR_NOMEM
#define MMSYSERR_NOMEM       7
#endif
#ifndef MMSYSERR_READERROR
#define MMSYSERR_READERROR   16
#endif
#ifndef MMSYSERR_WRITEERROR 
#define MMSYSERR_WRITEERROR  17
#endif

#else  /* WFIO_NO_WIN32 */

#include <windows.h>
#include <mmsystem.h>
#include "mmreg_.h"
#include <ks.h>
#include <ksmedia.h>
#include "macros.h"

#endif /* WFIO_NO_WIN32 */

// ===========================================================

  /* flag for WavFileIO */
  enum
  {
    wfioModeRead = 0,
    wfioModeWrite
  };
  
  /* ===========================================================================
   * WavFileIO struct
   */
  typedef struct WavFileIO_tag
  {
    WMA_I32      m_mode;
    
#if WFIO_NO_WIN32
    FILE    *m_fpWav;
    
    size_t   m_posRiffLength;
    size_t   m_posDataLength;
#else  /* WFIO_NO_WIN32 */
    HMMIO    m_hmmio;
    MMIOINFO m_mmioinfo;
    
    MMCKINFO m_ckWave;
    MMCKINFO m_ck;
#endif /* WFIO_NO_WIN32 */
    
    __field_bcount_opt(m_sizeFormat) WAVEFORMATEXTENSIBLE *m_pFormat;      /* but allocated using BYTEs...  */
    WMA_U32   m_sizeFormat;
    
    WMA_U32   m_sizeData;
    WMA_U32   m_posDataStart;

    WMA_I32 m_cbPos;
    
  } WavFileIO;
  
  
  /* ---------------------------------------------------------------------------
   * member functions
   */
  
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
  
  WavFileIO * wfioNew();
  void wfioDelete(WavFileIO *pwfio);
  
  /* pFormat and cbFormat are only for writing.
   * Upgrades the format to WAVE_FORMAT_EXTENSIBLE, if sources with
   * > 2 channels or samples with > 16 bits are to be saved. In such an upgrade
   * process, it "guesses" speaker positions.
   */
  WMA_I32 wfioOpen(WavFileIO *pwfio, const TCHAR *szFile, WAVEFORMATEXTENSIBLE *pFormat, WMA_U32 cbFormat, WMA_I32 mode);
  WMA_I32 prvwfioReWriteHeaders(WavFileIO *pwfio, WAVEFORMATEXTENSIBLE *pFormat, WMA_U32 cbFormat);
  void wfioClose(WavFileIO *pwfio);
  
  /* origin can be SEEK_SET, SEEK_CUR, or SEEK_END */
  WMA_I32 wfioSeek(WavFileIO *pwfio, WMA_I32 position, WMA_I32 origin);
  WMA_I32 wfioSeekNoBoundary(WavFileIO *pwfio, WMA_I32 position);
  /* prvwfioSeekRaw seeks from the beginning of the file instead of the data.*/
  WMA_I32 prvwfioSeekRaw(WavFileIO *pwfio, WMA_I32 position, WMA_I32 origin);
    
  WMA_I32 wfioRead(WavFileIO *pwfio, WMA_U8 *pBuf, WMA_I32 cbBuf);
  WMA_I32 wfioReadNoBoundary(WavFileIO *pwfio, WMA_U8 *pBuf, WMA_I32 cbBuf);
  WMA_I32 wfioWrite(WavFileIO *pwfio, WMA_U8 *pBuf, WMA_I32 cbBuf);
  
  WAVEFORMATEXTENSIBLE * wfioGetFormat(WavFileIO *pwfio);
  WMA_U32 wfioGetFormatLength(WavFileIO *pwfio);
  
  WMA_U32 wfioGetSampleSize(WavFileIO *pwfio);
  WMA_U32 wfioGetDataLength(WavFileIO *pwfio);
  
  WMA_I32 wfioGetMode(WavFileIO *pwfio);
  WMA_I32 wfioIsOpened(WavFileIO *pwfio);
  
  /* utility functions */
  WMA_U16 adjustByteOrder16(WMA_U16 val);
  WMA_U32 adjustByteOrder32(WMA_U32 val);
  
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _WAV_FILE_EX_IO_H_ */
