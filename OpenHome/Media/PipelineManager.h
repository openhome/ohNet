#ifndef HEADER_PIPELINE_MANAGER
#define HEADER_PIPELINE_MANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Msg.h>
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
#include <OpenHome/Av/InfoProvider.h>

namespace OpenHome {
namespace Media {

class ISupplier
{
public:
    virtual void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement) = 0;
    virtual void Play() = 0; // FIXME - should pass a uri to be played here
    virtual void Flush(Msg* aMsg) = 0;
    virtual void Quit(Msg* aMsg) = 0; // FIXME - do we need to pass a Quit all the way down the pipeline or can we inject it at the Stopper?
};

enum EPipelineState
{
    EPipelinePlaying
   ,EPipelinePaused
   ,EPipelineStopped
   ,EPipelineBuffering
};

class IPipelineObserver
{
public:
    virtual void NotifyPipelineState(EPipelineState aState) = 0;
    virtual void NotifyTrack() = 0; // FIXME - MsgTrack doesn't contain any data yet
    virtual void NotifyMetaText(const Brx& aText) = 0;
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
};
    
class PipelineManager : private IStopperObserver, private IPipelinePropertyObserver, private IStarvationMonitorObserver
{
    friend class SuitePipeline; // test code
    static const TUint kMsgCountEncodedAudio    = 512;
    static const TUint kMsgCountAudioEncoded    = 768;
    static const TUint kMsgCountDecodedAudio    = 512;
    static const TUint kMsgCountAudioPcm        = 768;
    static const TUint kMsgCountSilence         = 512;
    static const TUint kMsgCountPlayablePcm     = 1024;
    static const TUint kMsgCountPlayableSilence = 1024;
    static const TUint kMsgCountEncodedStream   = 20;
    static const TUint kMsgCountTrack           = 20;
    static const TUint kMsgCountDecodedStream   = 20;
    static const TUint kMsgCountMetaText        = 20;
    static const TUint kMsgCountHalt            = 20;
    static const TUint kMsgCountFlush           = 1;
    static const TUint kMsgCountQuit            = 1;

    static const TUint kEncodedReservoirSizeBytes            = 500 * 1024;
    static const TUint kDecodedReservoirSize                 = Jiffies::kJiffiesPerMs * 1000;
    static const TUint kVariableDelayRampDuration            = Jiffies::kJiffiesPerMs * 200;
    static const TUint kStopperRampDuration                  = Jiffies::kJiffiesPerMs * 500;
    static const TUint kStarvationMonitorNormalSize          = Jiffies::kJiffiesPerMs * 100;
    static const TUint kStarvationMonitorStarvationThreshold = Jiffies::kJiffiesPerMs * 50;
    static const TUint kStarvationMonitorGorgeSize           = Jiffies::kJiffiesPerMs * 1000;
    static const TUint kStarvationMonitorRampUpDuration      = Jiffies::kJiffiesPerMs * 100;
public:
    PipelineManager(Av::IInfoAggregator& aInfoAggregator, ISupplier& aSupplier, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes);
    ~PipelineManager();
    void AddCodec(Codec::CodecBase* aCodec);
    MsgFactory& Factory();
    IPipelineElementUpstream& FinalElement();
    void Play();
    void Pause();
    void Stop();
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute);
private:
    void Quit();
    void NotifyStatus();
private: // from IStopperObserver
    void PipelineHalted();
    void PipelineFlushed();
private: // from IPipelinePropertyObserver
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private: // from IStarvationMonitorObserver
    void NotifyStarvationMonitorBuffering(TBool aBuffering);
private:
    enum EStatus
    {
        EPlaying
       ,EHalting
       ,EHalted
       ,EFlushing
       ,EFlushed
       ,EQuit
    };
private:
    ISupplier& iSupplier;
    IPipelineObserver& iObserver;
    Mutex iLock;
    MsgFactory* iMsgFactory;
    EncodedAudioReservoir* iEncodedAudioReservoir;
    Logger* iLoggerEncodedAudioReservoir;
    Codec::Container* iContainer;
    Logger* iLoggerContainer;
    Codec::CodecController* iCodecController;
    DecodedAudioReservoir* iDecodedAudioReservoir;
    Logger* iLoggerDecodedAudioReservoir;
    VariableDelay* iVariableDelay;
    Logger* iLoggerVariableDelay;
    Stopper* iStopper;
    Logger* iLoggerStopper;
    Reporter* iReporter;
    Logger* iLoggerReporter;
    Splitter* iSplitter;
    Logger* iLoggerSplitter;
    StarvationMonitor* iStarvationMonitor;
    Logger* iLoggerStarvationMonitor;
    PreDriver* iPreDriver;
    Logger* iLoggerPreDriver;
    PipelineBranchNull iNullSongcaster; // FIXME - placeholder for real songcaster
    EStatus iStatus;
    EStatus iTargetStatus; // status at the end of a series of async operations
    TUint iHaltCompletedIgnoreCount;
    TUint iFlushCompletedIgnoreCount;
    TBool iBuffering;
    TBool iQuitting;
};

class NullPipelineObserver : public IPipelineObserver // test helper
{
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
};

class LoggingPipelineObserver : public IPipelineObserver // test helper
{
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MANAGER
