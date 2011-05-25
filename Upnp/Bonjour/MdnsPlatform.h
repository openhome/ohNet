#ifndef HEADER_MDNSPLATFORM
#define HEADER_MDNSPLATFORM

#include <Standard.h>
#include <Thread.h>
#include <Timer.h>
#include <Network.h>
#include <OhNet.h>

// Bonjour source code available from  http://developer.apple.com/networking/bonjour/index.html
// We take the mDNSCore folder from their source release and discard the rest

#include <mDNSEmbeddedAPI.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class MdnsPlatform
{
    typedef mStatus Status;
    
    static const TUint kMaxHostBytes = 16;
    static const TUint kMaxMessageBytes = 4096;
public: 
    MdnsPlatform(const TChar* aHost);
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
    Status AddInterface(NetworkInterface* aNif);
    TInt InterfaceIndex(const NetworkInterface& aNif);
    TInt InterfaceIndex(const NetworkInterface& aNif, const std::vector<NetworkInterface*>& aList);
    static TBool NifsMatch(const NetworkInterface& aNif1, const NetworkInterface& aNif2);
    static void SetAddress(mDNSAddr& aAddress, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, const Endpoint& aEndpoint);
    static void SetPort(mDNSIPPort& aPort, TUint aValue);
    static void SetDomainLabel(domainlabel& aLabel, const TChar* aBuffer);
    static void SetDomainName(domainname& aName, const TChar* aBuffer);
    static void InitCallback(mDNS* aCore, Status aStatus);
    static void ServiceCallback(mDNS* aCore, ServiceRecordSet* aRecordSet, Status aStatus);
private:
    class Nif : INonCopyable
    {
    public:
        Nif(NetworkInterface* aNif, NetworkInterfaceInfo* aMdnsInfo);
        ~Nif();
        NetworkInterface& Interface();
        TIpAddress Address() const;
        TBool ContainsAddress(TIpAddress aAddress) const;
    private:
        NetworkInterface* iNif;
        NetworkInterfaceInfo* iMdnsInfo;
    };
private:
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
    TInt iSubnetChangeListenerId;
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
