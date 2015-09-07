#include <OpenHome/Media/Pipeline/Ramper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint Ramper::kSupportedMsgTypes =   eMode
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
                                         | eSilence
                                         | eQuit;

Ramper::Ramper(IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iRamping(false)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMin)
{
}

Ramper::~Ramper()
{
}

Msg* Ramper::Pull()
{
    Msg* msg;
    if (!iQueue.IsEmpty()) {
        msg = iQueue.Dequeue();
    }
    else {
        msg = iUpstreamElement.Pull();
    }
    msg = msg->Process(*this);
    ASSERT(msg != nullptr);
    return msg;
}

Msg* Ramper::ProcessMsg(MsgHalt* aMsg)
{
    iRamping = false;
    return aMsg;
}

Msg* Ramper::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& info = aMsg->StreamInfo();
    const TBool newStream = (info.StreamId() != iStreamId);
    iStreamId = info.StreamId();
    if (info.Live() || (newStream && info.SampleStart() > 0)) {
        iRamping = true;
        iCurrentRampValue = Ramp::kMin;
        iRemainingRampSize = iRampDuration;
    }
    else {
        iRamping = false;
        iCurrentRampValue = Ramp::kMax;
        iRemainingRampSize = 0;
    }
    return aMsg;
}

Msg* Ramper::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iRamping) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != nullptr) {
                iQueue.Enqueue(split);
            }
        }
        split = nullptr;
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EUp, split);
        if (split != nullptr) {
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            iRamping = false;
        }
    }
    return aMsg;
}

Msg* Ramper::ProcessMsg(MsgSilence* aMsg)
{
    iRamping = false;
    iCurrentRampValue = Ramp::kMax;
    iRemainingRampSize = 0;
    return aMsg;
}
