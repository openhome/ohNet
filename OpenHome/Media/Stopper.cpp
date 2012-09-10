#include <OpenHome/Media/Stopper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Stopper

Stopper::Stopper(IStopperObserver& aObserver, IPipelineElement& aUpstreamElement)
    : iObserver(aObserver)
    , iUpstreamElement(aUpstreamElement)
    , iLock("MSTP")
    , iSem("SSTP", 0)
    , iState(EHalted)
    , iRampDuration(0xffffffff)
    , iRemainingRampSize(0xffffffff)
    , iCurrentRampValue(Ramp::kRampMin)
{
}

void Stopper::Start(TUint aRampDuration)
{
    iLock.Wait();
    ASSERT_DEBUG(iState != ERunning && iState != EFlushing);
    iState = EStarting;
    iRampDuration = aRampDuration;
    iRemainingRampSize = iRampDuration;
    iSem.Signal();
    iLock.Signal();
}

void Stopper::BeginHalt(TUint aRampDuration)
{
    iLock.Wait();
    ASSERT_DEBUG(iState != EFlushing);
    iRampDuration = aRampDuration;
    iRemainingRampSize = iRampDuration;
    iState = EHalting;
    iLock.Signal();
}

void Stopper::BeginFlush()
{
    ASSERT(iState == EHalted);
    iLock.Wait();
    iState = EFlushing;
    for (TUint i=0; i<kMaxStoredMsg; i++) {
        while (!iQueue.IsEmpty()) {
            iQueue.Dequeue()->RemoveRef();
        }
    }
    iLock.Signal();
}

Msg* Stopper::Pull()
{
    Msg* msg;
    do {
        iLock.Wait();
        const TBool wait = (iState == EHalted);
        iLock.Signal();
        if (wait) {
            iSem.Wait();
        }
        if (iQueue.IsEmpty()) {
            msg = iUpstreamElement.Pull();
        }
        else {
            msg = iQueue.Dequeue();
        }
        msg = msg->Process(*this);
        // handling of EFlushing state is common across all message types so we might as well do it here
        if (iState == EFlushing) {
            msg->RemoveRef();
            msg = NULL;
        }
    } while (msg == NULL);
    return msg;
}

Msg* Stopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessMsgAudio(aMsg);
}

Msg* Stopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // can't process MsgPlayable sensibly (e.g. they can't be ramped)
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* Stopper::ProcessMsg(MsgHalt* aMsg)
{
    if (iState == EHalting || iState == EHalted) {
        iState = EHalted;
        iObserver.PipelineHalted();
        return aMsg;
    }
    // possible we'll get here because we switched from halting to starting very quickly
    // in this case we want to consume the halt msg and not pass it on
    aMsg->RemoveRef();
    return NULL;
}

Msg* Stopper::ProcessMsg(MsgFlush* aMsg)
{
    ASSERT_DEBUG(iState == EFlushing);
    aMsg->RemoveRef();
    iState = EHalted;
    iObserver.PipelineFlushed();
    return NULL;
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
            iState = EHalted;
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
    TUint jiffies = aMsg->Jiffies();
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
    iRemainingRampSize -= jiffies;
}
