#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>

#include <array>
#include <vector>

namespace OpenHome {
namespace Media {
    class Track;
    class PipelineManager;
}
namespace Av {

class UriProviderPlaylist : public Media::UriProvider, private ITrackDatabaseObserver, private Media::IPipelineObserver, private Media::ITrackObserver
{
    static const Brn kCommandId;
    static const Brn kCommandIndex;
public:
    UriProviderPlaylist(ITrackDatabaseReader& aDatabase, Media::PipelineManager& aPipeline, ITrackDatabaseObserver& aObserver);
    ~UriProviderPlaylist();
    void SetActive(TBool aActive);
public: // from UriProvider
    TBool IsValid(TUint aTrackId) const override;
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    Media::EStreamPlay GetNext(Media::Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    TBool MoveNext() override;
    TBool MovePrevious() override;
    TBool MoveTo(const Brx& aCommand) override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private: // from Media::ITrackObserver
    void NotifyTrackPlay(Media::Track& aTrack) override;
    void NotifyTrackFail(Media::Track& aTrack) override;
private:
    void DoBegin(TUint aTrackId, Media::EStreamPlay aPendingCanPlay);
    TUint CurrentTrackIdLocked() const;
    TUint ParseCommand(const Brx& aCommand) const;
    Media::Track* ProcessCommandId(const Brx& aCommand);
    Media::Track* ProcessCommandIndex(const Brx& aCommand);
private:
    enum EPendingDirection
    {
        eForwards
       ,eBackwards
       ,eJumpTo
    };
private:
    mutable Mutex iLock;
    ITrackDatabaseReader& iDatabase;
    Media::IPipelineIdManager& iIdManager;
    ITrackDatabaseObserver& iObserver;
    Media::Track* iPending;
    Media::EStreamPlay iPendingCanPlay;
    EPendingDirection iPendingDirection;
    TUint iLastTrackId;
    TUint iPlayingTrackId;
    TUint iFirstFailedTrackId; // first id from a string of failures; reset by any track generating audio
    TBool iActive;
};

} // namespace Av
} // namespace OpenHome

