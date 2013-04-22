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
 *  Copyright (C) Microsoft Corporation, 1999 - 1999
 *
 *  File:       wavfileexio.c
 *              This is a variation of wavfileio that works with 
 *              WAVEFORMATEXTENSIBLE, rather than with WAVEFORMATEX. 
 *              Deals with both WAVE_FORMAT_PCM and WAVE_FORMAT_EXTENSIBLE 
 *              format types.
 *              It is aware of multi-channel, and > 16 bits/sample.
 *              Updates from wavfileio.h were made by Thumpudi Naveen
 *              1/31/2000.
 *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
// Mac OS X defines memset() and memcpy() in string.h rather than memory.h.
#if defined(macintosh)
#   include <string.h>
#endif

#if defined(_XBOX)
//#include <ntos.h>
#define NOD3D
#define NONET
#include <xtl.h>
#undef  NOD3D
#undef  NONET
#elif !defined(__arm) && !defined(macintosh)
#include <memory.h>
#include <windows.h>
#endif

#include "macros.h"     // must be included before wavfileexio.h for BIG_ENDIAN

#include "wavfileexio.h"
#include "wmatypes.h"
#include "mmreg_.h"

#ifdef __arm
#define _tfopen fopen
#define TEXT
#endif //__arm

#if defined(UNDER_CE) && defined(WIN32_PLATFORM_PSPC)
	// Palm-size PC 2.11 needs this, H/PC Pro 2.11 does not
#   pragma warning( disable : 4273 )
	FILE * __cdecl fopen( const char *filename, const char *mode );
	int __cdecl fseek( FILE *stream, long offset, int origin );
	size_t __cdecl fread( void *buffer, size_t size, size_t count, FILE *stream );
	size_t __cdecl fwrite( const void *buffer, size_t size, size_t count, FILE *stream );
	int __cdecl fclose( FILE *stream );
	int __cdecl ferror( FILE *stream );
	int __cdecl fflush( FILE *stream );
#endif // UNDER_CE

#ifndef mmioFOURCC
#  if WFIO_LITTLE_ENDIAN
#    define mmioFOURCC(ch0, ch1, ch2, ch3)  ((U32)(U8)(ch0)|((U32)(U8)(ch1)<<8)|((U32)(U8)(ch2)<<16)|((U32)(U8)(ch3)<<24))
#  else  /* WFIO_LITTLE_ENDIAN */
#    define mmioFOURCC(ch0, ch1, ch2, ch3)  ((U32)(U8)(ch3)|((U32)(U8)(ch2)<<8)|((U32)(U8)(ch1)<<16)|((U32)(U8)(ch0)<<24))
#  endif /* WFIO_LITTLE_ENDIAN */
#endif /* mmioFOURCC */

#define WFIO_FOURCC_RIFF    mmioFOURCC('R', 'I', 'F', 'F')
#define WFIO_FOURCC_WAVE    mmioFOURCC('W', 'A', 'V', 'E')
#define WFIO_FOURCC_fmt     mmioFOURCC('f', 'm', 't', ' ')
#define WFIO_FOURCC_data    mmioFOURCC('d', 'a', 't', 'a')
#define WFIO_FOURCC_fact    mmioFOURCC('f', 'a', 'c', 't')

/* forward declarations */
I32 wfioReWriteHeaders(WavFileIO *pwfio, WAVEFORMATEXTENSIBLE *pFormat, U32 cbFormat);
static I32 wfioReadHeaders(WavFileIO *pwfio);
static I32 wfioWriteHeaders(WavFileIO *pwfio, WAVEFORMATEXTENSIBLE *pFormat, U32 cbFormat);
static I32 wfioCleanUpRead(WavFileIO *pwfio);
static I32 wfioCleanUpWrite(WavFileIO *pwfio);


/* utility functions */

U16
adjustByteOrder16(U16 val)
{
#if WFIO_LITTLE_ENDIAN
  return val;
#else  /* WFIO_LITTLE_ENDIAN */
  U8 *p = (U8 *)&val;
  return ((U16)p[0])|((U16)p[1]<<8);
#endif /* WFIO_LITTLE_ENDIAN */
}

U32
adjustByteOrder32(U32 val)
{
#if WFIO_LITTLE_ENDIAN
  return val;
#else  /* WFIO_LITTLE_ENDIAN */
  U8 *p = (U8 *)&val;
  return ((U32)p[0])|((U32)p[1]<<8)|((U32)p[2]<<16)|((U32)p[3]<<24);
#endif /* WFIO_LITTLE_ENDIAN */
}


WavFileIO *
wfioNew()
{
  WavFileIO *pwfio = (WavFileIO *)malloc(sizeof(WavFileIO));
  if(pwfio == NULL)
    return NULL;
  
  pwfio->m_mode = wfioModeRead;
#if WFIO_NO_WIN32
  pwfio->m_fpWav = NULL;
  pwfio->m_posRiffLength = 0;
  pwfio->m_posDataLength = 0;
#else   /* WFIO_NO_WIN32 */
  pwfio->m_hmmio = NULL;
#endif  /* WFIO_NO_WIN32 */
  pwfio->m_pFormat = NULL;
  pwfio->m_sizeFormat = 0;
  pwfio->m_sizeData = 0;
  pwfio->m_posDataStart = 0;
  
#if !WFIO_NO_WIN32
  memset(&pwfio->m_mmioinfo, 0, sizeof(pwfio->m_mmioinfo));
  memset(&pwfio->m_ckWave, 0, sizeof(pwfio->m_ckWave));
  memset(&pwfio->m_ck, 0, sizeof(pwfio->m_ck));
#endif  /* WFIO_NO_WIN32 */
  
  return pwfio;
}


void
wfioDelete(WavFileIO *pwfio)
{
  wfioClose(pwfio);
  free(pwfio);
}


/* pFormat and cbFormat are only for writing.
 * Upgrades the format to WAVE_FORMAT_EXTENSIBLE, if sources with
 * > 2 channels or samples with > 16 bits are to be saved. In such an upgrade
 * process, it "guesses" speaker positions.
 */

I32
wfioOpen(WavFileIO *pwfio,
         const TCHAR *szFile,
         WAVEFORMATEXTENSIBLE *pFormat,
         U32 cbFormat,
         I32 mode)
{
  I32 lr;
  
  if(pwfio == NULL)
    return MMSYSERR_ERROR;
  
#if WFIO_NO_WIN32
  
  if(pwfio->m_fpWav)
    return MMSYSERR_ERROR;
  
  pwfio->m_mode = mode;
  
  if(pwfio->m_mode == wfioModeWrite)
    {
      /* open the file for writing */
      pwfio->m_fpWav = _tfopen(szFile, TEXT("wb"));
      if(pwfio->m_fpWav == NULL)
        {
          lr = MMSYSERR_ERROR;
          goto lerror;
        }
      
      /* write the header info */
      lr = wfioWriteHeaders(pwfio, pFormat, cbFormat);
      if(lr != MMSYSERR_NOERROR)
        goto lerror;
    }
  else
    {
      /* open the file for reading */
      pwfio->m_fpWav = _tfopen(szFile, TEXT("rb"));
      if(pwfio->m_fpWav == NULL)
        {
          lr = MMSYSERR_ERROR;
          goto lerror;
        }
      
      /* read the hearder info */
      lr = wfioReadHeaders(pwfio);
      if(lr != MMSYSERR_NOERROR)
        goto lerror;
      
      /* seek to the beginning */
      wfioSeek(pwfio, 0, SEEK_CUR);
    }
  
#else  /* WFIO_NO_WIN32 */
  
  if(pwfio->m_hmmio)
    return MMSYSERR_ERROR;
  
  pwfio->m_mode = mode;
  
  /* slightly different for READ and WRITE */
  if(pwfio->m_mode == wfioModeRead)
    {
      /* open the file for read */
      pwfio->m_hmmio = mmioOpen((LPSTR)szFile, NULL, MMIO_READ/*|MMIO_DENYWRITE*/);
      if(pwfio->m_hmmio == NULL)
        {
          lr = MMSYSERR_ERROR;
          goto lerror;
        }
      
      /* read the header info */
      lr = wfioReadHeaders(pwfio);
      if(lr != MMSYSERR_NOERROR)
        goto lerror;
      
      /* seek to the beginning */
      wfioSeek(pwfio, 0, SEEK_CUR);
    }
  else
    {
      /* open the file for write */
      pwfio->m_hmmio = mmioOpen((LPSTR)szFile, NULL, MMIO_READWRITE|MMIO_CREATE|MMIO_ALLOCBUF/*|MMIO_DENYWRITE*/);
      if(pwfio->m_hmmio == NULL)
        {
          lr = MMSYSERR_ERROR;
          goto lerror;
        }
      
      lr = wfioWriteHeaders(pwfio, pFormat, cbFormat);
      if(lr != MMSYSERR_NOERROR)
        goto lerror;
    }
  
#endif /* WFIO_NO_WIN32 */

  if (NULL != pFormat && wfioModeRead == pwfio->m_mode)
  {
      memcpy(pFormat, pwfio->m_pFormat,
             sizeof(WAVEFORMATEX)+pwfio->m_pFormat->Format.cbSize);
  }
  
  return MMSYSERR_NOERROR;
  
 lerror:
  wfioClose(pwfio);
  return lr;
}


void
wfioClose(WavFileIO *pwfio)
{
  if(pwfio == NULL)
    return;
  
#if WFIO_NO_WIN32
  
  if(pwfio->m_fpWav)
    {
      if(pwfio->m_mode == wfioModeWrite)
        wfioCleanUpWrite(pwfio);
      else
        wfioCleanUpRead(pwfio);
      
      fclose(pwfio->m_fpWav);
      pwfio->m_fpWav = NULL;
    }
  
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  
  pwfio->m_sizeData = 0;
  pwfio->m_posDataStart = 0;
  
  /* just for the safety... */
  pwfio->m_posRiffLength = 0;
  pwfio->m_posDataLength = 0;
  
#else  /* WFIO_NO_WIN32 */
  
  if(pwfio->m_hmmio)
    {
      if(pwfio->m_mode == wfioModeWrite)
        wfioCleanUpWrite(pwfio);
      else
        wfioCleanUpRead(pwfio);
      
      mmioClose(pwfio->m_hmmio, 0);
      pwfio->m_hmmio = NULL;
    }
  
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  
  pwfio->m_sizeData = 0;
  pwfio->m_posDataStart = 0;
  
  /* just for safety... */
  memset(&pwfio->m_mmioinfo, 0, sizeof(pwfio->m_mmioinfo));
  memset(&pwfio->m_ckWave, 0, sizeof(pwfio->m_ckWave));
  memset(&pwfio->m_ck, 0, sizeof(pwfio->m_ck));
  
#endif /* WFIO_NO_WIN32 */
}

/*
    This is a private function for encapp. Do not call it from anywhere else!
*/
I32 prvwfioSeekRaw(WavFileIO *pwfio,
                I32 position,
                I32 origin)
{
  if(pwfio == NULL)
    return -1;
/*  
  // only for reading...
  if(pwfio->m_mode != wfioModeRead)
    return -1;
*/  
#if WFIO_NO_WIN32
  
  switch(origin)
    {
    case SEEK_SET:
      return fseek(pwfio->m_fpWav, position, SEEK_SET);
      
    case SEEK_CUR:
      return fseek(pwfio->m_fpWav, position, SEEK_CUR);
      
    case SEEK_END:
      return fseek(pwfio->m_fpWav, pwfio->m_posDataStart + pwfio->m_sizeData + position, SEEK_SET);
    }
  
#else  /* WFIO_NO_WIN32 */
  
  switch(origin)
    {
    case SEEK_SET:
      return mmioSeek(pwfio->m_hmmio, position, SEEK_SET);
      
    case SEEK_CUR:
      return mmioSeek(pwfio->m_hmmio, position, SEEK_CUR);
      
    case SEEK_END:
      return mmioSeek(pwfio->m_hmmio, pwfio->m_posDataStart + pwfio->m_sizeData + position, SEEK_SET);
    }
  
#endif /* WFIO_NO_WIN32 */
  
  return -1;
}

I32
wfioSeek(WavFileIO *pwfio,
         I32 position,
         I32 origin)
{
  if(pwfio == NULL)
    return -1;
  
  /* only for reading... */
  if(pwfio->m_mode != wfioModeRead)
    return -1;
  
#if WFIO_NO_WIN32
  
  switch(origin)
    {
    case SEEK_SET:
      return fseek(pwfio->m_fpWav, pwfio->m_posDataStart + position, SEEK_SET);
      
    case SEEK_CUR:
      return fseek(pwfio->m_fpWav, position, SEEK_CUR);
      
    case SEEK_END:
      return fseek(pwfio->m_fpWav, pwfio->m_posDataStart + pwfio->m_sizeData + position, SEEK_SET);
    }
  
#else  /* WFIO_NO_WIN32 */
  
  switch(origin)
    {
    case SEEK_SET:
      return mmioSeek(pwfio->m_hmmio, pwfio->m_posDataStart + position, SEEK_SET);
      
    case SEEK_CUR:
      return mmioSeek(pwfio->m_hmmio, position, SEEK_CUR);
      
    case SEEK_END:
      return mmioSeek(pwfio->m_hmmio, pwfio->m_posDataStart + pwfio->m_sizeData + position, SEEK_SET);
    }
  
#endif /* WFIO_NO_WIN32 */
  
  return -1;
}

I32
wfioSeekNoBoundary(WavFileIO *pwfio, I32 position)
{
    pwfio->m_cbPos = position;
    return wfioSeek(pwfio, max(position, 0), SEEK_CUR);
}

I32
wfioRead(WavFileIO *pwfio,
         U8 *pBuf,
         I32 cbBuf)
{
#if WFIO_NO_WIN32
  
  size_t ret;
  size_t iCurrPos = 0;
  
  if(pwfio == NULL)
    return (I32)-1;
  
  if(pwfio->m_fpWav == NULL
     || pwfio->m_mode != wfioModeRead
     || pBuf == NULL)
    return (I32)-1;

  if ((iCurrPos = ftell(pwfio->m_fpWav)) >= pwfio->m_posDataStart)
  {
      if ((I32) pwfio->m_sizeData + (I32) pwfio->m_posDataStart - (I32) iCurrPos < cbBuf)
        cbBuf = pwfio->m_sizeData + pwfio->m_posDataStart - iCurrPos;
  }
  else
    return (I32)-1;
  
  /* in alignment units... */
  cbBuf = (cbBuf/pwfio->m_pFormat->Format.nBlockAlign)*pwfio->m_pFormat->Format.nBlockAlign;
  
  ret = fread(pBuf, 1, cbBuf, pwfio->m_fpWav);
  if(ferror(pwfio->m_fpWav))
    return (I32)-1;

#if !WFIO_LITTLE_ENDIAN
  
  /* have to swap bytes, but only for PCM format (not compressed wav) */
  if(( WAVE_FORMAT_PCM == pwfio->m_pFormat->Format.wFormatTag ) ||
    IS_KSDATAFORMAT_SUBTYPE_PCM(&(pwfio->m_pFormat->SubFormat) ))
  {
    switch (pwfio->m_pFormat->Format.wBitsPerSample)
    {
    case 16:
	    {
            I32 i;
		    U16 *p = (U16 *)pBuf;
		    for(i = cbBuf/2; i > 0; i--, p++)
			    *p = adjustByteOrder16(*p);
	    }
	    break;
    	  
    case 20:
	    break;
    	  
    case 24:
	    {
            I32 i;
		    U8 *p = pBuf;
		    U8 q;
		    for (i = cbBuf/3; i > 0; i--, p+=3)
		    {
			    q = *p;
			    *p = *(p+2);
			    *(p+2) = q;
		    }
	    }
	    break;

    case 32:
        {
            I32 i;
            U32 *p = (U32*)pBuf;
            for( i = cbBuf/4; i > 0; i--, ++p )
                *p = adjustByteOrder32( *p );
        }
        break;
    }
  }
  
#endif  /* WFIO_LITTLE_ENDIAN */

  return (I32)ret;
  
#else  /* WFIO_NO_WIN32 */
  
  if(pwfio == NULL)
    return (I32)-1;
  
  return mmioRead(pwfio->m_hmmio, (HPSTR)pBuf, cbBuf);
  
#endif /* WFIO_NO_WIN32 */
}

I32
wfioReadNoBoundary(WavFileIO *pwfio,
                   U8 *pBuf,
                   I32 cbBuf)
{
    I32 cbAmt, cbRead, cbTotalRead;
    Bool bRead, bFinish;

    /* in alignment units... */
    cbBuf = (cbBuf/pwfio->m_pFormat->Format.nBlockAlign)*pwfio->m_pFormat->Format.nBlockAlign;

    bFinish = FALSE;
    cbTotalRead = 0;
    while (0 != cbBuf)
    {
        if (pwfio->m_cbPos < 0)
        {
            cbAmt = min(cbBuf, -pwfio->m_cbPos);
            bRead = FALSE;
        }
        else if (pwfio->m_cbPos < (WMA_I32)pwfio->m_sizeData &&
                 FALSE == bFinish)
        {
            cbAmt = min(cbBuf, (I32)pwfio->m_sizeData-pwfio->m_cbPos);
            bRead = TRUE;
        }
        else
        {
            cbAmt = cbBuf;
            bRead = FALSE;
        }

        if (bRead)
        {
            cbRead = wfioRead(pwfio, pBuf, cbAmt);
            if (0 == cbRead)
                bFinish = TRUE;
        }
        else
        {
            cbRead = cbAmt;
            memset(pBuf, 0, cbRead);
        }
        pBuf += cbRead;
        pwfio->m_cbPos += cbRead;
        cbBuf -= cbRead;
        cbTotalRead += cbRead;
    }

    return cbTotalRead;
}

I32
wfioWrite(WavFileIO *pwfio,
          U8 *pBuf,
          I32 cbBuf )
{

#if WFIO_NO_WIN32
  
  size_t ret;
  
  if(pwfio == NULL)
    return (I32)-1;
  
  if(pwfio->m_fpWav == NULL
     || pwfio->m_mode != wfioModeWrite
     || pBuf == NULL)
    return (I32)-1;
  
  /* in alignment units... */
  cbBuf = (cbBuf/pwfio->m_pFormat->Format.nBlockAlign)*pwfio->m_pFormat->Format.nBlockAlign;

  if (cbBuf == 0) return 0;
  
#if !WFIO_LITTLE_ENDIAN
  
  // have to swap bytes... but only if
  // it is an uncompressed format.
  // this code probably needs improving.

  if(( pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_PCM ) ||
     ( pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE ))
  switch (pwfio->m_pFormat->Format.wBitsPerSample)
  {
  case 16:
	  {
          I32 i;
		  U16 *p = (U16 *)pBuf;
		  for(i = cbBuf/2; i > 0; i--, p++)
			  *p = adjustByteOrder16(*p);
	  }
	  break;
	  
  case 20:
	  break;
	  
  case 24:
	  {
          I32 i;
		  U8 *p = pBuf;
		  U8 q;
		  for (i = cbBuf/3; i > 0; i--, p+=3)
		  {
			 q = *p;
			 *p = *(p+2);
			 *(p+2) = q;
		  }
	  }
	  break;

  case 32:
      {
          I32 i;
          U32 *p = (U32*)pBuf;
          for( i = cbBuf/4; i > 0; i--, ++p )
              *p = adjustByteOrder32( *p );
      }
      break;
  }

#endif  /* WFIO_LITTLE_ENDIAN */
  
  ret = fwrite(pBuf, 1, cbBuf, pwfio->m_fpWav);
  if(ferror(pwfio->m_fpWav))
    return (I32)-1;
  
  pwfio->m_sizeData += (WMA_U32) ret;
  
  return (WMA_I32) ret;
  
#else  /* WFIO_NO_WIN32 */
  
  /* buffered write (MMIO_ALLOCBUF used for opening) */
  
  I32 lr;
  I32 cbBlock;
  I32 cbWritten = 0;
  
  if(pwfio == NULL)
    return (I32)-1;
  
  if(pBuf == NULL)
    return 0;
  
  while(cbBuf > 0)
    {
      /* check if we need to advance to the next buffer */
      if(pwfio->m_mmioinfo.pchNext == pwfio->m_mmioinfo.pchEndWrite)
        {
          pwfio->m_mmioinfo.dwFlags |= MMIO_DIRTY;
          lr = mmioAdvance(pwfio->m_hmmio, &pwfio->m_mmioinfo, MMIO_WRITE);
          if(lr != MMSYSERR_NOERROR)
            goto lerror;
        }
      
      /* copy in blocks */
      cbBlock = pwfio->m_mmioinfo.pchEndWrite - pwfio->m_mmioinfo.pchNext;
      if(cbBlock > cbBuf)
        cbBlock = cbBuf;
      CopyMemory(pwfio->m_mmioinfo.pchNext, pBuf, cbBlock);
      
      /* update pointers and counters */
      pBuf                      += cbBlock;
      pwfio->m_mmioinfo.pchNext += cbBlock;
      cbWritten                 += cbBlock;
      cbBuf                     -= cbBlock;
      
      /* update global stat members */
      pwfio->m_sizeData += cbBlock;
    }
  
 lerror:
  return cbWritten;
  
#endif /* WFIO_NO_WIN32 */
}


WAVEFORMATEXTENSIBLE *
wfioGetFormat(WavFileIO *pwfio)
{
  if(pwfio == NULL)
    return NULL;
  
  return pwfio->m_pFormat;
}


U32
wfioGetFormatLength(WavFileIO *pwfio)
{
  if(pwfio == NULL || pwfio->m_pFormat == NULL)
    return 0;
  
  return sizeof(WAVEFORMATEX) + pwfio->m_pFormat->Format.cbSize;
}


U32
wfioGetSampleSize(WavFileIO *pwfio)
{
  if(pwfio == NULL || pwfio->m_pFormat == NULL)
    return 0;
  
  return pwfio->m_pFormat->Format.nBlockAlign;
}


U32
wfioGetDataLength(WavFileIO *pwfio)
{
  if(pwfio == NULL)
    return 0;
  
  return pwfio->m_sizeData;
}


I32
wfioGetMode(WavFileIO *pwfio)
{
  if(pwfio == NULL)
    return 0;
  
  return pwfio->m_mode;
}


I32
wfioIsOpened(WavFileIO *pwfio)
{
#if WFIO_NO_WIN32
  return pwfio && pwfio->m_fpWav != NULL;
#else   /* WFIO_NO_WIN32 */
  return pwfio && pwfio->m_hmmio != NULL;
#endif  /* WFIO_NO_WIN32 */
}


I32
wfioReadHeaders(WavFileIO *pwfio)
{
    I32 lr;
    Bool fFmtChunkFound  = False;  
    Bool fDataChunkFound = False;
    
#if WFIO_NO_WIN32
    
    size_t ret;
    size_t offset = 0;
    size_t offSeek;
    
    U32 dwTemp;
    U32 dwSize;
    U32 dwHead;
    
    if(pwfio == NULL)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    if(pwfio->m_fpWav == NULL)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    /* -----------------------------------------------------------------------
    * find the RIFF/WAVE chunk
    */
    
    /* read "RIFF" */
    
    ret = fread(&dwHead, 1, sizeof(U32), pwfio->m_fpWav);
    if(ret != sizeof(U32))
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    offset += ret;
    
    if(dwHead != WFIO_FOURCC_RIFF)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    /* read "RIFF" length */
    
    pwfio->m_posRiffLength = offset;
    
    ret = fread(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
    if(ret != sizeof(U32))
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    offset += ret;
    dwSize = adjustByteOrder32(dwTemp); //Ignored
    
    /* read "WAVE" */
    
    ret = fread(&dwHead, 1, sizeof(U32), pwfio->m_fpWav);
    if(ret != sizeof(U32))
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    offset += ret;
    
    if(dwHead != WFIO_FOURCC_WAVE)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    offSeek = offset;
    
    /* -----------------------------------------------------------------------
    * find the FMT chunk: skip over unknown chunks
    */
    
    /* read "fmt " */
    fFmtChunkFound = False;  
    do {
        // Read chunk header
        ret = fread(&dwHead, 1, sizeof(U32), pwfio->m_fpWav);
        if(ret != sizeof(U32))
        {
            lr = MMSYSERR_READERROR;
            goto lerror;
        }
        offset += ret;
        
        if(dwHead == WFIO_FOURCC_fmt)
            fFmtChunkFound = True;
        
        /* read chunk length */
        ret = fread(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
        if(ret != sizeof(U32))
        {
            lr = MMSYSERR_READERROR;
            goto lerror;
        }
        offset += ret;
        
        dwSize = adjustByteOrder32(dwTemp);
        if (!fFmtChunkFound) {
            /* read-off dwSize bytes */
            offset += dwSize;
            ret = (size_t) fseek(pwfio->m_fpWav, (long) offset, SEEK_SET);
            if ( ret ) {
                lr = MMSYSERR_READERROR;
                goto lerror;
            } 
        }  
    } while (!fFmtChunkFound);
    
    /* "fmt " length was read earlier */
    /* prepare the format buffer */
    
    pwfio->m_sizeFormat = dwSize;
    if(pwfio->m_sizeFormat < sizeof(WAVEFORMATEXTENSIBLE))
        pwfio->m_sizeFormat = sizeof(WAVEFORMATEXTENSIBLE);
    
    pwfio->m_pFormat = (WAVEFORMATEXTENSIBLE *)malloc(pwfio->m_sizeFormat);
    if(pwfio->m_pFormat == NULL)
    {
        lr = MMSYSERR_NOMEM;
        goto lerror;
    }
    memset(pwfio->m_pFormat, 0, pwfio->m_sizeFormat);
    
    /* read the format chunk */
    
    ret = fread(pwfio->m_pFormat, 1, dwSize, pwfio->m_fpWav);
    if(ret != dwSize)
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    offset += ret;
    
    /* HongCho: I can convert the fields into the correct order here,
    *          but since I don't know the layouts of all the possible
    *          formats, only the fields in WAVEFORMATEXTENSIBLE will be
    *          converted.
    */
    
    pwfio->m_pFormat->Format.wFormatTag      = adjustByteOrder16(pwfio->m_pFormat->Format.wFormatTag);
    pwfio->m_pFormat->Format.nChannels       = adjustByteOrder16(pwfio->m_pFormat->Format.nChannels);
    pwfio->m_pFormat->Format.nSamplesPerSec  = adjustByteOrder32(pwfio->m_pFormat->Format.nSamplesPerSec);
    pwfio->m_pFormat->Format.nAvgBytesPerSec = adjustByteOrder32(pwfio->m_pFormat->Format.nAvgBytesPerSec);
    pwfio->m_pFormat->Format.nBlockAlign     = adjustByteOrder16(pwfio->m_pFormat->Format.nBlockAlign);
    pwfio->m_pFormat->Format.wBitsPerSample  = adjustByteOrder16(pwfio->m_pFormat->Format.wBitsPerSample);
    pwfio->m_pFormat->Format.cbSize          = adjustByteOrder16(pwfio->m_pFormat->Format.cbSize);
    
    if (pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE ) 
    {
        /* Additional formatting information */
        pwfio->m_pFormat->Samples.wValidBitsPerSample = adjustByteOrder16(pwfio->m_pFormat->Samples.wValidBitsPerSample);
        pwfio->m_pFormat->dwChannelMask      = adjustByteOrder32(pwfio->m_pFormat->dwChannelMask);
        pwfio->m_pFormat->SubFormat.Data1    = adjustByteOrder32(pwfio->m_pFormat->SubFormat.Data1);
        pwfio->m_pFormat->SubFormat.Data2    = adjustByteOrder16(pwfio->m_pFormat->SubFormat.Data2);
        pwfio->m_pFormat->SubFormat.Data3    = adjustByteOrder16(pwfio->m_pFormat->SubFormat.Data3);
    }
    else if( pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_WMAUDIO3 )
    {
        WMAUDIO3WAVEFORMAT* wma3fmt = (WMAUDIO3WAVEFORMAT*)pwfio->m_pFormat;
        {
            wma3fmt->wValidBitsPerSample = adjustByteOrder16(wma3fmt->wValidBitsPerSample);            
            wma3fmt->dwChannelMask       = adjustByteOrder32(wma3fmt->dwChannelMask);
            wma3fmt->dwReserved1         = adjustByteOrder32(wma3fmt->dwReserved1);
            wma3fmt->dwReserved2         = adjustByteOrder32(wma3fmt->dwReserved2);
            wma3fmt->wEncodeOptions      = adjustByteOrder16(wma3fmt->wEncodeOptions);
            wma3fmt->wReserved3          = adjustByteOrder16(wma3fmt->wReserved3);
        }
    }
    else if (pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_PCM ||
             pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_IEEE_FLOAT) 
    {
        /* Set some sensible values, just in case used by the application: Naveen */
        pwfio->m_pFormat->Samples.wValidBitsPerSample = pwfio->m_pFormat->Format.wBitsPerSample;
        switch (pwfio->m_pFormat->Format.nChannels) {
        case 1: 
            pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_CENTER;
            break;
        case 2:
            pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
            break;
        default:
            //wchen: let's make it default to 5.1 so that
            //we can open 5.1 data disguised as illegal WAV files
            pwfio->m_pFormat->dwChannelMask = (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | 
                                               SPEAKER_FRONT_CENTER | SPEAKER_BACK_LEFT | 
                                               SPEAKER_BACK_RIGHT | SPEAKER_LOW_FREQUENCY);
            break;
//            lr = MMSYSERR_ERROR;
//            goto lerror;
        }
    }

    /* the format chunk for PCM on WAVE files are WAVEFORMAT */
    if(pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_PCM)
        pwfio->m_pFormat->Format.cbSize = 0;
    
    if (pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
        if (pwfio->m_pFormat->Format.wBitsPerSample % 8) {
            /* Must be a multiple of 8 */
            lr = MMSYSERR_ERROR;
            goto lerror;
        }
        if (pwfio->m_pFormat->Format.cbSize != 22) {
            /* Must be 22 */
            lr = MMSYSERR_ERROR;
            goto lerror;
        }
        if (!IS_KSDATAFORMAT_SUBTYPE_PCM(&(pwfio->m_pFormat->SubFormat)) &&
            !IS_KSDATAFORMAT_SUBTYPE_IEEEFLOAT(&(pwfio->m_pFormat->SubFormat))) {
            /* We can only deal with PCM for now. */
            lr = MMSYSERR_ERROR;
            goto lerror;
        }
    }
    
    /* -----------------------------------------------------------------------
    * find the DATA chunk: skip over other unknown chunks
    */
    fDataChunkFound = False;
    
    do {  
        /* Read Chunk Header */
        ret = fread(&dwHead, 1, sizeof(U32), pwfio->m_fpWav);
        if(ret != sizeof(U32))
        {
            lr = MMSYSERR_READERROR;
            goto lerror;
        }
        offset += ret;
        
        fDataChunkFound = (dwHead == WFIO_FOURCC_data);
        
        if (!fDataChunkFound)
        {
            /* Read chunk length */
            ret = fread(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
            if(ret != sizeof(U32))
            {
                lr = MMSYSERR_READERROR;
                goto lerror;
            }
            offset += ret;
            
            dwSize = adjustByteOrder32(dwTemp);
            offset += dwSize;
            
            // Unknown/ un-needed chunk. Skip over it.
            /* read-off dwSize bytes */
            ret = (size_t) fseek(pwfio->m_fpWav, (long) offset, SEEK_SET);
            if ( ret) {
                lr = MMSYSERR_READERROR;
                goto lerror;
            }
        }
    } while (!fDataChunkFound);
    
    /* read "data" length */
    
    pwfio->m_posDataLength = offset;
    
    ret = fread(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
    if(ret != sizeof(U32))
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    offset += ret;
    
    pwfio->m_sizeData   = adjustByteOrder32(dwTemp);
    
    pwfio->m_posDataStart = (WMA_U32) offset;
    
#else  /* WFIO_NO_WIN32 */
    
    MMCKINFO ck;
    
    U32 cksize;
    
    if(pwfio == NULL)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    if(pwfio->m_hmmio == NULL)
    {
        lr = MMSYSERR_ERROR;
        goto lerror;
    }
    
    /* find the wave info chunk */
    pwfio->m_ckWave.fccType = WFIO_FOURCC_WAVE;
    lr = mmioDescend(pwfio->m_hmmio, &pwfio->m_ckWave, NULL, MMIO_FINDRIFF);
    if(lr != MMSYSERR_NOERROR)
        goto lerror;
    
    /* find FMT chunk */
    ck.ckid = WFIO_FOURCC_fmt;
    lr = mmioDescend(pwfio->m_hmmio, &ck, &pwfio->m_ckWave, MMIO_FINDCHUNK);
    if(lr != MMSYSERR_NOERROR)
        goto lerror;
    
    cksize = ck.cksize;
    if(cksize < sizeof(WAVEFORMATEXTENSIBLE))
        cksize = sizeof(WAVEFORMATEXTENSIBLE);
    
    /* prepare the format buffer */
    pwfio->m_sizeFormat = cksize;
    pwfio->m_pFormat = (WAVEFORMATEXTENSIBLE *)malloc(pwfio->m_sizeFormat);
    if(pwfio->m_pFormat == NULL)
    {
        lr = MMSYSERR_NOMEM;
        goto lerror;
    }
    memset(pwfio->m_pFormat, 0, pwfio->m_sizeFormat);
    
    /* read the format chunk */
    lr = mmioRead(pwfio->m_hmmio, (HPSTR)pwfio->m_pFormat, ck.cksize);
    if(lr != (I32)ck.cksize)
    {
        lr = MMSYSERR_READERROR;
        goto lerror;
    }
    
    /* the format chunk for PCM on WAV files are WAVEFORMAT */
    if(pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_PCM)
    {
        pwfio->m_pFormat->Format.cbSize = 0;
        /* Set some sensible values, just in case used by the application: Naveen */
        pwfio->m_pFormat->Samples.wValidBitsPerSample = pwfio->m_pFormat->Format.wBitsPerSample;
        switch (pwfio->m_pFormat->Format.nChannels) {
        case 1: 
            pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_CENTER;
            break;
        case 2:
            pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
            break;
        default:
            lr = MMSYSERR_ERROR;
            goto lerror;
        }
    }
    
    /* ascend out of FMT */
    lr = mmioAscend(pwfio->m_hmmio, &ck, 0);
    if(lr != MMSYSERR_NOERROR)
        goto lerror;
    
    /* find DATA chunk */
    pwfio->m_ck.ckid = WFIO_FOURCC_data;
    lr = mmioDescend(pwfio->m_hmmio, &pwfio->m_ck, &pwfio->m_ckWave, MMIO_FINDCHUNK);
    if(lr != MMSYSERR_NOERROR)
        goto lerror;
    
    pwfio->m_sizeData     = pwfio->m_ck.cksize;
    
    pwfio->m_posDataStart = pwfio->m_ck.dwDataOffset;
    
    /* get info */
    lr = mmioGetInfo(pwfio->m_hmmio, &pwfio->m_mmioinfo, 0);
    if(lr != MMSYSERR_NOERROR)
        goto lerror;
    
#endif /* WFIO_NO_WIN32 */
    
    return MMSYSERR_NOERROR;
    
lerror:
    if(pwfio &&
       pwfio->m_pFormat)
    {
        free(pwfio->m_pFormat);
        pwfio->m_pFormat = NULL;
        
        pwfio->m_sizeFormat = 0;
    }
    return lr;
}


/* This is a private function. It is only used in encapp. Don't call it from anywhere else */
I32
prvwfioReWriteHeaders(WavFileIO *pwfio,
                 WAVEFORMATEXTENSIBLE *pFormat,
                 U32 cbFormat)
{
    I32 lr;
    I32 iSizeData, iPosDataStart;
    // backup m_sizeData;
    iSizeData = pwfio->m_sizeData;
    iPosDataStart = pwfio->m_posDataStart; 
    /* seek to the beginning */
    prvwfioSeekRaw(pwfio, 0, SEEK_SET);
    /* write the header info */
    lr = wfioWriteHeaders(pwfio, pFormat, cbFormat);
    if(lr != MMSYSERR_NOERROR) {
        goto lerror;
    }
    pwfio->m_sizeData = iSizeData;    
    assert((U32)iPosDataStart == pwfio->m_posDataStart); 
    prvwfioSeekRaw(pwfio, pwfio->m_posDataStart + pwfio->m_sizeData , SEEK_SET);
lerror:
    return lr;
}

I32
wfioWriteHeaders(WavFileIO *pwfio,
                 WAVEFORMATEXTENSIBLE *pFormat,
                 U32 cbFormat)
{
  I32 lr;
  
#if WFIO_NO_WIN32
  
  size_t ret;
  size_t offset = 0;
  
  U32 dwTemp;
  
  WAVEFORMATEXTENSIBLE *pWavFormat = NULL;
  
  if(pwfio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  if(pwfio->m_fpWav == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pFormat == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(cbFormat < sizeof(WAVEFORMATEX))
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  /* copy the format locally */
  
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  pwfio->m_sizeFormat = cbFormat;
  pwfio->m_pFormat = (WAVEFORMATEXTENSIBLE *)malloc(pwfio->m_sizeFormat);
  if(pwfio->m_pFormat == NULL)
    {
      lr = MMSYSERR_NOMEM;
      goto lerror;
    }
  memcpy(pwfio->m_pFormat, pFormat, pwfio->m_sizeFormat);
  
  /* format in the right format... */
  pWavFormat = (WAVEFORMATEXTENSIBLE *)malloc(pwfio->m_sizeFormat);
  if(pWavFormat == NULL)
    {
      lr = MMSYSERR_NOMEM;
      goto lerror;
    }
  memcpy(pWavFormat, pFormat, pwfio->m_sizeFormat);
  
#define NO_HEADER_CLEANING
#if !defined (NO_HEADER_CLEANING)
  if (cbFormat == sizeof(WAVEFORMATEXTENSIBLE) &&
      pWavFormat->Format.wFormatTag == WAVE_FORMAT_PCM &&
      (pWavFormat->Format.nChannels > 2 ||
      pWavFormat->Format.wBitsPerSample > 16))
  {
      /* Automagically upgrade to WAVE_FORMAT_EXTENSIBLE format: Naveen */
      pWavFormat->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
      pWavFormat->Format.cbSize = 22;
      pWavFormat->Samples.wValidBitsPerSample = pWavFormat->Format.wBitsPerSample;
      switch (pWavFormat->Format.nChannels) {
      case 1:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_CENTER;
          break;
      case 2:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
          break;
      case 3:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_FRONT_CENTER;
          break;
      case 4:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT;
          break;
      case 5:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_CENTER;
          break;
      case 6: /* 5.1 */
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_CENTER |
              SPEAKER_LOW_FREQUENCY;
          break;
      default:
          lr = MMSYSERR_ERROR;
          goto lerror;
      }
      COPY_KSDATAFORMAT_SUBTYPE_PCM(&(pWavFormat->SubFormat));
  }
#endif // !defined (NO_HEADER_CLEANING)
  pWavFormat->Format.wFormatTag      = adjustByteOrder16(pWavFormat->Format.wFormatTag);
  pWavFormat->Format.nChannels       = adjustByteOrder16(pWavFormat->Format.nChannels);
  pWavFormat->Format.nSamplesPerSec  = adjustByteOrder32(pWavFormat->Format.nSamplesPerSec);
  pWavFormat->Format.nAvgBytesPerSec = adjustByteOrder32(pWavFormat->Format.nAvgBytesPerSec);
  pWavFormat->Format.nBlockAlign     = adjustByteOrder16(pWavFormat->Format.nBlockAlign);
  pWavFormat->Format.wBitsPerSample  = adjustByteOrder16(pWavFormat->Format.wBitsPerSample);
  pWavFormat->Format.cbSize          = adjustByteOrder16(pWavFormat->Format.cbSize);

  if( (pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE) || (pwfio->m_sizeFormat == sizeof(WAVEFORMATEXTENSIBLE)))
  {
    /* Additional formatting information */
    pWavFormat->Samples.wValidBitsPerSample = adjustByteOrder16(pWavFormat->Samples.wValidBitsPerSample);
    pWavFormat->dwChannelMask        = adjustByteOrder32(pWavFormat->dwChannelMask);
    pWavFormat->SubFormat.Data1    = adjustByteOrder32(pWavFormat->SubFormat.Data1);
    pWavFormat->SubFormat.Data2    = adjustByteOrder16(pWavFormat->SubFormat.Data2);
    pWavFormat->SubFormat.Data3    = adjustByteOrder16(pWavFormat->SubFormat.Data3);
  }
    
  if(((pwfio->m_pFormat->Format.wFormatTag == 0x162 )  ||
      (pwfio->m_pFormat->Format.wFormatTag == 0x164 )) &&
      (pwfio->m_sizeFormat == sizeof(WMAUDIO3WAVEFORMAT)))
  {
      // adjust the extra fields in the WMAUDIO3WAVEFORMAT structure.

      WMAUDIO3WAVEFORMAT *pFmt = (WMAUDIO3WAVEFORMAT*)pWavFormat;

      pFmt->wValidBitsPerSample = adjustByteOrder16( pFmt->wValidBitsPerSample );
      pFmt->dwChannelMask       = adjustByteOrder32( pFmt->dwChannelMask );
      pFmt->dwReserved1         = adjustByteOrder32( pFmt->dwReserved1 );
      pFmt->dwReserved2         = adjustByteOrder32( pFmt->dwReserved2 );
      pFmt->wEncodeOptions      = adjustByteOrder16( pFmt->wEncodeOptions );
      pFmt->wReserved3          = adjustByteOrder16( pFmt->wReserved3 );
  }
  /* -----------------------------------------------------------------------
   * create RIFF/WAVE chunk
   */
  
  /* write "RIFF" */
  
  dwTemp = WFIO_FOURCC_RIFF;
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* write "RIFF" length, temporarily */
  
  pwfio->m_posRiffLength = offset;
  
  dwTemp = 0;   /* temporary */
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* write "WAVE" */
  
  dwTemp = WFIO_FOURCC_WAVE;
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* -----------------------------------------------------------------------
   * create FMT chunk
   */
  
  /* write "fmt " */
  
  dwTemp = WFIO_FOURCC_fmt;
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* write "fmt " length */
  
  if (cbFormat == sizeof(WAVEFORMATEXTENSIBLE) &&
      pWavFormat->Format.cbSize == 0)
  {
    /* Traditional WAVE_FORMAT_PCM etc */
    cbFormat -= 22;
  } 
  
  dwTemp = adjustByteOrder32(cbFormat);
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* write actual format */
  
  ret = fwrite(pWavFormat, 1, cbFormat, pwfio->m_fpWav);
  if(ret != cbFormat)
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* -----------------------------------------------------------------------
   * create DATA chunk
   */
  
  /* write "data" */
  
  dwTemp = WFIO_FOURCC_data;
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  /* write "data" length */
  
  pwfio->m_posDataLength = offset;
  
  dwTemp = 0;
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  offset += ret;
  
  pwfio->m_sizeData   = 0;
  
  pwfio->m_posDataStart = (WMA_U32) offset;
  
  if(pWavFormat)
    {
      free(pWavFormat);
      pWavFormat = NULL;
    }
  
  return MMSYSERR_NOERROR;
  
 lerror:
  if (pwfio)
    {
      if(pwfio->m_pFormat)
        {
          free(pwfio->m_pFormat);
          pwfio->m_pFormat = NULL;
          
          pwfio->m_sizeFormat = 0;
        }
    }
  
  if(pWavFormat)
    {
      free(pWavFormat);
      pWavFormat = NULL;
    }
  
  return lr;
  
#else  /* WFIO_NO_WIN32 */
  
  if(pwfio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_hmmio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_mode != wfioModeWrite)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pFormat == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(cbFormat < sizeof(WAVEFORMATEX))
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  /* copy the format locally */
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  pwfio->m_sizeFormat = cbFormat;
  pwfio->m_pFormat = (WAVEFORMATEXTENSIBLE *)malloc(pwfio->m_sizeFormat);
  if(pwfio->m_pFormat == NULL)
    {
      lr = MMSYSERR_NOMEM;
      goto lerror;
    }
  CopyMemory(pwfio->m_pFormat, pFormat, pwfio->m_sizeFormat);
  if (pwfio->m_sizeFormat == sizeof(WAVEFORMATEXTENSIBLE) &&
      pwfio->m_pFormat->Format.wFormatTag == WAVE_FORMAT_PCM &&
      (pwfio->m_pFormat->Format.nChannels > 2 ||
      pwfio->m_pFormat->Format.wBitsPerSample > 16))
  {
      /* Automagically upgrade to WAVE_FORMAT_EXTENSIBLE */
      pwfio->m_pFormat->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
      pwfio->m_pFormat->Format.cbSize = 22;
      pwfio->m_pFormat->Samples.wValidBitsPerSample = pwfio->m_pFormat->Format.wBitsPerSample;
      switch (pwfio->m_pFormat->Format.nChannels) {
      case 1:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_CENTER;
          break;
      case 2:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
          break;
      case 3:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_FRONT_CENTER;
          break;
      case 4:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT;
          break;
      case 5:
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_CENTER;
          break;
      case 6: /* 5.1 */
          pwfio->m_pFormat->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
              SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_CENTER |
              SPEAKER_LOW_FREQUENCY;
          break;
      default:
          lr = MMSYSERR_ERROR;
          goto lerror;
      }
      COPY_KSDATAFORMAT_SUBTYPE_PCM(&(pwfio->m_pFormat->SubFormat));
  }
  
  /* create WAVE chunk */
  pwfio->m_ckWave.fccType = WFIO_FOURCC_WAVE;
  pwfio->m_ckWave.cksize  = 0;
  lr = mmioCreateChunk(pwfio->m_hmmio, &pwfio->m_ckWave, MMIO_CREATERIFF);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  /* create FMT chunk */
  if (cbFormat == sizeof(WAVEFORMATEXTENSIBLE) &&
      pwfio->m_pFormat->Format.cbSize == 0)
  {
    /* Not WAVE_FORMAT_EXTENSIBLE format */
    pwfio->m_sizeFormat -= 22;
  }
  pwfio->m_ck.ckid   = WFIO_FOURCC_fmt;
  pwfio->m_ck.cksize = pwfio->m_sizeFormat;
  lr = mmioCreateChunk(pwfio->m_hmmio, &pwfio->m_ck, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  
  /* copy out the format */
  lr = mmioWrite(pwfio->m_hmmio, (HPSTR)pwfio->m_pFormat, pwfio->m_sizeFormat);
  if(lr != (I32)pwfio->m_sizeFormat)
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  
  /* ascend out of FMT */
  lr = mmioAscend(pwfio->m_hmmio, &pwfio->m_ck, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  /* create DATA chunk */
  
  pwfio->m_ck.ckid   = WFIO_FOURCC_data;
  pwfio->m_ck.cksize = 0;
  lr = mmioCreateChunk(pwfio->m_hmmio, &pwfio->m_ck, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  /* get info */
  lr = mmioGetInfo(pwfio->m_hmmio, &pwfio->m_mmioinfo, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  
  return MMSYSERR_NOERROR;
  
 lerror:
  if(pwfio->m_pFormat)
    {
      free(pwfio->m_pFormat);
      pwfio->m_pFormat = NULL;
      
      pwfio->m_sizeFormat = 0;
    }
  return lr;
  
#endif /* WFIO_NO_WIN32 */
}


I32
wfioCleanUpRead(WavFileIO *pwfio)
{
  if(pwfio == NULL)
    return MMSYSERR_ERROR;
  
  /* for a historic reason... */
  return MMSYSERR_NOERROR;
}


I32
wfioCleanUpWrite(WavFileIO *pwfio)
{
  I32 lr;
  
#if WFIO_NO_WIN32
  
  size_t ret;
  
  U32 dwTemp;
  
  if(pwfio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_fpWav == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_mode != wfioModeWrite)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  /* flush it first */
  
  fflush(pwfio->m_fpWav);
  
  /* write back the data length */
  
  ret = (size_t) fseek(pwfio->m_fpWav, (long) pwfio->m_posDataLength, SEEK_SET);
  if(ret != 0)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  dwTemp = adjustByteOrder32(pwfio->m_sizeData);
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  
  /* write back the riff length */
  
  ret = (size_t) fseek(pwfio->m_fpWav, (long) pwfio->m_posRiffLength, SEEK_SET);
  if(ret != 0)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  dwTemp = pwfio->m_sizeData + pwfio->m_posDataStart - 8; /* "RIFF" and its size (4 + 4 bytes) */
  dwTemp = adjustByteOrder32(dwTemp);
  ret = fwrite(&dwTemp, 1, sizeof(U32), pwfio->m_fpWav);
  if(ret != sizeof(U32))
    {
      lr = MMSYSERR_WRITEERROR;
      goto lerror;
    }
  
  /* flush again... */
  
  fflush(pwfio->m_fpWav);
  
#else   /* WFIO_NO_WIN32 */
  
  if(pwfio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_hmmio == NULL)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  if(pwfio->m_mode != wfioModeWrite)
    {
      lr = MMSYSERR_ERROR;
      goto lerror;
    }
  
  /* write back the info */
  pwfio->m_mmioinfo.dwFlags |= MMIO_DIRTY;
  lr = mmioSetInfo(pwfio->m_hmmio, &pwfio->m_mmioinfo, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  /* ascend out of DATA.  this will cause the write-out. */
  lr = mmioAscend(pwfio->m_hmmio, &pwfio->m_ck, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
  /* ascend out of RIFF.  this will cause the file write-out, probably. */
  lr = mmioAscend(pwfio->m_hmmio, &pwfio->m_ckWave, 0);
  if(lr != MMSYSERR_NOERROR)
    goto lerror;
  
#endif  /* WFIO_NO_WIN32 */
  
  return MMSYSERR_NOERROR;
  
 lerror:
  return lr;
}
