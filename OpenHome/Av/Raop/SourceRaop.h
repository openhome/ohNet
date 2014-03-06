#ifndef HEADER_SOURCE_RAOP
#define HEADER_SOURCE_RAOP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Media/UdpServer.h>
#include <OpenHome/Configuration/ConfigManager.h>

namespace OpenHome {
    class Environment;
    class IPowerManager;
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
    class IMediaPlayer;
class IRaopObserver
{
public:
    virtual void NotifySessionStart(TUint aControlPort, TUint aTimingPort) = 0;
    virtual void NotifySessionEnd() = 0;
    virtual ~IRaopObserver() {}
};

class SourceRaop : public Source, public IRaopObserver, private Media::IPipelineObserver
{
private:
    static const Brn kRaopPrefix;
public:
    SourceRaop(Av::IMediaPlayer& aMediaPlayer, Media::UriProviderSingleTrack& aUriProvider, const TChar* aHostName, const TChar* aFriendlyName, const Brx& aMacAddr);
    ~SourceRaop();
    Media::IRaopDiscovery& Discovery();
private: // from ISource
    void Activate();
    void Deactivate();
private: // from IRaopObserver
    void NotifySessionStart(TUint aControlPort, TUint aTimingPort);
    void NotifySessionEnd();
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState);
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TUint aIdPipeline);
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo);
private:
    void OpenServers();
    void CloseServers();
    void StartNewTrack();
    void StopTrack();
    void AutoNetAuxChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
    void ActivateIfInactive();
    void DeactivateIfActive();
private:
    static const TUint kMaxUdpSize = 1472;
    static const TUint kMaxUdpPackets = 25;
    static const TUint kRaopPrefixBytes = 7;
    static const TUint kMaxPortBytes = 5; // 0-65535
    static const TUint kPortAudio = 60400;
    static const TUint kPortControl = 60401;
    static const TUint kPortTiming = 60402;
    static const TUint kMaxUriBytes = kRaopPrefixBytes+kMaxPortBytes*3+2;   // raop://xxxxx.yyyyy.zzzzz
    static const TUint kAutoNetAuxOn;
    static const TUint kAutoNetAuxOffVisible;
    static const TUint kAutoNetAuxOffNotVisible;
    static const Brn kKeyNetAux;
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    Media::UriProviderSingleTrack& iUriProvider;
    Media::RaopDiscovery* iRaopDiscovery;
    Media::UdpServerManager iServerManager;
    Media::SocketUdpServer* iServerAudio;   // no ownership
    Media::SocketUdpServer* iServerControl; // no ownership
    Media::SocketUdpServer* iServerTiming;  // no ownership
    Configuration::ConfigChoice* iConfigNetAux;
    TUint iConfigSubId;
    TUint iAutoNetAux;
    TBool iAutoSwitch;
    TBool iSessionActive;
    Bws<kMaxUriBytes> iNextTrackUri;
    Media::Track* iTrack;
    TUint iTrackPosSeconds;
    TUint iPipelineTrackId;
    TUint iStreamId;
    Media::EPipelineState iTransportState;
    TUint iAudioId;
    TUint iControlId;
    TUint iTimingId;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOURCE_RAOP
