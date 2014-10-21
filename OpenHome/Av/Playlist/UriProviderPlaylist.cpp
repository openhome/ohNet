#include <OpenHome/Av/Playlist/UriProviderPlaylist.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// UriProviderPlaylist

UriProviderPlaylist::UriProviderPlaylist(ITrackDatabaseReader& aDatabase, PipelineManager& aPipeline, ITrackDatabaseObserver& aObserver)
    : UriProvider("Playlist", false, false)
    , iLock("UPPL")
    , iDatabase(aDatabase)
    , iIdManager(aPipeline)
    , iObserver(aObserver)
    , iPending(NULL)
    , iLastTrackId(ITrackDatabase::kTrackIdNone)
    , iPlayingTrackId(ITrackDatabase::kTrackIdNone)
    , iFirstFailedTrackId(ITrackDatabase::kTrackIdNone)
{
    aPipeline.AddObserver(static_cast<IPipelineObserver&>(*this));
    iDatabase.SetObserver(*this);
    aPipeline.AddObserver(static_cast<ITrackObserver&>(*this));
}

UriProviderPlaylist::~UriProviderPlaylist()
{
    if (iPending != NULL) {
        iPending->RemoveRef();
    }
}

void UriProviderPlaylist::Begin(TUint aTrackId)
{
    DoBegin(aTrackId, ePlayYes);
}

void UriProviderPlaylist::BeginLater(TUint aTrackId)
{
    DoBegin(aTrackId, ePlayLater);
}

EStreamPlay UriProviderPlaylist::GetNext(Media::Track*& aTrack)
{
    EStreamPlay canPlay = ePlayYes;
    AutoMutex a(iLock);
    const TUint prevLastTrackId = iLastTrackId;
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
    if (aTrack != NULL && aTrack->Id() == iFirstFailedTrackId) {
        // every single track in a playlist has failed to generate any audio
        // set aTrack to NULL to halt the Filler until the user takes action
        iLastTrackId = prevLastTrackId;
        if (aTrack != NULL) {
            aTrack->RemoveRef();
            aTrack = NULL;
        }
        canPlay = ePlayNo;
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
    return (iPendingCanPlay == ePlayYes);
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
        iPending = iDatabase.NextTrackRef(ITrackDatabase::kTrackIdNone);
        iPendingCanPlay = (iPending == NULL? ePlayNo : ePlayLater);
    }
    iPendingDirection = eBackwards;
    return (iPendingCanPlay == ePlayYes);
}

void UriProviderPlaylist::DoBegin(TUint aTrackId, EStreamPlay aPendingCanPlay)
{
    AutoMutex a(iLock);
    if (iPending != NULL) {
        iPending->RemoveRef();
        iPending = NULL;
    }
    iPending = iDatabase.TrackRef(aTrackId);
    if (iPending == NULL) {
        iPending = iDatabase.NextTrackRef(ITrackDatabase::kTrackIdNone);
    }
    iPendingCanPlay = aPendingCanPlay;
    iPendingDirection = eJumpTo;
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
        if (aIdBefore == iPlayingTrackId) {
            iLastTrackId = iPlayingTrackId;
        }

        // allow additional loop round the playlist in case the new track is the only one that is playable
        iFirstFailedTrackId = ITrackDatabase::kTrackIdNone;
    }

    iObserver.NotifyTrackInserted(aTrack, aIdBefore, aIdAfter);
}

void UriProviderPlaylist::NotifyTrackDeleted(TUint aId, Track* aBefore, Track* aAfter)
{
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

    iObserver.NotifyTrackDeleted(aId, aBefore, aAfter);
}

void UriProviderPlaylist::NotifyAllDeleted()
{
    {
        AutoMutex a(iLock);
        if (iPending != NULL) {
            iPending->RemoveRef();
            iPending = NULL;
        }
        iIdManager.InvalidateAll();
    }

    iObserver.NotifyAllDeleted();
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

void UriProviderPlaylist::NotifyTrackPlay(Track& /*aTrack*/)
{
    iLock.Wait();
    iFirstFailedTrackId = ITrackDatabase::kTrackIdNone;
    iLock.Signal();
}

void UriProviderPlaylist::NotifyTrackFail(Track& aTrack)
{
    iLock.Wait();
    if (iFirstFailedTrackId == ITrackDatabase::kTrackIdNone) {
        iFirstFailedTrackId = aTrack.Id();
    }
    iLock.Signal();
}
