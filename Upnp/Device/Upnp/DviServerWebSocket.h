#ifndef HEADER_DVI_SERVER_WEBSOCKET
#define HEADER_DVI_SERVER_WEBSOCKET

#include <DviServer.h>
#include <Buffer.h>
#include <Thread.h>
#include <Network.h>
#include <Service.h>
#include <OhNet.h>
#include <Stream.h>
#include <Http.h>
#include <Exception.h>
#include <Fifo.h>
#include <DviSubscription.h>

#include <map>

EXCEPTION(WebSocketError);

namespace OpenHome {
namespace Net {

class WebSocket
{
public:
    static const Brn kHeaderProtocol;
    static const Brn kHeaderOrigin;
    static const Brn kHeaderResponseOrigin;
    static const Brn kHeaderLocation;
    static const Brn kUpgradeWebSocket;
    static const Brn kTagRoot;
    static const Brn kTagMethod;
    static const Brn kTagUdn;
    static const Brn kTagService;
    static const Brn kTagSid;
    static const Brn kTagNt;
    static const Brn kTagTimeout;
    static const Brn kTagNts;
    static const Brn kTagSeq;
    static const Brn kMethodSubscribe;
    static const Brn kMethodUnsubscribe;
    static const Brn kMethodRenew;
    static const Brn kMethodSubscriptionTimeout;
    static const Brn kMethodPropertyUpdate;
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

class SubscriptionDataWs : public IDviSubscriptionUserData
{
public:
    SubscriptionDataWs(const Brx& aSubscriberSid);
    const Brx& SubscriberSid() const;
    virtual const void* Data() const;
    virtual void Release();
private:
    ~SubscriptionDataWs() {}
private:
    Brh iSubscriberSid;
};

class DviSessionWebSocket;

class PropertyWriterWs : public PropertyWriter
{
public:
    PropertyWriterWs(DviSessionWebSocket& aSession, const Brx& aSid, TUint aSequenceNumber);
private: // IPropertyWriter
    ~PropertyWriterWs();
    void PropertyWriteEnd();
private:
    static const TUint kWriteBufGranularity = 1024;
    DviSessionWebSocket& iSession;
    WriterBwh iWriter;
};

class DviService;

class DviSessionWebSocket : public SocketTcpSession, private IPropertyWriterFactory
{
public:
    DviSessionWebSocket(TIpAddress aInterface, TUint aPort);
    ~DviSessionWebSocket();
    void QueuePropertyUpdate(Brh* aUpdate);
private:
    enum WsOpcode
    {
        eContinuation
       ,eClose
       ,ePing
       ,ePong
       ,eText
       ,eBinary
    };
private:
    void Run();
    void Error(const HttpStatus& aStatus);
    void Handshake();
    void Read();
    void Write(WsOpcode aOpcode, const Brx& aData);
    void WriteConnectionClose();
    void Subscribe(const Brx& aRequest);
    void Unsubscribe(const Brx& aRequest);
    void Renew(const Brx& aRequest);
    void WriteSubscriptionTimeout(const Brx& aSid, TUint aSeconds);
    void WritePropertyUpdates();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData,
                                  const Brx& aSid, TUint aSequenceNumber);
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
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxWriteBytes = 4*1024;
    static const TUint kMaxPropertyUpdates = 20;
    static const TByte kFrameMsgStart = (TByte)'\0';
    static const TByte kMsgEnd = (TByte)'\xff';
    static const TByte kFrameCloseStart = (TByte)'\xff';
    static const TByte kMsgCloseEnd = (TByte)'\0';
private:
    Endpoint iEndpoint;
    Srs<kMaxRequestBytes>* iReadBuffer;
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
    const HttpStatus* iErrorStatus;
    TBool iExit;
    typedef std::map<Brn,SubscriptionWrapper*,BufferCmp> Map;
    Map iMap;
    Mutex iInterruptLock;
    Semaphore iShutdownSem;
    Fifo<Brh*> iPropertyUpdates;
};

class DviServerWebSocket : public DviServer
{
public:
    DviServerWebSocket();
protected:
    virtual SocketTcpServer* CreateServer(const NetworkAdapter& aNif);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER_WEBSOCKET
