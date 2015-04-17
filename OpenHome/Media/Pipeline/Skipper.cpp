#include <OpenHome/Media/Pipeline/Skipper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Skipper::Skipper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iLock("SKP1")
    , iBlocker("SKP2")
    , iState(eStarting)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMax)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iStreamHandler(NULL)
    , iPassGeneratedHalt(false)
{
}

Skipper::~Skipper()
{
}

inline TBool Skipper::FlushUntilHalt() const
{
    return (iTargetHaltId != MsgHalt::kIdInvalid);
}

void Skipper::Block()
{
    iBlocker.Wait();
}

void Skipper::Unblock()
{
    iBlocker.Signal();
}

void Skipper::RemoveCurrentStream(TBool aRampDown)
{
    iLock.Wait();
    (void)TryRemoveCurrentStream(aRampDown);
    iLock.Signal();
}

TBool Skipper::TryRemoveStream(TUint aStreamId, TBool aRampDown)
{
    AutoMutex a(iLock);
    if (iStreamId == aStreamId) {
        return TryRemoveCurrentStream(aRampDown);
    }
    return false;
}

void Skipper::RemoveAll(TUint aHaltId, TBool aRampDown)
{
    AutoMutex a(iLock);
    iTargetHaltId = aHaltId;
    iPassGeneratedHalt = false;
    (void)TryRemoveCurrentStream(aRampDown);
}

Msg* Skipper::Pull()
{
    Msg* msg;
    do {
        msg = (iQueue.IsEmpty()? iUpstreamElement.Pull() : iQueue.Dequeue());
        iBlocker.Wait();
        iBlocker.Signal();
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

Msg* Skipper::ProcessMsg(MsgMode* aMsg)
{
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgSession* aMsg)
{
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgTrack* aMsg)
{
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgDelay* aMsg)
{
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    if (FlushUntilHalt()) {
        const TBool sendHalt = (iState != eFlushing); // only create a MsgHalt the first time we call StartFlushing()
        StartFlushing(sendHalt);
        // a bit dodgy not calling aMsg->StreamHandler()->OkToPlay()
        // ...but safe if we assume that RemoveAll() is only called when IdManager contents have also been invalidated
        aMsg->RemoveRef();
        return NULL;
    }

    NewStream();
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Skipper::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgHalt* aMsg)
{
    if (FlushUntilHalt() && aMsg->Id() == iTargetHaltId) {
        iTargetHaltId = MsgHalt::kIdInvalid;
        iState = eRunning;
        // don't consume this - downstream elements may also be waiting on it
        return aMsg;
    }
    if (iPassGeneratedHalt) {
        iPassGeneratedHalt = false;
        return aMsg;
    }
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == eFlushing);
        aMsg->RemoveRef();
        iTargetFlushId = MsgFlush::kIdInvalid;
        return NULL;
    }
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgWait* aMsg)
{
    return ProcessFlushableRemoveAll(aMsg);
}

Msg* Skipper::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (FlushUntilHalt()) {
        return ProcessFlushableRemoveAll(aMsg);
    }
    iState = (iTargetFlushId == MsgFlush::kIdInvalid? eStarting : eFlushing);
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iState == eStarting) {
        iState = eRunning;
    }
    else if (iState == eRamping) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != NULL) {
                split->RemoveRef(); // we're going to flush the rest of the stream so no need to add split to iQueue
            }
        }
        split = NULL;
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EDown, split);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            StartFlushing(true);
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgSilence* aMsg)
{
    if (iState == eStarting && !FlushUntilHalt()) {
        iState = eRunning;
    }
    else if (iState == eRamping) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
        StartFlushing(true);
    }
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Skipper::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

TBool Skipper::TryRemoveCurrentStream(TBool aRampDown)
{
    LOG(kMedia, "Skipper::TryRemoveCurrentStream(%u), iState=%u\n", aRampDown, iState);
    EState state = iState;
    if (!aRampDown || iState == eStarting) {
        StartFlushing(false); // if we don't need to ramp down we should already be halted (so don't need to generate another MsgHalt)
    }
    else if (iState == eRunning) {
        iState = eRamping;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMax;
    }
    return (state != iState);
}

void Skipper::StartFlushing(TBool aSendHalt)
{
    if (aSendHalt) {
        iQueue.Enqueue(iMsgFactory.CreateMsgHalt()); /* inform downstream parties (StarvationMonitor)
                                                        that any subsequent break in audio is expected */
        iPassGeneratedHalt = true;
    }
    iState = eFlushing;
    iTargetFlushId = (iStreamHandler==NULL? MsgFlush::kIdInvalid : iStreamHandler->TryStop(iStreamId));
}

Msg* Skipper::ProcessFlushable(Msg* aMsg)
{
    if (iState == eFlushing) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* Skipper::ProcessFlushableRemoveAll(Msg* aMsg)
{
    if (FlushUntilHalt()) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

void Skipper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    iState = (iTargetFlushId == MsgFlush::kIdInvalid? eStarting : eFlushing);
}
