#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecPcm : public CodecBase
{
public:
    CodecPcm();
    ~CodecPcm();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo) override;
    void StreamInitialise() override;
    void Process() override;
    TBool TrySeek(TUint aStreamId, TUint64 aSample) override;
private:
    void SendMsgDecodedStream(TUint64 aStartSample);
    TUint64 ToJiffies(TUint64 aSample);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    AudioDataEndian iEndian;
    SpeakerProfile iProfile;
    TUint iBitRate;
    TUint64 iStartSample;
    TUint64 iTrackOffset;
    TUint64 iTrackLengthJiffies;
    TBool iAnalogBypass;
    BwsCodecName iCodecName;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewPcm()
{ // static
    return new CodecPcm();
}


CodecPcm::CodecPcm()
    : CodecBase("PCM", kCostVeryLow)
{
}

CodecPcm::~CodecPcm()
{
}

TBool CodecPcm::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (!aStreamInfo.RawPcm()) {
        return false;
    }
    iBitDepth = aStreamInfo.BitDepth();
    iSampleRate = aStreamInfo.SampleRate();
    iNumChannels = aStreamInfo.NumChannels();
    iEndian = aStreamInfo.Endian();
    iProfile = aStreamInfo.Profile();
    iStartSample = aStreamInfo.StartSample();
    iAnalogBypass = aStreamInfo.AnalogBypass();
    iCodecName.Replace(aStreamInfo.CodecName());
    //Log::Print("CodecPcm::Recognise iBitDepth %d, iSampleRate %d, iNumChannels %d, iEndian %d, iStartSample %d, iAnalogBypass %d\n", iBitDepth, iSampleRate, iNumChannels, iEndian, iStartSample, iAnalogBypass);
    return true;
}

void CodecPcm::StreamInitialise()
{
    try {
        iReadBuf.SetBytes(0);
        const TUint64 lenBytes = iController->StreamLength();
        const TUint bytesPerSample = (iBitDepth * iNumChannels) / 8;
        const TUint64 numSamples = lenBytes / bytesPerSample;
        iBitRate = iBitDepth * iNumChannels * iSampleRate;
        iTrackLengthJiffies = numSamples * Jiffies::PerSample(iSampleRate);
        iTrackOffset = ToJiffies(iStartSample);
        SendMsgDecodedStream(iStartSample);
    }
    catch (SampleRateInvalid&) {
        THROW(CodecStreamCorrupt);
    }
}

void CodecPcm::Process()
{
    if (iEndian == AudioDataEndian::Big) {
        MsgAudioEncoded* msg = iController->ReadNextMsg();
        iTrackOffset += iController->OutputAudioPcm(msg, iNumChannels, iSampleRate, iBitDepth, iTrackOffset);
    }
    else {
        iController->Read(iReadBuf, iReadBuf.MaxBytes() - iReadBuf.Bytes());
        const TUint pendingBytes = iReadBuf.Bytes() % ((iBitDepth)/8 * iNumChannels);
        Bws<24> pending;
        if (pendingBytes != 0) {
            const TUint bytes = iReadBuf.Bytes() - pendingBytes;
            pending.Append(iReadBuf.Split(bytes));
            iReadBuf.SetBytes(bytes);
        }
        if (iReadBuf.Bytes() > 0) {
            iTrackOffset += iController->OutputAudioPcm(iReadBuf, iNumChannels, iSampleRate, iBitDepth, iEndian, iTrackOffset);
        }
        iReadBuf.Replace(pending);
    }
}

TBool CodecPcm::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint64 bytePos = aSample * iNumChannels * (iBitDepth/8);
    if (!iController->TrySeekTo(aStreamId, bytePos)) {
        return false;
    }
    iTrackOffset = ToJiffies(aSample);
    iReadBuf.SetBytes(0);
    SendMsgDecodedStream(aSample);
    return true;
}

void CodecPcm::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, iCodecName, iTrackLengthJiffies, aStartSample, true, iProfile, iAnalogBypass);
}

TUint64 CodecPcm::ToJiffies(TUint64 aSample)
{
    return ((TUint64)aSample * Jiffies::kPerSecond) / iSampleRate;
}
