#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>

#include <string.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecOhm : public CodecBase, private IReader
{
public:
    CodecOhm(Av::OhmMsgFactory& aMsgFactory);
    ~CodecOhm();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise();
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private: // from IReader
    Brn Read(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
    void ReadFlush();
    void ReadInterrupt();
private:
    void OutputDelay();
private:
    Av::OhmMsgFactory& iMsgFactory;
    Bws<Av::OhmMsgAudioBlob::kMaxBytes> iBuf;
    TUint iOffset;
    TBool iStreamOutput;
    TUint iSampleRate;
    TUint iLatency;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;

CodecBase* CodecFactory::NewOhm(OhmMsgFactory& aMsgFactory)
{ // static
    return new CodecOhm(aMsgFactory);
}



CodecOhm::CodecOhm(OhmMsgFactory& aMsgFactory)
    : iMsgFactory(aMsgFactory)
    , iOffset(0)
{
}

CodecOhm::~CodecOhm()
{
}

TBool CodecOhm::SupportsMimeType(const Brx& /*aMimeType*/)
{
    return false;
}

TBool CodecOhm::Recognise()
{
    try {
        OhmHeader header;
        header.Internalise(*this);
        return true;
    }
    catch (OhmError&) {
    }
    return false;
}

void CodecOhm::StreamInitialise()
{
    iBuf.SetBytes(0);
    iOffset = 0;
    iStreamOutput = false;
    iSampleRate = 0;
    iLatency = 0;
}

void CodecOhm::Process()
{
    OhmHeader header;
    header.Internalise(*this);
    ASSERT(header.MsgType() == OhmHeader::kMsgTypeAudioBlob);
    OhmMsgAudio* msg = iMsgFactory.CreateAudioFromBlob(*this, header);

    const TUint sampleRate = msg->SampleRate();
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(sampleRate);
    const TUint latency = msg->MediaLatency();

    if (!iStreamOutput) {
        const TUint64 trackLengthJiffies = jiffiesPerSample * msg->SamplesTotal();
        iController->OutputDecodedStream(msg->BitRate(), msg->BitDepth(), sampleRate, msg->Channels(), msg->Codec(), trackLengthJiffies, msg->SampleStart(), msg->Lossless());
        iStreamOutput = true;
    }

    if (sampleRate != iSampleRate || latency != iLatency) {
        iSampleRate = sampleRate;
        iLatency = latency;
        OutputDelay();
    }

    if (msg->Samples() > 0) {
        const TUint64 jiffiesStart = jiffiesPerSample * msg->SampleStart();
        const TUint rxTimestamp = (msg->RxTimestamped()? msg->RxTimestamp() : 0);
        const TUint networkTimestamp = (msg->Timestamped()? msg->NetworkTimestamp() : 0);
        const TUint mediaTimestamp = (msg->Timestamped()? msg->MediaTimestamp() : 0);
        iController->OutputAudioPcm(msg->Audio(), msg->Channels(), sampleRate, msg->BitDepth(), EMediaDataBigEndian, jiffiesStart, rxTimestamp, msg->MediaLatency(), networkTimestamp, mediaTimestamp);
    }

    if (msg->Halt()) {
        iController->OutputWait();
        iController->OutputHalt();
    }

    msg->RemoveRef();
}

TBool CodecOhm::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}

Brn CodecOhm::Read(TUint aBytes)
{
    while (aBytes + iOffset > iBuf.Bytes()) {
        if (iOffset > 0) {
            Log::Print("WARNING: (CodecOhm) songcast frame has been split\n");
        }
        iBuf.Replace(iBuf.Split(iOffset));
        iOffset = 0;
        iController->ReadNextMsg(iBuf);
    }
    Brn buf(iBuf.Ptr() + iOffset, aBytes);
    iOffset += aBytes;
    if (iOffset == iBuf.Bytes()) {
        iOffset = 0;
        iBuf.SetBytes(0);
    }
    return buf;
}

Brn CodecOhm::ReadUntil(TByte /*aSeparator*/)
{
    ASSERTS(); // not implemented
    return Brn(NULL, 0);
}

void CodecOhm::ReadFlush()
{
    ASSERTS(); // not implemented
}

void CodecOhm::ReadInterrupt()
{
}

void CodecOhm::OutputDelay()
{
    static const TUint kDelayDivisor48k = (48000 * 256) / 1000;
    static const TUint kDelayDivisor44k = (44100 * 256) / 1000;
    const TUint delayMs = iLatency / ((iSampleRate % 441) == 0 ? kDelayDivisor44k : kDelayDivisor48k);
    Log::Print("-- CodecOhm - delayMs=%u\n", delayMs);
    const TUint delayJiffies = delayMs * Jiffies::kJiffiesPerMs;
    iController->OutputDelay(delayJiffies);
}
