#pragma once

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

class TrackInspector : public PipelineElement, public IPipelineElementUpstream, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
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
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    std::vector<ITrackObserver*> iObservers;
    Track* iTrack;
};

} // namespace Media
} // namespace OpenHome

