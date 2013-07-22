#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Playlist/ProviderPlaylist.h>
#include <OpenHome/Av/Playlist/UriProviderPlaylist.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>

#include <limits.h>

namespace OpenHome {
    class Environment;
namespace Net {
    class DvDevice;
}
namespace Media {
    class PipelineManager;
    class TrackFactory;
}
namespace Av {

class UriProviderPlaylist;
class ProviderPlaylist;

class SourcePlaylist : public Source, private ISourcePlaylist, private Media::IPipelineObserver
{
public:
    SourcePlaylist(Environment& aEnv, Net::DvDevice& aDevice, Media::PipelineManager& aPipeline, Media::TrackFactory& aTrackFactory, const Brx& aProtocolInfo);
    ~SourcePlaylist();
private: // from ISource
    void Activate();
    void Deactivate();
private: // from ISourcePlaylist
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Prev();
    void SeekAbsolute(TUint aSeconds);
    void SeekRelative(TUint aSeconds);
    void SeekToTrackId(TUint aId);
    void SeekToTrackIndex(TUint aIndex);
private: // from Media::IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    PlaylistDatabase* iDatabase;
    UriProviderPlaylist* iUriProvider;
    ProviderPlaylist* iProviderPlaylist;
    TUint iTrackPosSeconds;
    TUint iPipelineTrackId;
    TUint iStreamId;
    Media::EPipelineState iTransportState;
};
    
} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

// SourceFactory

ISource* SourceFactory::NewPlaylist(IMediaPlayer& aMediaPlayer, const Brx& aSupportedProtocols)
{ // static
    return new SourcePlaylist(aMediaPlayer.Env(), aMediaPlayer.Device(), aMediaPlayer.Pipeline(), aMediaPlayer.TrackFactory(), aSupportedProtocols);
}


// SourcePlaylist

SourcePlaylist::SourcePlaylist(Environment& aEnv, Net::DvDevice& aDevice, Media::PipelineManager& aPipeline, Media::TrackFactory& aTrackFactory, const Brx& aProtocolInfo)
    : Source("Playlist", "Playlist")
    , iLock("SPLY")
    , iPipeline(aPipeline)
    , iTrackPosSeconds(0)
    , iPipelineTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    iDatabase = new PlaylistDatabase(aTrackFactory, aPipeline);
    iUriProvider = new UriProviderPlaylist(*iDatabase);
    iPipeline.Add(iUriProvider); // ownership passes to iPipeline
    iProviderPlaylist = new ProviderPlaylist(aDevice, aEnv, *this, *iDatabase, aProtocolInfo);
    iPipeline.AddObserver(*this);
}

SourcePlaylist::~SourcePlaylist()
{
    delete iProviderPlaylist;
}

void SourcePlaylist::Activate()
{
    iTrackPosSeconds = 0;
    iActive = true;
}

void SourcePlaylist::Deactivate()
{
    iLock.Wait();
    iTransportState = Media::EPipelineStopped;
    iLock.Signal();
    Source::Deactivate();
}

void SourcePlaylist::Play()
{
    if (!IsActive()) {
        DoActivate();
        TUint trackId = iDatabase->NextTrackId();
        if (trackId == IPlaylistDatabase::kTrackIdNone) {
            return; // nothing to play
        }
        iPipeline.Begin(iUriProvider->Mode(), trackId);
    }
    iLock.Wait();
    iTransportState = Media::EPipelinePlaying;
    iLock.Signal();
    iPipeline.Play();
}

void SourcePlaylist::Pause()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelinePaused;
        iLock.Signal();
        iPipeline.Pause();
    }
}

void SourcePlaylist::Stop()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelineStopped;
        iLock.Signal();
        iPipeline.Stop();
    }
}

void SourcePlaylist::Next()
{
    if (IsActive()) {
        iPipeline.Next();
    }
}

void SourcePlaylist::Prev()
{
    if (IsActive()) {
        iPipeline.Prev();
    }
}

void SourcePlaylist::SeekAbsolute(TUint aSeconds)
{
    if (IsActive()) {
        (void)iPipeline.Seek(iPipelineTrackId, iStreamId, aSeconds);
    }
}

void SourcePlaylist::SeekRelative(TUint aSeconds)
{
    SeekAbsolute(aSeconds + iTrackPosSeconds);
}

void SourcePlaylist::SeekToTrackId(TUint /*aId*/)
{
    // FIXME
}

void SourcePlaylist::SeekToTrackIndex(TUint /*aIndex*/)
{
    // FIXME
}

void SourcePlaylist::NotifyPipelineState(Media::EPipelineState aState)
{
    if (IsActive()) {
        iProviderPlaylist->NotifyPipelineState(aState);
    }
}

void SourcePlaylist::NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline)
{
    if (aMode == iUriProvider->Mode()) {
        iProviderPlaylist->NotifyTrack(aTrack.Id());
    }
    iLock.Wait();
    iPipelineTrackId = aIdPipeline;
    iLock.Signal();
}

void SourcePlaylist::NotifyMetaText(const Brx& /*aText*/)
{
}

void SourcePlaylist::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iLock.Wait();
    iTrackPosSeconds = aSeconds;
    iLock.Signal();
}

void SourcePlaylist::NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId = aStreamInfo.StreamId();
    iLock.Signal();
}
