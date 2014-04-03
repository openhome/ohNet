#ifndef HEADER_PIPELINE_TRACK_INSPECTOR
#define HEADER_PIPELINE_TRACK_INSPECTOR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

#include <vector>

namespace OpenHome {
namespace Media {

class ITrackObserver
{
public:
    virtual ~ITrackObserver() {}
    virtual void NotifyTrackPlay(Track& aTrack) = 0;
    virtual void NotifyTrackFail(Track& aTrack) = 0;
};

/*
Element which reports whether tracks have any associated content.
The DecodedStream msg following a MsgTrack is taken to indicate a good track.
Live streams that manage to generate a MsgEncodedStream are assumed good.
Any track that isn't covered by the cases above is assumed bad.
Is passive - it reports on Msgs but doesn't create/destroy/edit them.
*/

class TrackInspector : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    TrackInspector(IPipelineElementUpstream& aUpstreamElement);
    virtual ~TrackInspector();
    void AddObserver(ITrackObserver& aObserver);
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    void NotifyTrackPlaying();
    void NotifyTrackFailed();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<ITrackObserver*> iObservers;
    Track* iTrack;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_TRACK_INSPECTOR
