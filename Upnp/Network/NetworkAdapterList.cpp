#include <NetworkAdapterList.h>
#include <OhNetTypes.h>
#include <OsWrapper.h>
#include <Thread.h>
#include <Stack.h>

using namespace OpenHome;


NetworkAdapterList::NetworkAdapterList(TIpAddress aDefaultSubnet)
    : iListLock("MNIL")
    , iListenerLock("MNIO")
    , iCurrent(NULL)
    , iNextListenerId(1)
{
    Net::Stack::AddObject(this, "NetworkAdapterList");
    iDefaultSubnet = aDefaultSubnet;
    iNetworkAdapters = Os::NetworkListAdapters(Net::Stack::InitParams().UseLoopbackNetworkAdapter());
    iSubnets = CreateSubnetList();
    Os::NetworkSetInterfaceChangedObserver(&InterfaceListChanged, this);
}

NetworkAdapterList::~NetworkAdapterList()
{
    DestroySubnetList(iNetworkAdapters);
    DestroySubnetList(iSubnets);
    Net::Stack::RemoveObject(this, "NetworkAdapterList");
}

NetworkAdapter* NetworkAdapterList::CurrentAdapter() const
{
    AutoMutex a(iListLock);
    if (iCurrent == NULL) {
        return NULL;
    }
    iCurrent->AddRef();
    return iCurrent;
}

const std::vector<NetworkAdapter*>& NetworkAdapterList::List() const
{
    return *iNetworkAdapters;
}

std::vector<NetworkAdapter*>* NetworkAdapterList::CreateSubnetList() const
{
    iListLock.Wait();
    std::vector<NetworkAdapter*>* list = CreateSubnetListLocked();
    iListLock.Signal();
    return list;
}

void NetworkAdapterList::DestroySubnetList(std::vector<NetworkAdapter*>* aList)
{
    if (aList != NULL) {
        for (TUint i=0; i<aList->size(); i++) {
            (*aList)[i]->RemoveRef();
        }
        delete aList;
    }
}

void NetworkAdapterList::SetCurrentSubnet(TIpAddress aSubnet)
{
    iListLock.Wait();
    TIpAddress oldSubnet = (iCurrent==NULL? 0 : iCurrent->Subnet());
    iDefaultSubnet = aSubnet;
    UpdateCurrentAdapter();
    iListLock.Signal();
    if (aSubnet != oldSubnet) {
        RunCallbacks(iListenersCurrent);
    }
}

TUint NetworkAdapterList::AddCurrentChangeListener(Functor aFunctor)
{
    return AddListener(aFunctor, iListenersCurrent);
}

void NetworkAdapterList::RemoveCurrentChangeListener(TUint aId)
{
    RemoveSubnetListChangeListener(aId, iListenersCurrent);
}

TUint NetworkAdapterList::AddSubnetListChangeListener(Functor aFunctor)
{
    return AddListener(aFunctor, iListenersSubnet);
}

void NetworkAdapterList::RemoveSubnetListChangeListener(TUint aId)
{
    RemoveSubnetListChangeListener(aId, iListenersSubnet);
}

std::vector<NetworkAdapter*>* NetworkAdapterList::CreateSubnetListLocked() const
{
    std::vector<NetworkAdapter*>* list = new std::vector<NetworkAdapter*>;
    for (TUint i=0; i<iNetworkAdapters->size(); i++) {
        NetworkAdapter* nif = (*iNetworkAdapters)[i];
        TIpAddress subnet = nif->Subnet();
        if (-1 == NetworkAdapterList::FindSubnet(subnet, *list)) {
            nif->AddRef();
            list->push_back(nif);
        }
    }
    return list;
}

TUint NetworkAdapterList::AddListener(Functor aFunctor, Map& aMap)
{
    iListenerLock.Wait();
    TUint id = iNextListenerId;
    aMap.insert(std::pair<TUint,Functor>(id, aFunctor));
    iNextListenerId++;
    iListenerLock.Signal();
    return id;
}

void NetworkAdapterList::RemoveSubnetListChangeListener(TUint aId, Map& aMap)
{
    iListenerLock.Wait();
    Map::iterator it = aMap.find(aId);
    if (it != aMap.end()) {
        aMap.erase(it);
    }
    iListenerLock.Signal();
}

void NetworkAdapterList::InterfaceListChanged(void* aPtr)
{
    reinterpret_cast<NetworkAdapterList*>(aPtr)->HandleInterfaceListChanged();
}

TInt NetworkAdapterList::FindSubnet(TIpAddress aSubnet, const std::vector<NetworkAdapter*>& aList)
{
    for (TUint i=0; i<aList.size(); i++) {
        if (aList[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}

void NetworkAdapterList::UpdateCurrentAdapter()
{
    iCurrent = NULL;
    if (iNetworkAdapters != NULL && iNetworkAdapters->size() > 0) {
        for (TUint i=0; i<iNetworkAdapters->size(); i++) {
            NetworkAdapter* nif = (*iNetworkAdapters)[i];
            if (nif->Subnet() == iDefaultSubnet) {
                iCurrent = nif;
                break;
            }
        }
    }
}

void NetworkAdapterList::HandleInterfaceListChanged()
{
    iListLock.Wait();
    std::vector<NetworkAdapter*>* list = Os::NetworkListAdapters(Net::Stack::InitParams().UseLoopbackNetworkAdapter());
    TIpAddress oldAddress = (iCurrent==NULL? 0 : iCurrent->Address());
    DestroySubnetList(iNetworkAdapters);
    iNetworkAdapters = list;

    // update the 'current' adapter and inform observers if it has changed
    UpdateCurrentAdapter();
    TIpAddress newAddress = (iCurrent==NULL? 0 : iCurrent->Address());

    // update the subnet list, noting if it has changed
    std::vector<NetworkAdapter*>* subnets = CreateSubnetListLocked();
    TBool subnetsChanged = false;
    if (subnets->size() != iSubnets->size()) {
        subnetsChanged = true;
    }
    else {
        for (TUint i=0; i<iSubnets->size(); i++) {
            if ((*iSubnets)[i]->Address() != (*subnets)[i]->Address()) {
                subnetsChanged = true;
                break;
            }
        }
    }
    DestroySubnetList(iSubnets);
    iSubnets = subnets;
    iListLock.Signal();

    if (subnetsChanged) {
        RunCallbacks(iListenersSubnet);
    }
    else if (newAddress != oldAddress) {
        RunCallbacks(iListenersCurrent);
    }
}

void NetworkAdapterList::RunCallbacks(Map& aMap)
{
    iListenerLock.Wait();
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second();
        it++;
    }
    iListenerLock.Signal();
}
