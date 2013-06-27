#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

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


namespace OpenHome {
namespace Media {
namespace Codec {

class Adts
{
public:
    Adts();
    TBool   ReadHeader(Brn aHeader);
    TUint16 Profile() { return(iProfile); }
    TUint16 ChannelConfig() { return(iChannelConfig); }
    TUint32 SamplingFreq() { return(iSamplingFreq); }
    TUint32 PayloadBytes() { return(iPayloadBytes); }
    TUint32 HeaderBytes() { return(iHeaderBytes); }
    TUint32 StartOffset() { return(iStartOffset); }
    void SetStartOffset(TUint32 aStartOffset) { iStartOffset = aStartOffset; }
    TUint32 PayloadBytesAve() { return iPayloadBytesAve; }
    void SetPayloadBytesAve(TUint32 aPayloadBytesAve) { iPayloadBytesAve = aPayloadBytesAve; }
private:
    TUint8  iProfile;
    TUint8  iChannelConfig;
    TUint32 iSamplingFreq;
    TUint32 iPayloadBytes;
    TUint32 iHeaderBytes;
    TUint32 iStartOffset;
    TUint32 iPayloadBytesAve;
};

class CodecAac : public CodecBase
{
public:
    static const Brn kCodecAac;
public:
    CodecAac();
    ~CodecAac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    void ProcessHeader();
    void BigEndianData(TUint toWrite, TUint samplesWritten);
    void ProcessMpeg4();
    void ProcessAdts(TBool aParseOnly);
    void FlushOutput();
    void DecodeFrame(TBool aParseOnly);
    TUint SkipEsdsTag(const TByte& aPtr);

    Brn iName;
    Bws<4*1024> iInBuf;          // how big can these go and need to go ?
    Bws<16*10240> iDecodedBuf;
    Bws<DecodedAudio::kMaxBytes> iOutBuf;
    Mpeg4MediaInfo* iMp4;
    TUint32 iAudioBytes;
    TBool iAacMpeg4Format;
    TUint iFrameCounter;
    Adts iAdts;

    TUint32 iSampleRate;
    TUint32 iOutputSampleRate;
    TUint32 iBitrateMax;    
    TUint32 iBitrateAverage;
    TUint16 iChannels;
    TUint16 iBytesPerSample;
    TUint16 iBitDepth;
    TUint64 iSamplesTotal;
    TUint64 iCurrentSample;
    TUint64 iTotalSamplesOutput;
    TUint64 iTrackLengthJiffies;
    TUint64 iTrackOffset;

    TBool iNewStreamStarted;
    TBool iStreamEnded;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAac()
{ // static
    return new CodecAac();
}


const Brn CodecAac::kCodecAac("mp4a");

CodecAac::CodecAac()
    : iMp4(NULL)
{
    //LOG(kCodec, "CodecAac::CodecAac\n");
}

CodecAac::~CodecAac()
{
    //LOG(kCodec, "CodecAac::~CodecAac\n");
    if (iMp4) {
        delete iMp4;
    }
}

Adts::Adts(): iPayloadBytesAve(0)
{ 
} 

// ref ISO-IEC-13818-7 p21
TBool Adts::ReadHeader(Brn aHeader) 
{
    iProfile = 0;
    iSamplingFreq = 0;
    iChannelConfig = 0;
    iPayloadBytes = 0;

    if(aHeader.Bytes() < 6) {
        //LOG(kCodec, "header too small %d\n", aHeader.Bytes());
        return false;
    }

    //LOG(kCodec, "Adts::Header @0x%x, Bytes = %d ", aHeader.Ptr(), aHeader.Bytes());
    //LOG(kCodec, "[%x][%x][%x][%x][%x][%x]\n", aHeader[0], aHeader[1], aHeader[2], aHeader[3], aHeader[4], aHeader[5]);

    if((aHeader[0] != 0xff) || ((aHeader[1] & 0xf0) != 0xf0)) {
        return false;                   // invalid ADTS frame marker
    }
    //LOG(kCodec, "Adts::Header Sync found\n");

    if ((aHeader[1] & 0x06) != 0x00) {  // layer; should always be 0
        return false;
    }

    iHeaderBytes = 7;
    if((aHeader[1] & 0x01) == 0) {
        //LOG(kCodec, " CRC present\n");
        iHeaderBytes += 2;             // skip CRC bytes (should do CRC - ToDo)
    }
    iPayloadBytes = ((aHeader[3] & 0x03) << 11) | (aHeader[4] << 3) | ((aHeader[5] & 0xE0) >> 5);
    if(iPayloadBytes < iHeaderBytes) {
        //LOG(kCodec, " iPayloadBytes error %d\n", iPayloadBytes);
        return false;                   // size is invalid
    }
    iPayloadBytes -= iHeaderBytes;                 // remove header size
    iProfile = (aHeader[2] & 0xC0) >> 6;

    TUint sf = (aHeader[2] & 0x3C) >> 2;
    switch (sf) {
        case 0:
            iSamplingFreq = 96000;
            break;
        case 1:
            iSamplingFreq = 88200;
            break;
        case 2:
            iSamplingFreq = 64000;
            break;
        case 3:
            iSamplingFreq = 48000;
            break;
        case 4:
            iSamplingFreq = 44100;
            break;
        case 5:
            iSamplingFreq = 32000;
            break;
        case 6:
            iSamplingFreq = 24000;
            break;
        case 7:
            iSamplingFreq = 22050;
            break;
        case 8:
            iSamplingFreq = 16000;
            break;
        case 9:
            iSamplingFreq = 12000;
            break;
        case 10:
            iSamplingFreq = 11025;
            break;
        case 11:
            iSamplingFreq = 8000;
            break;
        case 12:
            iSamplingFreq = 7350;
            break;
        default:
            //LOG(kCodec, " sample freq error %d\n", sf);
            return false;   // invalid sample frequency
    }

    iChannelConfig = ((aHeader[2] & 0x01) << 2) | ((aHeader[3] & 0xC0) >> 6);

    //LOG(kCodec, "Adts::Header iPayloadBytes %d, iProfile %d, iSamplingFreq %d, iChannelConfig %d\n", iPayloadBytes, iProfile, iSamplingFreq, iChannelConfig);

    return true;
}

TBool CodecAac::Recognise(const Brx& aData)
{
    LOG(kCodec, "CodecAac::Recognise\n");
    const TUint kAdtsConsecutiveFrames = 5; // limit this to allow recognition within 1 data message
    Bws<4> codec;
    iAacMpeg4Format = false;

    try {
        Mpeg4MediaInfo::GetCodec(aData, codec);
    }
    catch (MediaMpeg4FileInvalid) {
        // We couldn't recognise this as an MPEG4/AAC file.
        // don't return here; attempt adts recognition below
    }

    if (codec == kCodecAac) {
        LOG(kCodec, "CodecAlac::Recognise aac mp4a\n");
        iAacMpeg4Format = true;
        return true;
    }

    // attempt Adts recognition
    for(TUint i = 0; i < aData.Bytes(); i++) {
        iAdts.SetStartOffset(i);                // save potential start position for first frame
        
        Adts adts;
        TUint matched = 0;        
        TUint j = i;
        TUint payloadBytes = 0;
        while((j+9) < aData.Bytes()) {           // ensure there are enough bytes for the maximum header size
            if(!adts.ReadHeader(Brn(aData.Ptr()+j, aData.Bytes()-j))) {
                break;                          // not a valid header so keep searching
            }
            payloadBytes += adts.PayloadBytes();
            if(++matched >= kAdtsConsecutiveFrames) {   // found enough consecutive valid frames
                if(!iAdts.ReadHeader(Brn(aData.Ptr()+iAdts.StartOffset(), aData.Bytes()-iAdts.StartOffset()))) {    // save info from first frame
                    break;                          // not a valid header so keep searching
                }
                iAdts.SetPayloadBytesAve(payloadBytes / kAdtsConsecutiveFrames);	// record average payload size over 3 frames
                LOG(kCodec, "CodecAlac::Recognise aac adts\n");
                return true;      
            }
            
            j += adts.PayloadBytes() + adts.HeaderBytes();   // point to where next frame should be
        }
        if (i > 1000) {
            break;      // searched far enough
        }
    }

    return false;
}

TUint CodecAac::SkipEsdsTag(const TByte& aPtr)
{
    switch(aPtr) {
        case 0x80:
        case 0x81:
        case 0xFE:
            return 3;
        default:
            return 0;
    }
}

void CodecAac::StreamInitialise()
{
    //this assumes that we have an MPEG4 header - modify for raw data files !!!
    //LOG(kCodec, "CodecAac::StreamInitialise\n");

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

    iCurrentSample = 0;
    iTotalSamplesOutput = 0;

    iInBuf.SetBytes(0);
    iDecodedBuf.SetBytes(0);
    iOutBuf.SetBytes(0);

    if(iAacMpeg4Format) {
        Bws<64> info;
        info.SetBytes(0);

        iMp4 = new Mpeg4MediaInfo(*iController);

        info.Append(iMp4->CodecSpecificData());   // get data extracted from MPEG-4 header
        // see http://wiki.multimedia.cx/index.php?title=Understanding_AAC for details
        // or http://xhelmboyx.tripod.com/formats/mp4-layout.txt - search for 'esds'

        // also see APar_Extract_esds_Info() in
        //          http://m4sharp.googlecode.com/svn-history/r3/trunk/m4aSharp/m4aSharp/AP_AtomExtracts.cpp
        // and
        //          http://www.jthink.net/jaudiotagger/javadoc/org/jaudiotagger/audio/mp4/atom/Mp4EsdsBox.html
/*
 EsdsBox ( stream specific description box), usually holds the Bitrate/No of Channels

It contains a number of (possibly optional?) sections (section 3 - 6) (containing optional filler) with differeent info in each section.

-> 4 bytes version/flags = 8-bit hex version + 24-bit hex flags (current = 0)

Section 3 -> 1 byte ES descriptor type tag = 8-bit hex value 0x03
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 2 bytes ES ID = 16-bit unsigned value
    -> 1 byte stream priority = 8-bit unsigned value - Defaults to 16 and ranges from 0 through to 31

Section 4 -> 1 byte decoder config descriptor type tag = 8-bit hex value 0x04
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length *
    -> 1 byte object type ID = 8-bit unsigned value
                            - type IDs are system v1 = 1 ; system v2 = 2
                            - type IDs are MPEG-4 video = 32 ; MPEG-4 AVC SPS = 33
                            - type IDs are MPEG-4 AVC PPS = 34 ; MPEG-4 audio = 64
                            - type IDs are MPEG-2 simple video = 96
                            - type IDs are MPEG-2 main video = 97
                            - type IDs are MPEG-2 SNR video = 98
                            - type IDs are MPEG-2 spatial video = 99
                            - type IDs are MPEG-2 high video = 100
                            - type IDs are MPEG-2 4:2:2 video = 101
                            - type IDs are MPEG-4 ADTS main = 102
                            - type IDs are MPEG-4 ADTS Low Complexity = 103
                            - type IDs are MPEG-4 ADTS Scalable Sampling Rate = 104
                            - type IDs are MPEG-2 ADTS = 105 ; MPEG-1 video = 106
                            - type IDs are MPEG-1 ADTS = 107 ; JPEG video = 108
                            - type IDs are private audio = 192 ; private video = 208
                            - type IDs are 16-bit PCM LE audio = 224 ; vorbis audio = 225
                            - type IDs are dolby v3 (AC3) audio = 226 ; alaw audio = 227
                            - type IDs are mulaw audio = 228 ; G723 ADPCM audio = 229
                            - type IDs are 16-bit PCM Big Endian audio = 230
                            - type IDs are Y'CbCr 4:2:0 (YV12) video = 240 ; H264 video = 241
                            - type IDs are H263 video = 242 ; H261 video = 243

    -> 6 bits stream type = 3/4 byte hex value - type IDs are object descript. = 1 ; clock ref. = 2 - type IDs are scene descript. = 4 ; visual = 4 - type IDs are audio = 5 ; MPEG-7 = 6 ; IPMP = 7 - type IDs are OCI = 8 ; MPEG Java = 9 - type IDs are user private = 32
    -> 1 bit upstream flag = 1/8 byte hex value
    -> 1 bit reserved flag = 1/8 byte hex value set to 1
    -> 3 bytes buffer size = 24-bit unsigned value
    -> 4 bytes maximum bit rate = 32-bit unsigned value
    -> 4 bytes average bit rate = 32-bit unsigned value

Section 5 -> 1 byte decoder specific descriptor type tag 8-bit hex value 0x05
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 1 byte Audio profile Id - 5 bits Profile Id - 3 bits Unknown
    -> 8 bits other flags - 3 bits unknown - 2 bits is No of Channels - 3 bits unknown

Section 6
    -> 1 byte SL config descriptor type tag = 8-bit hex value 0x06
    -> 3 bytes optional extended descriptor type tag string = 3 * 8-bit hex value - types are 0x80,0x81,0xFE
    -> 1 byte descriptor type length = 8-bit unsigned length
    -> 1 byte SL value = 8-bit hex value set to 0x02

    Valid Type ID seen for aac is "MPEG-4 audio" - not sure if any others are used so no checking for this is done
*/
        iChannels = 0;
        const TByte *ptr = info.Ptr();
        ptr += 4;

        if(*ptr == 3) {     // section 3
            ptr++;
            ptr += SkipEsdsTag(*ptr);
            if(*ptr != 0) {
                ptr += 4;
                if(*ptr == 4) {     // section 4
                    ptr++;
                    ptr += SkipEsdsTag(*ptr);
                    if(*ptr != 0) {
                        ptr++; //ObjectTypeIndication
                        ptr++; // a_v_flag
                        ptr += 4;
                            //extract bitrates
                        iBitrateMax = *(TUint32*)(ptr);
                        ptr += 4;
                        iBitrateAverage = *(TUint32*)(ptr);
                        ptr += 4;
                        if(*ptr == 5) {     // section 5
                            ptr++;
                            ptr += SkipEsdsTag(*ptr);
                            if(*ptr != 0) {
                                ptr += 2;
                                iChannels = (*ptr >> 3) & 0xf;
                            }
                        }

                    }
                }
            }
        }

        //LOG(kCodec, " iBitrateMax %d, iBitrateAverage %d\n", iBitrateMax, iBitrateAverage);


        //LOG(kCodec, "Aac::Initialise channels = %d, timescale %d, samplerate %d\n", iMp4->Timescale(), iMp4->SampleRate());

        iSampleRate = iMp4->Timescale();
        iOutputSampleRate = iSampleRate;
        iBitDepth = iMp4->BitDepth();
        //iChannels = iMp4->Channels();     // not valid !!!
        iSamplesTotal = iMp4->Duration();

        iBytesPerSample = iChannels*iBitDepth/8;
        //LOG(kCodec, "iSampleRate: %u, iSamplesTotal: %llu, iBytesPerSample: %u\n", iSampleRate, iSamplesTotal, iBytesPerSample);
        ProcessHeader();
    }
    else {
        iChannels = iAdts.ChannelConfig() == 0 ? 2 : iAdts.ChannelConfig();
        iSampleRate = iAdts.SamplingFreq();

        TUint rate;
        TUint incr;
        rate = (iSampleRate * iAdts.PayloadBytesAve() / 1000) * 8;
        // round bitrate to a standard value, eg 48, 56, 64, 80, 92 ...
        if(rate < 9000) incr = 1000;
        else if(rate < 18000) incr = 2000;
        else if(rate < 36000) incr = 4000;
        else if(rate < 72000) incr = 8000;
        else if(rate < 144000) incr = 16000;
        else if(rate < 288000) incr = 32000;
        else if(rate < 576000) incr = 64000;
        else incr = 128000;

        rate = (rate + (incr/2))/incr * incr;

        iBitrateAverage = rate;
        iBitrateMax = iBitrateAverage;

        iBitDepth = 16;
        iSamplesTotal = 0;  // stream

        iBytesPerSample = iChannels*iBitDepth/8;

        ProcessHeader();

        iInBuf.SetBytes(0);
        iController->Read(iInBuf, iAdts.StartOffset());  // skip to first frame header

        ProcessAdts(true);  //process first 2 frames to get iOutputSampleRate from the decoder
    }

    iTrackLengthJiffies = (iSamplesTotal * Jiffies::kJiffiesPerSecond) / iSampleRate;
    iTrackOffset = 0;

    //LOG(kCodec, "CodecAac::StreamInitialise  iBitDepth %u, iSamplesTotal %lld, iChannels %u, iTrackLengthJiffies %u\n", iBitDepth, iMp4->Duration(), iChannels(), iTrackLengthJiffies);
    iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, 0, false);
}

void CodecAac::StreamCompleted()
{
    //LOG(kCodec, "CodecAac::StreamCompleted\n");
}

TBool CodecAac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    //LOG(kCodec, "CodecAac::Seek(%lld)\n", aSample);
    TUint64 startSample;

    TUint64 bytes = iMp4->GetSeekTable().Offset(aSample, startSample);     // find file offset relating to given audio sample
    //LOG(kCodec, "CodecAac::Seek to sample: %lld, byte: %lld\n", iStartSample, bytes);
    TBool canSeek = iController->TrySeek(aStreamId, bytes);
    if (canSeek) {
        iTotalSamplesOutput = aSample;
        iCurrentSample = startSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iMp4->SampleRate();
        iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iMp4->SampleRate(), iChannels, kCodecAac, iTrackLengthJiffies, aSample, false);
    }
    return canSeek;
}

void CodecAac::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);
    TUint i=0;

    switch(iBitDepth) {
        case 8:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                *dst++ = *src++;
            }
            break;
        case 16:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                TInt16 tmp = Arch::BigEndian2((src[1] << 8) | src[0]);
                TByte* tmpPtr = reinterpret_cast<TByte*>(&tmp);
                *dst++ = *tmpPtr++;
                *dst++ = *tmpPtr++;
                src += 2;
            }
            break;
        case 24:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                TInt16 tmp = Arch::BigEndian2((src[2] << 8) | src[0]);
                TByte* tmpPtr = reinterpret_cast<TByte*>(&tmp);
                *dst++ = *tmpPtr++;
                *dst++ = src[1];
                *dst++ = *tmpPtr++;
                src += 3;
            }
            break;
        default:
            ASSERTS();
    }
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
  }

}

void CodecAac::Process()
{
    if(iAacMpeg4Format) {
        ProcessMpeg4();
    }
    else {
        ProcessAdts(false);
    }

    if (iNewStreamStarted) {
        THROW(CodecStreamStart);
    }
    if (iStreamEnded) {
        THROW(CodecStreamEnded);
    }
}


void CodecAac::ProcessMpeg4() 
{
    //LOG(kCodec, "CodecAac::Process\n");
    if (iCurrentSample < iMp4->GetSampleSizeTable().Count()) {

        // read in a single aac sample
        iInBuf.SetBytes(0);

        try {
            //LOG(kCodec, "CodecAac::Process  sample = %u, size = %u, inBuf max size %u\n", iCurrentSample, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample), iInBuf.MaxBytes());
            iController->Read(iInBuf, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample));
            //LOG(kCodec, "CodecAac::Process  read iInBuf.Bytes() = %u\n", iInBuf.Bytes());
            iCurrentSample++;
        }
        catch (CodecStreamStart&) {
            iNewStreamStarted = true;
            //LOG(kCodec, "CodecAlac::ProcessMpeg4 caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            //LOG(kCodec, "CodecAlac::ProcessMpeg4 caught CodecStreamEnded\n");
        }

        // now decode and output
        DecodeFrame(false);
    }
    else {
        iStreamEnded = true;
    }
    FlushOutput();
}

void CodecAac::ProcessAdts(TBool aParseOnly)
{
    Adts adts;
    TUint count = 0;
    TUint total = 0;
    //LOG(kCodec, "Aac::ProcessAdts - Parse Only = %d\n", aParseOnly);

    if (!aParseOnly) {
        total = 1;
    }
    else if (iFrameCounter < 2) {
        total = 2-iFrameCounter;
    }

    while (count < total) {
        // read in a single aac frame at a time
        try {
            TUint headerBytes = 7;
            iInBuf.SetBytes(0);
            iController->Read(iInBuf, headerBytes);
            if (iInBuf.Bytes() < headerBytes) {
                THROW(CodecStreamEnded);
            }
            if(!adts.ReadHeader(Brn(iInBuf))) {        // read and process header
                THROW(CodecStreamCorrupt);
            }
            if(adts.HeaderBytes() > 7) {
                iInBuf.SetBytes(0);
                iController->Read(iInBuf, adts.HeaderBytes()-7);   // skip any extra header info (i.e. CRC)
            }
            iInBuf.SetBytes(0);
            //LOG(kCodec, "Aac::Process Adts  size = %u, inBuf max size %u\n", adts.PayloadBytes(), iInBuf.MaxBytes());
            iController->Read(iInBuf, adts.PayloadBytes());
            //LOG(kCodec, "Aac::Process  read iInBuf.Bytes() = %u\n", iInBuf.Bytes());
        }
        catch (CodecStreamStart&) {
            iNewStreamStarted = true;
            //LOG(kCodec, "CodecAlac::ProcessAdts caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            //LOG(kCodec, "CodecAlac::ProcessAdts caught CodecStreamEnded\n");
        }

        DecodeFrame(aParseOnly);
        count++;
    }

    if(!aParseOnly) {
        FlushOutput();
    }
}

// flush any remaining samples from the decoded buffer
void CodecAac::FlushOutput()
{    
    if ((iStreamEnded || iNewStreamStarted) && iOutBuf.Bytes() > 0) {
        iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iOutputSampleRate,
            iBitDepth, EMediaDataBigEndian, iTrackOffset);
        iOutBuf.SetBytes(0);
    }
    //LOG(kCodec, "CodecAac::Process complete - total samples = %lld\n", iTotalSamplesOutput);
}

void CodecAac::DecodeFrame(TBool aParseOnly)
{
    TUint error = false;
    TInt16 frameSize = 0;
    TInt32 sampleRate = 0;
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


    iOutputSampleRate = sampleRate;
    numOutSamples = frameSize;

    //LOG(kCodec, "iSampleRate = %u, iOutputSampleRate = %u\n", iSampleRate, iOutputSampleRate);

    /* end spline resampler */

    if (!aParseOnly && (iFrameCounter > 0)) { // SBR incorrect on AAC+ first frame so skip
        /* interleave time samples */
        interleaveSamples(&timeData[0],&timeData[2 * SAMPLES_PER_FRAME], (Word16 *)iDecodedBuf.Ptr(),frameSize,&numChannels);
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
                iBitDepth, EMediaDataBigEndian, iTrackOffset);
            iOutBuf.SetBytes(0);
        }
        samplesToWrite -= samples;
        samplesWritten += samples;
        iTotalSamplesOutput += samples;
        //LOG(kCodec, "CodecAac::iSamplesWrittenTotal: %llu\n", iTotalSamplesOutput);
    }
}

void CodecAac::ProcessHeader()
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
