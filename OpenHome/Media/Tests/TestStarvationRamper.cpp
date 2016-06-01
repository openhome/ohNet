#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/StarvationRamper.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteStarvationRamper : public SuiteUnitTest
                            , private IPipelineElementUpstream
                            , private IMsgProcessor
                            , private IStreamHandler
                            , private IStarvationRamperObserver
{
    static const TUint kMaxAudioBuffer = Jiffies::kPerMs * 10;
    static const TUint kRampUpDuration = Jiffies::kPerMs * 50;
    static const TUint kExpectedFlushId = 5;
    static const TUint kSampleRateDefault = 48000;
    static const TUint kBitDepthDefault = 16;
    static const TUint kNumChannels = 2;
    static const TUint kAudioPcmBytesDefault = 960; // 5ms of 48k, 16-bit stereo
    static const Brn kMode;
public:
    SuiteStarvationRamper();
    ~SuiteStarvationRamper();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
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
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private: // from IStarvationRamperObserver
    void NotifyStarvationRamperBuffering(TBool aBuffering) override;
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
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
private:
    void AddPending(Msg* aMsg);
    void PullNext(TBool aWait=true);
    void PullNext(EMsgType aExpectedMsg, TBool aWait=true);
    Msg* CreateTrack();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    void Quit();
private:
    void TestMsgsPassWhenRunning();
    void TestBlocksWhenHasMaxAudio();
    void TestNoRampAroundHalt();
    void TestRampsAroundStarvation();
    void TestNotifyStarvingAroundStarvation();
    void TestReportsBuffering();
    void TestAllSampleRates();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    StarvationRamper* iStarvationRamper;
    ElementObserverSync* iEventCallback;
    Mutex iPendingMsgLock;
    Semaphore iMsgAvailable;
    EMsgType iLastPulledMsg;
    TBool iRampingUp;
    TBool iRampingDown;
    TBool iBuffering;
    TUint iStreamId;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastRampPos;
    TUint iNextStreamId;
    Bws<AudioData::kMaxBytes> iPcmData;
    TBool iStarving;
    TUint iStarvingStreamId;
    TUint iSampleRate;
    TUint iBitDepth;
};

} // namespace Media
} // namespace OpenHome


const Brn SuiteStarvationRamper::kMode("DummyMode");

SuiteStarvationRamper::SuiteStarvationRamper()
    : SuiteUnitTest("StarvationRamper")
    , iPendingMsgLock("SSR1")
    , iMsgAvailable("SSR2", 0)
{
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestMsgsPassWhenRunning), "TestMsgsPassWhenRunning");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestBlocksWhenHasMaxAudio), "TestBlocksWhenHasMaxAudio");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestNoRampAroundHalt), "TestNoRampAroundHalt");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestRampsAroundStarvation), "TestRampsAroundStarvation");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestNotifyStarvingAroundStarvation), "TestNotifyStarvingAroundStarvation");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestReportsBuffering), "TestReportsBuffering");
    AddTest(MakeFunctor(*this, &SuiteStarvationRamper::TestAllSampleRates), "TestAllSampleRates");

    // audio data with left=0x7f, right=0x00
    iPcmData.SetBytes(kAudioPcmBytesDefault);
    TByte* p = const_cast<TByte*>(iPcmData.Ptr());
    const TUint samples = iPcmData.Bytes() / ((kBitDepthDefault/8) * kNumChannels);
    for (TUint i=0; i<samples; i++) {
        *p++ = 0x7f;
        *p++ = 0x7f;
        *p++ = 0x00;
        *p++ = 0x00;
    }
}

SuiteStarvationRamper::~SuiteStarvationRamper()
{
}

void SuiteStarvationRamper::Setup()
{
    iStreamId = UINT_MAX;
    iTrackOffset = 0;
    iJiffies = 0;
    iRampingUp = iRampingDown = iBuffering = false;
    iLastRampPos = Ramp::kMax;
    iNextStreamId = 1;
    iStarving = false;
    iStarvingStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iSampleRate = kSampleRateDefault;
    iBitDepth = kBitDepthDefault;

    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    iEventCallback = new ElementObserverSync();
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(52, 50);
    init.SetMsgSilenceCount(20);
    init.SetMsgDecodedStreamCount(3);
    init.SetMsgTrackCount(3);
    init.SetMsgEncodedStreamCount(3);
    init.SetMsgMetaTextCount(3);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    init.SetMsgModeCount(2);
    init.SetMsgWaitCount(2);
    init.SetMsgDelayCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iStarvationRamper = new StarvationRamper(*iMsgFactory, *this, *this, *iEventCallback,
                                             kMaxAudioBuffer, kPriorityHigh, kRampUpDuration, 10);
    (void)iMsgAvailable.Clear();
}

void SuiteStarvationRamper::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iStarvationRamper;
    delete iEventCallback;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteStarvationRamper::Pull()
{
    iMsgAvailable.Wait();
    AutoMutex _(iPendingMsgLock);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    const Media::Ramp& ramp = aMsg->Ramp();
    if (iRampingDown) {
        TEST(ramp.Direction() == Ramp::EDown);
        TEST(ramp.Start() == iLastRampPos);
        if (ramp.End() == Ramp::kMin) {
            iRampingDown = false;
        }
    }
    else if (iRampingUp) {
        TEST(ramp.Direction() == Ramp::EUp);
        TEST(ramp.Start() == iLastRampPos);
        if (ramp.End() == Ramp::kMax) {
            iRampingUp = false;
        }
    }
    else {
        TEST(ramp.Direction() == Ramp::ENone);
    }
    iLastRampPos = ramp.End();
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteStarvationRamper::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

EStreamPlay SuiteStarvationRamper::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint SuiteStarvationRamper::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteStarvationRamper::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint SuiteStarvationRamper::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void SuiteStarvationRamper::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    TEST(aMode == kMode);
    iStarving = aStarving;
    iStarvingStreamId = aStreamId;
}

void SuiteStarvationRamper::NotifyStarvationRamperBuffering(TBool aBuffering)
{
    iBuffering = aBuffering;
}

void SuiteStarvationRamper::AddPending(Msg* aMsg)
{
    iPendingMsgLock.Wait();
    iPendingMsgs.push_back(aMsg);
    iPendingMsgLock.Signal();
    iMsgAvailable.Signal();
}

void SuiteStarvationRamper::PullNext(TBool aWait)
{
    if (aWait && !iRampingDown) {
        // no ramping => we expect a msg to be available
        // poll StarvationRamper state until it has pulled something
        TInt retries = 1000;
        while (iStarvationRamper->IsEmpty() && retries-- > 0) {
            Thread::Sleep(10);
        }
    }
    Msg* msg = iStarvationRamper->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteStarvationRamper::PullNext(EMsgType aExpectedMsg, TBool aWait)
{
    PullNext(aWait);
    if (iLastPulledMsg != aExpectedMsg) {
        static const TChar* types[] ={
            "None"
            , "MsgMode"
            , "MsgTrack"
            , "MsgDrain"
            , "MsgDelay"
            , "MsgEncodedStream"
            , "MsgMetaText"
            , "MsgStreamInterrupted"
            , "MsgDecodedStream"
            , "MsgAudioPcm"
            , "MsgSilence"
            , "MsgHalt"
            , "MsgFlush"
            , "MsgWait"
            , "MsgQuit" };
        Print("Expected %s, got %s\n", types[aExpectedMsg], types[iLastPulledMsg]);
    }
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteStarvationRamper::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteStarvationRamper::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, iBitDepth, iSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, false, false, this);
}

Msg* SuiteStarvationRamper::CreateAudio()
{
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(iPcmData, kNumChannels, iSampleRate, iBitDepth, AudioDataEndian::Big, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteStarvationRamper::Quit()
{
    iRampingDown = true; // if Pull() is called before StarvationRamper pulls the Halt below, it'll start a ramp down
    AddPending(iMsgFactory->CreateMsgHalt());
    AddPending(iMsgFactory->CreateMsgQuit());
    do {
        PullNext();
    } while (iLastPulledMsg != EMsgQuit);
}

void SuiteStarvationRamper::TestMsgsPassWhenRunning()
{
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(iMsgFactory->CreateMsgDrain(Functor()));
    AddPending(CreateDecodedStream());
    AddPending(CreateAudio());

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDrain);
    PullNext(EMsgDecodedStream);
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TUint size = Jiffies::kPerMs * 3;
    AddPending(iMsgFactory->CreateMsgSilence(size, 44100, 8, 2));
    do {
        PullNext(EMsgSilence);
    } while (!iStarvationRamper->IsEmpty());
    AddPending(iMsgFactory->CreateMsgHalt());
    AddPending(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgHalt);
    PullNext(EMsgQuit);
}

void SuiteStarvationRamper::TestBlocksWhenHasMaxAudio()
{
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);

    do {
        AddPending(CreateAudio());
    } while (iTrackOffset < kMaxAudioBuffer);
    AddPending(CreateAudio());

    // wait for expected number of pending msgs to be pulled
    TInt retries = 100;
    while (retries-- > 0) {
        if (iPendingMsgs.size() == 1) { // 1 == EMsgAudioPcm that doesn't yet fit into SR
            break;
        }
        ASSERT(retries != 0);
        Thread::Sleep(10);
    }
    
    // ...now wait long enough for pending audio to be pulled if SR is running
    Thread::Sleep(100); 
    TEST(iPendingMsgs.size() == 1);
    
    do {
        PullNext(EMsgAudioPcm);
    } while (iPendingMsgs.size() != 0 || !iStarvationRamper->IsEmpty());
    AddPending(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteStarvationRamper::TestNoRampAroundHalt()
{
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    AddPending(CreateAudio());
    AddPending(CreateAudio());
    AddPending(iMsgFactory->CreateMsgHalt());
    ASSERT(!iRampingDown);
    ASSERT(!iRampingUp);

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    do {
        PullNext(EMsgAudioPcm);
    } while (iJiffies < iTrackOffset);
    PullNext(EMsgHalt);
    AddPending(CreateAudio());
    AddPending(CreateAudio());
    AddPending(iMsgFactory->CreateMsgQuit());
    do {
        PullNext(EMsgAudioPcm);
    } while (iJiffies < iTrackOffset);
    PullNext(EMsgQuit);
}

void SuiteStarvationRamper::TestRampsAroundStarvation()
{
    // ramps down after > kMaxAudioBuffer of prior audio, ramp down takes StarvationRamper::kRampDownJiffies
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    do {
        AddPending(CreateAudio());
    } while (iTrackOffset < StarvationRamper::kTrainingJiffies);

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    do {
        PullNext(EMsgAudioPcm);
    } while (iJiffies < iTrackOffset);
    iRampingDown = true;
    iJiffies = 0;
    while (iRampingDown) {
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == StarvationRamper::kRampDownJiffies);
    PullNext(EMsgHalt, false);
    TEST(iStarvationRamper->iState == StarvationRamper::State::RampingUp);

    // ramps up once audio is available, ramp up takes kRampUpDuration
    iRampingUp = true;
    iJiffies = 0;
    TUint64 trackOffsetStart = iTrackOffset;
    do {
        AddPending(CreateAudio());
    } while (iTrackOffset - trackOffsetStart < kRampUpDuration);
    while (iRampingUp) {
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampUpDuration);
    TEST(iStarvationRamper->iState == StarvationRamper::State::Running);

    // clear any split msg at the end of the ramp up
    if (!iStarvationRamper->IsEmpty()) {
        PullNext(EMsgAudioPcm);
    }

    // ramps down after < kMaxAudioBuffer of prior audio, ramp down takes StarvationRamper::kRampDownJiffies
    AddPending(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    AddPending(CreateAudio());
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    iRampingDown = true;
    iJiffies = 0;
    while (iRampingDown) {
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == StarvationRamper::kRampDownJiffies);
    PullNext(EMsgHalt, false);
    TEST(iStarvationRamper->iState == StarvationRamper::State::RampingUp);

    Quit();
}

void SuiteStarvationRamper::TestNotifyStarvingAroundStarvation()
{
    TEST(!iStarving);
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iStarving);
    AddPending(CreateAudio());
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    iRampingDown = true;
    PullNext(EMsgAudioPcm);
    TEST(iStarving);
    while (iRampingDown) {
        PullNext(EMsgAudioPcm);
    }
    TEST(iStarving);
    PullNext(EMsgHalt, false);

    iRampingUp = true;
    AddPending(CreateAudio());
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TEST(!iStarving);

    Quit();
}

void SuiteStarvationRamper::TestReportsBuffering()
{
    TEST(iBuffering);
    AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iBuffering);
    PullNext(EMsgTrack);
    TEST(iBuffering);
    PullNext(EMsgDecodedStream);
    TEST(iBuffering);
    AddPending(CreateAudio());
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TEST(!iBuffering);
    iRampingDown = true;
    while (iRampingDown) {
        PullNext(EMsgAudioPcm);
        TEST(iBuffering);
    }
    PullNext(EMsgHalt, false);
    AddPending(CreateAudio());
    iRampingUp = true;
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TEST(!iBuffering);
    iRampingUp = false;
    iRampingDown = true;
    PullNext(EMsgAudioPcm);
    TEST(iBuffering);

    AddPending(CreateTrack());
    do {
        PullNext();
    } while (iLastPulledMsg != EMsgTrack);
    iRampingDown = false;
    TEST(iBuffering);
    AddPending(CreateDecodedStream());
    PullNext(EMsgDecodedStream);
    TEST(iBuffering);
    AddPending(CreateAudio());
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TEST(!iBuffering);

    AddPending(CreateTrack());
    AddPending(CreateDecodedStream());
    AddPending(CreateAudio());
    Thread::Sleep(50); // short wait to allow StarvationRamper to pull the above msgs
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    do {
        PullNext(EMsgAudioPcm);
    } while (!iStarvationRamper->IsEmpty());
    TEST(!iBuffering);

    Quit();
}

void SuiteStarvationRamper::TestAllSampleRates()
{
    static const TUint kSampleRates[] = {  7350,   8000,  11025,  12000,
                                          14700,  16000,  22050,  24000,
                                          29400,  32000,  44100,  48000,
                                          88200,  96000, 176400, 192000 };
    static const TUint kBitDepths[] = { 8, 16, 24, 32 };
#define NUM_ELEMS(arr) sizeof(arr) / sizeof(arr[0])
    static const TUint kNumSampleRates = NUM_ELEMS(kSampleRates);
    static const TUint kNumBitDepths = NUM_ELEMS(kBitDepths);

    for (TUint i=0; i<kNumBitDepths; i++) {
        iBitDepth = kBitDepths[i];
        const TUint byteDepth = iBitDepth / 8;
        TByte* p = const_cast<TByte*>(iPcmData.Ptr());
        const TUint samples = iPcmData.MaxBytes() / (byteDepth * kNumChannels);
        for (TUint j=0; j<samples; j++) {
            for (TUint k=0; k<byteDepth; k++) {
                *p++ = 0x7f;
            }
            for (TUint k=0; k<byteDepth; k++) {
                *p++ = 0x00;
            }
        }
        iPcmData.SetBytes(samples * byteDepth * kNumChannels);
        for (TUint j=0; j<kNumSampleRates; j++) {
            iSampleRate = kSampleRates[j];
            Print("\nbitDepth=%2u, sampleRate=%6u\n", iBitDepth, iSampleRate);
            iTrackOffset = 0;
            iJiffies = 0;
            AddPending(iMsgFactory->CreateMsgMode(kMode, false, true, ModeClockPullers(), false, false));
            AddPending(CreateTrack());
            AddPending(CreateDecodedStream());
            do {
                AddPending(CreateAudio());
            } while (iTrackOffset < StarvationRamper::kTrainingJiffies);

            PullNext(EMsgMode);
            PullNext(EMsgTrack);
            PullNext(EMsgDecodedStream);
            do {
                PullNext(EMsgAudioPcm);
            } while (iJiffies < iTrackOffset);
            iRampingDown = true;
            iJiffies = 0;
            while (iRampingDown) {
                PullNext(EMsgAudioPcm);
            }
            TUint expected = StarvationRamper::kRampDownJiffies;
            Jiffies::RoundDown(expected, iSampleRate);
            TEST(iJiffies == expected);
            PullNext(EMsgHalt, false);
        }
    }

    Quit();
}



void TestStarvationRamper()
{
    Runner runner("StarvationRamper tests\n");
    runner.Add(new SuiteStarvationRamper());
    runner.Run();
}
