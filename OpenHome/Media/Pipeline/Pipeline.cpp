#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Codec/MpegTs.h>
#include <OpenHome/Media/Pipeline/SampleRateValidator.h>
#include <OpenHome/Media/Pipeline/TimestampInspector.h>
#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/Ramper.h>
#include <OpenHome/Media/Pipeline/RampValidator.h>
#include <OpenHome/Media/Pipeline/Seeker.h>
#include <OpenHome/Media/Pipeline/VariableDelay.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>
#include <OpenHome/Media/Pipeline/Skipper.h>
#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/Pruner.h>
#include <OpenHome/Media/Pipeline/Logger.h>
#include <OpenHome/Media/Pipeline/StarvationMonitor.h>
#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PipelineInitParams

PipelineInitParams* PipelineInitParams::New()
{ // static
    return new PipelineInitParams();
}

PipelineInitParams::PipelineInitParams()
    : iEncodedReservoirBytes(kEncodedReservoirSizeBytes)
    , iDecodedReservoirJiffies(kDecodedReservoirSize)
    , iGorgeDurationJiffies(kGorgerSizeDefault)
    , iStarvationMonitorMaxJiffies(kStarvationMonitorMaxSizeDefault)
    , iStarvationMonitorMinJiffies(kStarvationMonitorMinSizeDefault)
    , iMaxStreamsPerReservoir(kMaxReservoirStreamsDefault)
    , iRampLongJiffies(kLongRampDurationDefault)
    , iRampShortJiffies(kShortRampDurationDefault)
    , iRampEmergencyJiffies(kEmergencyRampDurationDefault)
    , iThreadPriorityMax(kThreadPriorityMax)
    , iMaxLatencyJiffies(kMaxLatencyDefault)
{
}

PipelineInitParams::~PipelineInitParams()
{
}

void PipelineInitParams::SetEncodedReservoirSize(TUint aBytes)
{
    iEncodedReservoirBytes = aBytes;
}

void PipelineInitParams::SetDecodedReservoirSize(TUint aJiffies)
{
    iDecodedReservoirJiffies = aJiffies;
}

void PipelineInitParams::SetGorgerDuration(TUint aJiffies)
{
    iGorgeDurationJiffies = aJiffies;
}

void PipelineInitParams::SetStarvationMonitorMaxSize(TUint aJiffies)
{
    iStarvationMonitorMaxJiffies = aJiffies;
}

void PipelineInitParams::SetStarvationMonitorMinSize(TUint aJiffies)
{
    iStarvationMonitorMinJiffies = aJiffies;
}

void PipelineInitParams::SetMaxStreamsPerReservoir(TUint aCount)
{
    iMaxStreamsPerReservoir = aCount;
}

void PipelineInitParams::SetLongRamp(TUint aJiffies)
{
    iRampLongJiffies = aJiffies;
}

void PipelineInitParams::SetShortRamp(TUint aJiffies)
{
    iRampShortJiffies = aJiffies;
}

void PipelineInitParams::SetEmergencyRamp(TUint aJiffies)
{
    iRampEmergencyJiffies = aJiffies;
}

void PipelineInitParams::SetThreadPriorityMax(TUint aPriority)
{
    iThreadPriorityMax = aPriority;
}

void PipelineInitParams::SetMaxLatency(TUint aJiffies)
{
    iMaxLatencyJiffies = aJiffies;
}

TUint PipelineInitParams::EncodedReservoirBytes() const
{
    return iEncodedReservoirBytes;
}

TUint PipelineInitParams::DecodedReservoirJiffies() const
{
    return iDecodedReservoirJiffies;
}

TUint PipelineInitParams::GorgeDurationJiffies() const
{
   return iGorgeDurationJiffies;
}

TUint PipelineInitParams::StarvationMonitorMaxJiffies() const
{
    return iStarvationMonitorMaxJiffies;
}

TUint PipelineInitParams::StarvationMonitorMinJiffies() const
{
    return iStarvationMonitorMinJiffies;
}

TUint PipelineInitParams::MaxStreamsPerReservoir() const
{
    return iMaxStreamsPerReservoir;
}

TUint PipelineInitParams::RampLongJiffies() const
{
    return iRampLongJiffies;
}

TUint PipelineInitParams::RampShortJiffies() const
{
    return iRampShortJiffies;
}

TUint PipelineInitParams::RampEmergencyJiffies() const
{
    return iRampEmergencyJiffies;
}

TUint PipelineInitParams::ThreadPriorityMax() const
{
    return iThreadPriorityMax;
}

TUint PipelineInitParams::MaxLatencyJiffies() const
{
    return iMaxLatencyJiffies;
}


// Pipeline

Pipeline::Pipeline(PipelineInitParams* aInitParams, IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver,
                   IStreamPlayObserver& aStreamPlayObserver, ISeekRestreamer& aSeekRestreamer, IUrlBlockWriter& aUrlBlockWriter)
    : iInitParams(aInitParams)
    , iObserver(aObserver)
    , iLock("PLMG")
    , iState(EStopped)
    , iBuffering(false)
    , iWaiting(false)
    , iQuitting(false)
    , iNextFlushId(MsgFlush::kIdInvalid + 1)
{
    const TUint perStreamMsgCount = aInitParams->MaxStreamsPerReservoir() * kReservoirCount;
    TUint encodedAudioCount = ((aInitParams->EncodedReservoirBytes() + EncodedAudio::kMaxBytes - 1) / EncodedAudio::kMaxBytes); // this may only be required on platforms that don't guarantee priority based thread scheduling
    encodedAudioCount = std::max(encodedAudioCount, // songcast and some hardware inputs won't use the full capacity of each encodedAudio
                                 (aInitParams->MaxLatencyJiffies() + kSongcastFrameJiffies - 1) / kSongcastFrameJiffies);
    const TUint maxEncodedReservoirMsgs = encodedAudioCount;
    encodedAudioCount += kRewinderMaxMsgs; // this may only be required on platforms that don't guarantee priority based thread scheduling
    const TUint msgEncodedAudioCount = encodedAudioCount + 100; // +100 allows for Split()ing by Container and CodecController
    const TUint decodedReservoirSize = aInitParams->DecodedReservoirJiffies() + aInitParams->GorgeDurationJiffies() + aInitParams->StarvationMonitorMaxJiffies();
    const TUint decodedAudioCount = (decodedReservoirSize / DecodedAudioAggregator::kMaxJiffies) + 100; // +100 allows for some smaller msgs and some buffering in non-reservoir elements
    const TUint msgAudioPcmCount = decodedAudioCount + 100; // +100 allows for Split()ing in various elements
    const TUint msgHaltCount = perStreamMsgCount * 2; // worst case is tiny Vorbis track with embedded metatext in a single-track playlist with repeat
    iMsgFactory = new MsgFactory(aInfoAggregator,
                                 encodedAudioCount, msgEncodedAudioCount,
                                 decodedAudioCount, msgAudioPcmCount, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, perStreamMsgCount,
                                 perStreamMsgCount, perStreamMsgCount, perStreamMsgCount,
                                 msgHaltCount, kMsgCountFlush, kMsgCountWait,
                                 kMsgCountMode, perStreamMsgCount, perStreamMsgCount, kMsgCountQuit);
    const TUint threadPriorityBase = aInitParams->ThreadPriorityMax() - kThreadCount + 1;
    TUint threadPriority = threadPriorityBase;
    
    // construct encoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iEncodedAudioReservoir = new EncodedAudioReservoir(maxEncodedReservoirMsgs, aInitParams->MaxStreamsPerReservoir(), aInitParams->MaxStreamsPerReservoir());
    iLoggerEncodedAudioReservoir = new Logger(*iEncodedAudioReservoir, "Encoded Audio Reservoir");

    // construct decoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iDecodedAudioReservoir = new DecodedAudioReservoir(aInitParams->DecodedReservoirJiffies(), aInitParams->MaxStreamsPerReservoir(), aInitParams->MaxStreamsPerReservoir());
    iLoggerDecodedAudioReservoir = new Logger(*iDecodedAudioReservoir, "Decoded Audio Reservoir");

    iLoggerDecodedAudioAggregator = new Logger("Decoded Audio Aggregator", *iDecodedAudioReservoir);
    iDecodedAudioAggregator = new DecodedAudioAggregator(*iLoggerDecodedAudioAggregator, *iMsgFactory);

    iLoggerTimestampInspector = new Logger("Timestamp Inspector", *iDecodedAudioAggregator);
    iTimestampInspector = new TimestampInspector(*iMsgFactory, *iLoggerTimestampInspector);

    iLoggerSampleRateValidator = new Logger("Sample Rate Validator", *iTimestampInspector);
    iSampleRateValidator = new SampleRateValidator(*iLoggerSampleRateValidator);

    iContainer = new Codec::Container(*iMsgFactory, *iLoggerEncodedAudioReservoir);
    iContainer->AddContainer(new Codec::Id3v2());
    iContainer->AddContainer(new Codec::Mpeg4Start());
    iContainer->AddContainer(new Codec::MpegTs());
    iLoggerContainer = new Logger(*iContainer, "Codec Container");

    // construct push logger slightly out of sequence
    iLoggerCodecController = new Logger("Codec Controller", *iSampleRateValidator);
    iCodecController = new Codec::CodecController(*iMsgFactory, *iLoggerContainer, *iLoggerCodecController, aUrlBlockWriter, threadPriority);
    threadPriority++;

    iRamper = new Ramper(*iLoggerDecodedAudioReservoir, aInitParams->RampLongJiffies());
    iLoggerRamper = new Logger(*iRamper, "Ramper");
    iRampValidatorRamper = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerRamper));
    iSeeker = new Seeker(*iMsgFactory, *iRampValidatorRamper, *iCodecController, aSeekRestreamer, aInitParams->RampShortJiffies());
    iLoggerSeeker = new Logger(*iSeeker, "Seeker");
    iRampValidatorSeeker = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerSeeker));
    iVariableDelay1 = new VariableDelay(*iMsgFactory, *iRampValidatorSeeker, kSenderMinLatency, aInitParams->RampEmergencyJiffies());
    iLoggerVariableDelay1 = new Logger(*iVariableDelay1, "VariableDelay1");
    iRampValidatorDelay1 = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerVariableDelay1));
    iTrackInspector = new TrackInspector(*iRampValidatorDelay1);
    iLoggerTrackInspector = new Logger(*iTrackInspector, "TrackInspector");
    iSkipper = new Skipper(*iMsgFactory, *iLoggerTrackInspector, aInitParams->RampLongJiffies());
    iLoggerSkipper = new Logger(*iSkipper, "Skipper");
    iRampValidatorSkipper = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerSkipper));
    iWaiter = new Waiter(*iMsgFactory, *iRampValidatorSkipper, *this, aInitParams->RampShortJiffies());
    iLoggerWaiter = new Logger(*iWaiter, "Waiter");
    iRampValidatorWaiter = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerWaiter));
    iStopper = new Stopper(*iMsgFactory, *iRampValidatorWaiter, *this, aInitParams->RampLongJiffies());
    iStopper->SetStreamPlayObserver(aStreamPlayObserver);
    iLoggerStopper = new Logger(*iStopper, "Stopper");
    iRampValidatorStopper = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerStopper));
    iGorger = new Gorger(*iMsgFactory, *iRampValidatorStopper, threadPriority, aInitParams->GorgeDurationJiffies());
    threadPriority++;
    iLoggerGorger = new Logger(*iGorger, "Gorger");
    iSpotifyReporter = new Media::SpotifyReporter(*iLoggerGorger, *this);
    iLoggerSpotifyReporter = new Logger(*iSpotifyReporter, "SpotifyReporter");
    iReporter = new Reporter(*iLoggerSpotifyReporter, *iSpotifyReporter, threadPriorityBase-1);
    iLoggerReporter = new Logger(*iReporter, "Reporter");
    iRouter = new Router(*iLoggerReporter);
    iLoggerRouter = new Logger(*iRouter, "Router");
    iVariableDelay2 = new VariableDelay(*iMsgFactory, *iLoggerRouter, aInitParams->StarvationMonitorMaxJiffies(), aInitParams->RampEmergencyJiffies());
    iLoggerVariableDelay2 = new Logger(*iVariableDelay2, "VariableDelay2");
    iRampValidatorDelay2 = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerVariableDelay2));
    iPruner = new Pruner(*iRampValidatorDelay2);
    iLoggerPruner = new Logger(*iPruner, "Pruner");
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, *iLoggerPruner, *this, threadPriority,
                                               aInitParams->StarvationMonitorMaxJiffies(), aInitParams->StarvationMonitorMinJiffies(),
                                               aInitParams->RampShortJiffies(), aInitParams->MaxStreamsPerReservoir());
    iLoggerStarvationMonitor = new Logger(*iStarvationMonitor, "Starvation Monitor");
    iRampValidatorStarvationMonitor = new RampValidator(static_cast<IPipelineElementUpstream&>(*iLoggerStarvationMonitor));
    iPreDriver = new PreDriver(*iRampValidatorStarvationMonitor);
    iLoggerPreDriver = new Logger(*iPreDriver, "PreDriver");
    ASSERT(threadPriority == aInitParams->ThreadPriorityMax());

    iPipelineEnd = iLoggerPreDriver;
    if (iPipelineEnd == NULL) {
        iPipelineEnd = iPreDriver;
    }

    //iLoggerEncodedAudioReservoir->SetEnabled(true);
    //iLoggerContainer->SetEnabled(true);
    //iLoggerCodecController->SetEnabled(true);
    //iLoggerSampleRateValidator->SetEnabled(true);
    //iLoggerTimestampInspector->SetEnabled(true);
    //iLoggerDecodedAudioAggregator->SetEnabled(true);
    //iLoggerDecodedAudioReservoir->SetEnabled(true);
    //iLoggerSeeker->SetEnabled(true);
    //iLoggerVariableDelay1->SetEnabled(true);
    //iLoggerTrackInspector->SetEnabled(true);
    //iLoggerSkipper->SetEnabled(true);
    //iLoggerWaiter->SetEnabled(true);
    //iLoggerStopper->SetEnabled(true);
    //iLoggerRamper->SetEnabled(true);
    //iLoggerGorger->SetEnabled(true);
    //iLoggerSpotifyReporter->SetEnabled(true);
    //iLoggerReporter->SetEnabled(true);
    //iLoggerRouter->SetEnabled(true);
    //iLoggerVariableDelay2->SetEnabled(true);
    //iLoggerPruner->SetEnabled(true);
    //iLoggerStarvationMonitor->SetEnabled(true);
    //iLoggerPreDriver->SetEnabled(true);

    //iLoggerEncodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerContainer->SetFilter(Logger::EMsgAll);
    //iLoggerCodecController->SetFilter(Logger::EMsgAll);
    //iLoggerSampleRateValidator->SetFilter(Logger::EMsgAll);
    //iLoggerTimestampInspector->SetFilter(Logger::EMsgAll);
    //iLoggerDecodedAudioAggregator->SetFilter(Logger::EMsgAll);
    //iLoggerDecodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerSeeker->SetFilter(Logger::EMsgAll);
    //iLoggerVariableDelay1->SetFilter(Logger::EMsgAll);
    //iLoggerTrackInspector->SetFilter(Logger::EMsgAll);
    //iLoggerSkipper->SetFilter(Logger::EMsgAll);
    //iLoggerWaiter->SetFilter(Logger::EMsgAll);
    //iLoggerStopper->SetFilter(Logger::EMsgAll);
    //iLoggerRamper->SetFilter(Logger::EMsgAll);
    //iLoggerGorger->SetFilter(Logger::EMsgAll);
    //iLoggerSpotifyReporter->SetFilter(Logger::EMsgAll);
    //iLoggerReporter->SetFilter(Logger::EMsgAll);
    //iLoggerRouter->SetFilter(Logger::EMsgAll);
    //iLoggerVariableDelay2->SetFilter(Logger::EMsgAll);
    //iLoggerPruner->SetFilter(Logger::EMsgAll);
    //iLoggerStarvationMonitor->SetFilter(Logger::EMsgAll);
    //iLoggerPreDriver->SetFilter(Logger::EMsgAll);
}

Pipeline::~Pipeline()
{
    // FIXME - should we wait for the pipeline to be halted before issuing a Quit?
    //         ...otherwise, MsgQuit goes down the pipeline ahead of final audio
    Quit();

    // loggers (if non-null) and iPreDriver will block until they receive the Quit msg
    delete iLoggerPreDriver;
    delete iPreDriver;
    delete iRampValidatorStarvationMonitor;
    delete iLoggerStarvationMonitor;
    delete iStarvationMonitor;
    delete iRampValidatorDelay2;
    delete iLoggerVariableDelay2;
    delete iVariableDelay2;
    delete iLoggerPruner;
    delete iPruner;
    delete iLoggerRouter;
    delete iRouter;
    delete iLoggerReporter;
    delete iReporter;
    delete iLoggerSpotifyReporter;
    delete iSpotifyReporter;
    delete iLoggerGorger;
    delete iGorger;
    delete iRampValidatorStopper;
    delete iLoggerStopper;
    delete iStopper;
    delete iRampValidatorWaiter;
    delete iLoggerWaiter;
    delete iWaiter;
    delete iRampValidatorSkipper;
    delete iLoggerSkipper;
    delete iSkipper;
    delete iLoggerTrackInspector;
    delete iTrackInspector;
    delete iRampValidatorDelay1;
    delete iLoggerVariableDelay1;
    delete iVariableDelay1;
    delete iRampValidatorSeeker;
    delete iLoggerSeeker;
    delete iSeeker;
    delete iRampValidatorRamper;
    delete iLoggerRamper;
    delete iRamper;
    delete iLoggerDecodedAudioReservoir;
    delete iDecodedAudioReservoir;
    delete iLoggerDecodedAudioAggregator;
    delete iDecodedAudioAggregator;
    delete iLoggerTimestampInspector;
    delete iTimestampInspector;
    delete iLoggerSampleRateValidator;
    delete iSampleRateValidator;
    delete iLoggerCodecController;
    delete iCodecController;
    delete iLoggerContainer;
    delete iContainer;
    delete iLoggerEncodedAudioReservoir;
    delete iEncodedAudioReservoir;
    delete iMsgFactory;
    delete iInitParams;
}

void Pipeline::AddCodec(Codec::CodecBase* aCodec)
{
    iCodecController->AddCodec(aCodec);
}

void Pipeline::Start()
{
    iCodecController->Start();
}

void Pipeline::Quit()
{
    if (iQuitting) {
        return;
    }
    iQuitting = true;
    DoPlay(true);
}

void Pipeline::NotifyStatus()
{
    EPipelineState state;
    iLock.Wait();
    if (iQuitting) {
        iLock.Signal();
        return;
    }
    switch (iState)
    {
    case EPlaying:
        state = (iWaiting? EPipelineWaiting : (iBuffering? EPipelineBuffering : EPipelinePlaying));
        break;
    case EPaused:
        state = EPipelinePaused;
        break;
    case EStopped:
        state = EPipelineStopped;
        break;
    default:
        ASSERTS();
        state = EPipelineBuffering; // will never reach here but the compiler doesn't realise this
    }
    iLock.Signal();
    iObserver.NotifyPipelineState(state);
}

MsgFactory& Pipeline::Factory()
{
    return *iMsgFactory;
}

void Pipeline::Play()
{
    DoPlay(false);
}

void Pipeline::DoPlay(TBool aQuit)
{
    TBool notifyStatus = true;
    iLock.Wait();
    if (iState == EPlaying) {
        notifyStatus = false;
    }
    iState = EPlaying;
    iLock.Signal();

    if (aQuit) {
        iStopper->Quit();
    }
    else {
        iStopper->Play();
    }
    if (notifyStatus) {
        NotifyStatus();
    }
}

void Pipeline::Pause()
{
    iStopper->BeginPause();
}

void Pipeline::Wait(TUint aFlushId)
{
    const TBool rampDown = (iState == EPlaying);
    iWaiter->Wait(aFlushId, rampDown);
}

void Pipeline::Stop(TUint aHaltId)
{
    iLock.Wait();
    /* FIXME - is there any race where iBuffering is true but the pipeline is also
               running, meaning that we want to allow Stopper to ramp down? */
    if (iBuffering) {
        // FIXME - should maybe tell StarvationMonitor to skip to next track also
        iSkipper->RemoveCurrentStream(false);
        iLock.Signal();
        iStopper->StopNow();
        return;
    }
    iStopper->BeginStop(aHaltId);
    iLock.Signal();
}

void Pipeline::RemoveCurrentStream()
{
    const TBool rampDown = (iState == EPlaying);
    iSkipper->RemoveCurrentStream(rampDown);
}

TBool Pipeline::Seek(TUint aStreamId, TUint aSecondsAbsolute)
{
    const TBool rampDown = (iState == EPlaying);
    return iSeeker->Seek(aStreamId, aSecondsAbsolute, rampDown);
}

void Pipeline::AddObserver(ITrackObserver& aObserver)
{
    iTrackInspector->AddObserver(aObserver);
}

ISpotifyReporter& Pipeline::SpotifyReporter() const
{
    return *iSpotifyReporter;
}

ITrackChangeObserver& Pipeline::TrackChangeObserver() const
{
    return *iSpotifyReporter;
}

TBool Pipeline::SupportsMimeType(const Brx& aMimeType)
{
    return iCodecController->SupportsMimeType(aMimeType);
}

IPipelineElementUpstream& Pipeline::InsertElements(IPipelineElementUpstream& aTail)
{
    return iRouter->InsertElements(aTail);
}

TUint Pipeline::SenderMinLatencyMs() const
{
    return kSenderMinLatency / Jiffies::kPerMs;
}

void Pipeline::GetThreadPriorityRange(TUint& aMin, TUint& aMax) const
{
    aMax = iInitParams->ThreadPriorityMax();
    aMin = aMax - kThreadCount;
}

void Pipeline::Push(Msg* aMsg)
{
    iEncodedAudioReservoir->Push(aMsg);
}

Msg* Pipeline::Pull()
{
    return iPipelineEnd->Pull();
}

void Pipeline::SetAnimator(IPipelineAnimator& aAnimator)
{
    iSampleRateValidator->SetAnimator(aAnimator);
}

void Pipeline::PipelinePaused()
{
    iLock.Wait();
    iState = EPaused;
    iLock.Signal();
    NotifyStatus();
}

void Pipeline::PipelineStopped()
{
    iLock.Wait();
    iState = EStopped;
    iLock.Signal();
    NotifyStatus();
}

void Pipeline::PipelinePlaying()
{
    iLock.Wait();
    iState = EPlaying;
    iLock.Signal();
    NotifyStatus();
}

TUint Pipeline::NextFlushId()
{
    /* non-use of iLock is deliberate.  It isn't absolutely required since all callers
       run in the Filler thread.  If we re-instate the lock, the call to
       RemoveCurrentStream() in Stop() will need to move outside its lock. */
    TUint id = iNextFlushId++;
    return id;
}

void Pipeline::PipelineWaiting(TBool aWaiting)
{
    iLock.Wait();
    iWaiting = aWaiting;
    iLock.Signal();
    NotifyStatus();
}

void Pipeline::RemoveStream(TUint aStreamId)
{
    (void)iSkipper->TryRemoveStream(aStreamId, !iBuffering);
}

void Pipeline::NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream)
{
    iObserver.NotifyTrack(aTrack, aMode, aStartOfStream);
}

void Pipeline::NotifyMetaText(const Brx& aText)
{
    iObserver.NotifyMetaText(aText);
}

void Pipeline::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iObserver.NotifyTime(aSeconds, aTrackDurationSeconds);
}

void Pipeline::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iObserver.NotifyStreamInfo(aStreamInfo);
}

void Pipeline::NotifyStarvationMonitorBuffering(TBool aBuffering)
{
    iLock.Wait();
    iBuffering = aBuffering;
    const TBool notify = (iState == EPlaying);
    iLock.Signal();
    if (notify) {
        NotifyStatus();
#if 1
        if (aBuffering && !iWaiting) {
            const TUint encodedBytes = iEncodedAudioReservoir->SizeInBytes();
            const TUint decodedMs = iDecodedAudioReservoir->SizeInJiffies() / Jiffies::kPerMs;
            const TUint gorgedMs = iGorger->SizeInJiffies() / Jiffies::kPerMs;
            Log::Print("Pipeline utilisation: encodedBytes=%u, decodedMs=%u, gorgedMs=%u\n", encodedBytes, decodedMs, gorgedMs);
        }
#endif
    }
}
