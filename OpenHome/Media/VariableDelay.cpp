#include <OpenHome/Media/VariableDelay.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// VariableDelay

VariableDelay::VariableDelay(MsgFactory& aMsgFactory, IPipelineElement& aUpstreamElement, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iDelayJiffies(0)
    , iLock("VDLY")
    , iDelayAdjustment(0)
    , iStatus(ERunning)
    , iRampDirection(Ramp::ENone)
    , iRampDuration(aRampDuration)
    , iCurrentRampValue(Ramp::kRampMax)
    , iRemainingRampSize(0)
{
}

VariableDelay::~VariableDelay()
{
}

void VariableDelay::AdjustDelay(TUint aJiffies)
{
    AutoMutex a(iLock);
    if (aJiffies == iDelayJiffies) {
        return;
    }
    iDelayAdjustment += (aJiffies - iDelayJiffies);
    iDelayJiffies = aJiffies;
    iStatus = ERampingDown;
    iRampDirection = Ramp::EDown;
    iCurrentRampValue = Ramp::kRampMax;
    iRemainingRampSize = iRampDuration;
}

Msg* VariableDelay::Pull()
{
    Msg* msg;
    iLock.Wait();
    if (iStatus == ERampedDown && iDelayAdjustment > 0) {
        const TUint size = ((TUint)iDelayAdjustment > kMaxMsgSilenceDuration? kMaxMsgSilenceDuration : (TUint)iDelayAdjustment);
        msg = iMsgFactory.CreateMsgSilence(size);
        iDelayAdjustment -= size;
        if (iDelayAdjustment == 0) {
            iStatus = ERampingUp;
            iRampDirection = Ramp::EUp;
            iCurrentRampValue = Ramp::kRampMin;
            iRemainingRampSize = iRampDuration;
        }
    }
    else {
        do {
            iLock.Signal();
            if (!iQueue.IsEmpty()) {
                msg = iQueue.Dequeue();
            }
            else {
                msg = iUpstreamElement.Pull();
            }
            iLock.Wait();
            msg = msg->Process(*this);
        } while (msg == NULL);
    }
    iLock.Signal();
    return msg;
}

MsgAudio* VariableDelay::DoProcessAudioMsg(MsgAudio* aMsg)
{
    MsgAudio* msg = aMsg;
    switch (iStatus)
    {
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
        ASSERT(iDelayAdjustment < 0)
        TUint jiffies = msg->Jiffies();
        if (jiffies > (TUint)(-iDelayAdjustment)) {
            MsgAudio* remaining = msg->Split((TUint)(-iDelayAdjustment));
            jiffies = msg->Jiffies();
            iQueue.EnqueueAtHead(remaining);
        }
        iDelayAdjustment += jiffies;
        msg->RemoveRef();
        msg = NULL;
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
        iQueue.Enqueue(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRampDuration, iRampDirection, split);
    if (split != NULL) {
        iQueue.Enqueue(split);
    }
    iRemainingRampSize -= aMsg->Jiffies();
}

Msg* VariableDelay::ProcessMsg(MsgAudioPcm* aMsg)
{
    return DoProcessAudioMsg(aMsg);
}

Msg* VariableDelay::ProcessMsg(MsgSilence* aMsg)
{
    return DoProcessAudioMsg(aMsg);
}

Msg* VariableDelay::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    // MsgPlayable not supported at this stage of the pipeline (as we don't know how to ramp it)
    ASSERTS();
    return NULL;
}

Msg* VariableDelay::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* VariableDelay::ProcessMsg(MsgMetaText* aMsg)
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

Msg* VariableDelay::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
