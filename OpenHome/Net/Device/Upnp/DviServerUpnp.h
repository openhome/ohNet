#ifndef HEADER_DVI_SERVER_UPNP
#define HEADER_DVI_SERVER_UPNP

#include <OpenHome/Types.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Subscription.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Net/Private/DviSubscription.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class IRedirector
{
public:
    virtual TBool RedirectUri(const Brx& aUri, Brn& aRedirectTo) = 0;
};
    
class HeaderSoapAction : public HttpHeader
{
public:
    const Brx& Domain() const;
    const Brx& Type() const;
    TUint Version() const;
    const Brx& Action() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Bwh iDomain;
    Brh iType;
    TUint iVersion;
    Brh iAction;
};

class HeaderCallback : public HttpHeader
{
public:
    const OpenHome::Endpoint& Endpoint() const;
    const Brx& Uri() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    OpenHome::Endpoint iEndpoint;
    Bwh iUri;
};

class HeaderAcceptLanguage : public HttpHeader
{
public:
    ~HeaderAcceptLanguage();
    const Brx& LanguageString() const;
    std::vector<char*>& LanguageList();
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    struct PrioritisedLanguage
    {
        char* iLanguage;
        TUint iPriority;
    };
private:
    void ClearLanguageList();
    TUint ParseQualityValue(const Brx& aBuf);
    void AddPrioritisedLanguage(std::vector<PrioritisedLanguage>& aList, PrioritisedLanguage& aLanguage);
private:
    static const TUint kMaxQuality = 1000;
    static const TUint kMinQuality = 0;
    static const TUint kMaxQualityChars = 5; // HTTP spec says quality scores have max 3 dec places
    Brh iLanguages;
    std::vector<char*> iLanguageList;
};

class SubscriptionDataUpnp : public IDviSubscriptionUserData
{
public:
    SubscriptionDataUpnp(const Endpoint& aSubscriber, const Brx& aSubscriberPath, const Http::EVersion aHttpVersion);
    const Endpoint& Subscriber() const;
    const Brx& SubscriberPath() const;
    const Http::EVersion HttpVersion() const;
    virtual const void* Data() const;
    virtual void Release();
private:
    ~SubscriptionDataUpnp() {}
private:
    Endpoint iSubscriber;
    Brh iSubscriberPath;
    Http::EVersion iHttpVersion;
};

class PropertyWriterUpnp : public PropertyWriter
{
public:
    static PropertyWriterUpnp* Create(DvStack& aDvStack, const Endpoint& aPublisher, const Endpoint& aSubscriber,
                                      const Brx& aSubscriberPath, const Http::EVersion aHttpVersion, const Brx& aSid, TUint aSequenceNumber);
private:
    PropertyWriterUpnp(DvStack& aDvStack);
    void Connect(const Endpoint& aSubscriber);
    void WriteHeaders(const Endpoint& aPublisher, const Brx& aSubscriberPath,
                      const Http::EVersion aHttpVersion, const Brx& aSid, TUint aSequenceNumber);
private: // IPropertyWriter
    ~PropertyWriterUpnp();
    void PropertyWriteEnd();
private:
    static const TUint kMaxRequestBytes = 12*1024;
    static const TUint kMaxResponseBytes = 128;
    static const TUint kReadTimeoutMs = 5 * 1000;
    DvStack& iDvStack;
    SocketTcpClient iSocket;
    Sws<kMaxRequestBytes>* iWriteBuffer;
    WriterHttpRequest* iWriterEvent;
    WriterHttpChunked* iWriterChunked;
};

class DvStack;

class PropertyWriterFactory : public IPropertyWriterFactory
{
public:
    PropertyWriterFactory(DvStack& aDvStack, TIpAddress aAdapter, TUint aPort);
    void SubscriptionAdded(DviSubscription& aSubscription);
    void Disable();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
    void NotifySubscriptionCreated(const Brx& aSid);
    void NotifySubscriptionDeleted(const Brx& aSid);
    void NotifySubscriptionExpired(const Brx& aSid);
private:
    ~PropertyWriterFactory();
    void AddRef();
    void RemoveRef();
private:
    TUint iRefCount;
    DvStack& iDvStack;
    TBool iEnabled;
    TIpAddress iAdapter;
    TUint iPort;
    typedef std::map<Brn,DviSubscription*,BufferCmp> SubscriptionMap;
    SubscriptionMap iSubscriptionMap;
    Mutex iSubscriptionMapLock;
};


class DviSessionUpnp : public SocketTcpSession, private IResourceWriter, private IDviInvocation
{
public:
    DviSessionUpnp(DvStack& aDvStack, TIpAddress aInterface, TUint aPort, IRedirector& aRedirector);
    ~DviSessionUpnp();
private:
    void Run();
    void Error(const HttpStatus& aStatus);
    void Get();
    void Post();
    void Subscribe();
    void Unsubscribe();
    void Renew();
    void ParseRequestUri(const Brx& aUrlTail, DviDevice** aDevice, DviService** aService);
    void WriteServerHeader(IWriterHttpHeader& aWriter);
    void InvocationReportErrorNoThrow(TUint aCode, const Brx& aDescription);
private: // IResourceWriter
    void WriteResourceBegin(TUint aTotalBytes, const TChar* aMimeType);
    void WriteResource(const TByte* aData, TUint aBytes);
    void WriteResourceEnd();
private: // IDviInvocation
    void Invoke();
    TUint Version() const;
    TIpAddress Adapter() const;
    const char* ResourceUriPrefix() const;
    Endpoint ClientEndpoint() const;
    Brhz ClientUserAgent() const;
    void InvocationReadStart();
    TBool InvocationReadBool(const TChar* aName);
    void InvocationReadString(const TChar* aName, Brhz& aString);
    TInt InvocationReadInt(const TChar* aName);
    TUint InvocationReadUint(const TChar* aName);
    void InvocationReadBinary(const TChar* aName, Brh& aData);
    void InvocationReadEnd();
    void InvocationReportError(TUint aCode, const Brx& aDescription);
    void InvocationWriteStart();
    void InvocationWriteBool(const TChar* aName, TBool aValue);
    void InvocationWriteInt(const TChar* aName, TInt aValue);
    void InvocationWriteUint(const TChar* aName, TUint aValue);
    void InvocationWriteBinaryStart(const TChar* aName);
    void InvocationWriteBinary(TByte aValue);
    void InvocationWriteBinary(const Brx& aValue);
    void InvocationWriteBinaryEnd(const TChar* aName);
    void InvocationWriteStringStart(const TChar* aName);
    void InvocationWriteString(TByte aValue);
    void InvocationWriteString(const Brx& aValue);
    void InvocationWriteStringEnd(const TChar* aName);
    void InvocationWriteEnd();
private:
    static const TUint kMaxRequestBytes = 64*1024;
    static const TUint kMaxResponseBytes = 4*1024;
    static const TUint kReadTimeoutMs = 5 * 1000;
private:
    DvStack& iDvStack;
    TIpAddress iInterface;
    TUint iPort;
    IRedirector& iRedirector;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    ReaderHttpRequest* iReaderRequest;
    ReaderHttpChunked* iDechunker;
    WriterHttpChunked* iWriterChunked;
    Sws<kMaxResponseBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    HttpHeaderConnection iHeaderConnection;
    HttpHeaderExpect iHeaderExpect;
    HeaderSoapAction iHeaderSoapAction;
    HeaderSid iHeaderSid;
    HeaderTimeout iHeaderTimeout;
    HeaderNt iHeaderNt;
    HeaderCallback iHeaderCallback;
    HeaderAcceptLanguage iHeaderAcceptLanguage;
    HttpHeaderUserAgent iHeaderUserAgent;
    const HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    Bws<kMaxRequestBytes> iSoapRequest;
    DviDevice* iInvocationDevice;
    DviService* iInvocationService;
    mutable Bws<128> iResourceUriPrefix;
    TBool iResourceWriterHeadersOnly;
    PropertyWriterFactory* iPropertyWriterFactory;
    Semaphore iShutdownSem;
};


class DviServerUpnp : public DviServer, private IRedirector
{
public:
    DviServerUpnp(DvStack& aDvStack, TUint aPort = 0);
    void Redirect(const Brx& aUriRequested, const Brx& aUriRedirectedTo);
protected:
    virtual SocketTcpServer* CreateServer(const NetworkAdapter& aNif);
private:
    TBool RedirectUri(const Brx& aUri, Brn& aRedirectTo);
private:
    TUint iPort;
    Brh iRedirectUriRequested;
    Brh iRedirectUriRedirectedTo;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER_UPNP
