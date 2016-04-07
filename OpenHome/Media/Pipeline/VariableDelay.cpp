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

static const TChar* kStatus[] = { "Starting"
                                 ,"Running"
                                 ,"RampingDown"
                                 ,"RampedDown"
                                 ,"RampingUp" };

VariableDelay::VariableDelay(const TChar* aId, MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aDownstreamDelay, TUint aRampDuration)
    : iId(aId)
    , iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iDelayJiffies(0)
    , iLock("VDLY")
    , iDelayAdjustment(0)
    , iDownstreamDelay(aDownstreamDelay)
    , iRampDuration(aRampDuration)
    , iWaitForAudioBeforeGeneratingSilence(false)
    , iStreamHandler(nullptr)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
{
    ResetStatusAndRamp();
}

VariableDelay::~VariableDelay()
{
}

Msg* VariableDelay::Pull()
{
    Msg* msg = nullptr;
    AutoMutex _(iLock);
    if (iWaitForAudioBeforeGeneratingSilence) {
        do {
            msg = NextMsgLocked();
            if (msg != nullptr) {
                if (iWaitForAudioBeforeGeneratingSilence) {
                    return msg;
                }
                else {
                    DoEnqueue(msg);
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
            msg = NextMsgLocked();
        } while (msg == nullptr);
    }
    return msg;
}

Msg* VariableDelay::NextMsgLocked()
{
    Msg* msg;
    if (!IsEmpty()) {
        msg = DoDequeue();
    }
    else {
        iLock.Signal();
        msg = iUpstreamElement.Pull();
        iLock.Wait();
    }
    msg = msg->Process(*this);
    return msg;
}

MsgAudio* VariableDelay::DoProcessAudioMsg(MsgAudio* aMsg)
{
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
        if (iDelayAdjustment > 0) {
            // NotifyStarving() has been called since we last checked iDelayAdjustment in Pull()
            EnqueueAtHead(msg);
            return nullptr;
        }
        ASSERT(iDelayAdjustment < 0)
        TUint jiffies = msg->Jiffies();
        if (jiffies > (TUint)(-iDelayAdjustment)) {
            MsgAudio* remaining = msg->Split((TUint)(-iDelayAdjustment));
            jiffies = msg->Jiffies();
            EnqueueAtHead(remaining);
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

void VariableDelay::RampMsg(MsgAudio* aMsg)
{
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, iRampDirection, split);
    if (split != nullptr) {
        EnqueueAtHead(split);
    }
}

void VariableDelay::HandleStarving()
{
    AutoMutex _(iLock);
    iDelayAdjustment = iDelayJiffies;
    if (iDelayAdjustment == 0) {
        return;
    }
    switch (iStatus)
    {
    case EStarting:
        break;
    case ERunning:
        iStatus = ERampingDown;
        iRampDirection = Ramp::EDown;
        iCurrentRampValue = Ramp::kMax;
        iRemainingRampSize = iRampDuration;
        break;
    case ERampingDown:
        break;
    case ERampedDown:
        iWaitForAudioBeforeGeneratingSilence = true;
        break;
    case ERampingUp:
        iRampDirection = Ramp::EDown;
        // retain current value of iCurrentRampValue
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        if (iRemainingRampSize == 0) {
            iStatus = ERampedDown;
            iWaitForAudioBeforeGeneratingSilence = true;
        }
        else {
            iStatus = ERampingDown;
        }
        break;
    default:
        ASSERTS();
    }
}

void VariableDelay::ResetStatusAndRamp()
{
    iStatus = EStarting;
    iRampDirection = Ramp::ENone;
    iCurrentRampValue = Ramp::kMax;
    iRemainingRampSize = iRampDuration;
}

Msg* VariableDelay::ProcessMsg(MsgMode* aMsg)
{
    iMode.Replace(aMsg->Mode());
    iDelayJiffies = 0;
    iDelayAdjustment = 0;
    iWaitForAudioBeforeGeneratingSilence = true;
    ResetStatusAndRamp();
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgDrain* aMsg)
{
    iDelayAdjustment = iDelayJiffies;
    if (iDelayAdjustment == 0) {
        return aMsg;
    }
    iWaitForAudioBeforeGeneratingSilence = true;

    iRampDirection = Ramp::EDown;
    iCurrentRampValue = Ramp::kMin;
    iRemainingRampSize = 0;
    iStatus = ERampedDown;

    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgDelay* aMsg)
{
    TUint delayJiffies = aMsg->DelayJiffies();
    aMsg->RemoveRef();
    auto msg = iMsgFactory.CreateMsgDelay(iDownstreamDelay);
    LOG(kMedia, "VariableDelay::ProcessMsg(MsgDelay*): iId=%s, : delay=%u(%u), iDownstreamDelay=%u(%u), iDelayJiffies=%u(%u), iStatus=%s\n",
        iId, delayJiffies, delayJiffies / Jiffies::kPerMs,
        iDownstreamDelay, iDownstreamDelay / Jiffies::kPerMs,
        iDelayJiffies, iDelayJiffies / Jiffies::kPerMs,
        kStatus[iStatus]);
    delayJiffies = (iDownstreamDelay >= delayJiffies? 0 : delayJiffies - iDownstreamDelay);
    if (delayJiffies == iDelayJiffies) {
        return msg;
    }

    iDelayAdjustment += (TInt)(delayJiffies - iDelayJiffies);
    iDelayJiffies = delayJiffies;
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

    return msg;
}

Msg* VariableDelay::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamHandler = aMsg->StreamHandler();
    auto msg = iMsgFactory.CreateMsgEncodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* VariableDelay::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* VariableDelay::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iStreamHandler = stream.StreamHandler();
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();
    ResetStatusAndRamp();
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* VariableDelay::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iWaitForAudioBeforeGeneratingSilence) {
        iWaitForAudioBeforeGeneratingSilence = false;
        return aMsg;
    }
    return DoProcessAudioMsg(aMsg);
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

Msg* VariableDelay::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    // MsgPlayable not supported at this stage of the pipeline (as we don't know how to ramp it)
    ASSERTS();
    return nullptr;
}

Msg* VariableDelay::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

EStreamPlay VariableDelay::OkToPlay(TUint aStreamId)
{
    ASSERT(iStreamHandler != nullptr);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(aStreamId);
    //Log::Print("VariableDelay::OkToPlay(%u) iId=%s returned %u", iId, aStreamId, canPlay);
    return canPlay;
}

TUint VariableDelay::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    if (iStreamHandler != nullptr) {
        return iStreamHandler->TrySeek(aStreamId, aOffset);
    }
    return MsgFlush::kIdInvalid;
}

TUint VariableDelay::TryStop(TUint aStreamId)
{
    if (iStreamHandler != nullptr) {
        return iStreamHandler->TryStop(aStreamId);
    }
    return MsgFlush::kIdInvalid;
}

void VariableDelay::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    if (aStarving) {
        HandleStarving();
    }
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
