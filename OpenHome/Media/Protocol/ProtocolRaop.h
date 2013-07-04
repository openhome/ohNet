#ifndef HEADER_PIPELINE_PROTOCOL_RAOP
#define HEADER_PIPELINE_PROTOCOL_RAOP

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/Raop.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class RaopAudio
{
private:
    static const TUint kMaxReadBufferBytes = 2000;
public:
    RaopAudio(Environment& aEnv, TUint aPort);
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
    TUint iPort;
    SocketUdp iSocket;
    UdpReader iSocketReader;
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
    RaopControl(Environment& aEnv, TUint aPort);
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
    TUint iPort;
    Endpoint iEndpoint;
    SocketUdp iSocket;
    UdpReader iSocketReader;
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
};

//class RaopTiming
//{
//    static const TUint kMaxReadBufferBytes = 1000;
//public:
//    RaopTiming(TUint aPort);
//private:
//    Linn::Network::UdpServer iUdpServer;
//    Bws<kMaxReadBufferBytes> iDataBuffer;
//};

class ProtocolRaop : public ProtocolNetwork
{
public:
    ProtocolRaop(Environment& aEnv, Net::DvStack& aDvStack, TUint aDiscoveryPort);
    ~ProtocolRaop();
public:
    void DoInterrupt();
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
public:
    static const TUint kPortAudio = 60400;
    static const TUint kPortControl = 60401;
    //static const TUint kPortTiming = 60402;
private:
    static const TUint kMaxReadBufferBytes = 1500;

    //IRaopDiscovery& iDiscovery;    // FIXME - switch to this when finished refactoring
    IRaopDiscovery* iDiscovery;
    RaopAudio iRaopAudio;
    RaopControl iRaopControl;
    //RaopTiming iRaopTiming;

    Bws<kMaxReadBufferBytes> iResentData;

    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TUint iStreamId;
    TUint iNextFlushId;
    TBool iStopped;
};

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_RAOP
