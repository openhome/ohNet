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

class IRaopAudioResumer
{
public:
    virtual void AudioResuming() = 0;
    virtual ~IRaopAudioResumer() {}
};

class RaopAudio
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
public:
    RaopAudio(SocketUdpServer& aServer);
    ~RaopAudio();
    void Initialise(const Brx& aAeskey, const Brx& aAesiv);
    TUint ReadPacket();
    void DecodePacket();
    void DecodePacket(const Brx& aPacket);  // FIXME - remove one of these DecodePacket() calls - or, even better, move out to an AudioPacket object.
    void DoInterrupt();
    void Reset();
    const Brx& Audio() const;   // FIXME - remove this?
private:
    SocketUdpServer& iServer;
    Bws<kMaxReadBufferBytes> iDataBuffer;
    Bws<kMaxReadBufferBytes> iAudio;
    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TBool iInitId;
    TUint iId;
    TBool iInterrupted;
};

class RaopControl
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
    RaopControl(Environment& aEnv, SocketUdpServer& aServer, IRaopAudioResumer& aAudioResumer);
    ~RaopControl();
    void DoInterrupt();
    void Reset(TUint aClientPort);
    void Time(TUint& aSenderSkew, TUint& aLatency); // FIXME - do this without output params?
    void RequestResend(TUint aPacketId, TUint aPackets);
    void GetResentData(Bwx& aData, TUint aCount);
    void LockRx();
    void UnlockRx();
private:
    void Run();
    void TimerExpired();
private:
    Endpoint iEndpoint;
    TUint iClientPort;
    SocketUdpServer& iServer;
    Srs<kMaxReadBufferBytes> iReceive;
    Bws<kMaxReadBufferBytes> iResentData;
    Bws<kMaxReadBufferBytes> iPacket;
    IRaopAudioResumer& iAudioResumer;
    ThreadFunctor* iThreadControl;
    TUint iSenderSkew;
    TUint iLatency;
    Mutex iMutex;
    Mutex iMutexRx;
    Semaphore iSemaResend;
    TUint iResend;
    Timer* iTimerExpiry;
    TBool iExit;
};

class IRaopVolumeEnabler;

// NOTE: there are three channels to monitor:
// - Audio
// - Control
// - Timing
// However, the timing channel was never monitored in the previous codebase,
// so no RaopTiming class exists here.
class ProtocolRaop : public Media::ProtocolNetwork, public IRaopAudioResumer
{
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
private:
    void StartStream();
    void OutputAudio(const Brx& aPacket);
    void OutputContainer(const Brx& aFmtp);
    void DoInterrupt();
    void WaitForChangeInput();
    void InputChanged();
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
    RaopAudio iRaopAudio;
    RaopControl iRaopControl;
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
};

class RtpHeaderFixed
{
public:
    static const TUint kHeaderBytes = 12;
public:
    RtpHeaderFixed(const Brx& aRtpHeader);
public:
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
public:
    RtpPacketRaop(const Brx& aRtpPacket);
    const RtpHeaderFixed& Header() const;
    const Brx& Payload() const;
private:
    RtpHeaderFixed iHeader;
    Brn iPayload;
};

class RtpPacket
{
private:
    static const TUint kMinHeaderBytes = 12;
public:
    RtpPacket(const Brx& aRtpPacket);
    const RtpHeaderFixed& Header() const;
    const Brx& Payload() const;
private:
    RtpHeaderFixed iHeader;
    std::vector<TUint> iCsrc;
    TUint iHeaderExtensionProfile;
    Brn iHeaderExtension;
    Brn iPayload;
};

};  // namespace Av
};  // namespace OpenHome

#endif  // HEADER_PROTOCOL_RAOP
