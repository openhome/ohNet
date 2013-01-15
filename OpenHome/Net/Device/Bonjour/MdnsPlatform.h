#ifndef HEADER_MDNSPLATFORM
#define HEADER_MDNSPLATFORM

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Net/Core/OhNet.h>

// Bonjour source code available from  http://developer.apple.com/networking/bonjour/index.html
// We take the mDNSCore folder from their source release and discard the rest

#include <OpenHome/Net/Private/mDNSEmbeddedAPI.h>

#include <vector>
#include <map>

namespace OpenHome {

class Environment;
    
namespace Net {

class MdnsPlatform
{
    typedef mStatus Status;
    
    static const TUint kMaxHostBytes = 16;
    static const TUint kMaxMessageBytes = 4096;
public: 
    MdnsPlatform(Environment& aStack, const TChar* aHost);
    ~MdnsPlatform();
    Status Init();
    void Lock();
    void Unlock();
    void Close();
    Status SendUdp(const Brx& aBuffer, const Endpoint& aEndpoint);
    void SetHostName(const TChar* aName);
    TUint CreateService();
    void DeregisterService(TUint aHandle);
    void RegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress Interface, TUint aPort, const TChar* aInfo);
    void RenameAndReregisterService(TUint aHandle, const TChar* aName);
    void AppendTxtRecord(TChar* aBuffer, TUint aLength, const TChar* aKey, const TChar* aValue);
private:
    void Listen();
    void TimerExpired();
    void SubnetListChanged();
    Status AddInterface(NetworkAdapter* aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif);
    TInt InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList);
    static TBool NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2);
    static void SetAddress(mDNSAddr& aAddress, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, TUint aValue);
    static void SetDomainLabel(domainlabel& aLabel, const TChar* aBuffer);
    static void SetDomainName(domainname& aName, const TChar* aBuffer);
    static void InitCallback(mDNS* aCore, mStatus aStatus);
    static void ServiceCallback(mDNS* aCore, ServiceRecordSet* aRecordSet, mStatus aStatus);
private:
    class Nif : INonCopyable
    {
    public:
        Nif(NetworkAdapter& aNif, NetworkInterfaceInfo* aMdnsInfo);
        ~Nif();
        NetworkAdapter& Adapter();
        TIpAddress Address() const;
        TBool ContainsAddress(TIpAddress aAddress) const;
    private:
        NetworkAdapter& iNif;
        NetworkInterfaceInfo* iMdnsInfo;
    };
private:
    Environment& iEnv;
    Brhz iHost;
    Mutex iMutex;
    ThreadFunctor* iThreadListen;
    Timer* iTimer;
    Endpoint iMulticast;
    SocketUdpMulticast iReader;
    UdpReader iReaderController;
    SocketUdp iClient;
    mDNS* iMdns;
    Mutex iInterfacesLock;
    std::vector<MdnsPlatform::Nif*> iInterfaces;
    TInt iSubnetListChangeListenerId;
    Status iStatus;
    Bws<kMaxMessageBytes> iMessage;
    typedef std::map<TUint, ServiceRecordSet*> Map;
    Mutex iServicesLock;
    Map iServices;
    TUint iNextServiceIndex;
    TBool iStop;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_MDNSPLATFORM
