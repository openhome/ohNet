#pragma once

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/SupplyAggregator.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

EXCEPTION(InvalidRaopPacket)

namespace OpenHome {
    class Timer;
namespace Av {

class SocketUdpServer;
class UdpServerManager;
class IRaopDiscovery;

/**
 * RAOP appears to use a version of the RTP header that does not conform to
 * RFC 3350: https://www.ietf.org/rfc/rfc3550.txt.
 *
 * It uses only the first 4 bytes of the fixed-size header and the extension
 * bit can be set without providing an extension header.
 */
class RtpHeaderRaop : private INonCopyable
{
public:
    static const TUint kBytes = 4;
    static const TUint kVersion = 2;
public:
    RtpHeaderRaop(TBool aPadding, TBool aExtension, TUint aCsrcCount, TBool aMarker, TUint aPayloadType, TUint aSeqNumber);
    RtpHeaderRaop(const Brx& aRtpHeader);
    void Write(IWriter& aWriter) const;
    TBool Padding() const;
    TBool Extension() const;
    TUint CsrcCount() const;
    TBool Marker() const;
    TUint Type() const;
    TUint Seq() const;
private:
    TBool iPadding;
    TBool iExtension;
    TUint iCsrcCount;
    TBool iMarker;
    TUint iPayloadType;
    TUint iSequenceNumber;
};

class RtpPacketRaop
{
public:
    // Assume the following:
    // Max Ethernet frame size: 1500 bytes.
    // IPv4 header:             20 bytes.
    // UDP header:              8 bytes.
    // So, 1500-20-8 = 1472 RTP bytes max.
    static const TUint kMaxPacketBytes = 1472;
public:
    RtpPacketRaop(const Brx& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
private:
    const RtpHeaderRaop iHeader;
    const Brn iPayload;
};

class RaopPacketAudio : private INonCopyable
{
public:
    static const TUint kType = 0x60;
private:
    static const TUint kAudioSpecificHeaderBytes = 8;
public:
    RaopPacketAudio(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
    TUint Timestamp() const;
    TUint Ssrc() const;
private:
    const RtpPacketRaop& iPacket;
    const Brn iPayload;
    TUint iTimestamp;
    TUint iSsrc;
};

class RaopPacketSync : private INonCopyable
{
public:
    static const TUint kType = 0x54;
private:
    static const TUint kSyncSpecificHeaderBytes = 16;
public:
    RaopPacketSync(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
    TUint RtpTimestampMinusLatency() const;
    TUint NtpTimestampSecs() const;
    TUint NtpTimestampFract() const;
    TUint RtpTimestamp() const;
private:
    const RtpPacketRaop& iPacket;
    const Brn iPayload;
    TUint iRtpTimestampMinusLatency;
    TUint iNtpTimestampSecs;
    TUint iNtpTimestampFract;
    TUint iRtpTimestamp;
};

class RaopPacketResendResponse
{
public:
    static const TUint kType = 0x56;
public:
    RaopPacketResendResponse(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const RaopPacketAudio& AudioPacket() const;
private:
    const RtpPacketRaop& iPacketOuter;
    const RtpPacketRaop iPacketInner;
    const RaopPacketAudio iAudioPacket;
};

class RaopPacketResendRequest
{
public:
    static const TUint kType = 0x55;
    static const TUint kBytes = 8;
public:
    RaopPacketResendRequest(TUint aSeqStart, TUint aCount);
    void Write(IWriter& aWriter) const;
private:
    const RtpHeaderRaop iHeader;
    const TUint iSeqStart;
    const TUint iCount;
};

class RaopAudioServer : private INonCopyable
{
public:
    RaopAudioServer(SocketUdpServer& aServer);
    ~RaopAudioServer();
    void ReadPacket(Bwx& aBuf);
    void DoInterrupt();
    void Reset();
private:
    SocketUdpServer& iServer;
    TBool iInterrupted;
};

// FIXME - this class currently writes out the packet length at the start of decoded audio.
// That shouldn't be a responsibility of a generic decryptor.
// Maybe have a chain of elements that write into the same buffer (i.e., one element to write the packet length at the start, then pass onto decryptor to decrypt the audio into the buffer).
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

class IRaopTimer
{
public:
    virtual void Start(Functor aFunctor, TUint aFireInMs) = 0;
    virtual void Cancel() = 0;
    virtual ~IRaopTimer() {}
};

class RaopTimer : public IRaopTimer
{
public:
    RaopTimer(Environment& aEnv, const TChar* aId);
public: // from IRaopTimer
    void Start(Functor aFunctor, TUint aFireInMs) override;
    void Cancel() override;
private:
    void TimerFired();
private:
    Timer iTimer;
    Functor iFunctor;
};

/**
 * Interface for receiving individual resent RAOP audio packets.
 */
class IRaopResendReceiver
{
public:
    virtual void ResendReceive(const RaopPacketAudio& aPacket) = 0;
    virtual ~IRaopResendReceiver() {}
};

/**
 * Interface for receiving a block of resent RAOP audio packets.
 *
 * Implementor is notified of each packet that arrives via ResendReceive() and
 * should perform some basic sequence number checking (e.g., to identify if an
 * expected packet in the resend sequence didn't arrive and notify pipeline of a discontinuity in audio).
 *
 * When a resend sequence is complete (because all packets arrived or some/all
 * packet resends timed out), ResendComplete() is called. Implementor should
 * again perform some basic sequence number checking in case part or all of the
 * resend failed.
 */
class IRaopResendBlockObserver
{
public:
    virtual void ResendReceive(const RaopPacketAudio& aPacket) = 0;
    //virtual void ResendDropped(TUint aPacketId) = 0;
    virtual void ResendComplete() = 0;
    virtual ~IRaopResendBlockObserver() {}
};

class IRaopResendRequester
{
public:
    virtual void RequestResend(TUint aSeqStart, TUint aCount) = 0;
    virtual ~IRaopResendRequester() {}
};

class RaopResendHandler : public IRaopResendRequester, public IRaopResendReceiver
{
private:
    static const TUint kTimeoutMs = 80; // Taken from previous codebase.
public:
    RaopResendHandler(IRaopResendRequester& aRequester, IRaopTimer& aTimer);
    void RegisterObserver(IRaopResendBlockObserver& aObserver);
    void Interrupt();
public: // from IRaopResendRequester
    void RequestResend(TUint aSeqStart, TUint aCount) override;
public: // from IRaopResendReceiver
    void ResendReceive(const RaopPacketAudio& aPacket) override;
private:
    void TimerFired();
private:
    IRaopResendRequester& iRequester;
    IRaopResendBlockObserver* iObserver;
    IRaopTimer& iTimer;
    TUint iSeqNext;
    TUint iCount;
    Mutex iLock;
};

class RaopControlServer : public IRaopResendRequester
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
    RaopControlServer(SocketUdpServer& aServer);
    ~RaopControlServer();
    void RegisterResendObserver(IRaopResendReceiver& aReceiver);
    void DoInterrupt();
    void Reset(TUint aClientPort);
    TUint Latency() const;  // Returns latency in samples.
public: // from IRaopResendRequester
    void RequestResend(TUint aSeqStart, TUint aCount) override;
private:
    void Run();
private:
    Endpoint iEndpoint;
    TUint iClientPort;
    SocketUdpServer& iServer;
    Bws<kMaxReadBufferBytes> iPacket;
    ThreadFunctor* iThread;
    IRaopResendReceiver* iResendReceiver;
    TUint iLatency;
    mutable Mutex iLock;
    TBool iExit;
};

class IRaopVolumeEnabler;

// NOTE: there are three channels to monitor:
// - Audio
// - Control
// - Timing
// However, the timing channel was never monitored in the previous codebase,
// so no RaopTiming class exists here.
class ProtocolRaop : public Media::ProtocolNetwork, public IRaopResendBlockObserver
{
private:
    static const TUint kSampleRate = 44100;     // Always 44.1KHz. Can get this from fmtp field.
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
private: // from IRaopResendBlockObserver
    void ResendReceive(const RaopPacketAudio& aPacket) override;
    void ResendComplete() override;
private:
    void Reset();
    void Start();
    void StartStream();
    void UpdateSessionId(TUint aSessionId);
    TBool IsValidSession(TUint aSessionId) const;
    TBool ShouldFlush(TUint aSeq, TUint aTimestamp) const;
    void OutputAudio(const Brx& aAudio);
    void OutputDiscontinuity();
    void OutputContainer(const Brx& aFmtp);
    void DoInterrupt();
    void WaitForDrain();
    void InputChanged();
    void ResendTimerFired();
    static TUint Delay(TUint aSamples);
private:
    Media::TrackFactory& iTrackFactory;
    TBool iVolumeEnabled;
    IRaopVolumeEnabler& iVolume;
    IRaopDiscovery& iDiscovery;
    UdpServerManager& iServerManager;
    Bws<RtpPacketRaop::kMaxPacketBytes> iPacketBuf;
    Bws<RtpPacketRaop::kMaxPacketBytes> iAudioDecrypted;
    RaopAudioDecryptor iAudioDecryptor;
    RaopAudioServer iAudioServer;
    RaopControlServer iControlServer;
    Media::SupplyAggregatorBytes* iSupply;
    Uri iUri;

    TUint iSessionId;
    TUint iStreamId;
    TUint iLatency;
    TUint iFlushSeq;
    TUint iFlushTime;
    TUint iNextFlushId;
    TBool iActive;
    TBool iWaiting;
    TBool iResumePending;
    TBool iStopped;
    mutable Mutex iLockRaop;
    Semaphore iSem;
    Semaphore iSemDrain;

    TUint iSeqExpected;
    RaopTimer iResendTimer;
    RaopResendHandler iResendHandler;
    Semaphore iSemResend;
};

};  // namespace Av
};  // namespace OpenHome

