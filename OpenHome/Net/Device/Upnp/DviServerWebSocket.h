#ifndef HEADER_DVI_SERVER_WEBSOCKET
#define HEADER_DVI_SERVER_WEBSOCKET

#include <OpenHome/Net/Private/DviServer.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Net/Private/DviSubscription.h>

#include <map>

EXCEPTION(WebSocketError)

namespace OpenHome {
namespace Net {

class WebSocket
{
public:
    static const Brn kHeaderProtocol;
    static const Brn kHeaderOrigin;
    static const Brn kHeaderResponseOrigin;
    static const Brn kHeaderLocation;
    static const Brn kHeaderKey;
    static const Brn kHeaderVersion;
    static const Brn kUpgradeWebSocket;
    static const Brn kTagRoot;
    static const Brn kTagMethod;
    static const Brn kTagUdn;
    static const Brn kTagService;
    static const Brn kTagSid;
    static const Brn kTagNt;
    static const Brn kTagTimeout;
    static const Brn kTagNts;
    static const Brn kTagSubscription;
    static const Brn kTagSeq;
    static const Brn kTagClientId;
    static const Brn kMethodSubscribe;
    static const Brn kMethodUnsubscribe;
    static const Brn kMethodRenew;
    static const Brn kMethodSubscriptionSid;
    static const Brn kMethodSubscriptionRenewed;
    static const Brn kMethodGetPropertyUpdates;
    static const Brn kMethodPropertyUpdate;
    static const Brn kValueProtocol;
    static const Brn kValueNt;
    static const Brn kValuePropChange;
};

class HttpHeaderUpgrade : public HttpHeader
{
public:
    Brn Upgrade() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Brh iUpgrade;
};

class WsHeaderKey : public HttpHeader
{
public:
    TUint Key() const;
protected:
    WsHeaderKey(const TChar* aHeader);
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Brh iHeader;
    Brh iKey;
};

class WsHeaderKey1 : public WsHeaderKey
{
public:
    WsHeaderKey1();
};

class WsHeaderKey2 : public WsHeaderKey
{
public:
    WsHeaderKey2();
};

class WsHeaderProtocol : public HttpHeader
{
public:
    const Brx& Protocol() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Brh iProtocol;
};

class WsHeaderOrigin : public HttpHeader
{
public:
    const Brx& Origin() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Brh iOrigin;
};

class WsHeaderKey80 : public HttpHeader
{
public:
    const Brx& Key() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    Brh iKey;
};

class WsHeaderVersion : public HttpHeader
{
public:
    TUint Version() const;
private:
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TUint iVersion;;
};

class DviSessionWebSocket;

class PropertyWriterWs : public PropertyWriter
{
public:
    static PropertyWriterWs* Create(DviSessionWebSocket& aSession, const Brx& aSid, TUint aSequenceNumber);
private:
    PropertyWriterWs(DviSessionWebSocket& aSession);
    void WriteHeaders(const Brx& aSid, TUint aSequenceNumber);
private: // IPropertyWriter
    ~PropertyWriterWs();
    void PropertyWriteEnd();
private:
    static const TUint kWriteBufGranularity = 1024;
    DviSessionWebSocket& iSession;
    WriterBwh iWriter;
};

class WsProtocol : private INonCopyable
{
public:
    virtual ~WsProtocol();
    virtual void Read(Brn& aData, TBool& aClosed) = 0;
    virtual void Write(const Brx& aData) = 0;
    virtual void Close() = 0;
protected:
    WsProtocol(ReaderUntil& aReaderUntil, Swx& aWriteBuffer);
protected:
    ReaderUntil& iReaderUntil;
    Swx& iWriteBuffer;
};

class WsProtocol76 : public WsProtocol
{
public:
    WsProtocol76(ReaderUntil& aReaderUntil, Swx& aWriteBuffer);
private:
    void Read(Brn& aData, TBool& aClosed);
    void Write(const Brx& aData);
    void Close();
private:
    static const TByte kFrameMsgStart = (TByte)'\0';
    static const TByte kMsgEnd = (TByte)'\xff';
    static const TByte kFrameCloseStart = (TByte)'\xff';
    static const TByte kMsgCloseEnd = (TByte)'\0';
};

class WsProtocol80 : public WsProtocol
{
    static const TUint kMaxRequestBytes = 4*1024;
public:
    WsProtocol80(ReaderUntil& aReaderUntil, Swx& aWriteBuffer);
private:
    void Read(Brn& aData, TBool& aClosed);
    void Write(const Brx& aData);
    void Close();
private:
    enum WsOpcode
    {
        eContinuation = 0x0
       ,eText = 0x1
       ,eBinary = 0x2
       ,eClose = 0x8
       ,ePing = 0x9
       ,ePong = 0xA
    };
    static const TUint16 kCloseNormal          = 1000;
    static const TUint16 kCloseProtocolError   = 1002;
    static const TUint16 kCloseUnsupportedData = 1003;
    static const TUint16 kCloseMsgTooLong      = 1004;
private:
    void Write(WsOpcode aOpcode, const Brx& aData);
    void Close(TUint16 aCode);
private:
    Bwh iMessage;
    ReaderProtocolS<kMaxRequestBytes> iReaderProtocol;
};

class DviService;

class DviSessionWebSocket : public SocketTcpSession, private IPropertyWriterFactory
{
public:
    DviSessionWebSocket(DvStack& aDvStack, TIpAddress aInterface, TUint aPort);
    ~DviSessionWebSocket();
    void QueuePropertyUpdate(Brh* aUpdate);
private:
    enum WsOpcode
    {
        eContinuation = 0x0
       ,eText = 0x1
       ,eBinary = 0x2
       ,eClose = 0x8
       ,ePing = 0x9
       ,ePong = 0xA
    };
private:
    void Run();
    void Error(const HttpStatus& aStatus);
    void Handshake();
    WsProtocol* Handshake76();
    WsProtocol* Handshake80();
    void DoRead();
    void Subscribe(const Brx& aRequest);
    void Unsubscribe(const Brx& aRequest);
    void Renew(const Brx& aRequest);
    void WriteSubscriptionSid(const Brx& aDevice, const Brx& aService, const Brx& aSid, TUint aSeconds);
    void WriteSubscriptionRenewed(const Brx& aSid, TUint aSeconds);
    void WritePropertyUpdates();
private: // IPropertyWriterFactory
    IPropertyWriter* ClaimWriter(const IDviSubscriptionUserData* aUserData,
                                 const Brx& aSid, TUint aSequenceNumber);
    void ReleaseWriter(IPropertyWriter* aWriter);
    void NotifySubscriptionCreated(const Brx& aSid);
    void NotifySubscriptionDeleted(const Brx& aSid);
    void NotifySubscriptionExpired(const Brx& aSid);
    void LogUserData(IWriter& aWriter, const IDviSubscriptionUserData& aUserData);
private:
    class SubscriptionWrapper
    {
    public:
        SubscriptionWrapper(DviSubscription& aSubscription, const Brx& aSid, DviService& aService);
        ~SubscriptionWrapper();
        DviSubscription& Subscription() { return iSubscription; }
        const Brx& Sid() const { return iSid; }
    private:
        DviSubscription& iSubscription;
        Brh iSid;
        DviService& iService;
    };
public:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxWriteBytes = 4*1024;
    static const TUint kMaxPropertyUpdates = 20;
    static const TUint kReadTimeoutMs = 5 * 1000;
private:
    DvStack& iDvStack;
    Endpoint iEndpoint;
    Srx* iReadBuffer;
    ReaderUntil* iReaderUntil;
    ReaderHttpRequest* iReaderRequest;
    Sws<kMaxWriteBytes>* iWriterBuffer;
    WriterHttpResponse* iWriterResponse;
    HttpHeaderHost iHeaderHost;
    HttpHeaderConnection iHeaderConnection;
    HttpHeaderUpgrade iHeaderUpgrade;
    WsHeaderKey1 iHeaderKey1;
    WsHeaderKey2 iHeaderKey2;
    WsHeaderProtocol iHeaderProtocol;
    WsHeaderOrigin iHeaderOrigin;
    WsHeaderKey80 iHeadverKeyV8;
    WsHeaderVersion iHeaderVersion;
    HttpHeaderContentLength iHeaderContentLength;
    const HttpStatus* iErrorStatus;
    WsProtocol* iProtocol;
    TBool iExit;
    typedef std::map<Brn,SubscriptionWrapper*,BufferCmp> Map;
    Map iMap;
    Mutex iInterruptLock;
    Semaphore iShutdownSem;
    Fifo<Brh*> iPropertyUpdates; // used for web sockets
};

class DviServerWebSocket : public DviServer
{
public:
    DviServerWebSocket(DvStack& aDvStack);
public: // from DviServer
    void Start();
protected:
    virtual SocketTcpServer* CreateServer(const NetworkAdapter& aNif);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER_WEBSOCKET
