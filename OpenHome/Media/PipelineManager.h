#ifndef HEADER_PIPELINE_MANAGER
#define HEADER_PIPELINE_MANAGER

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/Pipeline/SpotifyReporter.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/MuteManager.h>

#include <vector>

namespace OpenHome {
namespace Av {
    class IInfoAggregator;
}
namespace Media {
class Pipeline;
class PipelineInitParams;
class IPipelineAnimator;
class ProtocolManager;
class ITrackObserver;
class Filler;
class IdManager;
class IMimeTypeList;
namespace Codec {
    class CodecBase;
}
class Protocol;
class ContentProcessor;
class UriProvider;

class PriorityArbitratorPipeline : public IPriorityArbitrator, private INonCopyable
{
    static const TUint kNumThreads = 4; // Filler, CodecController, Gorger, StarvationMonitor
public:
    PriorityArbitratorPipeline(TUint aOpenHomeMax);
private: // from IPriorityArbitrator
    TUint Priority(const TChar* aId, TUint aRequested, TUint aHostMax) override;
    TUint OpenHomeMin() const override;
    TUint OpenHomeMax() const override;
    TUint HostRange() const override;
private:
    const TUint iOpenHomeMax;
};

/**
 * External interface to the pipeline.
 */
class PipelineManager : public IPipeline
                      , public IPipelineIdManager
                      , public IMute
                      , private IPipelineObserver
                      , private ISeekRestreamer
                      , private IUrlBlockWriter
{
public:
    PipelineManager(PipelineInitParams* aInitParams, IInfoAggregator& aInfoAggregator, TrackFactory& aTrackFactory, IMimeTypeList& aMimeTypeList);
    ~PipelineManager();
    /**
     * Signal that the pipeline should quit.
     *
     * Normal shutdown order is
     *    Call Quit()
     *    Wait until Pull() returns a MsgQuit
     *    delete PipelineManager
     */
    void Quit();
    /**
     * Add a codec to the pipeline.
     *
     * There should only be a single instance of each codec aded.
     * Must be called before Start().
     *
     * @param[in] aCodec           Ownership transfers to PipelineManager.
     */
    void Add(Codec::CodecBase* aCodec);
    /**
     * Add a protocol to the pipeline.
     *
     * Multiple instances of a protocol may be added.
     * Must be called before Start().
     *
     * @param[in] aProtocol        Ownership transfers to PipelineManager.
     */
    void Add(Protocol* aProtocol);
    /**
     * Add a content processor to the pipeline.
     *
     * Typically only used by the Radio source (so may be added by it)
     * Must be called before Start().
     *
     * @param[in] aContentProcessor   Ownership transfers to PipelineManager.
     */
    void Add(ContentProcessor* aContentProcessor);
    /**
     * Add a uri provider to the pipeline.
     *
     * Must be called before Start().
     * Will typically be called during construction of a source so need not be called
     * directly by application code.
     *
     * @param[in] aUriProvider     Ownership transfers to PipelineManager.
     */
    void Add(UriProvider* aUriProvider);
    /**
     * Signal that all plug-ins have been Add()ed and the pipeline is ready to receive audio.
     *
     * Begin() can only be called after Start() returns.
     */
    void Start();
    /**
     * Add an observer of changes in pipeline state.
     *
     * Should be called before Start().
     *
     * @param[in] aObserver        Observer.  Ownership remains with caller.
     */
    void AddObserver(IPipelineObserver& aObserver);
    /**
     * Remove an observer.
     *
     * Can be called at any time.  Can be called even if AddObserver() was not called.
     * Callbacks may be run while this call is in progress.  No more callbacks will be
     * received after this completes.
     *
     * @param[in] aObserver        Previously added observer.
     */
    void RemoveObserver(IPipelineObserver& aObserver);
    void AddObserver(ITrackObserver& aObserver);
    /**
     * Retrieve a sample reporter.
     *
     * @return  ISpotifyReporter that reports the number of samples that have
     *          passed by it since the last MsgMode.
     */
    ISpotifyReporter& SpotifyReporter() const;
    /**
     * Retrieve a track change observer.
     *
     * @return  ITrackChangeObserver that can be notified out-of-band that the
     *          current track has changed, allowing IPipelinePropertyObservers
     *          to be updated without requiring a MsgTrack to be passed down
     *          the pipeline.
     */
    ITrackChangeObserver& TrackChangeObserver() const;
    /**
     * Instruct the pipeline what should be streamed next.
     *
     * Several other tracks may already exist in the pipeline.  Call Stop() or
     * RemoveAll() before this to control what is played next.
     *
     * @param[in] aMode            Identifier for the UriProvider
     * @param[in] aTrackId         Identifier of track to be played (Id() from Track class,
     *                             not pipelineTrackId as reported by pipeline).
     */
    void Begin(const Brx& aMode, TUint aTrackId);
    /**
     * Play the pipeline.
     *
     * Pipeline state will move to either EPipelinePlaying or EPipelineBuffering.
     * Begin() must have been called more recently than Stop() or RemoveAll() for audio
     * to be played.
     */
    void Play();
    /**
     * Pause the pipeline.
     *
     * If the pipeline is playing, the current track will ramp down.  Calling Play()
     * will restart playback at the same point.
     * Pipeline state will then change to EPipelinePaused.
     */
    void Pause();
    /**
     * Warn of a (planned) pending discontinuity in audio.
     *
     * Tell the pipeline to ramp down then discard audio until it pulls a MsgFlush with
     * identifier aFlushId.  Pipeline state will then move into EPipelineWaiting.
     */
    void Wait(TUint aFlushId);
    /**
     * Stop the pipeline.
     *
     * Stop playing any current track.  Don't play any pending tracks already in the
     * pipeline.  Don't add any new tracks to the pipeline.  Pipeline state will move
     * to EPipelineStopped.
     */
    void Stop();
    /**
     * Remove all current pipeline content, fetch but don't play a new track.
     *
     * Stops any current track (ramping down if necessary) then invalidates any pending
     * tracks.  Begins to fetch a new track.  Metadata describing the track will be
     * reported to observers but the track will not start playing.
     * This allows UIs to show what will be played next and can be useful e.g. when switching sources.
     *
     * @param[in] aMode            Identifier for the UriProvider
     * @param[in] aTrackId         Identifier of track to be played (Id() from Track class,
     *                             not pipelineTrackId as reported by pipeline).
     */
    void StopPrefetch(const Brx& aMode, TUint aTrackId);
    /**
     * Remove all pipeline content.  Prevent new content from being added.
     *
     * Use Begin() to select what should be played next.
     */
    void RemoveAll();
    /**
     * Seek to a specified point inside the current track.
     *
     * @param[in] aStreamId        Stream identifier.
     * @param[in] aSecondsAbsolute Number of seconds into the track to seek to.
     *
     * @return  true if the seek succeeded; false otherwise.
     */
    TBool Seek(TUint aStreamId, TUint aSecondsAbsolute);
    /**
     * Move immediately to the next track from the current UriProvider (or Source).
     *
     * Ramps down, removes the rest of the current track then fetches the track that
     * logically follows it.  The caller is responsible for calling Play() to start
     * playing this new track.
     */
    void Next();
    /**
     * Move immediately to the previous track from the current UriProvider (or Source).
     *
     * Ramps down, removes the rest of the current track then fetches the track that
     * logically precedes it.  The caller is responsible for calling Play() to start
     * playing this new track.
     */
    void Prev();
    IPipelineElementUpstream& InsertElements(IPipelineElementUpstream& aTail);
    TUint SenderMinLatencyMs() const;
private:
    void RemoveAllLocked();
private: // from IPipeline
    Msg* Pull() override;
    void SetAnimator(IPipelineAnimator& aAnimator) override;
private: // from IPipelineIdManager
    void InvalidateAt(TUint aId) override;
    void InvalidateAfter(TUint aId) override;
    void InvalidatePending() override;
    void InvalidateAll() override;
private: // from IMute
    void Mute() override;
    void Unmute() override;
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private: // from ISeekRestreamer
    TUint SeekRestream(const Brx& aMode, TUint aTrackId) override;
private: // from IUrlBlockWriter
    TBool TryGet(IWriter& aWriter, const Brx& aUrl, TUint64 aOffset, TUint aBytes) override;
private:
    class PrefetchObserver : public IStreamPlayObserver
    {
    public:
        PrefetchObserver();
        ~PrefetchObserver();
        void SetTrack(TUint aTrackId);
        void Wait(TUint aTimeoutMs);
    private: // from IStreamPlayObserver
        void NotifyTrackFailed(TUint aTrackId);
        void NotifyStreamPlayStatus(TUint aTrackId, TUint aStreamId, EStreamPlay aStatus);
    private:
        void CheckTrack(TUint aTrackId);
    private:
        Mutex iLock;
        Semaphore iSem;
        TUint iTrackId;
    };
private:
    Mutex iLock;
    Mutex iPublicLock;
    Pipeline* iPipeline;
    ProtocolManager* iProtocolManager;
    Filler* iFiller;
    IdManager* iIdManager;
    std::vector<UriProvider*> iUriProviders;
    std::vector<IPipelineObserver*> iObservers;
    EPipelineState iPipelineState;
    Semaphore iPipelineStoppedSem;
    BwsMode iMode;
    TUint iTrackId;
    PrefetchObserver* iPrefetchObserver;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MANAGER
