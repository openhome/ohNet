#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Raop/SourceRaop.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;


// SourceFactory
ISource* SourceFactory::NewRaop(IMediaPlayer& aMediaPlayer, const TChar* aHostName, const TChar* aFriendlyName, const Brx& aMacAddr)
{ // static
    UriProviderSingleTrack* raopUriProvider = new UriProviderSingleTrack("RAOP", aMediaPlayer.TrackFactory());
    aMediaPlayer.Add(raopUriProvider);
    return new SourceRaop(aMediaPlayer, *raopUriProvider, aHostName, aFriendlyName, aMacAddr);
}


// SourceRaop

const TChar* SourceRaop::kSourceNameStr = "Net Aux";
const Brn SourceRaop::kRaopPrefix("raop://");
const Brn SourceRaop::kKeyNetAux("Source.NetAux.Auto");
const TUint SourceRaop::kAutoNetAuxOn = 0;              // Always visible via Airplay; auto switch when stream starts
const TUint SourceRaop::kAutoNetAuxOffVisible = 1;      // Always visible via Airplay; don't auto switch
const TUint SourceRaop::kAutoNetAuxOffNotVisible = 2;   // Only visible via Airplay when Net Aux source selected

SourceRaop::SourceRaop(IMediaPlayer& aMediaPlayer, UriProviderSingleTrack& aUriProvider, const TChar* aHostName, const TChar* aFriendlyName, const Brx& aMacAddr)
    : Source(kSourceNameStr, kSourceNameStr)
    , iLock("SRAO")
    , iPipeline(aMediaPlayer.Pipeline())
    , iUriProvider(aUriProvider)
    , iServerManager(aMediaPlayer.Env(), kMaxUdpSize, kMaxUdpPackets)
    , iAutoNetAux(kAutoNetAuxOn)
    , iAutoSwitch(true)
    , iSessionActive(false)
    , iTrack(NULL)
    , iTrackPosSeconds(0)
    , iPipelineTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    GenerateMetadata();

    iRaopDiscovery = new RaopDiscovery(aMediaPlayer.Env(), aMediaPlayer.DvStack(), aMediaPlayer.PowerManager(), *this, aHostName, aFriendlyName, aMacAddr);
    iAudioId = iServerManager.CreateServer();
    iControlId = iServerManager.CreateServer();
    iTimingId = iServerManager.CreateServer();
    iPipeline.Add(ProtocolFactory::NewRaop(aMediaPlayer.Env(), *iRaopDiscovery, iServerManager, iAudioId, iControlId)); // bypassing MediaPlayer
    iPipeline.AddObserver(*this);

    iServerAudio = &iServerManager.Find(iAudioId);
    iServerControl = &iServerManager.Find(iControlId);
    iServerTiming = &iServerManager.Find(iTimingId);    // never Open() this
    iRaopDiscovery->SetListeningPorts(iServerAudio->Port(), iServerControl->Port(), iServerTiming->Port());

    std::vector<TUint> choices;
    choices.push_back(kAutoNetAuxOn);
    choices.push_back(kAutoNetAuxOffVisible);
    choices.push_back(kAutoNetAuxOffNotVisible);
    iConfigNetAux = new ConfigChoice(aMediaPlayer.ConfigManagerWriter(), kKeyNetAux, choices, iAutoNetAux);
    iConfigSubId = iConfigNetAux->Subscribe(MakeFunctorConfigChoice(*this, &SourceRaop::AutoNetAuxChanged));
}

SourceRaop::~SourceRaop()
{
    delete iRaopDiscovery;
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
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
        iLock.Signal();
    }
}

void SourceRaop::Deactivate()
{
    iLock.Wait();
    iTransportState = Media::EPipelineStopped;
    if (iTrack != NULL) {
        iTrack->RemoveRef();
        iTrack = NULL;
    }
    if (iAutoNetAux == kAutoNetAuxOffNotVisible) {
        // Disable RAOP visibility if config val was updated while Net Aux was
        // selected source.
        iRaopDiscovery->Disable();
    }
    StopTrack();
    if (iSessionActive) {
        CloseServers();
    }

    iLock.Signal();
    Source::Deactivate();
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
    if (iTrack != NULL) {
        iTrack->RemoveRef();
        iTrack = NULL;
    }

    iTrack = iUriProvider.SetTrack(iNextTrackUri, iDidlLite, true);
    iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());

    iTransportState = Media::EPipelinePlaying;
}

void SourceRaop::StopTrack()
{
    iPipeline.RemoveAll();
    if (iTrack != NULL) {
        iTrack->RemoveRef();
        iTrack = NULL;
    }
    iTransportState = Media::EPipelineStopped;
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
    AutoMutex a(iLock);
    StopTrack();
    iNextTrackUri.SetBytes(0);

    if (IsActive() && iSessionActive) {
        CloseServers();
    }

    iSessionActive = false;
}

void SourceRaop::NotifyPipelineState(Media::EPipelineState aState)
{
    iLock.Wait();
    iTransportState = aState;
    iLock.Signal();
}

void SourceRaop::NotifyTrack(Media::Track& aTrack, const Brx& /*aMode*/, TUint aIdPipeline)
{
    iLock.Wait();
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = &aTrack;
    iTrack->AddRef();
    iPipelineTrackId = aIdPipeline;
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
