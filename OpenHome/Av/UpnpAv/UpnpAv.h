#ifndef HEADER_UPNPAV_DEVICE
#define HEADER_UPNPAV_DEVICE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Av {

class ISourceUpnpAv;
class ProviderAvTransport;
class ProviderConnectionManager;
class ProviderRenderingControl;
    
class UpnpAv : public Media::IPipelineObserver
{
public:
    UpnpAv(Net::DvStack& aDvStack, ISourceUpnpAv& aSourceUpnpAv, const Brx& aUdn, const TChar* aFriendlyName, const TChar* aManufacturer, const TChar* aModelName, const TChar* aSupportedProtocols);
    ~UpnpAv();
    void SetEnabled();
    void SetDisabled(Functor aCompleted);
private:
    void DeviceDisabled();
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    Semaphore iSem;
    Net::DvDevice* iDevice;
    ProviderAvTransport* iProviderAvTransport;
    ProviderConnectionManager* iProviderConnectionManager;
    ProviderRenderingControl* iProviderRenderingControl;
    Media::IPipelineObserver* iDownstreamObserver;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_UPNPAV_DEVICE
