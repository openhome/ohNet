#include <OpenHome/Av/Playlist/UriProviderPlaylist.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderPlaylist

UriProviderPlaylist::UriProviderPlaylist(ITrackDatabaseReader& aDatabase, PipelineManager& aPipeline)
    : UriProvider("Playlist")
    , iLock("UPPL")
    , iDatabase(aDatabase)
    , iIdManager(aPipeline)
    , iPending(NULL)
    , iLastTrackId(ITrackDatabase::kTrackIdNone)
    , iPlayingTrackId(ITrackDatabase::kTrackIdNone)
{
    aPipeline.AddObserver(*this);
    iDatabase.SetObserver(*this);
}

UriProviderPlaylist::~UriProviderPlaylist()
{
    if (iPending != NULL) {
        iPending->RemoveRef();
    }
}

void UriProviderPlaylist::Begin(TUint aTrackId)
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        iPending->RemoveRef();
        iPending = NULL;
    }
    iPending = iDatabase.TrackRef(aTrackId);
    if (iPending != NULL) {
        iPendingCanPlay = ePlayYes;
    }
    else {
        iPending = iDatabase.NextTrackRef(ITrackDatabase::kTrackIdNone);
        iPendingCanPlay = ePlayLater;
    }
    iPendingDirection = eJumpTo;
}

EStreamPlay UriProviderPlaylist::GetNext(Media::Track*& aTrack)
{
    EStreamPlay canPlay = ePlayYes;
    AutoMutex a(iLock);
    if (iPending != NULL) {
        aTrack = iPending;
        iLastTrackId = iPending->Id();
        iPending = NULL;
        canPlay = iPendingCanPlay;
    }
    else {
        aTrack = iDatabase.NextTrackRef(iLastTrackId);
        if (aTrack == NULL) {
            aTrack = iDatabase.NextTrackRef(ITrackDatabase::kTrackIdNone);
            canPlay = (aTrack==NULL? ePlayNo : ePlayLater);
        }
        iLastTrackId = (aTrack != NULL? aTrack->Id() : ITrackDatabase::kTrackIdNone);
    }
    return canPlay;
}

TUint UriProviderPlaylist::CurrentTrackId() const
{
    iLock.Wait();
    const TUint id = CurrentTrackIdLocked();
    iLock.Signal();
    return id;
}

TBool UriProviderPlaylist::MoveNext()
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        iPending->RemoveRef();
        iPending = NULL;
    }
    const TUint trackId = CurrentTrackIdLocked();
    iPending = iDatabase.NextTrackRef(trackId);
    if (iPending != NULL) {
        iPendingCanPlay = ePlayYes;
    }
    else {
        iPending = iDatabase.NextTrackRef(ITrackDatabase::kTrackIdNone);
        iPendingCanPlay = (iPending == NULL? ePlayNo : ePlayLater);
    }
    iPendingDirection = eForwards;
    return true;
}

TBool UriProviderPlaylist::MovePrevious()
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        iPending->RemoveRef();
        iPending = NULL;
    }
    const TUint trackId = CurrentTrackIdLocked();
    iPending = iDatabase.PrevTrackRef(trackId);
    if (iPending != NULL) {
        iPendingCanPlay = ePlayYes;
    }
    else {
        iPending = iDatabase.PrevTrackRef(ITrackDatabase::kTrackIdNone);
        iPendingCanPlay = (iPending == NULL? ePlayNo : ePlayLater);
    }
    iPendingDirection = eBackwards;
    return true;
}

TUint UriProviderPlaylist::CurrentTrackIdLocked() const
{
    TUint id = iPlayingTrackId;
    if (iPending != NULL) {
        id = iPending->Id();
    }
    return id;
}

void UriProviderPlaylist::NotifyTrackInserted(Track& aTrack, TUint aIdBefore, TUint aIdAfter)
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        if ((iPendingDirection == eForwards && iPending->Id() == aIdAfter) ||
            (iPendingDirection == eBackwards && iPending->Id() == aIdBefore)) {
            iPending->RemoveRef();
            iPending = &aTrack;
            iPending->AddRef();
        }
    }
    iIdManager.InvalidateAfter(aIdBefore);
}

void UriProviderPlaylist::NotifyTrackDeleted(TUint aId, Track* aBefore, Track* aAfter)
{
    AutoMutex a(iLock);
    if (iPending != NULL && iPending->Id() == aId) {
        iPending->RemoveRef();
        iPending = NULL;
        if (iPendingDirection == eForwards) {
            iLastTrackId = (aBefore==NULL? ITrackDatabase::kTrackIdNone : aBefore->Id());
        }
        else { // eBackwards || eJumpTo
            iPending = (aBefore!=NULL? aAfter : aBefore);
            if (iPending == NULL) {
                iLastTrackId = ITrackDatabase::kTrackIdNone;
            }
            else {
                iPending->AddRef();
            }
        }
    }
    else if (iLastTrackId == aId) {
        iLastTrackId = (aBefore==NULL? ITrackDatabase::kTrackIdNone : aBefore->Id());
    }
    iIdManager.InvalidateAt(aId);
}

void UriProviderPlaylist::NotifyAllDeleted()
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        iPending->RemoveRef();
        iPending = NULL;
    }
    iIdManager.InvalidateAll();
}

void UriProviderPlaylist::NotifyPipelineState(EPipelineState /*aState*/)
{
}

void UriProviderPlaylist::NotifyTrack(Track& aTrack, const Brx& aMode, TUint /*aIdPipeline*/)
{
    if (aMode == Mode()) {
        iLock.Wait();
        iPlayingTrackId = aTrack.Id();
        iLock.Signal();
    }
}

void UriProviderPlaylist::NotifyMetaText(const Brx& /*aText*/)
{
}

void UriProviderPlaylist::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
}

void UriProviderPlaylist::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
}
