#ifndef HEADER_OHM_SENDER
#define HEADER_OHM_SENDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Http.h>

#include "Ohm.h"
#include "OhmMsg.h"
#include "OhmSocket.h"
#include "OhmSenderDriver.h"

namespace OpenHome {
namespace Av {

class ProviderSender;

class OhmSenderDriver : public IOhmSenderDriver
{
    static const TUint kMaxAudioFrameBytes = 16 * 1024;
	static const TUint kMaxHistoryFrames = 100;

public:
    OhmSenderDriver();
    void SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName);
    void SendAudio(const TByte* aData, TUint aBytes);

private:    
    // IOhmSenderDriver
    virtual void SetEnabled(TBool aValue);
    virtual void SetActive(TBool aValue);
    virtual void SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter);
    virtual void SetTtl(TUint aValue);
    virtual void SetLatency(TUint aValue);
    virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal);
	virtual void Resend(const Brx& aFrames);

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
};

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
    static const TUint kTimerExpiryTimeoutMs = 10000;
    static const TUint kMaxSlaveCount = 4;
	static const TUint kMaxMimeTypeBytes = 100;
    static const TUint kMaxZoneFrameBytes = 1 * 1024;
    static const TUint kTimerZoneUriDelayMs = 100;
    static const TUint kTimerPresetInfoDelayMs = 100;

public:
	static const TUint kMaxNameBytes = 64;
	static const TUint kMaxTrackUriBytes = Ohm::kMaxTrackUriBytes;
	static const TUint kMaxTrackMetadataBytes = Ohm::kMaxTrackMetadataBytes;
	static const TUint kMaxTrackMetatextBytes = Ohm::kMaxTrackMetatextBytes;

public:
    OhmSender(Net::DvDevice& aDevice, IOhmSenderDriver& aDriver, const Brx& aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TUint aLatency, TBool aMulticast, TBool aEnabled, const Brx& aImage, const Brx& aMimeType, TUint aPreset);
    ~OhmSender();

	const Brx& Image() const;
	const Brx& MimeType() const;
	const Brx& SenderUri() const;
	const Brx& SenderMetadata() const; // might change after SetName() and SetMulticast()

	void SetName(const Brx& aValue);
	void SetChannel(TUint aValue);
    void SetInterface(TIpAddress aValue);
    void SetTtl(TUint aValue);
    void SetLatency(TUint aValue);
    void SetMulticast(TBool aValue);
	void SetEnabled(TBool aValue);
    void SetTrack(const Brx& aUri, const Brx& aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart);
	void SetMetatext(const Brx& aValue);
	void SetPreset(TUint aValue);
    
private:
    void RunMulticast();
    void RunUnicast();
	void RunZone();

    void UpdateChannel();
    void UpdateMetadata();
    void UpdateUri();

    void Start();
    void Stop();
    void StartZone();
    void StopZone();
    void EnabledChanged();
    void ChannelChanged();
    void TimerAliveJoinExpired();
    void TimerAliveAudioExpired();
    void TimerExpiryExpired();
    void TimerZoneUriExpired();
    void TimerPresetInfoExpired();
    void Send();
    void SendTrackInfo();
    void SendTrack();
    void SendMetatext();
    void SendSlaveList();
    void SendListen(const Endpoint& aEndpoint);
    void SendLeave(const Endpoint& aEndpoint);
	void SendZoneUri(TUint aCount);
	void SendZoneUri();
	void SendPresetInfo(TUint aCount);
	void SendPresetInfo();
    TUint FindSlave(const Endpoint& aEndpoint);
    void RemoveSlave(TUint aIndex);
    TBool CheckSlaveExpiry();
    
private:
    Net::DvDevice& iDevice;
    IOhmSenderDriver& iDriver;
    Bws<kMaxNameBytes> iName;
    TUint iChannel;
    TIpAddress iInterface;
    TUint iTtl;
    TUint iLatency;
    TBool iMulticast;
    TBool iEnabled;
	Brh iImage;
	Bws<kMaxMimeTypeBytes> iMimeType;
    OhmSocket iSocketOhm;
    OhzSocket iSocketOhz;
    Srs<kMaxAudioFrameBytes> iRxBuffer;
    Bws<kMaxAudioFrameBytes> iTxBuffer;
    Srs<kMaxZoneFrameBytes> iRxZone;
    Bws<kMaxZoneFrameBytes> iTxZone;
    Mutex iMutexStartStop;
    Mutex iMutexActive;
    Mutex iMutexZone;
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
    ThreadFunctor* iThreadZone;
    Bws<Ohm::kMaxUriBytes> iUri;
    Uri iSenderUri;
    Bws<kMaxMetadataBytes> iSenderMetadata;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    TUint iSlaveExpiry[kMaxSlaveCount];
    Timer iTimerAliveJoin;
    Timer iTimerAliveAudio;
    Timer iTimerExpiry;
    Timer iTimerZoneUri;
    Timer iTimerPresetInfo;
    Bws<Ohm::kMaxTrackUriBytes> iTrackUri;
    Bws<Ohm::kMaxTrackMetadataBytes> iTrackMetadata;
    Bws<Ohm::kMaxTrackMetatextBytes> iTrackMetatext;
    TUint iSequenceTrack;
    TUint iSequenceMetatext;
    SocketTcpServer* iServer;
	TBool iClientControllingTrackMetadata;
	TUint iSendZoneUriCount;
	TUint iSendPresetInfoCount;
	TUint iPreset;
};

class OhmSenderSession : public SocketTcpSession
{
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxResponseBytes = 4*1024;
public:
    OhmSenderSession(const OhmSender& aSender);
    ~OhmSenderSession();
private:
    void Run();
    void Error(const HttpStatus& aStatus);
    void Get(TBool aWriteEntity);
private:
	const OhmSender& iSender;
    Srs<kMaxRequestBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    Sws<kMaxResponseBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderExpect iHeaderExpect;
	const HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    Semaphore iSemaphore;
};


} // namespace Av
} // namespace OpenHome

#endif // HEADER_OHM_SENDER

