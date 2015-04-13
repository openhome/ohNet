#include <OpenHome/Media/Pipeline/RampValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

RampValidator::RampValidator(IPipelineElementUpstream& aUpstream)
    : iUpstream(&aUpstream)
    , iDownstream(NULL)
    , iRampedDown(false)
{
}

RampValidator::RampValidator(IPipelineElementDownstream& aDownstream)
    : iUpstream(NULL)
    , iDownstream(&aDownstream)
    , iRampedDown(false)
{
}

RampValidator::~RampValidator()
{
}

Msg* RampValidator::Pull()
{
    ASSERT(iUpstream != NULL);
    Msg* msg = iUpstream->Pull();
    msg = msg->Process(*this);
    ASSERT(msg != NULL);
    return msg;
}

void RampValidator::Push(Msg* aMsg)
{
    ASSERT(iDownstream != NULL);
    Msg* msg = aMsg->Process(*this);
    ASSERT(msg != NULL);
    iDownstream->Push(msg);
}

void RampValidator::Reset()
{
    iRamping = false;
    iRampDirection = Ramp::ENone;
    iLastRamp = UINT_MAX;
}

void RampValidator::ProcessAudio(const Ramp& aRamp)
{
    if (iRampedDown) {
        ASSERT(aRamp.IsEnabled());
        ASSERT(aRamp.Start() == Ramp::kMin);
        ASSERT(aRamp.Direction() == Ramp::EUp);
        iRampedDown = false;
    }
    if (iRamping) {
        ASSERT(aRamp.IsEnabled());
        ASSERT(aRamp.Start() == iLastRamp);
        iLastRamp = aRamp.End();
        iRampDirection = aRamp.Direction();
        if (iRampDirection == Ramp::EUp   && iLastRamp == Ramp::kMax) {
            Reset();
        }
        else if (iRampDirection == Ramp::EDown && iLastRamp == Ramp::kMin) {
            Reset();
            iRampedDown = true;
        }
    }
    else if (aRamp.IsEnabled()) {
        iRamping = true;
        iRampDirection = aRamp.Direction();
        if (iRampDirection == Ramp::EUp) {
            ASSERT(aRamp.Start() == Ramp::kMin);
        }
        else { // iRampDirection == Ramp::EDown
            ASSERT(aRamp.Start() == Ramp::kMax);
        }
        iLastRamp = aRamp.End();
    }
}

Msg* RampValidator::ProcessMsg(MsgMode* aMsg)
{
    Reset();
    iRampedDown = false;
    iWaitingForAudio = false;
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgTrack* aMsg)
{
    if (aMsg->StartOfStream()) {
        Reset();
        iRampedDown = false;
    }
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgHalt* aMsg)
{
    iRampedDown = true;
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgDecodedStream* aMsg)
{
    Reset();
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iRampedDown = stream.Live() || (stream.SampleStart() > 0);
    iWaitingForAudio = true;
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgAudioPcm* aMsg)
{
    //ProcessAudio(aMsg->Ramp());
    iWaitingForAudio = false;
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgSilence* aMsg)
{
    if (!iWaitingForAudio) {
        //ProcessAudio(aMsg->Ramp());
    }
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgPlayable* aMsg)
{
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
