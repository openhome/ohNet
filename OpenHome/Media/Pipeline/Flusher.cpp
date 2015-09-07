#include <OpenHome/Media/Pipeline/Flusher.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Flusher::Flusher(IPipelineElementUpstream& aUpstream, const TChar* aId)
    : iLock("FLSH")
    , iUpstream(aUpstream)
    , iId(aId)
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
    LOG(kPipeline, "Flusher(%s) DiscardUntilHalt(%u)\n", iId, aId);
}

void Flusher::DiscardUntilFlush(TUint aId)
{
    ASSERT(aId != MsgFlush::kIdInvalid);
    AutoMutex _(iLock);
    iTargetFlushId = aId;
    LOG(kPipeline, "Flusher(%s) DiscardUntilFlush(%u)\n", iId, aId);
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
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgTrack* aMsg)
{
    /*if (IsFlushing()) {
        Log::Print("Flusher(%s) flushing Track %u\n", iId, aMsg->Track().Id());
    }*/
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
        LOG(kPipeline, "Flusher(%s), completed (pulled Halt id %u)\n", iId, aMsg->Id());
    }
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        iTargetFlushId = MsgFlush::kIdInvalid;
        LOG(kPipeline, "Flusher(%s), completed (pulled Flush id %u)\n", iId, aMsg->Id());
    }
    return aMsg;
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
        //Log::Print("Flusher(%s) flushing DecodedStream %u\n", iId, streamId);
        (void)streamHandler->TryStop(streamId);
        (void)streamHandler->OkToPlay(streamId);
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* Flusher::ProcessMsg(MsgBitRate* aMsg)
{
    return ProcessFlushable(aMsg);
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
