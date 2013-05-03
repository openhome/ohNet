#include <OpenHome/Media/Stopper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

#include <climits>

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
    , iReportHalted(false)
    , iReportFlushed(false)
    , iFlushStream(false)
    , iRemovingStream(false)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
{
}

Stopper::~Stopper()
{
}

void Stopper::Start()
{
    iLock.Wait();
    ASSERT_DEBUG(iState != ERunning && iState != EFlushing);
    if (iRemovingStream) {
        ;
    }
    else if (iRemainingRampSize == iRampDuration || iFlushStream) {
        iState = ERunning;
    }
    else {
        iState = EStarting;
        iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
    }
    iSem.Signal();
    iLock.Signal();
}

void Stopper::BeginHalt()
{
    iLock.Wait();
    DoBeginHalt();
    iLock.Signal();
}

void Stopper::BeginFlush()
{
    ASSERT(iState == EHalted);
    iLock.Wait();
    iState = EFlushing;
    iTargetFlushId = iIdProvider.NextFlushId();
    iSupply.OutputFlush(iTargetFlushId);
    iSem.Signal();
    iLock.Signal();
}

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
        }
        else if (!iQueue.IsEmpty()) {
            msg = iQueue.Dequeue();
        }
        else {
            msg = iUpstreamElement.Pull();
        }
        iLock.Wait();
        msg = msg->Process(*this);
        // handling of EFlushing state is common across all message types so we might as well do it here
        if (iState == EFlushing && msg != NULL) {
            msg->RemoveRef();
            msg = NULL;
        }
        iLock.Signal();
        if (iReportHalted) {
            iObserver.PipelineHalted();
            iReportHalted = false;
        }
        else if (iReportFlushed) {
            iObserver.PipelineFlushed();
            iReportFlushed = false;
        }
    } while (msg == NULL);
    return msg;
}

void Stopper::RemoveStream(TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    if (iTrackId == aTrackId && iStreamId == aStreamId) {
        iRemovingStream = true;
        DoBeginHalt();
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
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iFlushStream = iRemovingStream = false;
    iState = ERunning;

    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iStreamId = streamInfo.StreamId();
    IStreamHandler* sh = streamInfo.StreamHandler();
    if (sh->OkToPlay(iTrackId, streamInfo.StreamId()) == ePlayNo) {
        /*TUint flushId = */sh->TryStop(iTrackId, streamInfo.StreamId());
        iFlushStream = true;
        aMsg->RemoveRef();
        return NULL;
    }
    // FIXME - should maybe issue a halt if OkToPlay returns false (all cases) or true (for a live stream)
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
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
    iState = EHalted;
    iReportHalted = true;
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId == aMsg->Id()) { // flush may arrive as a result of either a Pause or a Seek
        iState = EHalted;
        iReportFlushed = true;
        iTargetFlushId = MsgFlush::kIdInvalid;
    }
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
        ASSERTS();
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
            if (iRemovingStream) {
                iState = ERunning;
                iRemovingStream = false;
                iFlushStream = true;
            }
            else {
                iState = EHaltPending;
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
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRampDuration, aDirection, split);
    if (split != NULL) {
        iQueue.EnqueueAtHead(split);
    }
    iRemainingRampSize -= aMsg->Jiffies();
}

void Stopper::DoBeginHalt()
{
    ASSERT_DEBUG(iState != EFlushing);
    iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
    iState = EHalting;
}
