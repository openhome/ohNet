#ifndef HEADER_NETWORKINTERFACELIST
#define HEADER_NETWORKINTERFACELIST

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Functor.h>
#include <OpenHome/FunctorNetworkAdapter.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>
#include <map>

namespace OpenHome {

class NetworkAdapterList : private IStackObject
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
    TUint AddSubnetAddedListener(FunctorNetworkAdapter aFunctor);
    void RemoveSubnetAddedListener(TUint aId);
    TUint AddSubnetRemovedListener(FunctorNetworkAdapter aFunctor);
    void RemoveSubnetRemovedListener(TUint aId);
    TUint AddNetworkAdapterChangeListener(FunctorNetworkAdapter aFunctor);
    void RemoveNetworkAdapterChangeListener(TUint aId);
private:
    typedef std::map<TUint,Functor> Map;
    typedef std::map<TUint,FunctorNetworkAdapter> MapNetworkAdapter;
    std::vector<NetworkAdapter*>* CreateSubnetListLocked() const;
    TUint AddListener(Functor aFunctor, Map& aMap);
    void RemoveSubnetListChangeListener(TUint aId, Map& aMap);
    TUint AddSubnetListener(FunctorNetworkAdapter aFunctor, MapNetworkAdapter& aMap);
    void RemoveSubnetListener(TUint aId, MapNetworkAdapter& aMap);
    static void InterfaceListChanged(void* aPtr);
    static TInt FindSubnet(TIpAddress aSubnet, const std::vector<NetworkAdapter*>& aList);
    void UpdateCurrentAdapter();
    void HandleInterfaceListChanged();
    void RunCallbacks(Map& aMap);
    void RunSubnetCallbacks(MapNetworkAdapter& aMap, NetworkAdapter& aAdapter);
    static TBool CompareSubnets(NetworkAdapter* aI, NetworkAdapter* aJ);
private: // from IStackObject
    void ListObjectDetails() const;
private:
    mutable Mutex iListLock;
    Mutex iListenerLock;
    std::vector<NetworkAdapter*>* iNetworkAdapters;
    std::vector<NetworkAdapter*>* iSubnets;
    mutable NetworkAdapter* iCurrent;
    TIpAddress iDefaultSubnet;
    Map iListenersCurrent;
    Map iListenersSubnet;
    MapNetworkAdapter iListenersAdded;
    MapNetworkAdapter iListenersRemoved;
    MapNetworkAdapter iListenersAdapterChanged;
    TUint iNextListenerId;
};

} // namespace OpenHome

#endif // HEADER_NETWORKINTERFACELIST
