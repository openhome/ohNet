#include <NetworkInterfaceList.h>
#include <ZappTypes.h>
#include <Os.h>
#include <Thread.h>

using namespace Zapp;


NetworkInterfaceList::NetworkInterfaceList(TIpAddress aDefaultSubnet)
    : iListLock("MNIL")
    , iListenerLock("MNIO")
    , iNextListenerId(0)
{
    iDefaultSubnet = aDefaultSubnet;
    iNetworkInterfaces = Os::NetworkListInterfaces();
    iSubnets = CreateSubnetList();
    UpdateCurrentInterface();
    Os::NetworkSetInterfaceChangedObserver(&InterfaceListChanged, this);
}

NetworkInterfaceList::~NetworkInterfaceList()
{
    ClearInterfaces(iNetworkInterfaces);
    ClearInterfaces(iSubnets);
}

NetworkInterface* NetworkInterfaceList::CurrentInterface() const
{
    NetworkInterface* ret = NULL;
    iListLock.Wait();
    ret = (iCurrent==NULL? NULL : iCurrent->Clone());
    iListLock.Signal();
    return ret;
}

const std::vector<NetworkInterface*>& NetworkInterfaceList::List() const
{
    return *iNetworkInterfaces;
}

std::vector<NetworkInterface*>* NetworkInterfaceList::CreateSubnetList() const
{
    iListLock.Wait();
    std::vector<NetworkInterface*>* list = CreateSubnetListLocked();
    iListLock.Signal();
    return list;
}

void NetworkInterfaceList::DestroySubnetList(std::vector<NetworkInterface*>* aList)
{
    for (TUint i=0; i<aList->size(); i++) {
        delete (*aList)[i];
    }
    delete aList;
}

void NetworkInterfaceList::SetCurrentSubnet(const NetworkInterface& aSubnet)
{
    SetDefaultSubnet(&aSubnet);
}

void NetworkInterfaceList::ClearCurrentSubnet()
{
    SetDefaultSubnet(NULL);
}

TUint NetworkInterfaceList::AddCurrentChangeListener(Functor aFunctor)
{
    return AddListener(aFunctor, iListenersCurrent);
}

void NetworkInterfaceList::RemoveCurrentChangeListener(TUint aId)
{
    RemoveSubnetChangeListener(aId, iListenersCurrent);
}

TUint NetworkInterfaceList::AddSubnetChangeListener(Functor aFunctor)
{
    return AddListener(aFunctor, iListenersSubnet);
}

void NetworkInterfaceList::RemoveSubnetChangeListener(TUint aId)
{
    RemoveSubnetChangeListener(aId, iListenersSubnet);
}

void NetworkInterfaceList::SetDefaultSubnet(const NetworkInterface* aSubnet)
{
    iListLock.Wait();
    TIpAddress oldSubnet = (iCurrent==NULL? 0 : iCurrent->Subnet());
    iDefaultSubnet = (aSubnet==NULL? 0 : aSubnet->Subnet());
    UpdateCurrentInterface();
    TIpAddress newSubnet = (iCurrent==NULL? 0 : iCurrent->Subnet());
    iListLock.Signal();
    if (newSubnet != oldSubnet) {
        RunCallbacks(iListenersCurrent);
    }
}

std::vector<NetworkInterface*>* NetworkInterfaceList::CreateSubnetListLocked() const
{
    std::vector<NetworkInterface*>* list = new std::vector<NetworkInterface*>;
    for (TUint i=0; i<iNetworkInterfaces->size(); i++) {
        const NetworkInterface* nif = (*iNetworkInterfaces)[i];
        TIpAddress subnet = nif->Subnet();
        if (-1 == NetworkInterfaceList::FindSubnet(subnet, *list)) {
            list->push_back(nif->Clone());
        }
    }
    return list;
}

TUint NetworkInterfaceList::AddListener(Functor aFunctor, Map& aMap)
{
    iListenerLock.Wait();
    TUint id = iNextListenerId;
    aMap.insert(std::pair<TUint,Functor>(id, aFunctor));
    iNextListenerId++;
    iListenerLock.Signal();
    return id;
}

void NetworkInterfaceList::RemoveSubnetChangeListener(TUint aId, Map& aMap)
{
    iListenerLock.Wait();
    Map::iterator it = aMap.find(aId);
    if (it != aMap.end()) {
        aMap.erase(it);
    }
    iListenerLock.Signal();
}

void NetworkInterfaceList::InterfaceListChanged(void* aPtr)
{
    reinterpret_cast<NetworkInterfaceList*>(aPtr)->HandleInterfaceListChanged();
}

TInt NetworkInterfaceList::FindSubnet(TIpAddress aSubnet, const std::vector<NetworkInterface*>& aList)
{
    for (TUint i=0; i<aList.size(); i++) {
        if (aList[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}

void NetworkInterfaceList::UpdateCurrentInterface()
{
    iCurrent = NULL;
    if (iNetworkInterfaces != NULL && iNetworkInterfaces->size() > 0) {
        if (iDefaultSubnet == 0) {
            iCurrent = (*iNetworkInterfaces)[0];
        }
        else {
            for (TUint i=0; i<iNetworkInterfaces->size(); i++) {
                const NetworkInterface* nif = (*iNetworkInterfaces)[i];
                if (nif->Subnet() == iDefaultSubnet) {
                    iCurrent = nif;
                    break;
                }
            }
        }
    }
}

void NetworkInterfaceList::HandleInterfaceListChanged()
{
    iListLock.Wait();
    std::vector<NetworkInterface*>* list = Os::NetworkListInterfaces();
    TIpAddress oldAddress = (iCurrent==NULL? 0 : iCurrent->Address());
    ClearInterfaces(iNetworkInterfaces);
    iNetworkInterfaces = list;

    // update the 'current' interface and inform observers if it has changed
    UpdateCurrentInterface();
    TIpAddress newAddress = (iCurrent==NULL? 0 : iCurrent->Address());

    // update the subnet list, noting if it has changed
    std::vector<NetworkInterface*>* subnets = CreateSubnetListLocked();
    TBool subnetsChanged = false;
    if (subnets->size() != iSubnets->size()) {
        subnetsChanged = true;
    }
    else {
        for (TUint i=0; i<iSubnets->size(); i++) {
            if ((*iSubnets)[i]->Subnet() != (*subnets)[i]->Subnet()) {
                subnetsChanged = true;
                break;
            }
        }
    }
    ClearInterfaces(iSubnets);
    iSubnets = subnets;
    iListLock.Signal();

    if (subnetsChanged) {
        RunCallbacks(iListenersSubnet);
    }
    else if (newAddress != oldAddress) {
        RunCallbacks(iListenersCurrent);
    }
}

void NetworkInterfaceList::RunCallbacks(Map& aMap)
{
    iListenerLock.Wait();
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second();
        it++;
    }
    iListenerLock.Signal();
}

void NetworkInterfaceList::ClearInterfaces(std::vector<NetworkInterface*>* aList)
{
    if (aList != NULL) {
        for (TUint i=0; i<aList->size(); i++) {
            delete (*aList)[i];
        }
        delete aList;
    }
}
