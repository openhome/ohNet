#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Raop/SourceRaop.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Av/Raop/CodecRaop.h>
#include <OpenHome/Media//ClockPullerUtilisation.h>

#include <limits.h>

namespace OpenHome {
namespace Av {

class UriProviderRaop : public Media::UriProviderSingleTrack
{
public:
    UriProviderRaop(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock);
    ~UriProviderRaop();
private: // from UriProvider
    Media::IClockPuller* ClockPuller() override;
private:
    Media::ClockPullerUtilisationPerStreamLeft* iClockPuller;
};

} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;


// SourceFactory

ISource* SourceFactory::NewRaop(IMediaPlayer& aMediaPlayer, Media::IPullableClock* aPullableClock, const TChar* aHostName, IObservableBrx& aFriendlyName, const Brx& aMacAddr)
{ // static
    UriProviderSingleTrack* raopUriProvider = new UriProviderRaop(aMediaPlayer, aPullableClock);
    aMediaPlayer.Add(raopUriProvider);
    return new SourceRaop(aMediaPlayer, *raopUriProvider, aHostName, aFriendlyName, aMacAddr);
}


// UriProviderRaop

UriProviderRaop::UriProviderRaop(IMediaPlayer& aMediaPlayer, IPullableClock* aPullableClock)
    : UriProviderSingleTrack("RAOP", true, true, aMediaPlayer.TrackFactory())
{
    if (aPullableClock == nullptr) {
        iClockPuller = nullptr;
    }
    else {
        iClockPuller = new ClockPullerUtilisationPerStreamLeft(aMediaPlayer.Env(), *aPullableClock);
    }
}

UriProviderRaop::~UriProviderRaop()
{
    delete iClockPuller;
}

IClockPuller* UriProviderRaop::ClockPuller()
{
    return iClockPuller;
}


// SourceRaop

const TChar* SourceRaop::kSourceNameStr = "Net Aux";
const Brn SourceRaop::kRaopPrefix("raop://");
const Brn SourceRaop::kKeyNetAux("Source.NetAux.Auto");
const TUint SourceRaop::kAutoNetAuxOn = 0;              // Always visible via Airplay; auto switch when stream starts
const TUint SourceRaop::kAutoNetAuxOffVisible = 1;      // Always visible via Airplay; don't auto switch
const TUint SourceRaop::kAutoNetAuxOffNotVisible = 2;   // Only visible via Airplay when Net Aux source selected

SourceRaop::SourceRaop(IMediaPlayer& aMediaPlayer, UriProviderSingleTrack& aUriProvider, const TChar* aHostName, IObservableBrx& aFriendlyName, const Brx& aMacAddr)
    : Source(kSourceNameStr, kSourceNameStr)
    , iEnv(aMediaPlayer.Env())
    , iLock("SRAO")
    , iPipeline(aMediaPlayer.Pipeline())
    , iUriProvider(aUriProvider)
    , iVolume(aMediaPlayer.VolumeManager(), aMediaPlayer.VolumeManager())
    , iServerManager(aMediaPlayer.Env(), kMaxUdpSize, kMaxUdpPackets)
    , iAutoNetAux(kAutoNetAuxOn)
    , iAutoSwitch(true)
    , iSessionActive(false)
    , iTrack(nullptr)
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    GenerateMetadata();

    iRaopDiscovery = new RaopDiscovery(aMediaPlayer.Env(), aMediaPlayer.DvStack(), aMediaPlayer.PowerManager(), aHostName, aFriendlyName, aMacAddr, iVolume);
    iRaopDiscovery->AddObserver(*this);

    iAudioId = iServerManager.CreateServer();
    iControlId = iServerManager.CreateServer();
    iTimingId = iServerManager.CreateServer();

    iProtocol = new ProtocolRaop(aMediaPlayer.Env(), aMediaPlayer.TrackFactory(), iVolume, *iRaopDiscovery, iServerManager, iAudioId, iControlId);          // creating directly, rather than through ProtocolFactory
    iPipeline.Add(iProtocol);   // takes ownership
    iPipeline.Add(new CodecRaop());
    iPipeline.AddObserver(*this);

    iServerAudio = &iServerManager.Find(iAudioId);
    iServerControl = &iServerManager.Find(iControlId);
    iServerTiming = &iServerManager.Find(iTimingId);    // never Open() this
    iRaopDiscovery->SetListeningPorts(iServerAudio->Port(), iServerControl->Port(), iServerTiming->Port());

    std::vector<TUint> choices;
    choices.push_back(kAutoNetAuxOn);
    choices.push_back(kAutoNetAuxOffVisible);
    choices.push_back(kAutoNetAuxOffNotVisible);
    iConfigNetAux = new ConfigChoice(aMediaPlayer.ConfigInitialiser(), kKeyNetAux, choices, iAutoNetAux);
    iConfigSubId = iConfigNetAux->Subscribe(MakeFunctorConfigChoice(*this, &SourceRaop::AutoNetAuxChanged));


    NetworkAdapterList& adapterList = iEnv.NetworkAdapterList();
    Functor functor = MakeFunctor(*this, &SourceRaop::HandleInterfaceChange);
    iCurrentAdapterChangeListenerId = adapterList.AddCurrentChangeListener(functor);
    iSubnetListChangeListenerId = adapterList.AddSubnetListChangeListener(functor);
}

SourceRaop::~SourceRaop()
{
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iCurrentAdapterChangeListenerId);
    iEnv.NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    delete iRaopDiscovery;

    iLock.Wait();
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
    if (iSessionActive) {
        CloseServers();
        iSessionActive = false;
    }
    iLock.Signal();

    iConfigNetAux->Unsubscribe(iConfigSubId);
    delete iConfigNetAux;
}

IRaopDiscovery& SourceRaop::Discovery()
{
    return *iRaopDiscovery;
}

void SourceRaop::Activate()
{
    iLock.Wait();
    iTrackPosSeconds = 0;
    iActive = true;
    if (iAutoNetAux == kAutoNetAuxOffNotVisible) {
        iRaopDiscovery->Enable();
    }

    if (iSessionActive) {
        OpenServers();
        StartNewTrack();
        iLock.Signal();
        iPipeline.Play();
    }
    else {
        if (iTrack != nullptr) {
            iTrack->RemoveRef();
            iTrack = nullptr;
        }
        iTrack = iUriProvider.SetTrack(iNextTrackUri, iDidlLite);
        const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
        iLock.Signal();
        iPipeline.StopPrefetch(iUriProvider.Mode(), trackId);
    }
}

void SourceRaop::Deactivate()
{
    iLock.Wait();
    iTransportState = Media::EPipelineStopped;
    if (iAutoNetAux == kAutoNetAuxOffNotVisible) {
        // Disable RAOP visibility if config val was updated while Net Aux was
        // selected source.
        iRaopDiscovery->Disable();
    }
    if (iSessionActive) {
        CloseServers();
        iSessionActive = false;
    }
    iLock.Signal();
    Source::Deactivate();
}

void SourceRaop::PipelineStopped()
{
    // FIXME - could nullptr iPipeline (if we also changed it to be a pointer)
}

void SourceRaop::GenerateMetadata()
/**
 * Helper method - should only be called during construction.
 */
{
    iDidlLite.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    iDidlLite.Append("<item id=\"\" parentID=\"\" restricted=\"True\">");
    iDidlLite.Append("<dc:title>");
    iDidlLite.Append(kSourceNameStr);
    iDidlLite.Append("</dc:title>");
    iDidlLite.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iDidlLite.Append("</item>");
    iDidlLite.Append("</DIDL-Lite>");
}

void SourceRaop::OpenServers()
{
    iServerAudio->Open();
    iServerControl->Open();
}

void SourceRaop::CloseServers()
{
    iServerAudio->Close();
    iServerControl->Close();
}

void SourceRaop::StartNewTrack()
{
    iPipeline.RemoveAll();
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
        iTrack = nullptr;
    }

    iTrack = iUriProvider.SetTrack(iNextTrackUri, iDidlLite);
    const TUint trackId = (iTrack==nullptr? Track::kIdNone : iTrack->Id());
    iPipeline.Begin(iUriProvider.Mode(), trackId);

    iTransportState = Media::EPipelinePlaying;
}

void SourceRaop::NotifySessionStart(TUint aControlPort, TUint aTimingPort)
{
    if (!IsActive()) {
        DoActivate();
    }

    iLock.Wait();
    if (!iSessionActive) {
        OpenServers();
    }
    iSessionActive = true;

    iNextTrackUri.Replace(kRaopPrefix);
    Ascii::AppendDec(iNextTrackUri, aControlPort);
    iNextTrackUri.Append('.');
    Ascii::AppendDec(iNextTrackUri, aTimingPort);

    if (iAutoSwitch || IsActive()) {
        StartNewTrack();
        iLock.Signal();
        iPipeline.Play();
    }
    else {
        iLock.Signal();
    }
}

void SourceRaop::NotifySessionEnd()
{
    iLock.Wait();
    iNextTrackUri.SetBytes(0);

    TBool shouldStop = (IsActive() && iSessionActive) ? true : false;
    if (shouldStop) {
        iPipeline.RemoveAll();
        if (iTrack != nullptr) {
            iTrack->RemoveRef();
            iTrack = nullptr;
        }
        CloseServers();
    }

    iSessionActive = false;
    iTransportState = Media::EPipelineStopped;
    iLock.Signal();

    if (shouldStop) {
        iPipeline.Stop();
    }
}

void SourceRaop::NotifySessionWait(TUint aSeq, TUint aTime)
{
    iLock.Wait();
    if (IsActive() && iSessionActive) {
        // Possible race condition here - MsgFlush could pass Waiter before
        // iPipeline::Wait is called.
        TUint flushId = iProtocol->SendFlush(aSeq, aTime);
        iTransportState = Media::EPipelineWaiting;
        iLock.Signal();
        iPipeline.Wait(flushId);
    }
    else {
        iLock.Signal();
    }
}

void SourceRaop::NotifyPipelineState(Media::EPipelineState aState)
{
    iLock.Wait();
    iTransportState = aState;
    iLock.Signal();
}

void SourceRaop::NotifyMode(const Brx& /*aMode*/, const ModeInfo& /*aInfo*/)
{
}

void SourceRaop::NotifyTrack(Media::Track& aTrack, const Brx& /*aMode*/, TBool /*aStartOfStream*/)
{
    iLock.Wait();
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
    }
    iTrack = &aTrack;
    iTrack->AddRef();
    iLock.Signal();
}

void SourceRaop::NotifyMetaText(const Brx& /*aText*/)
{
}

void SourceRaop::NotifyTime(TUint aSeconds, TUint /*aTrackDurationSeconds*/)
{
    iLock.Wait();
    iTrackPosSeconds = aSeconds;
    iLock.Signal();
}

void SourceRaop::NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo)
{
    iLock.Wait();
    iStreamId = aStreamInfo.StreamId();
    iLock.Signal();
}

void SourceRaop::AutoNetAuxChanged(ConfigChoice::KvpChoice& aKvp)
{
    AutoMutex a(iLock);
    iAutoNetAux = aKvp.Value();

    switch (iAutoNetAux) {
    case kAutoNetAuxOn:
        ActivateIfInactive();
        iAutoSwitch = true;
        break;
    case kAutoNetAuxOffVisible:
        ActivateIfInactive();
        iAutoSwitch = false;
        break;
    case kAutoNetAuxOffNotVisible:
        DeactivateIfActive();
        iAutoSwitch = false;
        break;
    default:
        ASSERTS();
    }
}

void SourceRaop::ActivateIfInactive()
{
    iRaopDiscovery->Enable();
}

void SourceRaop::DeactivateIfActive()
{
    if (!iActive) {
        iRaopDiscovery->Disable();
    }
}

void SourceRaop::HandleInterfaceChange()
{
    //iRaopDiscovery->Disable();
    //iRaopDiscovery->Enable();
    iRaopDiscovery->SetListeningPorts(iServerAudio->Port(), iServerControl->Port(), iServerTiming->Port());
}
