#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/StarvationMonitor.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class SuiteStarvationMonitor : public Suite, private IPipelineElementUpstream, private IMsgProcessor,
                                             private IStarvationMonitorObserver
{
    static const TUint kDecodedAudioCount = 1536;
    static const TUint kMsgAudioPcmCount  = 2048;
    static const TUint kMsgSilenceCount   = 128;

    static const TUint kRegularSize         = Jiffies::kPerMs * 100;
    static const TUint kStarvationThreshold = Jiffies::kPerMs * 40;
    static const TUint kRampUpSize          = Jiffies::kPerMs * 50;
    static const TUint kMaxStreamCount      = 5;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteStarvationMonitor();
    ~SuiteStarvationMonitor();
    void Test();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
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
private: // from IStarvationMonitorObserver
    void NotifyStarvationMonitorBuffering(TBool aBuffering) override;
private:
    void NotifySize(TUint aJiffies);
    void Stop();
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgDecodedStream
       ,EMsgTrack
       ,EMsgEncodedStream
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
       ,EMsgWait
       ,EMsgQuit
    };
enum EMsgGenerationState
{
    EStateWait
   ,EStateAudioFillInitial
   ,EStateAudioFillPostStarvation
   ,EStateHalt
   ,EStateQuit
   ,EStateCompleted
};
private:
    void GenerateUpstreamMsgs(EMsgGenerationState aState);
    void WaitForEnqueueToBlock();
    MsgAudio* CreateAudio();
private:
    MsgFactory* iMsgFactory;
    AllocatorInfoLogger iInfoAggregator;
    StarvationMonitor* iSm;
    EMsgType iLastMsg;
    EMsgGenerationState iMsgGenerationState;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamCompleted;
    TUint64 iTrackOffset;
    TBool iBuffering;
    TByte iBuf[DecodedAudio::kMaxBytes];
};

} // namespace Media
} // namespace OpenHome


// SuiteStarvationMonitor

SuiteStarvationMonitor::SuiteStarvationMonitor()
    : Suite("Starvation Monitor tests")
    , iLastMsg(ENone)
    , iMsgGenerationState(EStateWait)
    , iSemUpstream("TSRV", 0)
    , iSemUpstreamCompleted("TSRV", 0)
    , iTrackOffset(0)
    , iBuffering(false)
{
    iMsgFactory = new MsgFactory(iInfoAggregator, 1, 1, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    iSm = new StarvationMonitor(*iMsgFactory, *this, *this, kPriorityNormal, kRegularSize, kStarvationThreshold, kRampUpSize, kMaxStreamCount);
}

SuiteStarvationMonitor::~SuiteStarvationMonitor()
{
    delete iSm;
    delete iMsgFactory;
}

void SuiteStarvationMonitor::Test()
{
    /*
    Test goes something like
        Create SM.  Check pull would block.
        Add 0x7f filled audio.  Repeat until would block.  Check size is >= kRegularSize.
        Pull all audio.  Check the last bit ramps down.
        Check halt message is sent and pull would then block
        Start filling with 0x7f filled audio again.  Check pull would still block as we grow beyond regular limit
        Continue adding audio until we reach gorge size.  Check enqueue would now block.
        Pull audio.  Check it ramps up.
        Check enqueues would block until size drops below normal max
        Add Halt.  Check queue can be drained without ramping down
    */

    TEST(!iSm->EnqueueWouldBlock());
    TEST(iSm->PullWouldBlock());
    TEST(iSm->Jiffies() == 0);
    TEST(iSm->iStatus == StarvationMonitor::EBuffering);
    TEST(iBuffering);

    // Add 0x7f filled audio.  Repeat until would block.  Check size is >= kRegularSize.
    Print("\nAdd audio until would block\n");
    GenerateUpstreamMsgs(EStateAudioFillInitial);
    while (iSm->Jiffies() < kRegularSize) {
        Thread::Sleep(10); // last msg may not quite have been enqueued when we switched threads
    }
    TEST(iSm->EnqueueWouldBlock());
    TEST(!iSm->PullWouldBlock());
    TEST(iSm->iStatus == StarvationMonitor::ERunning);
    TEST(!iBuffering);

    Msg* msg;
    // Pull all audio.  Check the last bit ramps down.
    Print("\nPull all audio\n");
    do {
        TEST(!iSm->PullWouldBlock());
        TUint prevJiffies = iSm->Jiffies();
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
        TEST(iSm->Jiffies() < prevJiffies);
        if (iSm->Jiffies() > kRegularSize) {
            TEST(iSm->EnqueueWouldBlock());
        }
        else {
            TEST(!iSm->EnqueueWouldBlock());
        }
        if (iSm->Jiffies() == 0) {
            TEST(iSm->iStatus == StarvationMonitor::EBuffering);
        }
        else if (iSm->Jiffies() < kStarvationThreshold) {
            TEST(iSm->iStatus == StarvationMonitor::ERampingDown);
        }
        else {
            TEST(iSm->iStatus == StarvationMonitor::ERunning);
        }
    } while(iSm->Jiffies() > 0);
    TEST(!iSm->EnqueueWouldBlock());
    TEST(iSm->IsEmpty()); // queue is empty but we expect SM to generte a halt message if we Pull again
    TEST(iBuffering);

    // Check halt message is sent and pull would then block
    Print("\nCheck for halt then pull would block\n");
    msg = iSm->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgHalt);
    msg->RemoveRef();
    TEST(iSm->PullWouldBlock());

    // Start filling with 0x7f filled audio again.  Check pull would still block as we grow beyond regular limit
    // Continue adding audio until we reach gorge size.  Check enqueue would now block.
    Print("\nRe-fill until normal size\n");
    GenerateUpstreamMsgs(EStateAudioFillPostStarvation);
    WaitForEnqueueToBlock();
    Thread::Sleep(20); // WaitForEnqueueToBlock can return very shortly before NotifyStarvationMonitorBuffering is called
    TEST(!iBuffering);

    // Pull audio.  Check it ramps up.
    Print("\nPull audio, checking for ramp\n");
    TUint jiffies = iSm->Jiffies();
    do {
        TEST(!iSm->PullWouldBlock());
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iSm->iStatus == StarvationMonitor::ERampingUp);
    TEST(jiffies - iSm->Jiffies() == kRampUpSize);
    TEST(iSm->iStatus == StarvationMonitor::ERunning);
    TEST(!iBuffering);

    // Check enqueues would block until size drops below normal max
    Print("\nPull until below normal max\n");
    while (iSm->Jiffies() > kRegularSize) {
        TEST(!iSm->PullWouldBlock());
        TEST(iSm->EnqueueWouldBlock());
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
    }
    TEST(!iBuffering);

    // Add Halt.  Check queue can be drained without ramping down
    Print("\nDrain without ramping down\n");
    TEST(!iSm->iPlannedHalt);
    GenerateUpstreamMsgs(EStateHalt);
    while (!iSm->iPlannedHalt) {
        Thread::Sleep(1); // nasty delay to give time for Pull'd Halt to be stored in SM
    }
    do {
        TEST(!iSm->PullWouldBlock());
        TEST(iSm->iStatus == StarvationMonitor::ERunning);
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
        TEST(!iSm->EnqueueWouldBlock());
    } while (iSm->Jiffies() > 0);
    TEST(iSm->iStatus == StarvationMonitor::EBuffering);
    msg = iSm->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgHalt);
    msg->RemoveRef();
    TEST(iSm->iStatus == StarvationMonitor::EBuffering);
    TEST(iSm->PullWouldBlock());
    TEST(iBuffering);

    // Send Quit msg to unblock the SM thread which is blocked inside a Pull()
    GenerateUpstreamMsgs(EStateQuit);
    msg = iSm->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgQuit);
    msg->RemoveRef();
}

void SuiteStarvationMonitor::GenerateUpstreamMsgs(EMsgGenerationState aState)
{
    iMsgGenerationState = aState;
    iSemUpstream.Signal();
    iSemUpstreamCompleted.Wait();
}

void SuiteStarvationMonitor::WaitForEnqueueToBlock()
{
    // test has 2 threads and its a pain to use priorities on Linux...
    static const TUint kMaxRetries = 20;
    for (TUint i=0; i<kMaxRetries; i++) {
        if (iSm->EnqueueWouldBlock()) {
            return;
        }
        Thread::Sleep(10);
    }
    ASSERTS();
}

Msg* SuiteStarvationMonitor::Pull()
{
    switch (iMsgGenerationState)
    {
    case EStateWait:
        iSemUpstream.Wait();
        return Pull();
        // fallthrough
    case EStateAudioFillInitial:
    {
        MsgAudio* msg = CreateAudio();
        if (iSm->Jiffies() + msg->Jiffies() >= kRegularSize) {
            iMsgGenerationState = EStateWait;
            iSemUpstreamCompleted.Signal();
        }
        return msg;
    }
    case EStateAudioFillPostStarvation:
    {
        MsgAudio* msg = CreateAudio();
        if (iSm->Jiffies() + msg->Jiffies() >= kRegularSize) {
            iMsgGenerationState = EStateWait;
            iSemUpstreamCompleted.Signal();
        }
        TEST(iSm->PullWouldBlock());
        TEST(iSm->iStatus == StarvationMonitor::EBuffering);
        return msg;
    }
    case EStateHalt:
        iMsgGenerationState = EStateQuit;
        iSemUpstreamCompleted.Signal();
        return iMsgFactory->CreateMsgHalt();
    case EStateQuit:
        iSemUpstream.Wait();
        iMsgGenerationState = EStateCompleted;
        iSemUpstreamCompleted.Signal();
        return iMsgFactory->CreateMsgQuit();
    case EStateCompleted:
        ASSERTS(); // we'll only reach here if downstream element ignores quit msg
        break;
    }
    return NULL;
}

MsgAudio* SuiteStarvationMonitor::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0x7f, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataEndianLittle, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS(); // MsgMode not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS(); // MsgMode not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS(); // MsgTrack not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgChangeInput* /*aMsg*/)
{
    ASSERTS(); // MsgChangeInput not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS(); // MsgDelay not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS(); // MsgEncodedStream not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // MsgMetaText not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS(); // FIXME - missing test cases
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsg = EMsgHalt;
    return aMsg;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // MsgFlush not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // MsgWait not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS(); // MsgDecodedStream not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    MsgPlayable* playable = aMsg->CreatePlayable();
    ProcessorPcmBufPacked pcmProcessor;
    playable->Read(pcmProcessor);
    Brn buf = pcmProcessor.Buf();
    playable->RemoveRef();
    const TByte* ptr = buf.Ptr();
    const TUint firstSubsample = (ptr[0]<<8) | ptr[1];
    const TUint bytes = buf.Bytes();
    const TUint lastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];

    switch (iSm->iStatus)
    {
    case StarvationMonitor::ERampingDown:
        TEST(iSm->Jiffies() <= kStarvationThreshold);
        TEST(firstSubsample > lastSubsample);
        break;
    case StarvationMonitor::ERampingUp:
        TEST(firstSubsample < lastSubsample);
        break;
    default:
        // don't test subsample values here as we may be in state ERunning because aMsg was the last one to be ramped up
        break;
    }
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // MsgSilence not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // MsgPlayable not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgQuit* aMsg)
{
    iLastMsg = EMsgQuit;
    return aMsg;
}

void SuiteStarvationMonitor::NotifyStarvationMonitorBuffering(TBool aBuffering)
{
    iBuffering = aBuffering;
}



void TestStarvationMonitor()
{
    Runner runner("Starvation Monitor tests\n");
    runner.Add(new SuiteStarvationMonitor());
    runner.Run();
}

