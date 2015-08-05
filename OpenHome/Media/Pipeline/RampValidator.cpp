#include <OpenHome/Media/Pipeline/RampValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

#define RAMP_VALIDATOR_ENABLED 0

RampValidator::RampValidator(IPipelineElementUpstream& aUpstream, const TChar* aId)
    : iId(aId)
    , iUpstream(&aUpstream)
    , iDownstream(nullptr)
    , iRampedDown(false)
    , iWaitingForAudio(true)
{
}

RampValidator::RampValidator(const TChar* aId, IPipelineElementDownstream& aDownstream)
    : iId(aId)
    , iUpstream(nullptr)
    , iDownstream(&aDownstream)
    , iRampedDown(false)
    , iWaitingForAudio(true)
{
}

RampValidator::~RampValidator()
{
}

Msg* RampValidator::Pull()
{
    ASSERT(iUpstream != nullptr);
    Msg* msg = iUpstream->Pull();
    msg = msg->Process(*this);
    ASSERT(msg != nullptr);
    return msg;
}

void RampValidator::Push(Msg* aMsg)
{
    ASSERT(iDownstream != nullptr);
    Msg* msg = aMsg->Process(*this);
    ASSERT(msg != nullptr);
    iDownstream->Push(msg);
}

void RampValidator::Reset(const TChar* aCallerId)
{
    //Log::Print("RampValidator::Reset() - %s %s\n", iId, aCallerId);
    LOG(kMedia, "RampValidator::Reset() - %s %s\n", iId, aCallerId);
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
            Log::Print("WARNING: discontinuity in ramp (%s): expected %08x, got %08x\n", iId, iLastRamp, aRamp.Start());
#if RAMP_VALIDATOR_ENABLED
            ASSERTS();
#endif
        }
        iLastRamp = aRamp.End();
        if (aRamp.Direction() == Ramp::EUp && iLastRamp == Ramp::kMax) {
            Reset("completed ramp up");
        }
        else if (aRamp.Direction() == Ramp::EDown && iLastRamp == Ramp::kMin) {
            Reset("completed ramp down");
            iRampedDown = true;
        }
    }
    else if (aRamp.IsEnabled()) {
        iRamping = true;
        if (aRamp.Direction() == Ramp::EUp) {
            if (aRamp.Start() != Ramp::kMin) {
                Log::Print("WARNING: ramp up (%s) started at %08x\n", iId, aRamp.Start());
#if RAMP_VALIDATOR_ENABLED
                ASSERTS();
#endif
            }
        }
        else { // aRamp.Direction() == Ramp::EDown
            if (aRamp.Start() != Ramp::kMax) {
                Log::Print("WARNING: ramp down (%s) started at %08x\n", iId, aRamp.Start());
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
    Reset("Mode");
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
        Reset("Track");
        iRampedDown = false;
    }
    return aMsg;
}

Msg* RampValidator::ProcessMsg(MsgDrain* aMsg)
{
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

Msg* RampValidator::ProcessMsg(MsgStreamInterrupted* aMsg)
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
    Reset("DecodedStream");
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
