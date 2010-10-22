#ifndef HEADER_OHMSENDER
#define HEADER_OHMSENDER

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>
#include <Thread.h>

#include "Ohm.h"
#include "DvLinnCoUkSender1.h"

namespace Zapp {

class IProviderSenderHandler
{
public:
    void StoreChannel(TUint aValue);
    void StoreEnabled(TBool aValue);
    ~IProviderSenderHandler() {}
};

class ProviderSender : public DvServiceLinnCoUkMultipusSender1
{
    static const TUint kOhmPort = 51972;
    static const TUint kMaxChannel = 65535;
    static const TUint kTimeoutAudioPresentMs = 1000;

public:
    ProviderSender(DvDevice& aDevice, IProviderSenderHandler& aHandler, TUint aChannel, TBool aEnabled);
    void SetStatusReady();
    void SetStatusSending();
    void SetStatusBlocked();
    void SetStatusInactive();
    void InformAudioPresent();
    
private:
    virtual void Enabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    virtual void SetEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    virtual void Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaChannel);
    virtual void SetChannel(IInvocationResponse& aResponse, TUint aVersion, TUint aaChannel);
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaMetadata);
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaAudio);
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaStatus);
    virtual void InfoAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaInfoAvailable);
    virtual void TimeAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaTimeAvailable);

    void UpdateMetadata();
    void TimerAudioPresentExpired();

private:
    IProviderSenderHandler& iHandler;
    mutable Mutex iMutex;
    Timer iTimerAudioPresent;
    Endpoint iEndpoint;
};

class OhmSender : public IProviderSenderHandler
{
    static const TUint kTtl = 4;
    static const TUint kUdpSendBufBytes = 32 * 1024;
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
    static const TUint kThreadStackBytesAudio = 64 * 1024;
    static const TUint kThreadPriorityAudio = kPriorityNormal;
    static const TUint kTimerAliveJoinTimeoutMs = 10000;
    static const TUint kTimerAliveAudioTimeoutMs = 3000;

public:
    static const TUint kMaxTrackUriBytes = 1000;
    static const TUint kMaxTrackMetadataBytes = 5000;
    static const TUint kMaxTrackMetatextBytes = 1000;

public:
    OhmSender(DvDevice& aDevice);
    ~OhmSender();

    //void Play(const Brx& aAudioBuffer);
    //void SetTrack(const Brx& aUri, const Brx& aMetadata);
    //void SetMetatext(const Brx& aValue);
    
private:
    virtual void StoreChannel(TUint aValue);
    virtual void StoreEnabled(TBool aValue);

private:
    void RunPipeline();
    void RunAudio();
    void RunZone();

    void Start();
    void Stop();
    void EnabledChanged();
    void ChannelChanged();
    void TimerAliveJoinExpired();
    void TimerAliveAudioExpired();
    void SendTrackInfo();
    void SendTrack();
    void SendMetatext();
    void SendZone(TUint aCount);
    void SendZoneUri();
    void SendZoneQuery();
    void TimerSendZoneExpired();
    void TimerMonitorExpired();
    void ChangeChannel();
    void UpdateEndpoint();

private:
    DvDevice& iDevice;
    SocketUdpMulticast iSocketAudio;
    UdpControllerReader iReaderAudio;
    UdpControllerWriter iWriterAudio;
    Srs<kMaxAudioFrameBytes> iAudioReceive;
    Bws<kMaxAudioFrameBytes> iAudioTransmit;
    Mutex iMutexStartStop;
    Mutex iMutexActive;
    Semaphore iNetworkAudioDeactivated;
    Timer iTimerAliveJoin;
    Timer iTimerAliveAudio;
    ProviderSender* iProvider;
    TBool iEnabled;
    TUint iChannel;
    TBool iActivated;
    TBool iStarted;
    TBool iActive;
    Endpoint iEndpoint;
    TBool iAliveJoined;
    TBool iAliveBlocked;
    ThreadFunctor* iThreadAudio;
    TUint iFrame;
    Bws<Ohm::kMaxMpusUriBytes> iMpusUri;
    TBool iSendTrack;
    TBool iSendMetatext;
    Bws<kMaxTrackUriBytes> iTrackUri;
    Bws<kMaxTrackMetadataBytes> iTrackMetadata;
    Bws<kMaxTrackMetatextBytes> iTrackMetatext;
};

} // namespace Zapp

#endif // HEADER_OHMSENDER

