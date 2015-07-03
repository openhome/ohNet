#ifndef HEADER_PROTOCOL_RAOP
#define HEADER_PROTOCOL_RAOP

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/SupplyAggregator.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

namespace OpenHome {
    class Timer;
namespace Av {

class SocketUdpServer;
class UdpServerManager;
class IRaopDiscovery;

// FIXME - remove this
class IRaopAudioResumer
{
public:
    virtual void AudioResuming() = 0;
    virtual ~IRaopAudioResumer() {}
};

class RtpHeaderFixed
{
public:
    static const TUint kHeaderBytes = 12;
public:
    RtpHeaderFixed();
    RtpHeaderFixed(const Brx& aRtpHeader);
    void Replace(const Brx& aRtpHeader);
    void Clear();
    TBool Padding() const;
    TBool Extension() const;
    TUint CsrcCount() const;
    TBool Marker() const;
    TUint Type() const;
    TUint Seq() const;
    TUint Timestamp() const;
    TUint Ssrc() const;
private:
    TUint iVersion;
    TBool iPadding;
    TBool iExtension;
    TUint iCsrcCount;
    TBool iMarker;
    TUint iPayloadType;
    TUint iSequenceNumber;
    TUint iTimestamp;
    TUint iSsrc;
};

/**
* RAOP appears to use a version of the RTP header that does not conform to
* RFC 3350: https://www.ietf.org/rfc/rfc3550.txt.
*
* It uses the standardised fixed-size header, but can set the Extension bit
* without providing an extension header, and repurposes the SSRC field.
*/
class RtpPacketRaop
{
private:
    // Assume the following:
    // Max Ethernet frame size: 1500 bytes.
    // IPv4 header:             20 bytes.
    // UDP header:              8 bytes.
    // RTP fixed header:        12 bytes.
    // So, 1500-20-8-12 = 1460 RTP payload bytes max.
    static const TUint kMaxPayloadBytes = 1460;
public:
    RtpPacketRaop();
    RtpPacketRaop(const Brx& aRtpPacket);
    void Replace(const Brx& aRtpPacket);
    void Clear();
    const RtpHeaderFixed& Header() const;
    const Brx& Payload() const;
private:
    RtpHeaderFixed iHeader;
    Bws<kMaxPayloadBytes> iPayload;
};

class RtpPacket
{
private:
    static const TUint kMaxPayloadBytes = 1460;
public:
    RtpPacket(const Brx& aRtpPacket);
    const RtpHeaderFixed& Header() const;
    const Brx& Payload() const;
private:
    RtpHeaderFixed iHeader;
    std::vector<TUint> iCsrc;
    TUint iHeaderExtensionProfile;
    TUint iHeaderExtensionBytes;
    Bws<kMaxPayloadBytes> iData;
    Brn iPayload;
};

//class RaopAudioPacket
//{
//public:
//    RaopAudioPacket();
//    void Replace(const Brx& aAudioPacket);
//};

class RaopAudioServer
{
public:
    static const TUint kTypeAudio = 0x60;
    static const TUint kMaxPacketBytes = 1500;
public:
    RaopAudioServer(SocketUdpServer& aServer);
    ~RaopAudioServer();
    void ReadPacket(RtpPacketRaop& aPacket);
    void DoInterrupt();
    void Reset();
private:
    SocketUdpServer& iServer;
    Bws<kMaxPacketBytes> iDataBuffer;
    TUint iSessionId;
    TBool iInterrupted;
};

// FIXME - this class currently writes out the packet length at the start of decoded audio.
// That shouldn't be a responsibility of a generic decoder.
// Maybe have a chain of elements that write into the same buffer (i.e., one element to write the packet length at the start, then pass onto decoder to decode the audio into the buffer).
class RaopAudioDecryptor
{
private:
    static const TUint kAesKeyBytes = sizeof(AES_KEY);
    static const TUint kAesInitVectorBytes = 16;
    static const TUint kPacketSizeBytes = sizeof(TUint);
public:
    void Init(const Brx& aAesKey, const Brx& aAesInitVector);
    void Decrypt(const Brx& aEncryptedIn, Bwx& aAudioOut) const;
private:
    Bws<kAesKeyBytes> iKey;
    Bws<kAesInitVectorBytes> iInitVector;
};

//class IRaopResendRequester
//{
//public:
//    virtual void RequestResend(TUint aSeqStart, TUint aCount) = 0;
//    virtual ~IRaopResendRequester() {}
//};

class IRaopResendReceiver
{
public:
    virtual void ReceiveResend(const RtpPacketRaop& aPacket) = 0;
    virtual ~IRaopResendReceiver() {}
};

//class RaopResendHandler : public IRaopResendRequester, public IRaopResendReceiver
//{
//private:
//    static const TUint kTimerExpiryTimeoutMs = 80;  // Taken from previous codebase.
//public:
//    RaopResendHandler(IRaopResendRequester& aResendRequester, IRaopResendReceiver& aResendReceiver);
//public: // from IRaopResendRequester
//    void RequestResend(TUint aSeqStart, TUint aCount) override;
//public: // from IRaopResendReceiver
//    void ReceiveResend(const RtpPacketRaop& aPacket) override;
//private:
//    void TimerFired();  // Called when a resend times out.
//private:
//    IRaopResendRequester& iRequester;
//    IRaopResendReceiver& iReceiver;
//    TUint iSeqNext;
//    TUint iCount;
//    Timer* iTimer;
//    Mutex iLock;
//};

class RaopControl// : public IRaopResendRequester
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
    static const TUint kPriority = kPriorityNormal-1;
    static const TUint kSessionStackBytes = 10 * 1024;
    static const TUint kInvalidServerPort = 0;
private:
    enum EType {
        ESync = 0x54,
        EResendRequest = 0x55,
        EResendResponse = 0x56,
    };
public:
    RaopControl(SocketUdpServer& aServer, IRaopAudioResumer& aAudioResumer, IRaopResendReceiver& aResendReceiver);
    ~RaopControl();
    //void SetResendReceiver(IRaopResendReceiver& aResendReceiver);
    void DoInterrupt();
    void Reset(TUint aClientPort);
    void Time(TUint& aSenderSkew, TUint& aLatency); // FIXME - do this without output params?
    void RequestResend(TUint aSeqStart, TUint aCount);
//public: // from IRaopResendRequester
//    void RequestResend(TUint aSeqStart, TUint aCount) override;
private:
    void Run();
private:
    Endpoint iEndpoint;
    TUint iClientPort;
    SocketUdpServer& iServer;
    //Srs<kMaxReadBufferBytes> iReceive;
    //Bws<kMaxReadBufferBytes> iResentData;
    Bws<kMaxReadBufferBytes> iPacket;
    IRaopAudioResumer& iAudioResumer;   // FIXME - remove
    ThreadFunctor* iThread;
    IRaopResendReceiver& iResendReceiver;
    TUint iSenderSkew;
    TUint iLatency;
    Mutex iLock;
    //Mutex iMutexRx;
    //Semaphore iSemaResend;
    //TUint iResend;
    //Timer* iTimerExpiry;
    TBool iExit;
};

class IRaopVolumeEnabler;

// NOTE: there are three channels to monitor:
// - Audio
// - Control
// - Timing
// However, the timing channel was never monitored in the previous codebase,
// so no RaopTiming class exists here.
class ProtocolRaop : public Media::ProtocolNetwork, public IRaopAudioResumer, public IRaopResendReceiver
{
private:
    static const TUint kResendTimeoutMs = 80;   // Taken from previous codebase.
public:
    ProtocolRaop(Environment& aEnv, Media::TrackFactory& aTrackFactory, IRaopVolumeEnabler& aVolume, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId);
    ~ProtocolRaop();
    TUint SendFlush(TUint aSeq, TUint aTime);
private: // from Protocol
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream);
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private: // from IRaopAudioResumer
    void AudioResuming() override;
private: // from IRaopResendReceiver
    void ReceiveResend(const RtpPacketRaop& aPacket) override;
private:
    void StartStream();
    void OutputAudio(const Brx& aPacket);
    void OutputContainer(const Brx& aFmtp);
    void DoInterrupt();
    void WaitForChangeInput();
    void InputChanged();
    void TimerFired();
private:
    static const TUint kMaxReadBufferBytes = 1500;
    // FIXME - start latency can be retrieved from rtptime field of RTSP RECORD
    // packet (although it is always 2 seconds for Airplay streams)
    static const TUint kDelayJiffies = Media::Jiffies::kPerSecond*2; // expect 2s of buffering
    Media::TrackFactory& iTrackFactory;
    TBool iVolumeEnabled;
    IRaopVolumeEnabler& iVolume;
    IRaopDiscovery& iDiscovery;
    UdpServerManager& iServerManager;
    RtpPacketRaop iAudioPacket;
    Bws<RaopAudioServer::kMaxPacketBytes> iAudioDecrypted;
    RaopAudioDecryptor iAudioDecryptor;
    RaopAudioServer iAudioServer;
    RaopControl iControlServer;
    Media::SupplyAggregatorBytes* iSupply;
    Uri iUri;

    Bws<kMaxReadBufferBytes> iResentData;

    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TUint iStreamId;
    TUint iFlushSeq;
    TUint iFlushTime;
    TUint iNextFlushId;
    TBool iActive;
    TBool iWaiting;
    TBool iResumePending;
    TBool iStreamStart;
    TBool iStopped;
    Mutex iLockRaop;
    Semaphore iSem;
    Semaphore iSemInputChanged;
    Timer* iTimerResend;
    TUint iResendSeqNext;
    TUint iResendCount;
    Semaphore iSemResend;
};

};  // namespace Av
};  // namespace OpenHome

#endif  // HEADER_PROTOCOL_RAOP
