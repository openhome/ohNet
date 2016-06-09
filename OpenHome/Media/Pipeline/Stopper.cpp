#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <atomic>

using namespace OpenHome;
using namespace OpenHome::Media;

Stopper::Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver,
                 IPipelineElementObserverThread& aObserverThread, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iObserverThread(aObserverThread)
    , iLock("STP1")
    , iSem("STP2", 0)
    , iStreamPlayObserver(nullptr)
    , iRampDuration(aRampDuration)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iTrackId(0)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iStreamHandler(nullptr)
    , iBuffering(false)
    , iQuit(false)
{
    iState = EStopped;
    iEventState.store(EEventNone);
    ASSERT(iEventState.is_lock_free());
    iEventId = iObserverThread.Register(MakeFunctor(*this, &Stopper::ReportEvent));
    NewStream();
    iCheckedStreamPlayable = true; // override setting from NewStream() - we don't want to call OkToPlay() when we see a first MsgTrack
}

Stopper::~Stopper()
{
}

void Stopper::SetStreamPlayObserver(IStreamPlayObserver& aObserver)
{
    iStreamPlayObserver = &aObserver;
}

void Stopper::Play()
{
    AutoMutex a(iLock);
    LOG(kPipeline, "Stopper::Play(), iState=%s\n", State());
    switch (iState)
    {
    case ERunning:
        break;
    case ERampingDown:
        SetState(ERampingUp);
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp up from whatever value it is already at
        break;
    case ERampingUp:
        // We're already starting.  No Benefit in allowing another Play request to interrupt this.
        break;
    case EPaused:
        SetState(ERampingUp);
        iRemainingRampSize = iRampDuration;
        iSem.Signal();
        break;
    case EStopped:
        SetState(ERunning);
        iSem.Signal();
        break;
    case EFlushing:
        break;
    }
    iTargetHaltId = MsgHalt::kIdInvalid;
    ScheduleEvent(EEventPlaying);
}

void Stopper::BeginPause()
{
    AutoMutex a(iLock);
    LOG(kPipeline, "Stopper::BeginPause(), iState=%s\n", State());
    if (iQuit) {
        return;
    }

    if (iBuffering) {
        HandlePaused();
        return;
    }

    switch (iState)
    {
    case ERunning:
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMax;
        SetState(ERampingDown);
        break;
    case ERampingDown:
        // We're already pausing.  No Benefit in allowing another Pause request to interrupt this.
        break;
    case ERampingUp:
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp down from whatever value it is already at
        SetState(ERampingDown);
        break;
    case EPaused:
        break;
    case EStopped:
    case EFlushing:
        HandlePaused();
        break;
    }
}

void Stopper::BeginStop(TUint aHaltId)
{
    AutoMutex a(iLock);
    LOG(kPipeline, "Stopper::BeginStop(%u), iState=%s\n", aHaltId, State());
    if (iQuit) {
        return;
    }

    iTargetHaltId = aHaltId;
    if (iBuffering) {
        HandleStopped();
        return;
    }

    switch (iState)
    {
    case ERunning:
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMax;
        SetState(ERampingDown);
        break;
    case ERampingDown:
        break;
    case ERampingUp:
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp down from whatever value it is already at
        SetState(ERampingDown);
        break;
    case EPaused:
        // restart pulling, discarding data until a new stream or our target MsgHalt
        iSem.Signal();
        iFlushStream = true;
        break;
    case EStopped:
        return;
    case EFlushing:
        HandleStopped();
        break;
    }
}

void Stopper::StopNow()
{
    iLock.Wait();
    HandleStopped();
    iLock.Signal();
}

void Stopper::Quit()
{
    iQuit = true;
    if (iState == EStopped || iState == EPaused) {
        iFlushStream = true;
    }
    Play();
}

Msg* Stopper::Pull()
{
    Msg* msg;
    do {
        if (iHaltPending) {
            if (iQueue.IsEmpty()) {
                msg = iMsgFactory.CreateMsgHalt();
                iHaltPending = false;
            }
            else {
                msg = iQueue.Dequeue();
            }
        }
        else {
            if (iState == EPaused || iState == EStopped) {
                LOG(kPipeline, "Stopper::Pull(), waiting, iState=%s\n", State());
                iSem.Wait();
            }
            msg = (iQueue.IsEmpty()? iUpstreamElement.Pull() : iQueue.Dequeue());
            iLock.Wait();
            msg = msg->Process(*this);
            iLock.Signal();
        }
    } while (msg == nullptr);
    iLock.Wait();
    iBuffering = false;
    iLock.Signal();
    return msg;
}

Msg* Stopper::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    /* IdManager expects OkToPlay to be called for every stream that is added to it.
       This isn't the case if CodecController fails to recognise the format of a stream.
       Catch this here by using iCheckedStreamPlayable to spot when we haven't tried to
       play a stream. */
    if (aMsg->StartOfStream()) {
        if (!iCheckedStreamPlayable) {
            if (iStreamHandler != nullptr) {
                OkToPlay();
            }
            else if (iStreamPlayObserver != nullptr) {
                iStreamPlayObserver->NotifyTrackFailed(iTrackId);
                iCheckedStreamPlayable = true;
            }
        }
        NewStream();
    }

    iTrackId = aMsg->Track().Id();
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgEncodedStream* aMsg)
{
    /* IdManager expects OkToPlay to be called for every stream that is added to it.
       This isn't the case if CodecController fails to recognise the format of a stream.
       Catch this here by using iCheckedStreamPlayable to spot when we haven't tried to
       play a stream. */
    if (!iCheckedStreamPlayable && iStreamHandler != nullptr) {
        OkToPlay();
    }

    NewStream();
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    if (aMsg->Live()) {
        /* we won't receive MsgDecodedStream (or anything else) until we call OkToPlay
           Don't want to do this unconditionally, as waiting for MsgDecodedStream for
           non-live streams allows additional metadata to make it to the Reporter before
           we risk the pipeline stalling when response to OkToPlay is eLater. */
        OkToPlay();
    }
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Stopper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Stopper::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Stopper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Stopper::ProcessMsg(MsgHalt* aMsg)
{
    if (iTargetHaltId == aMsg->Id()) {
        iTargetHaltId = MsgHalt::kIdInvalid;
        HandleStopped();
    }
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgFlush* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Stopper::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (!aMsg->StreamInfo().Live() && !iCheckedStreamPlayable) {
        OkToPlay();
    }
    Msg* msg = ProcessFlushable(aMsg);
    if (msg != nullptr) {
        msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
        aMsg->RemoveRef();
    }
    return msg;
}

Msg* Stopper::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iState == ERampingDown || iState == ERampingUp) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize && iRemainingRampSize > 0) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != nullptr) {
                if (iState == ERampingDown) {
                    split->SetMuted();
                }
                iQueue.EnqueueAtHead(split);
            }
        }
        split = nullptr;
        const Ramp::EDirection direction = (iState == ERampingDown? Ramp::EDown : Ramp::EUp);
        if (iRemainingRampSize > 0) {
            iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, direction, split);
        }
        if (split != nullptr) {
            if (iState == ERampingDown) {
                split->SetMuted();
            }
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            RampCompleted();
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

Msg* Stopper::ProcessMsg(MsgSilence* aMsg)
{
    if (iState == ERampingDown || iState == ERampingUp) {
        RampCompleted();
    }
    return ProcessFlushable(aMsg);
}

Msg* Stopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Stopper::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

EStreamPlay Stopper::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint Stopper::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Stopper::TryDiscard(TUint aJiffies)
{
    // no need for locking - this is guaranteed to only be called from the same thread as Pull()
    return iStreamHandler->TryDiscard(aJiffies);
}

TUint Stopper::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void Stopper::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    AutoMutex _(iLock);
    if (aStarving) {
        if (iState != ERampingDown) {
            iBuffering = true;
        }
        else {
            if (iTargetHaltId == MsgHalt::kIdInvalid) {
                HandlePaused();
            }
            else {
                HandleStopped();
            }
        }
    }
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}

Msg* Stopper::ProcessFlushable(Msg* aMsg)
{
    if (iFlushStream) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

void Stopper::OkToPlay()
{
    ASSERT(iStreamHandler != nullptr);
    EStreamPlay canPlay = iStreamHandler->OkToPlay(iStreamId);
    if (iQuit) {
        SetState(EFlushing);
        iFlushStream = true;
    }
    else {
        LOG(kPipeline, "Stopper - OkToPlay returned %s.  trackId=%u, streamId=%u.\n", kStreamPlayNames[canPlay], iTrackId, iStreamId);

        switch (canPlay)
        {
        case ePlayYes:
            ScheduleEvent(EEventPlaying);
            break;
        case ePlayNo:
            /*TUint flushId = */iStreamHandler->TryStop(iStreamId);
            SetState(EFlushing);
            iFlushStream = true;
            iHaltPending = true;
            break;
        case ePlayLater:
            HandleStopped();
            iHaltPending = true;
            break;
        default:
            ASSERTS();
        }
    }
    if (iStreamPlayObserver != nullptr) {
        iStreamPlayObserver->NotifyStreamPlayStatus(iTrackId, iStreamId, canPlay);
    }
    iCheckedStreamPlayable = true;
}

void Stopper::RampCompleted()
{
    if (iState == ERampingDown) {
        if (iTargetHaltId == MsgHalt::kIdInvalid) {
            HandlePaused();
        }
        else {
            ASSERT(iStreamHandler != nullptr);
            (void)iStreamHandler->TryStop(iStreamId);
            SetState(ERunning);
            iFlushStream = true;
        }
        iHaltPending = true;
    }
    else { // iState == ERampingUp
        SetState(ERunning);
    }
}

void Stopper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    SetState(ERunning);
    iStreamHandler = nullptr;
    iCheckedStreamPlayable = false;
    iHaltPending = false;
    iFlushStream = false;
}

void Stopper::HandlePaused()
{
    SetState(EPaused);
    (void)iSem.Clear();
    ScheduleEvent(EEventPaused);
}

void Stopper::HandleStopped()
{
    SetState(EStopped);
    (void)iSem.Clear();
    ScheduleEvent(EEventStopped);
}

void Stopper::SetState(EState aState)
{
    if (iState != aState) {
        LOG(kPipeline, "Stopper changing state from %s to %s\n", State(), State(aState));
        LOG(kPipeline, "  iRemainingRampSize=%u, iCurrentRampValue=%08x\n", iRemainingRampSize, iCurrentRampValue);
        iState = aState;
    }
}

void Stopper::ScheduleEvent(EEventedState aState)
{
    iEventState.store(aState);
    iObserverThread.Schedule(iEventId);
}

void Stopper::ReportEvent()
{
    EEventedState state = iEventState.exchange(EEventNone);
    switch (state)
    {
    case EEventPlaying:
        iObserver.PipelinePlaying();
        break;
    case EEventPaused:
        iObserver.PipelinePaused();
        break;
    case EEventStopped:
        iObserver.PipelineStopped();
        break;
    case EEventNone:
        break;
    }
}

const TChar* Stopper::State() const
{
    return State(iState);
}

const TChar* Stopper::State(EState aState)
{ // static
    const TChar* state = nullptr;
    switch (aState)
    {
    case ERunning:
        state = "Running";
        break;
    case ERampingDown:
        state = "RampingDown";
        break;
    case ERampingUp:
        state = "RampingUp";
        break;
    case EPaused:
        state = "Paused";
        break;
    case EStopped:
        state = "Stopped";
        break;
    case EFlushing:
        state = "Flushing";
        break;
    default:
        ASSERTS();
    }
    return state;
}
