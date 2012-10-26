#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/AudioReservoir.h>
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

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, ISupplier& aSupplier, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes)
    : iSupplier(aSupplier)
    , iObserver(aObserver)
    , iLock("PLMG")
    , iLoggerAudioReservoir(NULL)
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
                                 kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountAudioFormat,
                                 kMsgCountTrack, kMsgCountMetaText, kMsgCountHalt,
                                 kMsgCountFlush, kMsgCountQuit);
    iAudioReservoir = new AudioReservoir(kDecodedReservoirSize);
    iLoggerAudioReservoir = new Logger(*iAudioReservoir, "Audio Reservoir");
    iVariableDelay = new VariableDelay(*iMsgFactory, /**iAudioReservoir*/*iLoggerAudioReservoir, kVariableDelayRampDuration);
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
    iSupplier.Initialise(*iMsgFactory, *iAudioReservoir);

    //iLoggerAudioReservoir->SetEnabled(true);
    //iLoggerVariableDelay->SetEnabled(true);
    //iLoggerStopper->SetEnabled(true);
    //iLoggerReporter->SetEnabled(true);
    //iLoggerSplitter->SetEnabled(true);
    //iLoggerStarvationMonitor->SetEnabled(true);
    //iLoggerPreDriver->SetEnabled(true);
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
    delete iLoggerAudioReservoir;
    delete iAudioReservoir;
    delete iMsgFactory;
}

void PipelineManager::Quit()
{
    iQuitting = true;
    if (iStatus != EPlaying) {
        iSupplier.Quit(iMsgFactory->CreateMsgQuit());
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

IPipelineElementUpstream& PipelineManager::FinalElement()
{
    if (iLoggerPreDriver == NULL) {
        return *iPreDriver;
    }
    return *iLoggerPreDriver;
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
    iSupplier.Play();
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
        iSupplier.Flush(iMsgFactory->CreateMsgFlush());
        iStatus = EFlushing;
    }
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
        iSupplier.Flush(iMsgFactory->CreateMsgFlush());
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
        iSupplier.Quit(iMsgFactory->CreateMsgQuit());
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

void PipelineManager::NotifyAudioFormat(const AudioFormat& aFormat)
{
    iObserver.NotifyAudioFormat(aFormat);
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


void NullPipelineObserver::NotifyAudioFormat(const AudioFormat& /*aFormat*/)
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


void LoggingPipelineObserver::NotifyAudioFormat(const AudioFormat& aFormat)
{
    Log::Print("Pipeline report property: FORMAT {bitRate=%u; bitDepth=%u, sampleRate=%u, numChannels=%u, codec=",
               aFormat.BitRate(), aFormat.BitDepth(), aFormat.SampleRate(), aFormat.NumChannels());
    Log::Print(aFormat.CodecName());
    Log::Print("; trackLength=%llx, lossless=%u}\n", aFormat.TrackLength(), aFormat.Lossless());
}
