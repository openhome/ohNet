#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Filler.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Supply.h>

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
    DummyUriProvider(TrackFactory& aTrackFactory);
    ~DummyUriProvider();
    const Brx& TrackUriByIndex(TUint aIndex) const;
    TUint IdByIndex(TUint aIndex) const;
private: // from UriProvider
    void Begin(TUint aTrackId) override;
    void BeginLater(TUint aTrackId) override;
    EStreamPlay GetNext(Track*& aTrack) override;
    TUint CurrentTrackId() const override;
    TBool MoveNext() override;
    TBool MovePrevious() override;
private:
    static const TInt kNumEntries = 3;
    TrackFactory& iTrackFactory;
    Track* iTracks[kNumEntries];
    TInt iIndex;
    TInt iPendingIndex;
};

class DummyUriStreamer : public IUriStreamer, private IStreamHandler, private INonCopyable
{
public:
    DummyUriStreamer(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement, Semaphore& aTrackAddedSem, Semaphore& aTrackCompleteSem);
    virtual ~DummyUriStreamer();
    TUint TrackId() const;
    TUint StreamId() const;
private: // from IUriStreamer
    ProtocolStreamResult DoStream(Track& aTrack) override;
    void Interrupt(TBool aInterrupt) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    Supply iSupply;
    Semaphore& iTrackAddedSem;
    Semaphore& iTrackCompleteSem;
    TUint iTrackId;
    TUint iStreamId;
};

class DummySupply : public IPipelineElementDownstream, private IMsgProcessor
{
public:
    DummySupply();
    ~DummySupply();
    const Brx& LastTrackUri() const;
    TUint LastTrackId() const;
    TUint LastStreamId() const;
    const Brx& LastMode() const;
    TBool LastSupportsLatency() const;
    TBool LastIsRealTime() const;
    TUint LastDelayJiffies() const;
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    BwsMode iLastMode;
    TBool iLastSupportsLatency;
    TBool iLastRealTime;
    BwsTrackUri iLastTrackUri;
    TUint iLastTrackId;
    TUint iLastStreamId;
    TUint iLastDelayJiffies;
};

class SuiteFiller : public Suite, private IPipelineIdTracker, private IFlushIdProvider, private IStreamPlayObserver, private IPipelineIdProvider
{
    static const TUint kDefaultLatency = Jiffies::kPerMs * 150;
public:
    SuiteFiller();
    ~SuiteFiller();
private: // from Suite
    void Test() override;
private: // from IPipelineIdTracker
    void AddStream(TUint aId, TUint aStreamId, TBool aPlayNow) override;
private: // from IFlushIdProvider
    TUint NextFlushId() override;
private: // from IStreamPlayObserver
    void NotifyTrackFailed(TUint aTrackId) override;
    void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus) override;
private: // from IPipelineIdProvider
    TUint NextStreamId() override;
    EStreamPlay OkToPlay(TUint aStreamId) override;
private:
    Semaphore iTrackAddedSem;
    Semaphore iTrackCompleteSem;
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Filler* iFiller;
    DummyUriProvider* iUriProvider;
    DummyUriStreamer* iUriStreamer;
    DummySupply* iDummySupply;
    TUint iTrackId;
    TUint iStreamId;
    TBool iPlayNow;
    TUint iNextFlushId;
};

} // namespace TestFiller
} // namespace Media
} // namespace OpenHome

using namespace OpenHome::Media::TestFiller;

// DummyUriProvider

DummyUriProvider::DummyUriProvider(TrackFactory& aTrackFactory)
    : UriProvider("Dummy", LatencyNotSupported, RealTimeNotSupported, NextNotSupported, PrevNotSupported)
    , iTrackFactory(aTrackFactory)
    , iIndex(-1)
    , iPendingIndex(-1)
{
    iTracks[0] = iTrackFactory.CreateTrack(Brn("http://addr:port/path/file1"), Brx::Empty());
    iTracks[1] = iTrackFactory.CreateTrack(Brn("http://addr:port/path/file2"), Brx::Empty());
    iTracks[2] = iTrackFactory.CreateTrack(Brn("http://addr:port/path/file3"), Brx::Empty());
}

DummyUriProvider::~DummyUriProvider()
{
    iTracks[0]->RemoveRef();
    iTracks[1]->RemoveRef();
    iTracks[2]->RemoveRef();
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

void DummyUriProvider::BeginLater(TUint /*aTrackId*/)
{
    ASSERTS(); // don't expect this to ever be called
}

EStreamPlay DummyUriProvider::GetNext(Track*& aTrack)
{
    const TBool firstCall = (iIndex<0);
    TUint index;
    if (iPendingIndex != -1) {
        index = iPendingIndex;
        iPendingIndex = -1;
    }
    else {
        if (++iIndex == kNumEntries) {
            iIndex = 0;
        }
        index = iIndex;
    }
    aTrack = iTracks[index];
    aTrack->AddRef();
    return (!firstCall && iIndex == 0? ePlayLater : ePlayYes);
}

TUint DummyUriProvider::CurrentTrackId() const
{
    return iTracks[iIndex]->Id();
}

TBool DummyUriProvider::MoveNext()
{
    iPendingIndex = ++iIndex;
    if (iPendingIndex == kNumEntries) {
        iPendingIndex = 0;
    }
    return true;
}

TBool DummyUriProvider::MovePrevious()
{
    iPendingIndex = --iIndex;
    if (iPendingIndex < 0) {
        iPendingIndex = kNumEntries-1;
    }
    return true;
}


// DummyUriStreamer

DummyUriStreamer::DummyUriStreamer(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownStreamElement, Semaphore& aTrackAddedSem, Semaphore& aTrackCompleteSem)
    : iSupply(aMsgFactory, aDownStreamElement)
    , iTrackAddedSem(aTrackAddedSem)
    , iTrackCompleteSem(aTrackCompleteSem)
    , iStreamId(0)
{
}

DummyUriStreamer::~DummyUriStreamer()
{
}

TUint DummyUriStreamer::TrackId() const
{
    return iTrackId;
}

TUint DummyUriStreamer::StreamId() const
{
    return iStreamId;
}

ProtocolStreamResult DummyUriStreamer::DoStream(Track& aTrack)
{
    iStreamId++;
    iTrackId = aTrack.Id();
    iSupply.OutputTrack(aTrack);
    iSupply.OutputStream(aTrack.Uri(), 1LL, 0, false, false, *this, iStreamId);
    iTrackAddedSem.Signal();
    iTrackCompleteSem.Wait();
    return EProtocolStreamSuccess;
}

void DummyUriStreamer::Interrupt(TBool /*aInterrupt*/)
{
}

EStreamPlay DummyUriStreamer::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint DummyUriStreamer::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DummyUriStreamer::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void DummyUriStreamer::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
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

const Brx& DummySupply::LastMode() const
{
    return iLastMode;
}

TBool DummySupply::LastSupportsLatency() const
{
    return iLastSupportsLatency;
}

TBool DummySupply::LastIsRealTime() const
{
    return iLastRealTime;
}

TUint DummySupply::LastDelayJiffies() const
{
    return iLastDelayJiffies;
}

void DummySupply::Push(Msg* aMsg)
{
    (void)aMsg->Process(*this);
    aMsg->RemoveRef();
}

Msg* DummySupply::ProcessMsg(MsgMode* aMsg)
{
    iLastMode.Replace(aMsg->Mode());
    const ModeInfo& info = aMsg->Info();
    iLastSupportsLatency = info.SupportsLatency();
    iLastRealTime = info.IsRealTime();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgTrack* aMsg)
{
    iLastTrackUri.Replace(aMsg->Track().Uri());
    iLastTrackId = aMsg->Track().Id();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgDrain* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgDelay* aMsg)
{
    iLastDelayJiffies = aMsg->DelayJiffies();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgMetaText* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgFlush* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgWait* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgBitRate* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* DummySupply::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}


// SuiteFiller

SuiteFiller::SuiteFiller()
    : Suite("Trivial Filler tests")
    , iTrackAddedSem("TASM", 0)
    , iTrackCompleteSem("TCSM", 0)
    , iNextFlushId(1)
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 4);
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iDummySupply = new DummySupply();
    iFiller = new Filler(*iDummySupply, *this, *this, *iMsgFactory, *iTrackFactory, *this, *this, kPriorityNormal, kDefaultLatency);
    iUriProvider = new DummyUriProvider(*iTrackFactory);
    iUriStreamer = new DummyUriStreamer(*iMsgFactory, *iFiller, iTrackAddedSem, iTrackCompleteSem);
    iFiller->Add(*iUriProvider);
    iFiller->Start(*iUriStreamer);
}

SuiteFiller::~SuiteFiller()
{
    iFiller->Quit();
    delete iUriStreamer;
    delete iFiller;
    delete iUriProvider;
    delete iDummySupply;
    delete iMsgFactory;
    delete iTrackFactory;
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
    TEST(iDummySupply->LastMode() == iUriProvider->Mode());
    TEST(iDummySupply->LastSupportsLatency() == iUriProvider->SupportsLatency());
    TEST(iDummySupply->LastIsRealTime() == iUriProvider->IsRealTime());
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(0));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iDummySupply->LastDelayJiffies() == kDefaultLatency);
    TEST(iTrackId == iUriProvider->IdByIndex(0));
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    TUint trackId = iTrackId;

    // When first track completes, IUriStreamer should be passed uri for second track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(1));
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;

    // Stop/Next during second track.  Once track completes IUriStreamer should be passed uri for third track
    (void)iFiller->Stop();
    iTrackCompleteSem.Signal();
    // test for invalid Next() arg
    TEST(!iFiller->Next(Brn("InvalidMode")));
    //
    TEST(iFiller->Next(iUriProvider->Mode()));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(2));
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;

    // Stop/Prev during third track.  Once track completes IUriStreamer should be passed uri for second track
    (void)iFiller->Stop();
    iTrackCompleteSem.Signal();
    TEST(iFiller->Prev(iUriProvider->Mode()));
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(1));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(1));
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;

    // Once track completes, IUriStreamer should (again) be passed uri for third track
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iDummySupply->LastTrackUri() == iUriProvider->TrackUriByIndex(2));
    TEST(iDummySupply->LastTrackId() == iUriStreamer->TrackId());
    TEST(iDummySupply->LastStreamId() == iUriStreamer->StreamId());
    TEST(iTrackId == iUriProvider->IdByIndex(2));
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(iPlayNow);
    trackId = iTrackId;

    // Once track completes, dummy UriProvider will return first track to be played later.  IUriStreamer should not be passed anything
    iTrackCompleteSem.Signal();
    iTrackAddedSem.Wait();
    TEST(iTrackId == iUriProvider->IdByIndex(0));
    TEST(iTrackId != trackId);
    TEST(iStreamId == iDummySupply->LastStreamId());
    TEST(!iPlayNow);
    (void)iFiller->Stop();
    iTrackCompleteSem.Signal();
}

void SuiteFiller::AddStream(TUint aId, TUint aStreamId, TBool aPlayNow)
{
    iTrackId = aId;
    iStreamId = aStreamId;
    iPlayNow = aPlayNow;
}

TUint SuiteFiller::NextFlushId()
{
    return iNextFlushId++;
}

void SuiteFiller::NotifyTrackFailed(TUint /*aTrackId*/)
{
}

void SuiteFiller::NotifyStreamPlayStatus(TUint /*aTrackId*/, TUint /*aStreamId*/, EStreamPlay /*aStatus*/)
{
}

TUint SuiteFiller::NextStreamId()
{
    ASSERTS();
    return kStreamIdInvalid;
}

EStreamPlay SuiteFiller::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayNo;
}



void TestFiller()
{
    Runner runner("Basic Filler tests\n");
    runner.Add(new SuiteFiller());
    runner.Run();
}
