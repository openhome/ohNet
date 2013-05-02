#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Os.h>


extern "C" {

#include <pcmfmt.h>
#include <wmaudio.h>

#define MAX_SAMPLES 16384
short g_pLeft [MAX_SAMPLES * 2]; // expand the container for 24-bit samples
short g_pRight [MAX_SAMPLES * 2]; // expand the container for 24-bit samples

tWMAFileHdrState g_hdrstate;
tHWMAFileState g_state;
tWMAFileHeader g_hdr;

} // extern "C"

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecWma : public CodecBase
{
public:
    static const Brn kCodecWma;
public:
    CodecWma();
    ~CodecWma();
    void CopyToBigEndian(TUint aSamples, TUint aBytesPerSample);
    TUint32 Read(const TUint8 **aDataPtr, TUint32 aBytes, TUint64 aOffset, TBool aRecognisingFromBuf);
private:
    private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    Bws<EncodedAudio::kMaxBytes> iRecogBuf;
    Bws<4*1024> iInBuf;          // how big can these go and need to go ?
    Bws<DecodedAudio::kMaxBytes> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;

    TUint64 iWmaReadOffset;
    TUint32 iPcmSamples;
    TUint32 iSampleRate;
    TUint32 iBytesPerSec;
    TUint32 iBitrate;
    TUint32 iDuration;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint16 iBitStorage;
    TUint64 iStartSample;
    TUint64 iSamplesTotal;
    TUint64 iTotalSamplesOutput;
    TUint64 iSeekOffset;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


CodecBase* CodecFactory::NewWma()
{ // static
    return new CodecWma();
}


const Brn CodecWma::kCodecWma("wma");

CodecWma::CodecWma()
{
}

CodecWma::~CodecWma()
{
}

// add data to Wma - ToDo
TBool bDropPacket = FALSE;
TUint16 nDecoderFlags = 0; 
TUint16 nDRCSetting = 0; 
TUint32 nDstChannelMask = 0;
TUint32 nInterpResampRate = 0;
TUint16 nMBRTargetStream = 1;


PCMFormat pcmFormat;

tWMAFileStatus rc;
tWMAExtendedContentDesc const *pECDesc;
TUint16 wMBRTotalStreams = 0;

tWMAFileContDesc const *pdesc = 0;

TBool recognising = FALSE;

CodecWma* iWma = 0;

TBool CodecWma::Recognise(const Brx& aData)
{
    iWma = this;           // temp to allow access to read/peek
    iWmaReadOffset = 0;
    iSeekOffset = 0;
    
    bDropPacket = FALSE;
    nDecoderFlags = 0; 
    nDRCSetting = 0; 
    nDstChannelMask = 0;
    nInterpResampRate = 0;
    nMBRTargetStream = 1;
    wMBRTotalStreams = 0;
    pdesc = 0;

    recognising = TRUE;

    // from original main() for arm...
    // fold-down to 2 channels, -cm 0x03
    // nDecoderFlags  |= DECOPT_CHANNEL_DOWNMIXING;
    nDstChannelMask = (U32) 0x03;

    // resample to 16 bits, -pcm 16
    // nDecoderFlags |= DECOPT_REQUANTTO16;

    // downsample to 44.1 or 48 kHZ
    // nDecoderFlags |= DECOPT_DOWNSAMPLETO44OR48;

    // init struct
    memset ((void *)&g_hdrstate, 0, sizeof(g_hdrstate));
    memset ((void *)&g_state, 0, sizeof(g_state));
    memset ((void *)&g_hdr, 0, sizeof(g_hdr));

    LOG(kCodec, "CodecWma::Recognise\n");

    iRecogBuf.Replace(aData);

    // test the checking API
    try {
        rc = WMAFileSetTargetMBRAudioStream(&g_hdrstate, nMBRTargetStream);

        if(rc != cWMA_NoErr) {
            LOG(kCodec, "WMA Error while setting target stream number.\n");
            return false;
        }

        rc = WMAFileIsWMA(&g_hdrstate);

        if(rc != cWMA_NoErr) {
            LOG(kCodec, " not WMA\n");
            return false;
        }
    }
    catch(CodecStreamCorrupt) {
        LOG(kCodec, "CodecWma::Recognise track is not WMA\n");
        return (false);
    }
    LOG(kCodec, "CodecWma::Recognise track is WMA\n");
    return (true);
}

void CodecWma::StreamInitialise()
{
    recognising = FALSE;
    iSeekOffset = 0;
    iWmaReadOffset = 0; // stream will have been pulled back to start after recognition

    // Check for MBR
    rc = WMAFileMBRAudioStreams(&g_hdrstate, &wMBRTotalStreams);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Error while verifying MBR information.\n");
        THROW(CodecStreamCorrupt);
    }

    if (wMBRTotalStreams > 1)
    {
        LOG(kCodec, "\n** This is an MBR (Multiple Bit Rates) file\n");
        LOG(kCodec, "Decoding audio stream %d out of %d audio streams\n",
            nMBRTargetStream, wMBRTotalStreams);
        LOG(kCodec, "Use -mbr option to decode a different stream\n\n");
    }

    /* init the decoder */

   rc = WMAFileDecodeCreate(&g_state);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Cannot create the WMA decoder.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }
    
    rc = WMAFileDecodeInitEx(g_state, nDecoderFlags, nDRCSetting, bDropPacket,
                             nDstChannelMask, nInterpResampRate, &pcmFormat,
                             nMBRTargetStream);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Cannot initialize the WMA decoder.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }
    
#ifdef WMALOSSLESS_TO_PCM
    rc = WMAFileIsLosslessWMA (g_state);
    if (rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Unsupported input format. Must be WMA Lossless.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }
#else
    rc = WMAFileIsLosslessWMA (g_state);
    if (rc == cWMA_NoErr)
    {
        LOG(kCodec, "** WMA Lossless unsupported.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }
#endif //WMALOSSLESS_TO_PCM
    
    /* get header information */

    rc = WMAFileDecodeInfo (g_state, &g_hdr);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve information.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }

    /* get content description */

    rc = WMAFileContentDesc (g_state, &pdesc);
    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve content description.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }

    rc = WMAFileExtendedContentDesc (g_state, &pECDesc);

    if(rc != cWMA_NoErr)
    {
        LOG(kCodec, "** Failed to retrieve extended content description.\n");
        THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
    }

    iChannels = static_cast<TUint16>(g_hdr.num_channels);
    iSampleRate = g_hdr.sample_rate;
    iBitDepth = g_hdr.valid_bits_per_sample;
    iSamplesTotal = (TUint64)g_hdr.duration * iSampleRate / 1000;
    iTotalSamplesOutput = 0;
    iStartSample = 0;
    iBitrate = g_hdr.bitrate;
    iDuration = g_hdr.duration;

    LOG(kCodec, "++ WMA bitstream version: %d\n", g_hdr.version);
    LOG(kCodec, "++         sampling rate: %ld Hz\n", g_hdr.sample_rate);
    LOG(kCodec, "++         # of channels: %d\n", g_hdr.num_channels);
    LOG(kCodec, "++          WMA bit-rate: %ld bps\n", g_hdr.bitrate);
    LOG(kCodec, "++ valid_bits_per_sample: %ld bits\n", g_hdr.valid_bits_per_sample);
    LOG(kCodec, "++              duration: %ld ms\n", g_hdr.duration);
    LOG(kCodec, "++           DRM content: %s\n", g_hdr.has_DRM ? "Yes" : "No");
    LOG(kCodec, "++         iSamplesTotal: %lld\n", iSamplesTotal);

    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);
    iPcmSamples = 0;

    iBytesPerSample = iChannels*iBitDepth/8;
    iBytesPerSec = iSampleRate * iBytesPerSample;

    iTrackLengthJiffies = (iDuration * static_cast<TUint64>(Jiffies::kJiffiesPerSecond)) / 1000;
    iTrackOffset = 0;

    LOG(kCodec, "CodecWma::StreamInitialise  iBitDepth %u, iSampleRate %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitDepth, iSampleRate, iSamplesTotal, iChannels, iTrackLengthJiffies);
    // Don't seem to support lossless at the moment, so always report lossy.
    iController->OutputDecodedStream(iBitrate, iBitDepth, iSampleRate, iChannels, kCodecWma, iTrackLengthJiffies, 0, false);
}

void CodecWma::Process() 
{
    LOG(kCodec, "CodecWma::Process\n");
    //LOG(kCodec, "CodecWma::Process  (start time = %d)\n", OpenHome::Os::TimeInMs(gEnv->OsCtx())/1000);
    TBool newStreamStarted = false;
    TBool streamEnded = false;
    const TUint bytesPerWMAPCMSample = 2 * iChannels; // 16bit * 2 channels    - alter for 24bit WMA - ToDo
    //const TUint bytesPerPCMSample = iChannels*iBitDepth / 8;
    const TUint samplesPerMsg = DecodedAudio::kMaxBytes/bytesPerWMAPCMSample;
    TUint32 decodedSamples=0;

    TInt64  presTime = 0;   // for curiosity only

    TUint32 t1 = 0;
    TUint32 t2 = 0;
    TUint32 t3 = 0;
    TUint32 t4 = 0;
    TUint timeStart;
    TUint timeEnd;
    timeEnd =  OpenHome::Os::TimeInMs(gEnv->OsCtx());

    try {
        timeStart = OpenHome::Os::TimeInMs(gEnv->OsCtx());
        t4 += timeStart-timeEnd;    //log time between main functions

        do {
            rc = WMAFileDecodeData(g_state, reinterpret_cast<tWMA_U32*>(&decodedSamples));
        } while ((rc == cWMA_NoErr) && (decodedSamples == 0)); //wait until something decoded

        if(rc != cWMA_NoErr)
        {
            if ( rc == cWMA_NoMoreFrames )
            {
                LOG(kCodec, " WMAFileDecodeData complete - cWMA_NoMoreFrames\n");
                streamEnded = true;
            }
            else if (rc == cWMA_Failed )
            {
                LOG(kCodec, " WMAFileDecodeData complete - cWMA_Failed\n");
                newStreamStarted = true;
            }
            else {
                LOG(kCodec, "DECODING ERR: decoding failed %d, %lld", rc, iTotalSamplesOutput);
                THROW(CodecStreamCorrupt);                           // use more suitable exception !!!
            }            
        }
        timeEnd =  OpenHome::Os::TimeInMs(gEnv->OsCtx());
        t1 += timeEnd-timeStart;
        if((timeEnd-timeStart) > 1000) {
            //LOG(kCodec, " ----------------------------------- WMAFileDecodeData taken %ums\n", timeEnd-timeStart);
        }

        // output samples
        while(decodedSamples != 0) {
            // translate samples into interleaved buffer
            TInt16* dest = (TInt16*)(iDecodedBuf.Ptr() + iDecodedBuf.Bytes());
            TUint32 bytesAvail = iDecodedBuf.MaxBytes() - iDecodedBuf.Bytes();

            //WMAFileGetPCM cannot process < 16 samples, so ensure last block > 16
            TInt32 samplesEstimate = bytesAvail/bytesPerWMAPCMSample;
            samplesEstimate -= (samplesEstimate%16);
            samplesEstimate = decodedSamples - samplesEstimate;
            if((samplesEstimate > 0) && (samplesEstimate <= 16)) {
                bytesAvail -= (16 * bytesPerWMAPCMSample);      // ensure > 16 samples remain for next loop
            }

            timeStart = OpenHome::Os::TimeInMs(gEnv->OsCtx());
            t4 += timeStart-timeEnd;    //log time between main functions
            TUint32 samples = WMAFileGetPCM (g_state, dest, 0, bytesAvail, decodedSamples, &presTime);

            timeEnd =  OpenHome::Os::TimeInMs(gEnv->OsCtx());
            t2 += timeEnd-timeStart;
            if((timeEnd-timeStart) > 1000) {
                //LOG(kCodec, " ----------------------------------- WMAFileGetPCM taken %ums\n", timeEnd-timeStart);
            }
            ASSERT(samples != 0);

            iPcmSamples += samples;
            iDecodedBuf.SetBytes(iPcmSamples * bytesPerWMAPCMSample);

            decodedSamples -= samples;

            timeStart = OpenHome::Os::TimeInMs(gEnv->OsCtx());
            t4 += timeStart-timeEnd;    //log time between main functions
            while(iPcmSamples >= samplesPerMsg) {
                CopyToBigEndian(samplesPerMsg, bytesPerWMAPCMSample);

                // Check that the amount we're outputting is not including extra samples to be processed next time around.
                iTrackOffset += iController->OutputAudioPcm(iDecodedBuf, iChannels, iSampleRate, iBitDepth, EMediaDataLittleEndian, iTrackOffset);
                iTotalSamplesOutput += samplesPerMsg;
                iOutBuf.SetBytes(0);

                LOG(kCodec, "CodecWma iTotalSamplesOutput = %llu\n", iTotalSamplesOutput);

                // shift remaining data to start of pcm buffer
                iPcmSamples -= samplesPerMsg;
                memmove((void*)iDecodedBuf.Ptr(), (const void*)(iDecodedBuf.Ptr() + (samplesPerMsg * bytesPerWMAPCMSample)), iPcmSamples * bytesPerWMAPCMSample);
                iDecodedBuf.SetBytes(iPcmSamples * bytesPerWMAPCMSample);
            }

            timeEnd =  OpenHome::Os::TimeInMs(gEnv->OsCtx());
            t3 += timeEnd-timeStart;
            if((timeEnd-timeStart) > 1000) {
                //LOG(kCodec, " ----------------------------------- Output taken %dms\n", timeEnd-timeStart);                
            }
        }
    }
    catch (CodecStreamEnded) {
        streamEnded = true;
    }
    catch (CodecStreamStart) {
        newStreamStarted = true;
    }

    //LOG(kCodec, "CodecWma::Process time: %u, %u, %u, %u (end time = %u)\n", t1/1000, t2/1000, t3/1000, t4/1000, OpenHome::Os::TimeInMs(gEnv->OsCtx())/1000);

    // flush any remaining samples from the decoded buffer
    if ((streamEnded || newStreamStarted)) {
        if (iPcmSamples) {
            CopyToBigEndian(iPcmSamples, bytesPerWMAPCMSample);
            iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate, iBitDepth, EMediaDataBigEndian, iTrackOffset);
            iOutBuf.SetBytes(0);
            iTotalSamplesOutput += iPcmSamples;
            LOG(kCodec, "CodecWma iTotalSamplesOutput = %llu\n", iTotalSamplesOutput);
        }
        if (newStreamStarted) {
            THROW(CodecStreamStart);
        }
        THROW(CodecStreamEnded);
    }

    LOG(kCodec, "CodecWma::Process Exit\n");
}

void CodecWma::StreamCompleted()
{
    LOG(kCodec, "CodecWma::Deinitialise\n");

    WMAFileDecodeClose(&g_state);
}


TBool CodecWma::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecWma::Seek(%u, %llu)\n", aStreamId, aSample);

    TUint seconds = static_cast<TUint>(aSample/iSampleRate);
    tWMA_U32 actualSeconds;
    tWMAFileStatus rv;
    // this will read a few bytes from the start of the file and determine the approximate offset into
    // the file that corresponds to the supplied time, will then seek from that offset
    // The decoder expects to be working on a flat file structure and uses absolute positioning in the file,
    // so use iSeekOffset to compensate for the partial get offset.
    rv = WMAFileSeek (g_state, seconds*1000, &actualSeconds, &iSeekOffset); // sets pInt->hdr_parse.nextPacketOffset to start of decode
    if(rv) {
        THROW(CodecStreamCorrupt);
    }

    LOG(kCodec, "CodecWma::Seek to sample: %llu, second: %u, byte: %llu\n", aSample, actualSeconds, iSeekOffset);
    TBool canSeek = iController->TrySeek(aStreamId, iSeekOffset);
    if (canSeek) {
        iWmaReadOffset = 0;
        iTotalSamplesOutput = aSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iSampleRate;
        iController->OutputDecodedStream(iBitrate, iBitDepth, iSampleRate, iChannels, kCodecWma, iTrackLengthJiffies, aSample, false);
    }
    return canSeek;
}

// copy audio data from decoded buffer to output buffer, converting to big endian if required.
void CodecWma::CopyToBigEndian(TUint aSamples, TUint aBytesPerSample)
{
    // FIXME - adapt for 24 bit streams too
    TByte* dstByte = const_cast<TByte*>(iOutBuf.Ptr());
    TInt16* dst = reinterpret_cast<TInt16*>(dstByte);
    TByte* srcByte = const_cast<TByte*>(iDecodedBuf.Ptr());
    TInt16* src = reinterpret_cast<TInt16*>(srcByte);
    TUint samples = aSamples*iChannels;
    while(samples--) {
        *dst++ = Arch::BigEndian2(*src++);
    }
    iOutBuf.SetBytes(aSamples*aBytesPerSample);
}

TUint32 CodecWma::Read(const TUint8 **aDataPtr, TUint32 aBytes, TUint64 aOffset, TBool aRecognisingFromBuf)
{
    //LOG(kCodec, ">Wma::Read %u bytes at %llu.\n", aBytes, aOffset);
    aOffset -= static_cast<TUint32>(iSeekOffset); // offset to the seeked position
    iInBuf.SetBytes(0);

    if (iRecogBuf.Bytes() < aOffset || iRecogBuf.Bytes()-aOffset < aBytes) {
        // going to exhaust buffer, so should read from controller instead
        aRecognisingFromBuf = false;
    }

    if (aRecognisingFromBuf) {
        //LOG(kCodec, "CodecWma::Read peeking from buffer\n");
        ASSERT(iRecogBuf.Bytes() > 0);  // check buffer has been initialised
        Brn tmpBuf = iRecogBuf.Split(static_cast<TUint>(aOffset), aBytes);
        iInBuf.Replace(tmpBuf);
    }
    else {
        //LOG(kCodec, "CodecWma::Read reading from controller\n");
        if (aOffset != iWmaReadOffset) {
            // LOG(kCodec, "Wma::Read skipping %llu bytes\n", aOffset - iWmaReadOffset);
            // reading of the stream is sequential so dump any sections that are not required
            TUint64 skipTotal = aOffset-iWmaReadOffset;
            while (skipTotal > 0) {
                TUint64 skipBytes = skipTotal;
                if (skipBytes > iInBuf.MaxBytes()) {
                    skipBytes = iInBuf.MaxBytes();
                }
                iController->Read(iInBuf, static_cast<TUint>(skipBytes));
                iInBuf.SetBytes(0);
                skipTotal -= skipBytes;
            }
            iWmaReadOffset = aOffset;
        }
        iController->Read(iInBuf, aBytes);
        iWmaReadOffset += iInBuf.Bytes();
    }
    *aDataPtr = iInBuf.Ptr();

    // LOG(kCodec, "<CodecWma::Read: [%x][%x], next read at %llu\n", (int)**aDataPtr, (int)*(*aDataPtr+1), iWmaReadOffset);
    return iInBuf.Bytes();
}


tWMA_U32 WMAFileCBGetData(
    tHWMAFileState state,
    tWMA_U64 offset,
    tWMA_U32 num_bytes,
    tWMA_U8  **ppData)
{
    LOG(kCodec, "WMAFileCBGetData state %d, offset %llu, num_bytes %u\n", state, offset, num_bytes);
    ASSERT(iWma);
    TUint32 bytes = iWma->Read((const TUint8 **)ppData, num_bytes, offset, recognising);
    LOG(kCodec, "WMAFileCBGetData bytes %d\n", bytes);
    return(bytes);
}


#include <stdio.h>
// fprintf for wmaudio.c and wmaudio_parse.c
void WMADebugMessage(const char* pszFmt, ... )
{
    va_list vargs;
    va_start(vargs, pszFmt);
    LOG(kCodec, pszFmt, vargs);
    va_end(vargs);
}
