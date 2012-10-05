#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/RampArray.h>

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

class Supplier : public Thread, public ISupplier
{
    static const TUint kBitDepth    = 16;
    static const TUint kSampleRate  = 44100;
    static const TUint kNumChannels = 2;
public:
    Supplier();
    ~Supplier();
    void Block();
    void Unblock();
private: // from Thread
    void Run();
private:
    MsgAudio* CreateAudio();
private: // from ISupplier
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void Play();
    void Flush(Msg* aMsg);
    void Quit(Msg* aMsg);
private:
    Mutex iLock;
    Semaphore iBlocker;
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    Msg* iPendingMsg;
    TBool iBlock;
    TBool iQuit;
    TUint64 iTrackOffset;
};

class SuitePipeline : public Suite, private IPipelineObserver, private IMsgProcessor
{
public:
    SuitePipeline();
private: // from Suite
    ~SuitePipeline();
    void Test();
private:
    enum EState
    {
        ERampDownDeferred
       ,ERampDown
       ,ERampUpDeferred
       ,ERampUp
    };
private:
    void PullUntilEnd(EState aState);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyAudioFormat(const AudioFormat& aFormat);
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
private:
    InfoAggregator iInfoAggregator;
    Supplier* iSupplier;
    PipelineManager* iPipelineManager;
    IPipelineElementUpstream* iPipelineEnd;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iJiffies;
    TUint iLastMsgJiffies;
    TBool iLastMsgWasAudio;
    TUint iFirstSubsample;
    TUint iLastSubsample;
    EPipelineState iPipelineState;
};
#undef LOG_PIPELINE_OBSERVER // enable this to check output from IPipelineObserver

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


// Supplier

Supplier::Supplier()
    : Thread("TSUP")
    , iLock("TSUP")
    , iBlocker("TSUP", 0)
    , iMsgFactory(NULL)
    , iPipeline(NULL)
    , iPendingMsg(NULL)
    , iBlock(true)
    , iQuit(false)
    , iTrackOffset(0)
{
}

Supplier::~Supplier()
{
    Join();
}

void Supplier::Block()
{
    iBlock = true;
    (void)iBlocker.Clear();
}

void Supplier::Unblock()
{
    iBlocker.Signal();
    iBlock = false;
}

void Supplier::Run()
{
    Msg* msg = iMsgFactory->CreateMsgTrack();
    iPipeline->Push(msg);
    msg = iMsgFactory->CreateMsgAudioFormat(3, kBitDepth, kSampleRate, kNumChannels, Brn("dummy codec"), 1LL<<34, false);
    iPipeline->Push(msg);
    while (!iQuit) {
        if (iBlock) {
            iBlocker.Wait();
        }
        iLock.Wait();
        if (iPendingMsg != NULL) {
            msg = iPendingMsg;
            iPendingMsg = NULL;
        }
        else {
            msg = CreateAudio();
        }
        iLock.Signal();
        iPipeline->Push(msg);
    }
    if (iPendingMsg != NULL) {
        iPipeline->Push(iPendingMsg);
        iPendingMsg = NULL;
    }
}

MsgAudio* Supplier::CreateAudio()
{
    static const TUint kDataBytes = 3 * 1024;
    TByte encodedAudioData[kDataBytes];
    (void)memset(encodedAudioData, 0xff, kDataBytes);
    Brn encodedAudioBuf(encodedAudioData, kDataBytes);
    MsgAudioPcm* audio = iMsgFactory->CreateMsgAudioPcm(encodedAudioBuf, kNumChannels, kSampleRate, kBitDepth, EMediaDataLittleEndian, iTrackOffset);
    iTrackOffset += audio->Jiffies();
    return audio;
}

void Supplier::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
{
    iMsgFactory = &aMsgFactory;
    iPipeline = &aDownstreamElement;
    Start();
}

void Supplier::Play()
{
    Unblock();
}

void Supplier::Flush(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    iLock.Signal();
}

void Supplier::Quit(Msg* aMsg)
{
    iLock.Wait();
    iPendingMsg = aMsg;
    iQuit = true;
    iLock.Signal();
}


// SuitePipeline

SuitePipeline::SuitePipeline()
    : Suite("Pipeline integration tests")
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffies(0)
    , iLastMsgJiffies(0)
    , iFirstSubsample(0)
    , iLastSubsample(0)
    , iPipelineState(EPipelineStopped)
{
    iSupplier = new Supplier();
    iPipelineManager = new PipelineManager(iInfoAggregator, *iSupplier, *this);
    iPipelineEnd = &iPipelineManager->FinalElement();
}

SuitePipeline::~SuitePipeline()
{
    delete iPipelineManager;
    delete iSupplier;
}

void SuitePipeline::Test()
{
    /*
    Test goes something like
        Push audio.  Repeat until our dummy driver can start pulling.
        Check audio ramps up for kStopperRampDuration jiffies.
        Check that pipeline status goes from Buffering to Playing.
        Duration of ramp should have been PipelineManager::kStopperRampDuration.
        Check that subsequent audio isn't ramped.
        Stop pushing audio.  Check that pipeline status eventually goes from Playing to Buffering.
        Check that audio then ramps down in ~PipelineManager::kStarvationMonitorStarvationThreshold.
        ...will actually take up to duration of 1 MsgAudioPcm extra.
        Push audio again.  Check that it ramps up in PipelineManager::kStarvationMonitorRampUpDuration.
        Set 1s delay.  Check for ramp down in PipelineManager::kVariableDelayRampDuration then 1s seilence then ramp up.
        Reduce delay to 0.  Check for ramp down then up, each in in PipelineManager::kVariableDelayRampDuration.
        Pause.  Check for ramp down in PipelineManager::kStopperRampDuration.
        Resume.  Check for ramp up in PipelineManager::kStopperRampDuration.
        Stop.  Check for ramp down in PipelineManager::kStopperRampDuration.
        Quit happens when iPipelineManager is deleted in d'tor.
    */

    // Push audio.  Repeat until our dummy driver can start pulling.
    // Check audio ramps up for kStopperRampDuration jiffies.
    // Check that pipeline status goes from Buffering to Playing.
    // Duration of ramp should have been PipelineManager::kStopperRampDuration.
    Print("Run until ramped up\n");
    iPipelineManager->Play();
    PullUntilEnd(ERampUp);
    TEST(iJiffies == PipelineManager::kStopperRampDuration);
    // skip earlier test for EPipelineBuffering state as it'd be fiddly to do in a threadsafe way
    TEST(iPipelineState == EPipelinePlaying);

    // Check that subsequent audio isn't ramped.
    // Stop pushing audio.  Check that pipeline status eventually goes from Playing to Buffering.
    // Check that audio then ramps down in ~PipelineManager::kStarvationMonitorStarvationThreshold.
    // ...will actually take up to duration of 1 MsgAudioPcm extra.
    Print("\nSimulate starvation\n");
    iJiffies = 0;
    iSupplier->Block();
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelineBuffering);
    TEST((iJiffies >= PipelineManager::kStarvationMonitorStarvationThreshold) &&
         (iJiffies <  PipelineManager::kStarvationMonitorStarvationThreshold + iLastMsgJiffies));

    // Push audio again.  Check that it ramps up in PipelineManager::kStarvationMonitorRampUpDuration.
    Print("\nRecover from starvation\n");
    iJiffies = 0;
    iSupplier->Unblock();
    PullUntilEnd(ERampUp);
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iJiffies == PipelineManager::kStarvationMonitorRampUpDuration);

    // Set 1s delay.  Check for ramp down in PipelineManager::kVariableDelayRampDuration then 1s seilence then ramp up.
    // FIXME - can't set VariableDelay via PipelineManager

    // Reduce delay to 0.  Check for ramp down then up, each in in PipelineManager::kVariableDelayRampDuration.
    // FIXME - can't set VariableDelay via PipelineManager

    // Pause.  Check for ramp down in PipelineManager::kStopperRampDuration.
    Print("\nPause\n");
    iJiffies = 0;
    iPipelineManager->Pause();
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelinePaused);
    TEST(iJiffies == PipelineManager::kStopperRampDuration);

    // Resume.  Check for ramp up in PipelineManager::kStopperRampDuration.
    Print("\nResume\n");
    iJiffies = 0;
    iPipelineManager->Play();
    PullUntilEnd(ERampUp);
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iJiffies == PipelineManager::kStopperRampDuration);

    // Stop.  Check for ramp down in PipelineManager::kStopperRampDuration.
    Print("\nStop\n");
    iJiffies = 0;
    iPipelineManager->Stop();
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelineStopped);
    TEST(iJiffies == PipelineManager::kStopperRampDuration);

    // Quit happens when iPipelineManager is deleted in d'tor.
    Print("\nQuit\n");
}

void SuitePipeline::PullUntilEnd(EState aState)
{
    static const TUint kSubsampleRampedUpFull = 0xffff0000;
    static const TUint kSubsampleRampUpFinal = (TUint)(((TUint64)kSubsampleRampedUpFull * kRampArray[0]) >> 31) & ~0xff;
    static const TUint kSubsampleRampedDownFull = 0;
    TBool ramping = (aState == ERampDown || aState == ERampUp);
    TBool done = false;
    do {
        Msg* msg = iPipelineEnd->Pull();
        (void)msg->Process(*this);
        if (!iLastMsgWasAudio) {
            continue;
        }
        switch (aState)
        {
        case ERampDownDeferred:
            if (!ramping) {
                if (iFirstSubsample == iLastSubsample) {
                    iJiffies = 0;
                    TEST(iFirstSubsample == kSubsampleRampedUpFull);
                    break;
                }
                ramping = true;
            }
            // fallthrough
        case ERampDown:
            TEST(iFirstSubsample > iLastSubsample);
            if (iLastSubsample == kSubsampleRampedDownFull) {
                done = true;
            }
            break;
        case ERampUpDeferred:
            if (!ramping) {
                if (iFirstSubsample == iLastSubsample) {
                    iJiffies = 0;
                    TEST(iFirstSubsample == kSubsampleRampedDownFull);
                    break;
                }
                ramping = true;
            }
            // fallthrough
            break;
        case ERampUp:
            TEST(iFirstSubsample < iLastSubsample);
            if (iLastSubsample == kSubsampleRampUpFinal) {
                done = true;
            }
            break;
        }
    }
    while (!done);
    if (aState == ERampDownDeferred || aState == ERampDown) {
        TEST(iPipelineState != EPipelinePlaying);
    }
    else {
        TEST(iPipelineState == EPipelinePlaying);
    }
}

void SuitePipeline::NotifyPipelineState(EPipelineState aState)
{
    iPipelineState = aState;
#ifdef LOG_PIPELINE_OBSERVER
    const char* state = "";
    switch (aState)
    {
    case EPipelinePlaying:
        state = "playing";
        break;
    case EPipelinePaused:
        state = "paused";
        break;
    case EPipelineStopped:
        state = "stopped";
        break;
    case EPipelineBuffering:
        state = "buffering";
        break;
    default:
        ASSERTS();
    }
    Print("Pipeline state change: %s\n", state);
#endif
}

#ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
# pragma warning(disable:4100)
#endif
void SuitePipeline::NotifyTrack()
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: TRACK\n");
#endif
}

void SuitePipeline::NotifyMetaText(const Brx& aText)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: METATEXT {");
    Print(aText);
    Print("}\n");
#endif
}

void SuitePipeline::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
#endif
}

void SuitePipeline::NotifyAudioFormat(const AudioFormat& aFormat)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aFormat.BitRate(), aFormat.BitDepth(), aFormat.SampleRate(), aFormat.NumChannels());
    Print(aFormat.CodecName());
    Print("; trackLength=%llx, lossless=%u}\n", aFormat.TrackLength(), aFormat.Lossless());
#endif
}

Msg* SuitePipeline::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgPlayable* aMsg)
{
    iLastMsgWasAudio = true;
    WriterBwh writerBuf(1024);
    aMsg->Write(writerBuf);
    Brh buf;
    writerBuf.TransferTo(buf);
    const TUint* ptr = (const TUint*)buf.Ptr();
    iFirstSubsample = ptr[0];
    const TUint numSubsamples = buf.Bytes() / sizeof(TUint);
    iLastSubsample = ptr[numSubsamples - 1];
    ASSERT(numSubsamples % iNumChannels == 0);
    iLastMsgJiffies = Jiffies::JiffiesPerSample(iSampleRate) * (numSubsamples / iNumChannels);
    iJiffies += iLastMsgJiffies;
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgAudioFormat* aMsg)
{
    iLastMsgWasAudio = false;
    iSampleRate = aMsg->Format().SampleRate();
    iNumChannels = aMsg->Format().NumChannels();
    aMsg->RemoveRef();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsgWasAudio = false;
    aMsg->RemoveRef();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgQuit* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}



void TestPipeline()
{
    Runner runner("Pipeline integration tests\n");
    runner.Add(new SuitePipeline());
    runner.Run();
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Net::UpnpLibrary::InitialiseMinimal(aInitParams);
    TestPipeline();
    delete aInitParams;
    Net::UpnpLibrary::Close();
}
