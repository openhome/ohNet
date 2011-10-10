#ifndef HEADER_EVENT_UPNP
#define HEADER_EVENT_UPNP

#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Net/Private/ProtocolUpnp.h>
#include <OpenHome/Net/Private/Subscription.h>

namespace OpenHome {
namespace Net {

class Subscription;

class EventSessionUpnp : public SocketTcpSession
{
public:
    EventSessionUpnp();
    ~EventSessionUpnp();
private:
    void Error(const HttpStatus& aStatus);
    void LogError(CpiSubscription* aSubscription, const TChar* aErr);
    virtual void Run();
    void ProcessNotification(IEventProcessor& aEventProcessor, const Brx& aEntity);
private:
    static const TUint kMaxReadBytes = 1024;
    static const TUint kReadTimeoutMs = 5 * 1000;
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

} // namespace Net
} // namespace OpenHome

#endif // HEADER_EVENT_UPNP