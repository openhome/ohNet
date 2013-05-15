#ifndef HEADER_PIPELINE_MANAGER
#define HEADER_PIPELINE_MANAGER

#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Pipeline.h> // FIXME - Pipeline.h shouldn't be externally visible

#include <vector>

namespace OpenHome {
namespace Av {
    class IInfoAggregator;
}
namespace Media {

class IPipelineObserver; // FIXME - define this (or equivalent) in this header
class Pipeline;
class ProtocolManager;
class Filler;
class PipelineIdProvider;
namespace Codec {
    class CodecBase;
}
class Protocol;
class ContentProcessor;
class UriProvider;

class PipelineManager : public IPipelineElementUpstream, private IPipelineObserver
{
public:
    PipelineManager(Av::IInfoAggregator& aInfoAggregator, TUint aDriverMaxAudioBytes); // FIXME - config options, observer
    ~PipelineManager();
    void Add(Codec::CodecBase* aCodec);
    void Add(Protocol* aProtocol);
    void Add(ContentProcessor* aContentProcessor);
    void Add(UriProvider* aUriProvider);
    void Start(); // should be called after all Add()s
    void AddObserver(IPipelineObserver& aObserver);
    void Begin(const Brx& aStyle, const Brx& aProviderId);
    void Play();
    void Pause();
    void Stop();
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute);
    void Next();
    void Prev();
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    Mutex iLock;
    Pipeline* iPipeline;
    ProtocolManager* iProtocolManager;
    Filler* iFiller;
    PipelineIdProvider* iIdProvider;
    std::vector<UriProvider*> iUriProviders; // FIXME - should PipelineManager own all UriProviders?
    std::vector<IPipelineObserver*> iObservers;
    BwsStyle iStyle;
    BwsTrackUri iProviderId; // some sources may mis-use ProviderId by passing a uri here
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MANAGER
