#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/MuterVolume.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteMuterVolume : public SuiteUnitTest
                       , private IPipelineElementUpstream
                       , private IMsgProcessor
                       , private IVolumeRamper
{
    static const TUint kExpectedFlushId = 5;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
public:
    SuiteMuterVolume();
    ~SuiteMuterVolume();
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
private: // from IVolumeRamper
    IVolumeRamper::Status BeginMute() override;
    IVolumeRamper::Status StepMute(TUint aJiffies) override;
    void SetMuted() override;
    IVolumeRamper::Status BeginUnmute() override;
    IVolumeRamper::Status StepUnmute(TUint aJiffies) override;
    void SetUnmuted() override;
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
    void PullNext();
    void PullNext(EMsgType aExpectedMsg);
    void MuteClient();
    void DoBeginMute();
    Msg* CreateTrack();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    void PullAudioMsg();
    void AcknowledgeDeferredHalt();
private:
    void TestMsgsPassWhenRunning();
    void TestMuteImmediateWhenHalted();
    void TestMuteRampsWhenNotHalted();
    void TestUnmuteImmediateWhenHalted();
    void TestUnmuteRampsWhenNotHalted();
    void TestUnmuteWhileMuting();
    void TestMuteWhileUnmuting();
    void TestMuteWhileHalting();
    void TestUnmuteWhileHalting();
    void TestHaltWhileMuting();
    void TestHaltWhileUnmuting();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    MuterVolume* iMuter;
    ThreadFunctor* iMuteClientThread;
    EMsgType iLastPulledMsg;
    TBool iDeferHaltAcknowledgement;
    TBool iCompleteRamp;
    TBool iNotifiedMuted;
    TBool iNotifiedUnmuted;
    TUint iStreamId;
    TUint64 iTrackOffset;
    TUint64 iJiffies;
    TUint64 iRampDownJiffies;
    TUint64 iRampUpJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iNextStreamId;
    TUint iLastHaltId;
    MsgHalt* iLastHaltMsg;
};

} // namespace Media
} // namespace OpenHome


const SpeakerProfile SuiteMuterVolume::kProfile(2);

SuiteMuterVolume::SuiteMuterVolume()
    : SuiteUnitTest("MuterVolume")
{
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestMsgsPassWhenRunning), "TestMsgsPassWhenRunning");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestMuteImmediateWhenHalted), "TestMuteImmediateWhenHalted");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestMuteRampsWhenNotHalted), "TestMuteRampsWhenNotHalted");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestUnmuteImmediateWhenHalted), "TestUnmuteImmediateWhenHalted");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestUnmuteRampsWhenNotHalted), "TestUnmuteRampsWhenNotHalted");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestUnmuteWhileMuting), "TestUnmuteWhileMuting");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestMuteWhileUnmuting), "TestMuteWhileUnmuting");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestMuteWhileHalting), "TestMuteWhileHalting");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestUnmuteWhileHalting), "TestUnmuteWhileHalting");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestHaltWhileMuting), "TestHaltWhileMuting");
    AddTest(MakeFunctor(*this, &SuiteMuterVolume::TestHaltWhileUnmuting), "TestHaltWhileMuting");
}

SuiteMuterVolume::~SuiteMuterVolume()
{
}

void SuiteMuterVolume::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(52, 50);
    init.SetMsgSilenceCount(10);
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
    iMuter = new MuterVolume(*iMsgFactory, *this);
    iMuter->Start(*this);
    iMuteClientThread = new ThreadFunctor("MuteClient", MakeFunctor(*this, &SuiteMuterVolume::MuteClient));
    iMuteClientThread->Start();
    iStreamId = UINT_MAX;
    iTrackOffset = 0;
    iJiffies = iRampDownJiffies = iRampUpJiffies = 0;
    iDeferHaltAcknowledgement = false;
    iCompleteRamp = iNotifiedMuted = iNotifiedUnmuted = false;
    iNextStreamId = 1;
    iLastHaltId = MsgHalt::kIdInvalid;
    iLastHaltMsg = nullptr;
}

void SuiteMuterVolume::TearDown()
{
    if (iLastHaltMsg != nullptr) {
        iLastHaltMsg->RemoveRef();
    }
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iMuteClientThread;
    delete iMuter;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteMuterVolume::Pull()
{
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    iLastHaltId = aMsg->Id();
    if (iDeferHaltAcknowledgement) {
        iLastHaltMsg = aMsg;
        iLastHaltMsg->AddRef();
    }
    else {
        aMsg->ReportHalted();
    }
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    iJiffies += aMsg->Jiffies();
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteMuterVolume::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

IVolumeRamper::Status SuiteMuterVolume::BeginMute()
{
    iNotifiedMuted = iNotifiedUnmuted = false;
    return iCompleteRamp ? IVolumeRamper::Status::eComplete : IVolumeRamper::Status::eInProgress;
}

IVolumeRamper::Status SuiteMuterVolume::StepMute(TUint aJiffies)
{
    iRampDownJiffies += aJiffies;
    return iCompleteRamp ? IVolumeRamper::Status::eComplete : IVolumeRamper::Status::eInProgress;
}

void SuiteMuterVolume::SetMuted()
{
    iNotifiedMuted = true;
}

IVolumeRamper::Status SuiteMuterVolume::BeginUnmute()
{
    iNotifiedMuted = iNotifiedUnmuted = false;
    return iCompleteRamp ? IVolumeRamper::Status::eComplete : IVolumeRamper::Status::eInProgress;
}

IVolumeRamper::Status SuiteMuterVolume::StepUnmute(TUint aJiffies)
{
    iRampUpJiffies += aJiffies;
    return iCompleteRamp ? IVolumeRamper::Status::eComplete : IVolumeRamper::Status::eInProgress;
}

void SuiteMuterVolume::SetUnmuted()
{
    iNotifiedUnmuted = true;
}

void SuiteMuterVolume::PullNext()
{
    Msg* msg = iMuter->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteMuterVolume::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iMuter->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
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

void SuiteMuterVolume::MuteClient()
{
    iMuteClientThread->Wait();
    iMuter->Mute();
}

void SuiteMuterVolume::DoBeginMute()
{
    auto state = iMuter->iState;
    iMuteClientThread->Signal();
    // wait for iMuteClientThread to be scheduled and start to apply the mute
    while (iMuter->iState == state) {
        Thread::Sleep(10);
    }
}

Msg* SuiteMuterVolume::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteMuterVolume::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, false, false, Multiroom::Allowed, kProfile, nullptr);
}

Msg* SuiteMuterVolume::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteMuterVolume::PullAudioMsg()
{
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}

void SuiteMuterVolume::AcknowledgeDeferredHalt()
{
    iLastHaltMsg->ReportHalted();
    iLastHaltMsg->RemoveRef();
    iLastHaltMsg = nullptr;
}

void SuiteMuterVolume::TestMsgsPassWhenRunning()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), false, ModeClockPullers(), false, false, false, false));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(CreateAudio());
    TUint size = Jiffies::kPerMs * 3;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgSilence(size, kSampleRate, 16, kNumChannels));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDrain);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgAudioPcm);
    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    PullNext(EMsgStreamInterrupted);
    PullNext(EMsgQuit);
}

void SuiteMuterVolume::TestMuteImmediateWhenHalted()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(!iNotifiedMuted);
    iMuter->Mute();
    TEST(iNotifiedMuted);
    TEST(iMuter->iState == MuterVolume::State::eMuted);
}

void SuiteMuterVolume::TestMuteRampsWhenNotHalted()
{
    PullAudioMsg();
    DoBeginMute();
    iJiffies = 0;
    // pull an arbitrarily chosen amount of audio
    for (TUint i=0; i<5; i++) {
        PullAudioMsg();
        TEST(iMuter->iState == MuterVolume::State::eMutingRamp);
    }
    iCompleteRamp = true;
    PullAudioMsg();
    TEST(iJiffies == iRampDownJiffies);
    TEST(iRampUpJiffies == 0);
    TEST(iMuter->iState == MuterVolume::State::eMutingWait);
    do {
        PullAudioMsg();
    } while (iMuter->iState == MuterVolume::State::eMutingWait);

    TEST(!iNotifiedMuted); // don't expect notification when the volume ramper decides that a ramp has completed
    TEST(iMuter->iState == MuterVolume::State::eMuted);
}

void SuiteMuterVolume::TestUnmuteImmediateWhenHalted()
{
    iMuter->Mute();

    TEST(!iNotifiedUnmuted);
    TEST(iMuter->iState != MuterVolume::State::eRunning);
    iMuter->Unmute();
    TEST(iNotifiedUnmuted);
    TEST(iMuter->iState == MuterVolume::State::eRunning);
}

void SuiteMuterVolume::TestUnmuteRampsWhenNotHalted()
{
    iMuter->Mute();
    PullAudioMsg();

    iMuter->Unmute();
    iJiffies = 0;
    // pull an arbitrarily chosen amount of audio
    for (TUint i=0; i<5; i++) {
        PullAudioMsg();
        TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    }
    iCompleteRamp = true;
    PullAudioMsg();
    TEST(iJiffies == iRampUpJiffies);
    TEST(iRampDownJiffies == 0);
    TEST(!iNotifiedUnmuted); // don't expect notification when the volume ramper decides that a ramp has completed
    TEST(iMuter->iState == MuterVolume::State::eRunning);
}

void SuiteMuterVolume::TestUnmuteWhileMuting()
{
    PullAudioMsg();
    DoBeginMute();
    TEST(iMuter->iState == MuterVolume::State::eMutingRamp);
    PullAudioMsg();

    iMuter->Unmute();
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    PullAudioMsg();
    PullAudioMsg();
    iCompleteRamp = true;
    PullAudioMsg();

    TEST(iMuter->iState == MuterVolume::State::eRunning);
    TEST(!iNotifiedMuted);
    TEST(!iNotifiedUnmuted);
}

void SuiteMuterVolume::TestMuteWhileUnmuting()
{
    iMuter->Mute();
    PullAudioMsg();
    TEST(iMuter->iState == MuterVolume::State::eMuted);
    iMuter->Unmute();
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    PullAudioMsg();
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    DoBeginMute();
    TEST(iMuter->iState == MuterVolume::State::eMutingRamp);
    for (TUint i=0; i<5; i++) {
        PullAudioMsg();
    }

    iCompleteRamp = true;
    PullAudioMsg();
    TEST(iMuter->iState == MuterVolume::State::eMutingWait);
    do {
        PullAudioMsg();
    } while (iMuter->iState == MuterVolume::State::eMutingWait);
    TEST(iMuter->iState == MuterVolume::State::eMuted);
    TEST(!iNotifiedMuted);
    TEST(!iNotifiedUnmuted);
}

void SuiteMuterVolume::TestMuteWhileHalting()
{
    PullAudioMsg();
    iDeferHaltAcknowledgement = true;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    DoBeginMute();
    TEST(iMuter->iState == MuterVolume::State::eMutingRamp);
    AcknowledgeDeferredHalt();
    TEST(iMuter->iState == MuterVolume::State::eMuted);
    TEST(iNotifiedMuted);
    TEST(!iNotifiedUnmuted);
}

void SuiteMuterVolume::TestUnmuteWhileHalting()
{
    iMuter->Mute();
    TEST(iMuter->iState == MuterVolume::State::eMuted);
    PullAudioMsg();
    iMuter->Unmute();
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    PullAudioMsg();
    iDeferHaltAcknowledgement = true;
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    AcknowledgeDeferredHalt();
    TEST(iMuter->iState == MuterVolume::State::eRunning);
    TEST(!iNotifiedMuted);
    TEST(iNotifiedUnmuted);
}

void SuiteMuterVolume::TestHaltWhileMuting()
{
    PullAudioMsg();
    DoBeginMute();
    TEST(iMuter->iState == MuterVolume::State::eMutingRamp);
    PullAudioMsg();
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iMuter->iState == MuterVolume::State::eMuted);
    TEST(iNotifiedMuted);
    TEST(!iNotifiedUnmuted);
}

void SuiteMuterVolume::TestHaltWhileUnmuting()
{
    iMuter->Mute();
    PullAudioMsg();
    iMuter->Unmute();
    TEST(iMuter->iState == MuterVolume::State::eUnmutingRamp);
    PullAudioMsg();
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgHalt);
    TEST(iMuter->iState == MuterVolume::State::eRunning);
    TEST(!iNotifiedMuted);
    TEST(iNotifiedUnmuted);
}



void TestMuterVolume()
{
    Runner runner("MuterVolume tests\n");
    runner.Add(new SuiteMuterVolume());
    runner.Run();
}
