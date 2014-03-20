#include <OpenHome/Media/TrackInspector.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// TrackInspector

TrackInspector::TrackInspector(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iTrack(NULL)
    , iWaitingForAudio(false)
{
}

TrackInspector::~TrackInspector()
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
}

void TrackInspector::AddObserver(ITrackObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

Msg* TrackInspector::Pull()
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

void TrackInspector::NotifyTrackPlaying()
{
    ASSERT(iTrack!=NULL);
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackPlay(*iTrack);
    }
    iTrack->RemoveRef();
    iTrack = NULL;
}

void TrackInspector::NotifyTrackFailed()
{
    ASSERT(iTrack!=NULL);
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackFail(*iTrack);
    }
    iTrack->RemoveRef();
    iTrack = NULL;
}

Msg* TrackInspector::TryQueue(Msg* aMsg)
{
    if (iWaitingForAudio) {
        iQueue.Enqueue(aMsg);
        return NULL;
    }
    return aMsg;
}

Msg* TrackInspector::ProcessMsg(MsgTrack* aMsg)
{
    if (iWaitingForAudio) {
        /* The last track contains no audio data.  Discard any queued msgs rather than risk
           them adding to an ever-growing queue in a downstream component which buffers audio (StarvationMonitor) */
        while (!iQueue.IsEmpty()) {
            iQueue.Dequeue()->RemoveRef();
        }
    }
    iWaitingForAudio = true;
    if (iTrack != NULL) {
        NotifyTrackFailed();
    }
    iTrack = &aMsg->Track();
    iTrack->AddRef();
    return TryQueue(aMsg); // will always queue aMsg.  Saves us duplicating the (short) body of TryQueue if we call it.
}

Msg* TrackInspector::ProcessMsg(MsgEncodedStream* aMsg)
{
    return TryQueue(aMsg);
}

Msg* TrackInspector::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* TrackInspector::ProcessMsg(MsgMetaText* aMsg)
{
    return TryQueue(aMsg);
}

Msg* TrackInspector::ProcessMsg(MsgHalt* aMsg)
{
    return TryQueue(aMsg);
}

Msg* TrackInspector::ProcessMsg(MsgFlush* aMsg)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
        iTrack = NULL;
    }
    return TryQueue(aMsg);
}

Msg* TrackInspector::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (iTrack != NULL && aMsg->StreamInfo().Live()) {
        /* Live streams wait for the stopper to tell them to start generating audio.
           Its possible we'll see this msg but no audio for a perfectly good stream
           ...so assume that generation of MsgDecodedStream implies the track is good
           ...(more accurately, not utterly bad) */
        NotifyTrackPlaying();
    }
    return TryQueue(aMsg);
}

Msg* TrackInspector::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iTrack != NULL) {
        NotifyTrackPlaying();
    }
    Msg* msg = TryQueue(aMsg);
    iWaitingForAudio = false;
    return msg;
}

Msg* TrackInspector::ProcessMsg(MsgSilence* aMsg)
{
    Msg* msg = TryQueue(aMsg);
    iWaitingForAudio = false;
    return msg;
}

Msg* TrackInspector::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* TrackInspector::ProcessMsg(MsgQuit* aMsg)
{
    Msg* msg = TryQueue(aMsg);
    iWaitingForAudio = false;
    return msg;
}
