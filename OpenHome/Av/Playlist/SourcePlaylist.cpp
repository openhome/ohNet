#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>
#include <OpenHome/Av/Playlist/ProviderPlaylist.h>
#include <OpenHome/Av/Playlist/UriProviderPlaylist.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/KvpStore.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Media/MimeTypeList.h>

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

class SourcePlaylist : public Source, private ISourcePlaylist, private ITrackDatabaseObserver, private Media::IPipelineObserver
{
public:
    SourcePlaylist(Environment& aEnv, Net::DvDevice& aDevice, Media::PipelineManager& aPipeline,
                   Media::TrackFactory& aTrackFactory, Media::MimeTypeList& aMimeTypeList, IPowerManager& aPowerManager);
    ~SourcePlaylist();
private:
    void EnsureActive();
    TBool StartedShuffled();
    void DoSeekToTrackId(Media::Track* aTrack);
private: // from ISource
    void Activate() override;
    void Deactivate() override;
    void StandbyEnabled() override;
    void PipelineStopped() override;
private: // from ISourcePlaylist
    void Play() override;
    void Pause() override;
    void Stop() override;
    void Next() override;
    void Prev() override;
    void SeekAbsolute(TUint aSeconds) override;
    void SeekRelative(TInt aSeconds) override;
    void SeekToTrackId(TUint aId) override;
    TBool SeekToTrackIndex(TUint aIndex) override;
    void SetShuffle(TBool aShuffle) override;
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
private:
    Mutex iLock;
    Mutex iActivationLock;
    TrackDatabase* iDatabase;
    Shuffler* iShuffler;
    Repeater* iRepeater;
    Media::UriProvider* iUriProvider;
    ProviderPlaylist* iProviderPlaylist;
    TUint iTrackPosSeconds;
    TUint iStreamId;
    Media::EPipelineState iTransportState; // FIXME - this appears to be set but never used
    TUint iTrackId;
    TBool iNoPipelineStateChangeOnActivation;
    TBool iNewPlaylist;
};
    
} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

// SourceFactory

ISource* SourceFactory::NewPlaylist(IMediaPlayer& aMediaPlayer)
{ // static
    return new SourcePlaylist(aMediaPlayer.Env(), aMediaPlayer.Device(), aMediaPlayer.Pipeline(), aMediaPlayer.TrackFactory(), aMediaPlayer.MimeTypes(), aMediaPlayer.PowerManager());
}


// SourcePlaylist

SourcePlaylist::SourcePlaylist(Environment& aEnv, Net::DvDevice& aDevice, PipelineManager& aPipeline,
                               TrackFactory& aTrackFactory, MimeTypeList& aMimeTypeList, IPowerManager& aPowerManager)
    : Source(Brn("Playlist"), "Playlist", aPipeline, aPowerManager)
    , iLock("SPL1")
    , iActivationLock("SPL2")
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iTransportState(EPipelineStopped)
    , iTrackId(ITrackDatabase::kTrackIdNone)
    , iNoPipelineStateChangeOnActivation(false)
    , iNewPlaylist(true)
{
    iDatabase = new TrackDatabase(aTrackFactory);
    iShuffler = new Shuffler(aEnv, *iDatabase);
    iRepeater = new Repeater(*iShuffler);
    iUriProvider = new UriProviderPlaylist(*iRepeater, aPipeline, *this);
    iPipeline.Add(iUriProvider); // ownership passes to iPipeline
    iProviderPlaylist = new ProviderPlaylist(aDevice, aEnv, *this, *iDatabase, *iRepeater);
    aMimeTypeList.AddUpnpProtocolInfoObserver(MakeFunctorGeneric(*iProviderPlaylist, &ProviderPlaylist::NotifyProtocolInfo));
    iPipeline.AddObserver(*this);
}

SourcePlaylist::~SourcePlaylist()
{
    delete iProviderPlaylist;
    delete iDatabase;
    delete iShuffler;
    delete iRepeater;
}

void SourcePlaylist::EnsureActive()
{
    AutoMutex a(iActivationLock);
    iNoPipelineStateChangeOnActivation = true;
    if (!IsActive()) {
        DoActivate();
    }
    iNoPipelineStateChangeOnActivation = false;
}

TBool SourcePlaylist::StartedShuffled()
{
    AutoMutex a(iLock);
    const TBool startShuffled = (iNewPlaylist && iShuffler->Enabled());
    if (startShuffled) {
        iShuffler->Reshuffle(); /* Pre-fetching will leave Shuffler with track#1 always appearing first.
                                   Force a reshuffle to allow us to start on a random track # */
        iPipeline.RemoveAll();
        iPipeline.Begin(iUriProvider->Mode(), ITrackDatabase::kTrackIdNone);
    }
    iNewPlaylist = false;
    return startShuffled;
}

void SourcePlaylist::DoSeekToTrackId(Track* aTrack)
{
    ASSERT(aTrack != nullptr);
    AutoAllocatedRef r(aTrack);
    iLock.Wait();
    if (iShuffler->TryMoveToStart(aTrack->Id())) {
        iNewPlaylist = false;
    }
    iLock.Signal();

    iPipeline.RemoveAll();
    iPipeline.Begin(iUriProvider->Mode(), aTrack->Id());
    DoPlay();
    iLock.Wait();
    iTransportState = EPipelinePlaying;
    iLock.Signal();
}

void SourcePlaylist::Activate()
{
    iTrackPosSeconds = 0;
    iActive = true;
    if (!iNoPipelineStateChangeOnActivation) {
        TUint trackId = ITrackDatabase::kTrackIdNone;
        if (static_cast<ITrackDatabase*>(iDatabase)->TrackCount() > 0) {
            trackId = iUriProvider->CurrentTrackId();
            if (trackId == ITrackDatabase::kTrackIdNone) {
                Track* track = static_cast<ITrackDatabaseReader*>(iDatabase)->NextTrackRef(ITrackDatabase::kTrackIdNone);
                if (track != nullptr) {
                    trackId = track->Id();
                    track->RemoveRef();
                }
            }
        }
        iPipeline.StopPrefetch(iUriProvider->Mode(), trackId);
    }
}

void SourcePlaylist::Deactivate()
{
    iLock.Wait();
    iTransportState = EPipelineStopped;
    iProviderPlaylist->NotifyPipelineState(EPipelineStopped);
    iLock.Signal();
    Source::Deactivate();
}

void SourcePlaylist::StandbyEnabled()
{
    Stop();
}

void SourcePlaylist::PipelineStopped()
{
    // FIXME - could nullptr iPipeline (if we also changed it to be a pointer)
}

void SourcePlaylist::Play()
{
    if (!IsActive()) {
        DoActivate();
    }
    if (static_cast<ITrackDatabase*>(iDatabase)->TrackCount() == 0) {
        iPipeline.Stop();
        return;
    }

    if (!StartedShuffled()) {
        if (iTransportState == EPipelinePlaying) {
            iPipeline.RemoveAll();
            iPipeline.Begin(iUriProvider->Mode(), iUriProvider->CurrentTrackId());
        }
    }
    iLock.Wait();
    iTransportState = EPipelinePlaying;
    iLock.Signal();
    DoPlay();
}

void SourcePlaylist::Pause()
{
    if (!IsActive()) {
        DoActivate();
    }
    if (static_cast<ITrackDatabase*>(iDatabase)->TrackCount() == 0) {
        iPipeline.Stop();
        return;
    }

    iLock.Wait();
    iTransportState = EPipelinePaused;
    iLock.Signal();
    iPipeline.Pause();
}

void SourcePlaylist::Stop()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = EPipelineStopped;
        const TUint trackId = iTrackId;
        iLock.Signal();
        iPipeline.StopPrefetch(iUriProvider->Mode(), trackId);
    }
}

void SourcePlaylist::Next()
{
    if (IsActive()) {
        if (!StartedShuffled()) {
            iPipeline.Next();
        }
        DoPlay();
    }
}

void SourcePlaylist::Prev()
{
    if (IsActive()) {
        if (!StartedShuffled()) {
            iPipeline.Prev();
        }
        DoPlay();
    }
}

void SourcePlaylist::SeekAbsolute(TUint aSeconds)
{
    if (IsActive()) {
        iPipeline.Seek(iStreamId, aSeconds);
        DoPlay();
    }
}

void SourcePlaylist::SeekRelative(TInt aSeconds)
{
    if (aSeconds == 0) {
        // assume this means no change rather than seek backwards to the most recent second boundary
        DoPlay();
        return;
    }
    iLock.Wait();
    TUint pos = aSeconds + iTrackPosSeconds;
    if (aSeconds < 0 && -aSeconds > (TInt)iTrackPosSeconds) {
        pos = 0;
    }
    iLock.Signal();
    SeekAbsolute(pos);
}

void SourcePlaylist::SeekToTrackId(TUint aId)
{
    EnsureActive();

    Track* track = nullptr;
    static_cast<ITrackDatabase*>(iDatabase)->GetTrackById(aId, track);
    DoSeekToTrackId(track);
}

TBool SourcePlaylist::SeekToTrackIndex(TUint aIndex)
{
    EnsureActive();

    Track* track = static_cast<ITrackDatabaseReader*>(iRepeater)->TrackRefByIndex(aIndex);
    if (track != nullptr) {
        DoSeekToTrackId(track);
    }
    return (track!=nullptr);
}

void SourcePlaylist::SetShuffle(TBool aShuffle)
{
    AutoMutex a(iLock);
    iShuffler->SetShuffle(aShuffle);
    if (aShuffle && iTransportState == EPipelineStopped) {
        iNewPlaylist = true;
    }
}

void SourcePlaylist::NotifyTrackInserted(Track& aTrack, TUint aIdBefore, TUint aIdAfter)
{
    if (aIdBefore == ITrackDatabase::kTrackIdNone && aIdAfter == ITrackDatabase::kTrackIdNone) {
        if (IsActive()) {
            iPipeline.StopPrefetch(iUriProvider->Mode(), aTrack.Id());
        }
        else {
            iProviderPlaylist->NotifyTrack(aTrack.Id()); /* Playlist's Id property is expected to show the track
                                                            that'll be fetched when the source is next activated - see #1807 */
        }
    }
}

void SourcePlaylist::NotifyTrackDeleted(TUint aId, Track* /*aBefore*/, Track* aAfter)
{
    if (IsActive() && iTransportState != EPipelinePlaying) {
        if (iUriProvider->CurrentTrackId() == aId) {
            const TUint id = (aAfter==nullptr? ITrackDatabase::kTrackIdNone : aAfter->Id());
            iPipeline.StopPrefetch(iUriProvider->Mode(), id);
        }
    }
    iLock.Wait();
    if (static_cast<ITrackDatabase*>(iDatabase)->TrackCount() == 0) {
        iNewPlaylist = true;
        iTrackId = ITrackDatabase::kTrackIdNone;
    }
    iLock.Signal();
}

void SourcePlaylist::NotifyAllDeleted()
{
    iLock.Wait();
    iNewPlaylist = true;
    iTrackId = ITrackDatabase::kTrackIdNone;
    iLock.Signal();
    if (IsActive()) {
        iPipeline.StopPrefetch(iUriProvider->Mode(), ITrackDatabase::kTrackIdNone);
    }
}

void SourcePlaylist::NotifyPipelineState(EPipelineState aState)
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = aState;
        iLock.Signal();
        iProviderPlaylist->NotifyPipelineState(aState);
    }
}

void SourcePlaylist::NotifyMode(const Brx& /*aMode*/, const ModeInfo& /*aInfo*/)
{
}

void SourcePlaylist::NotifyTrack(Track& aTrack, const Brx& aMode, TBool /*aStartOfStream*/)
{
    if (aMode == iUriProvider->Mode()) {
        iProviderPlaylist->NotifyTrack(aTrack.Id());
        iLock.Wait();
        iTrackId = aTrack.Id();
        iTrackPosSeconds = 0;
        iLock.Signal();
    }
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

void SourcePlaylist::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId = aStreamInfo.StreamId();
    iLock.Signal();
}
