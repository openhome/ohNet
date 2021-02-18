#ifndef HEADER_SSDP_DISCOVERY
#define HEADER_SSDP_DISCOVERY

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Network.h>

#include <vector>

namespace OpenHome {
class Environment;
namespace Net {


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
    SsdpSocketReader(Environment& aEnv, const TIpAddress& aInterface, const Endpoint& aMulticast);
    ~SsdpSocketReader();
    Endpoint Sender() const; // endpoint of the sender to the multicast address
private: // from IReaderSource
    void Read(Bwx& aBuffer);
    void ReadFlush();
    void ReadInterrupt();
private:
    UdpReader* iReader;
};

// SsdpListener - base class for ListenerMulticast and ListenerUnicast
class SsdpListener : public Thread
{
    static const TUint kPriority = kPriorityNormal;
protected:
    SsdpListener(const TChar* aName);
protected:
    SsdpHeaderCacheControl iHeaderCacheControl;
    HttpHeaderLocation iHeaderLocation;
    SsdpHeaderServer iHeaderServer;
    SsdpHeaderSt iHeaderSt;
    SsdpHeaderUsn iHeaderUsn;
};

// SsdpListenerMulticast - listens to the multicast udp endpoint
//                       - processes received messages and passes them on to either an IMsearchHandler or an INotifyHandler
class SsdpListenerMulticast : public SsdpListener, private IResumeObserver
{
    static const TUint kMaxMxSecs = 5; // UPnP 1.0 allows [1..120]; 1.1 reduced this to a more sensible [1..5]
    static const TUint kMaxBufferBytes = 1024;
    static const TUint kRecvBufBytes = 32 * 1024;
    class Handler
    {
    public:
        TInt Id() const { return iId; }
        OpenHome::Mutex& Mutex() { return iLock; }
        void Lock() { iLock.Wait(); }
        void Unlock() { iLock.Signal(); }
        void Disable() { iDead = true; }
        TBool IsDisabled() const { return iDead; }
    protected:
        Handler(TInt aId) : iDead(false), iId(aId), iLock("SSDM") {}
    private:
        TBool iDead;
        TInt iId;
        OpenHome::Mutex iLock;
    };
    class NotifyHandler : public Handler
    {
    public:
        NotifyHandler(ISsdpNotifyHandler* aHandler, TInt aId) : SsdpListenerMulticast::Handler(aId), iHandler(aHandler) {}
        ISsdpNotifyHandler* Handler() { return iHandler; }
    private:
        ISsdpNotifyHandler* iHandler;
    };
    class MsearchHandler : public Handler
    {
    public:
        MsearchHandler(ISsdpMsearchHandler* aHandler, TInt aId) : SsdpListenerMulticast::Handler(aId), iHandler(aHandler) {}
        ISsdpMsearchHandler* Handler() { return iHandler; }
    private:
        ISsdpMsearchHandler* iHandler;
    };
    typedef std::vector<NotifyHandler*> VectorNotifyHandler;
    typedef std::vector<MsearchHandler*> VectorMsearchHandler;
public:
    SsdpListenerMulticast(Environment& aEnv, const TIpAddress& aInterface);
    virtual ~SsdpListenerMulticast();
    TInt AddNotifyHandler(ISsdpNotifyHandler* aNotifyHandler);
    TInt AddMsearchHandler(ISsdpMsearchHandler* aMsearchHandler);
    void RemoveNotifyHandler(TInt aHandlerId);
    void RemoveMsearchHandler(TInt aHandlerId);
    const TIpAddress& Interface() const;
private:
    void Run();
    void Terminated();
    void Notify(NotifyHandler& aHandler);
    void Notify(ISsdpNotifyHandler& aNotifyHandler);
    void Msearch(MsearchHandler& aHandler);
    void Msearch(ISsdpMsearchHandler& aMsearchHandler);
    void EraseDisabled(VectorNotifyHandler& aVector);
    void EraseDisabled(VectorMsearchHandler& aVector);
    void DnsChanged();
private: // from IResumeObserver
    void NotifyResumed();
private:
    Environment& iEnv;
    VectorNotifyHandler iNotifyHandlers;
    VectorMsearchHandler iMsearchHandlers;
    OpenHome::Mutex iLock;
    TInt iNextHandlerId;
    TIpAddress iInterface;
    SsdpSocketReader iSocket;
    Srs<kMaxBufferBytes> iBuffer;
    ReaderUntilS<kMaxBufferBytes> iReaderUntil;
    ReaderHttpRequest iReaderRequest;
    SsdpHeaderHost iHeaderHost;
    SsdpHeaderMan iHeaderMan;
    SsdpHeaderMx iHeaderMx;
    SsdpHeaderNt iHeaderNt;
    SsdpHeaderNts iHeaderNts;
    TUint iDnsChangeListenerId;
    TBool iExiting;
    TBool iRecreateSocket;
};

// SsdpListenerUnicast - sends out an msearch request and listens to the unicast responses
//                     - processes received messages and passes them on an INotifyHandler
class SsdpListenerUnicast : public SsdpListener, private IResumeObserver
{
    static const TUint kMaxBufferBytes = 1024;
    static const TUint kRecvBufBytes = 64 * 1024;
public:
    SsdpListenerUnicast(Environment& aEnv, ISsdpNotifyHandler& aNotifyHandler, const TIpAddress& aInterface);
    ~SsdpListenerUnicast();
    void MsearchRoot();
    void MsearchUuid(const Brx& aUuid);
    void MsearchDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion);
    void MsearchServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion);
    void MsearchAll();
private: // from IResumeObserver
    void NotifyResumed();
private:
    TUint MsearchDurationSeconds() const;
    void Run();
private:
    Environment& iEnv;
    ISsdpNotifyHandler& iNotifyHandler;
    TIpAddress iInterface;
    SocketUdp iSocket;
    UdpWriter iSocketWriter;
    UdpReader iSocketReader;
    Sws<kMaxBufferBytes> iWriteBuffer;
    SsdpWriterMsearchRequest iWriter;
    Srs<kMaxBufferBytes> iReadBuffer;
    ReaderUntilS<kMaxBufferBytes> iReaderUntil;
    ReaderHttpResponse iReaderResponse;
    Mutex iWriterLock;
    SsdpHeaderExt iHeaderExt;
    TBool iExiting;
    TBool iRecreateSocket;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SSDP_DISCOVERY
