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

EXCEPTION(WebSocketError);
EXCEPTION(InvalidSid);
EXCEPTION(InvalidClientId);

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
    static const Brn kMethodSubscribe;
    static const Brn kMethodUnsubscribe;
    static const Brn kMethodRenew;
    static const Brn kMethodSubscriptionTimeout;
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

class WsProtocol : private INonCopyable
{
public:
    virtual void Read(Brn& aData, TBool& aClosed) = 0;
    virtual void Write(const Brx& aData) = 0;
    virtual void Close() = 0;
protected:
    WsProtocol(Srx& aReadBuffer, Swx& aWriteBuffer);
protected:
    Srx& iReadBuffer;
    Swx& iWriteBuffer;
};

class WsProtocol76 : public WsProtocol
{
public:
    WsProtocol76(Srx& aReadBuffer, Swx& aWriteBuffer);
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
public:
    WsProtocol80(Srx& aReadBuffer, Swx& aWriteBuffer);
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
};

class PropertyUpdate
{
public:
    class Property
    {
    public:
        Property(const Brx& aName, const Brx& aValue);
        Property(const Brx& aName, WriterBwh& aValue);
        const Brx& Name() const;
        const Brx& Value() const;
        void TransferValueTo(Property& aDest);
    private:
        Brh iName;
        Brh iValue;
    };
public:
    PropertyUpdate(const Brx& aSid, TUint aSeqNum);
    ~PropertyUpdate();
    void Add(const Brx& aName, const Brx& aValue);
    void Add(const Brx& aName, WriterBwh& aValue);
    const Brx& Sid() const;
    TUint SeqNum() const;
    void Merge(PropertyUpdate& aPropertyUpdate);
    void Write(IWriter& aWriter);
private:
    Brh iSid;
    TUint iSeqNum;
    std::vector<Property*> iProperties;
};

class IPolledUpdateMerger
{
public:
    virtual PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate) = 0;
};

class PropertyWriterPolled : public IPropertyWriter, private INonCopyable
{
public:
    PropertyWriterPolled(IPolledUpdateMerger& aMerger, const Brx& aSid, TUint aSeqNum);
    ~PropertyWriterPolled();
private: // IPropertyWriter
    void PropertyWriteString(const Brx& aName, const Brx& aValue);
    void PropertyWriteInt(const Brx& aName, TInt aValue);
    void PropertyWriteUint(const Brx& aName, TUint aValue);
    void PropertyWriteBool(const Brx& aName, TBool aValue);
    void PropertyWriteBinary(const Brx& aName, const Brx& aValue);
    void PropertyWriteEnd();
private:
    IPolledUpdateMerger& iMerger;
    PropertyUpdate* iPropertyUpdate;
};

class PropertyUpdatesFlattened
{
public:
    PropertyUpdatesFlattened(const Brx& aClientId);
    ~PropertyUpdatesFlattened();
    const Brx& ClientId() const;
    void AddSubscription(const Brx& aSid);
    void RemoveSubscription(const Brx& aSid);
    TBool ContainsSubscription(const Brx& aSid) const;
    TBool IsEmpty() const;
    PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate);
    void SetClientSignal(Semaphore* aSem);
    void WriteUpdates(IWriter& aWriter);
private:
    Brh iClientId;
    typedef std::map<Brn,PropertyUpdate*,BufferCmp> UpdatesMap;
    UpdatesMap iUpdatesMap;
    typedef std::map<Brn,Brh*,BufferCmp> SidMap;
    SidMap iSidMap;
    Semaphore* iSem;
};

class PropertyUpdateCollection : public IPropertyWriterFactory, private IPolledUpdateMerger
{
public:
    PropertyUpdateCollection();
    void Detach();
    void AddSubscription(const Brx& aClientId, const Brx& aSid);
    void RemoveSubscription(const Brx& aSid);
    void SetClientSignal(const Brx& aClientId, Semaphore* aSem);
    void WriteUpdates(const Brx& aClientId, IWriter& aWriter);
private:
    ~PropertyUpdateCollection();
    PropertyUpdatesFlattened* FindByClientId(const Brx& aClientId);
    PropertyUpdatesFlattened* FindByClientId(const Brx& aClientId, TUint& aIndex);
    PropertyUpdatesFlattened* FindBySid(const Brx& aSid);
    PropertyUpdatesFlattened* FindBySid(const Brx& aSid, TUint& aIndex);
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData, const Brx& aSid, TUint aSequenceNumber);
    void NotifySubscriptionDeleted(const Brx& aSid);
private: // IPolledUpdateMerger
    PropertyUpdate* MergeUpdate(PropertyUpdate* aUpdate);
private:
    Mutex iLock;
    std::vector<PropertyUpdatesFlattened*> iUpdates;
    TBool iDetached;
};

class DviService;

class DviSessionWebSocket : public SocketTcpSession, private IPropertyWriterFactory
{
public:
    DviSessionWebSocket(TIpAddress aInterface, TUint aPort, PropertyUpdateCollection& aPropertyUpdateCollection);
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
    void Read();
    void Write(WsOpcode aOpcode, const Brx& aData);
    void Subscribe(const Brx& aRequest);
    void Unsubscribe(const Brx& aRequest);
    void Renew(const Brx& aRequest);
    void WriteSubscriptionTimeout(const Brx& aSid, TUint aSeconds);
    void WritePropertyUpdates();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const IDviSubscriptionUserData* aUserData,
                                  const Brx& aSid, TUint aSequenceNumber);
    void NotifySubscriptionDeleted(const Brx& aSid);
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
    WsHeaderKey80 iHeadverKeyV8;
    WsHeaderVersion iHeaderVersion;
    const HttpStatus* iErrorStatus;
    WsProtocol* iProtocol;
    TBool iExit;
    typedef std::map<Brn,SubscriptionWrapper*,BufferCmp> Map;
    Map iMap;
    Mutex iInterruptLock;
    Semaphore iShutdownSem;
    Fifo<Brh*> iPropertyUpdates; // used for web sockets
    PropertyUpdateCollection& iPropertyUpdateCollection;
};

class DviServerWebSocket : public DviServer
{
public:
    DviServerWebSocket();
    ~DviServerWebSocket();
protected:
    virtual SocketTcpServer* CreateServer(const NetworkAdapter& aNif);
private:
    PropertyUpdateCollection* iPropertyUpdateCollection;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_SERVER_WEBSOCKET
