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
#include <OpenHome/Media/Seeker.h>
#include <OpenHome/Media/VariableDelay.h>
#include <OpenHome/Media/TrackInspector.h>
#include <OpenHome/Media/Skipper.h>
#include <OpenHome/Media/Waiter.h>
#include <OpenHome/Media/Stopper.h>
#include <OpenHome/Media/Gorger.h>
#include <OpenHome/Media/Reporter.h>
#include <OpenHome/Media/Splitter.h>
#include <OpenHome/Media/Pruner.h>
#include <OpenHome/Media/Logger.h>
#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Media/ClockPuller.h>

namespace OpenHome {
namespace Media {

class Pipeline : public ISupply, public IPipelineElementUpstream, public IFlushIdProvider, public IWaiterObserver, public IStopper, private IStopperObserver, private IPipelinePropertyObserver, private IStarvationMonitorObserver
{
    friend class SuitePipeline; // test code
    static const TUint kMsgCountEncodedAudio    = 768;
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
    static const TUint kMsgCountFlush           = 16;
    static const TUint kMsgCountWait            = 16;
    static const TUint kMsgCountMode            = 20;
    static const TUint kMsgCountDelay           = 20;
    static const TUint kMsgCountQuit            = 1;

    static const TUint kEncodedReservoirSizeBytes            = 500 * 1024;
    static const TUint kDecodedReservoirSize                 = Jiffies::kJiffiesPerMs * 1000;
    static const TUint kSeekerRampDuration                   = Jiffies::kJiffiesPerMs * 20;
    static const TUint kVariableDelayRampDuration            = Jiffies::kJiffiesPerMs * 20;
    static const TUint kSkipperRampDuration                  = Jiffies::kJiffiesPerMs * 500;
    static const TUint kWaiterRampDuration                   = Jiffies::kJiffiesPerMs * 500;
    static const TUint kStopperRampDuration                  = Jiffies::kJiffiesPerMs * 500;
    static const TUint kGorgerDuration                       = Jiffies::kJiffiesPerMs * 1000;
    static const TUint kStarvationMonitorNormalSize          = Jiffies::kJiffiesPerMs * 30;
    static const TUint kStarvationMonitorStarvationThreshold = Jiffies::kJiffiesPerMs * 20;
    static const TUint kStarvationMonitorRampUpDuration      = Jiffies::kJiffiesPerMs * 100;
    static const TUint kSenderMinLatency                     = Jiffies::kJiffiesPerMs * 150;
public:
    Pipeline(Av::IInfoAggregator& aInfoAggregator, IPipelineObserver& aObserver, IStreamPlayObserver& aStreamPlayObserver, TUint aDriverMaxAudioBytes);
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
    TUint SenderMinLatency() const;
public: // from ISupply
    void OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime);
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
    void OutputDelay(TUint aJiffies);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputWait();
    void OutputHalt(TUint aHaltId);
    void OutputQuit();
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
    ClockPuller iClockPuller;
    EStatus iState;
    TBool iBuffering;
    TBool iQuitting;
    TUint iNextFlushId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE
