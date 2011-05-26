#ifndef HEADER_DVI_SERVER_UPNP
#define HEADER_DVI_SERVER_UPNP

#include <OhNetTypes.h>
#include <Network.h>
#include <Http.h>
#include <Buffer.h>
#include <DviDevice.h>
#include <Stream.h>
#include <DviService.h>
#include <Subscription.h>
#include <Service.h>
#include <DviServer.h>
#include <DviSubscription.h>

#include <vector>

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
    void Log();
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    OpenHome::Endpoint iEndpoint;
    Bwh iUri;
};

class SubscriptionDataUpnp : public IDviSubscriptionUserData
{
public:
    SubscriptionDataUpnp(const Endpoint& aSubscriber, const Brx& aSubscriberPath);
    const Endpoint& Subscriber() const;
    const Brx& SubscriberPath() const;
    virtual const void* Data() const;
    virtual void Release();
private:
    ~SubscriptionDataUpnp() {}
private:
    Endpoint iSubscriber;
    Brh iSubscriberPath;
};

class PropertyWriterUpnp : public PropertyWriter
{
public:
    PropertyWriterUpnp(const Endpoint& aPublisher, const Endpoint& aSubscriber, const Brx& aSubscriberPath, const Brx& aSid, TUint aSequenceNumber);
private: // IPropertyWriter
    ~PropertyWriterUpnp();
    void PropertyWriteEnd();
private:
    static const TUint kMaxRequestBytes = 12*1024;
    static const TUint kMaxResponseBytes = 128;
    SocketTcpClient iSocket;
    Sws<kMaxRequestBytes>* iWriteBuffer;
    WriterHttpRequest* iWriterEvent;
    WriterHttpChunked* iWriterChunked;
};

class DviSessionUpnp : public SocketTcpSession, private IResourceWriter, private IDviInvocation, private IPropertyWriterFactory
{
public:
    DviSessionUpnp(TIpAddress aInterface, TUint aPort, IRedirector& aRedirector);
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
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxResponseBytes = 4*1024;
private:
    TIpAddress iInterface;
    TUint iPort;
    IRedirector& iRedirector;
    Srs<kMaxRequestBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    WriterHttpChunked* iWriterChunked;
    Sws<kMaxResponseBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderConnection iHeaderConnection;
    HttpHeaderExpect iHeaderExpect;
    HeaderSoapAction iHeaderSoapAction;
    HeaderSid iHeaderSid;
    HeaderTimeout iHeaderTimeout;
    HeaderNt iHeaderNt;
    HeaderCallback iHeaderCallback;
    const HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    Brn iSoapRequest;
    DviService* iInvocationService;
	TBool iResourceWriterHeadersOnly;
    Semaphore iShutdownSem;
};

class DviServerUpnp : public DviServer, private IRedirector
{
public:
    DviServerUpnp(TUint aPort = 0);
    void Redirect(const Brx& aUriRequested, const Brx& aUriRedirectedTo);
protected:
    virtual SocketTcpServer* CreateServer(const NetworkInterface& aNif);
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
