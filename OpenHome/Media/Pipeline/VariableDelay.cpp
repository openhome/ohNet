#include <OpenHome/Media/Pipeline/VariableDelay.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;

// VariableDelay

const TUint VariableDelay::kSupportedMsgTypes =   eMode
                                                | eTrack
                                                | eDrain
                                                | eDelay
                                                | eEncodedStream
                                                | eAudioEncoded
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

static const TChar* kStatus[] = { "Starting"
                                 ,"Running"
                                 ,"RampingDown"
                                 ,"RampedDown"
                                 ,"RampingUp" };

VariableDelay::VariableDelay(const TChar* aId, MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aDownstreamDelay, TUint aRampDuration)
    : PipelineElement(kSupportedMsgTypes)
    , iId(aId)
    , iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iLock("VDEL")
    , iDelayJiffies(0)
    , iDelayJiffiesTotal(0)
    , iDelayAdjustment(0)
    , iDownstreamDelay(aDownstreamDelay)
    , iRampDuration(aRampDuration)
    , iWaitForAudioBeforeGeneratingSilence(false)
    , iStreamHandler(nullptr)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iAnimatorLatencyOverride(0)
    , iAnimatorOverridePending(false)
{
    ResetStatusAndRamp();
}

VariableDelay::~VariableDelay()
{
}

void VariableDelay::OverrideAnimatorLatency(TUint aJiffies)
{
    iLock.Wait();
    iAnimatorLatencyOverride = aJiffies;
    iAnimatorOverridePending = true;
    iLock.Signal();
}

Msg* VariableDelay::Pull()
{
    {
        AutoMutex _(iLock);
        if (iAnimatorOverridePending) {
            ApplyAnimatorOverride();
            iAnimatorOverridePending = false;
        }
    }

    Msg* msg = nullptr;
    if (iWaitForAudioBeforeGeneratingSilence) {
        do {
            msg = NextMsg();
            if (msg != nullptr) {
                if (iWaitForAudioBeforeGeneratingSilence) {
                    return msg;
                }
                else {
                    iQueue.Enqueue(msg);
                }
            }
        } while (msg == nullptr && iWaitForAudioBeforeGeneratingSilence);
        msg = nullptr; // DoEnqueue() above passed ownership of msg back to reservoir
    }

    // msg(s) pulled above may have altered iDelayAdjustment (e.g. MsgMode sets it to zero)
    if ((iStatus == EStarting || iStatus == ERampedDown) && iDelayAdjustment > 0) {
        TUint size = ((TUint)iDelayAdjustment > kMaxMsgSilenceDuration? kMaxMsgSilenceDuration : (TUint)iDelayAdjustment);
        msg = iMsgFactory.CreateMsgSilence(size, iSampleRate, iBitDepth, iNumChannels);
        iDelayAdjustment -= size;
        if (iDelayAdjustment == 0) {
            if (iStatus == ERampedDown) {
                iStatus = ERampingUp;
                iRampDirection = Ramp::EUp;
                iCurrentRampValue = Ramp::kMin;
                iRemainingRampSize = iRampDuration;
            }
            else {
                iStatus = ERunning;
                iRampDirection = Ramp::ENone;
                iCurrentRampValue = Ramp::kMax;
                iRemainingRampSize = 0;
            }
        }
    }
    else if (msg == nullptr) {
        do {
            msg = NextMsg();
        } while (msg == nullptr);
    }

    return msg;
}

Msg* VariableDelay::NextMsg()
{
    Msg* msg;
    if (!iQueue.IsEmpty()) {
        msg = iQueue.Dequeue();
    }
    else {
        msg = iUpstreamElement.Pull();
    }
    msg = msg->Process(*this);
    return msg;
}

void VariableDelay::ApplyAnimatorOverride()
{
    ASSERT(iDownstreamDelay == 0); // only expect to support iAnimatorLatencyOverride in rightmost delay element
    TUint delayJiffies = (iAnimatorLatencyOverride >= iDelayJiffiesTotal? 0 : iDelayJiffiesTotal - iAnimatorLatencyOverride);
    if (delayJiffies == iDelayJiffies) {
        return;
    }

    iDelayAdjustment += (TInt)(delayJiffies - iDelayJiffies);
    iDelayJiffies = delayJiffies;
    SetupRamp();
}

void VariableDelay::RampMsg(MsgAudio* aMsg)
{
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        iQueue.EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, iRampDirection, split);
    if (split != nullptr) {
        iQueue.EnqueueAtHead(split);
    }
}

void VariableDelay::ResetStatusAndRamp()
{
    iStatus = EStarting;
    iRampDirection = Ramp::ENone;
    iCurrentRampValue = Ramp::kMax;
    iRemainingRampSize = iRampDuration;
}

void VariableDelay::SetupRamp()
{
    iWaitForAudioBeforeGeneratingSilence = true;
    LOG(kMedia, "VariableDelay: iId=%s, delay=%u, adjustment=%d\n",
        iId, iDelayJiffies/Jiffies::kPerMs, iDelayAdjustment/(TInt)Jiffies::kPerMs);
    switch (iStatus)
    {
    case EStarting:
        iRampDirection = Ramp::ENone;
        iCurrentRampValue = Ramp::kMax;
        iRemainingRampSize = iRampDuration;
        break;
    case ERunning:
        iStatus = ERampingDown;
        iRampDirection = Ramp::EDown;
        iCurrentRampValue = Ramp::kMax;
        iRemainingRampSize = iRampDuration;
        break;
    case ERampingDown:
        if (iDelayAdjustment == 0) {
            if (iRampDuration == iRemainingRampSize) {
                iStatus = ERunning;
                iRampDirection = Ramp::ENone;
                iRemainingRampSize = 0;
            }
            else {
                iStatus = ERampingUp;
                iRampDirection = Ramp::EUp;
                // retain current value of iCurrentRampValue
                iRemainingRampSize = iRampDuration - iRemainingRampSize;
            }
        }
        break;
    case ERampedDown:
        break;
    case ERampingUp:
        iStatus = ERampingDown;
        iRampDirection = Ramp::EDown;
        // retain current value of iCurrentRampValue
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        if (iRemainingRampSize == 0) {
            iStatus = ERampedDown;
        }
        break;
    }
}

Msg* VariableDelay::ProcessMsg(MsgMode* aMsg)
{
    iMode.Replace(aMsg->Mode());
    iDelayJiffies = 0;
    iDelayJiffiesTotal = 0;
    iDelayAdjustment = 0;
    iWaitForAudioBeforeGeneratingSilence = true;
    ResetStatusAndRamp();
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgDrain* aMsg)
{
    iDelayAdjustment = iDelayJiffies;
    if (iDelayAdjustment == 0) {
        iWaitForAudioBeforeGeneratingSilence = false;
        ResetStatusAndRamp();
    }
    else {
        iWaitForAudioBeforeGeneratingSilence = true;
        iRampDirection = Ramp::EDown;
        iCurrentRampValue = Ramp::kMin;
        iRemainingRampSize = 0;
        iStatus = ERampedDown;

    }
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgDelay* aMsg)
{
    TUint delayJiffies = aMsg->DelayJiffies();
    iDelayJiffiesTotal = delayJiffies;
    const TUint animatorDelay = aMsg->AnimatorDelayJiffies();
    aMsg->RemoveRef();
    const TUint downstream = (iDownstreamDelay > 0? iDownstreamDelay :
                                                    iAnimatorLatencyOverride > 0? iAnimatorLatencyOverride :
                                                                                  animatorDelay);
    auto msg = iMsgFactory.CreateMsgDelay(std::min(downstream, delayJiffies), animatorDelay);
    delayJiffies = (downstream >= delayJiffies? 0 : delayJiffies - downstream);
    LOG(kMedia, "VariableDelay::ProcessMsg(MsgDelay*): iId=%s, : delay=%u(%u), iDownstreamDelay=%u(%u), iDelayJiffies=%u(%u), iStatus=%s\n",
        iId, delayJiffies, Jiffies::ToMs(delayJiffies),
        iDownstreamDelay, Jiffies::ToMs(iDownstreamDelay),
        iDelayJiffies, Jiffies::ToMs(iDelayJiffies),
        kStatus[iStatus]);
    if (delayJiffies == iDelayJiffies) {
        return msg;
    }

    iDelayAdjustment += (TInt)(delayJiffies - iDelayJiffies);
    iDelayJiffies = delayJiffies;
    SetupRamp();

    return msg;
}

Msg* VariableDelay::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iStreamHandler = stream.StreamHandler();
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();
    ResetStatusAndRamp();
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iWaitForAudioBeforeGeneratingSilence) {
        iWaitForAudioBeforeGeneratingSilence = false;
        return aMsg;
    }

    MsgAudio* msg = aMsg;
    switch (iStatus)
    {
    case EStarting:
        iStatus = ERunning;
        break;
    case ERunning:
        // nothing to do, allow the message to be passed out unchanged
        break;
    case ERampingDown:
    {
        RampMsg(msg);
        if (iRemainingRampSize == 0) {
            if (iDelayAdjustment != 0) {
                iStatus = ERampedDown;
            }
            else {
                iStatus = ERampingUp;
                iRampDirection = Ramp::EUp;
                iRemainingRampSize = iRampDuration;
            }
        }
    }
        break;
    case ERampedDown:
    {
        ASSERT(iDelayAdjustment < 0);
        TUint jiffies = msg->Jiffies();
        if (jiffies >(TUint)(-iDelayAdjustment)) {
            MsgAudio* remaining = msg->Split((TUint)(-iDelayAdjustment));
            jiffies = msg->Jiffies();
            iQueue.EnqueueAtHead(remaining);
        }
        iDelayAdjustment += jiffies;
        msg->RemoveRef();
        msg = nullptr;
        if (iDelayAdjustment == 0) {
            iStatus = ERampingUp;
            iRampDirection = Ramp::EUp;
            iRemainingRampSize = iRampDuration;
        }
    }
        break;
    case ERampingUp:
    {
        RampMsg(msg);
        if (iRemainingRampSize == 0) {
            iStatus = ERunning;
        }
    }
        break;
    default:
        ASSERTS();
    }

    return msg;
}

Msg* VariableDelay::ProcessMsg(MsgSilence* aMsg)
{
    if (iStatus == ERampingUp) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMax;
        iStatus = ERunning;
    }
    else if (iStatus == ERampingDown) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
        if (iDelayAdjustment != 0) {
            iStatus = ERampedDown;
        }
        else {
            iStatus = ERampingUp;
            iRampDirection = Ramp::EUp;
            iRemainingRampSize = iRampDuration;
        }
    }

    return aMsg;
}
