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
    , iShuffle(false)
    , iSeq(0)
    , iCursorIndex(0)
{
    iTrackList.reserve(kMaxTracks);
    iShuffleList.reserve(kMaxTracks);
    // FIXME - Shuffle handling is likely incomplete.
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

TUint PlaylistDatabase::IdToIndex(TUint aId) const
{
    AutoMutex a(iLock);
    return TrackIndexFromId(aId);
}

TUint PlaylistDatabase::IndexToId(TUint aIndex) const
{
    AutoMutex a(iLock);
    if (aIndex >= iTrackList.size()) {
        THROW(PlaylistDbIdNotFound);
    }
    return iTrackList[aIndex]->Id();
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
            iIdManager.InvalidatePending();
            // no need to update iCursorIndex - we never use it in Shuffle mode
        }
        else {
            TUint idAfter = aIdAfter;
            if (idAfter == kTrackIdNone) {
                idAfter = iTrackList[iTrackList.size()-1]->Id();
            }
            iIdManager.InvalidateAfter(idAfter);
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

void PlaylistDatabase::NextTrack(Media::Track*& aTrack, TBool& aWrapped)
{
    aTrack = NULL;
    AutoMutex a(iLock);
    if (iShuffle) {
        // FIXME
        ASSERTS();
        return;
    }
    if (iCursorIndex >= iTrackList.size()) {
        iCursorIndex = 0;
        aWrapped = true;
    }
    aTrack = iTrackList[iCursorIndex];
    iCursorIndex++;
    aTrack->AddRef();
}

TBool PlaylistDatabase::TryMoveCursorAfter(TUint aId, TBool& aWrapped)
{
    AutoMutex a(iLock);
    if (iShuffle) {
        return true;
    }
    TBool moved = false;
    TUint index;
    try {
        index = TrackIndexFromId(aId);
        if (index < iTrackList.size()-1) {
            iCursorIndex = index+1;
        }
        else {
            iCursorIndex = 0;
            aWrapped = true;
        }
        moved = true;
    }
    catch (PlaylistDbIdNotFound&) { }
    return moved;
}

TBool PlaylistDatabase::TryMoveCursorBefore(TUint aId, TBool aCanWrap, TBool& aWouldWrap)
{
    AutoMutex a(iLock);
    if (iShuffle) {
        return true;
    }
    TBool moved = false;
    TUint index;
    try {
        index = TrackIndexFromId(aId);
        if (index != 0) {
            iCursorIndex = index-1;
        }
        else {
            iCursorIndex = 0;
            aWouldWrap = true;
            if (aCanWrap) {
                index = iTrackList.size()-1;
            }
        }
        moved = true;
    }
    catch (PlaylistDbIdNotFound&) { }
    return moved;
}

TUint PlaylistDatabase::IndexFromId(const std::vector<Media::Track*>& aList, TUint aId) const
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
