/*
   3g file reader
 */

#include "fileifc.h"

#include <string.h>
#include "simpleBitstream.h"

static const int SamplingRateInfoTable[16] =
{ 96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 7350, -1, -1, 0 };

enum {
  ISO3GppBrand            = MP4_FOUR_CHAR_CODE( '3', 'g', 'p', '4' )
};


static void __setupDecoder (unsigned int *samplingRate,
                            unsigned int *extensionSamplingRate,
                            unsigned int *bitRate, 
                            AUDIO_OBJECT_TYPE *aot,
                            unsigned int* channelConfig,
                            ISOHandle decoderConfig)
{
  static const unsigned long decoderConfigDescrTag = 0x04 ;
  static const unsigned long decSpecificInfoTag    = 0x05 ;

  simpleBitstream decConfig = { 0 } ;
  unsigned long tmp1, tmp, sizeOfClass ;

  __initializeBitstream( &decConfig, (const unsigned char*)*decoderConfig);

  if ((unsigned)__getBits (&decConfig, 8) != decoderConfigDescrTag)
  {

      return ;
  }

  for (sizeOfClass = 0, tmp = 0x80 ; tmp &= 0x80 ;
       sizeOfClass = (sizeOfClass << 7) | (tmp & 0x7F))
    tmp = __getBits (&decConfig, 8) ;

  if (__getBits (&decConfig, 8) != 0x40)  /* 0x40 : Audio ISO/IEC 14496-3 */
  {
    return ;
  }

  if (__getBits (&decConfig, 6) != 0x5)
  {
    return ;
  }

  __getBits (&decConfig, 1) ;   /* upStream */
  __getBits (&decConfig, 1) ;   /* reserved */

  __getBits (&decConfig, 8) ;   /* bufferSizeDB */
  __getBits (&decConfig, 16) ; 

  __getBits (&decConfig, 16) ;   /* maxBitrate */
  __getBits (&decConfig, 16) ;

  *bitRate = ((__getBits (&decConfig, 16) << 16) | __getBits (&decConfig, 16)) ; /* avgBitrate */
  
  /* decoderSpecificInfo */

  if ((unsigned)__getBits (&decConfig, 8) != decSpecificInfoTag)
  {
    return ;
  }

  for (sizeOfClass = 0, tmp = 0x80 ; tmp &= 0x80 ;
       sizeOfClass = (sizeOfClass << 7) | (tmp & 0x7F))
    tmp = __getBits (&decConfig, 8) ;

  tmp1 = __getReadBits(&decConfig);

  /* AudioSpecificConfig starts here */
  *aot = (AUDIO_OBJECT_TYPE) __getBits (&decConfig, 5) ;

  tmp = __getBits (&decConfig, 4) ; /* SamplingRateIndex */

  if (tmp == 0x0F)
  {
    *samplingRate =  __getBits (&decConfig, 24) ;
  }
  else
  {
    *samplingRate = SamplingRateInfoTable[tmp];
  }

  tmp = __getBits (&decConfig, 4); /* channelConfiguration */

  *channelConfig = tmp;

  if (*aot == AOT_SBR)
  {
    tmp = __getBits (&decConfig, 4) ; /* extensionSamplingRateIndex */

    if (tmp == 0x0F) 
    {
      *extensionSamplingRate = __getBits (&decConfig, 24) ; /* extensionSamplingRate */
    }
    else
    {
      *extensionSamplingRate = SamplingRateInfoTable[tmp];
    }

    *aot = (AUDIO_OBJECT_TYPE) __getBits (&decConfig, 5) ;

  }

  /* GASC */
  if (*aot == AOT_AAC_MAIN || *aot == AOT_AAC_LC   || *aot == AOT_AAC_SSR ||
      *aot == AOT_AAC_LTP  || *aot == AOT_AAC_SCAL || *aot == AOT_TWIN_VQ) 
  {
    tmp = __getBits (&decConfig, 1); /* frameLengthFlag */ 
    tmp = __getBits (&decConfig, 1); /* dependsOnCoreCoder */
    tmp = __getBits (&decConfig, 1); /* extension Flag */
  }

  tmp = __getReadBits (&decConfig);

  if (*aot != AOT_SBR && (sizeOfClass*8 - (tmp -tmp1) >= 16 ))
  {
    tmp = __getBits (&decConfig, 11); /* syncExtensionType */

    if ( tmp == 0x2b7 )
    {
      tmp = (AUDIO_OBJECT_TYPE) __getBits (&decConfig, 5); /* extensionAudioObjectType */
      
      if ( tmp == AOT_SBR )
      {
        tmp = __getBits (&decConfig, 1); /* sbrPresentFlag */
        if (tmp) 
        {
          tmp = __getBits (&decConfig, 4); /* extensionSamplingFrequencyIndex */
          if (tmp == 0xf)
          {
            tmp = __getBits (&decConfig, 4); /* extensionSamplingFrequency */
          }
        }
      }
    }
  }
  
}

FileWrapperPtr FileWrapper_Open(char fileName[])
{

  FileWrapperPtr transport = (FileWrapper*)calloc(1, sizeof(FileWrapper));

  ISOTrack theTrack ;
  ISOMedia theMedia ;

  ISOHandle initialObjectDescriptorH ;
  ISOHandle decoderConfig ;
  ISOHandle decoderSpecificInfo ;

  ISOErr err;
  
  unsigned int handlerType ;
  unsigned int handleSize ;
  unsigned int objectTypeIndication ;
  unsigned int streamType ;
  unsigned int decoderBufferSize ;
  int trackNumber = 1;

  transport->isMp4File = 0;
  transport->inputFile = NULL;
  /*  transport->profile = Profile_reserved; */
  transport->samplingRate = 0;
  transport->extensionSamplingRate = 0;
  transport->bitRate = 0;

  /*  transport->profileLevelIndication = Profile_Reserved; */
   
  err = ISOOpenMovieFile (&transport->theMovie, fileName, MP4OpenMovieNormal) ;

  if (err) { /* try if it's a non MP4 file */
    transport->inputFile = fopen (fileName, "rb") ;
    if (!transport->inputFile)
      return 0;
    else
      return transport;
  }

  transport->isMp4File = 1;

  {
    unsigned int major_brand, minor_version;

    err = ISOGetMovieBrand(transport->theMovie, &major_brand, &minor_version);

    if (!ISOIsMovieCompatibleBrand( transport->theMovie, major_brand )) {
      return 0;
    }
    
  }

  err = ISONewHandle (0, &initialObjectDescriptorH);
  if (err) return 0 ;
  err = MP4GetMovieInitialObjectDescriptor (transport->theMovie, initialObjectDescriptorH);
  if (err) return 0 ;

  {
    unsigned long tmp, sizeOfClass ;
    simpleBitstream initOD = { 0 } ;
    
    initOD.buffer = (const unsigned char *) *initialObjectDescriptorH ;

    if (__getBits (&initOD, 8) != 0x02)
    {
      return 0;
    }

    for (sizeOfClass = 0, tmp = 0x80 ; tmp &= 0x80 ;
         sizeOfClass = (sizeOfClass << 7) | (tmp & 0x7F))
      tmp = __getBits (&initOD, 8) ;

    __getBits (&initOD, 10);
    tmp = __getBits (&initOD, 1); /*URL_Flag */
    __getBits (&initOD, 1);

    if (__getBits (&initOD, 4) != 0xF)
    {
      return 0;
    }

    if (tmp) 
    {
      __getBits (&initOD, 8);
      __getBits (&initOD, 8);
    }
    else 
    {
      tmp = __getBits (&initOD, 8); /* ODProfileLevelIndication */
      tmp = __getBits (&initOD, 8); /* sceneProfileLevelIndication */
      /*transport->profileLevelIndication = (MPEG_4_PROFILE)__getBits (&initOD, 8); audioProfileLevelIndication */
      tmp = __getBits (&initOD, 8); /* visualProfileLevelIndication */
      tmp = __getBits (&initOD, 8); /* graphicsProfileLevelIndication */
    }
  }
  
  /* NB: this only ever tries to read track #1 in the file */

  err = ISOGetMovieIndTrack (transport->theMovie, trackNumber, &theTrack) ; if (err) return 0 ;
  err = ISOGetTrackMedia (theTrack, &theMedia) ; if (err) return 0 ;
  err = ISOGetMediaHandlerDescription (theMedia, &handlerType, NULL) ; if (err) return 0 ;

  err = ISOCreateTrackReader (theTrack, &transport->theReader) ; if (err) return 0 ;
  err = ISONewHandle (0, &decoderConfig) ; if (err) return 0 ;
  err = MP4TrackReaderGetCurrentDecoderConfig (transport->theReader, decoderConfig) ; if (err) return 0 ;
  err = ISONewHandle (0, &decoderSpecificInfo) ; if (err) return 0 ;

  err = MP4GetMediaDecoderType (theMedia, 1, &objectTypeIndication,
                                &streamType,
                                &decoderBufferSize,
                                decoderSpecificInfo) ; if (err) return 0 ;

  err = ISODisposeHandle (initialObjectDescriptorH) ;

  err = ISOGetHandleSize (decoderSpecificInfo, &handleSize) ; if (err) return 0 ;

  __setupDecoder (&transport->samplingRate,
                  &transport->extensionSamplingRate,
                  &transport->bitRate, 
                  &transport->audioObjectType, 
                  &transport->channelConfig, 
                  decoderConfig) ;


  if (transport->audioObjectType != AOT_AAC_LC) 
  {
    return 0;
  }
  
  /*  transport->profile = Profile_LowComplexity; */

  err = ISONewHandle (0, &transport->theSample) ; if (err) return 0;

  return transport;
}

int FileWrapper_Read(FileWrapperPtr transport, unsigned char *buffer, int bufSize, unsigned int *length)
{
  if (!transport->isMp4File)
    *length = fread (buffer, 1, bufSize, transport->inputFile) ;
  else {
    ISOErr err = ISONoErr ;
    unsigned int cts, dts, sampleFlags ;
    
    /* read a media sample from input file */
    err = MP4TrackReaderGetNextAccessUnit (transport->theReader, transport->theSample, length, &sampleFlags, &cts, &dts) ;
    
    if (err)  {
      if (err == ISOEOF)
        err = ISONoErr ;
      
      return 1;
    }

    assert (*length <= (unsigned)bufSize);
 
    memcpy (buffer, *transport->theSample, *length);
  }

  return 0;
}

unsigned int FileWrapper_Close(FileWrapperPtr transport)
{
  ISOErr err = ISONoErr;

  if (transport==0)
    return 0;
  
  if (transport->isMp4File) {
    if (transport->theSample)
      err = ISODisposeHandle(transport->theSample);
    
    if (transport->theReader)
      err = ISODisposeTrackReader(transport->theReader);
    
    if (transport->theMovie)
      err = ISODisposeMovie(transport->theMovie);
  }
  else if (transport->inputFile)
    fclose(transport->inputFile);

  free(transport);
  return 0;
}

unsigned int FileWrapper_IsMp4File(FileWrapperPtr transport)
{
  return transport->isMp4File;
}

unsigned int FileWrapper_Is3GPPFile(FileWrapperPtr transport)
{ 
  unsigned int major_brand, minor_version;
  ISOErr err;
  err = ISOGetMovieBrand(transport->theMovie, &major_brand, &minor_version);

  return (major_brand == ISO3GppBrand) ? 1 : 0;
}
