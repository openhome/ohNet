#ifndef HEADER_PIPELINE_RAOP
#define HEADER_PIPELINE_RAOP

#include <OpenHome/Av/Raop/SourceRaop.h>
#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Network.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

EXCEPTION(RaopNoActiveSession);

namespace OpenHome {
namespace Media {

class HeaderCSeq : public IHttpHeader
{
    static const TUint kMaxCSeqBytes = 20;
public:
    TBool Received() const;
    TUint CSeq() const;
    virtual void Reset();
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    TUint iCSeq;
    TBool iReceived;
};

class HeaderAppleChallenge : public IHttpHeader
{
    static const TUint kMaxChallengeBytes = 256;
public:
    TBool Received() const;
    const Brx& Challenge() const;
    virtual void Reset();
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    Bws<kMaxChallengeBytes> iChallenge;
    TBool iReceived;
};

class RaopDevice
{
    static const TUint kMaxNameBytes = 100;
    static const TUint kMacAddrBytes = 12;
public:
    // aMacAddr in hex of form 001122334455
    RaopDevice(Net::DvStack& aDvStack, TUint aDiscoveryPort, const Brx& aName, TIpAddress aIpAddr, const Brx& aMacAddr);
    void Register();
    void Deregister();
    const Endpoint& GetEndpoint() const;
    const Brx& MacAddress() const;
    void MacAddressOctets(TByte (&aOctets)[6]) const;
private:
    Net::IMdnsProvider& iProvider;
    TUint iHandleRaop;
    Bws<kMaxNameBytes> iName;
    TUint iPort;
    Endpoint iEndpoint;
    const Bws<kMacAddrBytes> iMacAddress;
    TBool iRegistered;
};

class ProtocolRaop;

class IRaopDiscovery
{
public:
    virtual TBool Active() = 0;
    virtual void Deactivate() = 0;
    virtual TUint AesSid() = 0;
    virtual const Brx& Aeskey() = 0;
    virtual const Brx& Aesiv() = 0;
    virtual const Brx& Fmtp() = 0;
    virtual void KeepAlive() = 0;
    virtual void Close() = 0;
};

class RaopDiscovery;

class RaopDiscoverySession : public SocketTcpSession, public IRaopDiscovery
{
    static const TUint kMaxReadBufferBytes = 12000;
    static const TUint kMaxWriteBufferBytes = 4000;

public:
    RaopDiscoverySession(Environment& aEnv, RaopDiscovery& aDiscovery, RaopDevice& aRaopDevice, TUint aInstance);
    ~RaopDiscoverySession();
private: // from SocketTcpSession
    void Run();
public: // from IRaopDiscovery
    const Brx &Aeskey();
    const Brx &Aesiv();
    const Brx &Fmtp();
    TBool Active();
    void KeepAlive();
    void Deactivate();
    TUint AesSid();
    void Close();
private:
    void WriteSeq(TUint aCSeq);
    void WriteFply(Brn aData);
    void ReadSdp(ISdpHandler& aSdpHandler);
    void GenerateAppleResponse(const Brx& aChallenge);
    void DecryptAeskey();
    void GetRsa();
    void DeactivateCallback();
private:
    Srs<kMaxReadBufferBytes>* iReaderBuffer;
    Sws<kMaxWriteBufferBytes>* iWriterBuffer;
    WriterAscii* iWriterAscii;
    ReaderHttpRequest* iReaderRequest;
    WriterRtspRequest* iWriterRequest;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderContentType iHeaderContentType;
    HeaderAppleChallenge iHeaderAppleChallenge;
    HeaderCSeq iHeaderCSeq;
    SdpInfo iSdpInfo;
    Bws<sizeof(AES_KEY)> iAeskey;
    TBool iAeskeyPresent;
    TUint iAesSid;
    RSA *iRsa;
    Bws<1024> iResponse;
    RaopDiscovery& iDiscovery;
    //Volume& iVolume;
    RaopDevice& iRaopDevice;
    TUint iInstance;
    TBool iActive;
    Timer* iDeactivateTimer;
    Semaphore iShutdownSem;
};

class RaopDiscovery : public IRaopDiscovery, private Av::IRaopObserver, private INonCopyable
{
public:
    RaopDiscovery(Environment& aEnv, Net::DvStack& aDvStack, Av::IRaopObserver& aObserver, const Brx& aDeviceName, TUint aDiscoveryPort);
    virtual ~RaopDiscovery();
public: // from IRaopDiscovery
    const Brx &Aeskey();
    const Brx &Aesiv();
    const Brx &Fmtp();
    TBool Active();
    void Deactivate();
    void KeepAlive();
    TUint AesSid();
    void Close();
public: // from IRaopObserver
    void NotifyStreamStart();
private:
    RaopDiscoverySession& ActiveSession();
private:
    static const TUint kPriority = kPriorityNormal;
    static const TUint kSessionStackBytes = 10 * 1024;

    Av::IRaopObserver& iRaopObserver;
    RaopDevice* iRaopDevice;
    SocketTcpServer* iRaopDiscoveryServer;
    RaopDiscoverySession* iRaopDiscoverySession1;
    RaopDiscoverySession* iRaopDiscoverySession2;
};


} // namespace Media
} // namespace OpenHome


#endif // HEADER_PIPELINE_RAOP
