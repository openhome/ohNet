#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteStopper : public SuiteUnitTest, private IPipelineElementUpstream, private IStopperObserver, private IStreamHandler, private IMsgProcessor
{
    static const TUint kRampDuration = Jiffies::kPerMs * 20;
    static const TUint kExpectedFlushId = 5;
    static const TUint kExpectedSeekSeconds = 51;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const TUint kBitDepth = 24;
    static const TUint kDataBytes = 960;
    static const TUint kJiffiesPerMsg;
public:
    SuiteStopper();
    ~SuiteStopper();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IStopperObserver
    void PipelinePaused() override;
    void PipelineStopped() override;
    void PipelinePlaying() override;
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
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void PullNext();
    void PullNext(EMsgType aExpectedMsg);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    Msg* CreateSilence(TUint aJiffies);
    void TestHaltedThread();
    void TestHalted();
    void TestMsgsPassWhilePlaying();
    void TestPlayFromStoppedNoRampUp();
    void TestPauseRamps();
    void TestInterruptRamps();
    void TestSilenceEndsRamp();
    void TestPauseFromStoppedIgnored();
    void TestOkToPlayCalledOnceForLiveStream();
    void TestOkToPlayCalledOnceForNonLiveStream();
    void TestStopFromPlay();
    void TestPlayStopPlayInterruptsRampDown();
    void TestPlayNoFlushes();
    void TestPlayLaterStops();
    void TestPlayPausePlayWithRamp();
    void TestPlayPausePlayNoRamp();
    void TestQuitMultipleTracksPending();
    void TestPauseWhileStarving();
    void TestStopWhileStarving();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Stopper* iStopper;
    ElementObserverSync* iEventCallback;
    EMsgType iLastPulledMsg;
    TBool iRampingDown;
    TBool iRampingUp;
    TBool iMuted;
    TBool iLiveStream;
    TUint iStreamId;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastSubsample;
    TUint iNextStreamId;
    TUint iPausedCount;
    TUint iStoppedCount;
    TUint iPlayingCount;
    TUint iOkToPlayCount;
    EStreamPlay iNextCanPlay;
    Semaphore iSemHalted;
    ThreadFunctor* iThreadHalted;
};

} // namespace Media
} // namespace OpenHome


const TUint SuiteStopper::kJiffiesPerMsg = kDataBytes/kNumChannels/(kBitDepth/8) * Jiffies::PerSample(kSampleRate);

SuiteStopper::SuiteStopper()
    : SuiteUnitTest("Stopper")
    , iSemHalted("TSTP", 0)
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(5, 5);
    init.SetMsgSilenceCount(10);
    init.SetMsgDecodedStreamCount(2);
    init.SetMsgTrackCount(2);
    init.SetMsgEncodedStreamCount(2);
    init.SetMsgMetaTextCount(2);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iThreadHalted = new ThreadFunctor("StoppedChecker", MakeFunctor(*this, &SuiteStopper::TestHaltedThread));
    iThreadHalted->Start();

    AddTest(MakeFunctor(*this, &SuiteStopper::TestMsgsPassWhilePlaying), "TestMsgsPassWhilePlaying");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayFromStoppedNoRampUp), "TestPlayFromStoppedNoRampUp");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPauseRamps), "TestPauseRamps");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestInterruptRamps), "TestInterruptRamps");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestSilenceEndsRamp), "TestSilenceEndsRamp");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPauseFromStoppedIgnored), "TestPauseFromStoppedIgnored");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestOkToPlayCalledOnceForLiveStream), "TestOkToPlayCalledOnceForLiveStream");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestOkToPlayCalledOnceForNonLiveStream), "TestOkToPlayCalledOnceForNonLiveStream");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestStopFromPlay), "TestStopFromPlay");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayStopPlayInterruptsRampDown), "TestPlayStopPlayInterruptsRampDown");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayNoFlushes), "TestPlayNoFlushes");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayLaterStops), "TestPlayLaterStops");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayPausePlayWithRamp), "TestPlayPausePlayWithRamp");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayPausePlayNoRamp), "TestPlayPausePlayNoRamp");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestQuitMultipleTracksPending), "TestQuitMultipleTracksPending");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPauseWhileStarving), "TestPauseWhileStarving");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestStopWhileStarving), "TestStopWhileStarving");
}

SuiteStopper::~SuiteStopper()
{
    delete iThreadHalted;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteStopper::Setup()
{
    iEventCallback = new ElementObserverSync();
    iStopper = new Stopper(*iMsgFactory, *this, *this, *iEventCallback, kRampDuration);
    iStreamId = UINT_MAX;
    iTrackOffset = 0;
    iRampingDown = iRampingUp = iMuted = false;
    iLiveStream = false;
    iLastSubsample = 0xffffff;
    iNextStreamId = 1;
    iJiffies = 0;
    iPausedCount = iStoppedCount = iPlayingCount = iOkToPlayCount = 0;
    iNextCanPlay = ePlayYes;
    iSemHalted.Clear();
}

void SuiteStopper::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iStopper;
    delete iEventCallback;
}

Msg* SuiteStopper::Pull()
{
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

void SuiteStopper::PipelinePaused()
{
    iPausedCount++;
}

void SuiteStopper::PipelineStopped()
{
    iStoppedCount++;
}

void SuiteStopper::PipelinePlaying()
{
    iPlayingCount++;
}

EStreamPlay SuiteStopper::OkToPlay(TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return iNextCanPlay;
}

TUint SuiteStopper::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteStopper::TryStop(TUint aStreamId)
{
    if (aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    return MsgFlush::kIdInvalid;
}

void SuiteStopper::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}

Msg* SuiteStopper::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteStopper::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgBitRate* aMsg)
{
    iLastPulledMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufTest pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
    ASSERT(buf.Bytes() >= 6);
    const TByte* ptr = buf.Ptr();
    const TUint bytes = buf.Bytes();
    const TUint firstSubsample = (ptr[0]<<16) | (ptr[1]<<8) | ptr[2];

    if (iRampingDown) {
        ASSERT(!iRampingUp);
    }
    
    if (iRampingDown) {
        TEST(firstSubsample <= iLastSubsample);
    }
    else if (iRampingUp) {
        TEST(firstSubsample >= iLastSubsample);
    }
    else if (iMuted) {
        TEST(firstSubsample == iLastSubsample);
        TEST(firstSubsample == 0);
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }
    iLastSubsample = (ptr[bytes-3]<<16) | (ptr[bytes-2]<<8) | ptr[bytes-1];
    if (iRampingDown) {
        TEST(iLastSubsample < firstSubsample);
        iRampingDown = (iLastSubsample > 0);
    }
    else if (iRampingUp) {
        TEST(iLastSubsample > firstSubsample);
        iRampingUp = (iLastSubsample < 0x7f7f7e); // FIXME - see #830
    }
    else if (iMuted) {
        TEST(iLastSubsample == firstSubsample);
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }

    return playable;
}

Msg* SuiteStopper::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteStopper::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteStopper::PullNext()
{
    Msg* msg = iStopper->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteStopper::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iStopper->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteStopper::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteStopper::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, 0, ++iNextStreamId, true, iLiveStream, this);
}

Msg* SuiteStopper::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, iLiveStream, false, nullptr);
}

Msg* SuiteStopper::CreateAudio()
{
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, kBitDepth, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteStopper::CreateSilence(TUint aJiffies)
{
    TUint jiffies = aJiffies;
    return iMsgFactory->CreateMsgSilence(jiffies, kSampleRate, kBitDepth, kNumChannels);
}

void SuiteStopper::TestHaltedThread()
{
    for (;;) {
        iThreadHalted->Wait();
        Msg* msg = iStopper->Pull();
        msg = msg->Process(*this);
        msg->RemoveRef();
        iSemHalted.Signal();
    }
}

void SuiteStopper::TestHalted()
{
    TBool pullTimeout = false;
    iThreadHalted->Signal();
    try {
        iSemHalted.Wait(50);
    }
    catch (Timeout&) {
        pullTimeout = true;
        iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
        iStopper->Play();
    }
    TEST(pullTimeout);
    iSemHalted.Wait();
}

void SuiteStopper::TestMsgsPassWhilePlaying()
{
    iStopper->Play();
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, ModeClockPullers(), false, false));
    PullNext(EMsgMode);
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    PullNext(EMsgDrain);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(0));
    PullNext(EMsgDelay);
    iPendingMsgs.push_back(CreateEncodedStream()); // not passed on
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    PullNext(EMsgStreamInterrupted);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iPendingMsgs.push_back(CreateSilence(Jiffies::kPerMs * 3));
    PullNext(EMsgSilence);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgBitRate(100));
    PullNext(EMsgBitRate);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2)); // not passed on
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteStopper::TestPlayFromStoppedNoRampUp()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    for (TUint i=0; i<10; i++) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
}

void SuiteStopper::TestPauseRamps()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iStopper->BeginPause();
    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    TEST(iJiffies == kRampDuration);
    iMuted = true;
    do {
        PullNext();
    } while (iLastPulledMsg != EMsgHalt);
    TestHalted();
    iJiffies = 0;

    // check that calling Play() now ramps up
    iRampingUp = true;
    iStopper->Play();
    while (iRampingUp) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 2);
    TEST(iJiffies == kRampDuration);
}

void SuiteStopper::TestInterruptRamps()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iStopper->BeginPause();
    iRampingDown = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);

    iStopper->Play();
    iRampingDown = false;
    iRampingUp = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(!iRampingUp);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iStopper->BeginPause();
    iRampingDown = true;
    iRampingUp = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iRampingDown = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iStopper->BeginPause();
    iRampingDown = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iRampingDown = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}

void SuiteStopper::TestSilenceEndsRamp()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iStopper->BeginPause();
    iRampingDown = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    iPendingMsgs.push_back(CreateSilence(Jiffies::kPerMs));
    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);

    iStopper->Play();
    iRampingDown = false;
    iRampingUp = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 2);
    iPendingMsgs.push_back(CreateSilence(Jiffies::kPerMs));
    PullNext(EMsgSilence);
    iRampingUp = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}

void SuiteStopper::TestPauseFromStoppedIgnored()
{
    iStopper->BeginPause();
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 0);
}

void SuiteStopper::TestOkToPlayCalledOnceForLiveStream()
{
    TEST(iOkToPlayCount == 0);
    iStopper->Play();
    iLiveStream = true;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateDecodedStream()); // multiple DecodedStream possible when seeking
    PullNext(EMsgDecodedStream);
    TEST(iOkToPlayCount == 1);
}

void SuiteStopper::TestOkToPlayCalledOnceForNonLiveStream()
{
    TEST(iOkToPlayCount == 0);
    iStopper->Play();
    iLiveStream = false;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateDecodedStream()); // multiple DecodedStream possible when seeking
    PullNext(EMsgDecodedStream);
    TEST(iOkToPlayCount == 1);
}

void SuiteStopper::TestStopFromPlay()
{
    iStopper->Play();
    iLiveStream = false;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iStopper->BeginStop(5);
    iRampingDown = true;
    iJiffies = 0;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    iMuted = true;
    do {
        PullNext();
    } while (iLastPulledMsg != EMsgHalt);
    iMuted = false;
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(CreateSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt(5));
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 1);
    TEST(iPlayingCount == 1);
    TEST(iStopper->iQueue.IsEmpty());
    iPendingMsgs.push_back(CreateTrack());
    TestHalted();
}

void SuiteStopper::TestPlayStopPlayInterruptsRampDown()
{
    iStopper->Play();
    iLiveStream = false;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iStopper->BeginStop(5);
    iRampingDown = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);

    iStopper->Play();
    iRampingDown = false;
    iRampingUp = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(!iRampingUp);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
}

void SuiteStopper::TestPlayNoFlushes()
{
    iNextCanPlay = ePlayNo;
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(CreateSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    PullNext(EMsgDrain);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    iNextCanPlay = ePlayYes;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream()); // not passed on
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    PullNext(EMsgDrain);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted()); // not passed on
    PullNext(EMsgStreamInterrupted);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
}

void SuiteStopper::TestPlayLaterStops()
{
    iNextCanPlay = ePlayLater;
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgDecodedStream);
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 1);
    TEST(iPlayingCount == 1);
    TestHalted();
}

void SuiteStopper::TestPlayPausePlayWithRamp()
{
    static const TUint kMsgPullCount = 3;
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iJiffies = 0;
    iStopper->BeginPause();
    iRampingDown = true;
    for (TUint i=0; i<kMsgPullCount; i++) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iRampingDown); // should still be ramping down
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    TEST(iJiffies == kJiffiesPerMsg*kMsgPullCount);

    // Call Play(). Should immediately ramp up without completing ramp down.
    iJiffies = 0;
    iStopper->Play();
    iRampingDown = false;
    iRampingUp = true;
    for (TUint i=0; i<kMsgPullCount; i++) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(!iRampingUp);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    TEST(iJiffies == kJiffiesPerMsg*kMsgPullCount);
}

void SuiteStopper::TestPlayPausePlayNoRamp()
{
    static const TUint kMsgPullCount = 3;
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iJiffies = 0;
    // Call BeginPause() followed immediately by Play().
    // No ramping should occur.
    iStopper->BeginPause();
    iStopper->Play();
    iRampingDown = false;
    iRampingUp = false;
    // Pull a few msgs to check no ramping has occurred.
    for (TUint i=0; i<kMsgPullCount; i++) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(!iRampingDown);
    TEST(!iRampingUp);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == 1);
    TEST(iJiffies == kJiffiesPerMsg*kMsgPullCount);
}

void SuiteStopper::TestQuitMultipleTracksPending()
{
    // Queue up some tracks, then call Stopper::Quit().
    // Attempt to pull tracks through. All msgs, apart from:
    // - MsgTrack
    // - MsgQuit
    // should be discarded.
    iStopper->Play();

    // Track 1.
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());

    // Track 2.
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());

    // Quit msg.
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());

    iStopper->Quit();

    PullNext(EMsgTrack);
    PullNext(EMsgTrack);
    PullNext(EMsgQuit);
    TEST(iPendingMsgs.size() == 0);
}

void SuiteStopper::TestPauseWhileStarving()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iStopper->NotifyStarving(Brx::Empty(), iNextStreamId, true);
    TEST(iPausedCount == 0);
    const TUint playingCount = iPlayingCount;
    iStopper->BeginPause();
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
    TEST(iPlayingCount == playingCount);
}

void SuiteStopper::TestStopWhileStarving()
{
    iStopper->Play();
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iStopper->NotifyStarving(Brx::Empty(), iNextStreamId, true);
    TEST(iPausedCount == 0);
    const TUint playingCount = iPlayingCount;
    iStopper->BeginStop(5);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 1);
    TEST(iPlayingCount == playingCount);
}



void TestStopper()
{
    Runner runner("Stopper tests\n");
    runner.Add(new SuiteStopper());
    runner.Run();
}
