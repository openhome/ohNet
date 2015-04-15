#include <OpenHome/Media/Pipeline/RampValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

#define RAMP_VALIDATOR_ENABLED 0

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
    iLastRamp = UINT_MAX;
}

void RampValidator::ProcessAudio(const Ramp& aRamp)
{
    /*if (iRampedDown) {
        ASSERT(aRamp.IsEnabled());
        ASSERT(aRamp.Start() == Ramp::kMin);
        ASSERT(aRamp.Direction() == Ramp::EUp);
        iRampedDown = false;
    }*/
    if (iRamping) {
#if RAMP_VALIDATOR_ENABLED
        ASSERT(aRamp.IsEnabled());
#endif
        if (aRamp.Start() != iLastRamp) {
            Log::Print("WARNING: discontinuity in ramp: expected %08x, got %08x\n", iLastRamp, aRamp.Start());
#if RAMP_VALIDATOR_ENABLED
            ASSERTS();
#endif
        }
        iLastRamp = aRamp.End();
        if (aRamp.Direction() == Ramp::EUp && iLastRamp == Ramp::kMax) {
            Reset();
        }
        else if (aRamp.Direction() == Ramp::EDown && iLastRamp == Ramp::kMin) {
            Reset();
            iRampedDown = true;
        }
    }
    else if (aRamp.IsEnabled()) {
        iRamping = true;
        if (aRamp.Direction() == Ramp::EUp) {
            if (aRamp.Start() != Ramp::kMin) {
                Log::Print("WARNING: ramp up started at %08x\n", aRamp.Start());
#if RAMP_VALIDATOR_ENABLED
                ASSERTS();
#endif
            }
        }
        else { // aRamp.Direction() == Ramp::EDown
            if (aRamp.Start() != Ramp::kMax) {
                Log::Print("WARNING: ramp down started at %08x\n", aRamp.Start());
#if RAMP_VALIDATOR_ENABLED
                ASSERTS();
#endif
            }
        }
        iLastRamp = aRamp.End();
    }
}

Msg* RampValidator::ProcessMsg(MsgMode* aMsg)
{
    Reset();
    iRampedDown = false;
    iWaitingForAudio = true;
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
    if (!iWaitingForAudio) {
        iRampedDown = true;
    }
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
    ProcessAudio(aMsg->Ramp());
    iWaitingForAudio = false;
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgSilence* aMsg)
{
    if (!iWaitingForAudio) {
        ProcessAudio(aMsg->Ramp());
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
