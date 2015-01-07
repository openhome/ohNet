#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/RampArray.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/Utils/Aggregator.h>

#include <string.h>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

namespace OpenHome {
namespace Media {

class Supplier : public Thread, private IStreamHandler
{
public:
    Supplier(ISupply& aSupply, TrackFactory& aTrackFactory);
    ~Supplier();
    void Block();
    void Unblock();
    void SendFlush(TUint aFlushId);
    void Exit(TUint aHaltId);
private: // from Thread
    void Run();
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private:
    ISupply& iSupply;
    TrackFactory& iTrackFactory;
    Mutex iLock;
    Semaphore iBlocker;
    TBool iBlock;
    TBool iQuit;
    TUint iFlushId;
    TUint iHaltId;
};

class SuitePipeline : public Suite, private IPipelineObserver, private IMsgProcessor, private IStreamPlayObserver, private ISeekRestreamer
{
    static const TUint kBitDepth    = 24;
    static const TUint kSampleRate  = 192000;
    static const TUint kNumChannels = 2;
    static const TUint kDriverMaxAudioJiffies = Jiffies::kPerMs * 5;
    static const TUint kSubsampleRampedUpFull = 0x7f7f7f;
    static const TUint kSubsampleRampedDownFull = 0;
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
    void TestJiffies(TUint aTarget);
    void PullNextAudio();
    void PullUntilEnd(EState aState);
    void PullUntilQuit();
    void TestRampingDownStarts(TUint aMaxMsgs);
    void TestRampingUpStartsFromPartialRampDown(TUint aMaxMsgs);
    void TestRampsUp(TUint aMaxMsgs);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // from IStreamPlayObserver
    void NotifyTrackFailed(TUint aTrackId);
    void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus);
private: // from ISeekRestreamer
    TUint SeekRestream(const Brx& aMode, TUint aTrackId);
private:
    AllocatorInfoLogger iInfoAggregator;
    Supplier* iSupplier;
    PipelineInitParams* iInitParams;
    Pipeline* iPipeline;
    Aggregator* iAggregator;
    TrackFactory* iTrackFactory;
    IPipelineElementUpstream* iPipelineEnd;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iBitDepth;
    TUint iJiffies;
    TUint iLastMsgJiffies;
    TBool iLastMsgWasAudio;
    TUint iFirstSubsample;
    TUint iLastSubsample;
    EPipelineState iPipelineState;
    TUint iStateChangeCount;
    Semaphore iSemFlushed;
    Semaphore iSemQuit;
    TBool iQuitReceived;
};

// Trivial codec which accepts all content and does a 1-1 translation between encoded and decoded audio
class DummyCodec : public CodecBase
{
public:
    DummyCodec(TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian);
private: // from CodecBase
    void StreamInitialise();
    TBool SupportsMimeType(const Brx& aMimeType);
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    EMediaDataEndian iEndian;
    TUint64 iTrackOffsetJiffies;
    TBool iSentDecodedInfo;
};

#undef LOG_PIPELINE_OBSERVER // enable this to check output from IPipelineObserver

} // namespace Media
} // namespace OpenHome


// Supplier

Supplier::Supplier(ISupply& aSupply, TrackFactory& aTrackFactory)
    : Thread("TSUP")
    , iSupply(aSupply)
    , iTrackFactory(aTrackFactory)
    , iLock("TSUP")
    , iBlocker("TSUP", 0)
    , iBlock(false)
    , iQuit(false)
    , iFlushId(MsgFlush::kIdInvalid)
    , iHaltId(MsgHalt::kIdInvalid)
{
    Start();
}

Supplier::~Supplier()
{
    Kill();
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

void Supplier::SendFlush(TUint aFlushId)
{
    iFlushId = aFlushId;
}

void Supplier::Exit(TUint aHaltId)
{
    iHaltId = aHaltId;
    iQuit = true;
}

void Supplier::Run()
{
    TByte encodedAudioData[EncodedAudio::kMaxBytes];
    (void)memset(encodedAudioData, 0x7f, sizeof(encodedAudioData));
    Brn encodedAudioBuf(encodedAudioData, sizeof(encodedAudioData));

    Track* track = iTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
    iSupply.OutputTrack(*track, 1);
    track->RemoveRef();
    iSupply.OutputStream(Brx::Empty(), 1LL<<32, false, false, *this, 1);
    while (!iQuit) {
        CheckForKill();
        if (iBlock) {
            iBlocker.Wait();
        }
        if (iFlushId != MsgFlush::kIdInvalid) {
            iSupply.OutputFlush(iFlushId);
            iFlushId = MsgFlush::kIdInvalid;
        }
        else {
            iSupply.OutputData(encodedAudioBuf);
        }
        Thread::Sleep(2); // small delay to avoid this thread hogging all cpu on platforms without priorities
    }
    iSupply.OutputHalt(iHaltId);
    iSupply.OutputQuit();
}

EStreamPlay Supplier::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return ePlayYes;
}

TUint Supplier::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Supplier::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

TBool Supplier::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    ASSERTS();
    return false;
}

void Supplier::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}


// SuitePipeline

SuitePipeline::SuitePipeline()
    : Suite("Pipeline integration tests")
    , iSampleRate(0)
    , iNumChannels(0)
    , iBitDepth(0)
    , iJiffies(0)
    , iLastMsgJiffies(0)
    , iFirstSubsample(0)
    , iLastSubsample(0)
    , iPipelineState(EPipelineStopped)
    , iStateChangeCount(0)
    , iSemFlushed("TPSF", 0)
    , iSemQuit("TPSQ", 0)
    , iQuitReceived(false)
{
    iInitParams = PipelineInitParams::New();
    iPipeline = new Pipeline(iInitParams, iInfoAggregator, *this, *this, *this);
    iAggregator = new Aggregator(*iPipeline, kDriverMaxAudioJiffies);
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iSupplier = new Supplier(*iPipeline, *iTrackFactory);
    iPipeline->AddCodec(new DummyCodec(kNumChannels, kSampleRate, kBitDepth, EMediaDataEndianLittle));
    iPipeline->Start();
    iPipelineEnd = iAggregator;
}

SuitePipeline::~SuitePipeline()
{
    iSupplier->Exit(0);
    // Pipeline d'tor will block until the driver pulls a Quit msg
    // we've been cheating by running a driver in this thread up until now
    // ...so we cheat some more by creating a worker thread to pull until Quit is read
    ThreadFunctor* th = new ThreadFunctor("QUIT", MakeFunctor(*this, &SuitePipeline::PullUntilQuit));
    th->Start();
    iPipeline->Quit();
    iSemQuit.Wait();
    delete iSupplier;
    delete iAggregator;
    delete iPipeline;
    delete iTrackFactory;
    delete th;
}

void SuitePipeline::Test()
{
    /*
    Test goes something like
        Push audio.  Repeat until our dummy driver can start pulling.
        Check audio ramps up for kStopperRampDuration jiffies.
        Check that pipeline status goes from Buffering to Playing.
        Duration of ramp should have been Pipeline::kStopperRampDuration.
        Check that subsequent audio isn't ramped.
        Stop pushing audio.  Check that pipeline status eventually goes from Playing to Buffering.
        Check that audio then ramps down in ~Pipeline::kStarvationMonitorStarvationThreshold.
        ...will actually take up to duration of 1 MsgAudioPcm extra.
        Push audio again.  Check that it ramps up in Pipeline::kStarvationMonitorRampUpDuration.
        Set 1s delay.  Check for ramp down in Pipeline::kVariableDelayRampDuration then 1s seilence then ramp up.
        Reduce delay to 0.  Check for ramp down then up, each in in Pipeline::kVariableDelayRampDuration.
        Pause.  Check for ramp down in Pipeline::kStopperRampDuration.
        Resume.  Check for ramp up in Pipeline::kStopperRampDuration.
        Stop.  Check for ramp down in Pipeline::kStopperRampDuration.
        Quit happens when iPipeline is deleted in d'tor.
    */

    // Push audio.  Repeat until our dummy driver can start pulling.
    // Check audio ramps up for kStopperRampDuration jiffies.
    // Check that pipeline status goes from Buffering to Playing.
    // There should not be any ramp        Duration of ramp should have been Pipeline::kStopperRampDuration.
    Print("Run until ramped up\n");
    iPipeline->Play();
    do {
        iPipelineEnd->Pull()->Process(*this);
    } while (!iLastMsgWasAudio);
    TEST(iFirstSubsample == iLastSubsample);
    // skip earlier test for EPipelineBuffering state as it'd be fiddly to do in a threadsafe way
    TEST(iPipelineState == EPipelinePlaying);

    // Check that subsequent audio isn't ramped.
    // Stop pushing audio.  Check that pipeline status eventually goes from Playing to Buffering.
    // Check that audio then ramps down in ~Pipeline::kStarvationMonitorStarvationThreshold.
    // ...will actually take up to duration of 1 MsgAudioPcm extra.
    Print("\nSimulate starvation\n");
    iJiffies = 0;
    iSupplier->Block();
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelineBuffering);
    TEST((iJiffies >= iInitParams->StarvationMonitorMinJiffies()) &&
         (iJiffies <= iInitParams->StarvationMonitorMinJiffies() + iLastMsgJiffies + kDriverMaxAudioJiffies));

    // Push audio again.  Check that it ramps up in Pipeline::kStarvationMonitorRampUpDuration.
    Print("\nRecover from starvation\n");
    iJiffies = 0;
    iSupplier->Unblock();
    PullUntilEnd(ERampUp);
    TEST(iPipelineState == EPipelinePlaying);
    TestJiffies(iInitParams->RampShortJiffies());

    // Set 1s delay.  Check for ramp down in Pipeline::kVariableDelayRampDuration then 1s silence then ramp up.
    // FIXME - can't set VariableDelay via Pipeline

    // Reduce delay to 0.  Check for ramp down then up, each in in Pipeline::kVariableDelayRampDuration.
    // FIXME - can't set VariableDelay via Pipeline

    // Pause.  Check for ramp down in Pipeline::kStopperRampDuration.
    Print("\nPause\n");
    iJiffies = 0;
    iPipeline->Pause();
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelinePaused);
    TestJiffies(iInitParams->RampLongJiffies());

    // Resume.  Check for ramp up in Pipeline::kStopperRampDuration.
    Print("\nResume\n");
    iJiffies = 0;
    iPipeline->Play();
    PullUntilEnd(ERampUp);
    TEST(iPipelineState == EPipelinePlaying);
    TestJiffies(iInitParams->RampLongJiffies());

    // Wait. Check for ramp down in Pipeline::kWaiterRampDuration.
    // Send down expected MsgFlush, then check for ramp up in
    // Pipeline::kWaiterRampDuration.
    Print("\nWait\n");
    iJiffies = 0;
    static const TUint kFlushId = 5; // randomly chosen value
    iPipeline->Wait(kFlushId);
    PullUntilEnd(ERampDownDeferred);
    TEST(iPipelineState == EPipelineWaiting);
    TestJiffies(iInitParams->RampShortJiffies());
    // push flush, then ramp back up
    iJiffies = 0;
    iSupplier->SendFlush(kFlushId);
    PullUntilEnd(ERampUp);
    TEST(iPipelineState == EPipelinePlaying);
    TestJiffies(iInitParams->RampShortJiffies());


    // Test pause with partial ramp down before play is called.
    Print("\nPause->Play with partial ramp down\n");
    static const TUint kMaxMsgs = 50;
    TUint initialStateChangeCount = iStateChangeCount;
    iJiffies = 0;
    iPipeline->Pause();
    TestRampingDownStarts(kMaxMsgs);
    // Now, play pipeline again.
    // Check ramping up starts before ramping down reaches end.
    iPipeline->Play();
    TestRampingUpStartsFromPartialRampDown(kMaxMsgs);
    // Check ramping up from partial ramp down completes.
    TestRampsUp(kMaxMsgs);
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iStateChangeCount == initialStateChangeCount+1); // shouldn't have changed from EPipelinePlaying, but may have received another notification


    // Test pause followed by play with no audio pulled in between.
    Print("\nPause->Play with no ramp down\n");
    initialStateChangeCount = iStateChangeCount;
    iJiffies = 0;
    iPipeline->Pause();
    iPipeline->Play();
    const TUint kTestMsgs = 50;
    // Pull kTestMsgs and check there is no ramping.
    for (TUint i=0; i<kTestMsgs; i++) {
        PullNextAudio();
        TEST(iFirstSubsample == iLastSubsample);
        Thread::Sleep(iLastMsgJiffies / Jiffies::kPerMs); // ensure StarvationMonitor doesn't kick in
    }
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iStateChangeCount == initialStateChangeCount+1); // // shouldn't have changed from EPipelinePlaying, but may have received another notification


    // Stop.  Check for ramp down in Pipeline::kStopperRampDuration.
    Print("\nStop\n");
    iJiffies = 0;
    static const TUint kHaltId = 10; // randomly chosen value
    iPipeline->Stop(kHaltId);
    PullUntilEnd(ERampDownDeferred);
    iSupplier->Exit(kHaltId);
    iSemFlushed.Wait();
    TEST(iPipelineState == EPipelineStopped);
    TestJiffies(iInitParams->RampLongJiffies());

    // Quit happens when iPipeline is deleted in d'tor.
    Print("\nQuit\n");
}

void SuitePipeline::TestJiffies(TUint aTarget)
{
    // MsgPlayable instances are grouped together into msgs of kDriverMaxAudioJiffies
    // This means that msgs don't typically end at the end of a ramp
    // ...so we'll read a bit more data than expected when checking ramp durations
    TEST(aTarget <= iJiffies);
    TEST(iJiffies - aTarget <= kDriverMaxAudioJiffies);
}

void SuitePipeline::PullNextAudio()
{
    TBool done = false;
    while (!done) {
        Msg* msg = iPipelineEnd->Pull();
        (void)msg->Process(*this);
        if (iLastMsgWasAudio) {
            done = true;
        }
    }
}

void SuitePipeline::PullUntilEnd(EState aState)
{
    static const TUint kSubsampleRampUpFinal = (TUint)(((TUint64)kSubsampleRampedUpFull * kRampArray[0]) >> 31) & kSubsampleRampedUpFull;
    TBool ramping = (aState == ERampDown || aState == ERampUp);
    TBool done = false;
    do {
        Msg* msg = iPipelineEnd->Pull();
        (void)msg->Process(*this);
        if (!iLastMsgWasAudio) {
            continue;
        }
        // Introduce a delay to avoid the risk of this thread pulling data faster than the supplier can push it
        // ...which would cause the starvation monitor to kick in at unpredictable times.
        Thread::Sleep(iLastMsgJiffies / Jiffies::kPerMs);
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
            if (iFirstSubsample >= iLastSubsample) {
                Print("Ramping up - first=%08x, last=%08x\n", iFirstSubsample, iLastSubsample);
            }
            if (iLastSubsample >= kSubsampleRampUpFinal && iLastSubsample <= kSubsampleRampedUpFull) {
                done = true;
            }
            break;
        }
    }
    while (!done);
}

void SuitePipeline::PullUntilQuit()
{
    do {
        Msg* msg = iPipelineEnd->Pull();
        (void)msg->Process(*this);
    } while (!iQuitReceived);
    iSemQuit.Signal();
}

void SuitePipeline::TestRampingDownStarts(TUint aMaxMsgs)
{
    TBool rampingDown = false;
    for (TUint i=0; i<aMaxMsgs; i++) {
        PullNextAudio();
        //Log::Print("SuitePipeline::TestRampingDownStarts iFirstSubsample: %x, iLastSubsample: %x\n", iFirstSubsample, iLastSubsample);
        if (iFirstSubsample == iLastSubsample) {
            TEST(iFirstSubsample == kSubsampleRampedUpFull);
        }
        else {
            rampingDown = true;
            break;
        }
        Thread::Sleep(iLastMsgJiffies / Jiffies::kPerMs);
    }
    TEST(rampingDown);
    TEST(iFirstSubsample > iLastSubsample);
}

void SuitePipeline::TestRampingUpStartsFromPartialRampDown(TUint aMaxMsgs)
{
    TBool rampingUp = false;
    for (TUint i=0; i<aMaxMsgs; i++) {
        PullNextAudio();
        //Log::Print("SuitePipeline::TestRampingUpStartsFromPartialRampDown iFirstSubsample: %x, iLastSubsample: %x\n", iFirstSubsample, iLastSubsample);
        if (iFirstSubsample < iLastSubsample) {
            rampingUp = true;
            break;
        }
        Thread::Sleep(iLastMsgJiffies / Jiffies::kPerMs);
    }
    TEST(rampingUp);
    TEST(iLastSubsample > kSubsampleRampedDownFull);
}

void SuitePipeline::TestRampsUp(TUint aMaxMsgs)
{
    TBool finishedRamping = false;
    for (TUint i=0; i<aMaxMsgs; i++) {
        PullNextAudio();
        //Log::Print("SuitePipeline::TestRampsUp iFirstSubsample: %x, iLastSubsample: %x\n", iFirstSubsample, iLastSubsample);
        if (iFirstSubsample == iLastSubsample) {
            finishedRamping = true;
            break;
        }
        Thread::Sleep(iLastMsgJiffies / Jiffies::kPerMs); // ensure StarvationMonitor doesn't kick in
    }
    TEST(finishedRamping);
    TEST(iFirstSubsample == kSubsampleRampedUpFull);
}

void SuitePipeline::NotifyPipelineState(EPipelineState aState)
{
    iPipelineState = aState;
    iStateChangeCount++;
    if (aState == EPipelineStopped) {
        iSemFlushed.Signal();
    }
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline state change: %s\n", TransportState::FromPipelineState(aState));
#endif
}

#ifdef _WIN32
// suppress 'unreferenced formal parameter' warnings which come and go depending
// on the state of LOG_PIPELINE_OBSERVER
# pragma warning(disable:4100)
#endif
void SuitePipeline::NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: TRACK {uri=");
    Print(aTrack.Uri());
    Print("; metadata=");
    Print(aTrack.MetaData());
    Print("; mode=");
    Print(aMode);
    Print("; providerId=");
    Print(aTrack.ProviderId());
    Print("; idPipeline=%u}\n", aIdPipeline);
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

void SuitePipeline::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
           aFormat.BitRate(), aFormat.BitDepth(), aFormat.SampleRate(), aFormat.NumChannels());
    Print(aFormat.CodecName());
    Print("; trackLength=%llx, lossless=%u}\n", aFormat.TrackLength(), aFormat.Lossless());
#endif
}

Msg* SuitePipeline::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
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

Msg* SuitePipeline::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsgWasAudio = false;
    iSampleRate = aMsg->StreamInfo().SampleRate();
    iNumChannels = aMsg->StreamInfo().NumChannels();
    iBitDepth = aMsg->StreamInfo().BitDepth();
    aMsg->RemoveRef();
    return NULL;
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
    ProcessorPcmBufPacked pcmProcessor;
    aMsg->Read(pcmProcessor);
    Brn buf(pcmProcessor.Buf());
    ASSERT(buf.Bytes() == aMsg->Bytes());
    aMsg->RemoveRef();
    const TByte* ptr = buf.Ptr();
    const TUint bytes = buf.Bytes();
    switch (iBitDepth)
    {
    case 8:
        iFirstSubsample = ptr[0];
        iLastSubsample = ptr[bytes-1];
        break;
    case 16:
        iFirstSubsample = (ptr[0]<<8) | ptr[1];
        iLastSubsample = (ptr[bytes-2]<<8) | ptr[bytes-1];
        break;
    case 24:
        iFirstSubsample = (ptr[0]<<16) | (ptr[1]<<8) | ptr[2];
        iLastSubsample = (ptr[bytes-3]<<16) | (ptr[bytes-2]<<8) | ptr[bytes-1];
        break;
    default:
        ASSERTS();
    }
    const TUint bytesPerSample = (iBitDepth/8) * iNumChannels;
    ASSERT(bytes % bytesPerSample == 0);
    const TUint numSamples = bytes / bytesPerSample;
    iLastMsgJiffies = Jiffies::JiffiesPerSample(iSampleRate) * numSamples;
    iJiffies += iLastMsgJiffies;
    return NULL;
}

Msg* SuitePipeline::ProcessMsg(MsgQuit* aMsg)
{
    iQuitReceived = true;
    aMsg->RemoveRef();
    return NULL;
}

void SuitePipeline::NotifyTrackFailed(TUint /*aTrackId*/)
{
}

void SuitePipeline::NotifyStreamPlayStatus(TUint /*aTrackId*/, TUint /*aStreamId*/, EStreamPlay /*aStatus*/)
{
}

TUint SuitePipeline::SeekRestream(const Brx& /*aMode*/, TUint /*aTrackId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}


// DummyCodec

DummyCodec::DummyCodec(TUint aChannels, TUint aSampleRate, TUint aBitDepth, EMediaDataEndian aEndian)
    : iChannels(aChannels)
    , iSampleRate(aSampleRate)
    , iBitDepth(aBitDepth)
    , iEndian(aEndian)
{
}

void DummyCodec::StreamInitialise()
{
    iTrackOffsetJiffies = 0;
    iSentDecodedInfo = false;
}

TBool DummyCodec::SupportsMimeType(const Brx& /*aMimeType*/)
{
    return false;
}

TBool DummyCodec::Recognise(const EncodedStreamInfo& /*aStreamInfo*/)
{
    return true;
}

void DummyCodec::Process()
{
    if (!iSentDecodedInfo) {
        const TUint bitRate = iSampleRate * iBitDepth * iChannels;
        iController->OutputDecodedStream(bitRate, iBitDepth, iSampleRate, iChannels, Brn("dummy codec"), 1LL<<34, 0, true);
        iSentDecodedInfo = true;
    }
    else {
        // Don't need any exit condition for loop below.  iController->Read will throw eventually.
        iReadBuf.SetBytes(0);
        iController->Read(iReadBuf, iReadBuf.MaxBytes());
        iTrackOffsetJiffies += iController->OutputAudioPcm(iReadBuf, iChannels, iSampleRate, iBitDepth, iEndian, iTrackOffsetJiffies);
    }
}

TBool DummyCodec::TrySeek(TUint /*aStreamId*/, TUint64 /*aSample*/)
{
    return false;
}


void TestPipeline()
{
    Runner runner("Pipeline integration tests\n");
    runner.Add(new SuitePipeline());
    runner.Run();
}

