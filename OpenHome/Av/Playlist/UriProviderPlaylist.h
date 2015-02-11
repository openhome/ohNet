#ifndef HEADER_URI_PROVIDER_PLAYLIST
#define HEADER_URI_PROVIDER_PLAYLIST

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
public:
    UriProviderPlaylist(ITrackDatabaseReader& aDatabase, Media::PipelineManager& aPipeline, ITrackDatabaseObserver& aObserver);
    ~UriProviderPlaylist();
private: // from UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    Media::EStreamPlay GetNext(Media::Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    TBool MoveNext() override;
    TBool MovePrevious() override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
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
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_URI_PROVIDER_PLAYLIST
