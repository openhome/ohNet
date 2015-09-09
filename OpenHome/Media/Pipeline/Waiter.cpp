#include <OpenHome/Media/Pipeline/Waiter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <atomic>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint Waiter::kSupportedMsgTypes =   eMode
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

Waiter::Waiter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IWaiterObserver& aObserver,
               IPipelineElementObserverThread& aObserverThread, TUint aRampDuration)
    : PipelineElement(kSupportedMsgTypes)
    , iFlusher(aUpstreamElement, "Waiter")
    , iMsgFactory(aMsgFactory)
    , iObserver(aObserver)
    , iObserverThread(aObserverThread)
    , iLock("WAIT")
    , iState(ERunning)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMax)
    , iTargetFlushId(MsgFlush::kIdInvalid)
{
    iEventWaiting.store(false);
    ASSERT(iEventWaiting.is_lock_free());
    iEventId = iObserverThread.Register(MakeFunctor(*this, &Waiter::ReportEvent));
}

Waiter::~Waiter()
{
}

void Waiter::Wait(TUint aFlushId, TBool aRampDown)
{
    // Wait can be called multiple times.
    AutoMutex a(iLock);
    if (aFlushId != iTargetFlushId) {
        iTargetFlushId = aFlushId;

        if (iState == ERampingUp) {
            iState = ERampingDown;
            if (iRampDuration == iRemainingRampSize) {
                // Already reached end of (previous) ramp down (and now ready to
                // start ramp up); go straight to flushing state.
                iState = EFlushing;
                DoWait();
            }
            else {
                iRemainingRampSize = iRampDuration - iRemainingRampSize;
            }
            // leave iCurrentRampValue unchanged
        }
        else if (!aRampDown || iState == EFlushing) {
            DoWait();
        }
        else if (iState != ERampingDown) {
            iState = ERampingDown;
            iRemainingRampSize = iRampDuration;
            iCurrentRampValue = Ramp::kMax;
        }
    }
}

Msg* Waiter::Pull()
{
    Msg* msg;
    do {
        msg = (iQueue.IsEmpty()? iFlusher.Pull() : iQueue.Dequeue());
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == nullptr);
    return msg;
}

Msg* Waiter::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Waiter::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Waiter::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == EFlushing); // Haven't received enough audio for a full ramp down.
        iTargetFlushId = MsgFlush::kIdInvalid;
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMin;
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
        ScheduleEvent(true);
    }
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (iState == EFlushing || iState == ERampingDown) {
        aMsg->RemoveRef();
        ASSERTS();
    }
    // iState may be ERampingUp if a MsgFlush was pulled
    if (iState == EWaiting || iState == ERampingUp) {
        ScheduleEvent(false);
    }
    NewStream();
    return aMsg;
}

Msg* Waiter::ProcessMsg(MsgAudioPcm* aMsg)
{
    HandleAudio();
    if (iState == ERampingDown || iState == ERampingUp) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != nullptr) {
                iQueue.EnqueueAtHead(split);
            }
        }
        split = nullptr;
        const Ramp::EDirection direction = (iState == ERampingDown? Ramp::EDown : Ramp::EUp);
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, direction, split);
        if (split != nullptr) {
            iQueue.EnqueueAtHead(split);
        }


        if (iRemainingRampSize == 0) {
            if (iState == ERampingDown) {
                DoWait();
                //aMsg->RemoveRef();
                //return nullptr;
            }
            else { // iState == ERampingUp
                iState = ERunning;
            }
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

Msg* Waiter::ProcessMsg(MsgSilence* aMsg)
{
    HandleAudio();
    if (iState == ERampingDown) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
        DoWait();
        //aMsg->RemoveRef();
        //return nullptr;
    }
    else if (iState == ERampingUp) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMax;
        iState = ERunning;
    }
    return ProcessFlushable(aMsg);
}

void Waiter::DoWait()
{
    iState = EFlushing;
    iQueue.Clear();
    iQueue.Enqueue(iMsgFactory.CreateMsgHalt()); /* inform downstream parties (StarvationMonitor)
                                                    that any subsequent break in audio is expected */
    iQueue.Enqueue(iMsgFactory.CreateMsgWait()); /* inform downstream elements (Songcast Sender)
                                                    of waiting state */
    ScheduleEvent(true);
    //iFlusher.DiscardUntilFlush(iTargetFlushId);
}

Msg* Waiter::ProcessFlushable(Msg* aMsg)
{
    if (iState == EFlushing) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

void Waiter::HandleAudio()
{
    if (iState == ERampingUp && iCurrentRampValue == Ramp::kMin) {
        // Start of ramping up.
        ScheduleEvent(false);
    }
    else if (iState == EWaiting) {
        iState = ERunning;
        ScheduleEvent(false);
    }
}

void Waiter::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    iState = ERunning;
}

void Waiter::ScheduleEvent(TBool aWaiting)
{
    iEventWaiting.store(aWaiting);
    iObserverThread.Schedule(iEventId);
}

void Waiter::ReportEvent()
{
    TBool waiting = iEventWaiting.load();
    iObserver.PipelineWaiting(waiting);
}
