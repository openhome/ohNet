#ifndef HEADER_URI_PROVIDER_PLAYLIST
#define HEADER_URI_PROVIDER_PLAYLIST

#include <OpenHome/OhNetTypes.h>
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
    void Begin(TUint aTrackId);
    void BeginLater(TUint aTrackId);
    Media::EStreamPlay GetNext(Media::Track*& aTrack);
    TUint CurrentTrackId() const;
    TBool MoveNext();
    TBool MovePrevious();
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter);
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter);
    void NotifyAllDeleted();
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private: // from Media::ITrackObserver
    void NotifyTrackPlay(Media::Track& aTrack);
    void NotifyTrackFail(Media::Track& aTrack);
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
