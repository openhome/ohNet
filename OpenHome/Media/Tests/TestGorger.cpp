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
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private:
    enum EMsgType
    {
        ENone
       ,EMsgMode
       ,EMsgSession
       ,EMsgTrack
       ,EMsgChangeInput
       ,EMsgDelay
       ,EMsgEncodedStream
       ,EMsgAudioEncoded
       ,EMsgMetaText
       ,EMsgStreamInterrupted
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgDecodedStream
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgQuit
    };
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgChangeInput* aMsg) override;
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
    iMsgFactory = new MsgFactory(iInfoAggregator, 0, 0, 50, 52, 1, 0, 0, 3, 2, 1, 2, 2, 1, 2, 2, 1, 3, 1, 1, 1);
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
    while (iPendingMsgs.size() == 0) {
        Thread::Sleep(10);
    }
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
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

void SuiteGorger::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/)
{
    iStarvationNotifications++;
}

Msg* SuiteGorger::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgSession* aMsg)
{
    iLastPulledMsg = EMsgSession;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteGorger::ProcessMsg(MsgChangeInput* aMsg)
{
    iLastPulledMsg = EMsgChangeInput;
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
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, NULL));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSession());
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgChangeInput(Functor()));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(0));
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brx::Empty()));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    iPendingMsgs.push_back(CreateAudio());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(Jiffies::kPerMs * 3));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());

    PullNext(EMsgMode);
    PullNext(EMsgSession);
    PullNext(EMsgTrack);
    PullNext(EMsgChangeInput);
    PullNext(EMsgDelay);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgMetaText);
    PullNext(EMsgStreamInterrupted);
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
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeGorgable, false, realTime, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorgeOnStreamOut);
    TEST(!iGorger->iGorging);

    realTime = true;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeRealTime, false, realTime, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());

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
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        iPendingMsgs.push_back(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestGorgingEndsWithNewMode()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    iPendingMsgs.push_back(CreateAudio());
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, NULL));
    PullNext(EMsgAudioPcm);
    while (iGorger->iGorging) {
        Thread::Sleep(10); // wait for new Mode to be pulled, cancelling gorging
    }
    TEST(!iGorger->iGorging);
    TEST(!iGorger->iGorging);
    PullNext(EMsgMode);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}

void SuiteGorger::TestHaltEnablesGorging()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        iPendingMsgs.push_back(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgHalt);
    TEST(iGorger->iGorging);
    PullNext(EMsgQuit);
}

void SuiteGorger::TestStarvationEnablesGorging()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeRealTime, false, true, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    iGorger->NotifyStarving(kModeRealTime, 1);
    TEST(!iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    TEST(iStarvationNotifications == 1);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(kModeGorgable, false, false, NULL));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgMode);
    TEST(iGorger->iCanGorge);
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iGorger->iGorging);
    TUint numAudioMsgs = 0;
    while (iTrackOffset < kGorgeSize) {
        iPendingMsgs.push_back(CreateAudio());
        numAudioMsgs++;
    }
    do {
        PullNext(EMsgAudioPcm);
    } while (--numAudioMsgs > 0);
    TEST(iGorger->iCanGorge);
    TEST(!iGorger->iGorging);
    iGorger->NotifyStarving(kModeGorgable, 2);
    TEST(iGorger->iCanGorge);
    TEST(iGorger->iGorging);
    TEST(iStarvationNotifications == 2);

    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());
    PullNext(EMsgQuit);
}



void TestGorger()
{
    Runner runner("Gorger tests\n");
    runner.Add(new SuiteGorger());
    runner.Run();
}
