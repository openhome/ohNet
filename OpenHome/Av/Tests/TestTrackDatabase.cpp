#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Av/Playlist/TrackDatabase.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Net/Private/Globals.h>

#include <limits.h>
#include <array>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Av {

class SuiteTrackDatabase : public SuiteUnitTest, private ITrackDatabaseObserver
{
public:
    SuiteTrackDatabase();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    void InsertInitialTrack();
    void InsertFailsWhenIdAfterInvalid();
    void InsertFailsWhenFull();
    void GetIdArrayDbEmpty();
    void GetIdArrayDbPartiallyFull();
    void GetIdArrayDbFull();
    void InsertAtStart();
    void InsertInMiddle();
    void InsertAtEnd();
    void DeleteValidId();
    void DeleteInvalidId();
    void DeleteAll();
    void SeqUpdatesOnChanges();
    void GetTrackByValidId();
    void GetTrackByInvalidIdFails();
    void GetTrackByIdValidSeq();
    void GetTrackByIdInvalidSeq();
    void MultipleObservers();
private:
    Media::AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    TrackDatabase* iDb;
    ITrackDatabase* iTrackDatabase;
    std::array<TUint32, ITrackDatabase::kMaxTracks> iIdArray;
    TUint iInsertedCount;
    TUint iIdLastInserted;
    TUint iIdLastInsertedBefore;
    TUint iIdLastInsertedAfter;
    TUint iDeletedCount;
    TUint iIdLastDeleted;
    TUint iIdLastDeletedBefore;
    TUint iIdLastDeletedAfter;
    TUint iAllDeletedCount;
};

class SuiteTrackReader : public SuiteUnitTest, private ITrackDatabaseObserver
{
public:
    SuiteTrackReader();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    void TrackRefValidId();
    void TrackRefInvalidId();
    void NextTrackRefValidId();
    void NextTrackRefInvalidId();
    void PrevTrackRefValidId();
    void PrevTrackRefInvalidId();
    void TrackRefByIndexValidId();
    void TrackRefByIndexInvalidId();
    void TrackRefByIndexSortedValidId();
    void TrackRefByIndexSortedInvalidId();
private:
    static const TUint kNumTracks = 3;
    Media::AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    TrackDatabase* iDb;
    ITrackDatabaseReader* iReader;
    TUint iIds[kNumTracks];
};

class SuiteShuffler : public SuiteUnitTest, private ITrackDatabaseObserver
{
public:
    SuiteShuffler();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    void TrackRefShuffleOff();
    void TrackRefShuffleOn();
    void NextTrackRefShuffleOff();
    void NextTrackRefShuffleOn();
    void PrevTrackRefShuffleOff();
    void PrevTrackRefShuffleOn();
    void TrackRefByIndexShuffleOff();
    void TrackRefByIndexShuffleOn();
    void TrackRefByIndexSortedShuffleOff();
    void TrackRefByIndexSortedShuffleOn();
    void ModeToggleReshuffles();
    void NextTrackBeyondEndReshuffles();
private:
    static const TUint kNumTracks = 16; // gives us ~1 in 21 trillion chance of shuffling tracks into their original order
    Media::AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    TrackDatabase* iDb;
    Shuffler* iShuffler;
    ITrackDatabaseReader* iReader;
    std::array<TUint, kNumTracks> iIds;
};

class SuiteRepeater : public SuiteUnitTest, private ITrackDatabaseObserver
{
public:
    SuiteRepeater();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from ITrackDatabaseObserver
    void NotifyTrackInserted(Media::Track& aTrack, TUint aIdBefore, TUint aIdAfter) override;
    void NotifyTrackDeleted(TUint aId, Media::Track* aBefore, Media::Track* aAfter) override;
    void NotifyAllDeleted() override;
private:
    void TrackRefRepeatOff();
    void TrackRefRepeatOn();
    void NextFromLastTrackRepeatOff();
    void NextFromLastTrackRepeatOn();
    void PrevFromFirstTrackRepeatOff();
    void PrevFromFirstTrackRepeatOn();
    void TrackRefByIndexRepeatOff();
    void TrackRefByIndexRepeatOn();
    void TrackRefByIndexSortedRepeatOff();
    void TrackRefByIndexSortedRepeatOn();
private:
    static const TUint kNumTracks = 3;
    Media::AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    TrackDatabase* iDb;
    Shuffler* iShuffler;
    Repeater* iRepeater;
    ITrackDatabaseReader* iReader;
    std::array<TUint, kNumTracks> iIds;
};

} // namespace Av
} // namespace OpenHome

// SuiteTrackDatabase

SuiteTrackDatabase::SuiteTrackDatabase()
    : SuiteUnitTest("Track database (ITrackDatabase)")
{
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertInitialTrack), "InsertInitialTrack");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertFailsWhenIdAfterInvalid), "InsertFailsWhenIdAfterInvalid");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertFailsWhenFull), "InsertFailsWhenFull");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetIdArrayDbEmpty), "GetIdArrayDbEmpty");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetIdArrayDbPartiallyFull), "GetIdArrayDbPartiallyFull");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetIdArrayDbFull), "GetIdArrayDbFull");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertAtStart), "InsertAtStart");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertInMiddle), "InsertInMiddle");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::InsertAtEnd), "InsertAtEnd");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::DeleteValidId), "DeleteValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::DeleteInvalidId), "DeleteInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::DeleteAll), "DeleteAll");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::SeqUpdatesOnChanges), "SeqUpdatesOnChanges");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetTrackByValidId), "GetTrackByValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetTrackByInvalidIdFails), "GetTrackByInvalidIdFails");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetTrackByIdValidSeq), "GetTrackByIdValidSeq");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::GetTrackByIdInvalidSeq), "GetTrackByIdInvalidSeq");
    AddTest(MakeFunctor(*this, &SuiteTrackDatabase::MultipleObservers), "MultipleObservers");
}

void SuiteTrackDatabase::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, ITrackDatabase::kMaxTracks);
    iDb = new TrackDatabase(*iTrackFactory);
    iTrackDatabase = static_cast<ITrackDatabase*>(iDb);
    iTrackDatabase->AddObserver(*this);
    iInsertedCount = iDeletedCount = iAllDeletedCount = 0;
    iIdLastInserted = iIdLastInsertedBefore = iIdLastInsertedAfter = 
        iIdLastDeleted = iIdLastDeletedBefore = iIdLastDeletedAfter = UINT_MAX;
}

void SuiteTrackDatabase::TearDown()
{
    delete iDb;
    delete iTrackFactory;
}

void SuiteTrackDatabase::NotifyTrackInserted(Track& aTrack, TUint aIdBefore, TUint aIdAfter)
{
    iInsertedCount++;
    iIdLastInserted = aTrack.Id();
    iIdLastInsertedBefore = aIdBefore;
    iIdLastInsertedAfter = aIdAfter;
}

void SuiteTrackDatabase::NotifyTrackDeleted(TUint aId, Track* aBefore, Track* aAfter)
{
    iDeletedCount++;
    iIdLastDeleted = aId;
    iIdLastDeletedBefore = (aBefore==NULL? ITrackDatabase::kTrackIdNone : aBefore->Id());
    iIdLastDeletedAfter = (aAfter==NULL? ITrackDatabase::kTrackIdNone : aAfter->Id());
}

void SuiteTrackDatabase::NotifyAllDeleted()
{
    iAllDeletedCount++;
}

void SuiteTrackDatabase::InsertInitialTrack()
{
    TUint inserted;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), inserted);
    TEST(iInsertedCount == 1);
    TEST(inserted != ITrackDatabase::kTrackIdNone);
    TEST(iIdLastInserted == inserted);
    TEST(iIdLastInsertedBefore == ITrackDatabase::kTrackIdNone);
    TEST(iIdLastInsertedAfter == ITrackDatabase::kTrackIdNone);
}

void SuiteTrackDatabase::InsertFailsWhenIdAfterInvalid()
{
    TUint inserted;
    TEST_THROWS(iTrackDatabase->Insert(1, Brx::Empty(), Brx::Empty(), inserted), TrackDbIdNotFound);
    TEST(iInsertedCount == 0);
}

void SuiteTrackDatabase::InsertFailsWhenFull()
{
    TUint after = ITrackDatabase::kTrackIdNone;
    TUint newId;
    for (TUint i=0; i<ITrackDatabase::kMaxTracks; i++) {
        iTrackDatabase->Insert(after, Brx::Empty(), Brx::Empty(), newId);
        after = newId;
    }
    TEST_THROWS(iTrackDatabase->Insert(after, Brx::Empty(), Brx::Empty(), newId), TrackDbFull);
    TEST_THROWS(iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), newId), TrackDbFull);
}

void SuiteTrackDatabase::GetIdArrayDbEmpty()
{
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    for (TUint i=0; i<ITrackDatabase::kMaxTracks; i++) {
        TEST_QUIETLY(iIdArray[i] == ITrackDatabase::kTrackIdNone);
    }
}

void SuiteTrackDatabase::GetIdArrayDbPartiallyFull()
{
    static const TUint kTrackCount = 100;
    TUint i;
    TUint after = ITrackDatabase::kTrackIdNone;
    TUint newId;
    for (i=0; i<kTrackCount; i++) {
        iTrackDatabase->Insert(after, Brx::Empty(), Brx::Empty(), newId);
        after = newId;
    }
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    std::array<TUint32, kTrackCount> trackIds;
    trackIds.fill((TUint)ITrackDatabase::kTrackIdNone);
    std::array<TUint32, kTrackCount>::iterator it;
    for (i=0; i<kTrackCount; i++) {
        const TUint id = iIdArray[i];
        TEST_QUIETLY(id != ITrackDatabase::kTrackIdNone);
        it = std::find(trackIds.begin(), trackIds.end(), id);
        TEST(it == trackIds.end()); // check that each track id is unique
        trackIds[i] = id;
    }
    for (i=kTrackCount; i<ITrackDatabase::kMaxTracks; i++) {
        TEST_QUIETLY(iIdArray[i] == ITrackDatabase::kTrackIdNone);
    }
}

void SuiteTrackDatabase::GetIdArrayDbFull()
{
    TUint after = ITrackDatabase::kTrackIdNone;
    TUint newId;
    for (TUint i=0; i<ITrackDatabase::kMaxTracks; i++) {
        iTrackDatabase->Insert(after, Brx::Empty(), Brx::Empty(), newId);
        after = newId;
    }
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    for (TUint i=0; i<ITrackDatabase::kMaxTracks; i++) {
        TEST_QUIETLY(iIdArray[i] != ITrackDatabase::kTrackIdNone);
    }
}

void SuiteTrackDatabase::InsertAtStart()
{
    TUint ids[2];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[1]);
    TEST(iInsertedCount == 2);
    TEST(iIdLastInserted == ids[1]);
    TEST(iIdLastInsertedBefore == ITrackDatabase::kTrackIdNone);
    TEST(iIdLastInsertedAfter == ids[0]);
}

void SuiteTrackDatabase::InsertInMiddle()
{
    TUint ids[3];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[1]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[2]);
    TEST(iInsertedCount == 3);
    TEST(iIdLastInserted == ids[2]);
    TEST(iIdLastInsertedBefore == ids[0]);
    TEST(iIdLastInsertedAfter == ids[1]);
}

void SuiteTrackDatabase::InsertAtEnd()
{
    TUint ids[3];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[1]);
    iTrackDatabase->Insert(ids[1], Brx::Empty(), Brx::Empty(), ids[2]);
    TEST(iInsertedCount == 3);
    TEST(iIdLastInserted == ids[2]);
    TEST(iIdLastInsertedBefore == ids[1]);
    TEST(iIdLastInsertedAfter == ITrackDatabase::kTrackIdNone);
}

void SuiteTrackDatabase::DeleteValidId()
{
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->DeleteId(id);
    TEST(iDeletedCount == 1);
    TEST(iIdLastDeleted == id);
    TEST(iIdLastDeletedBefore == ITrackDatabase::kTrackIdNone);
    TEST(iIdLastDeletedAfter == ITrackDatabase::kTrackIdNone);

    TUint ids[3];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[1]);
    iTrackDatabase->Insert(ids[1], Brx::Empty(), Brx::Empty(), ids[2]);
    iTrackDatabase->DeleteId(ids[1]);
    TEST(iDeletedCount == 2);
    TEST(iIdLastDeleted == ids[1]);
    TEST(iIdLastDeletedBefore == ids[0]);
    TEST(iIdLastDeletedAfter == ids[2]);

    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    int count = std::count_if(iIdArray.begin(), iIdArray.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 2);
}

void SuiteTrackDatabase::DeleteInvalidId()
{
    TEST_THROWS(iTrackDatabase->DeleteId(ITrackDatabase::kTrackIdNone), TrackDbIdNotFound);
    TEST_THROWS(iTrackDatabase->DeleteId(1), TrackDbIdNotFound);
    TEST_THROWS(iTrackDatabase->DeleteId(UINT_MAX), TrackDbIdNotFound);
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    TEST_THROWS(iTrackDatabase->DeleteId(id+1), TrackDbIdNotFound);
    TEST(iAllDeletedCount == 0);
}

void SuiteTrackDatabase::DeleteAll()
{
    TUint deleteCbCount = 0;
    TEST(iAllDeletedCount == deleteCbCount);
    iTrackDatabase->DeleteAll();
    TEST(iAllDeletedCount == deleteCbCount);

    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->DeleteAll();
    TEST(iAllDeletedCount == ++deleteCbCount);
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    int count = std::count_if(iIdArray.begin(), iIdArray.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 0);

    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->DeleteAll();
    TEST(iAllDeletedCount == ++deleteCbCount);
    iTrackDatabase->GetIdArray(iIdArray, seq);
    count = std::count_if(iIdArray.begin(), iIdArray.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 0);
}

void SuiteTrackDatabase::SeqUpdatesOnChanges()
{
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TUint prevSeq = seq;
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TEST(seq == prevSeq+1);
    prevSeq = seq;

    iTrackDatabase->DeleteId(id);
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TEST(seq == prevSeq+1);
    prevSeq = seq;

    try {
        iTrackDatabase->DeleteId(id);
    }
    catch (TrackDbIdNotFound&) {}
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TEST(seq == prevSeq);

    iTrackDatabase->DeleteAll();
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TEST(seq == prevSeq);

    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->GetIdArray(iIdArray, seq);
    prevSeq = seq;
    iTrackDatabase->DeleteAll();
    iTrackDatabase->GetIdArray(iIdArray, seq);
    TEST(seq == prevSeq+1);
}

void SuiteTrackDatabase::GetTrackByValidId()
{
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    Track* track;
    iTrackDatabase->GetTrackById(id, track);
    TEST(track != NULL);
    TEST(track->Id() == id);
    track->RemoveRef();
}

void SuiteTrackDatabase::GetTrackByInvalidIdFails()
{
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    Track* track;
    TEST_THROWS(iTrackDatabase->GetTrackById(ITrackDatabase::kTrackIdNone, track), TrackDbIdNotFound);
    TEST_THROWS(iTrackDatabase->GetTrackById(id+1, track), TrackDbIdNotFound);
}

void SuiteTrackDatabase::GetTrackByIdValidSeq()
{
    TUint ids[3];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[1]);
    iTrackDatabase->Insert(ids[1], Brx::Empty(), Brx::Empty(), ids[2]);
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);

    TUint index=0;
    Track* track;
    for (TUint i=0; i<sizeof(ids)/sizeof(ids[0]); i++) {
        iTrackDatabase->GetTrackById(ids[i], seq, track, index);
        TEST(track != NULL);
        TEST(track->Id() == ids[i]);
        track->RemoveRef();
    }

    index = 0;
    track = NULL;
    iTrackDatabase->GetTrackById(ids[2], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[2]);
    track->RemoveRef();
    iTrackDatabase->GetTrackById(ids[1], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[1]);
    track->RemoveRef();
    iTrackDatabase->GetTrackById(ids[0], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[0]);
    track->RemoveRef();
}

void SuiteTrackDatabase::GetTrackByIdInvalidSeq()
{
    TUint ids[3];
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), ids[0]);
    iTrackDatabase->Insert(ids[0], Brx::Empty(), Brx::Empty(), ids[1]);
    iTrackDatabase->Insert(ids[1], Brx::Empty(), Brx::Empty(), ids[2]);
    TUint seq;
    iTrackDatabase->GetIdArray(iIdArray, seq);
    seq--;

    TUint index=0;
    Track* track;
    for (TUint i=0; i<sizeof(ids)/sizeof(ids[0]); i++) {
        iTrackDatabase->GetTrackById(ids[i], seq, track, index);
        TEST(track != NULL);
        TEST(track->Id() == ids[i]);
        track->RemoveRef();
    }

    index = 0;
    track = NULL;
    iTrackDatabase->GetTrackById(ids[2], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[2]);
    track->RemoveRef();
    iTrackDatabase->GetTrackById(ids[1], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[1]);
    track->RemoveRef();
    iTrackDatabase->GetTrackById(ids[0], seq, track, index);
    TEST(track != NULL);
    TEST(track->Id() == ids[0]);
    track->RemoveRef();
}

void SuiteTrackDatabase::MultipleObservers()
{
    iTrackDatabase->AddObserver(*this);
    TUint id;
    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    TEST(iInsertedCount == 2);

    iTrackDatabase->DeleteId(id);
    TEST(iDeletedCount == 2);

    iTrackDatabase->Insert(ITrackDatabase::kTrackIdNone, Brx::Empty(), Brx::Empty(), id);
    iTrackDatabase->DeleteAll();
    TEST(iAllDeletedCount == 2);
}


// SuiteTrackReader

SuiteTrackReader::SuiteTrackReader()
    : SuiteUnitTest("Track database (ITrackDatabaseReader)")
{
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefValidId), "TrackRefValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefInvalidId), "TrackRefInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::NextTrackRefValidId), "NextTrackRefValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::NextTrackRefInvalidId), "NextTrackRefInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::PrevTrackRefValidId), "PrevTrackRefValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::PrevTrackRefInvalidId), "PrevTrackRefInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefByIndexValidId), "TrackRefByIndexValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefByIndexInvalidId), "TrackRefByIndexInvalidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefByIndexSortedValidId), "TrackRefByIndexSortedValidId");
    AddTest(MakeFunctor(*this, &SuiteTrackReader::TrackRefByIndexSortedInvalidId), "TrackRefByIndexSortedInvalidId");
}

void SuiteTrackReader::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, ITrackDatabase::kMaxTracks);
    iDb = new TrackDatabase(*iTrackFactory);
    iReader = static_cast<ITrackDatabaseReader*>(iDb);
    iReader->SetObserver(*this);
    
    ITrackDatabase* writer = static_cast<ITrackDatabase*>(iDb);
    TUint insertAfter = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        writer->Insert(insertAfter, Brx::Empty(), Brx::Empty(), iIds[i]);
        insertAfter = iIds[i];
    }
}

void SuiteTrackReader::TearDown()
{
    delete iDb;
    delete iTrackFactory;
}

void SuiteTrackReader::NotifyTrackInserted(Track& /*aTrack*/, TUint /*aIdBefore*/, TUint /*aIdAfter*/)
{
}

void SuiteTrackReader::NotifyTrackDeleted(TUint /*aId*/, Track* /*aBefore*/, Track* /*aAfter*/)
{
}

void SuiteTrackReader::NotifyAllDeleted()
{
}

void SuiteTrackReader::TrackRefValidId()
{
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->TrackRef(iIds[i]);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
}

void SuiteTrackReader::TrackRefInvalidId()
{
    Track* track = iReader->TrackRef(ITrackDatabase::kTrackIdNone);
    TEST(track == NULL);
    track = iReader->TrackRef(iIds[kNumTracks-1]+1);
    TEST(track == NULL);
}

void SuiteTrackReader::NextTrackRefValidId()
{
    TUint prev = ITrackDatabase::kTrackIdNone;
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->NextTrackRef(prev);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        prev = track->Id();
        track->RemoveRef();
    }
    track = iReader->NextTrackRef(iIds[2]);
    TEST(track == NULL);
}

void SuiteTrackReader::NextTrackRefInvalidId()
{
    Track* track = iReader->NextTrackRef(iIds[kNumTracks-1]+1);
    TEST(track == NULL);
    track = iReader->NextTrackRef(UINT_MAX);
    TEST(track == NULL);
}

void SuiteTrackReader::PrevTrackRefValidId()
{
    TUint next = iIds[kNumTracks-1];
    Track* track;
    for (TUint i=kNumTracks-1; i>0; i--) {
        track = iReader->PrevTrackRef(next);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i-1]);
        next = track->Id();
        track->RemoveRef();
    }
    track = iReader->PrevTrackRef(iIds[0]);
    TEST(track == NULL);
}

void SuiteTrackReader::PrevTrackRefInvalidId()
{
    Track* track = iReader->PrevTrackRef(ITrackDatabase::kTrackIdNone);
    TEST(track == NULL);
    track = iReader->PrevTrackRef(iIds[kNumTracks-1] + 1);
    TEST(track == NULL);
}

void SuiteTrackReader::TrackRefByIndexValidId()
{
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->TrackRefByIndex(i);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
}

void SuiteTrackReader::TrackRefByIndexInvalidId()
{
    Track* track = iReader->TrackRefByIndex(kNumTracks);
    TEST(track == NULL);
}

void SuiteTrackReader::TrackRefByIndexSortedValidId()
{
    TEST_THROWS(iReader->TrackRefByIndexSorted(0), AssertionFailed);
}

void SuiteTrackReader::TrackRefByIndexSortedInvalidId()
{
    TEST_THROWS(iReader->TrackRefByIndexSorted(kNumTracks), AssertionFailed);
}


// SuiteShuffler

SuiteShuffler::SuiteShuffler()
    : SuiteUnitTest("Shuffler")
{
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefShuffleOff), "TrackRefShuffleOff");
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefShuffleOn), "TrackRefShuffleOn");
    AddTest(MakeFunctor(*this, &SuiteShuffler::NextTrackRefShuffleOff), "NextTrackRefShuffleOff");
    AddTest(MakeFunctor(*this, &SuiteShuffler::NextTrackRefShuffleOn), "NextTrackRefShuffleOn");
    AddTest(MakeFunctor(*this, &SuiteShuffler::PrevTrackRefShuffleOff), "PrevTrackRefShuffleOff");
    AddTest(MakeFunctor(*this, &SuiteShuffler::PrevTrackRefShuffleOn), "PrevTrackRefShuffleOn");
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefByIndexShuffleOff), "TrackRefByIndexShuffleOff");
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefByIndexShuffleOn), "TrackRefByIndexShuffleOn");
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefByIndexSortedShuffleOff), "TrackRefByIndexSortedShuffleOff");
    AddTest(MakeFunctor(*this, &SuiteShuffler::TrackRefByIndexSortedShuffleOn), "TrackRefByIndexSortedShuffleOn");
    AddTest(MakeFunctor(*this, &SuiteShuffler::ModeToggleReshuffles), "ModeToggleReshuffles");
    AddTest(MakeFunctor(*this, &SuiteShuffler::NextTrackBeyondEndReshuffles), "NextTrackBeyondEndReshuffles");
}

void SuiteShuffler::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, ITrackDatabase::kMaxTracks);
    iDb = new TrackDatabase(*iTrackFactory);
    iShuffler = new Shuffler(*gEnv, *iDb);
    iReader = static_cast<ITrackDatabaseReader*>(iShuffler);
    iReader->SetObserver(*this);
    
    ITrackDatabase* writer = static_cast<ITrackDatabase*>(iDb);
    TUint insertAfter = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        writer->Insert(insertAfter, Brx::Empty(), Brx::Empty(), iIds[i]);
        insertAfter = iIds[i];
    }
}

void SuiteShuffler::TearDown()
{
    delete iShuffler;
    delete iDb;
    delete iTrackFactory;
}

void SuiteShuffler::NotifyTrackInserted(Track& /*aTrack*/, TUint /*aIdBefore*/, TUint /*aIdAfter*/)
{
}

void SuiteShuffler::NotifyTrackDeleted(TUint /*aId*/, Track* /*aBefore*/, Track* /*aAfter*/)
{
}

void SuiteShuffler::NotifyAllDeleted()
{
}

void SuiteShuffler::TrackRefShuffleOff()
{
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRef(iIds[i]);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
    track = iReader->TrackRef(ITrackDatabase::kTrackIdNone);
    TEST(track == NULL);
    track = iReader->TrackRef(iIds[kNumTracks-1]+1);
    TEST(track == NULL);
}

void SuiteShuffler::TrackRefShuffleOn()
{
    iShuffler->SetShuffle(true);
    // requesting track by id should have identical behaviour with/without shuffle
    TrackRefShuffleOff();
}

void SuiteShuffler::NextTrackRefShuffleOff()
{
    TUint prev = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(prev);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        prev = track->Id();
        track->RemoveRef();
    }
}

void SuiteShuffler::NextTrackRefShuffleOn()
{
    std::array<TUint, kNumTracks> availableIds;
    for (TUint i=0; i<kNumTracks; i++) {
        availableIds[i] = iIds[i];
    }
    std::array<TUint, kNumTracks>::iterator it;
    iShuffler->SetShuffle(true);

    TBool shuffled = false;
    TUint id = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(id);
        TEST(track != NULL);
        id = track->Id();
        if (id != iIds[i]) {
            shuffled = true;
        }
        it = std::find(availableIds.begin(), availableIds.end(), id);
        TEST(it != availableIds.end()); // i.e. check we haven't been given this track before
        *it = ITrackDatabase::kTrackIdNone;
        track->RemoveRef();
    }
    TEST(shuffled);
    int count = std::count_if(availableIds.begin(), availableIds.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 0);
}

void SuiteShuffler::PrevTrackRefShuffleOff()
{
    Track* track;
    TUint id = iIds[kNumTracks-1];
    for (TUint i=kNumTracks-1; i>0; i--) {
        track = iReader->PrevTrackRef(id);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i-1]);
        id = track->Id();
        track->RemoveRef();
    }
    track = iReader->PrevTrackRef(iIds[0]);
    TEST(track == NULL);
    track = iReader->PrevTrackRef(iIds[kNumTracks-1]+1);
    TEST(track == NULL);
}

void SuiteShuffler::PrevTrackRefShuffleOn()
{
    std::array<TUint, kNumTracks> availableIds;
    for (TUint i=0; i<kNumTracks; i++) {
        availableIds[i] = iIds[i];
    }
    std::array<TUint, kNumTracks>::iterator it;
    iShuffler->SetShuffle(true);

    // find id of last shuffled track
    TUint id = iShuffler->iShuffleList[iShuffler->iShuffleList.size()-1]->Id();

    TBool shuffled = false;
    for (TInt i=kNumTracks-1; i>=0; i--) {
        it = std::find(availableIds.begin(), availableIds.end(), id);
        TEST(it != availableIds.end()); // i.e. check we haven't been given this track before
        *it = ITrackDatabase::kTrackIdNone;
        Track* track = iReader->PrevTrackRef(id);
        if (track == NULL) {
            break;
        }
        id = track->Id();
        if (id != iIds[i]) {
            shuffled = true;
        }
        track->RemoveRef();
    }
    TEST(shuffled);
    int count = std::count_if(availableIds.begin(), availableIds.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 0);
}

void SuiteShuffler::TrackRefByIndexShuffleOff()
{
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRefByIndex(i);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
    track = iReader->TrackRefByIndex(kNumTracks+1);
    TEST(track == NULL);
    track = iReader->TrackRefByIndex(UINT_MAX);
    TEST(track == NULL);
}

void SuiteShuffler::TrackRefByIndexShuffleOn()
{
    std::array<TUint, kNumTracks> availableIds;
    for (TUint i=0; i<kNumTracks; i++) {
        availableIds[i] = iIds[i];
    }
    std::array<TUint, kNumTracks>::iterator it;
    iShuffler->SetShuffle(true);
    TBool shuffled = false;

    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->TrackRefByIndex(i);
        TEST(track != NULL);
        if (track->Id() != iIds[i]) {
            shuffled = true;
        }
        it = std::find(availableIds.begin(), availableIds.end(), track->Id());
        TEST(it != availableIds.end()); // i.e. check we haven't been given this track before
        *it = ITrackDatabase::kTrackIdNone;
        track->RemoveRef();
    }
    TEST(!shuffled);
    int count = std::count_if(availableIds.begin(), availableIds.end(), [](TUint aId) {return aId != ITrackDatabase::kTrackIdNone;});
    TEST(count == 0);
}

void SuiteShuffler::TrackRefByIndexSortedShuffleOff()
{
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRefByIndexSorted(i);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
    track = iReader->TrackRefByIndexSorted(kNumTracks+1);
    TEST(track == NULL);
    track = iReader->TrackRefByIndexSorted(UINT_MAX);
    TEST(track == NULL);
}

void SuiteShuffler::TrackRefByIndexSortedShuffleOn()
{
    iShuffler->SetShuffle(true);
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRefByIndexSorted(i);
        TEST(track != NULL);
        TEST(track->Id() == iShuffler->iShuffleList[i]->Id());
        track->RemoveRef();
    }
    track = iReader->TrackRefByIndexSorted(kNumTracks+1);
    TEST(track == NULL);
    track = iReader->TrackRefByIndexSorted(UINT_MAX);
    TEST(track == NULL);
}

void SuiteShuffler::ModeToggleReshuffles()
{
    iShuffler->SetShuffle(true);
    std::array<TUint, kNumTracks> initialShuffle;
    TUint id = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(id);
        id = track->Id();
        initialShuffle[i] = id;
        track->RemoveRef();
    }

    iShuffler->SetShuffle(false);
    iShuffler->SetShuffle(true);
    id = ITrackDatabase::kTrackIdNone;
    TBool reshuffled = false;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(id);
        if (track->Id() != initialShuffle[i]) {
            reshuffled = true;
        }
        track->RemoveRef();
    }
    TEST(reshuffled);
}

void SuiteShuffler::NextTrackBeyondEndReshuffles()
{
    iShuffler->SetShuffle(true);
    std::array<TUint, kNumTracks> initialShuffle;
    TUint id = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(id);
        id = track->Id();
        initialShuffle[i] = id;
        track->RemoveRef();
    }
    TEST(iReader->NextTrackRef(id) == NULL);

    id = ITrackDatabase::kTrackIdNone;
    TBool reshuffled = false;
    for (TUint i=0; i<kNumTracks; i++) {
        Track* track = iReader->NextTrackRef(id);
        if (track->Id() != initialShuffle[i]) {
            reshuffled = true;
        }
        track->RemoveRef();
    }
    TEST(reshuffled);
}


// SuiteRepeater

SuiteRepeater::SuiteRepeater()
    : SuiteUnitTest("Repeater")
{
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefRepeatOff), "TrackRefRepeatOff");
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefRepeatOn), "TrackRefRepeatOn");
    AddTest(MakeFunctor(*this, &SuiteRepeater::NextFromLastTrackRepeatOff), "NextFromLastTrackRepeatOff");
    AddTest(MakeFunctor(*this, &SuiteRepeater::NextFromLastTrackRepeatOn), "NextFromLastTrackRepeatOn");
    AddTest(MakeFunctor(*this, &SuiteRepeater::PrevFromFirstTrackRepeatOff), "PrevFromFirstTrackRepeatOff");
    AddTest(MakeFunctor(*this, &SuiteRepeater::PrevFromFirstTrackRepeatOn), "PrevFromFirstTrackRepeatOn");
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefByIndexRepeatOff), "TrackRefByIndexRepeatOff");
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefByIndexRepeatOn), "TrackRefByIndexRepeatOn");
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefByIndexSortedRepeatOff), "TrackRefByIndexSortedRepeatOff");
    AddTest(MakeFunctor(*this, &SuiteRepeater::TrackRefByIndexSortedRepeatOn), "TrackRefByIndexSortedRepeatOn");
}

void SuiteRepeater::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, ITrackDatabase::kMaxTracks);
    iDb = new TrackDatabase(*iTrackFactory);
    iShuffler = new Shuffler(*gEnv, *iDb);
    iRepeater = new Repeater(*iShuffler);
    iReader = static_cast<ITrackDatabaseReader*>(iRepeater);
    iReader->SetObserver(*this);
    
    ITrackDatabase* writer = static_cast<ITrackDatabase*>(iDb);
    TUint insertAfter = ITrackDatabase::kTrackIdNone;
    for (TUint i=0; i<kNumTracks; i++) {
        writer->Insert(insertAfter, Brx::Empty(), Brx::Empty(), iIds[i]);
        insertAfter = iIds[i];
    }
}

void SuiteRepeater::TearDown()
{
    delete iRepeater;
    delete iShuffler;
    delete iDb;
    delete iTrackFactory;
}

void SuiteRepeater::NotifyTrackInserted(Track& /*aTrack*/, TUint /*aIdBefore*/, TUint /*aIdAfter*/)
{
}

void SuiteRepeater::NotifyTrackDeleted(TUint /*aId*/, Track* /*aBefore*/, Track* /*aAfter*/)
{
}

void SuiteRepeater::NotifyAllDeleted()
{
}

void SuiteRepeater::TrackRefRepeatOff()
{
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRef(iIds[i]);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
    track = iReader->TrackRef(ITrackDatabase::kTrackIdNone);
    TEST(track == NULL);
    track = iReader->TrackRef(iIds[kNumTracks-1]+1);
    TEST(track == NULL);
}

void SuiteRepeater::TrackRefRepeatOn()
{
    static_cast<IRepeater*>(iRepeater)->SetRepeat(true);
    // requesting track by id should have identical behaviour with/without repeat
    TrackRefRepeatOff();
}

void SuiteRepeater::NextFromLastTrackRepeatOff()
{
    Track* track = iReader->NextTrackRef(iIds[kNumTracks-1]);
    TEST(track == NULL);
}

void SuiteRepeater::NextFromLastTrackRepeatOn()
{
    static_cast<IRepeater*>(iRepeater)->SetRepeat(true);
    Track* track = iReader->NextTrackRef(iIds[kNumTracks-1]);
    TEST(track != NULL);
    TEST(track->Id() == iIds[0]);
    track->RemoveRef();
}

void SuiteRepeater::PrevFromFirstTrackRepeatOff()
{
    Track* track = iReader->PrevTrackRef(iIds[0]);
    TEST(track == NULL);
}

void SuiteRepeater::PrevFromFirstTrackRepeatOn()
{
    static_cast<IRepeater*>(iRepeater)->SetRepeat(true);
    Track* track = iReader->PrevTrackRef(iIds[0]);
    TEST(track != NULL);
    TEST(track->Id() == iIds[kNumTracks-1]);
    track->RemoveRef();
}

void SuiteRepeater::TrackRefByIndexRepeatOff()
{
    Track* track;
    for (TUint i=0; i<kNumTracks; i++) {
        track = iReader->TrackRefByIndex(i);
        TEST(track != NULL);
        TEST(track->Id() == iIds[i]);
        track->RemoveRef();
    }
    track = iReader->TrackRefByIndex(kNumTracks);
    TEST(track == NULL);
}

void SuiteRepeater::TrackRefByIndexRepeatOn()
{
    static_cast<IRepeater*>(iRepeater)->SetRepeat(true);
    // requesting track by index should have identical behaviour with/without repeat
    TrackRefByIndexRepeatOff();
}

void SuiteRepeater::TrackRefByIndexSortedRepeatOff()
{
    TEST_THROWS(iReader->TrackRefByIndexSorted(0), AssertionFailed);
}

void SuiteRepeater::TrackRefByIndexSortedRepeatOn()
{
    static_cast<IRepeater*>(iRepeater)->SetRepeat(true);
    TEST_THROWS(iReader->TrackRefByIndexSorted(kNumTracks), AssertionFailed);
}



void TestTrackDatabase()
{
    Runner runner("Track database tests\n");
    // FIXME - Suite to validate assumptions about std::vector implementation (maybe only reserve behaviour?)
    runner.Add(new SuiteTrackDatabase());
    runner.Add(new SuiteTrackReader());
    runner.Add(new SuiteShuffler());
    runner.Add(new SuiteRepeater());
    runner.Run();
}
