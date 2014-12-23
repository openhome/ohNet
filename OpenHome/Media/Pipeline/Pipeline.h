#ifndef HEADER_PIPELINE
#define HEADER_PIPELINE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Supply.h>
#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Pipeline/DecodedAudioAggregator.h>
#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Media/Pipeline/Seeker.h>
#include <OpenHome/Media/Pipeline/VariableDelay.h>
#include <OpenHome/Media/Pipeline/TrackInspector.h>
#include <OpenHome/Media/Pipeline/Skipper.h>
#include <OpenHome/Media/Pipeline/Waiter.h>
#include <OpenHome/Media/Pipeline/Stopper.h>
#include <OpenHome/Media/Pipeline/Ramper.h>
#include <OpenHome/Media/Pipeline/Gorger.h>
#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Media/Pipeline/Splitter.h>
#include <OpenHome/Media/Pipeline/Pruner.h>
#include <OpenHome/Media/Pipeline/Logger.h>
#include <OpenHome/Media/Pipeline/StarvationMonitor.h>
#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/Media/InfoProvider.h>
#include <OpenHome/Media/ClockPuller.h>

namespace OpenHome {
namespace Media {

class PipelineInitParams
{
    static const TUint kEncodedReservoirSizeBytes       = 1536 * 1024;
    static const TUint kDecodedReservoirSize            = Jiffies::kPerMs * 1536; // some clock pulling algorithms will prefer this is larger than kGorgerDuration
    static const TUint kGorgerSizeDefault               = Jiffies::kPerMs * 1024;
    static const TUint kStarvationMonitorMaxSizeDefault = Jiffies::kPerMs * 50;
    static const TUint kStarvationMonitorMinSizeDefault = Jiffies::kPerMs * 20;
    static const TUint kMaxReservoirStreamsDefault      = 10;
    static const TUint kLongRampDurationDefault         = Jiffies::kPerMs * 500;
    static const TUint kShortRampDurationDefault        = Jiffies::kPerMs * 50;
    static const TUint kEmergencyRampDurationDefault    = Jiffies::kPerMs * 20;
public:
    static PipelineInitParams* New();
    virtual ~PipelineInitParams();
    // setters
    void SetEncodedReservoirSize(TUint aBytes);
    void SetDecodedReservoirSize(TUint aJiffies);
    void SetGorgerDuration(TUint aJiffies);
    void SetStarvationMonitorMaxSize(TUint aJiffies);
    void SetStarvationMonitorMinSize(TUint aJiffies);
    void SetMaxStreamsPerReservoir(TUint aCount);
    void SetLongRamp(TUint aJiffies);
    void SetShortRamp(TUint aJiffies);
    void SetEmergencyRamp(TUint aJiffies);
    // getters
    TUint EncodedReservoirBytes() const;
    TUint DecodedReservoirJiffies() const;
    TUint GorgeDurationJiffies() const;
    TUint StarvationMonitorMaxJiffies() const;
    TUint StarvationMonitorMinJiffies() const;
    TUint MaxStreamsPerReservoir() const;
    TUint RampLongJiffies() const;
    TUint RampShortJiffies() const;
    TUint RampEmergencyJiffies() const;
private:
    PipelineInitParams();
private:
    TUint iEncodedReservoirBytes;
    TUint iDecodedReservoirJiffies;
    TUint iGorgeDurationJiffies;
    TUint iStarvationMonitorMaxJiffies;
    TUint iStarvationMonitorMinJiffies;
    TUint iMaxStreamsPerReservoir;
    TUint iRampLongJiffies;
    TUint iRampShortJiffies;
    TUint iRampEmergencyJiffies;
};

class Pipeline : public ISupply, public IPipelineElementUpstream, public IFlushIdProvider, public IWaiterObserver, public IStopper, private IStopperObserver, private IPipelinePropertyObserver, private IStarvationMonitorObserver
{
    friend class SuitePipeline; // test code

    static const TUint kSenderMinLatency        = Jiffies::kPerMs * 150;
    static const TUint kReservoirCount          = 4; // Encoded + Decoded + StarvationMonitor + spare

    static const TUint kMsgCountSilence         = 410; // 2secs @ 5ms per msg + 10 spare
    static const TUint kMsgCountPlayablePcm     = 10;
    static const TUint kMsgCountPlayableSilence = 10;
    static const TUint kMsgCountMetaText        = 20;
    static const TUint kMsgCountHalt            = 20;
    static const TUint kMsgCountFlush           = 16;
    static const TUint kMsgCountWait            = 16;
    static const TUint kMsgCountMode            = 20;
    static const TUint kMsgCountQuit            = 1;
public:
    Pipeline(PipelineInitParams* aInitParams, IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, IStreamPlayObserver& aStreamPlayObserver, ISeekRestreamer& aSeekRestreamer);
    virtual ~Pipeline();
    void AddCodec(Codec::CodecBase* aCodec);
    void Start();
    void Quit();
    MsgFactory& Factory();
    void Play();
    void Pause();
    void Wait(TUint aFlushId);
    void Stop(TUint aHaltId);
    void RemoveCurrentStream();
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute);
    void AddObserver(ITrackObserver& aObserver);
    TBool SupportsMimeType(const Brx& aMimeType); // can only usefully be called after codecs have been added
    IPipelineElementDownstream* SetSender(IPipelineElementDownstream& aSender);
    TUint SenderMinLatencyMs() const;
public: // from ISupply
    void OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller) override;
    void OutputSession() override;
    void OutputTrack(Track& aTrack, TUint aTrackId) override;
    void OutputDelay(TUint aJiffies) override;
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
    void OutputMetadata(const Brx& aMetadata) override;
    void OutputFlush(TUint aFlushId) override;
    void OutputWait() override;
    void OutputHalt(TUint aHaltId) override;
    void OutputQuit() override;
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IFlushIdProvider
    TUint NextFlushId();
private: // from IWaiterObserver
    void PipelineWaiting(TBool aWaiting);
private: // from IStopper
    void RemoveStream(TUint aTrackId, TUint aStreamId);
private:
    void DoPlay(TBool aQuit);
    void NotifyStatus();
private: // from IStopperObserver
    void PipelinePaused();
    void PipelineStopped();
    void PipelinePlaying();
//    void PipelineHalted(TUint aHaltId);
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
       ,EPaused
       ,EStopped
       ,EWaiting
    };
private:
    PipelineInitParams* iInitParams;
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
    DecodedAudioAggregator* iDecodedAudioAggregator;
    Logger* iLoggerDecodedAudioAggregator;
    DecodedAudioReservoir* iDecodedAudioReservoir;
    Logger* iLoggerDecodedAudioReservoir;
    Seeker* iSeeker;
    Logger* iLoggerSeeker;
    VariableDelay* iVariableDelay1;
    Logger* iLoggerVariableDelay1;
    TrackInspector* iTrackInspector;
    Logger* iLoggerTrackInspector;
    Skipper* iSkipper;
    Logger* iLoggerSkipper;
    Waiter* iWaiter;
    Logger* iLoggerWaiter;
    Stopper* iStopper;
    Logger* iLoggerStopper;
    Ramper* iRamper;
    Logger* iLoggerRamper;
    Gorger* iGorger;
    Logger* iLoggerGorger;
    Reporter* iReporter;
    Logger* iLoggerReporter;
    Splitter* iSplitter;
    Logger* iLoggerSplitter;
    VariableDelay* iVariableDelay2;
    Logger* iLoggerVariableDelay2;
    Pruner* iPruner;
    Logger* iLoggerPruner;
    StarvationMonitor* iStarvationMonitor;
    Logger* iLoggerStarvationMonitor;
    PreDriver* iPreDriver;
    Logger* iLoggerPreDriver;
    IPipelineElementUpstream* iPipelineEnd;
    EStatus iState;
    TBool iBuffering;
    TBool iWaiting;
    TBool iQuitting;
    TUint iNextFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE
