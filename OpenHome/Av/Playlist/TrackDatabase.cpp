#include <OpenHome/Av/Playlist/TrackDatabase.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>

#include <algorithm>
#include <array>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

static inline void AddRefIfNonNull(Track* aTrack)
{
    if (aTrack != nullptr) {
        aTrack->AddRef();
    }
}

static inline void RemoveRefIfNonNull(Track* aTrack)
{
    if (aTrack != nullptr) {
        aTrack->RemoveRef();
    }
}

// TrackDatabase

TrackDatabase::TrackDatabase(TrackFactory& aTrackFactory)
    : iLock("TDB1")
    , iObserverLock("TDB2")
    , iTrackFactory(aTrackFactory)
    , iSeq(0)
{
    iTrackList.reserve(kMaxTracks);
}

TrackDatabase::~TrackDatabase()
{
    TrackListUtils::Clear(iTrackList);
}

void TrackDatabase::AddObserver(ITrackDatabaseObserver& aObserver)
{
    iObservers.push_back(&aObserver);
}

void TrackDatabase::GetIdArray(std::array<TUint32, kMaxTracks>& aIdArray, TUint& aSeq) const
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

void TrackDatabase::GetTrackById(TUint aId, Track*& aTrack) const
{
    AutoMutex a(iLock);
    return GetTrackByIdLocked(aId, aTrack);
}

void TrackDatabase::GetTrackByIdLocked(TUint aId, Track*& aTrack) const
{
    const TUint index = TrackListUtils::IndexFromId(iTrackList, aId);
    aTrack = iTrackList[index];
    aTrack->AddRef();
}

void TrackDatabase::GetTrackById(TUint aId, TUint aSeq, Track*& aTrack, TUint& aIndex) const
{
    AutoMutex a(iLock);
    aTrack = nullptr;
    if (iSeq != aSeq) {
        GetTrackByIdLocked(aId, aTrack);
        return;
    }
    if (!TryGetTrackById(aId, aTrack, aIndex, iTrackList.size(), aIndex)) {
        TUint endIndex = std::min(aIndex, (TUint)iTrackList.size());
        if (!TryGetTrackById(aId, aTrack, 0, endIndex, aIndex)) {
            THROW(TrackDbIdNotFound);
        }
    }
}

void TrackDatabase::Insert(TUint aIdAfter, const Brx& aUri, const Brx& aMetaData, TUint& aIdInserted)
{
    Track* track;
    TUint idBefore, idAfter;
    AutoMutex _(iObserverLock);
    {
        AutoMutex a(iLock);
        if (iTrackList.size() == kMaxTracks) {
            THROW(TrackDbFull);
        }
        TUint index = 0;
        if (aIdAfter != kTrackIdNone) {
            index = TrackListUtils::IndexFromId(iTrackList, aIdAfter) + 1;
        }
        track = iTrackFactory.CreateTrack(aUri, aMetaData);
        aIdInserted = track->Id();
        iTrackList.insert(iTrackList.begin() + index, track);
        iSeq++;
        idBefore = aIdAfter;
        idAfter = (index == iTrackList.size()-1? kTrackIdNone : index+1);
    }
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackInserted(*track, idBefore, idAfter);
    }
}

void TrackDatabase::DeleteId(TUint aId)
{
    Track* before = nullptr;
    Track* after = nullptr;
    AutoMutex _(iObserverLock);
    {
        AutoMutex a(iLock);
        TUint index = TrackListUtils::IndexFromId(iTrackList, aId);
        if (index > 0) {
            before = iTrackList[index-1];
            before->AddRef();
        }
        if (index < iTrackList.size()-1) {
            after = iTrackList[index+1];
            after->AddRef();
        }
        iTrackList[index]->RemoveRef();
        (void)iTrackList.erase(iTrackList.begin() + index);
        iSeq++;
    }
    for (TUint i=0; i<iObservers.size(); i++) {
        iObservers[i]->NotifyTrackDeleted(aId, before, after);
    }
    RemoveRefIfNonNull(before);
    RemoveRefIfNonNull(after);
}

void TrackDatabase::DeleteAll()
{
    AutoMutex _(iObserverLock);
    iLock.Wait();
    const TBool changed = (iTrackList.size() > 0);
    if (changed) {
        TrackListUtils::Clear(iTrackList);
        iSeq++;
    }
    iLock.Signal();
    if (changed) {
        for (TUint i=0; i<iObservers.size(); i++) {
            iObservers[i]->NotifyAllDeleted();
        }
    }
}

TUint TrackDatabase::TrackCount() const
{
    iLock.Wait();
    const TUint count = iTrackList.size();
    iLock.Signal();
    return count;
}

void TrackDatabase::SetObserver(ITrackDatabaseObserver& aObserver)
{
    iLock.Wait();
    AddObserver(aObserver);
    iLock.Signal();
}

Track* TrackDatabase::TrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    try {
        const TUint index = TrackListUtils::IndexFromId(iTrackList, aId);
        track = iTrackList[index];
        track->AddRef();
    }
    catch (TrackDbIdNotFound&) { }
    return track;
}

Track* TrackDatabase::NextTrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    if (aId == kTrackIdNone) {
        if (iTrackList.size() > 0) {
            track = iTrackList[0];
            track->AddRef();
        }
    }
    else {
        try {
            const TUint index = TrackListUtils::IndexFromId(iTrackList, aId);
            if (index < iTrackList.size()-1) {
                track = iTrackList[index+1];
                track->AddRef();
            }
        }
        catch (TrackDbIdNotFound&) { }
    }
    return track;
}

Track* TrackDatabase::PrevTrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    try {
        const TUint index = TrackListUtils::IndexFromId(iTrackList, aId);
        if (index > 0) {
            track = iTrackList[index-1];
            track->AddRef();
        }
    }
    catch (TrackDbIdNotFound&) { }
    return track;
}

Track* TrackDatabase::TrackRefByIndex(TUint aIndex)
{
    Track* track = nullptr;
    iLock.Wait();
    if (aIndex < iTrackList.size()) {
        track = iTrackList[aIndex];
        track->AddRef();
    }
    iLock.Signal();
    return track;
}

Track* TrackDatabase::TrackRefByIndexSorted(TUint /*aIndex*/)
{
    ASSERTS();
    return nullptr;
}

TBool TrackDatabase::TryGetTrackById(TUint aId, Track*& aTrack, TUint aStartIndex, TUint aEndIndex, TUint& aFoundIndex) const
{
    for (TUint i=aStartIndex; i<aEndIndex; i++) {
        if (iTrackList[i]->Id() == aId) {
            aTrack = iTrackList[i];
            aTrack->AddRef();
            aFoundIndex = i;
            return true;
        }
    }
    return false;
}


// Shuffler

Shuffler::Shuffler(Environment& aEnv, ITrackDatabaseReader& aReader)
    : iLock("TSHF")
    , iEnv(aEnv)
    , iReader(aReader)
    , iObserver(nullptr)
    , iPrevTrackId(ITrackDatabase::kTrackIdNone)
    , iShuffle(false)
{
    aReader.SetObserver(*this);
    iShuffleList.reserve(ITrackDatabase::kMaxTracks);
}

TBool Shuffler::Enabled() const
{
    iLock.Wait();
    const TBool enabled = iShuffle;
    iLock.Signal();
    return enabled;
}

Shuffler::~Shuffler()
{
    TrackListUtils::Clear(iShuffleList);
}

void Shuffler::SetShuffle(TBool aShuffle)
{
    iLock.Wait();
    iShuffle = aShuffle;
    DoReshuffle("Shuffled");
    iLock.Signal();
}

void Shuffler::Reshuffle()
{
    iLock.Wait();
    DoReshuffle("Reshuffle");
    iLock.Signal();
}

TBool Shuffler::TryMoveToStart(TUint aId)
{
    AutoMutex a(iLock);
    if (iShuffle) {
        try {
            const TUint index = TrackListUtils::IndexFromId(iShuffleList, aId);
            Track* track = iShuffleList[index];
            MoveToStartOfUnplayed(track, "MoveToStart");
            return true;
        }
        catch (TrackDbIdNotFound&) {}
    }
    return false;
}

void Shuffler::SetObserver(ITrackDatabaseObserver& aObserver)
{
    iLock.Wait();
    iObserver = &aObserver;
    iLock.Signal();
}

Track* Shuffler::TrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    if (iShuffle) {
        try {
            const TUint index = TrackListUtils::IndexFromId(iShuffleList, aId);
            track = iShuffleList[index];
            track->AddRef();
            iPrevTrackId = track->Id();
            LogIds("TrackRef");
        }
        catch (TrackDbIdNotFound&) {
            iPrevTrackId = ITrackDatabase::kTrackIdNone;
        }
    }
    else {
        track = iReader.TrackRef(aId);
    }
    return track;
}

Track* Shuffler::NextTrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    if (!iShuffle) {
        track = iReader.NextTrackRef(aId);
    }
    else {
        if (aId == ITrackDatabase::kTrackIdNone) {
            if (iShuffleList.size() > 0) {
                track = iShuffleList[0];
                track->AddRef();
            }
        }
        else {
            try {
                const TUint index = TrackListUtils::IndexFromId(iShuffleList, aId);
                if (index < iShuffleList.size()-1) {
                    track = iShuffleList[index+1];
                    track->AddRef();
                }
                else if (index == iShuffleList.size()-1) {
                    // we've run through the entire list
                    // prefer re-shuffling over repeating the order of tracks if we play again
                    std::random_shuffle(iShuffleList.begin(), iShuffleList.end());
                    LogIds("NextTrackRef");
                }
            }
            catch (TrackDbIdNotFound&) { }
        }
        iPrevTrackId = (track == nullptr? ITrackDatabase::kTrackIdNone : track->Id());
    }
    return track;
}

Track* Shuffler::PrevTrackRef(TUint aId)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    if (!iShuffle) {
        track = iReader.PrevTrackRef(aId);
    }
    else {
        try {
            const TUint index = TrackListUtils::IndexFromId(iShuffleList, aId);
            if (index != 0) {
                track = iShuffleList[index-1];
                track->AddRef();
            }
        }
        catch (TrackDbIdNotFound&) { }
    }
    if (iShuffle) {
        if (track == nullptr) {
            iPrevTrackId = ITrackDatabase::kTrackIdNone;
        }
        else {
            iPrevTrackId = track->Id();
        }
    }
    return track;
}

Track* Shuffler::TrackRefByIndex(TUint aIndex)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    track = iReader.TrackRefByIndex(aIndex);
    if (iShuffle && track != nullptr) {
        MoveToStartOfUnplayed(track, "TrackRefByIndex");
    }
        
    return track;
}

Track* Shuffler::TrackRefByIndexSorted(TUint aIndex)
{
    Track* track = nullptr;
    AutoMutex a(iLock);
    if (!iShuffle) {
        track = iReader.TrackRefByIndex(aIndex);
    }
    else if (aIndex < iShuffleList.size()) {
        track = iShuffleList[aIndex];
        track->AddRef();
    }
    return track;
}

void Shuffler::NotifyTrackInserted(Track& aTrack, TUint aIdBefore, TUint aIdAfter)
{
    TUint idBefore = aIdBefore;
    TUint idAfter = aIdAfter;
    try {
        AutoMutex a(iLock);
        TUint index = 0;
        if (iShuffleList.size() > 0) {
            TUint min = 0;
            if (iPrevTrackId != ITrackDatabase::kTrackIdNone) {
                min = TrackListUtils::IndexFromId(iShuffleList, iPrevTrackId) + 1;
            }
            if (min == iShuffleList.size()) {
                index = min;
            }
            else {
                index = iEnv.Random(iShuffleList.size(), min);
            }
        }
        iShuffleList.insert(iShuffleList.begin() + index, &aTrack);
        aTrack.AddRef();
        if (iShuffle) {
            idBefore = (index == 0? ITrackDatabase::kTrackIdNone : iShuffleList[index-1]->Id());
            idAfter = (index == iShuffleList.size()-1? ITrackDatabase::kTrackIdNone : iShuffleList[index+1]->Id());
            LogIds("TrackInserted");
        }
    }
    catch (TrackDbIdNotFound&) {
        return;
    }
    iObserver->NotifyTrackInserted(aTrack, idBefore, idAfter);
}

void Shuffler::NotifyTrackDeleted(TUint aId, Track* aBefore, Track* aAfter)
{
    Track* before = aBefore;
    Track* after = aAfter;
    try {
        AutoMutex a(iLock);
        const TUint index = TrackListUtils::IndexFromId(iShuffleList, aId);
        if (iShuffle) {
            before = (index==0? nullptr : iShuffleList[index-1]);
            after = (index==iShuffleList.size()-1? nullptr : iShuffleList[index+1]);
            if (iShuffleList[index]->Id() == iPrevTrackId) {
                if (index == 0) {
                    iPrevTrackId = ITrackDatabase::kTrackIdNone;
                }
                else {
                    iPrevTrackId = iShuffleList[index-1]->Id();
                }
            }
        }
        iShuffleList[index]->RemoveRef();
        iShuffleList.erase(iShuffleList.begin() + index);
        LogIds("TrackDeleted");
        AddRefIfNonNull(before);
        AddRefIfNonNull(after);
    }
    catch (TrackDbIdNotFound&) {
        return;
    }
    iObserver->NotifyTrackDeleted(aId, before, after);
    RemoveRefIfNonNull(before);
    RemoveRefIfNonNull(after);
}

void Shuffler::NotifyAllDeleted()
{
    iLock.Wait();
    iPrevTrackId = ITrackDatabase::kTrackIdNone;
    TrackListUtils::Clear(iShuffleList);
    iLock.Signal();
    iObserver->NotifyAllDeleted();
}

void Shuffler::DoReshuffle(const TChar* aLogPrefix)
{
    if (iShuffle) { // prefer re-shuffling over repeating the order of tracks if we play again
        std::random_shuffle(iShuffleList.begin(), iShuffleList.end());
        LogIds(aLogPrefix);
        iPrevTrackId = ITrackDatabase::kTrackIdNone;
    }
}

void Shuffler::MoveToStartOfUnplayed(Track* aTrack, const TChar* aLogPrefix)
{
    const TUint index = TrackListUtils::IndexFromId(iShuffleList, aTrack->Id());
    const TUint cursorIndex = (iPrevTrackId == ITrackDatabase::kTrackIdNone?
            0 : TrackListUtils::IndexFromId(iShuffleList, iPrevTrackId));
    if (index > cursorIndex+1) {
        iShuffleList.erase(iShuffleList.begin() + index);
        iShuffleList.insert(iShuffleList.begin() + cursorIndex, aTrack);
    }
    iPrevTrackId = aTrack->Id();
    LogIds(aLogPrefix);
}

void Shuffler::LogIds(const TChar* aPrefix)
{
    LOG(kSources, "%s.  New track order is: { ", aPrefix);
    if (iShuffleList.size() > 0) {
        LOG(kSources, "%u", iShuffleList[0]->Id());
        for (TUint i=1; i<iShuffleList.size(); i++) {
            LOG(kSources, ", %u", iShuffleList[i]->Id());
        }
    }
    LOG(kSources, "}\n");
}


// Repeater

Repeater::Repeater(ITrackDatabaseReader& aReader)
    : iLock("TRPT")
    , iReader(aReader)
    , iObserver(nullptr)
    , iRepeat(false)
    , iTrackCount(0)
{
}

void Repeater::SetRepeat(TBool aRepeat)
{
    iRepeat = aRepeat;
}

void Repeater::SetObserver(ITrackDatabaseObserver& aObserver)
{
    iObserver = &aObserver;
    iReader.SetObserver(*this);
}

Track* Repeater::TrackRef(TUint aId)
{
    AutoMutex a(iLock);
    Track* track = iReader.TrackRef(aId);
    if (track == nullptr && iRepeat) {
        track = iReader.TrackRef(ITrackDatabase::kTrackIdNone);
    }
    return track;
}

Track* Repeater::NextTrackRef(TUint aId)
{
    AutoMutex a(iLock);
    Track* track = iReader.NextTrackRef(aId);
    if (track == nullptr && iRepeat) {
        track = iReader.NextTrackRef(ITrackDatabase::kTrackIdNone);
    }
    return track;
}

Track* Repeater::TrackRefByIndex(TUint aIndex)
{
    return iReader.TrackRefByIndex(aIndex);
}

Track* Repeater::TrackRefByIndexSorted(TUint /*aIndex*/)
{
    ASSERTS();
    return nullptr;
}

Track* Repeater::PrevTrackRef(TUint aId)
{
    AutoMutex a(iLock);
    Track* track = iReader.PrevTrackRef(aId);
    if (track == nullptr && iRepeat) {
        track = iReader.TrackRefByIndexSorted(iTrackCount-1);
    }
    return track;
}

void Repeater::NotifyTrackInserted(Track& aTrack, TUint aIdBefore, TUint aIdAfter)
{
    iLock.Wait();
    iTrackCount++;
    ASSERT(iTrackCount <= ITrackDatabase::kMaxTracks);
    iLock.Signal();
    iObserver->NotifyTrackInserted(aTrack, aIdBefore, aIdAfter);
}

void Repeater::NotifyTrackDeleted(TUint aId, Track* aBefore, Track* aAfter)
{
    iLock.Wait();
    iTrackCount--;
    ASSERT(iTrackCount <= ITrackDatabase::kMaxTracks);
    iLock.Signal();
    iObserver->NotifyTrackDeleted(aId, aBefore, aAfter);
}

void Repeater::NotifyAllDeleted()
{
    iLock.Wait();
    iTrackCount = 0;
    iLock.Signal();
    iObserver->NotifyAllDeleted();
}


// TrackListUtils

TUint TrackListUtils::IndexFromId(const std::vector<Track*>& aList, TUint aId)
{ // static
    for (TUint i=0; i<aList.size(); i++) {
        if (aList[i]->Id() == aId) {
            return i;
        }
    }
    THROW(TrackDbIdNotFound);
}

void TrackListUtils::Clear(std::vector<Track*>& aList)
{ // static
    for (TUint i=0; i<aList.size(); i++) {
        aList[i]->RemoveRef();
    }
    aList.clear();
}
