#include <OpenHome/Media/Pipeline.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/Media/Seeker.h>
#include <OpenHome/Media/VariableDelay.h>
#include <OpenHome/Media/TrackInspector.h>
#include <OpenHome/Media/Skipper.h>
#include <OpenHome/Media/Stopper.h>
#include <OpenHome/Media/Reporter.h>
#include <OpenHome/Media/Splitter.h>
#include <OpenHome/Media/Logger.h>
#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Pipeline

Pipeline::Pipeline(Av::IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes)
    : iObserver(aObserver)
    , iLock("PLMG")
    , iState(EStopped)
    , iBuffering(false)
    , iQuitting(false)
    , iNextFlushId(MsgFlush::kIdInvalid + 1)
{
    iMsgFactory = new MsgFactory(aInfoAggregator,
                                 kMsgCountEncodedAudio, kMsgCountAudioEncoded,
                                 kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountEncodedStream,
                                 kMsgCountTrack, kMsgCountDecodedStream, kMsgCountMetaText,
                                 kMsgCountHalt, kMsgCountFlush, kMsgCountWait, kMsgCountQuit);

    
    // construct encoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iEncodedAudioReservoir = new EncodedAudioReservoir(kEncodedReservoirSizeBytes);
    iLoggerEncodedAudioReservoir = new Logger(*iEncodedAudioReservoir, "Encoded Audio Reservoir");
    // construct push logger slightly out of sequence
    iLoggerSupply = new Logger("Supply", *iEncodedAudioReservoir);
    iSupply = new Supply(*iMsgFactory, *iLoggerSupply);

    // construct decoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iDecodedAudioReservoir = new DecodedAudioReservoir(kDecodedReservoirSize, iClockPuller.DecodedReservoirHistory());
    iLoggerDecodedAudioReservoir = new Logger(*iDecodedAudioReservoir, "Decoded Audio Reservoir");

    iContainer = new Codec::Container(*iMsgFactory, *iLoggerEncodedAudioReservoir);
    iContainer->AddContainer(new Codec::Id3v2());
    iContainer->AddContainer(new Codec::Mpeg4Start());
    iLoggerContainer = new Logger(*iContainer, "Codec Container");

    // construct push logger slightly out of sequence
    iLoggerCodecController = new Logger("Codec Controller", *iDecodedAudioReservoir);
    iCodecController = new Codec::CodecController(*iMsgFactory, *iLoggerContainer, *iLoggerCodecController);

    iSeeker = NULL;
    iLoggerSeeker = NULL;
    iSeeker = new Seeker(*iMsgFactory, *iLoggerDecodedAudioReservoir, *iCodecController, kSeekerRampDuration);
    iLoggerSeeker = new Logger(*iSeeker, "Seeker");
    iVariableDelay = new VariableDelay(*iMsgFactory, *iLoggerSeeker, kVariableDelayRampDuration);
    iLoggerVariableDelay = new Logger(*iVariableDelay, "Variable Delay");
    iTrackInspector = new TrackInspector(*iLoggerVariableDelay);
    iLoggerTrackInspector = new Logger(*iTrackInspector, "TrackInspector");
    iSkipper = new Skipper(*iMsgFactory, *iLoggerTrackInspector, kSkipperRampDuration);
    iLoggerSkipper = new Logger(*iSkipper, "Skipper");
    iWaiter = new Waiter(*iMsgFactory, *iLoggerSkipper, *this, kWaiterRampDuration);
    iLoggerWaiter = new Logger(*iWaiter, "Waiter");
    iStopper = new Stopper(*iMsgFactory, *iLoggerWaiter, *this, kStopperRampDuration);
    iLoggerStopper = new Logger(*iStopper, "Stopper");
    iReporter = new Reporter(*iLoggerStopper, *this);
    iLoggerReporter = new Logger(*iReporter, "Reporter");
    iSplitter = new Splitter(*iLoggerReporter);
    iLoggerSplitter = new Logger(*iSplitter, "Splitter");
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, *iLoggerSplitter, *this,
                                               kStarvationMonitorNormalSize, kStarvationMonitorStarvationThreshold,
                                               kStarvationMonitorGorgeSize, kStarvationMonitorRampUpDuration,
                                               iClockPuller.StarvationMonitorHistory());
    iLoggerStarvationMonitor = new Logger(*iStarvationMonitor, "Starvation Monitor");
    iPreDriver = new PreDriver(*iMsgFactory, *iLoggerStarvationMonitor, aDriverMaxAudioBytes);
    iLoggerPreDriver = new Logger(*iPreDriver, "PreDriver");

    iPipelineEnd = iLoggerPreDriver;
    if (iPipelineEnd == NULL) {
        iPipelineEnd = iPreDriver;
    }

    //iLoggerSupply->SetEnabled(true);
    //iLoggerEncodedAudioReservoir->SetEnabled(true);
    //iLoggerContainer->SetEnabled(true);
    //iLoggerCodecController->SetEnabled(true);
    //iLoggerDecodedAudioReservoir->SetEnabled(true);
    //iLoggerSeeker->SetEnabled(true);
    //iLoggerVariableDelay->SetEnabled(true);
    //iLoggerTrackInspector->SetEnabled(true);
    //iLoggerSkipper->SetEnabled(true);
    //iLoggerStopper->SetEnabled(true);
    //iLoggerReporter->SetEnabled(true);
    //iLoggerSplitter->SetEnabled(true);
    //iLoggerStarvationMonitor->SetEnabled(true);
    //iLoggerPreDriver->SetEnabled(true);

    //iLoggerSupply->SetFilter(Logger::EMsgAll);
    //iLoggerEncodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerContainer->SetFilter(Logger::EMsgAll);
    //iLoggerCodecController->SetFilter(Logger::EMsgAll);
    //iLoggerDecodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerSeeker->SetFilter(Logger::EMsgAll);
    //iLoggerVariableDelay->SetFilter(Logger::EMsgAll);
    //iLoggerTrackInspector->SetFilter(Logger::EMsgAll);
    //iLoggerSkipper->SetFilter(Logger::EMsgAll);
    //iLoggerStopper->SetFilter(Logger::EMsgAll);
    //iLoggerReporter->SetFilter(Logger::EMsgAll);
    //iLoggerSplitter->SetFilter(Logger::EMsgAll);
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
    delete iLoggerSplitter;
    delete iSplitter;
    delete iLoggerReporter;
    delete iReporter;
    delete iLoggerStopper;
    delete iStopper;
    delete iLoggerSkipper;
    delete iSkipper;
    delete iLoggerTrackInspector;
    delete iTrackInspector;
    delete iLoggerVariableDelay;
    delete iVariableDelay;
    delete iLoggerSeeker;
    delete iSeeker;
    delete iLoggerDecodedAudioReservoir;
    delete iDecodedAudioReservoir;
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
    OutputQuit();
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
        state = (iBuffering? EPipelineBuffering : EPipelinePlaying);
        break;
    case EPaused:
        state = EPipelinePaused;
        break;
    case EStopped:
        state = EPipelineStopped;
        break;
    case EWaiting:
        state = EPipelineWaiting;
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
        iState = EStopped;
        iSkipper->RemoveCurrentStream(false);
        iLock.Signal();
        NotifyStatus();
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

void Pipeline::OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode)
{
    iSupply->OutputTrack(aTrack, aTrackId, aMode);
}

void Pipeline::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    iSupply->OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
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
    if (aWaiting) {
        iState = EWaiting;
    }
    else {
        iState = EPlaying;
    }
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
    }
}
