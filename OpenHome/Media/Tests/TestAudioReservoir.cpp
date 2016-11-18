#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Functor.h>

#include <string.h>
#include <vector>
#include <list>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteAudioReservoir : public Suite, private IMsgProcessor, private IFlushIdProvider
{
    static const TUint kDecodedAudioCount = 512;
    static const TUint kMsgAudioPcmCount  = 512;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kReservoirSize = Jiffies::kPerMs * 500;
    static const TUint kMaxStreams = 5;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
public:
    SuiteAudioReservoir();
    ~SuiteAudioReservoir();
    void Test() override;
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
private: // from IFlushIdProvider
    TUint NextFlushId() override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
enum EMsgGenerationState
{
    EGenerateSingle
   ,EFillReservoir
   ,EExit
};
private:
    void GenerateMsg(EMsgType aType);
    void GenerateMsgs(EMsgType aType);
    void Generate(EMsgGenerationState aState, EMsgType aType);
    void MsgEnqueueThread();
    TBool EnqueueMsg(EMsgType aType);
    MsgAudio* CreateAudio();
    TBool ReservoirIsFull() const { return static_cast<AudioReservoir*>(iReservoir)->IsFull(); }
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    DecodedAudioReservoir* iReservoir;
    TUint iNextFlushId;
    ThreadFunctor* iThread;
    EMsgGenerationState iMsgGenerationState;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamComplete;
    TUint64 iTrackOffset;
    IStreamHandler* iStreamHandler;
    TUint64 iLastPulledTrackPos;
    TUint iLastPulledJiffies;
    TUint iLastFlushId;
};

class SuiteEncodedReservoir : public SuiteUnitTest, private IStreamHandler, private IMsgProcessor, private IFlushIdProvider
{
    static const TUint kTrySeekResponse = 42;
    static const TUint kStreamId = 5;
public:
    SuiteEncodedReservoir();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
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
private: // from IFlushIdProvider
    TUint NextFlushId() override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgFlush
       ,EMsgQuit
    };
private:
    void PullNext(EMsgType aType);
    void PushEncodedStream();
    void PushEncodedAudio(TByte aFill);
private:
    void TestStreamHandlerCallsPassedOn();
    void TestSeekBackwards();
    void TestSeekForwardsIntoReservoir();
    void TestSeekForwardsBeyondReservoir();
    void TestNewStreamInterruptsSeek();
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    EncodedAudioReservoir* iReservoir;
    TUint iNextFlushId;
    EMsgType iLastMsg;
    TUint iOkToPlayCount;
    TUint iTrySeekCount;
    TUint iTryStopCount;
    TUint iNotifyStarvingCount;
    TUint iPulledFlushId;
    TUint iEncAudioFill;
    TByte iAudioSrc[EncodedAudio::kMaxBytes];
    TByte iAudioDest[EncodedAudio::kMaxBytes];
};

class SuiteGorger : public SuiteUnitTest, private IStreamHandler, private IMsgProcessor, private IFlushIdProvider
{
    static const TUint kGorgeSize = Jiffies::kPerMs * 100; // production code will likely use a much larger size
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
    static const Brn kModeRealTime;
    static const Brn kModeGorgable;
public:
    SuiteGorger();
    ~SuiteGorger();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    enum EMsgType
    {
        ENone
        , EMsgMode
        , EMsgTrack
        , EMsgDrain
        , EMsgDelay
        , EMsgEncodedStream
        , EMsgAudioEncoded
        , EMsgMetaText
        , EMsgStreamInterrupted
        , EMsgHalt
        , EMsgFlush
        , EMsgWait
        , EMsgDecodedStream
        , EMsgBitRate
        , EMsgAudioPcm
        , EMsgSilence
        , EMsgPlayable
        , EMsgQuit
    };
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
private: // from IFlushIdProvider
    TUint NextFlushId() override;
private:
    void Queue(Msg* aMsg);
    void PullNext(EMsgType aExpectedMsg);
    Msg* CreateMode(const Brx& aMode, TBool aSupportsLatency);
    Msg* CreateTrack();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    void TestAllMsgsPassWhileNotGorging();
    void TestNewModeUpdatesGorgeStatus();
    void TestGorgingEndsWithSufficientAudio();
    void TestGorgingEndsWithNewMode();
    void TestHaltEnablesGorging();
    void TestStarvationEnablesGorging();
private:
    Mutex iLock;
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    DecodedAudioReservoir* iDecodedReservoir;
    TUint iNextFlushId;
    EMsgType iLastPulledMsg;
    TUint64 iTrackOffset;
    TUint iNextStreamId;
    TUint iStarvationNotifications;
};

} // namespace Media
} // namespace OpenHome


// SuiteAudioReservoir

const SpeakerProfile SuiteAudioReservoir::kProfile(2);

SuiteAudioReservoir::SuiteAudioReservoir()
    : Suite("Decoded Audio Reservoir tests")
    , iLastMsg(ENone)
    , iSemUpstream("TRSV", 0)
    , iSemUpstreamComplete("TRSV", 0)
    , iTrackOffset(0)
    , iStreamHandler(nullptr)
    , iLastPulledTrackPos(0)
    , iLastPulledJiffies(0)
    , iLastFlushId(0)
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(kMsgAudioPcmCount, kDecodedAudioCount);
    init.SetMsgSilenceCount(kMsgSilenceCount);
    init.SetMsgDecodedStreamCount(kMaxStreams+2);
    init.SetMsgModeCount(2);
    init.SetMsgEncodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(*iMsgFactory, *this, kReservoirSize, kMaxStreams, 0);
    iNextFlushId = MsgFlush::kIdInvalid;
    iThread = new ThreadFunctor("TEST", MakeFunctor(*this, &SuiteAudioReservoir::MsgEnqueueThread));
    iThread->Start();
    iSemUpstreamComplete.Wait();
}

SuiteAudioReservoir::~SuiteAudioReservoir()
{
    iMsgGenerationState = EExit;
    iSemUpstream.Signal();
    delete iThread;
    delete iReservoir;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteAudioReservoir::Test()
{
    /*
    Test goes something like
        Add single 0xff filled audio.  Check it can be Pull()ed.
        Check that Silence, Track, MetaText, Quit & Halt msgs are passed through.
        Add audio until we exceed MaxSize.  Check adding thread is blocked.
        Pull single audio msg.  Add Flush; check that next msg Pull()ed is the Flush and that reservoir is now empty.
    */

    // Add single 0xff filled audio.  Check it can be Pull()ed.
    TEST(iLastMsg == ENone);
    GenerateMsg(EMsgAudioPcm);
    iSemUpstreamComplete.Wait();
    Msg* msg = iReservoir->Pull();
    msg = msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);
    ASSERT(msg == nullptr);

    // Check that uninteresting msgs are passed through.
    EMsgType types[] = { EMsgMode, EMsgTrack, EMsgDrain, EMsgEncodedStream,
                         EMsgDecodedStream, EMsgDelay, EMsgBitRate, EMsgMetaText,
                         EMsgStreamInterrupted, EMsgFlush, EMsgWait,
                         EMsgHalt, EMsgQuit };
    for (TUint i=0; i<sizeof(types)/sizeof(types[0]); i++) {
        EMsgType msgType = types[i];
        GenerateMsg(msgType);
        iSemUpstreamComplete.Wait();
        msg = iReservoir->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        TEST(iLastMsg == msgType);
    }

    // Add audio until we exceed MaxSize.  Check adding thread is blocked.
    GenerateMsgs(EMsgAudioPcm);
    while (iReservoir->Jiffies() < kReservoirSize) {
        Thread::Sleep(10);
    }
    TUint jiffies = iReservoir->Jiffies();
    // lazy check that Enqueue has blocked
    // ...sleep for a while then check size of reservoir is unchanged
    Thread::Sleep(25);
    TEST(iReservoir->Jiffies() == jiffies);

    // tell reservoir to discard some of its audio content
    const TUint kDiscardJiffies = 100 * Jiffies::kPerMs;
    const TUint64 prevTrackPos = iLastPulledTrackPos;
    const TUint flushId = iStreamHandler->TryDiscard(kDiscardJiffies);
    TEST(flushId != MsgFlush::kIdInvalid);
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgFlush);
    TEST(iLastFlushId == flushId);
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastMsg == EMsgDecodedStream);
    TEST(iLastPulledTrackPos == prevTrackPos + kDiscardJiffies);
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    TEST(iLastMsg == EMsgAudioPcm);

    // Pull single msg to unblock iThread
    msg = iReservoir->Pull();
    msg = msg->Process(*this);
    ASSERT(msg == nullptr);
    jiffies = iReservoir->Jiffies();

    // Keep adding DecodedStream until Enqueue blocks
    for (TUint i=0; i<kMaxStreams-1; i++) {
        GenerateMsg(EMsgDecodedStream);
        iSemUpstreamComplete.Wait();
    }
    TEST(!ReservoirIsFull());
    GenerateMsg(EMsgDecodedStream);
    while (!ReservoirIsFull()) {
        Thread::Sleep(1);
    }
    TEST(ReservoirIsFull());
    TEST(iReservoir->Jiffies() == jiffies);
    do {
        TEST(ReservoirIsFull());
        msg = iReservoir->Pull();
        msg = msg->Process(*this);
    } while (iLastMsg == EMsgAudioPcm);
    TEST(iLastMsg == EMsgDecodedStream);
    msg->RemoveRef();
    TEST(!ReservoirIsFull());
}

void SuiteAudioReservoir::GenerateMsg(EMsgType aType)
{
    Generate(EGenerateSingle, aType);
}

void SuiteAudioReservoir::GenerateMsgs(EMsgType aType)
{
    Generate(EFillReservoir, aType);
}

void SuiteAudioReservoir::Generate(EMsgGenerationState aState, EMsgType aType)
{
    iMsgGenerationState = aState;
    iNextGeneratedMsg = aType;
    iSemUpstream.Signal();
}

void SuiteAudioReservoir::MsgEnqueueThread()
{
    for (;;) {
        iSemUpstreamComplete.Signal();
        iSemUpstream.Wait();
        switch (iMsgGenerationState)
        {
        case EGenerateSingle:
            EnqueueMsg(iNextGeneratedMsg);
            break;
        case EFillReservoir:
            while (!EnqueueMsg(iNextGeneratedMsg)) {
            }
            break;
        case EExit:
            return;
        }
    }
}

TBool SuiteAudioReservoir::EnqueueMsg(EMsgType aType)
{
    TBool shouldBlock = false;
    Msg* msg = nullptr;
    switch (aType)
    {
    default:
    case ENone:
    case EMsgPlayable:
        ASSERTS();
        break;
    case EMsgAudioPcm:
    {
        MsgAudio* audio = CreateAudio();
        shouldBlock = (iReservoir->SizeInJiffies() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgDecodedStream:
        iTrackOffset = 0;
        msg = iMsgFactory->CreateMsgDecodedStream(0, 0, 16, kSampleRate, kNumChannels, Brx::Empty(), 0, 0, false, false, false, false, Multiroom::Allowed, kProfile, nullptr);
        break;
    case EMsgBitRate:
        msg = iMsgFactory->CreateMsgBitRate(1);
        break;
    case EMsgMode:
        msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, ModeClockPullers(), false, false);
        break;
    case EMsgTrack:
    {
        Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
        msg = iMsgFactory->CreateMsgTrack(*track);
        track->RemoveRef();
    }
        break;
    case EMsgDrain:
        msg = iMsgFactory->CreateMsgDrain(Functor());
        break;
    case EMsgDelay:
        msg = iMsgFactory->CreateMsgDelay(Jiffies::kPerMs * 5);
        break;
    case EMsgEncodedStream:
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, 0, false, false, Multiroom::Allowed, nullptr);
        break;
    case EMsgMetaText:
        msg = iMsgFactory->CreateMsgMetaText(Brn("metatext"));
        break;
    case EMsgStreamInterrupted:
        msg = iMsgFactory->CreateMsgStreamInterrupted();
        break;
    case EMsgHalt:
        msg = iMsgFactory->CreateMsgHalt();
        break;
    case EMsgFlush:
        msg = iMsgFactory->CreateMsgFlush(1);
        break;
    case EMsgWait:
        msg = iMsgFactory->CreateMsgWait();
        break;
    case EMsgQuit:
        msg = iMsgFactory->CreateMsgQuit();
        break;
    }
    iReservoir->Push(msg);
    return shouldBlock;
}

MsgAudio* SuiteAudioReservoir::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgMode* aMsg)
{
    iLastMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgTrack* aMsg)
{
    iLastMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgDrain* aMsg)
{
    iLastMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgDelay* aMsg)
{
    iLastMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgMetaText* aMsg)
{
    iLastMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    iLastFlushId = aMsg->Id();
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgWait* aMsg)
{
    iLastMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsg = EMsgDecodedStream;
    const auto info = aMsg->StreamInfo();
    iStreamHandler = info.StreamHandler();
    iLastPulledTrackPos = info.SampleStart() * Jiffies::PerSample(info.SampleRate());
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgBitRate* aMsg)
{
    iLastMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    iLastPulledJiffies = aMsg->Jiffies();
    iLastPulledTrackPos += iLastPulledJiffies;

    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufTest pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
//    playable->RemoveRef();
    const TByte* ptr = buf.Ptr();
    const TInt firstSubsample = (ptr[0]<<8) | ptr[1];
    const TUint bytes = buf.Bytes();
    const TInt lastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];
    TEST(firstSubsample == 0xffff);
    TEST(firstSubsample == lastSubsample);
    if (firstSubsample != lastSubsample) {
        Print("firstSubsample=%08x, lastSubsample=%08x\n", firstSubsample, lastSubsample);
    }
    playable->RemoveRef();
    return nullptr;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // MsgSilence not used in this test
    return nullptr;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not used in this test
    return nullptr;
}

Msg* SuiteAudioReservoir::ProcessMsg(MsgQuit* aMsg)
{
   iLastMsg = EMsgQuit;
    return aMsg;
}

TUint SuiteAudioReservoir::NextFlushId()
{
    return ++iNextFlushId;
}


// SuiteEncodedReservoir

SuiteEncodedReservoir::SuiteEncodedReservoir()
    : SuiteUnitTest("EncodedReservoir")
{
    AddTest(MakeFunctor(*this, &SuiteEncodedReservoir::TestStreamHandlerCallsPassedOn), "TestStreamHandlerCallsPassedOn");
    AddTest(MakeFunctor(*this, &SuiteEncodedReservoir::TestSeekBackwards), "TestSeekBackwards");
    AddTest(MakeFunctor(*this, &SuiteEncodedReservoir::TestSeekForwardsIntoReservoir), "TestSeekForwardsIntoReservoir");
    AddTest(MakeFunctor(*this, &SuiteEncodedReservoir::TestSeekForwardsBeyondReservoir), "TestSeekForwardsBeyondReservoir");
    AddTest(MakeFunctor(*this, &SuiteEncodedReservoir::TestNewStreamInterruptsSeek), "TestNewStreamInterruptsSeek");
}

void SuiteEncodedReservoir::Setup()
{
    MsgFactoryInitParams init;
    init.SetMsgAudioEncodedCount(11, 10);
    init.SetMsgEncodedStreamCount(3);
    init.SetMsgModeCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new EncodedAudioReservoir(*iMsgFactory, *this, 100/*max_msg*/, 10/*max_streams*/);
    iNextFlushId = MsgFlush::kIdInvalid;
    iLastMsg = ENone;
    iOkToPlayCount = iTrySeekCount = iTryStopCount = iNotifyStarvingCount = 0;
    iPulledFlushId = MsgFlush::kIdInvalid;
    iEncAudioFill = 12345;
    (void)memset(iAudioDest, 0, sizeof(iAudioDest));
}

void SuiteEncodedReservoir::TearDown()
{
    delete iReservoir;
    delete iTrackFactory;
    delete iMsgFactory;
}

EStreamPlay SuiteEncodedReservoir::OkToPlay(TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return ePlayNo;
}

TUint SuiteEncodedReservoir::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    iTrySeekCount++;
    return kTrySeekResponse;
}

TUint SuiteEncodedReservoir::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteEncodedReservoir::TryStop(TUint /*aStreamId*/)
{
    iTryStopCount++;
    return MsgFlush::kIdInvalid;
}

void SuiteEncodedReservoir::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
    iNotifyStarvingCount++;
}

Msg* SuiteEncodedReservoir::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteEncodedReservoir::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastMsg = EMsgAudioEncoded;
    (void)memset(iAudioDest, 0, sizeof(iAudioDest));
    aMsg->CopyTo(iAudioDest);
    iEncAudioFill = iAudioDest[0];
    return aMsg;
}

Msg* SuiteEncodedReservoir::ProcessMsg(MsgFlush* aMsg)
{
    iLastMsg = EMsgFlush;
    iPulledFlushId = aMsg->Id();
    return aMsg;
}

Msg* SuiteEncodedReservoir::ProcessMsg(MsgMode* aMsg)              { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgTrack* aMsg)             { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgDrain* aMsg)             { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgDelay* aMsg)             { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgMetaText* aMsg)          { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgStreamInterrupted* aMsg) { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgHalt* aMsg)              { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgWait* aMsg)              { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgDecodedStream* aMsg)     { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgBitRate* aMsg)           { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgAudioPcm* aMsg)          { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgSilence* aMsg)           { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgPlayable* aMsg)          { ASSERTS(); return aMsg; }
Msg* SuiteEncodedReservoir::ProcessMsg(MsgQuit* aMsg)              { ASSERTS(); return aMsg; }

TUint SuiteEncodedReservoir::NextFlushId()
{
    return ++iNextFlushId;
}

void SuiteEncodedReservoir::PullNext(EMsgType aType)
{
    Msg* msg = iReservoir->Pull();
    msg = msg->Process(*this);
    if (msg != nullptr) {
        msg->RemoveRef();
    }
    TEST(iLastMsg == aType);
}

void SuiteEncodedReservoir::PushEncodedStream()
{
    auto msg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1234567LL, 0, kStreamId, true/*seekable*/, false/*live*/, Multiroom::Allowed, this/*stream handler*/);
    iReservoir->Push(msg);
}

void SuiteEncodedReservoir::PushEncodedAudio(TByte aFill)
{
    (void)memset(iAudioSrc, aFill, sizeof(iAudioSrc));
    Brn buf(iAudioSrc, sizeof(iAudioSrc));
    auto msg = iMsgFactory->CreateMsgAudioEncoded(buf);
    iReservoir->Push(msg);
}

void SuiteEncodedReservoir::TestStreamHandlerCallsPassedOn()
{
    PushEncodedStream();
    PullNext(EMsgEncodedStream);

    TEST(iOkToPlayCount == 0);
    (void)iReservoir->OkToPlay(kStreamId);
    TEST(iOkToPlayCount == 1);

    TEST(iTryStopCount == 0);
    (void)iReservoir->TryStop(kStreamId);
    TEST(iTryStopCount == 1);

    TEST(iNotifyStarvingCount == 0);
    iReservoir->NotifyStarving(Brx::Empty(), kStreamId, true);
    TEST(iNotifyStarvingCount == 1);

    TEST(iTrySeekCount == 0);
    TEST(iReservoir->TrySeek(kStreamId+1, 0) == kTrySeekResponse);
    TEST(iTrySeekCount == 1);
}

void SuiteEncodedReservoir::TestSeekBackwards()
{
    PushEncodedStream();
    PushEncodedAudio(1);
    PushEncodedAudio(2);
    PullNext(EMsgEncodedStream);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 1);
    TEST(iReservoir->TrySeek(kStreamId, EncodedAudio::kMaxBytes-1) == kTrySeekResponse);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 2);
}

void SuiteEncodedReservoir::TestSeekForwardsIntoReservoir()
{
    PushEncodedStream();
    PushEncodedAudio(1);
    PushEncodedAudio(1);
    PushEncodedAudio(1);
    PushEncodedAudio(1);
    PushEncodedAudio(2);
    PullNext(EMsgEncodedStream);
    static const TUint64 kSeekPos = EncodedAudio::kMaxBytes*3 + 100;
    const TUint flushId = iReservoir->TrySeek(kStreamId, kSeekPos);
    TEST(flushId != MsgFlush::kIdInvalid);
    TEST(flushId != kTrySeekResponse);
    PullNext(EMsgFlush);
    TEST(iPulledFlushId == flushId);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 1);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 2);
}

void SuiteEncodedReservoir::TestSeekForwardsBeyondReservoir()
{
    PushEncodedStream();
    PushEncodedAudio(1);
    PushEncodedAudio(2);
    PushEncodedAudio(3);
    PullNext(EMsgEncodedStream);
    static const TUint64 kSeekPos = EncodedAudio::kMaxBytes * 10;
    TEST(iReservoir->TrySeek(kStreamId, kSeekPos) == kTrySeekResponse);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 1);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 2);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 3);
}

void SuiteEncodedReservoir::TestNewStreamInterruptsSeek()
{
    PushEncodedStream();
    PushEncodedAudio(1);
    PushEncodedAudio(2);
    PushEncodedAudio(3);
    PushEncodedAudio(4);
    PushEncodedStream();
    PushEncodedAudio(5);
    PushEncodedAudio(6);
    PullNext(EMsgEncodedStream);
    static const TUint64 kSeekPos = EncodedAudio::kMaxBytes * 5;
    const TUint flushId = iReservoir->TrySeek(kStreamId, kSeekPos);
    TEST(flushId != MsgFlush::kIdInvalid);
    TEST(flushId != kTrySeekResponse);
    PullNext(EMsgFlush);
    TEST(iPulledFlushId == flushId);
    PullNext(EMsgEncodedStream);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 5);
    PullNext(EMsgAudioEncoded);
    TEST(iEncAudioFill == 6);
}


// SuiteGorger

const Brn SuiteGorger::kModeRealTime("RealTime");
const Brn SuiteGorger::kModeGorgable("Gorgable");
const SpeakerProfile SuiteGorger::kProfile(2);

SuiteGorger::SuiteGorger()
    : SuiteUnitTest("Gorger")
    , iLock("TGRG")
{
    AddTest(MakeFunctor(*this, &SuiteGorger::TestAllMsgsPassWhileNotGorging), "TestAllMsgsPassWhileNotGorging");
    AddTest(MakeFunctor(*this, &SuiteGorger::TestNewModeUpdatesGorgeStatus), "TestNewModeUpdatesGorgeStatus");
    AddTest(MakeFunctor(*this, &SuiteGorger::TestGorgingEndsWithSufficientAudio), "TestGorgingEndsWithSufficientAudio");
    AddTest(MakeFunctor(*this, &SuiteGorger::TestGorgingEndsWithNewMode), "TestGorgingEndsWithNewMode");
    AddTest(MakeFunctor(*this, &SuiteGorger::TestHaltEnablesGorging), "TestHaltEnablesGorging");
    AddTest(MakeFunctor(*this, &SuiteGorger::TestStarvationEnablesGorging), "TestStarvationEnablesGorging");
}

SuiteGorger::~SuiteGorger()
{
}

void SuiteGorger::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(52, 50);
    init.SetMsgDecodedStreamCount(3);
    init.SetMsgTrackCount(2);
    init.SetMsgEncodedStreamCount(2);
    init.SetMsgMetaTextCount(2);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    init.SetMsgModeCount(3);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iDecodedReservoir = new DecodedAudioReservoir(*iMsgFactory, *this, kGorgeSize * 3, 10, kGorgeSize);
    iNextFlushId = MsgFlush::kIdInvalid;
    iLastPulledMsg = ENone;
    iTrackOffset = 0;
    iNextStreamId = 1;
    iStarvationNotifications = 0;
}

void SuiteGorger::TearDown()
{
    delete iDecodedReservoir;
    delete iMsgFactory;
    delete iTrackFactory;
}

EStreamPlay SuiteGorger::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteGorger::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteGorger::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteGorger::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteGorger::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool aStarving)
{
    if (aStarving) {
        iStarvationNotifications++;
    }
}

Msg* SuiteGorger::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgAudioEncoded* aMsg)
{
    iLastPulledMsg = EMsgAudioEncoded;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgBitRate* aMsg)
{
    iLastPulledMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgPlayable* aMsg)
{
    iLastPulledMsg = EMsgPlayable;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

TUint SuiteGorger::NextFlushId()
{
    return ++iNextFlushId;
}

void SuiteGorger::Queue(Msg* aMsg)
{
    iDecodedReservoir->Push(aMsg);
}

void SuiteGorger::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iDecodedReservoir->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteGorger::CreateMode(const Brx& aMode, TBool aSupportsLatency)
{
    return iMsgFactory->CreateMsgMode(aMode, aSupportsLatency, ModeClockPullers(), false, false);
}

Msg* SuiteGorger::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteGorger::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, false, false, Multiroom::Allowed, kProfile, this);
}

Msg* SuiteGorger::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteGorger::TestAllMsgsPassWhileNotGorging()
{
    Queue(CreateMode(kModeRealTime, true));
    Queue(CreateTrack());
    Queue(iMsgFactory->CreateMsgDrain(Functor()));
    Queue(iMsgFactory->CreateMsgDelay(0));
    Queue(CreateDecodedStream());
    Queue(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    Queue(iMsgFactory->CreateMsgStreamInterrupted());
    Queue(iMsgFactory->CreateMsgBitRate(42));
    Queue(CreateAudio());
    Queue(iMsgFactory->CreateMsgHalt());
    Queue(iMsgFactory->CreateMsgWait());
    Queue(iMsgFactory->CreateMsgQuit());

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDrain);
    PullNext(EMsgDelay);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgMetaText);
    PullNext(EMsgStreamInterrupted);
    PullNext(EMsgBitRate);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    PullNext(EMsgQuit);
}

void SuiteGorger::TestNewModeUpdatesGorgeStatus()
{
    TEST(!iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);

    TBool realTime = false;
    Queue(CreateMode(kModeGorgable, realTime));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);

    realTime = true;
    Queue(CreateMode(kModeRealTime, realTime));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());

    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iDecodedReservoir->iCanGorge);
    while (iDecodedReservoir->iGorging) {
        Thread::Sleep(10); // wait for new Mode to be pulled, cancelling gorging
    }
    TEST(!iDecodedReservoir->iGorging);
    PullNext(EMsgMode);
    TEST(!iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
}

void SuiteGorger::TestGorgingEndsWithSufficientAudio()
{
    Queue(CreateMode(kModeGorgable, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(iDecodedReservoir->iGorging);

    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
    Queue(CreateAudio());
    PullNext(EMsgAudioPcm);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestGorgingEndsWithNewMode()
{
    Queue(CreateMode(kModeGorgable, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(iDecodedReservoir->iGorging);

    Queue(CreateAudio());
    TEST(iDecodedReservoir->iCanGorge);
    TEST(iDecodedReservoir->iGorging);

    Queue(CreateMode(kModeRealTime, true));
    PullNext(EMsgAudioPcm);
    while (iDecodedReservoir->iGorging) {
        Thread::Sleep(10); // wait for new Mode to be pulled, cancelling gorging
    }
    TEST(!iDecodedReservoir->iGorging);
    TEST(!iDecodedReservoir->iGorging);
    PullNext(EMsgMode);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestHaltEnablesGorging()
{
    Queue(CreateMode(kModeGorgable, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(iDecodedReservoir->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);

    Queue(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iDecodedReservoir->iGorging);
    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestStarvationEnablesGorging()
{
    Queue(CreateMode(kModeRealTime, true));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
    iDecodedReservoir->NotifyStarving(kModeRealTime, 1, true);
    TEST(!iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
    TEST(iStarvationNotifications == 1);

    Queue(CreateMode(kModeGorgable, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iDecodedReservoir->iCanGorge);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iDecodedReservoir->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(!iDecodedReservoir->iGorging);
    iDecodedReservoir->NotifyStarving(kModeGorgable, 2, true);
    TEST(iDecodedReservoir->iCanGorge);
    TEST(iDecodedReservoir->iGorging);
    TEST(iStarvationNotifications == 2);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}



void TestAudioReservoir()
{
    Runner runner("Decoded Audio Reservoir tests\n");
    runner.Add(new SuiteAudioReservoir());
    runner.Add(new SuiteEncodedReservoir());
    runner.Add(new SuiteGorger());
    runner.Run();
}
