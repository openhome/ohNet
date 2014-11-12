#include <OpenHome/Media/Pipeline/Pipeline.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Supply.h>
#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/Seeker.h>
#include <OpenHome/Media/Pipeline/VariableDelay.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>
#include <OpenHome/Media/Pipeline/Skipper.h>
#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Media/Pipeline/Ramper.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/Splitter.h>
#include <OpenHome/Media/Pipeline/Pruner.h>
#include <OpenHome/Media/Pipeline/Logger.h>
#include <OpenHome/Media/Pipeline/StarvationMonitor.h>
#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Pipeline

Pipeline::Pipeline(IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, IStreamPlayObserver& aStreamPlayObserver, ISeekRestreamer& aSeekRestreamer)
    : iObserver(aObserver)
    , iLock("PLMG")
    , iState(EStopped)
    , iBuffering(false)
    , iWaiting(false)
    , iQuitting(false)
    , iNextFlushId(MsgFlush::kIdInvalid + 1)
{
    iMsgFactory = new MsgFactory(aInfoAggregator,
                                 kMsgCountEncodedAudio, kMsgCountAudioEncoded,
                                 kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountDecodedStream,
                                 kMsgCountTrack, kMsgCountEncodedStream, kMsgCountMetaText,
                                 kMsgCountHalt, kMsgCountFlush, kMsgCountWait,
                                 kMsgCountMode, kMsgCountSession, kMsgCountDelay, kMsgCountQuit);

    
    // construct encoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iEncodedAudioReservoir = new EncodedAudioReservoir(kEncodedReservoirSizeBytes, kMaxReservoirStreams, kMaxReservoirStreams);
    iLoggerEncodedAudioReservoir = new Logger(*iEncodedAudioReservoir, "Encoded Audio Reservoir");
    // construct push logger slightly out of sequence
    iLoggerSupply = new Logger("Supply", *iEncodedAudioReservoir);
    iSupply = new Supply(*iMsgFactory, *iLoggerSupply);

    // construct decoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iDecodedAudioReservoir = new DecodedAudioReservoir(kDecodedReservoirSize, kMaxReservoirStreams, kMaxReservoirStreams);
    iLoggerDecodedAudioReservoir = new Logger(*iDecodedAudioReservoir, "Decoded Audio Reservoir");

    iLoggerDecodedAudioAggregator = new Logger("Decoded Audio Aggregator", *iDecodedAudioReservoir);
    iDecodedAudioAggregator = new DecodedAudioAggregator(*iLoggerDecodedAudioAggregator, *iMsgFactory);

    iContainer = new Codec::Container(*iMsgFactory, *iLoggerEncodedAudioReservoir);
    iContainer->AddContainer(new Codec::Id3v2());
    iContainer->AddContainer(new Codec::Mpeg4Start());
    iLoggerContainer = new Logger(*iContainer, "Codec Container");

    // construct push logger slightly out of sequence
    iLoggerCodecController = new Logger("Codec Controller", *iDecodedAudioAggregator);
    iCodecController = new Codec::CodecController(*iMsgFactory, *iLoggerContainer, *iLoggerCodecController);

    iSeeker = new Seeker(*iMsgFactory, *iLoggerDecodedAudioReservoir, *iCodecController, aSeekRestreamer, kSeekerRampDuration);
    iLoggerSeeker = new Logger(*iSeeker, "Seeker");
    iVariableDelay1 = new VariableDelay(*iMsgFactory, *iLoggerSeeker, kSenderMinLatency, kVariableDelayRampDuration);
    iLoggerVariableDelay1 = new Logger(*iVariableDelay1, "VariableDelay1");
    iTrackInspector = new TrackInspector(*iLoggerVariableDelay1);
    iLoggerTrackInspector = new Logger(*iTrackInspector, "TrackInspector");
    iSkipper = new Skipper(*iMsgFactory, *iLoggerTrackInspector, kSkipperRampDuration);
    iLoggerSkipper = new Logger(*iSkipper, "Skipper");
    iWaiter = new Waiter(*iMsgFactory, *iLoggerSkipper, *this, kWaiterRampDuration);
    iLoggerWaiter = new Logger(*iWaiter, "Waiter");
    iStopper = new Stopper(*iMsgFactory, *iLoggerWaiter, *this, kStopperRampDuration);
    iStopper->SetStreamPlayObserver(aStreamPlayObserver);
    iLoggerStopper = new Logger(*iStopper, "Stopper");
    iRamper = new Ramper(*iLoggerStopper, kRamperRampDuration);
    iLoggerRamper = new Logger(*iRamper, "Ramper");
    iGorger = new Gorger(*iMsgFactory, *iLoggerRamper, kGorgerDuration);
    iLoggerGorger = new Logger(*iGorger, "Gorger");
    iReporter = new Reporter(*iLoggerGorger, *this);
    iLoggerReporter = new Logger(*iReporter, "Reporter");
    iSplitter = new Splitter(*iLoggerReporter);
    iLoggerSplitter = new Logger(*iSplitter, "Splitter");
    iVariableDelay2 = new VariableDelay(*iMsgFactory, *iLoggerSplitter, kStarvationMonitorNormalSize, kVariableDelayRampDuration);
    iLoggerVariableDelay2 = new Logger(*iVariableDelay2, "VariableDelay2");
    iPruner = new Pruner(*iLoggerVariableDelay2);
    iLoggerPruner = new Logger(*iPruner, "Pruner");
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, *iLoggerPruner, *this,
                                               kStarvationMonitorNormalSize, kStarvationMonitorStarvationThreshold,
                                               kStarvationMonitorRampUpDuration, kMaxReservoirStreams);
    iLoggerStarvationMonitor = new Logger(*iStarvationMonitor, "Starvation Monitor");
    iPreDriver = new PreDriver(*iLoggerStarvationMonitor);
    iLoggerPreDriver = new Logger(*iPreDriver, "PreDriver");

    iPipelineEnd = iLoggerPreDriver;
    if (iPipelineEnd == NULL) {
        iPipelineEnd = iPreDriver;
    }

    //iLoggerSupply->SetEnabled(true);
    //iLoggerEncodedAudioReservoir->SetEnabled(true);
    //iLoggerContainer->SetEnabled(true);
    //iLoggerCodecController->SetEnabled(true);
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
    //iLoggerReporter->SetEnabled(true);
    //iLoggerSplitter->SetEnabled(true);
    //iLoggerVariableDelay2->SetEnabled(true);
    //iLoggerPruner->SetEnabled(true);
    //iLoggerStarvationMonitor->SetEnabled(true);
    //iLoggerPreDriver->SetEnabled(true);

    //iLoggerSupply->SetFilter(Logger::EMsgAll);
    //iLoggerEncodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerContainer->SetFilter(Logger::EMsgAll);
    //iLoggerCodecController->SetFilter(Logger::EMsgAll);
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
    //iLoggerReporter->SetFilter(Logger::EMsgAll);
    //iLoggerSplitter->SetFilter(Logger::EMsgAll);
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
    delete iLoggerStarvationMonitor;
    delete iStarvationMonitor;
    delete iLoggerVariableDelay2;
    delete iVariableDelay2;
    delete iLoggerPruner;
    delete iPruner;
    delete iLoggerSplitter;
    delete iSplitter;
    delete iLoggerReporter;
    delete iReporter;
    delete iLoggerGorger;
    delete iGorger;
    delete iLoggerRamper;
    delete iRamper;
    delete iLoggerStopper;
    delete iStopper;
    delete iLoggerWaiter;
    delete iWaiter;
    delete iLoggerSkipper;
    delete iSkipper;
    delete iLoggerTrackInspector;
    delete iTrackInspector;
    delete iLoggerVariableDelay1;
    delete iVariableDelay1;
    delete iLoggerSeeker;
    delete iSeeker;
    delete iLoggerDecodedAudioReservoir;
    delete iDecodedAudioReservoir;
    delete iLoggerDecodedAudioAggregator;
    delete iDecodedAudioAggregator;
    delete iLoggerCodecController;
    delete iCodecController;
    delete iLoggerContainer;
    delete iContainer;
    delete iLoggerEncodedAudioReservoir;
    delete iEncodedAudioReservoir;
    delete iLoggerSupply;
    delete iSupply;
    delete iMsgFactory;
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
    iLock.Wait();
    if (iState == EPlaying) {
        iLock.Signal();
        return; // already playing so ignore this additional request
    }
    if (aQuit) {
        iStopper->Quit();
    }
    else {
        iStopper->Play();
    }
    iState = EPlaying;
    iLock.Signal();
    NotifyStatus();
}

void Pipeline::Pause()
{
    AutoMutex a(iLock);
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

TBool Pipeline::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    const TBool rampDown = (iState == EPlaying);
    return iSeeker->Seek(aTrackId, aStreamId, aSecondsAbsolute, rampDown);
}

void Pipeline::AddObserver(ITrackObserver& aObserver)
{
    iTrackInspector->AddObserver(aObserver);
}

TBool Pipeline::SupportsMimeType(const Brx& aMimeType)
{
    return iCodecController->SupportsMimeType(aMimeType);
}

IPipelineElementDownstream* Pipeline::SetSender(IPipelineElementDownstream& aSender)
{
    return iSplitter->SetPipelineBranch(aSender);
}

TUint Pipeline::SenderMinLatencyMs() const
{
    return kSenderMinLatency / Jiffies::kPerMs;
}

void Pipeline::OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller)
{
    iSupply->OutputMode(aMode, aSupportsLatency, aRealTime, aClockPuller);
}

void Pipeline::OutputSession()
{
    iSupply->OutputSession();
}

void Pipeline::OutputTrack(Track& aTrack, TUint aTrackId)
{
    iSupply->OutputTrack(aTrack, aTrackId);
}

void Pipeline::OutputDelay(TUint aJiffies)
{
    iSupply->OutputDelay(aJiffies);
}

void Pipeline::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    iSupply->OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
}

void Pipeline::OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream)
{
    iSupply->OutputPcmStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId, aPcmStream);
}

void Pipeline::OutputData(const Brx& aData)
{
    iSupply->OutputData(aData);
}

void Pipeline::OutputMetadata(const Brx& aMetadata)
{
    iSupply->OutputMetadata(aMetadata);
}

void Pipeline::OutputFlush(TUint aFlushId)
{
    iSupply->OutputFlush(aFlushId);
}

void Pipeline::OutputWait()
{
    iSupply->OutputWait();
}

void Pipeline::OutputHalt(TUint aHaltId)
{
    iSupply->OutputHalt(aHaltId);
}

void Pipeline::OutputQuit()
{
    iSupply->OutputQuit();
}

Msg* Pipeline::Pull()
{
    return iPipelineEnd->Pull();
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

void Pipeline::RemoveStream(TUint aTrackId, TUint aStreamId)
{
    (void)iSkipper->TryRemoveStream(aTrackId, aStreamId, !iBuffering);
}

void Pipeline::NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline)
{
    iObserver.NotifyTrack(aTrack, aMode, aIdPipeline);
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
