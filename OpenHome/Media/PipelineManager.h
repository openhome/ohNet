#ifndef HEADER_PIPELINE_MANAGER
#define HEADER_PIPELINE_MANAGER

#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Pipeline.h> // FIXME - Pipeline.h shouldn't be externally visible

#include <vector>

namespace OpenHome {
namespace Media {

class Av::IInfoAggregator;
class IPipelineObserver; // FIXME - define this (or equivalent) in this header
class Pipeline;
class ProtocolManager;
class Filler;
class PipelineIdProvider;
class Codec::CodecBase;
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
private: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IPipelineObserver
    // FIXME - shouldn't silently consume Pipeline events
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack(Track& aTrack, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    Pipeline* iPipeline;
    ProtocolManager* iProtocolManager;
    Filler* iFiller;
    PipelineIdProvider* iIdProvider;
    std::vector<UriProvider*> iUriProviders; // FIXME - should PipelineManager own all UriProviders?
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MANAGER
