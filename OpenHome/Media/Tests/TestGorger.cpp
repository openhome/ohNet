#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Gorger.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>

#include <list>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteGorger : public SuiteUnitTest, private IPipelineElementUpstream, private IStreamHandler, private IMsgProcessor
{
    static const TUint kGorgeSize = Jiffies::kPerMs * 100; // production code will likely use a much larger size
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const Brn kModeRealTime;
    static const Brn kModeGorgable;
public:
    SuiteGorger();
    ~SuiteGorger();
private: // from SuiteUnitTest
    void Setup() override;
    void TearDown() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgTrack
       ,EMsgDrain
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgBitRate
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgQuit
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
private:
    void Queue(Msg* aMsg);
    void PullNext(EMsgType aExpectedMsg);
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
    Gorger* iGorger;
    EMsgType iLastPulledMsg;
    std::list<Msg*> iPendingMsgs;
    TUint64 iTrackOffset;
    TUint iNextStreamId;
    TUint iStarvationNotifications;
};

} // namespace Media
} // namespace OpenHome


const Brn SuiteGorger::kModeRealTime("RealTime");
const Brn SuiteGorger::kModeGorgable("Gorgable");

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
    iGorger = new Gorger(*iMsgFactory, *this, kPriorityNormal, kGorgeSize);
    iLastPulledMsg = ENone;
    iTrackOffset = 0;
    iNextStreamId = 1;
    iStarvationNotifications = 0;
}

void SuiteGorger::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iGorger;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteGorger::Pull()
{
    for (;;) {
        iLock.Wait();
        const TBool msgAvailable = (iPendingMsgs.size() > 0);
        iLock.Signal();
        if (msgAvailable) {
            break;
        }
        Thread::Sleep(10);
    }

    iLock.Wait();
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    iLock.Signal();

    return msg;
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

void SuiteGorger::Queue(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsgs.push_back(aMsg);
    iLock.Signal();
}

void SuiteGorger::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iGorger->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
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
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, false, this);
}

Msg* SuiteGorger::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteGorger::TestAllMsgsPassWhileNotGorging()
{
    Queue(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, nullptr, false, false));
    Queue(CreateTrack());
    Queue(iMsgFactory->CreateMsgDrain(Functor()));
    Queue(iMsgFactory->CreateMsgDelay(0));
    Queue(CreateDecodedStream());
    Queue(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    Queue(iMsgFactory->CreateMsgStreamInterrupted());
    Queue(iMsgFactory->CreateMsgBitRate(42));
    Queue(CreateAudio());
    Queue(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
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
    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    PullNext(EMsgWait);
    PullNext(EMsgQuit);
}

void SuiteGorger::TestNewModeUpdatesGorgeStatus()
{
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);

    TBool realTime = false;
    Queue(iMsgFactory->CreateMsgMode(kModeGorgable, false, realTime, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorgeOnStreamOut);
    TEST(!iGorger->iGorging);

    realTime = true;
    Queue(iMsgFactory->CreateMsgMode(kModeRealTime, false, realTime, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());

    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorgeOnStreamOut);
    while (iGorger->iGorging) {
        Thread::Sleep(10); // wait for new Mode to be pulled, cancelling gorging
    }
    TEST(!iGorger->iGorging);
    PullNext(EMsgMode);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorgeOnStreamOut);
    TEST(!iGorger->iGorging);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
}

void SuiteGorger::TestGorgingEndsWithSufficientAudio()
{
    Queue(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    Queue(CreateAudio());
    PullNext(EMsgAudioPcm);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestGorgingEndsWithNewMode()
{
    Queue(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    Queue(CreateAudio());
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    Queue(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, nullptr, false, false));
    PullNext(EMsgAudioPcm);
    while (iGorger->iGorging) {
        Thread::Sleep(10); // wait for new Mode to be pulled, cancelling gorging
    }
    TEST(!iGorger->iGorging);
    TEST(!iGorger->iGorging);
    PullNext(EMsgMode);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestHaltEnablesGorging()
{
    Queue(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);

    Queue(iMsgFactory->CreateMsgHalt());
    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgHalt);
    TEST(iGorger->iGorging);
    PullNext(EMsgQuit);
}

void SuiteGorger::TestStarvationEnablesGorging()
{
    Queue(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    iGorger->NotifyStarving(kModeRealTime, 1, true);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    TEST(iStarvationNotifications == 1);

    Queue(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, nullptr, false, false));
    Queue(CreateTrack());
    Queue(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iGorger->iCanGorge);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        Queue(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    iGorger->NotifyStarving(kModeGorgable, 2, true);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);
    TEST(iStarvationNotifications == 2);

    Queue(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}



void TestGorger()
{
    Runner runner("Gorger tests\n");
    runner.Add(new SuiteGorger());
    runner.Run();
}
