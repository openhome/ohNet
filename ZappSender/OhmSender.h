#ifndef HEADER_OHMSENDER
#define HEADER_OHMSENDER

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>
#include <Thread.h>

#include "Ohm.h"
#include "DvMusicOpenhomeOrgSender1.h"

namespace Zapp {

class ProviderSender : public DvServiceMusicOpenhomeOrgSender1
{
    static const TUint kMaxMetadataBytes = 4096;
    static const TUint kTimeoutAudioPresentMs = 1000;

public:
    ProviderSender(DvDevice& aDevice);
    
    void SetMetadata(const Brx& aValue);
    
    void SetStatusReady();
    void SetStatusSending();
    void SetStatusBlocked();
    void SetStatusInactive();
    
    void InformAudioPresent();
    
private:
    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);

    void UpdateMetadata();
    void TimerAudioPresentExpired();

private:
    Bws<kMaxMetadataBytes> iMetadata;
    mutable Mutex iMutex;
    Timer iTimerAudioPresent;
};

class OhmSender
{
    static const TUint kTtl = 4;
    static const TUint kUdpSendBufBytes = 32 * 1024;
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
    static const TUint kThreadStackBytesAudio = 64 * 1024;
    static const TUint kThreadPriorityAudio = kPriorityNormal;
    static const TUint kTimerAliveJoinTimeoutMs = 10000;
    static const TUint kTimerAliveAudioTimeoutMs = 3000;
    static const TUint kMaxMetadataBytes = 5000;

public:
	static const TUint kMaxNameBytes = 32;
    static const TUint kMaxTrackUriBytes = 1000;
    static const TUint kMaxTrackMetadataBytes = 5000;
    static const TUint kMaxTrackMetatextBytes = 1000;

public:
    OhmSender(DvDevice& aDevice, const Brx& aName, TUint aChannel);
    ~OhmSender();

	void SetName(const Brx& aValue);
	void SetChannel(TUint aValue);
	void SetEnabled(TBool aValue);
	
    //void Play(const Brx& aAudioBuffer);
    //void SetTrack(const Brx& aUri, const Brx& aMetadata);
    //void SetMetatext(const Brx& aValue);
    
private:
    void RunPipeline();
    void RunAudio();

    void UpdateChannel();
    void UpdateMetadata();

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

private:
    DvDevice& iDevice;
    Bws<kMaxNameBytes> iName;
    TUint iChannel;
    TBool iEnabled;
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
    TBool iActivated;
    TBool iStarted;
    TBool iActive;
    Endpoint iEndpoint;
    TBool iAliveJoined;
    TBool iAliveBlocked;
    ThreadFunctor* iThreadAudio;
    TUint iFrame;
    Bws<Ohm::kMaxUriBytes> iUri;
    Bws<kMaxMetadataBytes> iMetadata;
    TBool iSendTrack;
    TBool iSendMetatext;
    Bws<kMaxTrackUriBytes> iTrackUri;
    Bws<kMaxTrackMetadataBytes> iTrackMetadata;
    Bws<kMaxTrackMetatextBytes> iTrackMetatext;
};

} // namespace Zapp

#endif // HEADER_OHMSENDER

