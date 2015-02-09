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

class RaopAudio
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
public:
    RaopAudio(SocketUdpServer& aServer);
    ~RaopAudio();
    void Initialise(const Brx &aAeskey, const Brx &aAesiv);
    TUint16 ReadPacket();
    void DecodePacket(TUint aSenderSkew, TUint aLatency);
    void DecodePacket(TUint aSenderSkew, TUint aLatency, Brx& aPacket);
    void DoInterrupt();
    void Reset();
    Brn Audio();
    TBool First() const;
    void SetMute();
private:
    SocketUdpServer& iServer;
    Bws<kMaxReadBufferBytes> iDataBuffer;
    Bws<kMaxReadBufferBytes> iAudio;
    TBool iFirst;
    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TBool iInitId;
    TUint32 iId;
    TBool iInterrupted;
};

class RaopControl
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
    static const TUint kPriority = kPriorityNormal-1;
    static const TUint kSessionStackBytes = 10 * 1024;
    static const TUint kInvalidServerPort = 0;
public:
    RaopControl(Environment& aEnv, SocketUdpServer& aServer);
    ~RaopControl();
    void DoInterrupt();
    void Reset(TUint aClientPort);
    void Time(TUint& aSenderSkew, TUint& aLatency);
    void RequestResend(TUint aPacketId, TUint aPackets);
    void GetResentData(Bwx& aData, TUint16 aCount);
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

// NOTE: there are three channels to monitor:
// - Audio
// - Control
// - Timing
// However, the timing channel was never monitored in the previous codebase,
// so no RaopTiming class exists here.
class ProtocolRaop : public Media::ProtocolNetwork
{
public:
    ProtocolRaop(Environment& aEnv, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId);
    ~ProtocolRaop();
    TBool Active();
    void Deactivate();
    void Close();
    TUint SendFlush();
public:
    void NotifySessionStart(TUint aControlPort, TUint aTimingPort);
    void NotifySessionEnd();
    void NotifySessionWait();
private: // from Protocol
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream);
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private:
    void StartStream();
    void OutputAudio(const Brn &aPacket, TBool aFirst);
    void OutputContainer(const Brn &aFmtp);
    void DoInterrupt();
private:
    static const TUint kMaxReadBufferBytes = 1500;
    // FIXME - start latency can be retrieved from rtptime field of RTSP RECORD
    // packet (although it is always 2 seconds for Airplay streams)
    static const TUint kDelayJiffies = Media::Jiffies::kPerSecond*2; // expect 2s of buffering

    IRaopDiscovery& iDiscovery;
    UdpServerManager& iServerManager;
    RaopAudio iRaopAudio;
    RaopControl iRaopControl;
    Media::SupplyAggregatorBytes* iSupply;

    Bws<kMaxReadBufferBytes> iResentData;

    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TUint iStreamId;
    TUint iNextFlushId;
    TBool iActive;
    TBool iWaiting;
    TBool iResumePending;
    TBool iStopped;
    Mutex iLockRaop;
    Semaphore iSem;
};

};  // namespace Av
};  // namespace OpenHome

#endif  // HEADER_PROTOCOL_RAOP
