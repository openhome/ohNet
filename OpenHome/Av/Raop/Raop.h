#ifndef HEADER_PIPELINE_RAOP
#define HEADER_PIPELINE_RAOP

#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Network.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

EXCEPTION(RaopNoActiveSession);

namespace OpenHome {
    class IPowerManager;
namespace Av {

class IRaopObserver
{
public:
    virtual void NotifySessionStart(TUint aControlPort, TUint aTimingPort) = 0;
    virtual void NotifySessionEnd() = 0;
    virtual void NotifySessionWait() = 0;
    virtual ~IRaopObserver() {}
};

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

class HeaderRtspTransport : public HttpHeader
{
public:
    static const Brn kControlPortStr;
    static const Brn kTimingPortStr;
public:
    TUint ControlPort() const;
    TUint TimingPort() const;
    virtual void Reset();
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    static TUint ParsePort(Brx& aData);
private:
    TUint iControlPort;
    TUint iTimingPort;
};

class RaopDevice
{
    static const TUint kMaxNameBytes = 100;
    static const TUint kMacAddrBytes = 12;
public:
    // aMacAddr in hex of form 001122334455
    RaopDevice(Net::DvStack& aDvStack, TUint aDiscoveryPort, const TChar* aHost, const TChar* aFriendlyName, TIpAddress aIpAddr, const Brx& aMacAddr);
    void SetEndpoint(const Endpoint& aEndpoint);
    void Register();
    void Deregister();
    const Endpoint& GetEndpoint() const;
    const Brx& MacAddress() const;
    void MacAddressOctets(TByte (&aOctets)[6]) const;
private:
    Net::IMdnsProvider& iProvider;
    TUint iHandleRaop;
    Bws<kMaxNameBytes> iName;
    Endpoint iEndpoint;
    const Bws<kMacAddrBytes> iMacAddress;
    TBool iRegistered;
    Mutex iLock;
};

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
    virtual void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming) = 0;
    virtual void AddObserver(IRaopObserver& aObserver) = 0;
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
    void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming);
    void AddObserver(IRaopObserver& aObserver);
private:
    void WriteSeq(TUint aCSeq);
    void WriteFply(Brn aData);
    void ReadSdp(Media::ISdpHandler& aSdpHandler);
    void GenerateAppleResponse(const Brx& aChallenge);
    void DecryptAeskey();
    void GetRsa();
    void DeactivateCallback();
private:
    static const TUint kMaxPortNumBytes = 5;
    Srs<kMaxReadBufferBytes>* iReaderBuffer;
    Sws<kMaxWriteBufferBytes>* iWriterBuffer;
    WriterAscii* iWriterAscii;
    ReaderHttpRequest* iReaderRequest;
    Media::WriterRtspRequest* iWriterRequest;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderContentType iHeaderContentType;
    HeaderAppleChallenge iHeaderAppleChallenge;
    HeaderRtspTransport iHeaderRtspTransport;
    HeaderCSeq iHeaderCSeq;
    Media::SdpInfo iSdpInfo;
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
    TUint iAudioPort;
    TUint iControlPort;
    TUint iTimingPort;
    TUint iClientControlPort;
    TUint iClientTimingPort;
};

class RaopDiscovery : public IRaopDiscovery, private Av::IRaopObserver, private INonCopyable
{
public:
    RaopDiscovery(Environment& aEnv, Net::DvStack& aDvStack, IPowerManager& aPowerManager, const TChar* aHostName, const TChar* aFriendlyName, const Brx& aMacAddr);
    virtual ~RaopDiscovery();
public: // from IRaopDiscovery
    const Brx &Aeskey();
    const Brx &Aesiv();
    const Brx &Fmtp();
    TBool Active();
    void Deactivate();
    void Enable();
    void Disable();
    void KeepAlive();
    TUint AesSid();
    void Close();
    void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming);
    void AddObserver(IRaopObserver& aObserver);
public: // from IRaopObserver
    void NotifySessionStart(TUint aControlPort, TUint aTimingPort);
    void NotifySessionEnd();
    void NotifySessionWait();
private:
    RaopDiscoverySession& ActiveSession();
    void HandleInterfaceChange();
    void PowerDown();
private:
    static const TUint kPriority = kPriorityNormal;
    static const TUint kSessionStackBytes = 10 * 1024;
    Environment& iEnv;
    std::vector<Av::IRaopObserver*> iObservers;
    RaopDevice* iRaopDevice;
    SocketTcpServer* iRaopDiscoveryServer;
    RaopDiscoverySession* iRaopDiscoverySession1;
    RaopDiscoverySession* iRaopDiscoverySession2;
    TUint iCurrentAdapterChangeListenerId;
    TUint iSubnetListChangeListenerId;
    Mutex iObserversLock;
};


} // namespace Av
} // namespace OpenHome


#endif // HEADER_PIPELINE_RAOP