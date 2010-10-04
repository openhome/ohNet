#ifndef HEADER_EVENT_UPNP
#define HEADER_EVENT_UPNP

#include <Network.h>
#include <Stream.h>
#include <Http.h>
#include <ProtocolUpnp.h>
#include <Subscription.h>

namespace Zapp {

class Subscription;

class EventSessionUpnp : public SocketTcpSession
{
public:
    EventSessionUpnp();
    ~EventSessionUpnp();
private:
    void Error(const HttpStatus& aStatus);
    void LogError(const TChar* aErr);
    void Run();
private:
    static const TUint kMaxReadBytes = 1024;
    static const Brn kMethodNotify;
    static const Brn kExpectedNt;
    static const Brn kExpectedNts;
private:
    Srs<kMaxReadBytes>* iReadBuffer;
    ReaderHttpRequest* iReaderRequest;
    HeaderNt iHeaderNt;
    HeaderNts iHeaderNts;
    HeaderSid iHeaderSid;
    HeaderSeq iHeaderSeq;
    HttpHeaderContentLength iHeaderContentLength;
    HttpHeaderTransferEncoding iHeaderTransferEncoding;
    const HttpStatus* iErrorStatus;
};

class EventServerUpnp
{
public:
    EventServerUpnp(TIpAddress aInterface);
	TUint Port() const { return iTcpServer.Port(); }
private:
    SocketTcpServer iTcpServer;
};

} // namespace Zapp

#endif // HEADER_EVENT_UPNP