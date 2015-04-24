#include <OpenHome/Media/Pipeline/Pruner.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Pruner

Pruner::Pruner(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iPendingMode(NULL)
    , iWaitingForAudio(false)
    , iConsumeHalts(false)
{
}

Pruner::~Pruner()
{
    if (iPendingMode != NULL) {
        iPendingMode->RemoveRef();
    }
}

Msg* Pruner::Pull()
{
    Msg* msg = NULL;
    do {
        if (iWaitingForAudio || iQueue.IsEmpty()) {
            msg = iUpstreamElement.Pull();
            msg = msg->Process(*this);
        }
        else if (iPendingMode != NULL) {
            msg = iPendingMode;
            iPendingMode = NULL;
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
    if (iWaitingForAudio) {
        iQueue.Clear();
    }
    iWaitingForAudio = true;
    if (iPendingMode != NULL) {
        iPendingMode->RemoveRef();
    }
    iPendingMode = aMsg;
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgSession* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgDelay* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* Pruner::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
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
    // if we've passed on a Halt more recently than any audio, there's no need to pass on another Halt
    if (iConsumeHalts) {
        aMsg->RemoveRef();
        return NULL;
    }
    iConsumeHalts = true;
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
    if (iWaitingForAudio) {
        /* The last track contains no audio data.  Discard any queued msgs rather than risk
           them adding to an ever-growing queue in a downstream component which buffers audio (StarvationMonitor) */
        iQueue.Clear();
    }
    iWaitingForAudio = true;
    return TryQueue(aMsg);
}

Msg* Pruner::ProcessMsg(MsgAudioPcm* aMsg)
{
    iConsumeHalts = false;
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
