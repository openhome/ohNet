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
using namespace OpenHome::Media;
using namespace OpenHome::Net;


// SourceFactory
ISource* SourceFactory::NewRaop(IMediaPlayer& aMediaPlayer, const TChar* aHostName, const Brx& aDeviceName)
{ // static
    UriProviderSingleTrack* raopUriProvider = new UriProviderSingleTrack("RAOP", aMediaPlayer.TrackFactory());
    aMediaPlayer.Add(raopUriProvider);
    return new SourceRaop(aMediaPlayer.Env(), aMediaPlayer.DvStack(), aMediaPlayer.Pipeline(), *raopUriProvider, aMediaPlayer.PowerManager(), aHostName, aDeviceName);
}


// SourceRaop

const Brn SourceRaop::kRaopPrefix("raop://");

SourceRaop::SourceRaop(Environment& aEnv, Net::DvStack& aDvStack, Media::PipelineManager& aPipeline, Media::UriProviderSingleTrack& aUriProvider, IPowerManager& aPowerManager, const TChar* aHostName, const Brx& aDeviceName)
    : Source("Net Aux", "Net Aux")
    , iLock("SRAO")
    , iPipeline(aPipeline)
    , iUriProvider(aUriProvider)
    , iServerManager(aEnv, kMaxUdpSize, kMaxUdpPackets)
    , iTrack(NULL)
    , iTrackPosSeconds(0)
    , iPipelineTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iTransportState(Media::EPipelineStopped)
{
    iRaopDiscovery = new RaopDiscovery(aEnv, aDvStack, aPowerManager, *this, aHostName, aDeviceName);
    iAudioId = iServerManager.CreateServer(kPortAudio);
    iControlId = iServerManager.CreateServer(kPortControl);
    iTimingId = iServerManager.CreateServer(kPortTiming);
    iPipeline.Add(ProtocolFactory::NewRaop(aEnv, *iRaopDiscovery, iServerManager, iAudioId, iControlId, iTimingId)); // bypassing MediaPlayer
    iPipeline.AddObserver(*this);

    SocketUdpServer& audioServer = iServerManager.Find(iAudioId);
    SocketUdpServer& controlServer = iServerManager.Find(iControlId);
    SocketUdpServer& timingServer = iServerManager.Find(iTimingId);
    iRaopDiscovery->SetListeningPorts(audioServer.Port(), controlServer.Port(), timingServer.Port());
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
    iServerManager.OpenAll();
    iTrackPosSeconds = 0;
    iActive = true;
}

void SourceRaop::Deactivate()
{
    iLock.Wait();
    iTransportState = Media::EPipelineStopped;
    if (iTrack != NULL) {
        iTrack->RemoveRef();
        iTrack = NULL;
    }
    iLock.Signal();
    iServerManager.CloseAll();
    Source::Deactivate();
}

void SourceRaop::NotifyStreamStart(TUint /*aControlPort*/, TUint /*aTimingPort*/)
    // FIXME - get client UDP ports via params, then compose into URI so that
    // control and timing servers know ports to send on - currently just send
    // to ports that packets were sent from, which also happen to be the
    // receiving ports.
    // Can also compose UDP servers/ports into URI, so that ProtocolRaop can
    // retrieve servers at the start of each streaming session for each member
    // class requiring a server.

    // Current implementation of getting client UDP ports below causes
    // streaming to fail - possible race condition? Without it, works at least
    // as well as existing solution.
{
    if (!IsActive()) {
        DoActivate();
    }
    if (iTrack == NULL) {
        iPipeline.RemoveAll();
        if (iTrack != NULL) {
            iTrack->RemoveRef();
        }
        //const TUint maxPortBytes = 5;
        //const TUint portCount = 2;
        //Bwh track(kRaopPrefix.Bytes() + portCount*maxPortBytes + portCount-1); // raop://xxxxx.yyyyy.zzzzz
        //track.Append(kRaopPrefix);
        //Ascii::AppendDec(track, aControlPort);
        //track.Append('.');
        //Ascii::AppendDec(track, aTimingPort);
        ////Log::Print("track: ");
        ////Log::Print(track);
        ////Log::Print("\n");
        //iTrack = iUriProvider.SetTrack(track, Brn(""), true);

        iTrack = iUriProvider.SetTrack(Brn("raop://dummyuri"), Brn(""), true);
        iPipeline.Begin(iUriProvider.Mode(), iTrack->Id());
    }
    iLock.Wait();
    iTransportState = Media::EPipelinePlaying;
    iLock.Signal();
    iPipeline.Play();
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
