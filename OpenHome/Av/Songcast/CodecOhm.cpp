#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Av/Songcast/CodecOhm.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>

#include <string.h>


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;
using namespace OpenHome::Av;

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

TBool CodecOhm::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    if (aStreamInfo.RawPcm()) {
        return false;
    }
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
    iSendSession = false;
    iSampleRate = 0;
    iLatency = 0;
}

void CodecOhm::Process()
{
    OhmHeader header;
    header.Internalise(*this);
    ASSERT(header.MsgType() == OhmHeader::kMsgTypeAudioBlob);
    OhmMsgAudio* msg = iMsgFactory.CreateAudioFromBlob(*this, header);

    if (msg->Samples() > 0) {
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
            if (iSendSession) {
                iController->OutputSession();
                iSendSession = false;
            }
            const TUint64 jiffiesStart = jiffiesPerSample * msg->SampleStart();
            if (msg->RxTimestamped() && msg->Timestamped()) {
                iController->OutputAudioPcm(msg->Audio(), msg->Channels(), sampleRate, msg->BitDepth(), EMediaDataEndianBig, jiffiesStart, msg->RxTimestamp(), msg->NetworkTimestamp());
            }
            else {
                iController->OutputAudioPcm(msg->Audio(), msg->Channels(), sampleRate, msg->BitDepth(), EMediaDataEndianBig, jiffiesStart);
            }
        }
    }

    if (msg->Halt()) {
        iController->OutputWait();
        iController->OutputHalt();
        iSendSession = true;
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

TUint CodecOhm::ReadCapacity() const
{
    return iBuf.MaxBytes();
}

void CodecOhm::OutputDelay()
{
    static const TUint kDelayDivisor48k = (48000 * 256) / 1000;
    static const TUint kDelayDivisor44k = (44100 * 256) / 1000;
    const TUint delayMs = iLatency / ((iSampleRate % 441) == 0 ? kDelayDivisor44k : kDelayDivisor48k);
    //Log::Print("-- CodecOhm - delayMs=%u\n", delayMs);
    const TUint delayJiffies = delayMs * Jiffies::kPerMs;
    iController->OutputDelay(delayJiffies);
}
