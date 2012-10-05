#include <OpenHome/Media/Stopper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Stopper

Stopper::Stopper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, IStopperObserver& aObserver, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iLock("MSTP")
    , iSem("SSTP", 0)
    , iState(EHalted)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kRampMin)
    , iReportHalted(false)
    , iReportFlushed(false)
{
}

void Stopper::Start()
{
    iLock.Wait();
    ASSERT_DEBUG(iState != ERunning && iState != EFlushing);
    if (iRemainingRampSize == iRampDuration) {
        iState = ERunning;
    }
    else {
        iState = EStarting;
        iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
//        Log::Print("Start, iRemainingRampSize=%u\n", iRemainingRampSize);
    }
    iSem.Signal();
    iLock.Signal();
}

void Stopper::BeginHalt()
{
    iLock.Wait();
    ASSERT_DEBUG(iState != EFlushing);
    iRemainingRampSize = (iRemainingRampSize == 0? iRampDuration : iRampDuration - iRemainingRampSize);
    iState = EHalting;
    iLock.Signal();
}

void Stopper::BeginFlush()
{
    ASSERT(iState == EHalted);
    iLock.Wait();
    iState = EFlushing;
    while (!iQueue.IsEmpty()) {
        iQueue.Dequeue()->RemoveRef();
    }
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
        if (iState == EFlushing) {
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

Msg* Stopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    //Log::Print("Stopper - MsgAudioPcm(%p), jiffies=%u\n", aMsg, aMsg->Jiffies()); // FIXME - add to ohNet's debug system
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgSilence* aMsg)
{
    //Log::Print("Stopper - MsgSilence(%p)\n", aMsg);
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // can't process MsgPlayable sensibly (e.g. they can't be ramped)
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgAudioFormat* aMsg)
{
    //Log::Print("Stopper - MsgAudioFormat(%p)\n", aMsg);
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    //Log::Print("Stopper - MsgTrack(%p)\n", aMsg);
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgMetaText* aMsg)
{
    //Log::Print("Stopper - MsgMetaText(%p)\n", aMsg);
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgHalt* aMsg)
{
    //Log::Print("Stopper - MsgHalt(%p)\n", aMsg);
    iState = EHalted;
    iReportHalted = true;
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgFlush* aMsg)
{
    //Log::Print("Stopper - MsgFlush(%p)\n", aMsg);
    ASSERT_DEBUG(iState == EFlushing);
    aMsg->RemoveRef();
    iState = EHalted;
    iReportFlushed = true;
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgQuit* aMsg)
{
    //Log::Print("Stopper - MsgQuit(%p)\n", aMsg);
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
            iState = EHaltPending;
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
