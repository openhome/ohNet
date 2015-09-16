#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Media/Pipeline/Ramper.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteRamper : public SuiteUnitTest, private IPipelineElementUpstream, private IMsgProcessor
{
    static const TUint kRampDuration = Jiffies::kPerMs * 50; // shorter than production code but this is assumed to not matter
    static const TUint kExpectedFlushId = 5;
    static const TUint kSampleRate = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteRamper();
    ~SuiteRamper();
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
    Msg* CreateDecodedStream();
    Msg* CreateAudio();
private:
    void TestNonAudioMsgsPass();
    void TestNonLiveStreamAtStartNoRamp();
    void TestNonLiveStreamInMiddleRamps();
    void TestLiveStreamRamps();
private:
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Ramper* iRamper;
    EMsgType iLastPulledMsg;
    TBool iRamping;
    TUint iStreamId;
    TUint64 iTrackOffset;
    TUint iJiffies;
    std::list<Msg*> iPendingMsgs;
    TUint iLastSubsample;
    TUint iNextStreamId;
    TUint64 iSampleStart;
    TBool iLive;
};

} // namespace Media
} // namespace OpenHome


SuiteRamper::SuiteRamper()
    : SuiteUnitTest("Ramper")
{
    AddTest(MakeFunctor(*this, &SuiteRamper::TestNonAudioMsgsPass), "TestNonAudioMsgsPass");
    AddTest(MakeFunctor(*this, &SuiteRamper::TestNonLiveStreamAtStartNoRamp), "TestNonLiveStreamAtStartNoRamp");
    AddTest(MakeFunctor(*this, &SuiteRamper::TestNonLiveStreamInMiddleRamps), "TestNonLiveStreamInMiddleRamps");
    AddTest(MakeFunctor(*this, &SuiteRamper::TestLiveStreamRamps), "TestLiveStreamRamps");
}

SuiteRamper::~SuiteRamper()
{
}

void SuiteRamper::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 5);
    MsgFactoryInitParams init;
    init.SetMsgAudioPcmCount(52, 50);
    init.SetMsgSilenceCount(10);
    init.SetMsgDecodedStreamCount(2);
    init.SetMsgTrackCount(2);
    init.SetMsgEncodedStreamCount(2);
    init.SetMsgMetaTextCount(2);
    init.SetMsgHaltCount(2);
    init.SetMsgFlushCount(2);
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iRamper = new Ramper(*this, kRampDuration);
    iStreamId = UINT_MAX;
    iTrackOffset = 0;
    iJiffies = 0;
    iRamping = false;
    iLastSubsample = 0xffffff;
    iNextStreamId = 1;
    iSampleStart = 0;
    iLive = false;
}

void SuiteRamper::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iRamper;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteRamper::Pull()
{
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

Msg* SuiteRamper::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    iStreamId = aMsg->StreamId();
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteRamper::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgBitRate* aMsg)
{
    iLastPulledMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgAudioPcm* aMsg)
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

    if (iRamping) {
        TEST(firstSubsample <= iLastSubsample);
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }
    iLastSubsample = (ptr[bytes-3]<<16) | (ptr[bytes-2]<<8) | ptr[bytes-1];
    if (iRamping) {
        TEST(iLastSubsample > firstSubsample);
        iRamping = (iLastSubsample < 0x7f7f7f);
    }
    else {
        TEST(firstSubsample == 0x7f7f7f);
    }

    return playable;
}

Msg* SuiteRamper::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteRamper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteRamper::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteRamper::PullNext()
{
    Msg* msg = iRamper->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
}

void SuiteRamper::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iRamper->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}

Msg* SuiteRamper::CreateTrack()
{
    Track* track = iTrackFactory->CreateTrack(Brx::Empty(), Brx::Empty());
    Msg* msg = iMsgFactory->CreateMsgTrack(*track);
    track->RemoveRef();
    return msg;
}

Msg* SuiteRamper::CreateDecodedStream()
{
    return iMsgFactory->CreateMsgDecodedStream(iNextStreamId, 100, 24, kSampleRate, kNumChannels, Brn("notARealCodec"), 1LL<<38, iSampleStart, true, true, iLive, nullptr);
}

Msg* SuiteRamper::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 24, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void SuiteRamper::TestNonAudioMsgsPass()
{
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brn("Mode"), true, false, nullptr, false, false));
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDrain(Functor()));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgDelay(Jiffies::kPerMs * 100));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMetaText(Brn("MetaText")));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgStreamInterrupted());
    iPendingMsgs.push_back(CreateDecodedStream());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgBitRate(100));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgFlush(MsgFlush::kIdInvalid));
    iPendingMsgs.push_back(iMsgFactory->CreateMsgWait());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgQuit());

    PullNext(EMsgMode);
    PullNext(EMsgTrack);
    PullNext(EMsgDrain);
    PullNext(EMsgDelay);
    PullNext(EMsgMetaText);
    PullNext(EMsgStreamInterrupted);
    PullNext(EMsgDecodedStream);
    PullNext(EMsgBitRate);
    PullNext(EMsgHalt);
    PullNext(EMsgFlush);
    PullNext(EMsgWait);
    PullNext(EMsgQuit);
}

void SuiteRamper::TestNonLiveStreamAtStartNoRamp()
{
    iLive = false;
    iSampleStart = 0;
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);

    iRamping = false;
    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}

void SuiteRamper::TestNonLiveStreamInMiddleRamps()
{
    iLive = false;
    iSampleStart = 100;
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iRamper->iRamping);

    iRamping = true;
    iJiffies = 0;
    while (iRamper->iRamping) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
}

void SuiteRamper::TestLiveStreamRamps()
{
    iLive = true;
    iSampleStart = 0;
    iPendingMsgs.push_back(CreateTrack());
    iPendingMsgs.push_back(CreateDecodedStream());
    PullNext(EMsgTrack);
    PullNext(EMsgDecodedStream);
    TEST(iRamper->iRamping);

    iRamping = true;
    iJiffies = 0;
    while (iRamper->iRamping) {
        iPendingMsgs.push_back(CreateAudio());
        PullNext(EMsgAudioPcm);
    }
    TEST(iJiffies == kRampDuration);
    iRamping = false; /* rounding errors in ramp code mean that
                         we can't rely on this being updated automatically */

    iPendingMsgs.push_back(CreateAudio());
    PullNext(EMsgAudioPcm);
}



void TestRamper()
{
    Runner runner("Ramper tests\n");
    runner.Add(new SuiteRamper());
    runner.Run();
}
