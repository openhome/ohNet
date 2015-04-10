/*
   Main for enhanced aacPlus decoding
 */

#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "FFR_bitbuffer.h"
#include "au_channel.h"
#include "fileifc.h"

#include "aacdecoder.h"
#include "sbrdecoder.h"
#include "spline_resampler.h"
#include "aac_ram.h"
#include "aac_rom.h"

/* ETSI operators types and WMOPS measurement */
#include "typedef.h"
#include "count.h"


#ifdef WMOPS
//#define MEASURE_AVERAGE
#define MEASURE_WORST_CASE
#endif


#define FILE_NAME_MAX     256
#define SAMPLES_PER_FRAME 1024

enum {
  MAIN_OK = 0x0,
  MAIN_OPEN_BITSTREAM_FILE_FAILED,
  MAIN_OPEN_16_BIT_PCM_FILE_FAILED,
  MAIN_OPEN_ERROR_PATTERN_FILE_FAILED,
  MAIN_FRAME_COUNTER_REACHED_STOP_FRAME
};  

int ErrorStatus = MAIN_OK;                             /*!< error status */

hAudioChannel audioOut = 0;                            /*!< handle to audio output */
AuChanInfo audioOutInfo;                               /*!< info structure for audio output file */
AuChanType audioOutType;                               /*!< type specifier for audio output (RT or File) */

FileWrapperPtr inputFile;                              /*!< file pointer to bitstream file (mp4) */
FILE *pOutputFile;                                     /*!< file pointer to 16 bit output file */
FILE *pErrorPatternFile = NULL;                        /*!< file pointer to error pattern file */

unsigned short frameCounter = 0;                       /*!< frame counter */

char inputBsFilename[FILENAME_MAX] = {0};              /*!< name of bitstream file */
char output16BitPcmFilename[FILENAME_MAX] = {0};       /*!< name of 16 bit output file */
char errorPatternFilename[FILENAME_MAX] = {0};         /*!< name of error pattern file */

/* 
   IO-Buffers 
*/
#define INPUT_BUF_SIZE (6144*2/8)                      /*!< Size of Input buffer in bytes*/

unsigned short inBuffer[INPUT_BUF_SIZE/(sizeof(short))];   /*!< Input buffer */
Word16 timeData[4*SAMPLES_PER_FRAME];                  /*!< Output buffer */

/*
  The function determines the last instructions if the exit process is called.
*/
static void aac_exit(void)
{
  if (audioOut)
    AuChannelClose(audioOut);
  FileWrapper_Close(inputFile);
  if (pOutputFile)
    fclose(pOutputFile);
  if (pErrorPatternFile)
    fclose(pErrorPatternFile);
}



/*
  The function reads the frameError flag from a file.
  
  return:  1 if the frame is ok, else 0
*/
static char ReadErrorPatternFile(FILE *epf)
{
  char tmp;
  int readOk;

  if (!epf)
    return 1;

  readOk = fscanf(epf, "%c\n", &tmp);
  if (readOk != 1) {
    rewind(epf);
    fscanf(epf, "%c\n", &tmp);
  }
  if (tmp == '0')
    return 1;
  else
    return 0;
}


/*
  The function reads the bitstream from a MPEG-4 file and stores the bitstream
  in the input buffer. The input buffer is filled with one AU.

  return:  1 if end of file has been reached
*/
static Flag CBitstreamFillBufferAU(HANDLE_BIT_BUF hBitBuf,     /*!< pointer to current data in bitstream */
                                   FileWrapperPtr transport
                                   )
{
  unsigned int cbValid = 0;
  unsigned int i;
  int ErrorStatus = 0;
  unsigned char readbuf[4096];

  /* read bitstream */
  ErrorStatus = FileWrapper_Read(transport, readbuf, 4096,  &cbValid);

  for (i=0; i<cbValid; i++)
    WriteBits(hBitBuf,readbuf[i],8);

  return ErrorStatus;
}

/*
  Interleave output samples. In case of mono input, copy left channel to right channel
*/
static void 
interleaveSamples(Word16 *pTimeCh0, 
                  Word16 *pTimeCh1, 
                  Word16 *pTimeOut, 
                  Word32  frameSize, 
                  Word16 *channels)
{
  int i;

  for (i=0; i<frameSize; i++)
  {
    *pTimeOut++ = *pTimeCh0++;

    if(*channels == 2) {
      *pTimeOut++ = *pTimeCh1++;
    }
    else {
      *pTimeOut = *(pTimeOut-1);
      *pTimeOut++;
    }
  }

  *channels = 2;
}

/*
  The function sets default audio parameters and opens the
  output file for 16 bit.

  return:  error status
*/
static int 
AuChannelInit16(char *outfile,     /*!< pointer to output file */
                Word32 sampleRate, /*!< sampling frequency */
                short max_chan,    /*!< channels */
                int read_args)     /*!< read arguments */
{
  AuChanError audioError = AU_CHAN_OK;
  
  /* determination of the audio output type */
  if (read_args == 2)
    audioOutType = TYPE_AUTODETECT;
  else
  {
    audioOutInfo.typeInfo.rt.level = 200;
    audioOutType = TYPE_RT;
  }

  /* set audio output default values */
  audioOutInfo.valid = 1;
  audioOutInfo.bitsPerSample = 16;
  audioOutInfo.fpScaleFactor = 32768.0;
  audioOutInfo.nChannels = max_chan;
  audioOutInfo.sampleRate = sampleRate;

  /* open output file */
  if ((audioError = AuChannelOpen(&audioOut,outfile,AU_CHAN_WRITE,&audioOutType,&audioOutInfo)))
  {
    fprintf(stderr,"\n    AuChannelOpen output file failed: error %d\n", audioError);
    return MAIN_OPEN_16_BIT_PCM_FILE_FAILED;
  }

  fprintf(stderr,"\nopened output ch=%d, fs=%d\n", audioOutInfo.nChannels, audioOutInfo.sampleRate);
  return MAIN_OK;
}


/*
  The function opens the error pattern file (if any).

  return:  error status
*/

static int 
OpenErrorPatternFile(char *file)    /*!< char[] containing the filename (if any) */
{
  /* open error pattern file */
  if (!file[0])
    return MAIN_OK;
  pErrorPatternFile = fopen(file, "r");
  if (pErrorPatternFile == NULL)
  {
    fprintf (stderr, "\n error pattern file not found\n\n");
    return MAIN_OPEN_ERROR_PATTERN_FILE_FAILED;
  }
  return MAIN_OK;
}

/*
  The function displays copyright message
*/
static void display_copyright_message(void)
{
  fprintf(stderr,"\n");
  fprintf(stderr,"*************************************************************\n");
  fprintf(stderr,"* Enhanced aacPlus 3GPP ETSI-op Reference Decoder\n");
  fprintf(stderr,"* Build %s, %s\n", __DATE__, __TIME__);
  fprintf(stderr,"*\n");
  fprintf(stderr,"*************************************************************\n\n");
}

int cntIdExt1, cntIdExt2, cntIdExt3; /* global counters, may be used for profiling */


/*
  After an initialization phase, CAacDecoder_DecodeFrame() and applySBR()
  are called in an endless loop until the complete bitstream has been decoded.

  The main program provides the aac core and the sbr tool with the time data buffer of length
  4 * SAMPLES_PER_FRAME.

  return:  error status
*/
int main(int argc, char *argv[])
{
  int cntId1, cntId2, cntId3;

  int endOfFile = 0;
  Flag frameOk = 1;                                 /*!< frameOk flag */
  Flag lastFrameOk = 1;
  int i;
  int written16;
  Word8 channelMode = 0;
  struct BIT_BUF bitBuf, *hBitBuf;
  AACDECODER aacDecoderInfo = 0;                    /*!< pointer to aacdecoder structure */
  SBRBITSTREAM streamSBR[2];                        /*!< pointer to sbr bitstream buffer */
  SBRDECODER sbrDecoderInfo = 0;                    /*!< pointer to sbrdecoder structure */
  HANDLE_SPLINE_RESAMPLER splineResampler = 0;      /*!< pointer to spline resampler instance */ 
  Word16 pTimeDataPcm[4*SAMPLES_PER_FRAME];         /*!< required only for interfacing with 
                                                         audio output library, thus not counted
                                                         for RAM usage */

  Word16 frameSize;
  Word32 sampleRate, outputSampleRate = 0;
  Word16 numChannels;
  Word16 numChannelsLast = 0;
  Word16 numOutSamples;
  Flag bDownSample = 0;

  Flag fosr16 = 0;
  Flag fosr8  = 0;
  Flag bBitstreamDownMix = 0;
  Flag bValidMode = 0;

  /* print copyright message */
  display_copyright_message();

  bBitstreamDownMix = 0;    
  
  if (argc != 4 && argc != 5) {
    fprintf(stderr, "\nUsage: %s <bitstream_file> <wav_file> <mode> [error_pattern_file]\n", argv[0]);
    fprintf(stderr, "\n       <mode> is one out of:");
    fprintf(stderr, "\n         (def) default decoding");
    fprintf(stderr, "\n         (mon) mono output decoding");
    fprintf(stderr, "\n         (f08) 8 kHz output decoding");
    fprintf(stderr, "\n         (f16) 16 kHz output decoding\n");
    fprintf(stderr, "\n         (m08) mono 8 kHz output decoding");
    fprintf(stderr, "\n         (m16) mono 16 kHz output decoding\n");
    return 0;
  }

  /*
    evaluate mode and set flags accordingly
  */
  if (strcmp(argv[3],"def")==0) {
    bValidMode = 1;
  }
  
  if (strcmp(argv[3],"mon")==0) {
    bValidMode = 1;
    bBitstreamDownMix = 1;
  }

  if (strcmp(argv[3],"f08")==0) {
    bValidMode = 1;
    fosr8 = 1;
  }

  if (strcmp(argv[3],"f16")==0) {
    bValidMode = 1;
    fosr16 = 1;
  }
  
  if (strcmp(argv[3],"m08")==0) {
    bValidMode = 1;
    bBitstreamDownMix = 1;
    fosr8 = 1;
  }
  
  if (strcmp(argv[3],"m16")==0) {
    bValidMode = 1;
    bBitstreamDownMix = 1;
    fosr16 = 1;
  }

#ifdef MONO_ONLY
  bBitstreamDownMix = 1;
#endif

  if (bValidMode == 0) {
    fprintf(stderr, "Invalid mode, call %s without arguments for help\n", argv[0]);
    return -1;
  }
  
  atexit(aac_exit);
  inputFile = FileWrapper_Open(argv[1]);
  if (inputFile == 0) {
    fprintf(stderr, "Failed to open bitstream file %s\n", argv[1]);
    return -1;
  } else if (!FileWrapper_IsMp4File(inputFile)) {
    fprintf(stderr, "Invalid input file %s\n", argv[1]);
    return -2;
  } else {
    fprintf(stderr, "Input bitstream file:\t%s\n", argv[1]);
  }

  strcpy(output16BitPcmFilename, argv[2]);

  if (argc == 5) {
    ErrorStatus = OpenErrorPatternFile(argv[4]);
    if (ErrorStatus == MAIN_OPEN_ERROR_PATTERN_FILE_FAILED) {
      fprintf(stderr, "Failed to open error pattern file\n");
      return -3;
    }
  }


  /* dual or dingle rate signalled in bitstream ? */
  if (inputFile->samplingRate == inputFile->extensionSamplingRate) {
    bDownSample = 1;
  }
  
  /* initialize time data buffer */
  for (i=0; i < 4*SAMPLES_PER_FRAME; i++)
  {
    timeData[i] = 0;
  }

  /* initialize bit buffer */
  hBitBuf = CreateBitBuffer(&bitBuf,(unsigned char*) inBuffer,INPUT_BUF_SIZE);

  /* initialize AAC decoder */
  if (!ErrorStatus) {
    
    aacDecoderInfo =  CAacDecoderOpen(hBitBuf,
                                      streamSBR,
                                      inputFile->samplingRate); 
    if (!aacDecoderInfo) {
      ErrorStatus = -1;
    }
  }
  
  
  if (ErrorStatus)
    return ErrorStatus;

  Init_WMOPS_counter();
#ifdef MEASURE_AVERAGE
  cntId1=getCounterId("AAC Decoder");
  cntId2=getCounterId("SBR Decoder");
  cntId3=getCounterId("Spline Res.");
#endif

#ifdef MEASURE_WORST_CASE
  cntId1=getCounterId("Enhanced aacPlus Decoder");
#endif

  cntIdExt1=getCounterId("External Counter #1");
  cntIdExt2=getCounterId("External Counter #2");
  cntIdExt3=getCounterId("External Counter #3");
  
   
  while (!ErrorStatus && !endOfFile)  {

    /* initiate counter */
    setCounter(cntId1); 
    Reset_WMOPS_counter ();

    /* decode one frame of audio data */
    streamSBR[0].nrElements = 0;
    
    /* Reading bitstream data from file (not instrumented) */
    endOfFile = CBitstreamFillBufferAU(hBitBuf,inputFile);
    
    /* Reading error pattern from file (not instrumented) */
    frameOk = ReadErrorPatternFile(pErrorPatternFile); 
    

    /* AAC core decoder */
    ErrorStatus = CAacDecoder_DecodeFrame(aacDecoderInfo,
                                          &frameSize,
                                          &sampleRate,
                                          &channelMode,
                                          &numChannels,
                                          timeData,
                                          frameOk);
   
    if (ErrorStatus) {
      /*
        Leave loop in case of errors, EOF is no error
      */
      if (endOfFile) {
        ErrorStatus = 0;
      }
      break;
    }

    /* end AAC decoder */


    /* SBR decoder */

    /* initiate counter */
#ifdef MEASURE_AVERAGE
    fwc();
    setCounter(cntId2); 
    Reset_WMOPS_counter();
#endif

    /* open SBR-handle if SBR-Bitstream has been detected in core decoder */
    if ((!sbrDecoderInfo) && streamSBR[0].nrElements) {
      int lpFilter = 0;      

      if(fosr16){
        lpFilter = 8;
        bDownSample = 1;
      }
      if(fosr8){
        lpFilter = 4;
        bDownSample = 1;
      }
      
      sbrDecoderInfo = openSBR (sampleRate, frameSize, bDownSample, lpFilter);
    }

    {
      Flag tmp = frameOk;
      frameOk = lastFrameOk;
      lastFrameOk = tmp;
    }

    if (sbrDecoderInfo) {
      
      /* apply SBR processing */
      if (applySBR(sbrDecoderInfo,
                   &streamSBR[0],
                   timeData,
                   &numChannels,
                   frameOk, 
                   bDownSample,
                   bBitstreamDownMix) != SBRDEC_OK){
        sbrDecoderInfo = 0;
      }
      else {
        if(!bDownSample){
          
          frameSize = frameSize*2;
          sampleRate *= 2;
        }
      }
      
      if(bBitstreamDownMix) {
        numChannels = 1;
      }
    }
    /* end sbr decoder */

#ifdef MEASURE_AVERAGE
    /* initiate counter */
    fwc();
    setCounter(cntId3); 
    Reset_WMOPS_counter();
#endif

    
    outputSampleRate = sampleRate;
    numOutSamples = frameSize;


    /* spline resampler*/
    /* init spline resampler if desired and/or needed */
    if (fosr16 && sampleRate != 16000) {
      
      /* initialize resampler if not done already */
      if (!splineResampler) {
        CreateSplineResampler(&splineResampler, (Word16)sampleRate, 16000);
      }
      
      if (numChannels == 2 && numChannelsLast == 1) {
        CopyResamplerState(splineResampler);
      }

      /* do resampling, works inplace on one channel */
      SplineResample (splineResampler, timeData, frameSize, &numOutSamples, 0);
      
      if (numChannels == 2) {
        SplineResample (splineResampler, &timeData[2 * SAMPLES_PER_FRAME], frameSize, &numOutSamples, 1);
      }
      
      outputSampleRate = 16000;
    }
    else {
      if (fosr8 && sampleRate != 8000) {
        
        /* initialize resampler if not done already */
        if (!splineResampler) {
          CreateSplineResampler(&splineResampler, (Word16)sampleRate, 8000);
        }
        
        if (numChannels == 2 && numChannelsLast == 1) {
          CopyResamplerState(splineResampler);
        }

        /* do resampling, works inplace on one channel */
        SplineResample (splineResampler, timeData, frameSize, &numOutSamples, 0);
        
        if (numChannels == 2) {
          SplineResample (splineResampler, &timeData[2 * SAMPLES_PER_FRAME], frameSize, &numOutSamples, 1);
        }
        
        outputSampleRate = 8000;
      }
    }

    numChannelsLast = numChannels;

    /* end spline resampler */


    /* Audio output handling (not instrumented) */
    if (output16BitPcmFilename[0]) {
      if (frameCounter > 0) {

        /* interleave time samples */
        interleaveSamples(&timeData[0],&timeData[2 * SAMPLES_PER_FRAME],pTimeDataPcm,frameSize,&numChannels);
    
        /* open audio output if not done yet */
        if (!audioOut) {
          if ( (ErrorStatus = AuChannelInit16(output16BitPcmFilename,outputSampleRate,numChannels,2)) ) {
            fprintf(stderr, "Failed to open output file %s\n", output16BitPcmFilename);
            return -4;
          }
          else {
            fprintf(stderr, "Output file:\t\t%s\n", output16BitPcmFilename);
            /* doesn't really fit here, but we want to display argv in order */
            if (pErrorPatternFile != NULL) {
              fprintf(stderr, "Error pattern file:\t%s\n", argv[4]);
            }

            fprintf(stderr, "\n");
          }
        }

        /* write audio channels to pcm file */
        AuChannelWriteShort(audioOut,pTimeDataPcm,numOutSamples*numChannels,&written16);
      }
    }
    


    frameCounter++;
    
    if (frameCounter > 1) {
      fprintf(stderr,"\r[%5d]",frameCounter);
    }
    

    fwc();

#ifdef MEASURE_WORST_CASE
    WMOPS_output(0);
#endif
  }

#ifdef MEASURE_AVERAGE
  WMOPS_summary(0);
#endif

  if (ErrorStatus) {
    fprintf(stderr, "\nError: %x", ErrorStatus);
  }

  fprintf(stderr, "\ndecoding finished\n");

  return ErrorStatus;
}






