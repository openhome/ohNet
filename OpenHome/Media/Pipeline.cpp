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

// Pipeline

Pipeline::Pipeline(Av::IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes)
    : iObserver(aObserver)
    , iLock("PLMG")
    , iLoggerSupply(NULL)
    , iLoggerEncodedAudioReservoir(NULL)
    , iLoggerContainer(NULL)
    , iLoggerCodecController(NULL)
    , iLoggerDecodedAudioReservoir(NULL)
    , iLoggerVariableDelay(NULL)
    , iLoggerTrackInspector(NULL)
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
    , iNextFlushId(MsgFlush::kIdInvalid + 1)
    , iTargetHaltId(MsgHalt::kIdInvalid)
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

    iVariableDelay = new VariableDelay(*iMsgFactory, *iLoggerDecodedAudioReservoir, kVariableDelayRampDuration);
    iLoggerVariableDelay = new Logger(*iVariableDelay, "Variable Delay");
    iTrackInspector = new TrackInspector(*iLoggerVariableDelay);
    iLoggerTrackInspector = new Logger(*iTrackInspector, "TrackInspector");
    iStopper = new Stopper(*iMsgFactory, *iLoggerTrackInspector, *iSupply, *this, *this, kStopperRampDuration);
    iLoggerStopper = new Logger(*iStopper, "Stopper");
    iReporter = new Reporter(*iLoggerStopper, *this);
    iLoggerReporter = new Logger(*iReporter, "Reporter");
    iSplitter = new Splitter(*iLoggerReporter);
    iLoggerSplitter = new Logger(*iSplitter, "Splitter");
    iStarvationMonitor = new StarvationMonitor(*iMsgFactory, *iLoggerSplitter, *this,
                                               kStarvationMonitorNormalSize, kStarvationMonitorStarvationThreshold,
                                               kStarvationMonitorGorgeSize, kStarvationMonitorRampUpDuration);
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
    //iLoggerVariableDelay->SetEnabled(true);
    //iLoggerTrackInspector->SetEnabled(true);
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
    //iLoggerVariableDelay->SetFilter(Logger::EMsgAll);
    //iLoggerTrackInspector->SetFilter(Logger::EMsgAll);
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
    delete iLoggerTrackInspector;
    delete iTrackInspector;
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
    iQuitting = true;
    /*if (iStatus != EPlaying) */ { // always send quit message and ensure pipeline is playing.
        OutputQuit();
        Play();
        iTargetStatus = EQuit;
    }
}

void Pipeline::NotifyStatus()
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

MsgFactory& Pipeline::Factory()
{
    return *iMsgFactory;
}

void Pipeline::Play()
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

void Pipeline::Pause()
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

void Pipeline::Stop(TUint aHaltId)
{
    AutoMutex a(iLock);
    iTargetHaltId = aHaltId;
    iStopper->BeginHalt(aHaltId);
    iStatus = EHalting;
    iTargetStatus = EFlushed;

    /*if (iTargetStatus == EFlushed || iTargetStatus == EQuit) {
        return; // already stopped or in the process of stopping so ignore this additional request
    }
    iTargetStatus = EFlushed;
    if (iStatus == EPlaying) {
        iStopper->BeginHalt();
        iStatus = EHalting;
    }
    else if (iStatus == EHalted) {
        iStopper->BeginFlush();
        iStatus = EFlushing;
    }*/
}

void Pipeline::RemoveCurrentStream()
{
    iStopper->RemoveCurrentStream();
}

TBool Pipeline::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute)
{
    // FIXME - update iTargetStatus
    return iCodecController->Seek(aTrackId, aStreamId, aSecondsAbsolute);
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

void Pipeline::PipelineHalted(TUint aHaltId)
{
    iLock.Wait();
    if (iTargetHaltId != MsgHalt::kIdInvalid && iTargetHaltId != aHaltId) {
        iLock.Signal();
        return;
    }
    iTargetHaltId = MsgHalt::kIdInvalid;
    switch (iTargetStatus)
    {
    case EPlaying:
        iTargetStatus = EHalted;
        // fallthrough
    case EHalted:
        iStatus = EHalted;
        break;
    case EFlushed:
    case EQuit:
        iStatus = EFlushed;
        break;
    default:
        ASSERTS();
        break;
    }
    iLock.Signal();
    NotifyStatus();

    /*iLock.Wait();
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
        iLock.Signal();
        iStopper->BeginFlush();
        break;
    default:
        ASSERTS();
        break;
    }*/
}

TUint Pipeline::NextFlushId()
{
    iLock.Wait();
    TUint id = iNextFlushId++;
    iLock.Signal();
    return id;
}

void Pipeline::RemoveStream(TUint aTrackId, TUint aStreamId)
{
    iStopper->RemoveStream(aTrackId, aStreamId);
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
    const TBool notify = (iStatus == EPlaying);
    iLock.Signal();
    if (notify) {
        NotifyStatus();
    }
}
