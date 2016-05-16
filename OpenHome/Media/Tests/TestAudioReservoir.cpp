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

class SuiteAudioReservoir : public Suite, private IMsgProcessor
{
    static const TUint kDecodedAudioCount = 512;
    static const TUint kMsgAudioPcmCount  = 512;
    static const TUint kMsgSilenceCount   = 1;

    static const TUint kReservoirSize = Jiffies::kPerMs * 500;
    static const TUint kMaxStreams = 5;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
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
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
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
    ThreadFunctor* iThread;
    EMsgGenerationState iMsgGenerationState;
    EMsgType iNextGeneratedMsg;
    EMsgType iLastMsg;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamComplete;
    TUint64 iTrackOffset;
};

class SuiteReservoirHistory : public Suite, private IMsgProcessor, private IClockPullerReservoir
{
    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
    static const TUint kBitDepth = 16;
    static const TUint kReservoirSize = Jiffies::kPerMs * 1000;
    static const TUint kMaxStreams = 5;
    static const TUint kMaxHistorySamples = 10;
    static const TUint kTotalHistoryUpdates = kMaxHistorySamples * 2;
public:
    SuiteReservoirHistory();
    ~SuiteReservoirHistory();
private: // from Suite
    void Test() override;
private:
    void PullerThread();
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
private: // from IClockPullerReservoir
    void Reset() override;
    void Stop() override;
    void Start(TUint aNotificationFrequency) override;
    void NotifySize(TUint aJiffies) override;
private:
    MsgFactory* iMsgFactory;
    TrackFactory* iTrackFactory;
    AllocatorInfoLogger iInfoAggregator;
    DecodedAudioReservoir* iReservoir;
    ThreadFunctor* iThread;
    TUint64 iDequeuedJiffies;
    TUint iHistoryPointCount;
    TBool iStopAudioGeneration;
    TByte iBuf[DecodedAudio::kMaxBytes];
    TUint iStreamId;
    TUint iSampleRate;
    TBool iStartCalled;
    TBool iNotifySizeCalled;
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

} // namespace Media
} // namespace OpenHome


// SuiteAudioReservoir

SuiteAudioReservoir::SuiteAudioReservoir()
    : Suite("Decoded Audio Reservoir tests")
    , iLastMsg(ENone)
    , iSemUpstream("TRSV", 0)
    , iSemUpstreamComplete("TRSV", 0)
    , iTrackOffset(0)
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(kMsgAudioPcmCount, kDecodedAudioCount);
    init.SetMsgSilenceCount(kMsgSilenceCount);
    init.SetMsgDecodedStreamCount(kMaxStreams+2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize, kMaxStreams);
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
    EMsgType types[] = { EMsgSilence, EMsgDecodedStream, EMsgBitRate, EMsgMode,
                         EMsgTrack, EMsgDrain, EMsgDelay, EMsgEncodedStream,
                         EMsgMetaText, EMsgStreamInterrupted, EMsgFlush, EMsgWait,
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
    case EMsgSilence:
    {
        TUint size = Jiffies::kPerMs;
        MsgAudio* audio = iMsgFactory->CreateMsgSilence(size, kSampleRate, 16, kNumChannels);
        shouldBlock = (iReservoir->SizeInJiffies() + audio->Jiffies() >= kReservoirSize);
        msg = audio;
        break;
    }
    case EMsgDecodedStream:
        msg = iMsgFactory->CreateMsgDecodedStream(0, 0, 0, 0, 0, Brx::Empty(), 0, 0, false, false, false, false, nullptr);
        break;
    case EMsgBitRate:
        msg = iMsgFactory->CreateMsgBitRate(1);
        break;
    case EMsgMode:
        msg = iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, ModeClockPullers(), false, false);
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
        msg = iMsgFactory->CreateMsgEncodedStream(Brn("http://127.0.0.1:65535"), Brn("metatext"), 0, 0, 0, false, false, nullptr);
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

Msg* SuiteAudioReservoir::ProcessMsg(MsgSilence* aMsg)
{
    iLastMsg = EMsgSilence;
    return aMsg;
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


// SuiteReservoirHistory

SuiteReservoirHistory::SuiteReservoirHistory()
    : Suite("DecodedReservoir History")
    , iDequeuedJiffies(0)
    , iHistoryPointCount(0)
    , iStopAudioGeneration(false)
    , iStreamId(UINT_MAX)
{
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(200, 200);
    init.SetMsgSilenceCount(20);
    init.SetMsgDecodedStreamCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iReservoir = new DecodedAudioReservoir(kReservoirSize, kMaxStreams);
    memset(iBuf, 0xff, sizeof(iBuf));
}

SuiteReservoirHistory::~SuiteReservoirHistory()
{
    delete iReservoir;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteReservoirHistory::Test()
{
    static const TUint kPcmMsgCount = 15;
    iThread = new ThreadFunctor("RHPT", MakeFunctor(*this, &SuiteReservoirHistory::PullerThread));
    iThread->Start();
    iStartCalled = iNotifySizeCalled = false;
    ModeClockPullers clockPullers(this);
    iReservoir->Push(iMsgFactory->CreateMsgMode(Brn("ClockPullTest"), false, true, clockPullers, false, false));
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    MsgTrack* msgTrack = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    iReservoir->Push(msgTrack);
    MsgDecodedStream* msgStream = iMsgFactory->CreateMsgDecodedStream(100, 12, 16, 44100, 2, Brn("dummy"), 1LL<<40, 0, false, false, false, false, nullptr);
    iStreamId = msgStream->StreamInfo().StreamId();
    iSampleRate = msgStream->StreamInfo().SampleRate();
    iReservoir->Push(msgStream);
    TUint pcmMsgs = kPcmMsgCount;
    TUint64 trackOffset = 0;
    Brn audioBuf(iBuf, sizeof(iBuf));
    while (!iStopAudioGeneration) {
        MsgAudio* audio;
        if (pcmMsgs == 0) {
            TUint size = 400 * Jiffies::kPerMs;
            audio = iMsgFactory->CreateMsgSilence(size, kSampleRate, kBitDepth, kNumChannels);
            pcmMsgs = kPcmMsgCount;
        }
        else {
            audio = iMsgFactory->CreateMsgAudioPcm(audioBuf, kNumChannels, kSampleRate, kBitDepth, AudioDataEndian::Little, trackOffset);
            pcmMsgs--;
        }
        trackOffset += audio->Jiffies();
        iReservoir->Push(audio);
    }
    delete iThread;
    TEST(iStartCalled);
    TEST(iNotifySizeCalled);
}

void SuiteReservoirHistory::PullerThread()
{
    Thread::Sleep(200); /* We test below that history sizes are non-zero.  Give pushing
                           thread a chance to fill the reservoir to limit the chances
                           of it always being close to empty */
    while (!iStopAudioGeneration) {
        Msg* msg = iReservoir->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        Thread::Sleep(1);
    }

    // consume any remaining msgs in case pushing thread is blocked
    while (!iReservoir->IsEmpty()) {
        iReservoir->Pull()->RemoveRef();
    }
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgAudioPcm* aMsg)
{
    iDequeuedJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgSilence* aMsg)
{
    iDequeuedJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgBitRate* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}

Msg* SuiteReservoirHistory::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS(); // only MsgAudioPcm and MsgSilence expected in this test
    return nullptr;
}
void SuiteReservoirHistory::Start(TUint aNotificationFrequency)
{
    TEST(aNotificationFrequency == iReservoir->kUtilisationSamplePeriodJiffies);
    iStartCalled = true;
}

void SuiteReservoirHistory::Reset()
{
}

void SuiteReservoirHistory::NotifySize(TUint aJiffies)
{
    iHistoryPointCount++;
    TEST(aJiffies != 0);
    TEST(aJiffies < 0x40000000); // arbitrarily chosen value.  2^30 or ~17s of audio

    if (iHistoryPointCount == kTotalHistoryUpdates) {
        iStopAudioGeneration = true;
    }
    iNotifySizeCalled = true;
}

void SuiteReservoirHistory::Stop()
{
    ASSERTS(); // test only generates a single MsgMode so this shouldn't be called
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
    auto msg = iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1234567LL, 0, kStreamId, true/*seekable*/, false/*live*/, this/*stream handler*/);
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



void TestAudioReservoir()
{
    Runner runner("Decoded Audio Reservoir tests\n");
    runner.Add(new SuiteAudioReservoir());
    runner.Add(new SuiteReservoirHistory());
    runner.Add(new SuiteEncodedReservoir());
    runner.Run();
}
