#ifndef HEADER_PIPELINE_MANAGER
#define HEADER_PIPELINE_MANAGER

#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Av {
    class IInfoAggregator;
}
namespace Media {
class Pipeline;
class ProtocolManager;
class ITrackObserver;
class Filler;
class IdManager;
namespace Codec {
    class CodecBase;
}
class Protocol;
class ContentProcessor;
class UriProvider;

class PipelineManager : public IPipelineElementUpstream, public IPipelineIdManager, private IPipelineObserver
{
public:
    PipelineManager(Av::IInfoAggregator& aInfoAggregator, TrackFactory& aTrackFactory, TUint aDriverMaxAudioBytes); // FIXME - config options
    ~PipelineManager();
    void Quit();
    void Add(Codec::CodecBase* aCodec);
    void Add(Protocol* aProtocol);
    void Add(ContentProcessor* aContentProcessor);
    void Add(UriProvider* aUriProvider);
    void Start(); // should be called after all Add()s
    void AddObserver(IPipelineObserver& aObserver);
    void RemoveObserver(IPipelineObserver& aObserver);
    void AddObserver(ITrackObserver& aObserver);
    void Begin(const Brx& aMode, TUint aTrackId);
    void Play();
    void Pause();
    void Wait(TUint aFlushId);
    void Stop();
    void StopPrefetch(const Brx& aMode, TUint aTrackId);
    void RemoveAll();
    TBool Seek(TUint aPipelineTrackId, TUint aStreamId, TUint aSecondsAbsolute);
    TBool Next(); // returns true if a new track should be immediately played
    TBool Prev(); // returns true if a new track should be immediately played
    TBool SupportsMimeType(const Brx& aMimeType); // can only usefully be called after codecs have been added
    IPipelineElementDownstream* SetSender(IPipelineElementDownstream& aSender);
    TUint SenderMinLatencyMs() const;
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IPipelineIdManager
    void InvalidateAt(TUint aId);
    void InvalidateAfter(TUint aId);
    void InvalidatePending();
    void InvalidateAll();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    class PrefetchObserver : public IStreamPlayObserver
    {
    public:
        PrefetchObserver();
        ~PrefetchObserver();
        void Quit();
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
    PrefetchObserver iPrefetchObserver;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MANAGER
