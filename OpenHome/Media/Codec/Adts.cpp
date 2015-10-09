#include <OpenHome/Media/Codec/AacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

namespace OpenHome {
namespace Media {
    class IMimeTypeList;
namespace Codec {

class Adts
{
private:
    static const TUint kMaxAacFramesPerFrame = 1;   // This code only supports 1 AAC frame per ADTS frame.
public:
    Adts();
    TBool ReadHeader(Brn aHeader);
    TUint Profile() { return(iProfile); }
    TUint ChannelConfig() { return(iChannelConfig); }
    TUint SamplingFreq() { return(iSamplingFreq); }
    TUint PayloadBytes() { return(iPayloadBytes); }
    TUint AacFrames() { return iAacFrames; }
    TUint HeaderBytes() { return(iHeaderBytes); }
    TUint StartOffset() { return(iStartOffset); }
    void SetStartOffset(TUint aStartOffset) { iStartOffset = aStartOffset; }
    TUint PayloadBytesAve() { return iPayloadBytesAve; }
    void SetPayloadBytesAve(TUint aPayloadBytesAve) { iPayloadBytesAve = aPayloadBytesAve; }
private:
    TUint  iProfile;
    TUint  iChannelConfig;
    TUint iSamplingFreq;
    TUint iPayloadBytes;
    TUint iAacFrames;
    TUint iHeaderBytes;
    TUint iStartOffset;
    TUint iPayloadBytesAve;
};

class CodecAdts : public CodecAacBase
{
public:
    CodecAdts(IMimeTypeList& aMimeTypeList);
    ~CodecAdts();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo) override;
    void StreamInitialise() override;
    void Process() override;
    //TBool TrySeek(TUint aStreamId, TUint64 aSample) override;
    //void StreamCompleted() override;
private:
    void ProcessAdts(TBool aParseOnly);
private:
    static const TUint kMaxRecogBytes = 6 * 1024; // copied from previous CodecController behaviour
    Bws<kMaxRecogBytes> iRecogBuf;
    Adts iAdts;
};

} //namespace Codec
} //namespace Media
} //namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAdts(IMimeTypeList& aMimeTypeList)
{ // static
    return new CodecAdts(aMimeTypeList);
}


// Adts

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
    iAacFrames = 0;

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

    iPayloadBytes = ((aHeader[3] & 0x03) << 11) | (aHeader[4] << 3) | ((aHeader[5] & 0xE0) >> 5);
    if(iPayloadBytes < iHeaderBytes) {
        //LOG(kCodec, " iPayloadBytes error %d\n", iPayloadBytes);
        return false;                   // size is invalid
    }
    iPayloadBytes -= iHeaderBytes;                 // remove header size

    //iBufferFullness = (((aHeader[5] & 0x1F) << 6) | ((aHeader[6] & 0xFC) >> 2));

    iAacFrames = (aHeader[6] & 0x03) + 1;
    if (iAacFrames > kMaxAacFramesPerFrame) {
        LOG(kCodec, "Adts::ReadHeader unexpected iAacFrames: %u; expected %u\n", iAacFrames, kMaxAacFramesPerFrame);
        return false;   // Currently only support 1 AAC frame per ADTS frame.
    }

    //LOG(kCodec, "Adts::Header iPayloadBytes %d, iProfile %d, iSamplingFreq %d, iChannelConfig %d\n", iPayloadBytes, iProfile, iSamplingFreq, iChannelConfig);

    return true;
}


// CodecAdts

CodecAdts::CodecAdts(IMimeTypeList& aMimeTypeList)
    : CodecAacBase("ADTS", aMimeTypeList)
{
    LOG(kCodec, "CodecAdts::CodecAdts\n");
}

CodecAdts::~CodecAdts()
{
    LOG(kCodec, "CodecAdts::~CodecAdts\n");
}

TBool CodecAdts::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecAdts::Recognise\n");
    if (aStreamInfo.RawPcm()) {
        return false;
    }
    const TUint kAdtsConsecutiveFrames = 5; // limit this to allow recognition within 1 data message
    iRecogBuf.SetBytes(0);
    iController->Read(iRecogBuf, iRecogBuf.MaxBytes());

    // attempt Adts recognition
    for(TUint i = 0; i < iRecogBuf.Bytes(); i++) {
        iAdts.SetStartOffset(i);                // save potential start position for first frame

        Adts adts;
        TUint matched = 0;
        TUint j = i;
        TUint payloadBytes = 0;
        while((j+9) < iRecogBuf.Bytes()) {           // ensure there are enough bytes for the maximum header size
            if(!adts.ReadHeader(Brn(iRecogBuf.Ptr()+j, iRecogBuf.Bytes()-j))) {
                break;                          // not a valid header so keep searching
            }
            payloadBytes += adts.PayloadBytes();
            if(++matched >= kAdtsConsecutiveFrames) {   // found enough consecutive valid frames
                if(!iAdts.ReadHeader(Brn(iRecogBuf.Ptr()+iAdts.StartOffset(), iRecogBuf.Bytes()-iAdts.StartOffset()))) {    // save info from first frame
                    break;                          // not a valid header so keep searching
                }
                iAdts.SetPayloadBytesAve(payloadBytes / kAdtsConsecutiveFrames);    // record average payload size over 3 frames
                LOG(kCodec, "CodecAdts::Recognise aac adts\n");
                return true;
            }

            TUint size = adts.PayloadBytes() + adts.HeaderBytes();
            j += size;   // point to where next frame should be
        }
        if (i > 1000) {
            break;      // searched far enough
        }
    }

    return false;
}

void CodecAdts::StreamInitialise()
{
    LOG(kCodec, "CodecAdts::StreamInitialise\n");

    CodecAacBase::StreamInitialise();

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

    InitialiseDecoder();

    iInBuf.SetBytes(0);
    iController->Read(iInBuf, iAdts.StartOffset());  // skip to first frame header
    if (iInBuf.Bytes() < iAdts.StartOffset()) {
        THROW(CodecStreamEnded);
    }

    ProcessAdts(true);  //process first 2 frames to get iOutputSampleRate from the decoder

    iTrackLengthJiffies = (iSamplesTotal * Jiffies::kPerSecond) / iSampleRate;
    iTrackOffset = 0;

    LOG(kCodec, "CodecAdts::StreamInitialise iBitrateAverage %u, iBitDepth %u, iSampleRate: %u, iSamplesTotal %llu, iChannels %u, iTrackLengthJiffies %u\n", iBitrateAverage, iBitDepth, iOutputSampleRate, iSamplesTotal, iChannels, iTrackLengthJiffies);
    iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, 0, false);
}

void CodecAdts::Process()
{
    ProcessAdts(false);

    if (iNewStreamStarted) {
        THROW(CodecStreamStart);
    }
    if (iStreamEnded) {
        THROW(CodecStreamEnded);
    }
}

void CodecAdts::ProcessAdts(TBool aParseOnly)
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

    try {
        while (count < total) {
            // Read in a single aac frame at a time.
            TUint headerBytes = 7;
            iInBuf.SetBytes(0);
            iController->Read(iInBuf, headerBytes);
            if (iInBuf.Bytes() < headerBytes) {
                THROW(CodecStreamEnded);
            }

            TBool streamInterruptedOutput = false;
            while (!adts.ReadHeader(Brn(iInBuf))) { // Read and process header.

                // Notify pipeline of (possible) discontinuity in audio.
                if (!streamInterruptedOutput) {
                    iController->OutputStreamInterrupted();
                    streamInterruptedOutput = true;
                }

                LOG(kCodec, "CodecAdts::ProcessAdts failed to process header 0x");
                for (TUint i=0; i<iInBuf.Bytes(); i++) {
                    LOG(kCodec, "%02x", iInBuf[i]);
                }
                LOG(kCodec, "\n");

                // Failed to find header. Shift buffer along by 1 byte and append next byte to end, then attempt to re-recognise header.
                iInBuf.Replace(iInBuf.Ptr()+1, iInBuf.Bytes()-1);
                iController->Read(iInBuf, 1);
                if (iInBuf.Bytes() < headerBytes) {
                    THROW(CodecStreamEnded);
                }
            }
            if (streamInterruptedOutput) {
                const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(iOutputSampleRate);
                iTrackOffset += jiffiesPerSample;   // Impossible to estimate how much audio has been lost, so assume only 1 sample.
                const TUint64 sampleStart = iTrackOffset / jiffiesPerSample;
                iController->OutputDecodedStream(iBitrateAverage, iBitDepth, iOutputSampleRate, iChannels, kCodecAac, iTrackLengthJiffies, sampleStart, false);
            }


            LOG(kCodec, "CodecAdts::ProcessAdts processed header 0x");
            for (TUint i=0; i<iInBuf.Bytes(); i++) {
                LOG(kCodec, "%02x", iInBuf[i]);
            }
            LOG(kCodec, ", payloadBytes: %u, aacFrames: %u\n", adts.PayloadBytes(), adts.AacFrames());

            if(adts.HeaderBytes() > 7) {
                TUint readBytes = adts.HeaderBytes()-7;
                iInBuf.SetBytes(0);
                iController->Read(iInBuf, readBytes);   // skip any extra header info (i.e. CRC)
                if (iInBuf.Bytes() < readBytes) {
                    THROW(CodecStreamEnded);
                }
            }
            iInBuf.SetBytes(0);
            //LOG(kCodec, "Aac::Process Adts  size = %u, inBuf max size %u\n", adts.PayloadBytes(), iInBuf.MaxBytes());
            iController->Read(iInBuf, adts.PayloadBytes());
            if (iInBuf.Bytes() < adts.PayloadBytes()) {
                THROW(CodecStreamEnded);
            }
            //LOG(kCodec, "Aac::Process  read iInBuf.Bytes() = %u\n", iInBuf.Bytes());

            DecodeFrame(aParseOnly);
            count++;
        }
    }
    catch (CodecStreamStart&) {
        iNewStreamStarted = true;
        //LOG(kCodec, "CodecAlac::ProcessAdts caught CodecStreamStart\n");
    }
    catch (CodecStreamEnded&) {
        iStreamEnded = true;
        //LOG(kCodec, "CodecAlac::ProcessAdts caught CodecStreamEnded\n");
    }

    if(!aParseOnly) {
        FlushOutput();
    }
}
