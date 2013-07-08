#ifndef HEADER_SOURCE_RAOP
#define HEADER_SOURCE_RAOP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>

namespace OpenHome {
    class Environment;
namespace Net {
    class DvStack;
}
namespace Media {
    class PipelineManager;
    class UriProviderSingleTrack;
    class IRaopDiscovery;
    class RaopDiscovery;
}
namespace Av {

class IRaopObserver
{
public:
    //virtual ~IObserverRaop() {}
    //virtual void NotifyStreamStart(TUint aAudioPort, TUint aControlPort, TUint aTimingPort) = 0;
    virtual void NotifyStreamStart() = 0;
};

class SourceRaop : public Source, public IRaopObserver, private Media::IPipelineObserver
{
public:
    SourceRaop(Environment& aEnv, Net::DvStack& aDvStack, Media::PipelineManager& aPipeline, Media::UriProviderSingleTrack& aUriProvider, TUint aDiscoveryPort);
    ~SourceRaop();
    Media::IRaopDiscovery& Discovery();
private: // from ISource
    void Activate();
    void Deactivate();
private: // from IRaopObserver
    void NotifyStreamStart();
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    Media::UriProviderSingleTrack& iUriProvider;
    Media::RaopDiscovery* iRaopDiscovery;
    Media::Track* iTrack;
    TUint iTrackPosSeconds;
    TUint iPipelineTrackId;
    TUint iStreamId;
    Media::EPipelineState iTransportState;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOURCE_RAOP
