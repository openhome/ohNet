#ifndef HEADER_OHMSENDER
#define HEADER_OHMSENDER

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <Thread.h>
#include <Timer.h>

#include "Ohm.h"

namespace Zapp {

class ProviderSender;

class OhmSender
{
    static const TUint kMaxMetadataBytes = 1000;
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
    static const TUint kThreadStackBytesAudio = 64 * 1024;
    static const TUint kThreadStackBytesNetwork = 64 * 1024;
    static const TUint kThreadPriorityAudio = kPriorityNormal;
    static const TUint kThreadPriorityNetwork = kPriorityNormal;
    static const TUint kTimerAliveJoinTimeoutMs = 10000;
    static const TUint kTimerAliveAudioTimeoutMs = 3000;
    static const TUint kTimerExpiryTimeoutMs = 3100;
    static const TUint kMaxSlaveCount = 4;

public:
	static const TUint kMaxNameBytes = 32;
	static const TUint kMaxTrackUriBytes = Ohm::kMaxTrackUriBytes;
	static const TUint kMaxTrackMetadataBytes = Ohm::kMaxTrackMetadataBytes;
	static const TUint kMaxTrackMetatextBytes = Ohm::kMaxTrackMetatextBytes;

public:
    OhmSender(DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled);
    ~OhmSender();

	void SetName(const Brx& aValue);
	void SetChannel(TUint aValue);
    void SetInterface(TIpAddress aValue);
    void SetTtl(TUint aValue);
    void SetMulticast(TBool aValue);
	void SetEnabled(TBool aValue);

    void SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName);
    
    void StartTrack(TUint64 aSampleStart);
    void StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal);
    void StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal, const Brx& aUri, const Brx& aMetadata);
    
	void SendAudio(const TByte* aData, TUint aBytes);

	void SetMetatext(const Brx& aValue);
    
private:
    void RunPipeline();
    void RunMulticast();
    void RunUnicast();

    void UpdateChannel();
    void UpdateMetadata();

    void Start();
    void Stop();
    void EnabledChanged();
    void ChannelChanged();
    void TimerAliveJoinExpired();
    void TimerAliveAudioExpired();
    void TimerExpiryExpired();
    void Send();
    void SendTrackInfo();
    void SendTrack();
    void SendMetatext();
    void SendSlaveList();
    void SendListen(const Endpoint& aEndpoint);
    void SendLeave(const Endpoint& aEndpoint);
    TUint FindSlave(const Endpoint& aEndpoint);
    void RemoveSlave(TUint aIndex);
    TBool CheckSlaveExpiry();
    
private:
    DvDevice& iDevice;
    Bws<kMaxNameBytes> iName;
    TUint iChannel;
    TIpAddress iInterface;
    TUint iTtl;
    TBool iMulticast;
    TBool iEnabled;
    OhmSocket iSocket;
    Srs<kMaxAudioFrameBytes> iRxBuffer;
    Bws<kMaxAudioFrameBytes> iTxBuffer;
    Mutex iMutexStartStop;
    Mutex iMutexActive;
    Semaphore iNetworkAudioDeactivated;
    Timer iTimerAliveJoin;
    Timer iTimerAliveAudio;
    Timer iTimerExpiry;
    ProviderSender* iProvider;
    TBool iStarted;
    TBool iActive;
    Endpoint iMulticastEndpoint;
    Endpoint iTargetEndpoint;
    TBool iAliveJoined;
    TBool iAliveBlocked;
    ThreadFunctor* iThreadMulticast;
    ThreadFunctor* iThreadUnicast;
    TUint iFrame;
    Bws<Ohm::kMaxUriBytes> iUri;
    Bws<kMaxMetadataBytes> iMetadata;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    TUint iSlaveExpiry[kMaxSlaveCount];
    Bws<Ohm::kMaxTrackUriBytes> iTrackUri;
    Bws<Ohm::kMaxTrackMetadataBytes> iTrackMetadata;
    Bws<Ohm::kMaxTrackMetatextBytes> iTrackMetatext;
    Bws<Ohm::kMaxCodecNameBytes> iCodecName;
    TUint iSampleRate;
    TUint iBitRate;
    TUint iChannels;
    TUint iBitDepth;
    TBool iLossless;
    TUint64 iSampleStart;
    TUint64 iSamplesTotal;
};

} // namespace Zapp

#endif // HEADER_OHMSENDER

