#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Stopper::Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iLock("STP1")
    , iSem("STP2", 0)
    , iStreamPlayObserver(NULL)
    , iRampDuration(aRampDuration)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iTrackId(0)
    , iTrackIdPipeline(0)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iStreamHandler(NULL)
    , iQuit(false)
{
    iState = EStopped;
    NewStream();
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
}

void Stopper::BeginPause()
{
    AutoMutex a(iLock);
    LOG(kPipeline, "Stopper::BeginPause(), iState=%s\n", State());
    if (iQuit) {
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
        return;
    case ERampingUp:
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp down from whatever value it is already at
        SetState(ERampingDown);
        break;
    case EPaused:
    case EStopped:
        return;
    case EFlushing:
        HandleStopped();
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

    iTargetHaltId = aHaltId;
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
    Play();
}

Msg* Stopper::Pull()
{
    Msg* msg;
    do {
        if (iHaltPending) {
            msg = iMsgFactory.CreateMsgHalt();
            iHaltPending = false;
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
    } while (msg == NULL);
    return msg;
}

Msg* Stopper::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    /* IdManager expects OkToPlay to be called for every stream that is added to it.
       This isn't the case if CodecController fails to recognise the format of a stream.
       Catch this here by using iCheckedStreamPlayable to spot when we haven't tried to
       play a stream. */
    if (!iCheckedStreamPlayable) {
        if (iStreamHandler != NULL) {
            OkToPlay();
        }
        else if (iStreamPlayObserver != NULL) {
            iStreamPlayObserver->NotifyTrackFailed(iTrackId);
        }
    }

    NewStream();
    iTrackId = aMsg->Track().Id();
    iTrackIdPipeline = aMsg->IdPipeline();
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgEncodedStream* aMsg)
{
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
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgMetaText* aMsg)
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
    return NULL;
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
    return ProcessFlushable(aMsg);
}

Msg* Stopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgQuit* aMsg)
{
    if (iStreamHandler != NULL) {
        iStreamHandler->TryStop(iTrackIdPipeline, iStreamId);
    }
    return aMsg;
}

Msg* Stopper::ProcessFlushable(Msg* aMsg)
{
    if (iFlushStream) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

void Stopper::OkToPlay()
{
    EStreamPlay canPlay = iStreamHandler->OkToPlay(iTrackIdPipeline, iStreamId);
    switch (canPlay)
    {
    case ePlayYes:
        break;
    case ePlayNo:
        /*TUint flushId = */iStreamHandler->TryStop(iTrackIdPipeline, iStreamId);
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
    if (iStreamPlayObserver != NULL) {
        iStreamPlayObserver->NotifyStreamPlayStatus(iTrackId, iStreamId, canPlay);
    }
    iCheckedStreamPlayable = true;
}

Msg* Stopper::ProcessAudio(MsgAudio* aMsg)
{
    if (iState == ERampingDown || iState == ERampingUp) {
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
                if (iTargetHaltId == MsgHalt::kIdInvalid) {
                    SetState(EPaused);
                    (void)iSem.Clear();
                    iObserver.PipelinePaused();
                }
                else {
                    (void)iStreamHandler->TryStop(iTrackIdPipeline, iStreamId);
                    SetState(ERunning);
                    iFlushStream = true;
                }
                iHaltPending = true;
            }
            else { // iState == ERampingUp
                SetState(ERunning);
            }
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

void Stopper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    SetState(ERunning);
    iCheckedStreamPlayable = false;
    iHaltPending = false;
    iFlushStream = false;
}

void Stopper::HandleStopped()
{
    SetState(EStopped);
    (void)iSem.Clear();
    iObserver.PipelineStopped();
}

void Stopper::SetState(EState aState)
{
    LOG(kPipeline, "Stopper changing state from %s to %s\n", State(), State(aState));
    LOG(kPipeline, "  iRemainingRampSize=%u, iCurrentRampValue=%08x\n", iRemainingRampSize, iCurrentRampValue);
    iState = aState;
}

const TChar* Stopper::State() const
{
    return State(iState);
}

const TChar* Stopper::State(EState aState)
{ // static
    const TChar* state = NULL;
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
