#ifndef HEADER_PIPELINE
#define HEADER_PIPELINE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Supply.h>
#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/Media/VariableDelay.h>
#include <OpenHome/Media/TrackInspector.h>
#include <OpenHome/Media/Stopper.h>
#include <OpenHome/Media/Reporter.h>
#include <OpenHome/Media/Splitter.h>
#include <OpenHome/Media/Logger.h>
#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/Av/InfoProvider.h>

namespace OpenHome {
namespace Media {

class Pipeline : public ISupply, public IPipelineElementUpstream, public IFlushIdProvider, public IStopper, private IStopperObserver, private IPipelinePropertyObserver, private IStarvationMonitorObserver
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
    Pipeline(Av::IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, TUint aDriverMaxAudioBytes);
    virtual ~Pipeline();
    void AddCodec(Codec::CodecBase* aCodec);
    void Start();
    MsgFactory& Factory();
    void Play();
    void Pause();
    void Stop();
    void RemoveCurrentStream();
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute);
public: // from ISupply
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputQuit();
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IFlushIdProvider
    TUint NextFlushId();
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private:
    void Quit();
    void NotifyStatus();
private: // from IStopperObserver
    void PipelineHalted();
    void PipelineFlushed();
private: // from IPipelinePropertyObserver
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
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
    IPipelineObserver& iObserver;
    Mutex iLock;
    MsgFactory* iMsgFactory;
    Supply* iSupply;
    Logger* iLoggerSupply;
    EncodedAudioReservoir* iEncodedAudioReservoir;
    Logger* iLoggerEncodedAudioReservoir;
    Codec::Container* iContainer;
    Logger* iLoggerContainer;
    Codec::CodecController* iCodecController;
    Logger* iLoggerCodecController;
    DecodedAudioReservoir* iDecodedAudioReservoir;
    Logger* iLoggerDecodedAudioReservoir;
    VariableDelay* iVariableDelay;
    Logger* iLoggerVariableDelay;
    TrackInspector* iTrackInspector;
    Logger* iLoggerTrackInspector;
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
    IPipelineElementUpstream* iPipelineEnd;
    PipelineBranchNull iNullSongcaster; // FIXME - placeholder for real songcaster
    EStatus iStatus;
    EStatus iTargetStatus; // status at the end of a series of async operations
    TUint iHaltCompletedIgnoreCount;
    TUint iFlushCompletedIgnoreCount;
    TBool iBuffering;
    TBool iQuitting;
    TUint iNextFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE
