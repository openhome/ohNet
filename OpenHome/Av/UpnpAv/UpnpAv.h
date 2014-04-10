#ifndef HEADER_UPNPAV_DEVICE
#define HEADER_UPNPAV_DEVICE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Source.h>

namespace OpenHome {
namespace Media {
    class PipelineManager;
    class UriProviderSingleTrack;
}
namespace Av {

class ISourceUpnpAv
{
public:
    virtual ~ISourceUpnpAv() {}
    virtual void SetTrack(const Brx& aUri, const Brx& aMetaData) = 0;
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual void Next() = 0;
    virtual void Prev() = 0;
    virtual void Seek(TUint aSecondsAbsolute) = 0;
};

class ProviderAvTransport;
class ProviderConnectionManager;
class ProviderRenderingControl;
    
class SourceUpnpAv : public Source, private ISourceUpnpAv, private Media::IPipelineObserver
{
public:
    SourceUpnpAv(Environment& aEnv, Net::DvDevice& aDevice, Media::PipelineManager& aPipeline, Media::UriProviderSingleTrack& aUriProvider, const Brx& aSupportedProtocols);
    ~SourceUpnpAv();
private: // from Source
    void Activate();
    void Deactivate();
private: // from ISourceUpnpAv
    void SetTrack(const Brx& aUri, const Brx& aMetaData);
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Prev();
    void Seek(TUint aSecondsAbsolute);
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    Mutex iLock;
    Net::DvDevice& iDevice;
    Media::PipelineManager& iPipeline;
    Media::UriProviderSingleTrack& iUriProvider;
    Media::Track* iTrack;
    ProviderAvTransport* iProviderAvTransport;
    ProviderConnectionManager* iProviderConnectionManager;
    ProviderRenderingControl* iProviderRenderingControl;
    Media::IPipelineObserver* iDownstreamObserver;
    TUint iPipelineTrackId;
    TUint iStreamId;
    Media::EPipelineState iTransportState;
    Media::EPipelineState iPipelineTransportState;
    TBool iTrackStartedNotPlaying;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_UPNPAV_DEVICE
