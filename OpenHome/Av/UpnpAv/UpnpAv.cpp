#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/UpnpAv/ProviderAvTransport.h>
#include <OpenHome/Av/UpnpAv/ProviderConnectionManager.h>
#include <OpenHome/Av/UpnpAv/ProviderRenderingControl.h>
#include <OpenHome/Media/Tests/AllocatorInfoLogger.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Net;

// UpnpAv

UpnpAv::UpnpAv(DvStack& aDvStack, ISourceUpnpAv& aSourceUpnpAv, const Brx& aUdn, const TChar* aFriendlyName, const TChar* aManufacturer, const TChar* aModelName, const TChar* aSupportedProtocols)
    : iSem("UPAV", 0)
{
    iDevice = new DvDeviceStandard(aDvStack, aUdn);
    iDevice->SetAttribute("Upnp.Domain", "upnp.org");
    iDevice->SetAttribute("Upnp.Type", "MediaRenderer");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aFriendlyName);
    iDevice->SetAttribute("Upnp.Manufacturer", aManufacturer);
    iDevice->SetAttribute("Upnp.ModelName", aModelName);
    iProviderAvTransport = new ProviderAvTransport(*iDevice, aDvStack.Env(), aSourceUpnpAv);
    iProviderConnectionManager = new ProviderConnectionManager(*iDevice, aSupportedProtocols);
    iProviderRenderingControl = new ProviderRenderingControl(*iDevice);
    iDownstreamObserver = iProviderAvTransport;
    iDevice->SetEnabled();
}

UpnpAv::~UpnpAv()
{
    SetDisabled(MakeFunctor(*this, &UpnpAv::DeviceDisabled));
    iSem.Wait();
    delete iProviderAvTransport;
    delete iProviderConnectionManager;
    delete iProviderRenderingControl;
    delete iDevice;
}

void UpnpAv::SetEnabled()
{
    if (!iDevice->Enabled()) {
        iDevice->SetEnabled();
    }
}

void UpnpAv::SetDisabled(Functor aCompleted)
{
    if (iDevice->Enabled()) {
        iDevice->SetDisabled(aCompleted);
    }
    else if (aCompleted) {
        aCompleted();
    }
}

void UpnpAv::DeviceDisabled()
{
    iSem.Signal();
}

void UpnpAv::NotifyPipelineState(EPipelineState aState)
{
    iDownstreamObserver->NotifyPipelineState(aState);
}

void UpnpAv::NotifyTrack(Track& aTrack, TUint aIdPipeline)
{
    iDownstreamObserver->NotifyTrack(aTrack, aIdPipeline);
}

void UpnpAv::NotifyMetaText(const Brx& aText)
{
    iDownstreamObserver->NotifyMetaText(aText);
}

void UpnpAv::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    iDownstreamObserver->NotifyTime(aSeconds, aTrackDurationSeconds);
}

void UpnpAv::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iDownstreamObserver->NotifyStreamInfo(aStreamInfo);
}
