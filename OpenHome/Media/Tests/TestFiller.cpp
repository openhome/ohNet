#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Av/InfoProvider.h>
#include "AllocatorInfoLogger.h"
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>

#include <limits.h>
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
    TUint IdByIndex(TUint aIndex) const;
private: // from UriProvider
    void Begin(TUint aTrackId);
    EStreamPlay GetNext(Track*& aTrack);
    TUint CurrentTrackId() const;
    TBool MoveNext();
    TBool MovePrevious();
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
    TBool DoStream(Track& aTrack, const Brx& aMode);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    ISupply& iSupply;
    Semaphore& iTrackAddedSem;
    Semaphore& iTrackCompleteSem;
    TUint iPipelineTrackId;
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
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
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
    void AddStream(TUint aId, TUint aPipelineTrackId, TUint aStreamId, TBool aPlayNow);
private:
    Semaphore iTrackAddedSem;
    Semaphore iTrackCompleteSem;
    Filler* iFiller;
    DummyUriProvider* iUriProvider;
    DummyUriStreamer* iUriStreamer;
    DummySupply* iDummySupply;
    TUint iTrackId;
    TUint iPipelineTrackId;
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
    iTracks[0] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file1"), Brx::Empty(), NULL);
    iTracks[1] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file2"), Brx::Empty(), NULL);
    iTracks[2] = iTrackFactory->CreateTrack(Brn("http://addr:port/path/file3"), Brx::Empty(), NULL);
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

TUint DummyUriProvider::IdByIndex(TUint aIndex) const
{
    return iTracks[aIndex]->Id();
}

void DummyUriProvider::Begin(TUint aTrackId)
{
    TInt index = 0;
    while (index < kNumEntries && iTracks[index]->Id() != aTrackId) {
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

TUint DummyUriProvider::CurrentTrackId() const
{
    return iTracks[iIndex]->Id();
}

TBool DummyUriProvider::MoveNext()
{
    if (++iIndex == kNumEntries) {
        iIndex = 0;
    }
    return true;
}

TBool DummyUriProvider::MovePrevious()
{
    if (--iIndex < 0) {
        iIndex = kNumEntries-1;
    }
    return true;
}


// DummyUriStreamer

DummyUriStreamer::DummyUriStreamer(ISupply& aSupply, Semaphore& aTrackAddedSem, Semaphore& aTrackCompleteSem)
    : iSupply(aSupply)
    , iTrackAddedSem(aTrackAddedSem)
    , iTrackCompleteSem(aTrackCompleteSem)
    , iPipelineTrackId(0)
    , iStreamId(0)
{
}

DummyUriStreamer::~DummyUriStreamer()
{
    iSupply.OutputQuit();
}

TUint DummyUriStreamer::TrackId() const
{
    return iPipelineTrackId;
}

TUint DummyUriStreamer::StreamId() const
{
    return iStreamId;
}

TBool DummyUriStreamer::DoStream(Track& aTrack, const Brx& aMode)
{
    iPipelineTrackId++;
    iStreamId++;
    iSupply.OutputTrack(aTrack, iPipelineTrackId, aMode);
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

void DummySupply::OutputTrack(Track& aTrack, TUint aTrackId, const Brx& /*aMode*/)
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
    // Play for invalid mode should throw
    TEST_THROWS(iFiller->Play(Brn("NotARealMode"), 1), FillerInvalidMode);

    // Play for valid mode but invalid trackId should throw
    TEST_THROWS(iFiller->Play(iUriProvider->Mode(), UINT_MAX), UriProviderInvalidId);

    // Play for valid mode/trackId should succeed and Begin should be called
    // IUriStreamer should be passed uri for first track
    iFiller->Play(iUriProvider->Mode(), iUriProvider->IdByIndex(0));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(0));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(0));
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    TUint pipelineTrackId = iPipelineTrackId;
    TUint trackId = iTrackId;

    // When first track completes, IUriStreamer should be passed uri for second track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(1));
    TEST(iTrackId != trackId);
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iPipelineTrackId != pipelineTrackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    pipelineTrackId = iPipelineTrackId;
    trackId = iTrackId;

    // Stop/Next during second track.  Once track completes IUriStreamer should be passed uri for third track
    iFiller->Stop();
    iTrackCompleteSem.Signal();
    // test for invalid Next() arg
    TEST(iFiller->Next(Brn("InvalidMode")));
    //
    TEST(iFiller->Next(iUriProvider->Mode()));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(2));
    TEST(iTrackId != trackId);
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iPipelineTrackId != pipelineTrackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    pipelineTrackId = iPipelineTrackId;
    trackId = iTrackId;

    // Stop/Prev during third track.  Once track completes IUriStreamer should be passed uri for second track
    iFiller->Stop();
    iTrackCompleteSem.Signal();
    TEST(iFiller->Prev(iUriProvider->Mode()));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(1));
    TEST(iTrackId != trackId);
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iPipelineTrackId != pipelineTrackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    pipelineTrackId = iPipelineTrackId;
    trackId = iTrackId;

    // Once track completes, IUriStreamer should (again) be passed uri for third track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(2));
    TEST(iTrackId != trackId);
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iPipelineTrackId != pipelineTrackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    pipelineTrackId = iPipelineTrackId;
    trackId = iTrackId;

    // Once track completes, dummy UriProvider will return first track to be played later.  IUriStreamer should not be passed anything
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iTrackId == iUriProvider->IdByIndex(0));
    TEST(iTrackId != trackId);
    TEST(iPipelineTrackId == iDummySupply->LastTrackId());
    TEST(iPipelineTrackId != pipelineTrackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(!iPlayNow);
    iFiller->Stop();
    iTrackCompleteSem.Signal();
}

void SuiteFiller::AddStream(TUint aId, TUint aPipelineTrackId, TUint aStreamId, TBool aPlayNow)
{
    iTrackId = aId;
    iPipelineTrackId = aPipelineTrackId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
}



void TestFiller()
{
    Runner runner("Basic Filler tests\n");
    runner.Add(new SuiteFiller());
    runner.Run();
}
