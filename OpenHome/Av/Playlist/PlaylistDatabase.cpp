#include <OpenHome/Av/Playlist/PlaylistDatabase.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/IdManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// PlaylistDatabase

PlaylistDatabase::PlaylistDatabase(TrackFactory& aTrackFactory, IPipelineIdManager& aIdManager)
    : iLock("UPPL")
    , iTrackFactory(aTrackFactory)
    , iIdManager(aIdManager)
    , iObserver(NULL)
    , iRepeat(false)
    , iShuffle(false)
    , iSeq(0)
    , iCursorIndex(0)
{
    iTrackList.reserve(kMaxTracks);
    iShuffleList.reserve(kMaxTracks);
    // FIXME - Shuffle & Repeat handling is likely incomplete.
    // FIXME - no unit tests
}

TUint PlaylistDatabase::NextTrackId() const
{
    TUint trackId = kTrackIdNone;
    iLock.Wait();
    if (iCursorIndex < iTrackList.size()) {
        trackId = iTrackList[iCursorIndex]->Id();
    }
    iLock.Signal();
    return trackId;
}

void PlaylistDatabase::SetObserver(IPlaylistDatabaseObserver& aObserver)
{
    iObserver = &aObserver;
}

void PlaylistDatabase::GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const
{
    AutoMutex a(iLock);
    TUint i;
    for (i=0; i<iTrackList.size(); i++) {
        aIdArray[i] = iTrackList[i]->Id();
    }
    for (i=iTrackList.size(); i<kMaxTracks; i++) {
        aIdArray[i] = kTrackIdNone;
    }
    aSeq = iSeq;
}

void PlaylistDatabase::SetRepeat(TBool aRepeat)
{
    AutoMutex a(iLock);
    iRepeat = aRepeat;
    // FIXME
}

void PlaylistDatabase::SetShuffle(TBool aShuffle)
{
    AutoMutex a(iLock);
    iShuffle = aShuffle;
    // FIXME
}

void PlaylistDatabase::GetTrackById(TUint aId, Track*& aTrack) const
{
    AutoMutex a(iLock);
    std::vector<Media::Track*>::const_iterator it = iTrackList.begin();
    while (it != iTrackList.end()) {
        if (*it != NULL && (*it)->Id() == aId) {
            aTrack = *it;
            aTrack->AddRef();
            return;
        }
        it++;
    }
    THROW(PlaylistDbIdNotFound);
}

void PlaylistDatabase::GetTrackById(TUint aId, TUint aSeq, Track*& aTrack, TUint& aIndex) const
{
    AutoMutex a(iLock);
    aTrack = NULL;
    if (iSeq != aSeq) {
        GetTrackById(aId, aTrack);
        return;
    }
    for (TUint i=aIndex; i<kMaxTracks; i++) {
        if (iTrackList[i] == NULL) {
            break;
        }
        if (iTrackList[i]->Id() == aId) {
            aTrack = iTrackList[i];
            aTrack->AddRef();
            aIndex = i;
            return;
        }
    }
    for (TUint i=0; i<aIndex; i++) {
        if (iTrackList[i] == NULL) {
            THROW(PlaylistDbIdNotFound);
        }
        if (iTrackList[i]->Id() == aId) {
            aTrack = iTrackList[i];
            aTrack->AddRef();
            aIndex = i;
            return;
        }
    }
    THROW(PlaylistDbIdNotFound);
}

void PlaylistDatabase::Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted)
{
    TBool changed = false;
    {
        AutoMutex a(iLock);
        if (iTrackList.size() == kMaxTracks) {
            THROW(PlaylistDbFull);
        }
        TUint index = 0;
        if (aIdAfter != kTrackIdNone) {
            index = TrackIndexFromId(aIdAfter) + 1;
        }
        Track* track = iTrackFactory.CreateTrack(aUri, aMetaData, NULL);
        aIdInserted = track->Id();
        iTrackList.insert(iTrackList.begin() + index, track);
        changed = true;
        iSeq++;
        if (iShuffle) {
            track->AddRef();
            iShuffleList.push_back(track);
            iIdManager.InvalidateAll(); // FIXME - this may cancel the current track.  Want something like InvalidatePending() instead.
            // no need to update iCursorIndex - we never use it in Shuffle mode
        }
        else {
            iIdManager.InvalidateAfter(aIdAfter);
            if (index < iCursorIndex) {
                iCursorIndex++;
            }
        }
    }
    if (changed) {
        iObserver->PlaylistDatabaseChanged();
    }
}

void PlaylistDatabase::DeleteId(TUint aId)
{
    TBool changed = false;
    {
        AutoMutex a(iLock);
        TUint index = TrackIndexFromId(aId);
        iTrackList[index]->RemoveRef();
        (void)iTrackList.erase(iTrackList.begin() + index);
        changed = true;
        iSeq++;
        if (iShuffle) {
            try {
                index = ShuffleIndexFromId(aId);
                iShuffleList[index]->RemoveRef();
                (void)iShuffleList.erase(iShuffleList.begin() + index);
            }
            catch (PlaylistDbIdNotFound&) { }
        }
        else {
            if (index < iCursorIndex) {
                iCursorIndex--;
            }
        }
        iIdManager.InvalidateAt(aId);
    }
    if (changed) {
        iObserver->PlaylistDatabaseChanged();
    }
}

void PlaylistDatabase::DeleteAll()
{
    TBool changed = false;
    {
        AutoMutex a(iLock);
        changed = (iTrackList.size() > 0);
        Clear(iTrackList);
        Clear(iShuffleList);
        iSeq++;
        iIdManager.InvalidateAll();
    }
    if (changed) {
        iObserver->PlaylistDatabaseChanged();
    }
}

void PlaylistDatabase::MoveCursorTo(TUint aId)
{
    AutoMutex a(iLock);
    if (iShuffle) {
        return;
    }
    try {
        iCursorIndex = TrackIndexFromId(aId);
    }
    catch (PlaylistDbIdNotFound&) {
        iCursorIndex = 0;
    }
}

Track* PlaylistDatabase::NextTrack()
{
    Track* track = NULL;
    iLock.Wait();
    if (iShuffle) {
        ASSERTS(); // FIXME
    }
    else {
        if (iCursorIndex > iTrackList.size()) {
            if (iRepeat) {
                iCursorIndex = 0;
            }
            else {
                // FIXME - want to return a Track #0 but indicate that it shouldn't be played
            }
        }
        if (iCursorIndex < iTrackList.size()) {
            track = iTrackList[iCursorIndex];
            iCursorIndex++;
            track->AddRef();
        }
    }
    iLock.Signal();
    return track;
}

TBool PlaylistDatabase::TryMoveCursorAfter(TUint aId)
{
    return TryMoveCursor(aId, true);
}

TBool PlaylistDatabase::TryMoveCursorBefore(TUint aId)
{
    return TryMoveCursor(aId, false);
}

TBool PlaylistDatabase::TryMoveCursor(TUint aId, TBool aAfter)
{
    // FIXME - rules for (before && iCursorIndex==0) and (after && iCursorIndex==iTrackList.size())
    AutoMutex a(iLock);
    if (iShuffle) {
        return true;
    }
    TBool moved = false;
    TUint index;
    try {
        index = TrackIndexFromId(aId);
        if (aAfter) {
            if (index > iTrackList.size() - 1) {
                // FIXME
            }
            else {
                iCursorIndex = index+1;
            }
        }
        else { // MoveCursorBefore
            if (index == 0) {
                // FIXME
            }
            else {
                iCursorIndex = index-1;
            }
        }
        moved = true;
    }
    catch (PlaylistDbIdNotFound&) { }
    return moved;
}

TUint PlaylistDatabase::IndexFromId(std::vector<Media::Track*>& aList, TUint aId)
{
    for (TUint i=0; i<aList.size(); i++) {
        if (aList[i] != NULL && aList[i]->Id() == aId) {
            return i;
        }
    }
    THROW(PlaylistDbIdNotFound);
}

void PlaylistDatabase::Clear(std::vector<Media::Track*>& aList)
{
    for (TUint i=0; i<aList.size(); i++) {
        if (aList[i] != NULL) {
            aList[i]->RemoveRef();
        }
    }
    aList.clear();
}
