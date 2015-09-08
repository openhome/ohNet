#include <OpenHome/Media/Pipeline/DecodedAudioAggregator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioAggregator

const TUint DecodedAudioAggregator::kSupportedMsgTypes =   eMode
                                                         | eTrack
                                                         | eDrain
                                                         | eDelay
                                                         | eEncodedStream
                                                         | eMetatext
                                                         | eStreamInterrupted
                                                         | eHalt
                                                         | eFlush
                                                         | eWait
                                                         | eDecodedStream
                                                         | eBitRate
                                                         | eAudioPcm
                                                         | eQuit;

DecodedAudioAggregator::DecodedAudioAggregator(IPipelineElementDownstream& aDownstreamElement, MsgFactory& aMsgFactory)
    : PipelineElement(kSupportedMsgTypes)
    , iDownstreamElement(aDownstreamElement)
    , iMsgFactory(aMsgFactory)
    , iDecodedAudio(nullptr)
    , iChannels(0)
    , iSampleRate(0)
    , iBitDepth(0)
{
}

void DecodedAudioAggregator::Push(Msg* aMsg)
{
    ASSERT(aMsg != nullptr);
    Msg* msg = aMsg->Process(*this);
    if (msg != nullptr) {
        iDownstreamElement.Push(msg);
    }
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgMode* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgTrack* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgDrain* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgEncodedStream* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgHalt* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgFlush* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgWait* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    OutputAggregatedAudio();
    ASSERT(iDecodedAudio == nullptr);
    const DecodedStreamInfo& info = aMsg->StreamInfo();
    iChannels = info.NumChannels();
    iSampleRate = info.SampleRate();
    iBitDepth = info.BitDepth();
    return aMsg;
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgAudioPcm* aMsg)
{
    return TryAggregate(aMsg);
}

Msg* DecodedAudioAggregator::ProcessMsg(MsgQuit* aMsg)
{
    OutputAggregatedAudio();
    return aMsg;
}

TBool DecodedAudioAggregator::AggregatorFull(TUint aBytes, TUint aJiffies)
{
    return (aBytes == DecodedAudio::kMaxBytes || aJiffies >= kMaxJiffies);
}

MsgAudioPcm* DecodedAudioAggregator::TryAggregate(MsgAudioPcm* aMsg)
{
    // This method only looks at the byte capacity when deciding whether to
    // buffer data. There is no point in chopping the data purely on a jiffy
    // limit when buffer space could be used to output all jiffies together.

    TUint jiffies = aMsg->Jiffies();
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(iSampleRate);
    const TUint msgBytes = Jiffies::BytesFromJiffies(jiffies, jiffiesPerSample, iChannels, iBitDepth/8);
    ASSERT(jiffies == aMsg->Jiffies()); // refuse to handle msgs not terminating on sample boundaries

    if (iDecodedAudio == nullptr) {
        if (AggregatorFull(msgBytes, aMsg->Jiffies())) {
            return aMsg;
        }
        else {
            iDecodedAudio = aMsg;
            return nullptr;
        }
    }

    TUint aggregatedJiffies = iDecodedAudio->Jiffies();
    TUint aggregatedBytes = Jiffies::BytesFromJiffies(aggregatedJiffies, jiffiesPerSample, iChannels, iBitDepth/8);
    if (aggregatedBytes + msgBytes <= kMaxBytes) {
        // Have byte capacity to add new data.
        iDecodedAudio->Aggregate(*aMsg);

        aggregatedJiffies = iDecodedAudio->Jiffies();
        aggregatedBytes = Jiffies::BytesFromJiffies(aggregatedJiffies, jiffiesPerSample, iChannels, iBitDepth/8);
        if (AggregatorFull(aggregatedBytes, iDecodedAudio->Jiffies())) {
            MsgAudioPcm* msg = iDecodedAudio;
            iDecodedAudio = nullptr;
            return msg;
        }
    }
    else {
        // Lazy approach here - if new aMsg can't be appended, just return
        // iDecodedAudio and set iDecodedAudio = aMsg.
        // Could add a method to MsgAudioPcm that chops audio when aggregating
        // to make even more efficient use of decoded audio msgs.
        MsgAudioPcm* msg = iDecodedAudio;
        iDecodedAudio = aMsg;
        return msg;
    }

    return nullptr;
}

void DecodedAudioAggregator::OutputAggregatedAudio()
{
    if (iDecodedAudio != nullptr) {
        iDownstreamElement.Push(iDecodedAudio);
        iDecodedAudio = nullptr;
    }
}

void DecodedAudioAggregator::ReleaseAggregatedAudio()
{
    if (iDecodedAudio != nullptr) {
        iDecodedAudio->RemoveRef();
        iDecodedAudio = nullptr;
    }
}
