#include <OpenHome/Media/Codec/AacBase.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <string.h>

extern "C" {
#include <aacdecoder.h>
#include <aac_ram.h>
#include <aac_rom.h>
#include <bitstream.h>
#include <block.h>
#include <channel.h>
#include <channelinfo.h>
#include <conceal.h>
#include <datastream.h>
#include <imdct.h>
#include <pns.h>
#include <pulsedata.h>
#include <stereo.h>
#include <streaminfo.h>
#include <tns.h>
#include <overlapadd.h>
#include <defines.h>
#include <spline_resampler.h>

#define SAMPLES_PER_FRAME 1024

  // global AAC decoder variables
  Flag frameOk = 1;                                 /*!< frameOk flag */
  Flag lastFrameOk = 1;
  Word8 channelMode = 0;
  struct BIT_BUF bitBuf, *hBitBuf;
  AACDECODER aacDecoderInfo = 0;                    /*!< pointer to aacdecoder structure */
  SBRBITSTREAM streamSBR[2];                        /*!< pointer to sbr bitstream buffer */
  SBRDECODER sbrDecoderInfo = 0;                    /*!< pointer to sbrdecoder structure */
  HANDLE_SPLINE_RESAMPLER splineResampler = 0;      /*!< pointer to spline resampler instance */ 
  Word16 pTimeDataPcm[4*SAMPLES_PER_FRAME];         /*!< required only for interfacing with 
                                                         audio output library, thus not counted
                                                         for RAM usage */
  Word16 timeData[4*SAMPLES_PER_FRAME];                  /*!< Output buffer */
}


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// CodecAacBase

const Brn CodecAacBase::kCodecAac("AAC");

CodecAacBase::CodecAacBase()
{
    LOG(kCodec, "CodecAacBase::CodecAacBase\n");
}

CodecAacBase::~CodecAacBase()
{
    LOG(kCodec, "CodecAacBase::~CodecAacBase\n");
}

TBool CodecAacBase::SupportsMimeType(const Brx& aMimeType)
{
    static const Brn kMimeAac("audio/aac");
    static const Brn kMimeAacp("audio/aacp");
    if (aMimeType == kMimeAac || aMimeType == kMimeAacp) {
        return true;
    }
    return false;
}

void CodecAacBase::StreamInitialise()
{
    LOG(kCodec, "CodecAacBase::StreamInitialise\n");

    // initialise global aac variables
    frameOk = 1;
    lastFrameOk = 1;
    channelMode = 0;
    aacDecoderInfo = 0;
    sbrDecoderInfo = 0;
    splineResampler = 0;

    iFrameCounter = 0;

    iNewStreamStarted = false;
    iStreamEnded = false;

    iTotalSamplesOutput = 0;

    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);
}

void CodecAacBase::StreamCompleted()
{
    LOG(kCodec, "CodecAacBase::StreamCompleted\n");
}

TBool CodecAacBase::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

void CodecAacBase::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);
    TUint i=0;

    for(i=0 ; i<aToWrite*iChannels; i++) {
        switch (iBitDepth) {
        case 8:
            *dst++ = *src++;
            break;
        case 16:
#ifdef DEFINE_BIG_ENDIAN
            *dst++ = src[0];
            *dst++ = src[1];
#else
            *dst++ = src[1];
            *dst++ = src[0];
#endif
            src += 2;
            break;
        case 24:
#ifdef DEFINE_BIG_ENDIAN
            *dst++ = src[0];
            *dst++ = src[1];
            *dst++ = src[2];
#else
            *dst++ = src[2];
            *dst++ = src[1];
            *dst++ = src[0];
#endif
            src += 3;
            break;
        default:
            ASSERTS();
        }
    }
}


void CodecAacBase::InterleaveSamples(Word16 *pTimeCh0, 
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
  }

}

void CodecAacBase::Process()
{
    if (iNewStreamStarted) {
        THROW(CodecStreamStart);
    }
    if (iStreamEnded) {
        THROW(CodecStreamEnded);
    }
}

// flush any remaining samples from the decoded buffer
void CodecAacBase::FlushOutput()
{    
    if ((iStreamEnded || iNewStreamStarted) && iOutBuf.Bytes() > 0) {
        iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iOutputSampleRate,
            iBitDepth, EMediaDataEndianBig, iTrackOffset);
        iOutBuf.SetBytes(0);
    }
    //LOG(kCodec, "CodecAac::Process complete - total samples = %lld\n", iTotalSamplesOutput);
}

void CodecAacBase::DecodeFrame(TBool aParseOnly)
{
    TUint error = false;
    TInt16 frameSize = 0;
    TUint32 sampleRate = 0;
    TInt16 numChannels = 0;
    TInt16 numOutSamples = 0;
    TBool bDownSample = false;
    TBool bBitstreamDownMix = false;

    /* decode one frame of audio data */
    streamSBR[0].nrElements = 0;   
    frameOk = 1;        // assume frame is always ok
    frameSize = (TInt16)(iInBuf.Bytes());
    sampleRate = iSampleRate;
    numChannels = iChannels;

    // must be reinitialised every time through if the buffer size changes
    hBitBuf = CreateInitializedBitBuffer(&bitBuf, (unsigned char*)iInBuf.Ptr(), (TInt16)iInBuf.Bytes());

    /* AAC core decoder */
    error = CAacDecoder_DecodeFrame(aacDecoderInfo,
                                          &frameSize,
                                          (Word32*)&sampleRate,
                                          &channelMode,
                                          &numChannels,
                                          timeData,
                                          frameOk);
   
    if (error) {
        //LOG(kCodec, "Aac::DecodeFrame error %d\n", error);
        THROW(CodecStreamCorrupt);
    }


    /* end AAC decoder */


    /* SBR decoder */

    /* initiate counter */

#ifndef DISABLE_SBR
    /* open SBR-handle if SBR-Bitstream has been detected in core decoder */
    if ((!sbrDecoderInfo) && streamSBR[0].nrElements) {
      int lpFilter = 0;

      sbrDecoderInfo = openSBR (sampleRate, frameSize, bDownSample, lpFilter);
    }
#endif

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

    if (sampleRate != iOutputSampleRate) {
        iOutputSampleRate = sampleRate;
        iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, 0, false);
    }
    numOutSamples = frameSize;

    //LOG(kCodec, "iSampleRate = %u, iOutputSampleRate = %u\n", iSampleRate, iOutputSampleRate);

    /* end spline resampler */

    if (!aParseOnly && (iFrameCounter > 0)) { // SBR incorrect on AAC+ first frame so skip
        /* interleave time samples */
        InterleaveSamples(&timeData[0],&timeData[2 * SAMPLES_PER_FRAME], (Word16 *)iDecodedBuf.Ptr(),frameSize,&numChannels);
        iDecodedBuf.SetBytes(numOutSamples * iBytesPerSample);
    }
    iFrameCounter++;

    // output samples
    TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
    TUint samplesWritten = 0;
    while (samplesToWrite > 0) {
        TUint bytes = samplesToWrite * (iBitDepth/8) * iChannels;
        TUint samples = samplesToWrite;
        TUint outputSpace = iOutBuf.MaxBytes() - iOutBuf.Bytes();
        if (bytes > outputSpace) {
            samples = outputSpace / (iChannels * (iBitDepth/8));
            bytes = samples * (iBitDepth/8) * iChannels;
        }

        // read from iDecodedBuf into iOutBuf
        BigEndianData(samples, samplesWritten);
        iOutBuf.SetBytes(iOutBuf.Bytes() + bytes);
        if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)(iBitDepth/8) * iChannels) {
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iOutputSampleRate,
                iBitDepth, EMediaDataEndianBig, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        samplesToWrite -= samples;
        samplesWritten += samples;
        iTotalSamplesOutput += samples;
        //LOG(kCodec, "CodecAac::iSamplesWrittenTotal: %llu\n", iTotalSamplesOutput);
    }
}

void CodecAacBase::ProcessHeader()
{
    TUint error = false;
    //LOG(kCodec, "CodecAac::ProcessHeader()\n");

    /* initialize time data buffer */
    for (int i=0; i < 4*SAMPLES_PER_FRAME; i++) {
        timeData[i] = 0;
    }

    /* initialize bit buffer */
    hBitBuf = CreateBitBuffer(&bitBuf, (unsigned char *)iInBuf.Ptr(), (TInt16)iInBuf.MaxBytes());

    aacDecoderInfo =  CAacDecoderOpen(hBitBuf, streamSBR, iSampleRate);

    if (!aacDecoderInfo) {
        error = true;
    }
    
    if (error) {
        //LOG(kCodec, "Error initializing AAC decoder (%d)\n", error);
        THROW(CodecStreamCorrupt);
    }

}

#include <stdio.h>
// fprintf for aacdecoder.c
void AACDebugMessage(const char* pszFmt, ... )
{
    va_list vargs;
    va_start(vargs, pszFmt);
    //LOG(kCodec, pszFmt, vargs);
    va_end(vargs);
}
