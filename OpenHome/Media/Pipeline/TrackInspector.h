#ifndef HEADER_PIPELINE_TRACK_INSPECTOR
#define HEADER_PIPELINE_TRACK_INSPECTOR

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    Msg* Pull() override;
private:
    void NotifyTrackPlaying();
    void NotifyTrackFailed();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<ITrackObserver*> iObservers;
    Track* iTrack;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_TRACK_INSPECTOR
