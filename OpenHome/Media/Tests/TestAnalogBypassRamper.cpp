#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/AnalogBypassRamper.h>
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

class SuiteAnalogBypassRamper : public SuiteUnitTest
                              , private IPipelineElementUpstream
                              , private IMsgProcessor
                              , private IAnalogBypassVolumeRamper
{
    static const TUint kExpectedFlushId = 5;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
    static const TUint kVolumeMultiplierUninitialised = IAnalogBypassVolumeRamper::kMultiplierFull + 1;
    static const TUint kRampDuration = Jiffies::kPerMs * 100;
public:
    SuiteAnalogBypassRamper();
    ~SuiteAnalogBypassRamper();
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
private: // from IAnalogBypassVolumeRamper
    void ApplyVolumeMultiplier(TUint aValue) override;
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
    Msg* CreateTrack();
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
    void DrainCallback();
    void HaltCallback();
private:
    void TestMsgsPass();
    void TestMutesWhenHaltAcknowledged();
    void TestMutesWhenDrainAcknowledged();
    void TestNoMuteWhenAudioBeforeHaltAcknowledged();
    void TestUnmutesOnNonBypassAudio();
    void TestRampsVolumeDownOnAudioRampDown();
    void TestRampsVolumeUpOnAudioRampUp();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    AnalogBypassRamper* iAnalogBypassRamper;
    EMsgType iNextMsg;
    EMsgType iLastPulledMsg;
    TUint64 iTrackOffset;
    TBool iDrainAcknowledged;
    TBool iHaltAcknowledged;
    TBool iDeferDrainAcknowledgement;
    TBool iDeferHaltAcknowledgement;
    TBool iAnalogBypassEnable;
    Ramp::EDirection iRampDirection;
    TUint iRampPos;
    TUint iRampRemaining;
    TUint iLastRampMultiplier;
    MsgDrain* iLastDrainMsg;
    MsgHalt* iLastHaltMsg;
};

} // namespace Media
} // namespace OpenHome


const SpeakerProfile SuiteAnalogBypassRamper::kProfile(2);

SuiteAnalogBypassRamper::SuiteAnalogBypassRamper()
    : SuiteUnitTest("AnalogBypassRamper")
{
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestMsgsPass), "TestMsgsPass");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestMutesWhenHaltAcknowledged), "TestMutesWhenHaltAcknowledged");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestMutesWhenDrainAcknowledged), "TestMutesWhenDrainAcknowledged");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestNoMuteWhenAudioBeforeHaltAcknowledged), "TestNoMuteWhenAudioBeforeHaltAcknowledged");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestUnmutesOnNonBypassAudio), "TestUnmutesOnNonBypassAudio");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestRampsVolumeDownOnAudioRampDown), "TestRampsVolumeDownOnAudioRampDown");
    AddTest(MakeFunctor(*this, &SuiteAnalogBypassRamper::TestRampsVolumeUpOnAudioRampUp), "TestRampsVolumeUpOnAudioRampUp");
}

SuiteAnalogBypassRamper::~SuiteAnalogBypassRamper()
{
}

void SuiteAnalogBypassRamper::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(2, 1);
    init.SetMsgDrainCount(2);
    init.SetMsgHaltCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iAnalogBypassRamper = new AnalogBypassRamper(*iMsgFactory, *this);
    iAnalogBypassRamper->SetVolumeRamper(*this);
    iNextMsg = iLastPulledMsg = ENone;
    iTrackOffset = 0;
    iDrainAcknowledged = iHaltAcknowledged = iDeferDrainAcknowledgement = iDeferHaltAcknowledgement = false;
    iAnalogBypassEnable = false;
    iRampDirection = Ramp::ENone;
    iLastRampMultiplier = kVolumeMultiplierUninitialised;
    iLastDrainMsg = nullptr;
    iLastHaltMsg = nullptr;
}

void SuiteAnalogBypassRamper::TearDown()
{
    delete iAnalogBypassRamper;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteAnalogBypassRamper::Pull()
{
    switch (iNextMsg)
    {
    case EMsgMode:
        return iMsgFactory->CreateMsgMode(Brx::Empty(), false, ModeClockPullers(), false, false);
    case EMsgDrain:
        return iMsgFactory->CreateMsgDrain(MakeFunctor(*this, &SuiteAnalogBypassRamper::DrainCallback));
    case EMsgStreamInterrupted:
        return iMsgFactory->CreateMsgStreamInterrupted();
    case EMsgDecodedStream:
        return iMsgFactory->CreateMsgDecodedStream(1, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, 0, true, true, false, iAnalogBypassEnable, Multiroom::Allowed, kProfile, nullptr);
    case EMsgAudioPcm:
        return CreateAudio();
    case EMsgSilence:
    {
        TUint size = Jiffies::kPerMs * 3;
        return iMsgFactory->CreateMsgSilence(size, kSampleRate, 24, kNumChannels);
    }
    case EMsgHalt:
        return iMsgFactory->CreateMsgHalt(42, MakeFunctor(*this, &SuiteAnalogBypassRamper::HaltCallback));
    case EMsgQuit:
        return iMsgFactory->CreateMsgQuit();
    default:
        ASSERTS();
    }
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    if (iDeferDrainAcknowledgement) {
        iLastDrainMsg = aMsg;
        return nullptr;
    }
    aMsg->ReportDrained();
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    if (iDeferHaltAcknowledgement) {
        iLastHaltMsg = aMsg;
        return nullptr;
    }
    aMsg->ReportHalted();
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteAnalogBypassRamper::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteAnalogBypassRamper::ApplyVolumeMultiplier(TUint aValue)
{
    iLastRampMultiplier = aValue;
}

void SuiteAnalogBypassRamper::PullNext(EMsgType aExpectedMsg)
{
    iNextMsg = aExpectedMsg;
    Msg* msg = static_cast<IPipelineElementUpstream*>(iAnalogBypassRamper)->Pull();
    msg = msg->Process(*this);
    if (msg != nullptr) {
        msg->RemoveRef();
    }
    if (iLastPulledMsg != aExpectedMsg) {
        static const TChar* types[] = {
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
        Print("Expected %s, got %s\n", types[iLastPulledMsg], types[aExpectedMsg]);
    }
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteAnalogBypassRamper::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, AudioDataEndian::Little, iTrackOffset);
    iTrackOffset += audio->Jiffies();

    if (iRampDirection != Ramp::ENone) {
        if (iRampRemaining < audio->Jiffies()) {
            audio->Split(iRampRemaining)->RemoveRef();
        }
        MsgAudio* split = nullptr;
        iRampPos = audio->SetRamp(iRampPos, iRampRemaining, iRampDirection, split);
        ASSERT(split == nullptr);
        if (iRampRemaining == 0) {
            iRampDirection = Ramp::ENone;
        }
    }

    return audio;
}

void SuiteAnalogBypassRamper::DrainCallback()
{
    iDrainAcknowledged = true;
}

void SuiteAnalogBypassRamper::HaltCallback()
{
    iHaltAcknowledged = true;
}

void SuiteAnalogBypassRamper::TestMsgsPass()
{
    const EMsgType msgs[] = { EMsgMode
                            , EMsgDrain
                            , EMsgStreamInterrupted
                            , EMsgDecodedStream
                            , EMsgAudioPcm
                            , EMsgSilence
                            , EMsgHalt
                            , EMsgQuit
        };
    const TUint count = sizeof(msgs) / sizeof(msgs[0]);
    for (TUint i=0; i<count; i++) {
        PullNext(msgs[i]);
    }
}

void SuiteAnalogBypassRamper::TestMutesWhenHaltAcknowledged()
{
    TEST(!iHaltAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
    iDeferHaltAcknowledgement = true;
    PullNext(EMsgHalt);
    TEST(!iHaltAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
    iLastHaltMsg->ReportHalted();
    iLastHaltMsg->RemoveRef();
    TEST(iHaltAcknowledged);
    TEST(iLastRampMultiplier == IAnalogBypassVolumeRamper::kMultiplierZero);
}

void SuiteAnalogBypassRamper::TestMutesWhenDrainAcknowledged()
{
    TEST(!iDrainAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
    iDeferDrainAcknowledgement = true;
    PullNext(EMsgDrain);
    TEST(!iDrainAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
    iLastDrainMsg->ReportDrained();
    iLastDrainMsg->RemoveRef();
    TEST(iDrainAcknowledged);
    TEST(iLastRampMultiplier == IAnalogBypassVolumeRamper::kMultiplierZero);
}

void SuiteAnalogBypassRamper::TestNoMuteWhenAudioBeforeHaltAcknowledged()
{
    iDeferHaltAcknowledgement = true;
    PullNext(EMsgHalt);
    TEST(!iHaltAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
    PullNext(EMsgAudioPcm);
    iLastHaltMsg->ReportHalted();
    iLastHaltMsg->RemoveRef();
    TEST(iHaltAcknowledged);
    TEST(iLastRampMultiplier == kVolumeMultiplierUninitialised);
}

void SuiteAnalogBypassRamper::TestUnmutesOnNonBypassAudio()
{
    PullNext(EMsgDecodedStream);
    PullNext(EMsgHalt);
    TEST(iHaltAcknowledged);
    TEST(iLastRampMultiplier == IAnalogBypassVolumeRamper::kMultiplierZero);
    PullNext(EMsgAudioPcm);
    TEST(iLastRampMultiplier == IAnalogBypassVolumeRamper::kMultiplierFull);
}

void SuiteAnalogBypassRamper::TestRampsVolumeDownOnAudioRampDown()
{
    iRampDirection = Ramp::EDown;
    iRampPos = Ramp::kMax;
    iRampRemaining = kRampDuration;
    iAnalogBypassEnable = true;
    PullNext(EMsgDecodedStream);
    TUint prevRampMultiplier = iLastRampMultiplier;
    do {
        PullNext(EMsgAudioPcm);
        TEST(prevRampMultiplier > iLastRampMultiplier);
        prevRampMultiplier = iLastRampMultiplier;

    } while (iRampRemaining > 0);
    PullNext(EMsgHalt);
    TEST(iLastRampMultiplier == IAnalogBypassVolumeRamper::kMultiplierZero);
}

void SuiteAnalogBypassRamper::TestRampsVolumeUpOnAudioRampUp()
{
    iRampDirection = Ramp::EUp;
    iRampPos = Ramp::kMin;
    iRampRemaining = kRampDuration;
    iAnalogBypassEnable = true;
    PullNext(EMsgDecodedStream);
    PullNext(EMsgHalt);
    TUint prevRampMultiplier = iLastRampMultiplier;
    do {
        PullNext(EMsgAudioPcm);
        TEST(prevRampMultiplier < iLastRampMultiplier);
        prevRampMultiplier = iLastRampMultiplier;

    } while (iRampRemaining > 0);
    PullNext(EMsgAudioPcm);
    TEST(IAnalogBypassVolumeRamper::kMultiplierFull - iLastRampMultiplier < IAnalogBypassVolumeRamper::kMultiplierFull/8);
}



void TestAnalogBypassRamper()
{
    Runner runner("Analog bypass ramper tests\n");
    runner.Add(new SuiteAnalogBypassRamper());
    runner.Run();
}
