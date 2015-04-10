/*
   3g file reader
 */

#ifndef __fileifc_h__
#define __fileifc_h__

#include <stdio.h>
#include <stdlib.h>

#include "MP4Movies.h"
#include "audioobjecttypes.h"

typedef struct FileWrapper
{
  ISOMovie theMovie ;

  MP4TrackReader theReader ;
  MP4Handle theSample ;

  AUDIO_OBJECT_TYPE audioObjectType;
  /*  MPEG_4_PROFILE profileLevelIndication; */

  unsigned int samplingRate;
  unsigned int extensionSamplingRate;
  unsigned int bitRate;
  unsigned int channelConfig;
  
  /*  MPEG_2_PROFILE profile; */
  unsigned int isMp4File;

  FILE *inputFile;

} FileWrapper, *FileWrapperPtr;


FileWrapperPtr FileWrapper_Open(char fileName[]);
int FileWrapper_Read(FileWrapperPtr transport, unsigned char *buffer, int bufSize, unsigned int *len);
unsigned int FileWrapper_Close(FileWrapperPtr transport);

unsigned int FileWrapper_IsMp4File(FileWrapperPtr transport);

unsigned int FileWrapper_Is3GPPFile(FileWrapperPtr transport);


#endif
