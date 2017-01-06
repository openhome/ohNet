#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Drainer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/OsWrapper.h>

#include <list>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteDrainer : public SuiteUnitTest, private IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
public:
    SuiteDrainer(Environment& aEnv);
    ~SuiteDrainer();
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
    void PullNext(EMsgType aExpectedMsg);
    void TimerCallback();
    Msg* CreateMsgSilence();
private:
    void TestMsgDrainFollowsHalt();
    void TestBlocksWaitingForDrainResponse();
    void TestDrainAfterStarvation();
    void TestOneDrainAfterHaltAndStarvation();
private:
    Environment& iEnv;
    AllocatorInfoLogger iInfoAggregator;
    TrackFactory* iTrackFactory;
    MsgFactory* iMsgFactory;
    Drainer* iDrainer;
    MsgDrain* iMsgDrain;
    EMsgType iLastPulledMsg;
    std::list<Msg*> iPendingMsgs;
    Timer* iTimer;
};

} // namespace Media
} // namespace OpenHome


SuiteDrainer::SuiteDrainer(Environment& aEnv)
    : SuiteUnitTest("Drainer")
    , iEnv(aEnv)
{
    AddTest(MakeFunctor(*this, &SuiteDrainer::TestMsgDrainFollowsHalt), "TestMsgDrainFollowsHalt");
    AddTest(MakeFunctor(*this, &SuiteDrainer::TestBlocksWaitingForDrainResponse), "TestBlocksWaitingForDrainResponse");
    AddTest(MakeFunctor(*this, &SuiteDrainer::TestDrainAfterStarvation), "TestDrainAfterStarvation");
    AddTest(MakeFunctor(*this, &SuiteDrainer::TestOneDrainAfterHaltAndStarvation), "TestOneDrainAfterHaltAndStarvation");
}

SuiteDrainer::~SuiteDrainer()
{
}

void SuiteDrainer::Setup()
{
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    MsgFactoryInitParams init;
    iMsgFactory = new MsgFactory(iInfoAggregator, init);
    iDrainer = new Drainer(*iMsgFactory, *this);
    iMsgDrain = nullptr;
    iTimer = new Timer(iEnv, MakeFunctor(*this, &SuiteDrainer::TimerCallback), "SuiteDrainer");
}

void SuiteDrainer::TearDown()
{
    while (iPendingMsgs.size() > 0) {
        iPendingMsgs.front()->RemoveRef();
        iPendingMsgs.pop_front();
    }
    delete iTimer;
    if (iMsgDrain != nullptr) {
        iMsgDrain->ReportDrained();
        iMsgDrain->RemoveRef();
    }
    delete iDrainer;
    delete iMsgFactory;
    delete iTrackFactory;
}

Msg* SuiteDrainer::Pull()
{
    ASSERT(iPendingMsgs.size() > 0);
    Msg* msg = iPendingMsgs.front();
    iPendingMsgs.pop_front();
    return msg;
}

Msg* SuiteDrainer::ProcessMsg(MsgMode* aMsg)
{
    iLastPulledMsg = EMsgMode;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgTrack* aMsg)
{
    iLastPulledMsg = EMsgTrack;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgDrain* aMsg)
{
    iLastPulledMsg = EMsgDrain;
    iMsgDrain = aMsg;
    iMsgDrain->AddRef();
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgDelay* aMsg)
{
    iLastPulledMsg = EMsgDelay;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgEncodedStream* aMsg)
{
    iLastPulledMsg = EMsgEncodedStream;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteDrainer::ProcessMsg(MsgMetaText* aMsg)
{
    iLastPulledMsg = EMsgMetaText;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    iLastPulledMsg = EMsgStreamInterrupted;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgHalt* aMsg)
{
    iLastPulledMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgFlush* aMsg)
{
    iLastPulledMsg = EMsgFlush;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgWait* aMsg)
{
    iLastPulledMsg = EMsgWait;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastPulledMsg = EMsgDecodedStream;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgBitRate* aMsg)
{
    iLastPulledMsg = EMsgBitRate;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastPulledMsg = EMsgAudioPcm;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgSilence* aMsg)
{
    iLastPulledMsg = EMsgSilence;
    return aMsg;
}

Msg* SuiteDrainer::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuiteDrainer::ProcessMsg(MsgQuit* aMsg)
{
    iLastPulledMsg = EMsgQuit;
    return aMsg;
}

void SuiteDrainer::PullNext(EMsgType aExpectedMsg)
{
    Msg* msg = iDrainer->Pull();
    msg = msg->Process(*this);
    msg->RemoveRef();
    TEST(iLastPulledMsg == aExpectedMsg);
}

void SuiteDrainer::TimerCallback()
{
    ASSERT(iMsgDrain != nullptr);
    iMsgDrain->ReportDrained();
    iMsgDrain->RemoveRef();
    iMsgDrain = nullptr;
}

Msg* SuiteDrainer::CreateMsgSilence()
{
    TUint size = Jiffies::kPerMs * 3;
    return iMsgFactory->CreateMsgSilence(size, 44100, 16, 2);
}

void SuiteDrainer::TestMsgDrainFollowsHalt()
{
    iPendingMsgs.push_back(CreateMsgSilence());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());

    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    PullNext(EMsgDrain);
}

void SuiteDrainer::TestBlocksWaitingForDrainResponse()
{
    iPendingMsgs.push_back(CreateMsgSilence());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgMode(Brx::Empty(), false, ModeClockPullers(), false, false));

    PullNext(EMsgSilence);
    PullNext(EMsgHalt);
    PullNext(EMsgDrain);
    const TUint start = Os::TimeInMs(iEnv.OsCtx());
    const TUint kTimerDuration = 50;
    iTimer->FireIn(kTimerDuration);
    PullNext(EMsgMode);
    const TUint now = Os::TimeInMs(iEnv.OsCtx());
    const TUint delay = now - start;
    TEST(delay >= kTimerDuration);
}

void SuiteDrainer::TestDrainAfterStarvation()
{
    iDrainer->NotifyStarving(Brx::Empty(), 0, true);
    PullNext(EMsgDrain);
}

void SuiteDrainer::TestOneDrainAfterHaltAndStarvation()
{
    iPendingMsgs.push_back(CreateMsgSilence());
    iPendingMsgs.push_back(iMsgFactory->CreateMsgHalt());
    PullNext(EMsgSilence);
    iPendingMsgs.push_back(CreateMsgSilence());
    PullNext(EMsgHalt);
    iDrainer->NotifyStarving(Brx::Empty(), 0, true);
    PullNext(EMsgDrain);
    iMsgDrain->ReportDrained();
    iMsgDrain->RemoveRef();
    iMsgDrain = nullptr;
    PullNext(EMsgSilence);
}



void TestDrainer(Environment& aEnv)
{
    Runner runner("Drainer tests\n");
    runner.Add(new SuiteDrainer(aEnv));
    runner.Run();
}
