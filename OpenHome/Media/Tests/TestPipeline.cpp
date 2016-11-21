#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/RampArray.h>
#include <OpenHome/Media/Utils/AllocatorInfoLogger.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Media/Pipeline/AnalogBypassRamper.h>

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
    Supplier(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream, TrackFactory& aTrackFactory);
    ~Supplier();
    void Block();
    void Unblock();
    void SendFlush(TUint aFlushId);
    void Exit(TUint aHaltId);
private:
    void Drain();
private: // from Thread
    void Run() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    IPipelineElementDownstream& iDownstream;
    TrackFactory& iTrackFactory;
    Mutex iLock;
    Semaphore iBlocker;
    Semaphore iDrain;
    TBool iBlock;
    TBool iQuit;
    TUint iFlushId;
    TUint iHaltId;
};

class SuitePipeline : public Suite
                    , private IPipelineObserver
                    , private IMsgProcessor
                    , private IStreamPlayObserver
                    , private ISeekRestreamer
                    , private IUrlBlockWriter
                    , private IPipelineAnimator
                    , private IAnalogBypassVolumeRamper
{
    static const TUint kBitDepth    = 24;
    static const TUint kSampleRate  = 192000;
    static const TUint kNumChannels = 2;
    static const SpeakerProfile kProfile;
    static const TUint kDriverMaxAudioJiffies = Jiffies::kPerMs * 5;
    static const TUint kSubsampleRampedUpFull = 0x7f7f7f;
    static const TUint kSubsampleRampedDownFull = 0;
public:
    SuitePipeline();
private: // from Suite
    ~SuitePipeline();
    void Test() override;
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
    void WaitForStateChange(EPipelineState aState);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
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
private: // from IStreamPlayObserver
    void NotifyTrackFailed(TUint aTrackId) override;
    void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus) override;
private: // from ISeekRestreamer
    TUint SeekRestream(const Brx& aMode, TUint aTrackId) override;
private: // from IUrlBlockWriter
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
private: // from IPipelineAnimator
    TUint PipelineAnimatorBufferJiffies() override;
    TUint PipelineAnimatorDelayJiffies(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels) override;
private: // from IAnalogBypassVolumeRamper
    void ApplyVolumeMultiplier(TUint aValue) override;
private:
    AllocatorInfoLogger iInfoAggregator;
    Supplier* iSupplier;
    PipelineInitParams* iInitParams;
    Pipeline* iPipeline;
    TrackFactory* iTrackFactory;
    IPipelineElementUpstream* iPipelineEnd;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iBitDepth;
    TUint iJiffies;
    TUint iLastMsgJiffies;
    TBool iLastMsgWasAudio;
    TBool iLastMsgWasDrain;
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
    DummyCodec(TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndian, SpeakerProfile aProfile);
private: // from CodecBase
    void StreamInitialise();
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
private:
    Bws<DecodedAudio::kMaxBytes> iReadBuf;
    TUint iChannels;
    TUint iSampleRate;
    TUint iBitDepth;
    AudioDataEndian iEndian;
    SpeakerProfile iProfile;
    TUint64 iTrackOffsetJiffies;
    TBool iSentDecodedInfo;
};

class PcmProcessorTestPipeline : public IPcmProcessor
{
public:
    TUint FirstSubsample() const;
    TUint LastSubsample() const;
    TUint SampleCount() const;
private:
    inline TUint Subsample8(const TByte* aData) const;
    inline TUint Subsample16(const TByte* aData) const;
    inline TUint Subsample24(const TByte* aData) const;
    inline TUint Subsample32(const TByte* aData) const;
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void EndBlock() override;
    void Flush() override;
private:
    TBool iSetFirstSubsample;
    TUint iFirstSubsample;
    TUint iLastSubsample;
    TUint iSamples;
};

#undef LOG_PIPELINE_OBSERVER // enable this to check output from IPipelineObserver

} // namespace Media
} // namespace OpenHome


// Supplier

Supplier::Supplier(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream, TrackFactory& aTrackFactory)
    : Thread("TSUP")
    , iMsgFactory(aMsgFactory)
    , iDownstream(aDownstream)
    , iTrackFactory(aTrackFactory)
    , iLock("TSUP")
    , iBlocker("TSUP", 0)
    , iDrain("TSP2", 0)
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

void Supplier::Drain()
{
    iDrain.Signal();
}

void Supplier::Run()
{
    TByte encodedAudioData[EncodedAudio::kMaxBytes];
    (void)memset(encodedAudioData, 0x7f, sizeof(encodedAudioData));
    Brn encodedAudioBuf(encodedAudioData, sizeof(encodedAudioData));

    iDownstream.Push(iMsgFactory.CreateMsgDrain(MakeFunctor(*this, &Supplier::Drain)));
    iDrain.Wait();
    Track* track = iTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
    iDownstream.Push(iMsgFactory.CreateMsgTrack(*track));
    iDownstream.Push(iMsgFactory.CreateMsgDelay(Jiffies::kPerMs * 20));
    track->RemoveRef();
    iDownstream.Push(iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1LL<<32, 0, 1, false, false, Multiroom::Allowed, this));
    while (!iQuit) {
        CheckForKill();
        if (iBlock) {
            iBlocker.Wait();
        }
        if (iFlushId != MsgFlush::kIdInvalid) {
            iDownstream.Push(iMsgFactory.CreateMsgFlush(iFlushId));
            iFlushId = MsgFlush::kIdInvalid;
            iDownstream.Push(iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 1LL<<32, 0, 1, false, true, Multiroom::Allowed, this));
        }
        else {
            iDownstream.Push(iMsgFactory.CreateMsgAudioEncoded(encodedAudioBuf));
        }
        Thread::Sleep(2); // small delay to avoid this thread hogging all cpu on platforms without priorities
    }
    iDownstream.Push(iMsgFactory.CreateMsgHalt(iHaltId));
    iDownstream.Push(iMsgFactory.CreateMsgQuit());
}

EStreamPlay Supplier::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayYes;
}

TUint Supplier::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Supplier::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Supplier::TryStop(TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

void Supplier::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}


// SuitePipeline

const SpeakerProfile SuitePipeline::kProfile(2);

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
    iInitParams->SetLongRamp(Jiffies::kPerMs * 150); // reduced size to ensure that 1ms chunks of ramped audio show a change
    iTrackFactory = new TrackFactory(iInfoAggregator, 1);
    iPipeline = new Pipeline(iInitParams, iInfoAggregator, *iTrackFactory, *this, *this, *this, *this);
    iPipeline->SetAnimator(*this);
    iSupplier = new Supplier(iPipeline->Factory(), *iPipeline, *iTrackFactory);
    iPipeline->AddCodec(new DummyCodec(kNumChannels, kSampleRate, kBitDepth, AudioDataEndian::Little, kProfile));
    iPipeline->Start(*this);
    iPipelineEnd = iPipeline;
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
    iLastMsgWasDrain = false;
    iPipelineEnd->Pull()->Process(*this);
    TEST(iLastMsgWasDrain);
    iLastMsgWasDrain = false;
    do {
        iPipelineEnd->Pull()->Process(*this);
    } while (!iLastMsgWasAudio);
    TEST(iFirstSubsample == iLastSubsample);
    // skip earlier test for EPipelineBuffering state as it'd be fiddly to do in a threadsafe way
    WaitForStateChange(EPipelinePlaying);
    TEST(iPipelineState == EPipelinePlaying);

    // Check that subsequent audio isn't ramped.
    // Stop pushing audio.  Check that pipeline status eventually goes from Playing to Buffering.
    // Check that audio then ramps down in ~Pipeline::kStarvationMonitorStarvationThreshold.
    // ...will actually take up to duration of 1 MsgAudioPcm extra.
    Print("\nSimulate starvation\n");
    iJiffies = 0;
    iSupplier->Block();
    PullUntilEnd(ERampDownDeferred);
    WaitForStateChange(EPipelineBuffering);
    TEST(iPipelineState == EPipelineBuffering);
    TEST((iJiffies >= iInitParams->StarvationRamperMinJiffies()) &&
        (iJiffies <= iInitParams->StarvationRamperMinJiffies() + iLastMsgJiffies + kDriverMaxAudioJiffies));

    // Push audio again.  Check that it ramps up in Pipeline::kStarvationMonitorRampUpDuration.
    Print("\nRecover from starvation\n");
    iJiffies = 0;
    iSupplier->Unblock();
    PullUntilEnd(ERampUp);
    WaitForStateChange(EPipelinePlaying);
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
    WaitForStateChange(EPipelinePaused);
    TEST(iPipelineState == EPipelinePaused);
    TestJiffies(iInitParams->RampLongJiffies());

    // Resume.  Check for ramp up in Pipeline::kStopperRampDuration.
    Print("\nResume\n");
    iJiffies = 0;
    iPipeline->Play();
    PullUntilEnd(ERampUpDeferred);
    WaitForStateChange(EPipelinePlaying);
    TEST(iPipelineState == EPipelinePlaying);
    TestJiffies(iInitParams->RampLongJiffies());

#if 0 /* Waiter tests disabled pending decision on whether a new stream must always follow a Wait */
    // Wait. Check for ramp down in Pipeline::kWaiterRampDuration.
    // Send down expected MsgFlush, then check for ramp up in
    // Pipeline::kWaiterRampDuration.
    Print("\nWait\n");
    iJiffies = 0;
    static const TUint kFlushId = 5; // randomly chosen value
    iPipeline->Wait(kFlushId);
    PullUntilEnd(ERampDownDeferred);
    WaitForStateChange(EPipelineWaiting);
    TEST(iPipelineState == EPipelineWaiting);
    TestJiffies(iInitParams->RampShortJiffies());
    // push flush, then ramp back up
    iJiffies = 0;
    iSupplier->SendFlush(kFlushId);
    PullUntilEnd(ERampUp);
    WaitForStateChange(EPipelinePlaying);
    TEST(iPipelineState == EPipelinePlaying);
    TestJiffies(iInitParams->RampShortJiffies());
#endif

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
    WaitForStateChange(EPipelinePlaying);
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iStateChangeCount == initialStateChangeCount);


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
        //Log::Print("iFirstSubsample: %x, iLastSubsample: %x\n", iFirstSubsample, iLastSubsample);
        Thread::Sleep(Jiffies::ToMs(iLastMsgJiffies)); // ensure StarvationMonitor doesn't kick in
    }
    TEST(iFirstSubsample == iLastSubsample);    // only check last message; StarvationMonitor could have kicked in between Pause() and Play() above.
    WaitForStateChange(EPipelinePlaying);
    TEST(iPipelineState == EPipelinePlaying);
    TEST(iStateChangeCount == initialStateChangeCount);


    // Stop.  Check for ramp down in Pipeline::kStopperRampDuration.
    Print("\nStop\n");
    iJiffies = 0;
    iLastMsgWasDrain = false;
    static const TUint kHaltId = 10; // randomly chosen value
    iPipeline->Stop(kHaltId);
    PullUntilEnd(ERampDownDeferred);
    iSupplier->Exit(kHaltId);
    while (!iLastMsgWasDrain) {
        iPipelineEnd->Pull()->Process(*this);
    }
    iSemFlushed.Wait();
    WaitForStateChange(EPipelineStopped);
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
    if (aTarget > iJiffies) {
        Print("  Expected %u (%u), got %u (%u)\n", aTarget, Jiffies::ToMs(aTarget), iJiffies, Jiffies::ToMs(iJiffies));
    }
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
    static const TUint kSubsampleRampUpFinal = (TUint)(((TUint64)kSubsampleRampedUpFull * kRampArray[0]) >> 15) & kSubsampleRampedUpFull;
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
        Thread::Sleep(Jiffies::ToMs(iLastMsgJiffies));
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
            if (iFirstSubsample <= iLastSubsample) {
                Print("Ramping down - first=%08x, last=%08x\n", iFirstSubsample, iLastSubsample);
            }
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
        Thread::Sleep(Jiffies::ToMs(iLastMsgJiffies));
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
        Thread::Sleep(Jiffies::ToMs(iLastMsgJiffies));
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
        Thread::Sleep(Jiffies::ToMs(iLastMsgJiffies)); // ensure StarvationMonitor doesn't kick in
    }
    TEST(finishedRamping);
    TEST(iFirstSubsample == kSubsampleRampedUpFull);
}

void SuitePipeline::WaitForStateChange(EPipelineState aState)
{
    // reporting of state changes is asynchronous...
    TInt retries = 100;
    while (iPipelineState != aState && retries-- > 0) {
        Thread::Sleep(10);
    }
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
void SuitePipeline::NotifyMode(const Brx& aMode, const ModeInfo& aInfo)
{
#ifdef LOG_PIPELINE_OBSERVER
    Log::Print("Pipeline report property: MODE {mode=");
    Log::Print(aMode);
    Log::Print("; supportsLatency=%u; supportsNext=%u; supportsPrev=%u}\n",
               aInfo.SupportsLatency(),aInfo.SupportsNext(), aInfo.SupportsPrev());
#endif
}

void SuitePipeline::NotifyTrack(Track& aTrack, const Brx& aMode, TBool /*aStartOfStream*/)
{
#ifdef LOG_PIPELINE_OBSERVER
    Print("Pipeline report property: TRACK {uri=%.*s; metadata=%.*s; mode=%.*s}\n",
          PBUF(aTrack.Uri()), PBUF(aTrack.MetaData()), PBUF(aMode));
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
    Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u; sampleRate=%u; numChannels=%u; codec=%.*s; trackLength=%llx; lossless=%u, channelConfig=%s}\n",
          aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels(),
          PBUF(aStreamInfo.CodecName()), aStreamInfo.TrackLength(), aStreamInfo.Lossless(), ChannelInfo::FromSpeakerProfile(aStreamInfo.Profile()));
#endif
}

Msg* SuitePipeline::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgDrain* aMsg)
{
    aMsg->ReportDrained();
    aMsg->RemoveRef();
    iLastMsgWasDrain = true;
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgHalt* aMsg)
{
    iLastMsgWasAudio = false;
    aMsg->ReportHalted();
    aMsg->RemoveRef();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgDecodedStream* aMsg)
{
    iLastMsgWasAudio = false;
    iSampleRate = aMsg->StreamInfo().SampleRate();
    iNumChannels = aMsg->StreamInfo().NumChannels();
    iBitDepth = aMsg->StreamInfo().BitDepth();
    aMsg->RemoveRef();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgPlayable* aMsg)
{
    PcmProcessorTestPipeline pcmProcessor;
    aMsg->Read(pcmProcessor);
    iFirstSubsample = pcmProcessor.FirstSubsample();
    iLastSubsample = pcmProcessor.LastSubsample();
    aMsg->RemoveRef();
    iLastMsgWasAudio = (iFirstSubsample != 0 || iLastSubsample != 0);
    if (iLastMsgWasAudio) {
        iLastMsgJiffies = Jiffies::PerSample(iSampleRate) * pcmProcessor.SampleCount();
        iJiffies += iLastMsgJiffies;
    }
    return nullptr;
}

Msg* SuitePipeline::ProcessMsg(MsgQuit* aMsg)
{
    iQuitReceived = true;
    aMsg->RemoveRef();
    return nullptr;
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

TBool SuitePipeline::TryGet(IWriter& /*aWriter*/, const Brx& /*aUrl*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}

TUint SuitePipeline::PipelineAnimatorBufferJiffies()
{
    return 0;
}

TUint SuitePipeline::PipelineAnimatorDelayJiffies(TUint /*aSampleRate*/, TUint /*aBitDepth*/, TUint /*aNumChannels*/)
{
    return 0;
}

void SuitePipeline::ApplyVolumeMultiplier(TUint /*aValue*/)
{
}


// DummyCodec

DummyCodec::DummyCodec(TUint aChannels, TUint aSampleRate, TUint aBitDepth, AudioDataEndian aEndian, SpeakerProfile aProfile)
    : CodecBase("Dummy")
    , iChannels(aChannels)
    , iSampleRate(aSampleRate)
    , iBitDepth(aBitDepth)
    , iEndian(aEndian)
    , iProfile(aProfile)
{
}

void DummyCodec::StreamInitialise()
{
    iTrackOffsetJiffies = 0;
    iSentDecodedInfo = false;
}

TBool DummyCodec::Recognise(const EncodedStreamInfo& /*aStreamInfo*/)
{
    return true;
}

void DummyCodec::Process()
{
    if (!iSentDecodedInfo) {
        const TUint bitRate = iSampleRate * iBitDepth * iChannels;
        iController->OutputDecodedStream(bitRate, iBitDepth, iSampleRate, iChannels, Brn("dummy codec"), 1LL<<34, 0, true, iProfile);
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


// PcmProcessorTestPipeline

TUint PcmProcessorTestPipeline::FirstSubsample() const
{
    return iFirstSubsample;
}

TUint PcmProcessorTestPipeline::LastSubsample() const
{
    return iLastSubsample;
}

TUint PcmProcessorTestPipeline::SampleCount() const
{
    return iSamples;
}

void PcmProcessorTestPipeline::BeginBlock()
{
    iFirstSubsample = iLastSubsample = 0xffffffff;
    iSetFirstSubsample = true;
    iSamples = 0;
}

inline TUint PcmProcessorTestPipeline::Subsample8(const TByte* aData) const
{
    return *aData;
}

inline TUint PcmProcessorTestPipeline::Subsample16(const TByte* aData) const
{
    TUint subsample = *aData++ << 8;
    subsample += *aData;
    return subsample;
}

inline TUint PcmProcessorTestPipeline::Subsample24(const TByte* aData) const
{
    TUint subsample = *aData++ << 16;
    subsample += *aData++ << 8;
    subsample += *aData;
    return subsample;
}

inline TUint PcmProcessorTestPipeline::Subsample32(const TByte* aData) const
{
    TUint subsample = *aData++ << 24;
    subsample += *aData++ << 16;
    subsample += *aData++ << 8;
    subsample += *aData;
    return subsample;
}

void PcmProcessorTestPipeline::ProcessFragment8(const Brx& aData, TUint aNumChannels)
{
    const TByte* start = aData.Ptr();
    const TByte* end = start + aData.Bytes() - 1;
    if (iSetFirstSubsample) {
        iFirstSubsample = Subsample8(start);
        iSetFirstSubsample = false;
    }
    iLastSubsample = Subsample8(end);
    iSamples += aData.Bytes() / aNumChannels;
}

void PcmProcessorTestPipeline::ProcessFragment16(const Brx& aData, TUint aNumChannels)
{
    const TByte* start = aData.Ptr();
    const TByte* end = start + aData.Bytes() - 2;
    if (iSetFirstSubsample) {
        iFirstSubsample = Subsample16(start);
        iSetFirstSubsample = false;
    }
    iLastSubsample = Subsample16(end);
    iSamples += aData.Bytes() / (aNumChannels * 2);
}

void PcmProcessorTestPipeline::ProcessFragment24(const Brx& aData, TUint aNumChannels)
{
    const TByte* start = aData.Ptr();
    const TByte* end = start + aData.Bytes() - 3;
    if (iSetFirstSubsample) {
        iFirstSubsample = Subsample24(start);
        iSetFirstSubsample = false;
    }
    iLastSubsample = Subsample24(end);
    iSamples += aData.Bytes() / (aNumChannels * 3);
}

void PcmProcessorTestPipeline::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    const TByte* start = aData.Ptr();
    const TByte* end = start + aData.Bytes() - 4;
    if (iSetFirstSubsample) {
        iFirstSubsample = Subsample32(start);
        iSetFirstSubsample = false;
    }
    iLastSubsample = Subsample32(end);
    iSamples += aData.Bytes() / (aNumChannels * 4);
}

void PcmProcessorTestPipeline::EndBlock()
{
}

void PcmProcessorTestPipeline::Flush()
{
}



void TestPipeline()
{
    //Debug::SetLevel(Debug::kPipeline | Debug::kMedia);
    Runner runner("Pipeline integration tests\n");
    runner.Add(new SuitePipeline());
    runner.Run();
}

