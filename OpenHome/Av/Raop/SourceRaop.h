#ifndef HEADER_SOURCE_RAOP
#define HEADER_SOURCE_RAOP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Source.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Av/Raop/UdpServer.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/ObservableBrx.h>

namespace OpenHome {
    class Environment;
    class IPowerManager;
namespace Net {
    class DvStack;
}
namespace Media {
    class PipelineManager;
    class UriProviderSingleTrack;
}
namespace Av {
    class IMediaPlayer;
    class IRaopDiscovery;
    class RaopDiscovery;
    class ProtocolRaop;

class SourceRaop : public Source, public IRaopObserver, private Media::IPipelineObserver
{
private:
    static const Brn kRaopPrefix;
public:
    SourceRaop(IMediaPlayer& aMediaPlayer, Media::UriProviderSingleTrack& aUriProvider, const TChar* aHostName, IObservableBrx& aFriendlyName, const Brx& aMacAddr);
    ~SourceRaop();
    IRaopDiscovery& Discovery();
private: // from ISource
    void Activate() override;
    void Deactivate() override;
    void PipelineStopped() override;
private: // from IRaopObserver
    void NotifySessionStart(TUint aControlPort, TUint aTimingPort) override;
    void NotifySessionEnd() override;
    void NotifySessionWait() override;
private: // from IPipelineObserver
    void NotifyPipelineState(Media::EPipelineState aState) override;
    void NotifyTrack(Media::Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const Media::DecodedStreamInfo& aStreamInfo) override;
private:
    void GenerateMetadata();
    void OpenServers();
    void CloseServers();
    void StartNewTrack();
    void AutoNetAuxChanged(Configuration::ConfigChoice::KvpChoice& aKvp);
    void ActivateIfInactive();
    void DeactivateIfActive();
    void HandleInterfaceChange();
private:
    static const TUint kMaxUdpSize = 1472;
    static const TUint kMaxUdpPackets = 25;
    static const TUint kRaopPrefixBytes = 7;
    static const TUint kMaxPortBytes = 5; // 0-65535
    static const TUint kMaxUriBytes = kRaopPrefixBytes+kMaxPortBytes*2+1;   // raop://xxxxx.yyyyy
    static const TUint kAutoNetAuxOn;
    static const TUint kAutoNetAuxOffVisible;
    static const TUint kAutoNetAuxOffNotVisible;
    static const TChar* kSourceNameStr;
    static const Brn kKeyNetAux;
    Environment& iEnv;
    Mutex iLock;
    Media::PipelineManager& iPipeline;
    Media::UriProviderSingleTrack& iUriProvider;
    RaopDiscovery* iRaopDiscovery;
    ProtocolRaop* iProtocol;
    UdpServerManager iServerManager;
    SocketUdpServer* iServerAudio;   // no ownership
    SocketUdpServer* iServerControl; // no ownership
    SocketUdpServer* iServerTiming;  // no ownership
    Configuration::ConfigChoice* iConfigNetAux;
    TUint iConfigSubId;
    TUint iCurrentAdapterChangeListenerId;
    TUint iSubnetListChangeListenerId;
    TUint iAutoNetAux;
    TBool iAutoSwitch;
    TBool iSessionActive;
    Bws<Media::kTrackMetaDataMaxBytes> iDidlLite;
    Bws<kMaxUriBytes> iNextTrackUri;
    Media::Track* iTrack;
    TUint iTrackPosSeconds;
    TUint iStreamId;
    Media::EPipelineState iTransportState;
    TUint iAudioId;
    TUint iControlId;
    TUint iTimingId;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOURCE_RAOP
