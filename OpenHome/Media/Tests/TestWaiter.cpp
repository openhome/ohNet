#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Waiter.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <list>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteWaiter : public SuiteUnitTest, private IPipelineElementUpstream
                  , private IWaiterObserver, private IStreamHandler
                  , private IMsgProcessor
{
    static const TUint kRampDuration = Jiffies::kPerMs * 20;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteWaiter();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IWaiterObserver
    void PipelineWaiting(TBool aWaiting) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
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
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgDecodedStream
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void PullNext(EMsgType aExpectedMsg);
    Msg* CreateTrack();
    Msg* CreateEncodedStream();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();

    void TestWaitFromPlayingRampDown();
    void TestWaitFromPlayingNoRampDown();
    void TestPlayingFromWaitRampsUp();

    void TestMsgsPassWhilePlaying();
    void TestMsgsPassWhileWaitPending();
    void TestMsgsPassWhileWaiting();
    void TestAudioFlushedWhileWaiting();

    void TestWaitDuringWait();
    void TestWaitDuringRampingDown();
    void TestWaitDuringRampingUp();

    void TestMsgDecodedStreamDuringWaitAsserts();
    void TestMsgDecodedStreamDuringRampingDownAsserts();
    void TestMsgDecodedStreamCancelsWaiting();

    void TestWaitingStateOnMsgWait();

    void TestSilenceEndsRamp();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Waiter* iWaiter;
    ElementObserverSync* iEventCallback;
    EMsgType iLastPulledMsg;
    TBool iRampingDown;
    TBool iRampingUp;
    TBool iLiveStream;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastSubsample;
    TUint iNextStreamId;
    TUint iWaitingCount;
    TUint iWaitingTrueCount;
    TUint iWaitingFalseCount;
};

} // namespace Media
} // namespace OpenHome


SuiteWaiter::SuiteWaiter()
    : SuiteUnitTest("SuiteWaiter")
{
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitFromPlayingRampDown), "TestWaitFromPlayingRampDown");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitFromPlayingNoRampDown), "TestWaitFromPlayingNoRampDown");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestPlayingFromWaitRampsUp), "TestPlayingFromWaitRampsUp");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgsPassWhilePlaying), "TestMsgsPassWhilePlaying");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgsPassWhileWaitPending), "TestMsgsPassWhileWaitPending");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgsPassWhileWaiting), "TestMsgsPassWhileWaiting");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestAudioFlushedWhileWaiting), "TestAudioFlushedWhileWaiting");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitDuringWait), "TestWaitDuringWait");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitDuringRampingDown), "TestWaitDuringRampingDown");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitDuringRampingUp), "TestWaitDuringRampingUp");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgDecodedStreamDuringWaitAsserts), "TestMsgDecodedStreamkDuringWaitAsserts");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgDecodedStreamDuringRampingDownAsserts), "TestMsgDecodedStreamDuringRampingDownAsserts");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestMsgDecodedStreamCancelsWaiting), "TestMsgDecodedStreamCancelsWaiting");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestWaitingStateOnMsgWait), "TestWaitingStateOnMsgWait");
    AddTest(MakeFunctor(*this, &SuiteWaiter::TestSilenceEndsRamp), "TestSilenceEndsRamp");
}

void SuiteWaiter::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(5, 5);
    init.SetMsgSilenceCount(10);
    init.SetMsgDecodedStreamCount(2);
    init.SetMsgTrackCount(3);
    init.SetMsgEncodedStreamCount(3);
    init.SetMsgMetaTextCount(3);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iEventCallback = new ElementObserverSync();
    iWaiter = new Waiter(*iMsgFactory, *this, *this, *iEventCallback, kRampDuration);
    iRampingDown = iRampingUp = false;
    iLiveStream = false;
    iTrackOffset = 0;
    iJiffies = 0;
    iLastSubsample = 0xffffffff;
    iNextStreamId = 1;
    iWaitingCount = iWaitingTrueCount = iWaitingFalseCount = 0;
}

void SuiteWaiter::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iWaiter;
    delete iEventCallback;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteWaiter::Pull()
{
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

void SuiteWaiter::PipelineWaiting(TBool aWaiting)
{
    iWaitingCount++;
    if (aWaiting) {
        iWaitingTrueCount++;
    }
    else {
        iWaitingFalseCount++;
    }
}

EStreamPlay SuiteWaiter::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteWaiter::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteWaiter::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteWaiter::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/)
{
}

Msg* SuiteWaiter::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgSession* aMsg)
{
    iLastPulledMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteWaiter::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgAudioPcm* aMsg)
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

Msg* SuiteWaiter::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteWaiter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteWaiter::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteWaiter::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iWaiter->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}


Msg* SuiteWaiter::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteWaiter::CreateEncodedStream()
{
    return iMsgFactory->CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1<<21, ++iNextStreamId, true, iLiveStream, this);
}

Msg* SuiteWaiter::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, iLiveStream, nullptr);
}

Msg* SuiteWaiter::CreateAudio()
{
    static const TUint kDataBytes = 960;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteWaiter::TestWaitFromPlayingRampDown()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestWaitFromPlayingNoRampDown()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = false;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestPlayingFromWaitRampsUp()
{
    // First, put waiter into a waiting state.
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));


    // Waiter should come out of its waiting state on arrival of new audio.
    iRampingUp = true;
    iJiffies = 0;

    while (iRampingUp) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 2);
    TEST(iWaitingFalseCount == 1);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgAudioPcm); // Remainder of audio after ramping up.
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestMsgsPassWhilePlaying()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), true, false, nullptr, false, false));
    PullNext(EMsgMode);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSession());
    PullNext(EMsgSession);
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    PullNext(EMsgDrain);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(0));
    PullNext(EMsgDelay);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    PullNext(EMsgStreamInterrupted);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    PullNext(EMsgSilence);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestMsgsPassWhileWaitPending()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kFlushId = 2;
    static const TUint kWaitFlushId = 3;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    // Push some msgs down pipeline (except for MsgTrack and MsgDecodedStream
    // as they cancel the waiting, MsgAudioPcm and MsgSilence as they are
    // ramped down, and MsgWait as it shouldn't occur here) before the expected
    // MsgFlush.
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    PullNext(EMsgStreamInterrupted);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kFlushId));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestMsgsPassWhileWaiting()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kFlushId = 2;
    static const TUint kWaitFlushId = 3;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));

    // Push some msgs down pipeline (except for MsgTrack and MsgDecodedStream
    // as they cancel the waiting, MsgAudioPcm and MsgSilence as they are
    // ramped down, and MsgWait as it shouldn't occur here) before the expected
    // MsgFlush.
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kFlushId));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);
}

void SuiteWaiter::TestAudioFlushedWhileWaiting()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);

    // All audio before MsgFlush should be consumed
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(CreateAudio());

    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));

    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteWaiter::TestWaitDuringWait()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);

    // Calling Wait() after ramp down should not have any ill effects.
    iWaiter->Wait(kWaitFlushId, kRampDown);
    TEST(iWaitingCount == 2);
    TEST(iWaitingTrueCount == 2);

    // Already ramped down, so should expect a MsgHalt and MsgWait, rather than
    // more audio.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
}

void SuiteWaiter::TestWaitDuringRampingDown()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    // Calling Wait() while already waiting and ramping down.
    iWaiter->Wait(kWaitFlushId, kRampDown);
    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    // Should still have been in ramp down state in first Wait() and not yet
    // switched to waiting state, so should only reach waiting state after
    // second Wait().
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
}

void SuiteWaiter::TestWaitDuringRampingUp()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));

    // Waiter should come out of its waiting state on arrival of new audio.
    iRampingUp = true;
    iJiffies = 0;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm); // pull the MsgFlush through; should be in ERampingUp state


    // Calling Wait() after starting to ramp back up should cause a ramp back down.
    iWaiter->Wait(kWaitFlushId, kRampDown);


    iJiffies = 0;
    iRampingUp = false;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    //TEST(iJiffies == kRampDuration);
    // Test Waiter came out of waiting and went back into it.
    TEST(iWaitingCount == 3);
    TEST(iWaitingTrueCount == 2);
    TEST(iWaitingFalseCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
}

void SuiteWaiter::TestMsgDecodedStreamDuringWaitAsserts()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);

    // No MsgTrack is expected, so should ASSERT()
    iPendingMsgs.push_back(CreateDecodedStream());
    TEST_THROWS(PullNext(EMsgDecodedStream), AssertionFailed);
}

void SuiteWaiter::TestMsgDecodedStreamDuringRampingDownAsserts()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    // No MsgTrack is expected, so should ASSERT()
    iPendingMsgs.push_back(CreateDecodedStream());
    TEST_THROWS(PullNext(EMsgDecodedStream), AssertionFailed);
}

void SuiteWaiter::TestMsgDecodedStreamCancelsWaiting()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    while (iRampingDown) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));

    // Pull MsgDecodedStream and check audio comes through.
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    TEST(iWaitingCount == 1);   // pre-test state
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    TEST(iWaitingCount == 2);
    TEST(iWaitingFalseCount == 1);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}

void SuiteWaiter::TestWaitingStateOnMsgWait()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);

    // Send a MsgWait. Waiter should notify all IWaiterObservers that the
    // pipeline is entering a waiting state.

    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);

    // Some msgs should pass through while in a Songcast waiting state.
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    PullNext(EMsgMetaText);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(2));
    PullNext(EMsgFlush);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);

    // Send audio down. Waiter should notify all IWaiterObservers that the
    // pipeline is no longer in a waiting state (and audio should pass through).
    TEST(iWaitingCount == 1);   // check pre-test state is as expected (i.e.,
                                // that none of the msgs above changed the state)
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iWaitingCount == 2);
    TEST(iWaitingFalseCount == 1);

    // Waiting state again
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    PullNext(EMsgWait);
    TEST(iWaitingCount == 3);
    TEST(iWaitingTrueCount == 2);

    // Send track down.  Waiter should not change state
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    TEST(iWaitingCount == 3);
    TEST(iWaitingTrueCount == 2);

    // Send MsgDecodedStream down.  Waiter should notify all IWaiterObservers that the
    // pipeline is no longer in a waiting state
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    TEST(iWaitingCount == 4);
    TEST(iWaitingFalseCount == 2);
}


void SuiteWaiter::TestSilenceEndsRamp()
{
    iPendingMsgs.push_back(CreateTrack());
    PullNext(EMsgTrack);
    iPendingMsgs.push_back(CreateEncodedStream());
    PullNext(EMsgEncodedStream);
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    static const TUint kWaitFlushId = 2;
    static const TBool kRampDown = true;
    TEST(iWaitingCount == 0);
    TEST(iWaitingTrueCount == 0);
    iWaiter->Wait(kWaitFlushId, kRampDown);

    iJiffies = 0;
    iRampingDown = true;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
    TEST(iRampingDown);
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs));
    iRampingDown = false;
    // MsgHalt and MsgWait are created and passed on after ramping down.
    PullNext(EMsgHalt);
    TEST(iWaitingCount == 1);
    TEST(iWaitingTrueCount == 1);
    TEST(iWaitingFalseCount == 0);
    PullNext(EMsgWait);
    // Expected MsgFlush should be consumed
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(kWaitFlushId));

    iRampingUp = false;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs));
    PullNext(EMsgSilence);
    TEST(iWaitingCount == 2);
    TEST(iWaitingTrueCount == 1);
    TEST(iWaitingFalseCount == 1);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}



void TestWaiter()
{
    Runner runner("Waiter tests\n");
    runner.Add(new SuiteWaiter());
    runner.Run();
}
