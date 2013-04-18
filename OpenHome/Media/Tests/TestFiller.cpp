#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>

#include <vector>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {
namespace TestFiller {

class DummyUriProvider : public UriProvider
{
public:
    DummyUriProvider();
    ~DummyUriProvider();
    const Brx& TrackUriByIndex(TUint aIndex) const;
    const Brx& ProviderIdByIndex(TUint aIndex) const;
private: // from UriProvider
    void Begin(const Brx& aProviderId);
    EStreamPlay GetNext(Track*& aTrack);
    EStreamPlay GetPrev(Track*& aTrack);
private:
    static const TInt kNumEntries = 3;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    Track* iTracks[kNumEntries];
    TInt iIndex;
};

class DummyUriStreamer : public IUriStreamer, private IStreamHandler, private INonCopyable
{
public:
    DummyUriStreamer(ISupply& aSupply, Semaphore& aTrackAddedSem, Semaphore& aTrackCompleteSem);
    virtual ~DummyUriStreamer();
    TUint TrackId() const;
    TUint StreamId() const;
private: // from IUriStreamer
    TBool DoStream(Track& aTrack);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    ISupply& iSupply;
    Semaphore& iTrackAddedSem;
    Semaphore& iTrackCompleteSem;
    TUint iTrackId;
    TUint iStreamId;
};

class DummySupply : public ISupply
{
public:
    DummySupply();
    ~DummySupply();
    const Brx& LastTrackUri() const;
    TUint LastTrackId() const;
    TUint LastStreamId() const;
private: // from ISupply
    void OutputTrack(Track& aTrack, TUint aTrackId);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputQuit();
private:
    BwsTrackUri iLastTrackUri;
    TUint iLastTrackId;
    TUint iLastStreamId;
};

class SuiteFiller : public Suite, private IPipelineIdTracker
{
public:
    SuiteFiller();
    ~SuiteFiller();
private: // from Suite
    void Test();
private: // from IPipelineIdTracker
    void AddStream(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow);
private:
    Semaphore iTrackAddedSem;
    Semaphore iTrackCompleteSem;
    Filler* iFiller;
    DummyUriProvider* iUriProvider;
    DummyUriStreamer* iUriStreamer;
    DummySupply* iDummySupply;
    BwsStyle iStyle;
    BwsProviderId iProviderId;
    TUint iTrackId;
    TUint iStreamId;
    TBool iPlayNow;
};

} // namespace TestFiller
} // namespace Media
} // namespace OpenHome

using namespace OpenHome::Media::TestFiller;

// DummyUriProvider

DummyUriProvider::DummyUriProvider()
    : UriProvider("Dummy")
    , iIndex(-1)
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 3);
    iTracks[0] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file1"), Brx::Empty(), Style(), Brn("1"), 0);
    iTracks[1] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file2"), Brx::Empty(), Style(), Brn("2"), 0);
    iTracks[2] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file3"), Brx::Empty(), Style(), Brn("3"), 0);
}

DummyUriProvider::~DummyUriProvider()
{
    iTracks[0]->RemoveRef();
    iTracks[1]->RemoveRef();
    iTracks[2]->RemoveRef();
    delete iTrackFactory;
}

const Brx& DummyUriProvider::TrackUriByIndex(TUint aIndex) const
{
    return iTracks[aIndex]->Uri();
}

const Brx& DummyUriProvider::ProviderIdByIndex(TUint aIndex) const
{
    return iTracks[aIndex]->ProviderId();
}

void DummyUriProvider::Begin(const Brx& aProviderId)
{
    TInt index = 0;
    while (index < kNumEntries && iTracks[index]->ProviderId() != aProviderId) {
        index++;
    }
    if (index == kNumEntries) {
        THROW(UriProviderInvalidId);
    }
    iIndex = index-1;
}

EStreamPlay DummyUriProvider::GetNext(Track*& aTrack)
{
    const TBool firstCall = (iIndex<0);
    if (++iIndex == kNumEntries) {
        iIndex = 0;
    }
    aTrack = iTracks[iIndex];
    aTrack->AddRef();
    return (!firstCall && iIndex == 0? ePlayLater : ePlayYes);
}

EStreamPlay DummyUriProvider::GetPrev(Track*& aTrack)
{
    const TBool firstCall = (iIndex<0);
    if (--iIndex < 0) {
        iIndex = kNumEntries - 1;
    }
    aTrack = iTracks[iIndex];
    aTrack->AddRef();
    return (!firstCall && iIndex == kNumEntries - 1? ePlayLater : ePlayYes);
}


// DummyUriStreamer

DummyUriStreamer::DummyUriStreamer(ISupply& aSupply, Semaphore& aTrackAddedSem, Semaphore& aTrackCompleteSem)
    : iSupply(aSupply)
    , iTrackAddedSem(aTrackAddedSem)
    , iTrackCompleteSem(aTrackCompleteSem)
    , iTrackId(0)
    , iStreamId(0)
{
}

DummyUriStreamer::~DummyUriStreamer()
{
    iSupply.OutputQuit();
}

TUint DummyUriStreamer::TrackId() const
{
    return iTrackId;
}

TUint DummyUriStreamer::StreamId() const
{
    return iStreamId;
}

TBool DummyUriStreamer::DoStream(Track& aTrack)
{
    iTrackId++;
    iStreamId++;
    iSupply.OutputTrack(aTrack, iTrackId);
    iSupply.OutputStream(aTrack.Uri(), 1LL, false, false, *this, iStreamId);
    iTrackAddedSem.Signal();
    iTrackCompleteSem.Wait();
    return true;
}

EStreamPlay DummyUriStreamer::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint DummyUriStreamer::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DummyUriStreamer::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}


// DummySupply

DummySupply::DummySupply()
{
}

DummySupply::~DummySupply()
{
}

const Brx& DummySupply::LastTrackUri() const
{
    return iLastTrackUri;
}

TUint DummySupply::LastTrackId() const
{
    return iLastTrackId;
}

TUint DummySupply::LastStreamId() const
{
    return iLastStreamId;
}

void DummySupply::OutputTrack(Track& aTrack, TUint aTrackId)
{
    iLastTrackUri.Replace(aTrack.Uri());
    iLastTrackId = aTrackId;
}

void DummySupply::OutputStream(const Brx& /*aUri*/, TUint64 /*aTotalBytes*/, TBool /*aSeekable*/, TBool /*aLive*/, IStreamHandler& /*aStreamHandler*/, TUint aStreamId)
{
    iLastStreamId = aStreamId;
}

void DummySupply::OutputData(const Brx& /*aData*/)
{
    ASSERTS();
}

void DummySupply::OutputMetadata(const Brx& /*aMetadata*/)
{
    ASSERTS();
}

void DummySupply::OutputFlush(TUint /*aFlushId*/)
{
    ASSERTS();
}

void DummySupply::OutputQuit()
{
}


// SuiteFiller

SuiteFiller::SuiteFiller()
    : Suite("Trivial Filler tests")
    , iTrackAddedSem("TASM", 0)
    , iTrackCompleteSem("TCSM", 0)
{
    iDummySupply = new DummySupply();
    iFiller = new Filler(*iDummySupply, *this);
    iUriProvider = new DummyUriProvider();
    iUriStreamer = new DummyUriStreamer(*iFiller, iTrackAddedSem, iTrackCompleteSem);
    iFiller->Add(*iUriProvider);
    iFiller->Start(*iUriStreamer);
}

SuiteFiller::~SuiteFiller()
{
    delete iUriStreamer;
    delete iFiller;
    delete iUriProvider;
    delete iDummySupply;
}

void SuiteFiller::Test()
{
    // Play for invalid style should throw
    TEST_THROWS(iFiller->Play(Brn("NotARealStyle"), Brn("1")), FillerInvalidStyle);

    // Play for valid style but invalid providerId should throw
    TEST_THROWS(iFiller->Play(iUriProvider->Style(), Brn("NoARealProviderId")), UriProviderInvalidId);

    // Play for valid style/providerId should succeed and Begin should be called
    // IUriStreamer should be passed uri for first track
    iFiller->Play(iUriProvider->Style(), iUriProvider->ProviderIdByIndex(0));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(0));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(0));
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    TUint trackId = iTrackId;
    BwsProviderId providerId(iProviderId);

    // When first track completes, IUriStreamer should be passed uri for second track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(1));
    TEST(iProviderId != providerId);
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;
    providerId.Replace(iProviderId);

    // Stop/Next during second track.  Once track completes IUriStreamer should be passed uri for third track
    iFiller->Stop();
    iTrackCompleteSem.Signal();
    iFiller->Next();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(2));
    TEST(iProviderId != providerId);
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;
    providerId.Replace(iProviderId);

    // Stop/Prev during third track.  Once track completes IUriStreamer should be passed uri for second track
    iFiller->Stop();
    iTrackCompleteSem.Signal();
    iFiller->Prev();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(1));
    TEST(iProviderId != providerId);
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;
    providerId.Replace(iProviderId);

    // Once track completes, IUriStreamer should (again) be passed uri for third track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(2));
    TEST(iProviderId != providerId);
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;
    providerId.Replace(iProviderId);

    // Once track completes, dummy UriProvider will return first track to be played later.  IUriStreamer should not be passed anything
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iStyle == iUriProvider->Style());
    TEST(iProviderId == iUriProvider->ProviderIdByIndex(0));
    TEST(iProviderId != providerId);
    TEST(iTrackId == iDummySupply->LastTrackId());
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(!iPlayNow);
    iFiller->Stop();
    iTrackCompleteSem.Signal();
}

void SuiteFiller::AddStream(const Brx& aStyle, const Brx& aProviderId, TUint aTrackId, TUint aStreamId, TBool aPlayNow)
{
    iStyle.Replace(aStyle);
    iProviderId.Replace(aProviderId);
    iTrackId = aTrackId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
}



void TestFiller()
{
    Runner runner("Basic Filler tests\n");
    runner.Add(new SuiteFiller());
    runner.Run();
}
