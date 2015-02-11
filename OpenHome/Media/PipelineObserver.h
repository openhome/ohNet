#ifndef HEADER_PIPELINE_OBSERVER
#define HEADER_PIPELINE_OBSERVER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/**
 * Pipeline states.
 */
enum EPipelineState
{
    EPipelinePlaying    /**< Pipeline is playing. */
   ,EPipelinePaused     /**< Pipeline is paused. */
   ,EPipelineStopped    /**< Pipeline is stopped. */
   ,EPipelineBuffering  /**< Pipeline is buffering.  No audio is playing due to unexpected
                             (likely network error) condition.  If this error is resolved,
                             audio will automatically start playing. */
   ,EPipelineWaiting    /**< Pipeline is waiting.  No audio is playing; this is expected due
                             to a change in state of the audio provider.  If the audio provider
                             restarts playing, the pipeline will automatically start too. */
   ,EPipelineStateCount /**< Count of available states. Never reported as a state itself. */
};

/**
 * Pipeline observer interface.
 *
 * Implementors are called whenever pipeline state changes.
 * State changes are normally notified a short period before the change takes effect
 * locally.  All state changes are guaranteed to take effect.
 */
class IPipelineObserver
{
public:
    virtual ~IPipelineObserver() {}
    /**
     * Pipeline state has changed.  This normally implies a transition to/from playing audio.
     *
     * @param[in] aState           New pipeline state.
     */
    virtual void NotifyPipelineState(EPipelineState aState) = 0;
    /**
     * A new track is starting to play.
     *
     * @param[in] aTrack           Uri and metadata for the track.
     * @param[in] aMode            Identifier for the UriProvider which owns aTrack.
     */
    virtual void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) = 0;
    /**
     * Metatext associated with the current track has changed.
     *
     * Some sources will not generate metatext events.
     * The Radio source may cause this to be called.
     *
     * @param[in] aText            Updated metatext.
     */
    virtual void NotifyMetaText(const Brx& aText) = 0;
    /**
     * Called once per second of playback for any track.
     *
     * @param[in] aSeconds         Number of seconds that have been played.
     * @param[in] aTrackDurationSeconds  Duration of the track in seconds.
     */
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    /**
     * Describes an audio stream.
     *
     * Will typically be called once per track, immediately after NotifyTrack().  May also
     * be called if a single track contains many independent audio streams (e.g. an internet
     * radio stream that starts with an advert then moves to the radio station) or after
     * seeking.
     *
     * @param[in] aStreamInfo      Description of the current stream.
     */
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
};

class TransportState
{
public:
    static const TChar* FromPipelineState(EPipelineState aState);
};

class NullPipelineObserver : public IPipelineObserver
{
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
};

class LoggingPipelineObserver : public IPipelineObserver
{
public:
    LoggingPipelineObserver();
    void Enable(TBool aEnable);
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    TBool iEnable;
};
    
} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_OBSERVER
