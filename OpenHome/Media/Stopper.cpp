#include <OpenHome/Media/Stopper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Stopper::Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iLock("STP1")
    , iSem("STP2", 0)
    , iRampDuration(aRampDuration)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iStreamHandler(NULL)
    , iQuit(false)
{
    NewStream();
    iState = EStopped;
}

Stopper::~Stopper()
{
}

void Stopper::Play()
{
    AutoMutex a(iLock);
    switch (iState)
    {
    case ERunning:
        break;
    case ERampingDown:
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp up from whatever value it is already at
        break;
    case ERampingUp:
        // We're already starting.  No Benefit in allowing another Play request to interrupt this.
        break;
    case EPaused:
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iSem.Signal();
        break;
    case EStopped:
        iState = ERunning;
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
    if (iQuit) {
        return;
    }
    switch (iState)
    {
    case ERunning:
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kRampMax;
        iState = ERampingDown;
        break;
    case ERampingDown:
        // We're already pausing.  No Benefit in allowing another Pause request to interrupt this.
        return;
    case ERampingUp:
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp down from whatever value it is already at
        iState = ERampingDown;
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
    if (iQuit) {
        return;
    }

    switch (iState)
    {
    case ERunning:
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kRampMax;
        iState = ERampingDown;
        break;
    case ERampingDown:
        break;
    case ERampingUp:
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // don't change iCurrentRampValue - just start ramp down from whatever value it is already at
        iState = ERampingDown;
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

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    NewStream();
    iTrackId = aMsg->IdPipeline();
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

Msg* Stopper::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (!aMsg->StreamInfo().Live()) {
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
    EStreamPlay canPlay = iStreamHandler->OkToPlay(iTrackId, iStreamId);
    switch (canPlay)
    {
    case ePlayYes:
        break;
    case ePlayNo:
        /*TUint flushId = */iStreamHandler->TryStop(iTrackId, iStreamId);
        iState = EFlushing;
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
                    iState = EPaused;
                    (void)iSem.Clear();
                    iObserver.PipelinePaused();
                }
                else {
                    iState = ERunning;
                    iFlushStream = true;
                }
                iHaltPending = true;
            }
            else { // iState == ERampingUp
                iState = ERunning;
            }
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

void Stopper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iState = ERunning;
    iHaltPending = false;
    iFlushStream = false;
}

void Stopper::HandleStopped()
{
    iState = EStopped;
    (void)iSem.Clear();
    iObserver.PipelineStopped();
}
