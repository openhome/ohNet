#ifndef HEADER_DVI_SERVER_WEBSOCKET
#define HEADER_DVI_SERVER_WEBSOCKET

#include <DviServer.h>
#include <Network.h>
#include <Service.h>
#include <Zapp.h>
#include <Stream.h>
#include <Http.h>
#include <Exception.h>
#include <DvResourceWriter.h>

EXCEPTION(WebSocketError);

namespace Zapp {

class WebSocket
{
public:
    static const Brn kHeaderProtocol;
    static const Brn kHeaderOrigin;
    static const Brn kHeaderResponseOrigin;
    static const Brn kHeaderLocation;
    static const Brn kUpgradeWebSocket;
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

class DviSessionWebSocket : public SocketTcpSession, private IPropertyWriterFactory
{
public:
    DviSessionWebSocket(TIpAddress aInterface, TUint aPort);
    ~DviSessionWebSocket();
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
    void Close();
private: // IPropertyWriterFactory
    IPropertyWriter* CreateWriter(const Endpoint& aSubscriber, const Brx& aSubscriberPath,
                                  const Brx& aSid, TUint aSequenceNumber);
private:
    static const TUint kMaxRequestBytes = 4*1024;
    static const TUint kMaxWriteBytes = 4*1024;
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
};

class DviServerWebSocket : public DviServer
{
public:
    DviServerWebSocket();
protected:
    virtual SocketTcpServer* CreateServer(const NetworkInterface& aNif);
};

} // namespace Zapp

#endif // HEADER_DVI_SERVER_WEBSOCKET
