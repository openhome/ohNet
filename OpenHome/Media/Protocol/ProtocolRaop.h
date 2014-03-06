#ifndef HEADER_PIPELINE_PROTOCOL_RAOP
#define HEADER_PIPELINE_PROTOCOL_RAOP

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

namespace OpenHome {
    class Timer;
namespace Media {

class SocketUdpServer;

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
    void SetMute();
private:
    SocketUdpServer& iServer;
    Bws<kMaxReadBufferBytes> iDataBuffer;
    Bws<kMaxReadBufferBytes> iAudio;
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
public:
    RaopControl(Environment& aEnv, SocketUdpServer& aServer);
    ~RaopControl();
    void DoInterrupt();
    void Reset();
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
class ProtocolRaop : public ProtocolNetwork
{
public:
    ProtocolRaop(Environment& aEnv, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId, TUint aTimingId);
    ~ProtocolRaop();
public:
    TBool Active();
    void Deactivate();
    void Close();
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
private: // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    void StartStream();
    void OutputAudio(const Brn &aPacket);
    void OutputContainer(const Brn &aFmtp);
    void DoInterrupt();
private:
    static const TUint kMaxReadBufferBytes = 1500;

    IRaopDiscovery& iDiscovery;
    UdpServerManager& iServerManager;
    RaopAudio iRaopAudio;
    RaopControl iRaopControl;

    Bws<kMaxReadBufferBytes> iResentData;

    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TUint iStreamId;
    TUint iNextFlushId;
    TBool iStopped;
    Mutex iLockRaop;
};

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_RAOP
