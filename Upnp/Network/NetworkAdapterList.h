#ifndef HEADER_NETWORKINTERFACELIST
#define HEADER_NETWORKINTERFACELIST

#include <OhNetTypes.h>
#include <OhNet.h>
#include <Functor.h>
#include <Thread.h>

#include <vector>
#include <map>

namespace OpenHome {

class NetworkAdapterList
{
public:
    static const TUint kListenerIdNull = 0;
public:
    NetworkAdapterList(TIpAddress aDefaultSubnet=0);
    ~NetworkAdapterList();
    NetworkAdapter* CurrentAdapter() const;
    const std::vector<NetworkAdapter*>& List() const;
    std::vector<NetworkAdapter*>* CreateSubnetList() const;
    static void DestroySubnetList(std::vector<NetworkAdapter*>* aList);
    void SetCurrentSubnet(TIpAddress aSubnet);
    TUint AddCurrentChangeListener(Functor aFunctor);
    void RemoveCurrentChangeListener(TUint aId);
    TUint AddSubnetListChangeListener(Functor aFunctor);
    void RemoveSubnetListChangeListener(TUint aId);
private:
    typedef std::map<TUint,Functor> Map;
    std::vector<NetworkAdapter*>* CreateSubnetListLocked() const;
    TUint AddListener(Functor aFunctor, Map& aMap);
    void RemoveSubnetListChangeListener(TUint aId, Map& aMap);
    static void InterfaceListChanged(void* aPtr);
    static TInt FindSubnet(TIpAddress aSubnet, const std::vector<NetworkAdapter*>& aList);
    void UpdateCurrentAdapter();
    void HandleInterfaceListChanged();
    void RunCallbacks(Map& aMap);
private:
    mutable Mutex iListLock;
    Mutex iListenerLock;
    std::vector<NetworkAdapter*>* iNetworkAdapters;
    std::vector<NetworkAdapter*>* iSubnets;
    mutable NetworkAdapter* iCurrent;
    TIpAddress iDefaultSubnet;
    Map iListenersCurrent;
    Map iListenersSubnet;
    TUint iNextListenerId;
};

} // namespace OpenHome

#endif // HEADER_NETWORKINTERFACELIST
