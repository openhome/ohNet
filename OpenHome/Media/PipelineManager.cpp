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

PipelineManager::PipelineManager(Av::IInfoAggregator& aInfoAggregator, ISupplier& aSupplier, IPipelineObserver& aObserver)
    : iSupplier(aSupplier)
    , iObserver(aObserver)
    , iLock("PLMG")
    , iShutdownSem("PLMG", 0)
    , iStatus(EFlushed)
    , iTargetStatus(EFlushed)
    , iHaltCompletedIgnoreCount(0)
    , iFlushCompletedIgnoreCount(0)
    , iBuffering(false)
{
    iMsgFactory = new MsgFactory(aInfoAggregator,
                                 kMsgCountDecodedAudio, kMsgCountAudioPcm, kMsgCountSilence,
                                 kMsgCountPlayablePcm, kMsgCountPlayableSilence, kMsgCountAudioFormat,
                                 kMsgCountTrack, kMsgCountMetaText, kMsgCountHalt,
                                 kMsgCountFlush, kMsgCountQuit);
    iAudioReservoir = new AudioReservoir(kDecodedReservoirSize);
    iVariableDelay = new VariableDelay(*iMsgFactory, *iAudioReservoir, kVariableDelayRampDuration);
    iStopper = new Stopper(*iMsgFactory, *iVariableDelay, *this, kStopperRampDuration);
    iReporter = new Reporter(*iStopper, *this);
    iSplitter = new Splitter(*iReporter, iNullSongcaster);
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, *iSplitter, *this,
                                               kStarvationMonitorNormalSize, kStarvationMonitorStarvationThreshold,
                                               kStarvationMonitorGorgeSize, kStarvationMonitorRampUpDuration);
    iPreDriver = new PreDriver(*iMsgFactory, *iStarvationMonitor);
    iSupplier.Initialise(*iMsgFactory, *iAudioReservoir);
}

PipelineManager::~PipelineManager()
{
    Quit();

    delete iPreDriver;
    delete iStarvationMonitor;
    delete iSplitter;
    delete iReporter;
    delete iStopper;
    delete iVariableDelay;
    delete iAudioReservoir;
    delete iMsgFactory;
}

void PipelineManager::Quit()
{
    if (iStatus == EFlushed) {
        iSupplier.Quit(iMsgFactory->CreateMsgQuit());
    }
    else {
        Stop();
        iTargetStatus = EQuit;
    }

    // wait to be told that the driver has shutdown
    iShutdownSem.Wait();
}

void PipelineManager::NotifyStatus()
{
    EPipelineState state;
    iLock.Wait();
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
    return *iPreDriver;
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
        iSupplier.Flush(iMsgFactory->CreateMsgFlush());
        iStatus = EFlushing;
    }
}

void PipelineManager::DriverShutdown()
{
    iShutdownSem.Signal();
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
    default:
        ASSERTS();
        break;
    case EHalted:
        iStatus = EHalted;
        iLock.Signal();
        NotifyStatus();
        break;
    case EFlushed:
    case EQuit:
        iStatus = EFlushing;
        iStopper->BeginFlush();
        iLock.Signal();
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
    iLock.Signal();
    NotifyStatus();
}
