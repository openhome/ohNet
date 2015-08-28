#include <OpenHome/Media/Pipeline/Flusher.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Flusher::Flusher(IPipelineElementUpstream& aUpstream)
    : iLock("FLSH")
    , iUpstream(aUpstream)
    , iTargetHaltId(MsgHalt::kIdInvalid)
    , iTargetFlushId(MsgFlush::kIdInvalid)
{
}

void Flusher::DiscardUntilHalt(TUint aId)
{
    ASSERT(aId != MsgHalt::kIdNone);
    ASSERT(aId != MsgHalt::kIdInvalid);
    AutoMutex _(iLock);
    iTargetHaltId = aId;
}

void Flusher::DiscardUntilFlush(TUint aId)
{
    ASSERT(aId != MsgFlush::kIdInvalid);
    AutoMutex _(iLock);
    iTargetFlushId = aId;
}

Msg* Flusher::Pull()
{
    Msg* msg;
    do {
        msg = iUpstream.Pull();
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

inline TBool Flusher::IsFlushing() const
{
    return (iTargetHaltId != MsgHalt::kIdInvalid || iTargetFlushId != MsgFlush::kIdInvalid);
}

Msg* Flusher::ProcessFlushable(Msg* aMsg)
{
    if (IsFlushing()) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgMode* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgTrack* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgEncodedStream* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Flusher::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgHalt* aMsg)
{
    if (iTargetHaltId != MsgHalt::kIdInvalid && iTargetHaltId == aMsg->Id()) {
        iTargetHaltId = MsgHalt::kIdInvalid;
        return aMsg;
    }
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        iTargetFlushId = MsgFlush::kIdInvalid;
        return aMsg;
    }
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgWait* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (IsFlushing()) {
        auto streamInfo = aMsg->StreamInfo();
        IStreamHandler* streamHandler = streamInfo.StreamHandler();
        auto streamId = streamInfo.StreamId();
        (void)streamHandler->TryStop(streamId);
        (void)streamHandler->OkToPlay(streamId);
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Flusher::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Flusher::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
