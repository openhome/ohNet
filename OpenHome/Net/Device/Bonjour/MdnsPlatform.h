#ifndef HEADER_MDNSPLATFORM
#define HEADER_MDNSPLATFORM

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/FunctorCpiDevice.h>

// Bonjour source code available from  http://developer.apple.com/networking/bonjour/index.html
// We take the mDNSCore folder from their source release and discard the rest

#include <OpenHome/Net/Private/mDNSEmbeddedAPI.h>
#include <OpenHome/Net/Private/dns_sd.h>

#include <vector>
#include <map>

namespace OpenHome {

class Environment;

namespace Net {

class MdnsDevice{
public:
    MdnsDevice(const Brx& aType, const Brx& aFriendlyName, const Brx& aUglyName, const Brx& aIpAddress, TUint aPort);
    virtual ~MdnsDevice() {};

    const Brx& Type();
    const Brx& FriendlyName();
    const Brx& UglyName();
    const Brx& IpAddress();
    const TUint Port();
private:
    Brn iType;
    Brn iFriendlyName;
    Brn iUglyName;
    Brn iIpAddress;
    TUint iPort;
};

class IMdnsDeviceListener
{
public:
    virtual void DeviceAdded(MdnsDevice& aDev) = 0;
    virtual ~IMdnsDeviceListener() {}
};

class MdnsPlatform
{
    typedef mStatus Status;

    static const TUint kMaxHostBytes = 16;
    static const TUint kMaxMessageBytes = 4096;
    static const TUint kMaxQueueLength = 25;
    static const TChar* kNifCookie;
public:
    static const TUint kRRCacheSize = 500;
public: 
    MdnsPlatform(Environment& aStack, const TChar* aHost, TBool aHasCache);
    ~MdnsPlatform();
    Status Init();
    void Lock();
    void Unlock();
    void Close();
    Status GetPrimaryInterface(TIpAddress& aInterface);
    Status SendUdp(const Brx& aBuffer, const Endpoint& aEndpoint);
    void SetHostName(const TChar* aName);
    TUint CreateService();
    void DeregisterService(TUint aHandle);
    void RegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo);
    void RenameAndReregisterService(TUint aHandle, const TChar* aName);
    void AppendTxtRecord(Bwx& aBuffer, const TChar* aKey, const TChar* aValue);

    void DeviceDiscovered(const Brx& aType, const Brx& aFriendlyName, const Brx& aUglyName, const Brx&  aIpAddress, TUint aPort); // called from extern C mDNS callback DNSResolveReply
    void AddMdnsDeviceListener(IMdnsDeviceListener* aListener);
    TBool FindDevices(const TChar* aServiceName);
private:
    void ServiceThread();
    void Listen();
    void TimerExpired();
    void SubnetListChanged();
    void CurrentAdapterChanged();
    void DoSetHostName();
    Status AddInterface(NetworkAdapter* aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList);
    static TBool NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2);
    static void SetAddress(mDNSAddr& aAddress, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, TUint aValue);
    static void SetDomainLabel(domainlabel& aLabel, const TChar* aBuffer);
    static void SetDomainName(domainname& aName, const TChar* aBuffer);
    static void ServiceCallback(mDNS* aCore, ServiceRecordSet* aRecordSet, mStatus aStatus);
    static void StatusCallback(mDNS *const m, mStatus aStatus);
private:
    class Nif : INonCopyable
    {
    public:
        Nif(NetworkAdapter& aNif, NetworkInterfaceInfo* aMdnsInfo);
        ~Nif();
        NetworkAdapter& Adapter();
        NetworkInterfaceInfo& Info();
        TIpAddress Address() const;
        TBool ContainsAddress(TIpAddress aAddress) const;
    private:
        NetworkAdapter& iNif;
        NetworkInterfaceInfo* iMdnsInfo;
    };
    enum MdnsServiceAction
    {
        eInvalid,
        eRegister,
        eDeregister,
        eRenameAndReregister,
    };
    class MdnsService
    {
    public:
        MdnsService(mDNS& aMdns);
        void Set(MdnsServiceAction aAction, TUint aHandle, ServiceRecordSet& aService, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo);
        TUint PerformAction();
    private:
        TUint Register();
        TUint Deregister();
        TUint RenameAndReregister();
    private:
        // NOTE: all buffer sizes taken from mDNSEmbeddedAPI.h
        mDNS& iMdns;
        MdnsServiceAction iAction;
        TUint iHandle;
        ServiceRecordSet* iService;
        Bws<MAX_DOMAIN_LABEL-1> iName;
        Bws<MAX_DOMAIN_NAME-1> iType;
        TIpAddress iInterface;
        TUint iPort;
        Bws<2048> iInfo;
    };
    /*
     * Simple recursive mutex.
     *
     * Only works if called from at most 1 thread not created by ohNet.
     * (i.e. one thread where Thread::Current() returns NULL).
     */
    class MutexRecursive
    {
    #define Thread_None ((Thread*)1) // assumed invalid thread address
    public:
        MutexRecursive();
        ~MutexRecursive();
        void Lock();
        void Unlock();
    private:
        Mutex iMutex;
        Thread* iOwner;
        TUint iCount;
    };
private:
    Environment& iEnv;
    Brhz iHost;
    TBool iHasCache;
    MutexRecursive iMutex;
    ThreadFunctor* iThreadListen;
    Timer* iTimer;
    Mutex iTimerLock;
    Endpoint iMulticast;
    SocketUdpMulticast iReader;
    UdpReader iReaderController;
    SocketUdp iClient;
    mDNS* iMdns;
    Mutex iInterfacesLock;
    std::vector<MdnsPlatform::Nif*> iInterfaces;
    TUint iSubnetListChangeListenerId;
    TUint iCurrentAdapterChangeListenerId;
    Bws<kMaxMessageBytes> iMessage;
    typedef std::map<TUint, ServiceRecordSet*> Map;
    Mutex iServicesLock;
    Fifo<MdnsService*> iFifoFree;
    Fifo<MdnsService*> iFifoPending;
    Semaphore iSem;
    ThreadFunctor* iThreadService;
    Map iServices;
    TUint iNextServiceIndex;
    TBool iStop;
    TBool iTimerDisabled;
    std::vector<DNSServiceRef*> iSdRefs;
    std::vector<IMdnsDeviceListener*> iDeviceListeners;
    CacheEntity iMdnsCache[kRRCacheSize];
    std::vector<void*> iDynamicCache;
    Mutex iDiscoveryLock;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_MDNSPLATFORM
