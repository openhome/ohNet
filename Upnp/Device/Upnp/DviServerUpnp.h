#ifndef HEADER_DVI_SERVER
#define HEADER_DVI_SERVER

#include <ZappTypes.h>
#include <Network.h>
#include <Http.h>
#include <Zapp.h>
#include <Thread.h>
#include <DviDevice.h>
#include <Stream.h>
#include <DviService.h>
#include <Subscription.h>
#include <Service.h>

#include <vector>

namespace Zapp {

class HeaderExpect : public HttpHeader
{
public:
    TBool Continue() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TBool iContinue;
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
    const Zapp::Endpoint& Endpoint() const;
    const Brx& Uri() const;
    void Log();
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Zapp::Endpoint iEndpoint;
    Bwh iUri;
};

class PropertyWriter : public IPropertyWriter
{
public:
    PropertyWriter(const Endpoint& aPublisher, const Endpoint& aSubscriber, const Brx& aSubscriberPath, const Brx& aSid, TUint aSequenceNumber);
private: // IPropertyWriter
    ~PropertyWriter();
    void PropertyWriteString(const Brx& aName, const Brx& aValue);
    void PropertyWriteInt(const Brx& aName, TInt aValue);
    void PropertyWriteUint(const Brx& aName, TUint aValue);
    void PropertyWriteBool(const Brx& aName, TBool aValue);
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue);
    void PropertyWriteEnd();
private:
    void WriteVariable(const Brx& aName, const Brx& aValue);
private:
    static const TUint kMaxRequestBytes = 12*1024;
    static const TUint kMaxResponseBytes = 128;
    SocketTcpClient iSocket;
    Sws<kMaxRequestBytes>* iWriteBuffer;
    WriterHttpRequest* iWriterEvent;
    WriterHttpChunked* iWriterChunked;
};

class DviSessionUpnp : public SocketTcpSession, private IResourceWriter, private IDvInvocation, private IPropertyWriterFactory
{
public:
    DviSessionUpnp(TIpAddress aInterface, TUint aPort);
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
private: // IResourceWriter
    void WriteResourceBegin(TUint aTotalBytes, const TChar* aMimeType);
    void WriteResource(const TByte* aData, TUint aBytes);
    void WriteResourceEnd();
private: // IDvInvocation
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
    IPropertyWriter* CreateWriter(const Endpoint& aSubscriber, const Brx& aSubscriberPath,
                                  const Brx& aSid, TUint aSequenceNumber);
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxResponseBytes = 4*1024;
private:
    TIpAddress iInterface;
    TUint iPort;
    Srs<kMaxRequestBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    WriterHttpChunked* iWriterChunked;
    Sws<kMaxResponseBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderConnection iHeaderConnection;
    HeaderExpect iHeaderExpect;
    HeaderSoapAction iHeaderSoapAction;
    HeaderSid iHeaderSid;
    HeaderTimeout iHeaderTimeout;
    HeaderNt iHeaderNt;
    HeaderCallback iHeaderCallback;
    const HttpStatus* iErrorStatus;
    TBool iResponseStarted;
    TBool iResponseEnded;
    Brn iSoapRequest;
};

class DviServerUpnp
{
public:
    DviServerUpnp();
    ~DviServerUpnp();
    static TUint Port(TIpAddress aInterface);
private:
    void CreateServer(const NetworkInterface& aNif);
    void SubnetChanged();
    TInt FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList);
    TInt FindServer(TIpAddress aSubnet);
private:
    class Server
    {
    public:
        Server(const NetworkInterface& aNif);
        ~Server();
        TIpAddress Interface() const { return iNif->Address(); }
        TIpAddress Subnet() const { return iNif->Subnet(); }
        TUint Port() const { return iServer->Port(); }
    private:
        Server() {}
    private:
        SocketTcpServer* iServer;
        NetworkInterface* iNif;
    };
private:
    Mutex iLock;
    std::vector<DviServerUpnp::Server*> iServers;
    TInt iSubnetChangeListenerId;
};

} // namespace Zapp

#endif // HEADER_DVI_SERVER
