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

class ProviderSender;

class OhmSender
{
    static const TUint kTtl = 4;
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
    OhmSender(DvDevice& aDevice, TIpAddress aInterface, const Brx& aName, TUint aChannel);
    ~OhmSender();

	void SetName(const Brx& aValue);
	void SetChannel(TUint aValue);
	void SetEnabled(TBool aValue);

    void SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName);
    
    void StartTrack(TUint64 aSampleStart);
    void StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal);
    void StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal, const Brx& aUri, const Brx& aMetadata);
    
	void SendAudio(const TByte* aData, TUint aBytes);
	
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
    void CalculateMclocksPerSample();
    
private:
    DvDevice& iDevice;
    Bws<kMaxNameBytes> iName;
    TUint iChannel;
    TBool iEnabled;
    OhmSocket iSocketAudio;
    Srs<kMaxAudioFrameBytes> iAudioReceive;
    Bws<kMaxAudioFrameBytes> iAudioTransmit;
    Mutex iMutexStartStop;
    Mutex iMutexActive;
    Semaphore iNetworkAudioDeactivated;
    Timer iTimerAliveJoin;
    Timer iTimerAliveAudio;
    ProviderSender* iProvider;
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
    TUint iSampleRate;
    TUint iBitRate;
    TUint iChannels;
    TUint iBitDepth;
    TBool iLossless;
    Bws<OhmHeaderAudio::kMaxCodecNameBytes> iCodecName;
    TUint64 iSampleStart;
    TUint64 iSamplesTotal;
    TUint iTimestamp;
    TUint iMclocksPerSample;
};

} // namespace Zapp

#endif // HEADER_OHMSENDER

