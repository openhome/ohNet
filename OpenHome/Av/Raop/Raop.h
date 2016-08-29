#pragma once

#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/PowerManager.h>
#include <OpenHome/Av/VolumeManager.h>
#include <OpenHome/Media/Pipeline/Attenuator.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

EXCEPTION(RaopError);
EXCEPTION(RaopVolumeInvalid);

namespace OpenHome {
    class IPowerManager;
namespace Av {

class IRaopServerObserver
{
public:
    virtual void NotifySessionStart(const NetworkAdapter& aNif, TUint aControlPort, TUint aTimingPort) = 0;
    virtual void NotifySessionEnd(const NetworkAdapter& aNif) = 0;
    virtual void NotifySessionWait(const NetworkAdapter& aNif, TUint aSeq, TUint aTime) = 0;
    virtual ~IRaopServerObserver() {}
};

class IRaopObserver
{
public:
    virtual void NotifySessionStart(TUint aControlPort, TUint aTimingPort) = 0;
    virtual void NotifySessionEnd() = 0;
    virtual void NotifySessionWait(TUint aSeq, TUint aTime) = 0;
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

class HeaderRtpInfo : public HttpHeader
{
public:
    static const Brn kSeqStr;
    static const Brn kRtpTimeStr;
public:
    TUint Seq() const;
    TUint RtpTime() const;
    virtual void Reset();
private:
    virtual TBool Recognise(const Brx& aHeader);
    virtual void Process(const Brx& aValue);
private:
    static Brn ParameterValue(Brx& aData);
private:
    TUint iSeq;
    TUint iRtpTime;
};

class IFriendlyNameObservable;

class RaopDevice
{
public:
    static const TUint kMaxNameBytes = 100;
    static const TUint kMacAddrBytes = 12;
public:
    // aMacAddr in hex of form 001122334455
    RaopDevice(Net::DvStack& aDvStack, TUint aDiscoveryPort, IFriendlyNameObservable& aFriendlyNameObservable, TIpAddress aIpAddr, const Brx& aMacAddr);
    ~RaopDevice();
    void Register();
    void Deregister();
    const Endpoint& GetEndpoint() const;
    const Brx& MacAddress() const;
    void MacAddressOctets(TByte (&aOctets)[6]) const;
private:
    void DoRegister();
    void DoDeregister();
    void FriendlyNameUpdate(const Brx& aNewFriendlyName);
private:
    Net::IMdnsProvider& iProvider;
    TUint iHandleRaop;
    IFriendlyNameObservable& iFriendlyNameObservable;
    TUint iFriendlyNameId;
    Bws<kMaxNameBytes> iName;
    const Endpoint iEndpoint;
    const Bws<kMacAddrBytes> iMacAddress;
    TBool iRegistered;
    Mutex iLock;
};

class IRaopDiscovery
{
public:
    virtual TBool Active() = 0;
    virtual TUint AesSid() = 0;
    virtual const Brx& Aeskey() = 0;
    virtual const Brx& Aesiv() = 0;
    virtual const Brx& Fmtp() = 0;
    virtual void KeepAlive() = 0;
    virtual void Close() = 0;
    virtual void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming) = 0;
    virtual ~IRaopDiscovery() {}
};

class RaopDiscoveryServer;

class RaopDiscoverySession : public SocketTcpSession, public IRaopDiscovery
{
private:
    static const TUint kMaxReadBufferBytes = 12000;
    static const TUint kMaxWriteBufferBytes = 4000;
    static const unsigned char kRsaKeyPrivate[];
public:
    RaopDiscoverySession(Environment& aEnv, RaopDiscoveryServer& aDiscovery, RaopDevice& aRaopDevice, TUint aInstance, Media::IAttenuator& aAttenuator);
    ~RaopDiscoverySession();
    void Deactivate();
private: // from SocketTcpSession
    void Run() override;
public: // from IRaopDiscovery
    const Brx& Aeskey() override;
    const Brx& Aesiv() override;
    const Brx& Fmtp() override;
    TBool Active() override;
    void KeepAlive() override;
    TUint AesSid() override;
    void Close() override;
    void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming) override;
private:
    void WriteSeq(TUint aCSeq);
    void WriteFply(Brn aData);
    void ReadSdp(Media::ISdpHandler& aSdpHandler);
    void GenerateAppleResponse(const Brx& aChallenge);
    void DecryptAeskey();
    void DeactivateCallback();
private:
    static const TUint kMaxPortNumBytes = 5;
    Srx* iReaderBuffer;
    ReaderUntil* iReaderUntil;
    ReaderProtocol* iReaderProtocol;
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
    HeaderRtpInfo iHeaderRtpInfo;
    Media::SdpInfo iSdpInfo;
    Bws<sizeof(AES_KEY)> iAeskey;
    TBool iAeskeyPresent;
    TUint iAesSid;
    RSA *iRsa;
    Bws<1024> iResponse;
    RaopDiscoveryServer& iDiscovery;
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
    Media::IAttenuator& iAttenuator;
};

class RaopDiscoveryServer : public IRaopDiscovery, private IRaopObserver, private INonCopyable
{
public:
    RaopDiscoveryServer(Environment& aEnv, Net::DvStack& aDvStack, NetworkAdapter& aNif, IFriendlyNameObservable& aFriendlyNameObservable, const Brx& aMacAddr, Media::IAttenuator& aAttenuator);
    ~RaopDiscoveryServer();
    const NetworkAdapter& Adapter() const;
    void AddObserver(IRaopServerObserver& aObserver); // FIXME - can probably do away with this and just pass a single IRaopServerObserver in at construction (i.e., a ref to the RaopDiscovery class, as this will only call that)
    void PowerDown();
    void Enable();
    void Disable();
    void AddObserver(IRaopObserver& aObserver);
    void Deactivate();
public: // from IRaopDiscovery
    const Brx& Aeskey() override;
    const Brx& Aesiv() override;
    const Brx& Fmtp() override;
    TBool Active() override;
    void KeepAlive() override;
    TUint AesSid() override;
    void Close() override;
    void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming) override;
public: // from IRaopObserver
    void NotifySessionStart(TUint aControlPort, TUint aTimingPort) override;
    void NotifySessionEnd() override;
    void NotifySessionWait(TUint aSeq, TUint aTime) override;
private:
    RaopDiscoverySession& ActiveSession();
    void HandleInterfaceChange();
    TInt InterfaceIndex(const NetworkAdapter& aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList);
    static TBool NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2);
private:
    static const TUint kPriority = kPriorityNormal;
    static const TUint kSessionStackBytes = 10 * 1024;
    static const TChar* kAdapterCookie;
    Environment& iEnv;
    NetworkAdapter& iAdapter;
    std::vector<IRaopServerObserver*> iObservers;
    RaopDevice* iRaopDevice;
    SocketTcpServer* iRaopDiscoveryServer;
    RaopDiscoverySession* iRaopDiscoverySession1;
    RaopDiscoverySession* iRaopDiscoverySession2;
    Mutex iObserversLock;
};


/**
 * RAOP uses a TCP channel to discover device capabilities and control
 * streaming session (starting/stopping/flushing/etc.).
 *
 * This class creates a TCP server which contains two sessions. When a request
 * comes in, a TCP session's Run() method is called. That Run() method keeps
 * iterating in a loop while a streaming session is in progress, being queried
 * by the sender and having commands sent to it.
 *
 * Only one TCP session may be active at any time. There are two TCP sessions
 * to allow for an alternative sender (or, the same sender if there is a
 * network issue) to come in on the second session and disable the first
 * session.
 *
 * As the discovery sessions are held open in their Run() method, there is a
 * 10s keep-alive timeout implemented here, so that if no query is received
 * in that time period, the session is freed up for alternative connections.
 */
class RaopDiscovery : public IRaopDiscovery, public IPowerHandler, private IRaopServerObserver, public IVolumeScalerEnabler, private INonCopyable
{
public:
    static const TUint kVolMaxScaled = 256;
public:
    RaopDiscovery(Environment& aEnv, Net::DvStack& aDvStack, IPowerManager& aPowerManager, IFriendlyNameObservable& aFriendlyNameObservable, const Brx& aMacAddr, Media::IAttenuator& aAttenuator);
    ~RaopDiscovery();
    void AddObserver(IRaopObserver& aObserver);
public: // from IRaopDiscovery
    TBool Active() override;
    TUint AesSid() override;
    const Brx& Aeskey() override;
    const Brx& Aesiv() override;
    const Brx& Fmtp() override;
    void KeepAlive() override;
    void Close() override;
    void SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming) override;
public: // from IRaopObserver
    void NotifySessionStart(const NetworkAdapter& aNif, TUint aControlPort, TUint aTimingPort) override;
    void NotifySessionEnd(const NetworkAdapter& aNif) override;
    void NotifySessionWait(const NetworkAdapter& aNif, TUint aSeq, TUint aTime) override;
private: // from IPowerHandler
    void PowerUp() override;
    void PowerDown() override;
private:
    void HandleInterfaceChange();
    void AddAdapter(NetworkAdapter& aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList);
    static TBool NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2);
private:
    Environment& iEnv;
    Net::DvStack& iDvStack;
    const Bws<RaopDevice::kMaxNameBytes> iHostName;
    IFriendlyNameObservable& iFriendlyNameObservable;
    const Bws<RaopDevice::kMacAddrBytes> iMacAddr;
    std::vector<RaopDiscoveryServer*> iServers;
    std::vector<IRaopObserver*> iObservers;
    TUint iCurrentAdapterChangeListenerId;
    TUint iSubnetListChangeListenerId;
    RaopDiscoveryServer* iCurrent; // protected by iServersLock
    IPowerManagerObserver* iPowerObserver;
    Mutex iServersLock;
    Mutex iObserversLock;
    Media::IAttenuator& iAttenuator;
};

} // namespace Av
} // namespace OpenHome
