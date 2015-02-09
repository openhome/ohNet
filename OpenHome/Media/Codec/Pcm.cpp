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
    static const Brn kCodecName;
public:
    CodecPcm();
    ~CodecPcm();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType) override;
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
    EMediaDataEndian iEndian;
    TUint iBitRate;
    TUint64 iStartSample;
    TUint64 iTrackOffset;
    TUint64 iTrackLengthJiffies;
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


const Brn CodecPcm::kCodecName("PCM");

CodecPcm::CodecPcm()
{
}

CodecPcm::~CodecPcm()
{
}

TBool CodecPcm::SupportsMimeType(const Brx& /*aMimeType*/)
{
    return false;
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
    iStartSample = aStreamInfo.StartSample();
    return true;
}

void CodecPcm::StreamInitialise()
{
    iReadBuf.SetBytes(0);
    const TUint64 lenBytes = iController->StreamLength();
    const TUint bytesPerSample = (iBitDepth * iNumChannels) / 8;
    const TUint64 numSamples = lenBytes / bytesPerSample;
    iBitRate = iBitDepth * iNumChannels * iSampleRate;
    iTrackLengthJiffies = numSamples * Jiffies::JiffiesPerSample(iSampleRate);
    iTrackOffset = ToJiffies(iStartSample);
    SendMsgDecodedStream(iStartSample);
}

void CodecPcm::Process()
{
    iController->Read(iReadBuf, iReadBuf.MaxBytes() - iReadBuf.Bytes());
    const TUint pendingBytes = iReadBuf.Bytes() % ((iBitDepth)/8 * iNumChannels);
    Bws<24> pending;
    if (pendingBytes != 0) {
        const TUint bytes = iReadBuf.Bytes() - pendingBytes;
        pending.Append(iReadBuf.Split(bytes));
        iReadBuf.SetBytes(bytes);
    }
    if (iReadBuf.Bytes() > 0) {
        iTrackOffset = iController->OutputAudioPcm(iReadBuf, iNumChannels, iSampleRate, iBitDepth, iEndian, iTrackOffset);
    }
    iReadBuf.Replace(pending);
}

TBool CodecPcm::TrySeek(TUint aStreamId, TUint64 aSample)
{
    const TUint64 bytePos = aSample * iNumChannels * (iBitDepth/8);
    if (!iController->TrySeekTo(aStreamId, bytePos)) {
        return false;
    }
    iTrackOffset = ToJiffies(aSample);
    SendMsgDecodedStream(aSample);
    return true;
}

void CodecPcm::SendMsgDecodedStream(TUint64 aStartSample)
{
    iController->OutputDecodedStream(iBitRate, iBitDepth, iSampleRate, iNumChannels, kCodecName, iTrackLengthJiffies, aStartSample, true);
}

TUint64 CodecPcm::ToJiffies(TUint64 aSample)
{
    return ((TUint64)aSample * Jiffies::kPerSecond) / iSampleRate;
}
