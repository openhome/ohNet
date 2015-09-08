#include <OpenHome/Media/Pipeline/TrackInspector.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// TrackInspector

const TUint TrackInspector::kSupportedMsgTypes =   eMode
                                                 | eTrack
                                                 | eDrain
                                                 | eDelay
                                                 | eEncodedStream
                                                 | eMetatext
                                                 | eStreamInterrupted
                                                 | eHalt
                                                 | eFlush
                                                 | eWait
                                                 | eDecodedStream
                                                 | eBitRate
                                                 | eAudioPcm
                                                 | eSilence
                                                 | eQuit;

TrackInspector::TrackInspector(IPipelineElementUpstream& aUpstreamElement)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iTrack(nullptr)
{
}

TrackInspector::~TrackInspector()
{
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
}

void TrackInspector::AddObserver(ITrackObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

Msg* TrackInspector::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

void TrackInspector::NotifyTrackPlaying()
{
    ASSERT(iTrack!=nullptr);
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackPlay(*iTrack);
    }
    iTrack->RemoveRef();
    iTrack = nullptr;
}

void TrackInspector::NotifyTrackFailed()
{
    ASSERT(iTrack!=nullptr);
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackFail(*iTrack);
    }
    iTrack->RemoveRef();
    iTrack = nullptr;
}

Msg* TrackInspector::ProcessMsg(MsgTrack* aMsg)
{
    if (iTrack != nullptr) {
        NotifyTrackFailed();
    }
    iTrack = &aMsg->Track();
    iTrack->AddRef();
    return aMsg;
}

Msg* TrackInspector::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (iTrack != nullptr && aMsg->Live()) {
        /* Live streams wait for the stopper to tell them to start generating audio.
           Its possible we'll see this msg but no audio for a perfectly good stream
           ...so assume that generation of MsgEncodedStream implies the track is good
           ...(more accurately, not utterly bad) */
        NotifyTrackPlaying();
    }
    return aMsg;
}

Msg* TrackInspector::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (iTrack != nullptr) {
        NotifyTrackPlaying();
    }
    return aMsg;
}
