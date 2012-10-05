#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;

namespace OpenHome {
namespace Media {

class InfoAggregator : public Av::IInfoAggregator, private IWriter
{
public:
    InfoAggregator();
    void PrintStats();
private: // from IInfoAggregator
    void Register(Av::IInfoProvider& aProvider, std::vector<Brn>& aSupportedQueries);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    std::vector<Av::IInfoProvider*> iInfoProviders;
};

class SuiteStarvationMonitor : public Suite, private IPipelineElementUpstream, private IMsgProcessor, private IStarvationMonitorObserver
{
    static const TUint kDecodedAudioCount = 1536;
    static const TUint kMsgAudioPcmCount  = 2048;
    static const TUint kMsgSilenceCount   = 128;

    static const TUint kRegularSize         = Jiffies::kJiffiesPerMs * 100;
    static const TUint kStarvationThreshold = Jiffies::kJiffiesPerMs * 40;
    static const TUint kGorgeSize           = Jiffies::kJiffiesPerMs * 500;
    static const TUint kRampUpSize          = Jiffies::kJiffiesPerMs * 50;

    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    SuiteStarvationMonitor();
    ~SuiteStarvationMonitor();
    void Test();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // from IStarvationMonitorObserver
    void NotifyStarvationMonitorBuffering(TBool aBuffering);
private:
    enum EMsgType
    {
        ENone
       ,EMsgAudioPcm
       ,EMsgSilence
       ,EMsgPlayable
       ,EMsgAudoiFormat
       ,EMsgTrack
       ,EMsgMetaText
       ,EMsgHalt
       ,EMsgFlush
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
    InfoAggregator iInfoAggregator;
    StarvationMonitor* iSm;
    EMsgType iLastMsg;
    EMsgGenerationState iMsgGenerationState;
    Semaphore iSemUpstream;
    Semaphore iSemUpstreamCompleted;
    TUint64 iTrackOffset;
    TBool iBuffering;
};

} // namespace Media
} // namespace OpenHome


// InfoAggregator

InfoAggregator::InfoAggregator()
{
}

void InfoAggregator::PrintStats()
{
    for (size_t i=0; i<iInfoProviders.size(); i++) {
        iInfoProviders[i]->QueryInfo(AllocatorBase::kQueryMemory, *this);
    }
}

void InfoAggregator::Register(Av::IInfoProvider& aProvider, std::vector<Brn>& /*aSupportedQueries*/)
{
    iInfoProviders.push_back(&aProvider);
}

void InfoAggregator::Write(TByte aValue)
{
    Print("%c", aValue);
}

void InfoAggregator::Write(const Brx& aBuffer)
{
    Print(aBuffer);
}

void InfoAggregator::WriteFlush()
{
}


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
    iMsgFactory = new MsgFactory(iInfoAggregator, kDecodedAudioCount, kMsgAudioPcmCount, kMsgSilenceCount, 1, 1, 1, 1, 1, 1, 1, 1);
    iSm = new StarvationMonitor(*iMsgFactory, *this, *this, kRegularSize, kStarvationThreshold, kGorgeSize, kRampUpSize);
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
        Add 0xff filled audio.  Repeat until would block.  Check size is >= kGorgeSize.
        Pull all audio.  Check the last bit ramps down.
        Check halt message is sent and pull would then block
        Start filling with 0xff filled audio again.  Check pull would still block as we grow beyond regular limit
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

    // Add 0xff filled audio.  Repeat until would block.  Check size is >= kGorgeSize.
    GenerateUpstreamMsgs(EStateAudioFillInitial);
    while (iSm->Jiffies() < kGorgeSize) {
        Thread::Sleep(10); // last msg may not quite have been enqueued when we switched threads
    }
    TEST(iSm->EnqueueWouldBlock());
    TEST(!iSm->PullWouldBlock());
    TEST(iSm->iStatus == StarvationMonitor::ERunning);
    TEST(!iBuffering);

    Msg* msg;
    // Pull all audio.  Check the last bit ramps down.
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
    msg = iSm->Pull();
    (void)msg->Process(*this);
    TEST(iLastMsg == EMsgHalt);
    msg->RemoveRef();
    TEST(iSm->PullWouldBlock());

    // Start filling with 0xff filled audio again.  Check pull would still block as we grow beyond regular limit
    // Continue adding audio until we reach gorge size.  Check enqueue would now block.
    GenerateUpstreamMsgs(EStateAudioFillPostStarvation);
    WaitForEnqueueToBlock();
    TEST(!iBuffering);

    // Pull audio.  Check it ramps up.
    TUint jiffies = iSm->Jiffies();
    do {
        TEST(!iSm->PullWouldBlock());
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
        TEST(iSm->EnqueueWouldBlock());
    } while (iSm->iStatus == StarvationMonitor::ERampingUp);
    TEST(jiffies - iSm->Jiffies() == kRampUpSize);
    TEST(iSm->iStatus == StarvationMonitor::ERunning);
    TEST(!iBuffering);

    // Check enqueues would block until size drops below normal max
    do {
        TEST(!iSm->PullWouldBlock());
        TEST(iSm->EnqueueWouldBlock());
        msg = iSm->Pull();
        (void)msg->Process(*this);
        TEST(iLastMsg == EMsgAudioPcm);
    } while (iSm->Jiffies() > kRegularSize);
    TEST(!iBuffering);

    // Add Halt.  Check queue can be drained without ramping down
    GenerateUpstreamMsgs(EStateHalt);
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
        if (iSm->Jiffies() + msg->Jiffies() >= kGorgeSize) {
            iMsgGenerationState = EStateWait;
            iSemUpstreamCompleted.Signal();
        }
        return msg;
    }
    case EStateAudioFillPostStarvation:
    {
        MsgAudio* msg = CreateAudio();
        if (iSm->Jiffies() + msg->Jiffies() >= kGorgeSize) {
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
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, 16, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgAudioPcm* aMsg)
{
    iLastMsg = EMsgAudioPcm;
    MsgPlayable* playable = aMsg->CreatePlayable();
    WriterBwh writerBuf(1024);
    playable->Write(writerBuf);
    Brh buf;
    writerBuf.TransferTo(buf);
    const TUint* ptr = (const TUint*)buf.Ptr();
    const TUint firstSubsample = ptr[0];
    const TUint numSubsamples = buf.Bytes() / sizeof(TUint);
    const TUint lastSubsample = ptr[numSubsamples - 1];

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

Msg* SuiteStarvationMonitor::ProcessMsg(MsgAudioFormat* /*aMsg*/)
{
    ASSERTS(); // MsgAudioFormat not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS(); // MsgTrack not used in this test
    return NULL;
}

Msg* SuiteStarvationMonitor::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS(); // MsgMetaText not used in this test
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


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestStarvationMonitor();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
