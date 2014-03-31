#include <OpenHome/Media/Waiter.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Waiter::Waiter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IWaiterObserver& aObserver, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iLock("WAIT")
    , iState(ERunning)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kRampMax)
    , iTargetFlushId(MsgFlush::kIdInvalid)
{
}

Waiter::~Waiter()
{
}

void Waiter::Wait(TUint aFlushId, TBool aRampDown)
{
    AutoMutex a(iLock);
    ASSERT(iState == ERunning); // Already in process of waiting.
    iTargetFlushId = aFlushId;

    if (iState == ERampingUp) {
        iState = ERampingDown;
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // leave iCurrentRampValue unchanged
    }
    else if (!aRampDown || iState == EFlushing) {
        DoWait();
    }
    else {
        iState = ERampingDown;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kRampMax;
    }
}

Msg* Waiter::Pull()
{
    Msg* msg;
    do {
        msg = (iQueue.IsEmpty()? iUpstreamElement.Pull() : iQueue.Dequeue());
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

Msg* Waiter::ProcessMsg(MsgTrack* aMsg)
{
    if (iState != ERunning && iState != ERampingUp) {
        // Could ramp down, then receive expected flush, which puts this back
        // into ramping up state, then receive a new MsgTrack during ramp up.
        aMsg->RemoveRef();
        ASSERTS();
    }
    NewStream();
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (iState != ERunning) {
        aMsg->RemoveRef();
        ASSERTS();
    }
    NewStream();
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Waiter::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Waiter::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == EFlushing); // haven't received enough audio for a full ramp down
        // FIXME - the above ASSERT can be expected at the moment if we
        // pause/unpause/seek too quickly as the VariableDelay pipeline element
        // does not currently give us a 2s buffer.
        aMsg->RemoveRef();
        iTargetFlushId = MsgFlush::kIdInvalid;
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kRampMin;
        return NULL;
    }
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgWait* aMsg)
{
    // Can receive a MsgWait here that we've queued ourselves in response to an
    // expected MsgFlush, or coming down through the pipeline via Songcast.

    if (iState != EFlushing) {
        // Received a MsgWait through the pipeline, via Songcast protocol.
        iState = EWaiting;
        iObserver.PipelineWaiting(true);
    }
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Waiter::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Waiter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Waiter::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

void Waiter::DoWait()
{
    iState = EFlushing;
    while (!iQueue.IsEmpty()) {
        iQueue.Dequeue()->RemoveRef();
    }
    iQueue.Enqueue(iMsgFactory.CreateMsgHalt()); /* inform downstream parties (StarvationMonitor)
                                                    that any subsequent break in audio is expected */
    iQueue.Enqueue(iMsgFactory.CreateMsgWait()); /* inform downstream elements (Songcast Sender)
                                                    of waiting state */
    iObserver.PipelineWaiting(true);
}

Msg* Waiter::ProcessFlushable(Msg* aMsg)
{
    if (iState == EFlushing) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* Waiter::ProcessAudio(MsgAudio* aMsg)
{
    if (iState == ERampingDown || iState == ERampingUp) {
        if (iState == ERampingUp && iCurrentRampValue == Ramp::kRampMin) {
            // Start of ramping up.
            iObserver.PipelineWaiting(false);
        }

        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != NULL) {
                iQueue.EnqueueAtHead(split);
            }
        }
        split = NULL;
        const Ramp::EDirection direction = (iState == ERampingDown? Ramp::EDown : Ramp::EUp);
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, direction, split);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            if (iState == ERampingDown) {
                DoWait();
            }
            else { // iState == ERampingUp
                iState = ERunning;
            }
        }
        return aMsg;
    }
    else if (iState == EWaiting) {
        iState = ERunning;
        iObserver.PipelineWaiting(false);
    }

    return ProcessFlushable(aMsg);
}

void Waiter::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iState = ERunning;
}
