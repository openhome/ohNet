#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/Media/VariableDelay.h>
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

// PipelineManager

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes)
    : iObserver(aObserver)
    , iLock("PLMG")
    , iLoggerSupply(NULL)
    , iLoggerEncodedAudioReservoir(NULL)
    , iLoggerContainer(NULL)
    , iLoggerCodecController(NULL)
    , iLoggerDecodedAudioReservoir(NULL)
    , iLoggerVariableDelay(NULL)
    , iLoggerStopper(NULL)
    , iLoggerReporter(NULL)
    , iLoggerSplitter(NULL)
    , iLoggerStarvationMonitor(NULL)
    , iLoggerPreDriver(NULL)
    , iStatus(EFlushed)
    , iTargetStatus(EFlushed)
    , iHaltCompletedIgnoreCount(0)
    , iFlushCompletedIgnoreCount(0)
    , iBuffering(false)
    , iQuitting(false)
{
    iMsgFactory = new MsgFactory(aInfoAggregator,
                                 kMsgCountEncodedAudio, kMsgCountAudioEncoded,
                                 kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountEncodedStream,
                                 kMsgCountTrack, kMsgCountDecodedStream, kMsgCountMetaText,
                                 kMsgCountHalt, kMsgCountFlush, kMsgCountQuit);

    
    // construct encoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iEncodedAudioReservoir = new EncodedAudioReservoir(kEncodedReservoirSizeBytes);
    iLoggerEncodedAudioReservoir = new Logger(*iEncodedAudioReservoir, "Encoded Audio Reservoir");
    // construct push logger slightly out of sequence
    iLoggerSupply = new Logger("Supply", *iEncodedAudioReservoir);
    iSupply = new Supply(*iMsgFactory, /**iEncodedAudioReservoir*/*iLoggerSupply);

    // construct decoded reservoir out of sequence.  It doesn't pull from the left so doesn't need to know its preceeding element
    iDecodedAudioReservoir = new DecodedAudioReservoir(kDecodedReservoirSize);
    iLoggerDecodedAudioReservoir = new Logger(*iDecodedAudioReservoir, "Decoded Audio Reservoir");

    iContainer = new Codec::Container(*iMsgFactory, /**iEncodedAudioReservoir*/*iLoggerEncodedAudioReservoir);
    iLoggerContainer = new Logger(*iContainer, "Codec Container");
    
    // construct push logger slightly out of sequence
    iLoggerCodecController = new Logger("Codec Controller", *iDecodedAudioReservoir);
    iCodecController = new Codec::CodecController(*iMsgFactory, /**iContainer*/*iLoggerContainer, /**iDecodedAudioReservoir*/*iLoggerCodecController);

    iVariableDelay = new VariableDelay(*iMsgFactory, /**iDecodedAudioReservoir*/*iLoggerDecodedAudioReservoir, kVariableDelayRampDuration);
    iLoggerVariableDelay = new Logger(*iVariableDelay, "Variable Delay");
    iStopper = new Stopper(*iMsgFactory, /**iVariableDelay*/*iLoggerVariableDelay, *this, kStopperRampDuration);
    iLoggerStopper = new Logger(*iStopper, "Stopper");
    iReporter = new Reporter(/**iStopper*/*iLoggerStopper, *this);
    iLoggerReporter = new Logger(*iReporter, "Reporter");
    iSplitter = new Splitter(/**iReporter*/*iLoggerReporter, iNullSongcaster);
    iLoggerSplitter = new Logger(*iSplitter, "Splitter");
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, /**iSplitter*/*iLoggerSplitter, *this,
                                               kStarvationMonitorNormalSize, kStarvationMonitorStarvationThreshold,
                                               kStarvationMonitorGorgeSize, kStarvationMonitorRampUpDuration);
    iLoggerStarvationMonitor = new Logger(*iStarvationMonitor, "Starvation Monitor");
    iPreDriver = new PreDriver(*iMsgFactory, /**iStarvationMonitor*/*iLoggerStarvationMonitor, aDriverMaxAudioBytes);
    iLoggerPreDriver = new Logger(*iPreDriver, "PreDriver");

    iPipelineEnd = iLoggerPreDriver;
    if (iPipelineEnd == NULL) {
        iPipelineEnd = iPreDriver;
    }

    //iLoggerEncodedAudioReservoir->SetEnabled(true);
    //iLoggerContainer->SetEnabled(true);
    //iLoggerCodecController->SetEnabled(true);
    //iLoggerDecodedAudioReservoir->SetEnabled(true);
    //iLoggerVariableDelay->SetEnabled(true);
    //iLoggerStopper->SetEnabled(true);
    //iLoggerReporter->SetEnabled(true);
    //iLoggerSplitter->SetEnabled(true);
    //iLoggerStarvationMonitor->SetEnabled(true);
    //iLoggerPreDriver->SetEnabled(true);

    //iLoggerEncodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerContainer->SetFilter(Logger::EMsgAll);
    //iLoggerCodecController->SetFilter(Logger::EMsgAll);
    //iLoggerDecodedAudioReservoir->SetFilter(Logger::EMsgAll);
    //iLoggerVariableDelay->SetFilter(Logger::EMsgAll);
    //iLoggerStopper->SetFilter(Logger::EMsgAll);
    //iLoggerReporter->SetFilter(Logger::EMsgAll);
    //iLoggerSplitter->SetFilter(Logger::EMsgAll);
    //iLoggerStarvationMonitor->SetFilter(Logger::EMsgAll);
    //iLoggerPreDriver->SetFilter(Logger::EMsgAll);
}

PipelineManager::~PipelineManager()
{
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
    delete iLoggerVariableDelay;
    delete iVariableDelay;
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

void PipelineManager::AddCodec(Codec::CodecBase* aCodec)
{
    iCodecController->AddCodec(aCodec);
}

void PipelineManager::Quit()
{
    iQuitting = true;
    /*if (iStatus != EPlaying) */ { // always send quit message and ensure pipeline is playing.
        OutputQuit();
        Play();
        iTargetStatus = EQuit;
    }
}

void PipelineManager::NotifyStatus()
{
    EPipelineState state;
    iLock.Wait();
    if (iQuitting) {
        iLock.Signal();
        return;
    }
    ASSERT(iTargetStatus == iStatus);
    switch (iTargetStatus)
    {
    case EPlaying:
        state = (iBuffering? EPipelineBuffering : EPipelinePlaying);
        break;
    case EHalted:
        state = EPipelinePaused;
        break;
    case EFlushed:
        state = EPipelineStopped;
        break;
    default:
        ASSERTS();
        state = EPipelineBuffering; // will never reach here but the compiler doesn't realise this
    }
    iLock.Signal();
    iObserver.NotifyPipelineState(state);
}

MsgFactory& PipelineManager::Factory()
{
    return *iMsgFactory;
}

void PipelineManager::Play()
{
    iLock.Wait();
    if (iStatus == EPlaying) {
        iLock.Signal();
        return; // already playing so ignore this additional request
    }
    if (iStatus == EHalting) {
        iHaltCompletedIgnoreCount++;
    }
    else if (iStatus == EFlushing) {
        iFlushCompletedIgnoreCount++;
    }
    iStopper->Start();
    iStatus = EPlaying;
    iTargetStatus = EPlaying;
    iLock.Signal();
    NotifyStatus();
}

void PipelineManager::Pause()
{
    AutoMutex a(iLock);
    if (iTargetStatus != EPlaying) {
        // any other status means we're already halting, halted or beyond halted (flush is preceded by halt)
        // in any of these cases we can safely ignore this additional request
        return;
    }
    iTargetStatus = EHalted;
    iStopper->BeginHalt();
    iStatus = EHalting;
}

void PipelineManager::Stop()
{
    AutoMutex a(iLock);
    if (iTargetStatus == EFlushed || iTargetStatus == EQuit) {
        return; // already stopped or in the process of stopping so ignore this additional request
    }
    iTargetStatus = EFlushed;
    if (iStatus == EPlaying) {
        iStopper->BeginHalt();
        iStatus = EHalting;
    }
    else if (iStatus == EHalted) {
        iStopper->BeginFlush();
        OutputFlush();
        iStatus = EFlushing;
    }
}

TBool PipelineManager::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    // FIXME - update iTargetStatus
    return iCodecController->Seek(aTrackId, aStreamId, aSecondsAbsolute);
}

void PipelineManager::OutputTrack(const Brx& aUri, TUint aTrackId)
{
    iSupply->OutputTrack(aUri, aTrackId);
}

void PipelineManager::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    iSupply->OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
}

void PipelineManager::OutputData(const Brx& aData)
{
    iSupply->OutputData(aData);
}

void PipelineManager::OutputMetadata(const Brx& aMetadata)
{
    iSupply->OutputMetadata(aMetadata);
}

void PipelineManager::OutputFlush()
{
    iSupply->OutputFlush();
}

void PipelineManager::OutputQuit()
{
    iSupply->OutputQuit();
}

Msg* PipelineManager::Pull()
{
    return iPipelineEnd->Pull();
}

void PipelineManager::PipelineHalted()
{
    iLock.Wait();
    if (iHaltCompletedIgnoreCount > 0) {
        iHaltCompletedIgnoreCount--;
        iLock.Signal();
        return;
    }
    switch (iTargetStatus)
    {
    case EPlaying:
        iTargetStatus = EHalted;
        // fallthrough
    case EHalted:
        iStatus = EHalted;
        iLock.Signal();
        NotifyStatus();
        break;
    case EFlushed:
    case EQuit:
        iStatus = EFlushing;
        iStopper->BeginFlush();
        OutputFlush();
        iLock.Signal();
        break;
    default:
        ASSERTS();
        break;
    }
}

void PipelineManager::PipelineFlushed()
{
    iLock.Wait();
    if (iFlushCompletedIgnoreCount > 0) {
        iFlushCompletedIgnoreCount--;
        iLock.Signal();
        return;
    }
    switch (iTargetStatus)
    {
    case EFlushed:
        iStatus = EFlushed;
        iLock.Signal();
        NotifyStatus();
        break;
    case EQuit:
        iStatus = EFlushed;
        iLock.Signal();
        OutputQuit();
        break;
    default:
        ASSERTS();
    }
}

void PipelineManager::NotifyTrack()
{
    iObserver.NotifyTrack();
}

void PipelineManager::NotifyMetaText(const Brx& aText)
{
    iObserver.NotifyMetaText(aText);
}

void PipelineManager::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iObserver.NotifyTime(aSeconds, aTrackDurationSeconds);
}

void PipelineManager::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iObserver.NotifyStreamInfo(aStreamInfo);
}

void PipelineManager::NotifyStarvationMonitorBuffering(TBool aBuffering)
{
    iLock.Wait();
    iBuffering = aBuffering;
    const TBool notify = (iStatus == EPlaying);
    iLock.Signal();
    if (notify) {
        NotifyStatus();
    }
}


// NullPipelineObserver

void NullPipelineObserver::NotifyPipelineState(EPipelineState /*aState*/)
{
}

void NullPipelineObserver::NotifyTrack()
{
}

void NullPipelineObserver::NotifyMetaText(const Brx& /*aText*/)
{
}

void NullPipelineObserver::NotifyTime(TUint /*aSeconds*/, TUint /*aTrackDurationSeconds*/)
{
}


void NullPipelineObserver::NotifyStreamInfo(const DecodedStreamInfo& /*aStreamInfo*/)
{
}


// LoggingPipelineObserver

void LoggingPipelineObserver::NotifyPipelineState(EPipelineState aState)
{
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
    Log::Print("Pipeline state change: %s\n", state);
}

void LoggingPipelineObserver::NotifyTrack()
{
    Log::Print("Pipeline report property: TRACK\n");
}

void LoggingPipelineObserver::NotifyMetaText(const Brx& aText)
{
    Log::Print("Pipeline report property: METATEXT {");
    Log::Print(aText);
    Log::Print("}\n");
}

void LoggingPipelineObserver::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    Log::Print("Pipeline report property: TIME {secs=%u; duration=%u}\n", aSeconds, aTrackDurationSeconds);
}


void LoggingPipelineObserver::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
               aStreamInfo.BitRate(), aStreamInfo.BitDepth(), aStreamInfo.SampleRate(), aStreamInfo.NumChannels());
    Log::Print(aStreamInfo.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aStreamInfo.TrackLength(), aStreamInfo.Lossless());
}
