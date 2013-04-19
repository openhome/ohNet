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
The first chunk of decoded audio following a MsgTrack is taken to indicate a good track.
Any track that doesn't result in some decoded audio and isn't interrupted by a Flush is assumed bad.
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
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<ITrackObserver*> iObservers;
    Track* iTrack;
};

class TrackObserver : public ITrackObserver
{
public:
    TrackObserver(const Brx& aStyle, ITrackObserver& aObserver);
private: // from ITrackObserver
    void NotifyTrackPlay(Track& aTrack);
    void NotifyTrackFail(Track& aTrack);
private:
    BwsStyle iStyle;
    ITrackObserver& iObserver;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_TRACK_INSPECTOR
