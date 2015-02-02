#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/IdManager.h>
#include <OpenHome/Private/SuiteUnitTest.h>

#include <vector>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteIdsAreUnique : public Suite, private IStopper
{
public:
    SuiteIdsAreUnique();
    ~SuiteIdsAreUnique();
    void Test();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private:
    IdManager* iIdManager;
};

class SuiteSingleStream : public SuiteUnitTest, private IStopper
{
    static const Brn kMode;
    static const TUint kTrackId = 100;
    static const TUint kStreamId = 0;
public:
    SuiteSingleStream();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void OkToPlayOnceForValidId();
    void OkToPlayForInvalidId();
    void InvalidateAtMatch();
    void InvalidateAtNoMatch();
    void InvalidateAfterMatch();
    void InvalidateAfterNoMatch();
private:
    IdManager* iIdManager;
    IPipelineIdProvider* iIdProvider;
};

class SuitePlayLater : public Suite, private IStopper
{
public:
    SuitePlayLater();
    ~SuitePlayLater();
    void Test();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
};

class SuiteMaxStreams : public Suite, private IStopper
{
    static const Brn kMode;
    static const TUint kTrackId = 200;
    static const TUint kStreamId = 0;
public:
    SuiteMaxStreams();
    ~SuiteMaxStreams();
    void Test();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
};

class SuiteMultiStreams : public SuiteUnitTest, private IStopper
{
    static const Brn kMode;
    static const TUint kTrackId1 = 300;
    static const TUint kTrackId2 = 301;
    static const TUint kTrackId3 = 302;
    static const TUint kStreamId1 = 1;
    static const TUint kStreamId2 = 2;
    static const TUint kStreamId3 = 3;
    static const TUint kStreamId4 = 4;
    static const TUint kIdInvalid = 999;
public:
    SuiteMultiStreams();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void AllCanBePlayed();
    void FirstPlaysIncorrectCallsThenPlayAll();
    void FirstPlaysThenInvalidated();
    void FirstPlaysThenInvalidateAfter();
    void FirstPlaysThenInvalidateThird();
    void FirstPlaysThenInvalidateAfterThird();
    void SecondPlaysThenInvalidated();
    void SecondPlaysThenInvalidateAfter();
    void InvalidateAtWithInvalidProviderId();
    void InvalidatePending();
    void InvalidateAll();
private:
    IdManager* iIdManager;
    IPipelineIdProvider* iIdProvider;
    TUint iRemoveStreamId;
};

} // namespace Media
} // namespace OpenHome

/* Test cases are
Create Id provider
    check that NextTrackId returns vary
    check that NextStreamId returns vary
Create Id provider, add 1 element
    check it can be OkToPlay'd; check another OkToPlay fails
    call InvalidateAt for element, check OkToPlay fails
    call InvalidateAt for no element, check OkToPlay succeeds
    call InvalidateAfter for element, check OkToPlay succeeds
    call InvalidateAfter for no element, check OkToPlay succeeds
Create Id provider, add max elements
    check each can be OkToPlay'd, check second attempt at initial element fails
Create Id provider, add 3 elements (2 streams in first track, 1 in second track)
    check all can be OkToPlay'd
    check first can be OkToPlay'd, correct track and incorrect stream fails
                                   incorrect track and correct stream fails
                                   incorrect track and incorrect stream fails
                                   second can be OkToPlay'd, third can be OkToPlay'd, fourth OkToPlay fails
    check first can be OkToPlay'd, call InvalidateAt for first, check Stopper is called and OkToPlay for second fails, third succeeds
    check first can be OkToPlay'd, call InvalidateAfter for first, check OkToPlay for second, third fails
    check first can be OkToPlay'd, call InvalidateAt for second, check OkToPlay for third succeeds
    check first can be OkToPlay'd, call InvalidateAfter for second, check OkToPlay for third fails
    play first then second, call InvalidateAt for second, check Stopper is called and OkToPlay for third, fourth succeeds
    play first then second, call InvalidateAfter for second, check OkToPlay for third, fourth fails
    check first can be OkToPlay'd, call InvalidateAt for first with incorrect style, check OkToPlay for second succeeds
    check first can be OkToPlay'd, call InvalidateAt for first with incorrect providerId, check OkToPlay for second succeeds
*/

// SuiteIdsAreUnique

SuiteIdsAreUnique::SuiteIdsAreUnique()
    : Suite("Ids are unique")
{
    iIdManager = new IdManager(*this);
}

SuiteIdsAreUnique::~SuiteIdsAreUnique()
{
    delete iIdManager;
}

void SuiteIdsAreUnique::Test()
{
    static const TUint kTestIterations = 10;
    std::vector<TUint> ids;
    IPipelineIdProvider* idProvider = static_cast<IPipelineIdProvider*>(iIdManager);
    for (TUint i=0; i<kTestIterations; i++) {
        TUint trackId = idProvider->NextTrackId();
        TEST(std::find(ids.begin(), ids.end(), trackId) == ids.end());
        ids.push_back(trackId);
    }
    ids.clear();
    for (TUint i=0; i<kTestIterations; i++) {
        TUint streamId = idProvider->NextTrackId();
        TEST(std::find(ids.begin(), ids.end(), streamId) == ids.end());
        ids.push_back(streamId);
    }
}

void SuiteIdsAreUnique::RemoveStream(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
}


// SuiteSingleStream

const Brn SuiteSingleStream::kMode("TestMode");

SuiteSingleStream::SuiteSingleStream()
    : SuiteUnitTest("Single active stream")
{
    AddTest(MakeFunctor(*this, &SuiteSingleStream::OkToPlayOnceForValidId));
    AddTest(MakeFunctor(*this, &SuiteSingleStream::OkToPlayForInvalidId));
    AddTest(MakeFunctor(*this, &SuiteSingleStream::InvalidateAtMatch));
    AddTest(MakeFunctor(*this, &SuiteSingleStream::InvalidateAtNoMatch));
    AddTest(MakeFunctor(*this, &SuiteSingleStream::InvalidateAfterMatch));
    AddTest(MakeFunctor(*this, &SuiteSingleStream::InvalidateAfterNoMatch));
}

void SuiteSingleStream::RemoveStream(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
}

void SuiteSingleStream::Setup()
{
    iIdManager = new IdManager(*this);
    iIdManager->AddStream(kTrackId, kStreamId, true);
    iIdProvider = static_cast<IPipelineIdProvider*>(iIdManager);
}

void SuiteSingleStream::TearDown()
{
    delete iIdManager;
    iIdManager = NULL;
    iIdProvider = NULL;
}

void SuiteSingleStream::OkToPlayOnceForValidId()
{
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayYes);
    // check we don't get permission to play the same track twice
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayNo);
}

void SuiteSingleStream::OkToPlayForInvalidId()
{
    TEST(iIdProvider->OkToPlay(kStreamId+1) == ePlayNo);
    // check that previous failures don't prevent us from playing the next track
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayYes);
}

void SuiteSingleStream::InvalidateAtMatch()
{
    iIdManager->InvalidateAt(kTrackId);
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayNo);
}

void SuiteSingleStream::InvalidateAtNoMatch()
{
    iIdManager->InvalidateAt(999);
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayYes);
}

void SuiteSingleStream::InvalidateAfterMatch()
{
    iIdManager->InvalidateAfter(kTrackId);
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayYes);
}

void SuiteSingleStream::InvalidateAfterNoMatch()
{
    iIdManager->InvalidateAfter(999);
    TEST(iIdProvider->OkToPlay(kStreamId) == ePlayYes);
}


// SuitePlayLater

SuitePlayLater::SuitePlayLater()
    : Suite("Play later")
{
}

SuitePlayLater::~SuitePlayLater()
{
}

void SuitePlayLater::Test()
{
    const TUint trackId = 4;
    const TUint streamId = 0;
    IdManager* pipelineIdProvider = new IdManager(*this);
    pipelineIdProvider->AddStream(trackId, streamId, false);
    TEST(static_cast<IPipelineIdProvider*>(pipelineIdProvider)->OkToPlay(streamId) == ePlayLater);
    delete pipelineIdProvider;
}

void SuitePlayLater::RemoveStream(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
}


// SuiteMaxStreams

const Brn SuiteMaxStreams::kMode("TestMode");

SuiteMaxStreams::SuiteMaxStreams()
    : Suite("Max active streams")
{
}

SuiteMaxStreams::~SuiteMaxStreams()
{
}

void SuiteMaxStreams::Test()
{
    // fill idProvider
    // check each can be OkToPlay'd, check second attempt at initial element fails
    // add another stream, check OkToPlay for it succeeds (so the buffer indices can wrap)

    IdManager* pipelineIdProvider = new IdManager(*this);
    const TUint max = pipelineIdProvider->MaxStreams()-1;
    for (TUint streamId = kStreamId; streamId<max; streamId++) {
        pipelineIdProvider->AddStream(kTrackId, streamId, true);
    }
    IPipelineIdProvider* idProvider = static_cast<IPipelineIdProvider*>(pipelineIdProvider);
    for (TUint streamId = kStreamId; streamId<max; streamId++) {
        TEST(idProvider->OkToPlay(streamId) == ePlayYes);
    }
    TEST(idProvider->OkToPlay(kStreamId) == ePlayNo);

    pipelineIdProvider->AddStream(kTrackId, kStreamId, true);
    pipelineIdProvider->AddStream(kTrackId, kStreamId+1, true);
    pipelineIdProvider->AddStream(kTrackId, kStreamId+2, true);
    TEST(idProvider->OkToPlay(kStreamId) == ePlayYes);
    TEST(idProvider->OkToPlay(kStreamId+1) == ePlayYes);
    TEST(idProvider->OkToPlay(kStreamId+2) == ePlayYes);

    delete pipelineIdProvider;
}

void SuiteMaxStreams::RemoveStream(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
}


// SuiteMultiStreams

const Brn SuiteMultiStreams::kMode("TestMode");

SuiteMultiStreams::SuiteMultiStreams()
    : SuiteUnitTest("Multiple active streams")
{
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::AllCanBePlayed));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::FirstPlaysIncorrectCallsThenPlayAll));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::FirstPlaysThenInvalidated));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::FirstPlaysThenInvalidateAfter));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::FirstPlaysThenInvalidateThird));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::FirstPlaysThenInvalidateAfterThird));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::SecondPlaysThenInvalidated));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::SecondPlaysThenInvalidateAfter));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::InvalidateAtWithInvalidProviderId));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::InvalidatePending));
    AddTest(MakeFunctor(*this, &SuiteMultiStreams::InvalidateAll));
}

void SuiteMultiStreams::RemoveStream(TUint /*aTrackId*/, TUint aStreamId)
{
    iRemoveStreamId = aStreamId;
}

void SuiteMultiStreams::Setup()
{
    iIdManager = new IdManager(*this);
    iIdManager->AddStream(kTrackId1, kStreamId1, true);
    iIdManager->AddStream(kTrackId1, kStreamId2, true);
    iIdManager->AddStream(kTrackId2, kStreamId3, true);
    iIdManager->AddStream(kTrackId3, kStreamId4, true);
    iIdProvider = static_cast<IPipelineIdProvider*>(iIdManager);
    iRemoveStreamId = kIdInvalid;
}

void SuiteMultiStreams::TearDown()
{
    delete iIdManager;
    iIdManager = NULL;
    iIdProvider = NULL;
}

void SuiteMultiStreams::AllCanBePlayed()
{
    // check all can be OkToPlay'd
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::FirstPlaysIncorrectCallsThenPlayAll()
{
    /* check first can be OkToPlay'd, correct track and incorrect stream fails
            incorrect track and correct stream fails
            incorrect track and incorrect stream fails
            second can be OkToPlay'd, third can be OkToPlay'd, fourth OkToPlay fails */
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kIdInvalid) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::FirstPlaysThenInvalidated()
{
    // check first can be OkToPlay'd, call InvalidateAt for first, check Stopper is called and OkToPlay for second fails, third + fourth succeed
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAt(kTrackId1);
    TEST(iRemoveStreamId == kStreamId1);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::FirstPlaysThenInvalidateAfter()
{
    // check first can be OkToPlay'd, call InvalidateAfter for first, check OkToPlay for second succeeds, third/fourth fails
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAfter(kTrackId1);
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayNo);
}

void SuiteMultiStreams::FirstPlaysThenInvalidateThird()
{
    // check first can be OkToPlay'd, call InvalidateAt for third, check OkToPlay for second succeeds, third fails, fourth succeeds
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAt(kTrackId2);
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::FirstPlaysThenInvalidateAfterThird()
{
    // check first can be OkToPlay'd, call InvalidateAfter for third, check OkToPlay for second/third succeeds, fourth fails
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAfter(kTrackId2);
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayNo);
}

void SuiteMultiStreams::SecondPlaysThenInvalidated()
{
    // play first then second, call InvalidateAt for second, check Stopper is called and OkToPlay for third, fourth succeeds
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    iIdManager->InvalidateAt(kTrackId1);
    TEST(iRemoveStreamId == kStreamId2);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::SecondPlaysThenInvalidateAfter()
{
    // play first then second, call InvalidateAfter for second, check OkToPlay for third, fourth fails
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    iIdManager->InvalidateAfter(kTrackId1);
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayNo);
}

void SuiteMultiStreams::InvalidateAtWithInvalidProviderId()
{
    // check first can be OkToPlay'd, call InvalidateAt for first with incorrect providerId, check OkToPlay for second etc succeeds
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAfter(999);
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayYes);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayYes);
}

void SuiteMultiStreams::InvalidatePending()
{
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidatePending();
    TEST(iRemoveStreamId == kIdInvalid);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayNo);
}

void SuiteMultiStreams::InvalidateAll()
{
    TEST(iIdProvider->OkToPlay(kStreamId1) == ePlayYes);
    iIdManager->InvalidateAll();
    TEST(iRemoveStreamId == kStreamId1);
    TEST(iIdProvider->OkToPlay(kStreamId2) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId3) == ePlayNo);
    TEST(iIdProvider->OkToPlay(kStreamId4) == ePlayNo);
}



void TestIdProvider()
{
    Runner runner("Basic IdProvider tests\n");
    runner.Add(new SuiteIdsAreUnique());
    runner.Add(new SuiteSingleStream());
    runner.Add(new SuitePlayLater());
    runner.Add(new SuiteMaxStreams());
    runner.Add(new SuiteMultiStreams());
    runner.Run();
}
