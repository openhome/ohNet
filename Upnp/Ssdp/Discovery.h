#ifndef HEADER_SSDP_DISCOVERY
#define HEADER_SSDP_DISCOVERY

#include <ZappTypes.h>
#include <Buffer.h>
#include <Thread.h>
#include <Ssdp.h>
#include <Stream.h>
#include <Network.h>

#include <vector>

namespace Zapp {

// INotifyHandler - called by MulticastListener on receiving an alive or byebye notification
class ISsdpNotifyHandler
{
public:
    virtual void SsdpNotifyRootAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge) = 0;
    virtual void SsdpNotifyUuidAlive(const Brx& aUuid, const Brx& aLocation, TUint aMaxAge) = 0;
    virtual void SsdpNotifyDeviceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge) = 0;
    virtual void SsdpNotifyServiceTypeAlive(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aLocation, TUint aMaxAge) = 0;
    virtual void SsdpNotifyRootByeBye(const Brx& aUuid) = 0;
    virtual void SsdpNotifyUuidByeBye(const Brx& aUuid) = 0;
    virtual void SsdpNotifyDeviceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
    virtual void SsdpNotifyServiceTypeByeBye(const Brx& aUuid, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
    virtual ~ISsdpNotifyHandler() {}
};

// IMsearchHandler - called by MulticastListener on receiving an m-search request
class ISsdpMsearchHandler
{
public:
    virtual void SsdpSearchAll(const Endpoint& aEndpoint, TUint aMx) = 0;
    virtual void SsdpSearchRoot(const Endpoint& aEndpoint, TUint aMx) = 0;
    virtual void SsdpSearchUuid(const Endpoint& aEndpoint, TUint aMx, const Brx& aUuid) = 0;
    virtual void SsdpSearchDeviceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
    virtual void SsdpSearchServiceType(const Endpoint& aEndpoint, TUint aMx, const Brx& aDomain, const Brx& aType, TUint aVersion) = 0;
    virtual ~ISsdpMsearchHandler() {}
};

class SsdpSocketReader : public SocketUdpMulticast, public IReaderSource
{
public:
    SsdpSocketReader(const Endpoint& aMulticast, TIpAddress aInterface);
    ~SsdpSocketReader();
    Endpoint Sender() const; // endpoint of the sender to the multicast address
    // IReaderSource
    virtual void Read(Bwx& aBuffer);
    virtual void ReadFlush();
    virtual void ReadInterrupt();
private:
    UdpControllerReader* iReader;
};

// SsdpListener - base class for ListenerMulticast and ListenerUnicast
class SsdpListener : public Thread
{
    static const TUint kPriority = kPriorityNormal;
protected:
    SsdpListener();
protected:
    SsdpHeaderCacheControl iHeaderCacheControl;
    HttpHeaderLocation iHeaderLocation;
    SsdpHeaderServer iHeaderServer;
    SsdpHeaderSt iHeaderSt;
    SsdpHeaderUsn iHeaderUsn;
};

// SsdpListenerMulticast - listens to the multicast udp endpoint
//                       - processes received messages and passes them on to either an IMsearchHandler or an INotifyHandler
class SsdpListenerMulticast : public SsdpListener
{
    static const TUint kMaxBufferBytes = 1024;
public:
    SsdpListenerMulticast(TIpAddress aInterface);
    virtual ~SsdpListenerMulticast();
    TInt AddNotifyHandler(ISsdpNotifyHandler* aNotifyHandler);
    TInt AddMsearchHandler(ISsdpMsearchHandler* aMsearchHandler);
    void RemoveNotifyHandler(TInt aHandlerId);
    void RemoveMsearchHandler(TInt aHandlerId);
    TIpAddress Interface() const;
private:
    void Run();
    void Terminated();
    void Notify(ISsdpNotifyHandler& aNotifyHandler);
    void Msearch(ISsdpMsearchHandler& aMsearchHandler);
private:
    class NotifyHandler
    {
    public:
        NotifyHandler(ISsdpNotifyHandler* aHandler, TInt aId) : iHandler(aHandler), iId(aId) {}
    public:
        ISsdpNotifyHandler* iHandler;
        TInt iId;
    };
    class MsearchHandler
    {
    public:
        MsearchHandler(ISsdpMsearchHandler* aHandler, TInt aId) : iHandler(aHandler), iId(aId) {}
    public:
        ISsdpMsearchHandler* iHandler;
        TInt iId;
    };
private:
    typedef std::vector<NotifyHandler> VectorNotifyHandler;
    typedef std::vector<MsearchHandler> VectorMsearchHandler;
    VectorNotifyHandler iNotifyHandlers;
    VectorMsearchHandler iMsearchHandlers;
    Mutex iLock;
    TInt iNextHandlerId;
    TIpAddress iInterface;
    SsdpSocketReader iSocket;
    Srs<kMaxBufferBytes> iBuffer;
    ReaderHttpRequest iReaderRequest;
    SsdpHeaderHost iHeaderHost;
    SsdpHeaderMan iHeaderMan;
    SsdpHeaderMx iHeaderMx;
    SsdpHeaderNt iHeaderNt;
    SsdpHeaderNts iHeaderNts;
};

// SsdpListenerUnicast - sends out an msearch request and listens to the unicast responses
//                     - processes received messages and passes them on an INotifyHandler
class SsdpListenerUnicast : public SsdpListener
{
    static const TUint kMaxBufferBytes = 1024;
public:
    SsdpListenerUnicast(ISsdpNotifyHandler& aNotifyHandler, TIpAddress aInterface);
    ~SsdpListenerUnicast();
    void MsearchRoot();
    void MsearchUuid(const Brx& aUuid);
    void MsearchDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion);
    void MsearchServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion);
    void MsearchAll();
private:
    TUint MsearchDurationSeconds() const;
    void Run();
private:
    ISsdpNotifyHandler& iNotifyHandler;
    SsdpSocketStream iSocket;
    Sws<kMaxBufferBytes> iWriteBuffer;
    SsdpWriterMsearchRequest iWriter;
    Srs<kMaxBufferBytes> iReadBuffer;
    ReaderHttpResponse iReaderResponse;
    SsdpHeaderExt iHeaderExt;
};

} //namespace Zapp

#endif // HEADER_SSDP_DISCOVERY
