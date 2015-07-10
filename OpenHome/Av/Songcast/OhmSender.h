#ifndef HEADER_OHM_SENDER
#define HEADER_OHM_SENDER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>

#include "Ohm.h"
#include "OhmMsg.h"
#include "OhmSocket.h"
#include "OhmSenderDriver.h"

namespace OpenHome {
class Environment;
namespace Av {

class ProviderSender;
class IOhmTimestamper;
class IOhmTimestampMapper;

class OhmSenderDriver : public IOhmSenderDriver
{
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
    static const TUint kMaxHistoryFrames = 100;
public:
    OhmSenderDriver(Environment& aEnv, IOhmTimestamper* aTimestamper, IOhmTimestampMapper* aTsMapper);
    void SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName);
    void SendAudio(const TByte* aData, TUint aBytes, TBool aHalt = false);
private: // from IOhmSenderDriver
    void SetEnabled(TBool aValue) override;
    void SetActive(TBool aValue) override;
    void SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter) override;
    void SetTtl(TUint aValue) override;
    void SetLatency(TUint aValue) override;
    void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal) override;
    void Resend(const Brx& aFrames) override;
private:
    void ResetLocked();
    void Resend(OhmMsgAudio& aMsg);
private:
    Mutex iMutex;
    TBool iEnabled;
    TBool iActive;
    TBool iSend;
    Endpoint iEndpoint;
    TIpAddress iAdapter;
    Bws<kMaxAudioFrameBytes> iBuffer;
    TUint iFrame;
    TUint iSampleRate;
    TUint iBitRate;
    TUint iChannels;
    TUint iBitDepth;
    TBool iLossless;
    Bws<Ohm::kMaxCodecNameBytes> iCodecName;
    TUint64 iSamplesTotal;
    TUint64 iSampleStart;
    TUint iLatency;
    SocketUdp iSocket;
    OhmMsgFactory iFactory;
    FifoLite<OhmMsgAudio*, kMaxHistoryFrames> iFifoHistory;
    IOhmTimestamper* iTimestamper;
    TBool iFirstFrame;
    IOhmTimestampMapper* iTsMapper;
};

class OhmSender
{
    static const TUint kMaxMetadataBytes = 1000;
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
    static const TUint kThreadStackBytesNetwork = 64 * 1024;
    static const TUint kThreadPriorityNetwork = kPriorityNormal;
    static const TUint kTimerAliveJoinTimeoutMs = 10000;
    static const TUint kTimerAliveAudioTimeoutMs = 3000;
    static const TUint kTimerExpiryTimeoutMs = 10000;
    static const TUint kMaxSlaveCount = 4;
    static const TUint kTtl = 1;
public:
    static const TUint kMaxNameBytes = 64;
    static const TUint kMaxTrackUriBytes = Ohm::kMaxTrackUriBytes;
    static const TUint kMaxTrackMetadataBytes = Ohm::kMaxTrackMetadataBytes;
    static const TUint kMaxTrackMetatextBytes = Ohm::kMaxTrackMetatextBytes;
public:
    OhmSender(Environment& aEnv, Net::DvDeviceStandard& aDevice, IOhmSenderDriver& aDriver, ZoneHandler& aZoneHandler, const Brx& aName, TUint aChannel, TUint aLatency, TBool aMulticast, const Brx& aImageFileName);
    ~OhmSender();

    void SetName(const Brx& aValue);
    void SetChannel(TUint aValue);
    void SetLatency(TUint aValue);
    void SetMulticast(TBool aValue);
    void SetEnabled(TBool aValue);
    void SetTrack(const Brx& aUri, const Brx& aMetadata);
    void SetTrackPosition(TUint64 aSamplesTotal, TUint64 aSampleStart);
    void SetMetatext(const Brx& aValue);
    void SetPreset(TUint aValue);
    void NotifyAudioPlaying(TBool aPlaying);
private:
    void RunMulticast();
    void RunUnicast();
    void UpdateChannel();
    void UpdateMetadata();
    void UpdateUri();
    void CurrentSubnetChanged();
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
    Environment& iEnv;
    Net::DvDeviceStandard& iDevice;
    IOhmSenderDriver& iDriver;
    ZoneHandler* iZoneHandler; // FIXME - store by reference instead
    Bws<kMaxNameBytes> iName;
    TUint iChannel;
    TIpAddress iInterface;
    TUint iLatency;
    TBool iMulticast;
    TBool iEnabled;
    Brh iImageFileName;
    OhmSocket iSocketOhm;
    Srs<kMaxAudioFrameBytes> iRxBuffer;
    Bws<kMaxAudioFrameBytes> iTxBuffer;
    Mutex iMutexStartStop;
    Mutex iMutexActive;
    Semaphore iNetworkDeactivated;
    Semaphore iZoneDeactivated;
    ProviderSender* iProvider;
    TBool iStarted;
    TBool iActive;
    TBool iAliveJoined;
    TBool iAliveBlocked;
    Endpoint iMulticastEndpoint;
    Endpoint iTargetEndpoint;
    TIpAddress iTargetInterface;
    ThreadFunctor* iThreadMulticast;
    ThreadFunctor* iThreadUnicast;
    Bws<Ohm::kMaxUriBytes> iUri;
    TUint iNacnId;
    Uri iSenderUri;
    Bws<kMaxMetadataBytes> iSenderMetadata;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    TUint iSlaveExpiry[kMaxSlaveCount];
    Timer* iTimerAliveJoin;
    Timer* iTimerAliveAudio;
    Timer* iTimerExpiry;
    Bws<Ohm::kMaxTrackUriBytes> iTrackUri;
    Bws<Ohm::kMaxTrackMetadataBytes> iTrackMetadata;
    Bws<Ohm::kMaxTrackMetatextBytes> iTrackMetatext;
    TUint iSequenceTrack;
    TUint iSequenceMetatext;
    TBool iClientControllingTrackMetadata;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHM_SENDER

