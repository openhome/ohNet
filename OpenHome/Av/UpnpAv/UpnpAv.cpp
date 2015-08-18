#include <OpenHome/Av/UpnpAv/UpnpAv.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/UpnpAv/ProviderAvTransport.h>
#include <OpenHome/Av/UpnpAv/ProviderConnectionManager.h>
#include <OpenHome/Av/UpnpAv/ProviderRenderingControl.h>
#include <OpenHome/Av/UpnpAv/UriProviderRepeater.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Media/PipelineManager.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

ISource* SourceFactory::NewUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice)
{ // static
    UriProviderRepeater* uriProvider = new UriProviderRepeater("UpnpAv", aMediaPlayer.TrackFactory());
    aMediaPlayer.Pipeline().AddObserver(*uriProvider);
    aMediaPlayer.Add(uriProvider);
    return new SourceUpnpAv(aMediaPlayer, aDevice, *uriProvider, aMediaPlayer.MimeTypes());
}

// UpnpAv

const TChar* SourceUpnpAv::kSourceName("UPnP AV");

SourceUpnpAv::SourceUpnpAv(IMediaPlayer& aMediaPlayer, Net::DvDevice& aDevice, UriProviderRepeater& aUriProvider, Media::MimeTypeList& aMimeTypeList)
    : Source(kSourceName, "UpnpAv")
    , iLock("UPA1")
    , iActivationLock("UPA2")
    , iDevice(aDevice)
    , iPipeline(aMediaPlayer.Pipeline())
    , iUriProvider(aUriProvider)
    , iTrack(nullptr)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
    , iPipelineTransportState(Media::EPipelineStopped)
    , iNoPipelinePrefetchOnActivation(false)
{
    iProviderAvTransport = new ProviderAvTransport(iDevice, aMediaPlayer.Env(), *this);
    iProviderConnectionManager = new ProviderConnectionManager(iDevice);
    aMimeTypeList.AddUpnpProtocolInfoObserver(MakeFunctorGeneric(*iProviderConnectionManager, &ProviderConnectionManager::NotifyProtocolInfo));
    iProviderRenderingControl = new ProviderRenderingControl(iDevice, aMediaPlayer.Env(), aMediaPlayer.VolumeManager());
    iPipeline.AddObserver(*this);
    iDownstreamObserver = iProviderAvTransport;
}

SourceUpnpAv::~SourceUpnpAv()
{
    ASSERT(!iDevice.Enabled());
    delete iProviderAvTransport;
    delete iProviderConnectionManager;
    delete iProviderRenderingControl;
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
}

void SourceUpnpAv::EnsureActive()
{
    AutoMutex a(iActivationLock);
    iNoPipelinePrefetchOnActivation = true;
    if (!IsActive()) {
        DoActivate();
    }
    iNoPipelinePrefetchOnActivation = false;
}

void SourceUpnpAv::Activate()
{
    iActive = true;
    if (!iNoPipelinePrefetchOnActivation) {
        const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
        iPipeline.StopPrefetch(iUriProvider.Mode(), trackId);
    }
}

void SourceUpnpAv::Deactivate()
{
    iLock.Wait();
    iTransportState = EPipelineStopped;
    iDownstreamObserver->NotifyPipelineState(EPipelineStopped);
    iLock.Signal();
    Source::Deactivate();
}

void SourceUpnpAv::PipelineStopped()
{
    // FIXME - could nullptr iPipeline (if we also changed it to be a pointer)
}

void SourceUpnpAv::SetTrack(const Brx& aUri, const Brx& aMetaData)
{
    EnsureActive();
    if (iTrack == nullptr || iTrack->Uri() != aUri) {
        if (iTrack != nullptr) {
            iTrack->RemoveRef();
        }
        iTrack = iUriProvider.SetTrack(aUri, aMetaData);

        const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
        if (iTrack == nullptr) {
            iTransportState = Media::EPipelineStopped;
        }
        iPipeline.StopPrefetch(iUriProvider.Mode(), trackId);

        if (iTransportState == Media::EPipelinePlaying) {
            iPipeline.Play();
        }
    }
}

void SourceUpnpAv::Play()
{
    EnsureActive();
    TBool notifyUriProvider = false;
    iLock.Wait();
    if (iTrack != nullptr && iTransportState == Media::EPipelinePlaying) {
        notifyUriProvider = true;
    }
    if (iTrack != nullptr) {
        iTransportState = Media::EPipelinePlaying;
        iLock.Signal();
        if (notifyUriProvider) {
            iPipeline.RemoveAll();
            iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());
        }
        iPipeline.Play();
    }
    else {
        iLock.Signal();
    }
}

void SourceUpnpAv::Pause()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelinePaused;
        iLock.Signal();
        iPipeline.Pause();
    }
}

void SourceUpnpAv::Stop()
{
    if (IsActive()) {
        iLock.Wait();
        iTransportState = Media::EPipelineStopped;
        const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
        iLock.Signal();
        iPipeline.StopPrefetch(iUriProvider.Mode(), trackId);
    }
}

void SourceUpnpAv::Next()
{
    Stop(); // we only store a single track so have nothing to move forward to
}

void SourceUpnpAv::Prev()
{
    Stop(); // we only store a single track so have nothing to move back to
}

void SourceUpnpAv::Seek(TUint aSecondsAbsolute)
{
    if (IsActive()) {
        (void)iPipeline.Seek(iStreamId, aSecondsAbsolute);
    }
}

void SourceUpnpAv::NotifyPipelineState(EPipelineState aState)
{
    iLock.Wait();
    iPipelineTransportState = aState;
    if (aState == Media::EPipelineStopped) {
        iTransportState = aState;
    }
    iLock.Signal();
    if (IsActive()) {
        iDownstreamObserver->NotifyPipelineState(aState);
    }
}

void SourceUpnpAv::NotifyMode(const Brx& /*aMode*/, const ModeInfo& /*aInfo*/)
{
}

void SourceUpnpAv::NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream)
{
    iLock.Wait();
    iStreamId = UINT_MAX;
    iLock.Signal();
    if (IsActive()) {
        iDownstreamObserver->NotifyTrack(aTrack, aMode, aStartOfStream);
        iDownstreamObserver->NotifyPipelineState(iPipelineTransportState);
    }
    else {
        iDownstreamObserver->NotifyPipelineState(EPipelineStopped);
    }
}

void SourceUpnpAv::NotifyMetaText(const Brx& aText)
{
    if (IsActive()) {
        iDownstreamObserver->NotifyMetaText(aText);
    }
}

void SourceUpnpAv::NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds)
{
    if (IsActive()) {
        iDownstreamObserver->NotifyTime(aSeconds, aTrackDurationSeconds);
    }
}

void SourceUpnpAv::NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId = aStreamInfo.StreamId();
    iLock.Signal();
    if (IsActive()) {
        iDownstreamObserver->NotifyStreamInfo(aStreamInfo);
    }
}
