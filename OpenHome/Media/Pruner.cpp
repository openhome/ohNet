#include <OpenHome/Media/Pruner.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Pruner

Pruner::Pruner(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iWaitingForAudio(false)
{
}

Pruner::~Pruner()
{
}

Msg* Pruner::Pull()
{
    Msg* msg = NULL;
    do {
        if (iWaitingForAudio || iQueue.IsEmpty()) {
            msg = iUpstreamElement.Pull();
            msg = msg->Process(*this);
        }
        else {
            msg = iQueue.Dequeue();
        }
    } while (msg == NULL);
    return msg;
}

Msg* Pruner::TryQueue(Msg* aMsg)
{
    if (iWaitingForAudio) {
        iQueue.Enqueue(aMsg);
        return NULL;
    }
    return aMsg;
}

Msg* Pruner::TryQueueCancelWaiting(Msg* aMsg)
{
    Msg* msg = TryQueue(aMsg);
    iWaitingForAudio = false;
    return msg;
}

Msg* Pruner::ProcessMsg(MsgMode* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgTrack* aMsg)
{
    if (iWaitingForAudio) {
        /* The last track contains no audio data.  Discard any queued msgs rather than risk
           them adding to an ever-growing queue in a downstream component which buffers audio (StarvationMonitor) */
        while (!iQueue.IsEmpty()) {
            iQueue.Dequeue()->RemoveRef();
        }
    }
    iWaitingForAudio = true;
    return TryQueue(aMsg);
}

Msg* Pruner::ProcessMsg(MsgDelay* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgEncodedStream* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgMetaText* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgHalt* aMsg)
{
    return TryQueue(aMsg);
}

Msg* Pruner::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgWait* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgDecodedStream* aMsg)
{
    return TryQueue(aMsg);
}

Msg* Pruner::ProcessMsg(MsgAudioPcm* aMsg)
{
    return TryQueueCancelWaiting(aMsg);
}

Msg* Pruner::ProcessMsg(MsgSilence* aMsg)
{
    return TryQueueCancelWaiting(aMsg);
}

Msg* Pruner::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgQuit* aMsg)
{
    return TryQueueCancelWaiting(aMsg);
}
