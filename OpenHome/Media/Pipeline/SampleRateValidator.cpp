#include <OpenHome/Media/Pipeline/SampleRateValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;


SampleRateValidator::SampleRateValidator(IPipelineElementDownstream& aDownstreamElement, IPipelineAnimator& aPipelineAnimator)
    : iDownstream(aDownstreamElement)
    , iAnimator(aPipelineAnimator)
    , iFlushing(false)
{
}

void SampleRateValidator::Push(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    if (msg != NULL) {
        iDownstream.Push(msg);
    }
}

Msg* SampleRateValidator::ProcessMsg(MsgMode* aMsg)
{
    iFlushing = false;
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgSession* aMsg)
{
    iFlushing = false;
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgTrack* aMsg)
{
    iFlushing = false;
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        iTargetFlushId = MsgFlush::kIdInvalid;
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    try {
        (void)iAnimator.PipelineDriverDelayJiffies(0, streamInfo.SampleRate());
        iFlushing = false;
    }
    catch (SampleRateUnsupported&) {
        iFlushing = true;
        iTargetFlushId = streamInfo.StreamHandler()->TryStop(streamInfo.StreamId());
    }
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

Msg* SampleRateValidator::ProcessFlushable(Msg* aMsg)
{
    if (iFlushing) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}
