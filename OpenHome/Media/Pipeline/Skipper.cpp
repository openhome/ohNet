#include <OpenHome/Media/Pipeline/Skipper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Flusher.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Skipper::Skipper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration)
    : iFlusher(aUpstreamElement, "Skipper")
    , iMsgFactory(aMsgFactory)
    , iLock("SKP1")
    , iBlocker("SKP2")
    , iState(eStarting)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMax)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iStreamHandler(nullptr)
    , iPassGeneratedHalt(false)
    , iRunning(false)
{
}

Skipper::~Skipper()
{
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
    AutoMutex _(iLock);
    (void)TryRemoveCurrentStream(aRampDown);
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
    LOG(kPipeline, "Skipper::RemoveAll() - flush until haltId %u\n", aHaltId);
    iTargetHaltId = aHaltId;
    iPassGeneratedHalt = false;
    (void)TryRemoveCurrentStream(aRampDown);
}

TBool Skipper::RemoveAllPending() const
{ // inline
    return (iState == eRamping && iTargetHaltId != MsgHalt::kIdInvalid);
}

Msg* Skipper::Pull()
{
    Msg* msg;
    do {
        msg = (iQueue.IsEmpty()? iFlusher.Pull() : iQueue.Dequeue());
        iBlocker.Wait();
        iBlocker.Signal();
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == nullptr);
    return msg;
}

Msg* Skipper::ProcessMsg(MsgMode* aMsg)
{
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgTrack* aMsg)
{
    if (RemoveAllPending()) {
        StartFlushing(true);
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (RemoveAllPending()) {
        StartFlushing(true);
        aMsg->RemoveRef();
        return nullptr;
    }
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    auto msg = iMsgFactory.CreateMsgEncodedStream(aMsg->Uri(), aMsg->MetaText(), aMsg->TotalBytes(), aMsg->StreamId(), aMsg->Seekable(), aMsg->Live(), this);
    aMsg->RemoveRef();
    NewStream();
    return msg;
}

Msg* Skipper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Skipper::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iRunning = false;
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgHalt* aMsg)
{
    iRunning = false;
    if (iState == eRamping) {
        /* A Halt signals a potential discontinuity in audio.
          Appropriate ramps must already have been applied by the creator of this msg
          ...so we can terminate our ramp */
        StartFlushing(true);
    }
    if (iTargetHaltId != MsgHalt::kIdInvalid && aMsg->Id() == iTargetHaltId) {
        LOG(kPipeline, "Skipper - completed flush (pulled haltId %u)\n", iTargetHaltId);
        iTargetHaltId = MsgHalt::kIdInvalid;
        iState = eRunning;
        // don't consume this - downstream elements may also be waiting on it
        return aMsg;
    }
    if (iPassGeneratedHalt) {
        iPassGeneratedHalt = false;
        return aMsg;
    }
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == eFlushing);
        iState = eStarting;
        aMsg->RemoveRef();
        iTargetFlushId = MsgFlush::kIdInvalid;
        return nullptr;
    }
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgWait* aMsg)
{
    iRunning = false;
    if (iState == eRamping) {
        /* A Wait signals a potential discontinuity in audio.
           Appropriate ramps must already have been applied by the creator of this msg
           ...so we can terminate our ramp */
        StartFlushing(true);
    }
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iState = (iTargetFlushId == MsgFlush::kIdInvalid? eStarting : eFlushing);
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* Skipper::ProcessMsg(MsgBitRate* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iRunning = true;
    if (iState == eStarting) {
        iState = eRunning;
    }
    else if (iState == eRamping) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != nullptr) {
                split->RemoveRef(); // we're going to flush the rest of the stream so no need to add split to iQueue
            }
        }
        split = nullptr;
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EDown, split);
        if (split != nullptr) {
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
    if (iState == eStarting) {
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
    return nullptr;
}

Msg* Skipper::ProcessMsg(MsgQuit* aMsg)
{
    iRunning = false;
    return aMsg;
}

EStreamPlay Skipper::OkToPlay(TUint aStreamId)
{
    return iStreamHandler->OkToPlay(aStreamId);
}

TUint Skipper::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Skipper::TryStop(TUint aStreamId)
{
    return iStreamHandler->TryStop(aStreamId);
}

void Skipper::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    {
        AutoMutex _(iLock);
        if (aStarving) {
            iRunning = false;
            if (iState == eRamping) {
                // FIXME - consider queueing StreamInterrupted.  But how to do this in a thread safe way?
                StartFlushing(true);
            }
        }
    }
    iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
}

TBool Skipper::TryRemoveCurrentStream(TBool aRampDown)
{
    if (!iRunning) {
        aRampDown = false;
    }
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
    iTargetFlushId = (iStreamHandler==nullptr? MsgFlush::kIdInvalid : iStreamHandler->TryStop(iStreamId));
    if (iTargetHaltId != MsgHalt::kIdNone && iTargetHaltId != MsgHalt::kIdInvalid) {
        iFlusher.DiscardUntilHalt(iTargetHaltId);
    }
    else if (iTargetFlushId != MsgFlush::kIdInvalid) {
        iFlusher.DiscardUntilFlush(iTargetFlushId);
    }
}

Msg* Skipper::ProcessFlushable(Msg* aMsg)
{
    if (iState == eFlushing) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

void Skipper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    iState = (iTargetFlushId == MsgFlush::kIdInvalid? eStarting : eFlushing);
}
