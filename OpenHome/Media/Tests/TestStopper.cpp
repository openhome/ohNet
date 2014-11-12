#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Private/Globals.h>

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
public:
    SuiteStopper();
    ~SuiteStopper();
private: // from SuiteUnitTest
    void Setup();
    void TearDown();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IStopperObserver
    void PipelinePaused();
    void PipelineStopped();
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgDecodedStream
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
    void TestHaltedThread();
    void TestHalted();
    void TestMsgsPassWhilePlaying();
    void TestPlayFromStoppedNoRampUp();
    void TestPauseRamps();
    void TestInterruptRamps();
    void TestPauseFromStoppedIgnored();
    void TestOkToPlayCalledOnceForLiveStream();
    void TestOkToPlayCalledOnceForNonLiveStream();
    void TestStopFromPlay();
    void TestPlayStopPlayInterruptsRampDown();
    void TestPlayNoFlushes();
    void TestPlayLaterStops();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Stopper* iStopper;
    EMsgType iLastPulledMsg;
    TBool iRampingDown;
    TBool iRampingUp;
    TBool iLiveStream;
    TUint iTrackId;
    TUint iStreamId;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastSubsample;
    TUint iNextTrackId;
    TUint iNextStreamId;
    TUint iPausedCount;
    TUint iStoppedCount;
    TUint iOkToPlayCount;
    EStreamPlay iNextCanPlay;
    Semaphore iSemHalted;
    ThreadFunctor* iThreadHalted;
};

} // namespace Media
} // namespace OpenHome


SuiteStopper::SuiteStopper()
    : SuiteUnitTest("Stopper")
    , iSemHalted("TSTP", 0)
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    iMsgFactory = new MsgFactory(iInfoAggregator, 0, 0, 5, 5, 10, 1, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1);
    iThreadHalted = new ThreadFunctor("StoppedChecker", MakeFunctor(*this, &SuiteStopper::TestHaltedThread));
    iThreadHalted->Start();

    AddTest(MakeFunctor(*this, &SuiteStopper::TestMsgsPassWhilePlaying), "TestMsgsPassWhilePlaying");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayFromStoppedNoRampUp), "TestPlayFromStoppedNoRampUp");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPauseRamps), "TestPauseRamps");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestInterruptRamps), "TestInterruptRamps");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPauseFromStoppedIgnored), "TestPauseFromStoppedIgnored");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestOkToPlayCalledOnceForLiveStream), "TestOkToPlayCalledOnceForLiveStream");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestOkToPlayCalledOnceForNonLiveStream), "TestOkToPlayCalledOnceForNonLiveStream");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestStopFromPlay), "TestStopFromPlay");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayStopPlayInterruptsRampDown), "TestPlayStopPlayInterruptsRampDown");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayNoFlushes), "TestPlayNoFlushes");
    AddTest(MakeFunctor(*this, &SuiteStopper::TestPlayLaterStops), "TestPlayLaterStops");
}

SuiteStopper::~SuiteStopper()
{
    delete iThreadHalted;
    delete iMsgFactory;
    delete iTrackFactory;
}

void SuiteStopper::Setup()
{
    iStopper = new Stopper(*iMsgFactory, *this, *this, kRampDuration);
    iTrackId = iStreamId = UINT_MAX;
    iTrackOffset = 0;
    iRampingDown = iRampingUp = false;
    iLiveStream = false;
    iLastSubsample = 0xffffff;
    iNextTrackId = 1;
    iNextStreamId = 1;
    iJiffies = 0;
    iPausedCount = iStoppedCount = iOkToPlayCount = 0;
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

EStreamPlay SuiteStopper::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    iOkToPlayCount++;
    return iNextCanPlay;
}

TUint SuiteStopper::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteStopper::TryStop(TUint aTrackId, TUint aStreamId)
{
    if (aTrackId == iTrackId && aStreamId == iStreamId) {
        return kExpectedFlushId;
    }
    return MsgFlush::kIdInvalid;
}

TBool SuiteStopper::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

void SuiteStopper::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}

Msg* SuiteStopper::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgSession* aMsg)
{
    iLastPulledMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteStopper::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    iTrackId = aMsg->IdPipeline();
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
    return NULL;
}

Msg* SuiteStopper::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
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

Msg* SuiteStopper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
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
    return NULL;
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
    Msg* msg = iMsgFactory->CreateMsgTrack(*track, iNextTrackId++);
    track->RemoveRef();
    return msg;
}

Msg* SuiteStopper::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, ++iNextStreamId, true, iLiveStream, this);
}

Msg* SuiteStopper::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, iLiveStream, NULL);
}

Msg* SuiteStopper::CreateAudio()
{
    static const TUint kDataBytes = 960;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
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
        iStopper->Play();
    }
    TEST(pullTimeout);
    iSemHalted.Wait();
}

void SuiteStopper::TestMsgsPassWhilePlaying()
{
    iStopper->Play();
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), true, true, NULL));
    PullNext(EMsgMode);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSession());
    PullNext(EMsgSession);
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(0));
    PullNext(EMsgDelay);
    iPendingMsgs.push_back(CreateEncodedStream()); // not passed on
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    PullNext(EMsgSilence);
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
    TEST(iJiffies == kRampDuration);
    iJiffies = 0;
    iRampingUp = true;
    PullNext(EMsgHalt);
    TestHalted();

    // check that calling Play() now ramps up
    iStopper->Play();
    while (iRampingUp) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iPausedCount == 1);
    TEST(iStoppedCount == 0);
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

    iStopper->Play();
    iRampingDown = false;
    iRampingUp = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(!iRampingUp);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);

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

void SuiteStopper::TestPauseFromStoppedIgnored()
{
    iStopper->BeginPause();
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
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
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    TEST(iJiffies == kRampDuration);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt(5));
    PullNext(EMsgHalt);
    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 1);
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
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    iNextCanPlay = ePlayYes;
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream()); // not passed on
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    TEST(iPausedCount == 0);
    TEST(iStoppedCount == 0);
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
    TestHalted();
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}



void TestStopper()
{
    Runner runner("Stopper tests\n");
    runner.Add(new SuiteStopper());
    runner.Run();
}
