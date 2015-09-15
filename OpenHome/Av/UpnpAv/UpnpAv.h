#ifndef HEADER_UPNPAV_DEVICE
#define HEADER_UPNPAV_DEVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/Source.h>

#include <atomic>

namespace OpenHome {
namespace Media {
    class PipelineManager;
    class MimeTypeList;
}
namespace Av {
    class UriProviderRepeater;

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

class IMediaPlayer;
class ProviderAvTransport;
class ProviderConnectionManager;
class ProviderRenderingControl;
    
class SourceUpnpAv : public Source, private ISourceUpnpAv, private Media::IPipelineObserver
{
public:
    static const TChar* kSourceName;
public:
    SourceUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, UriProviderRepeater& aUriProvider, Media::MimeTypeList& aMimeTypeList);
    ~SourceUpnpAv();
private:
    void EnsureActive();
    void NotifyState(Media::EPipelineState aState);
private: // from Source
    void Activate() override;
    void Deactivate() override;
    void PipelineStopped() override;
private: // from ISourceUpnpAv
    void SetTrack(const Brx& aUri, const Brx& aMetaData) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
    void Next() override;
    void Prev() override;
    void Seek(TUint aSecondsAbsolute) override;
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyMode(const Brx& aMode, const Media::ModeInfo& aInfo) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    Mutex iLock;
    Mutex iActivationLock;
    Net::DvDevice& iDevice;
    Media::PipelineManager& iPipeline;
    UriProviderRepeater& iUriProvider;
    Media::Track* iTrack;
    ProviderAvTransport* iProviderAvTransport;
    ProviderConnectionManager* iProviderConnectionManager;
    ProviderRenderingControl* iProviderRenderingControl;
    Media::IPipelineObserver* iDownstreamObserver;
    std::atomic<TUint> iStreamId;
    Media::EPipelineState iTransportState;
    Media::EPipelineState iPipelineTransportState;
    TBool iNoPipelinePrefetchOnActivation;
    TBool iIgnorePipelineStateUpdates;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_UPNPAV_DEVICE
