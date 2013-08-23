#include <OpenHome/Media/Stopper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Stopper

Stopper::Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISupply& aSupply, IFlushIdProvider& aIdProvider, IStopperObserver& aObserver, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iSupply(aSupply)
    , iIdProvider(aIdProvider)
    , iObserver(aObserver)
    , iLock("MSTP")
    , iSem("SSTP", 0)
    , iState(EHalted)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kRampMin)
    //, iReportHalted(false)
    //, iReportFlushed(false)
    , iFlushStream(false)
    , iRemovingStream(false)
    , iResumeAfterHalt(false)
    //, iStopping(false)
    //, iInStream(false)
    //, iTargetFlushId(MsgFlush::kIdInvalid)
    , iTargetHaltId(MsgHalt::kIdNone)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iStreamHandler(NULL)
{
}

Stopper::~Stopper()
{
}

void Stopper::Start()
{
    AutoMutex a(iLock);
    //ASSERT_DEBUG(iState != ERunning && iState != EFlushing);
    if (iState == ERunning) {
        return;
    }
    if (iRemainingRampSize == iRampDuration || iFlushStream) {
        iState = ERunning;
    }
    else {
        iState = EStarting;
        if (!iRemovingStream) {
            iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
        }
    }
    iTargetHaltId = MsgHalt::kIdNone;
    //iStopping = false;
    iSem.Signal();
}

void Stopper::BeginHalt()
{
    iLock.Wait();
    iTargetHaltId = MsgHalt::kIdNone;
    //iStopping = true;
    //iResumeAfterHalt = true; // FIXME - seems wrong
    DoBeginHalt();
    iLock.Signal();
}

void Stopper::BeginHalt(TUint aHaltId)
{
    iLock.Wait();
    iTargetHaltId = aHaltId;
    iResumeAfterHalt = false;
    DoBeginHalt();
    iLock.Signal();
}

/*void Stopper::BeginFlush()
{
    ASSERT(iState == EHalted);
    iLock.Wait();
    DoBeginFlush();
    iLock.Signal();
}*/

Msg* Stopper::Pull()
{
    Msg* msg;
    do {
        iLock.Wait();
        TBool wait = false;
        if (iState == EHalted) {
            wait = true;
            (void)iSem.Clear();
        }
        iLock.Signal();
        if (wait) {
            iSem.Wait();
        }
        if (iState == EHaltPending) {
            msg = iMsgFactory.CreateMsgHalt();
            if (iResumeAfterHalt) {
                iState = ERunning;
                iResumeAfterHalt = false;
            }
            else {
                iState = EHalted;
                iObserver.PipelineHalted(static_cast<MsgHalt*>(msg)->Id());
            }
        }
        else {
            msg = iQueue.IsEmpty()? iUpstreamElement.Pull() :
                                    iQueue.Dequeue();
            iLock.Wait();
            msg = msg->Process(*this);
            iLock.Signal();
        }
        // handling of EFlushing state is common across all message types so we might as well do it here
        if (iState == EFlushing && msg != NULL) {
            msg->RemoveRef();
            msg = NULL;
        }
        if (iState == EFlushPending) {
            iState = EFlushing;
        }
        /*if (iState == EHalted && iResumeAfterHalt) {
            iResumeAfterHalt = false;
            iReportHalted = false;
            iState = ERunning;
        }*/
        /*if (iReportHalted) {
            iObserver.PipelineHalted();
            iReportHalted = false;
        }
        else if (iReportFlushed) {
            iObserver.PipelineFlushed();
            iReportFlushed = false;
        }*/
    } while (msg == NULL);
    return msg;
}

void Stopper::RemoveCurrentStream()
{
    iLock.Wait();
    DoRemoveCurrentStream();
    iLock.Signal();
}

void Stopper::DoRemoveCurrentStream()
{
    iRemovingStream = true;
    DoBeginHalt();
}

void Stopper::RemoveStream(TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    if (iTrackId == aTrackId && iStreamId == aStreamId) {
        DoRemoveCurrentStream();
    }
    iLock.Signal();
}

Msg* Stopper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iFlushStream) {
        aMsg->RemoveRef();
        return NULL;
    }
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgSilence* aMsg)
{
    if (iFlushStream) {
        aMsg->RemoveRef();
        return NULL;
    }
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // can't process MsgPlayable sensibly (e.g. they can't be ramped)
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iFlushStream = iRemovingStream = false;
    iState = ERunning;

    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    if (iStreamHandler->OkToPlay(iTrackId, iStreamId) == ePlayNo) {
        /*TUint flushId = */iStreamHandler->TryStop(iTrackId, iStreamId);
        iFlushStream = true;
    }
    // FIXME - move to state Halted if ePlayLater
    // FIXME - should maybe issue a halt if OkToPlay returns false (all cases) or true (for a live stream)
    aMsg->RemoveRef();
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgMetaText* aMsg)
{
    if (iFlushStream) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgHalt* aMsg)
{
    if (iTargetHaltId == MsgHalt::kIdNone || aMsg->Id() == iTargetHaltId) {
        iState = EHalted;
        iTargetHaltId = MsgHalt::kIdNone;
    }
    iObserver.PipelineHalted(aMsg->Id());
    /*iState = EHalted;
    //if (aMsg->Id() == iTargetHaltId) {
    //    iTargetHaltId = MsgHalt::kIdNone;
        iObserver.PipelineHalted(aMsg->Id());
    //}*/
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgFlush* aMsg)
{
    /*if (iTargetFlushId == aMsg->Id()) { // flush may arrive as a result of either a Stop or a Seek
        iState = EHalted;
        //iReportFlushed = true;
        iTargetFlushId = MsgFlush::kIdInvalid;
    }*/
    aMsg->RemoveRef();
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsgAudio(MsgAudio* aMsg)
{
    switch (iState)
    {
    case ERunning:
    case EFlushing:
        break;
    case EHalted:
        ASSERT(iRemovingStream);
        break;
    case EStarting:
        Ramp(aMsg, Ramp::EUp);
        if (iRemainingRampSize == 0) {
            iState = ERunning;
        }
        break;
    case EHalting:
        Ramp(aMsg, Ramp::EDown);
        if (iRemainingRampSize == 0) {
            if (iTargetHaltId != MsgHalt::kIdNone) {
                iState = EFlushPending;
                /*TUint flushId = */iStreamHandler->TryStop(iTrackId, iStreamId);
            }
            else {
                iState = EHaltPending;
                if (iRemovingStream) {
                    iRemovingStream = false;
                    iResumeAfterHalt = true;
                    /*TUint flushId = */iStreamHandler->TryStop(iTrackId, iStreamId);
                    iFlushStream = true;
                }
            }
            // FIXME - may need to empty/delete iQueue
            // ... or could hang onto them and see whether they're still relevant if we restart playing?
        }
        break;
    default:
        ASSERTS();
        break;
    }
    return aMsg;
}

void Stopper::Ramp(MsgAudio* aMsg, Ramp::EDirection aDirection)
{
    if (iRemainingRampSize == 0) {
        // may happen if we receive a MsgTrack while ramping
        return;
    }
    MsgAudio* split;
    if (aMsg->Jiffies() > iRemainingRampSize) {
        split = aMsg->Split(iRemainingRampSize);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
    }
    split = NULL;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, aDirection, split);
    if (split != NULL) {
        iQueue.EnqueueAtHead(split);
    }
}

void Stopper::DoBeginHalt()
{
    ASSERT_DEBUG(iState != EFlushing);
    /*if (!iInStream) {
        iState = EHaltPending;
        iResumeAfterHalt = false;
    }
    else */if (iState == ERunning || iState == EStarting) {
        iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
        iState = EHalting;
    }
}
/*
void Stopper::DoBeginFlush()
{
    iState = EFlushing;
    iTargetFlushId = MsgFlush::kIdInvalid;
    if (iStreamHandler != NULL) {
        iTargetFlushId = iStreamHandler->TryStop(iTrackId, iStreamId);
    }
    if (iTargetFlushId == MsgFlush::kIdInvalid) {
        iTargetFlushId = iIdProvider.NextFlushId();
        iSupply.OutputFlush(iTargetFlushId);
    }
    iSem.Signal();
}
*/
