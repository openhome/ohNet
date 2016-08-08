#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Raop/SourceRaop.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/UriProviderSingleTrack.h>
#include <OpenHome/Av/Raop/ProtocolRaop.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Av/SourceFactory.h>
#include <OpenHome/Av/MediaPlayer.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Av/Raop/CodecRaopApple.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Private/Converter.h>

#include <limits.h>
#include <memory>

namespace OpenHome {
namespace Av {

class UriProviderRaop : public Media::UriProviderSingleTrack
{
public:
    UriProviderRaop(IMediaPlayer& aMediaPlayer, Optional<Media::IClockPuller> aClockPuller);
private: // from UriProvider
    Media::ModeClockPullers ClockPullers() override;
private:
    Optional<Media::IClockPuller> iClockPuller;
};

} // namespace Av
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Configuration;
using namespace OpenHome::Media;
using namespace OpenHome::Net;


// SourceFactory

ISource* SourceFactory::NewRaop(IMediaPlayer& aMediaPlayer, Optional<Media::IClockPuller> aClockPuller, const Brx& aMacAddr)
{ // static
    UriProviderSingleTrack* raopUriProvider = new UriProviderRaop(aMediaPlayer, aClockPuller);
    aMediaPlayer.Add(raopUriProvider);
    return new SourceRaop(aMediaPlayer, *raopUriProvider, aMacAddr);
}

const TChar* SourceFactory::kSourceTypeRaop = "NetAux";
const Brn SourceFactory::kSourceNameRaop("Net Aux");


// UriProviderRaop

UriProviderRaop::UriProviderRaop(IMediaPlayer& aMediaPlayer, Optional<Media::IClockPuller> aClockPuller)
    : UriProviderSingleTrack("RAOP", true, aMediaPlayer.TrackFactory())
    , iClockPuller(aClockPuller)
{
}

ModeClockPullers UriProviderRaop::ClockPullers()
{
    return ModeClockPullers(iClockPuller.Ptr());
}


// SourceRaop

const Brn SourceRaop::kRaopPrefix("raop://");

SourceRaop::SourceRaop(IMediaPlayer& aMediaPlayer, UriProviderSingleTrack& aUriProvider, const Brx& aMacAddr)
    : Source(SourceFactory::kSourceNameRaop, SourceFactory::kSourceTypeRaop, aMediaPlayer.Pipeline(), aMediaPlayer.PowerManager(), false)
    , iEnv(aMediaPlayer.Env())
    , iLock("SRAO")
    , iUriProvider(aUriProvider)
    , iServerManager(aMediaPlayer.Env(), kMaxUdpSize, kMaxUdpPackets)
    , iSessionActive(false)
    , iTrack(nullptr)
    , iTrackPosSeconds(0)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    IVolumeManager& volManager = aMediaPlayer.VolumeManager();

    iRaopDiscovery = new RaopDiscovery(aMediaPlayer.Env(), aMediaPlayer.DvStack(), aMediaPlayer.PowerManager(), aMediaPlayer.FriendlyNameObservable(), aMacAddr, volManager, volManager, volManager.VolumeMax()*volManager.VolumeMilliDbPerStep());
    iRaopDiscovery->AddObserver(*this);

    iAudioId = iServerManager.CreateServer();
    iControlId = iServerManager.CreateServer();
    iTimingId = iServerManager.CreateServer();

    iProtocol = new ProtocolRaop(aMediaPlayer.Env(), aMediaPlayer.TrackFactory(), *iRaopDiscovery, *iRaopDiscovery, iServerManager, iAudioId, iControlId);   // creating directly, rather than through ProtocolFactory
    iPipeline.Add(iProtocol);   // takes ownership
    // Only one RAOP codec should be added. Only the first will be used.
    //iPipeline.Add(new CodecRaop());
    iPipeline.Add(new CodecRaopApple());
    iPipeline.AddObserver(*this);

    SocketUdpServer& serverAudio = iServerManager.Find(iAudioId);
    SocketUdpServer& serverControl = iServerManager.Find(iControlId);
    SocketUdpServer& serverTiming = iServerManager.Find(iTimingId);    // never Open() this
    iRaopDiscovery->SetListeningPorts(serverAudio.Port(), serverControl.Port(), serverTiming.Port());

    NetworkAdapterList& adapterList = iEnv.NetworkAdapterList();
    Functor functor = MakeFunctor(*this, &SourceRaop::HandleInterfaceChange);
    iCurrentAdapterChangeListenerId = adapterList.AddCurrentChangeListener(functor, "SourceRaop-current");
    iSubnetListChangeListenerId = adapterList.AddSubnetListChangeListener(functor, "SourceRaop-subnet");
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
        iSessionActive = false;
    }
    iLock.Signal();
}

IRaopDiscovery& SourceRaop::Discovery()
{
    return *iRaopDiscovery;
}

void SourceRaop::Activate(TBool aAutoPlay)
{
    SourceBase::Activate(aAutoPlay);
    iLock.Wait();
    iTrackPosSeconds = 0;

    if (iSessionActive) {
        StartNewTrack();
        iLock.Signal();
        DoPlay();
    }
    else {
        if (iTrack != nullptr) {
            iTrack->RemoveRef();
            iTrack = nullptr;
        }
        GenerateMetadata(); // Updates iDidlLite.
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
    iSessionActive = false; // If switching away from Net Aux, don't want to allow session to be re-initialised without user explicitly re-selecting device from a control point.
    iLock.Signal();
    Source::Deactivate();
}

void SourceRaop::StandbyEnabled()
{
    iPipeline.Stop();
    {
        AutoMutex _(iLock);
        iTransportState = Media::EPipelineStopped;
        iSessionActive = false; // If switching away from Net Aux, don't want to allow session to be re-initialised without user explicitly re-selecting device from a control point.
    }
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
    // Get current system name.
    iDidlLite.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    iDidlLite.Append("<item id=\"\" parentID=\"\" restricted=\"True\">");
    iDidlLite.Append("<dc:title>");

    // Append name.
    Bws<kMaxSourceNameBytes> name;
    Name(name);
    WriterBuffer writerBuf(iDidlLite);
    Converter::ToXmlEscaped(writerBuf, name);

    iDidlLite.Append("</dc:title>");
    iDidlLite.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iDidlLite.Append("</item>");
    iDidlLite.Append("</DIDL-Lite>");
}

void SourceRaop::StartNewTrack()
{
    iPipeline.RemoveAll();
    if (iTrack != nullptr) {
        iTrack->RemoveRef();
        iTrack = nullptr;
    }

    GenerateMetadata(); // Updates iDidlLite.
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

    {
        AutoMutex a(iLock);
        iSessionActive = true;

        iNextTrackUri.Replace(kRaopPrefix);
        Ascii::AppendDec(iNextTrackUri, aControlPort);
        iNextTrackUri.Append('.');
        Ascii::AppendDec(iNextTrackUri, aTimingPort);

        StartNewTrack();
    }

    DoPlay();
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
    // This call will only come in while session should be active.
    // However, it's possible that the pipeline may not have recognised the
    // stream and asked ProtocolRaop to TryStop(), which will have caused it to
    // exit its Stream() method, so SendFlush() will return
    // MsgFlush::kIdInvalid (as it can no longer send a flush).

    TUint flushId = MsgFlush::kIdInvalid;
    {
        AutoMutex a(iLock);
        if (IsActive() && iSessionActive) {
            // Possible race condition here - MsgFlush could pass Waiter before
            // iPipeline::Wait is called.
            flushId = iProtocol->SendFlush(aSeq, aTime);
            if (flushId != MsgFlush::kIdInvalid) {
                iTransportState = Media::EPipelineWaiting;
            }
        }
    }

    if (flushId != MsgFlush::kIdInvalid) {
        iPipeline.Wait(flushId);
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
 
void SourceRaop::HandleInterfaceChange()
{
    //iRaopDiscovery->Disable();
    //iRaopDiscovery->Enable();
    SocketUdpServer& serverAudio = iServerManager.Find(iAudioId);
    SocketUdpServer& serverControl = iServerManager.Find(iControlId);
    SocketUdpServer& serverTiming = iServerManager.Find(iTimingId);    // never Open() this
    iRaopDiscovery->SetListeningPorts(serverAudio.Port(), serverControl.Port(), serverTiming.Port());
}
