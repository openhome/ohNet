#ifndef HEADER_PIPELINE_RAOP
#define HEADER_PIPELINE_RAOP

#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Network.h>
//#include <Linn/Standard.h>
//#include <Linn/Control/IProtocol.h>
//#include <Linn/Network/Network.h>
//#include <Linn/Network/MdnsPlatform.h>
//#include <vector>
//#include <Linn/Control/Http/Http.h>
//#include <Linn/Control/Rtsp/Rtsp.h>
//#include <Linn/Media/SourcePairplay.h>
#include  <openssl/rsa.h>
//#include  <openssl/evp.h>
#include  <openssl/aes.h>


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
    static const TUint kPortRaopDiscovery = 5048;//5000;
    // aMacAddr in hex of form 001122334455
    RaopDevice(Net::DvStack& aDvStackconst, const Brx& aName, TIpAddress aIpAddr, const Brx& aMacAddr);
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
};

class ProtocolRaop;

class RaopDiscovery : public SocketTcpSession
{
    static const TUint kMaxReadBufferBytes = 12000;
    static const TUint kMaxWriteBufferBytes = 4000;

public:
    //RaopDiscovery(ProtocolRaop& aProtocolRaop, SourcePairplay& aPairplaySource, Volume& aVolume, RaopDevice& aRaopDevice, TUint aInstance);
    RaopDiscovery(Environment& aEnv, ProtocolRaop& aProtocolRaop, RaopDevice& aRaopDevice, TUint aInstance);
    ~RaopDiscovery();
    const Brx &Aeskey();
    const Brx &Aesiv();
    const Brx &Fmtp();
    TBool Active();
    void KeepAlive();
    void Deactivate();
    TUint AesSid();
    void Close();
private: // from SocketTcpSession
    void Run();
private:
    void WriteSeq(TUint aCSeq);
    //void WriteFply(TUint aLen, Brn aData);
    void WriteFply(Brn aData);
    void ReadSdp(ISdpHandler& aSdpHandler);
    void GenerateAppleResponse(const Brx& aChallenge);
    void DecryptAeskey();
    void GetRsa();
    void DeactivateCallback();
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
    ProtocolRaop& iProtocolRaop;
    //SourcePairplay& iPairplaySource;
    //Volume& iVolume;
    RaopDevice& iRaopDevice;
    TUint iInstance;
    TBool iActive;
    Timer* iDeactivateTimer;
};


} // namespace Media
} // namespace OpenHome


#endif // HEADER_PIPELINE_RAOP
