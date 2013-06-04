#ifndef HEADER_PIPELINE_PROTOCOL_RAOP
#define HEADER_PIPELINE_PROTOCOL_RAOP

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/Raop.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>

//#include <openssl/rsa.h>

namespace OpenHome {
namespace Media {


//class ProtocolRaop;

class RaopAudio
{
private:
    static const TUint kMaxReadBufferBytes = 2000;
public:
    //RaopAudio(TUint aPort, ProtocolRaop& aProtocol);
    RaopAudio(Environment& aEnv, TUint aPort);
    ~RaopAudio();
    void Initialise(const Brx &aAeskey, const Brx &aAesiv);
    TUint16 ReadPacket();
    void DecodePacket(TUint aSenderSkew, TUint aLatency);
    void DecodePacket(TUint aSenderSkew, TUint aLatency, Brn& aPacket);
    void DoInterrupt();
    void Reset();
    Brn Audio();
    void SetMute();
private:
    TUint iPort;
    SocketUdp iSocket;
    UdpReader iSocketReader;
    Srs<kMaxReadBufferBytes> iReaderBuffer;
    Brn iDataBuffer;
    Bws<kMaxReadBufferBytes> iAudio;
    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    TBool iInitId;
    TUint32 iId;
    TBool iInterrupted;
    //ProtocolRaop& iProtocol;
};

class RaopControl
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
    static const TUint kPriority = kPriorityNormal-1;
    static const TUint kSessionStackBytes = 10 * 1024;
public:
    //RaopControl(TUint aPort, I2sDriver& aI2sDriver);
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
    SocketUdp iSocket;
    UdpReader iSocketReader;
    //UdpWriter iSocketWriter;
    Srs<kMaxReadBufferBytes> iReceive;
    Bws<kMaxReadBufferBytes> iResentData;
    ThreadFunctor* iThreadControl;
    TUint iSenderSkew;
    TUint iLatency;
    Mutex iMutex;
    Mutex iMutexRx;
    Semaphore iSemaResend;
    TUint iResend;
    //I2sDriver& iI2sDriver;
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
    ProtocolRaop(Environment& aEnv, Net::DvStack& aDvStack);
    //ProtocolRaop(ProtocolManager& aManager, I2sDriver& aI2sDriver, SourcePairplay& aPairplaySource, Volume& aVolume);
    ~ProtocolRaop();
public:
    //virtual void Stream();
    //void DoInterrupt();
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
    static const TUint kPriority = kPriorityNormal;
    static const TUint kSessionStackBytes = 10 * 1024;

    SocketTcpServer* iRaopDiscoveryServer;

    RaopDiscovery* iRaopDiscoverySession1;
    RaopDiscovery* iRaopDiscoverySession2;

    RaopAudio iRaopAudio;
    RaopControl iRaopControl;
    //RaopTiming iRaopTiming;

    Bws<kMaxReadBufferBytes> iResentData;

    Bws<sizeof(AES_KEY)> iAeskey;
    Bws<16> iAesiv;
    //SourcePairplay& iPairplaySource;
    RaopDevice* iRaopDevice;
    Uri iUri;
    TUint iNextFlushId;
};

class RaopDataHeader
{
public:
    RaopDataHeader(Brn& aRawData, TUint aSenderSkew, TUint aLatency);
    RaopDataHeader(Brn& aBinData);
    TUint SenderSkew() {return iSenderSkew;}
    TUint Latency() {return iLatency;}
    TUint16 Seqno() {return iSeqno;}
    TUint16 Bytes() {return iBytes;}
    TUint32 Timestamp() {return iTimestamp;}
    TBool Start() {return iStart;}
    TBool Mute() {return iMute;}
    void SetMute() {iMute = true;}
private:
    TUint   iSenderSkew;
    TUint   iLatency;
    TUint16 iSeqno;
    TUint16 iBytes;
    TUint32 iTimestamp;
    TBool iStart;
    TBool iMute;
};

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_RAOP
