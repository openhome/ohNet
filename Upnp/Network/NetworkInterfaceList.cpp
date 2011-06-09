#include <NetworkInterfaceList.h>
#include <OhNetTypes.h>
#include <OsWrapper.h>
#include <Thread.h>
#include <Stack.h>

using namespace OpenHome;


NetworkInterfaceList::NetworkInterfaceList(TIpAddress aDefaultSubnet)
    : iListLock("MNIL")
    , iListenerLock("MNIO")
    , iCurrent(NULL)
    , iNextListenerId(1)
{
    Net::Stack::AddObject(this, "NetworkInterfaceList");
    iDefaultSubnet = aDefaultSubnet;
    iNetworkInterfaces = Os::NetworkListInterfaces(Net::Stack::InitParams().UseLoopbackNetworkInterface());
    iSubnets = CreateSubnetList();
    Os::NetworkSetInterfaceChangedObserver(&InterfaceListChanged, this);
}

NetworkInterfaceList::~NetworkInterfaceList()
{
    DestroySubnetList(iNetworkInterfaces);
    DestroySubnetList(iSubnets);
    Net::Stack::RemoveObject(this, "NetworkInterfaceList");
}

NetworkInterface* NetworkInterfaceList::CurrentInterface() const
{
    AutoMutex a(iListLock);
    if (iCurrent == NULL) {
        return NULL;
    }
    iCurrent->AddRef();
    return iCurrent;
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
    if (aList != NULL) {
        for (TUint i=0; i<aList->size(); i++) {
            (*aList)[i]->RemoveRef();
        }
        delete aList;
    }
}

void NetworkInterfaceList::SetCurrentSubnet(TIpAddress aSubnet)
{
    iListLock.Wait();
    TIpAddress oldSubnet = (iCurrent==NULL? 0 : iCurrent->Subnet());
    iDefaultSubnet = aSubnet;
    UpdateCurrentInterface();
    iListLock.Signal();
    if (aSubnet != oldSubnet) {
        RunCallbacks(iListenersCurrent);
    }
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

std::vector<NetworkInterface*>* NetworkInterfaceList::CreateSubnetListLocked() const
{
    std::vector<NetworkInterface*>* list = new std::vector<NetworkInterface*>;
    for (TUint i=0; i<iNetworkInterfaces->size(); i++) {
        NetworkInterface* nif = (*iNetworkInterfaces)[i];
        TIpAddress subnet = nif->Subnet();
        if (-1 == NetworkInterfaceList::FindSubnet(subnet, *list)) {
            nif->AddRef();
            list->push_back(nif);
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
        for (TUint i=0; i<iNetworkInterfaces->size(); i++) {
            NetworkInterface* nif = (*iNetworkInterfaces)[i];
            if (nif->Subnet() == iDefaultSubnet) {
                iCurrent = nif;
                break;
            }
        }
    }
}

void NetworkInterfaceList::HandleInterfaceListChanged()
{
    iListLock.Wait();
    std::vector<NetworkInterface*>* list = Os::NetworkListInterfaces(Net::Stack::InitParams().UseLoopbackNetworkInterface());
    TIpAddress oldAddress = (iCurrent==NULL? 0 : iCurrent->Address());
    DestroySubnetList(iNetworkInterfaces);
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
