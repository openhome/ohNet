#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Stack.h>
#include <algorithm>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;


NetworkAdapterList::NetworkAdapterList(TIpAddress aDefaultSubnet)
    : iListLock("MNIL")
    , iListenerLock("MNIO")
    , iCurrent(NULL)
    , iNextListenerId(1)
{
    Net::Stack::AddObject(this);
    iDefaultSubnet = aDefaultSubnet;
    iNetworkAdapters = Os::NetworkListAdapters(Net::Stack::InitParams().UseLoopbackNetworkAdapter(), "NetworkAdapterList");
    iSubnets = CreateSubnetList();
    Os::NetworkSetInterfaceChangedObserver(&InterfaceListChanged, this);
    for (size_t i=0; i<iSubnets->size(); i++) {
        TraceAdapter("NetworkAdapter added", *(*iSubnets)[i]);
    }
}

NetworkAdapterList::~NetworkAdapterList()
{
    DestroySubnetList(iNetworkAdapters);
    DestroySubnetList(iSubnets);
    Net::Stack::RemoveObject(this);
}

NetworkAdapter* NetworkAdapterList::CurrentAdapter(const char* aCookie) const
{
    AutoMutex a(iListLock);
    if (iCurrent == NULL) {
        return NULL;
    }
    iCurrent->AddRef(aCookie);
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
            (*aList)[i]->RemoveRef("NetworkAdapterList");
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

TUint NetworkAdapterList::AddSubnetAddedListener(FunctorNetworkAdapter aFunctor)
{
    return AddSubnetListener(aFunctor, iListenersAdded);
}

void NetworkAdapterList::RemoveSubnetAddedListener(TUint aId)
{
    RemoveSubnetListener(aId, iListenersAdded);
}

TUint NetworkAdapterList::AddSubnetRemovedListener(FunctorNetworkAdapter aFunctor)
{
    return AddSubnetListener(aFunctor, iListenersRemoved);
}

void NetworkAdapterList::RemoveSubnetRemovedListener(TUint aId)
{
    RemoveSubnetListener(aId, iListenersRemoved);
}

TUint NetworkAdapterList::AddNetworkAdapterChangeListener(FunctorNetworkAdapter aFunctor)
{
    return AddSubnetListener(aFunctor, iListenersAdapterChanged);
}

void NetworkAdapterList::RemoveNetworkAdapterChangeListener(TUint aId)
{
    RemoveSubnetListener(aId, iListenersAdapterChanged);
}

// Disabled while we experiment with retrying RunCallbacks() instead
/*
void NetworkAdapterList::TempFailureRetry(Functor& aCallback)
{ // static
    static const TUint kDelaysMs[] = { 100, 200, 400, 800, 1600, 3200, 5000, 10000, 20000, 20000, 30000 }; // roughly 90s worth of retries
    for (TUint i=0; i<sizeof(kDelaysMs)/sizeof(kDelaysMs[0]); i++) {
        try {
            aCallback();
            return;
        }
        catch (NetworkError&) {
            LOG2(kNetwork, kError, "TempFailureRetry: error handling adapter change, try again in %ums\n", kDelaysMs[i]);
            Thread::Sleep(kDelaysMs[i]);
        }
    }
    THROW(NetworkError);
}
*/
std::vector<NetworkAdapter*>* NetworkAdapterList::CreateSubnetListLocked() const
{
    std::vector<NetworkAdapter*>* list = new std::vector<NetworkAdapter*>;
    for (TUint i=0; i<iNetworkAdapters->size(); i++) {
        NetworkAdapter* nif = (*iNetworkAdapters)[i];
        TIpAddress subnet = nif->Subnet();
        if (-1 == NetworkAdapterList::FindSubnet(subnet, *list)) {
            nif->AddRef("NetworkAdapterList");
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

TUint NetworkAdapterList::AddSubnetListener(FunctorNetworkAdapter aFunctor, MapNetworkAdapter& aMap)
{
    iListenerLock.Wait();
    TUint id = iNextListenerId;
    aMap.insert(std::pair<TUint,FunctorNetworkAdapter>(id, aFunctor));
    iNextListenerId++;
    iListenerLock.Signal();
    return id;
}

void NetworkAdapterList::RemoveSubnetListener(TUint aId, MapNetworkAdapter& aMap)
{
    iListenerLock.Wait();
    MapNetworkAdapter::iterator it = aMap.find(aId);
    if (it != aMap.end()) {
        aMap.erase(it);
    }
    iListenerLock.Signal();
}

void NetworkAdapterList::InterfaceListChanged(void* aPtr)
{
    try
    {
        reinterpret_cast<NetworkAdapterList*>(aPtr)->HandleInterfaceListChanged();
    }
    catch(Exception& e) {
        UnhandledExceptionHandler(e);
    }
    catch(std::exception& e) {
        UnhandledExceptionHandler(e);
    }
    catch(...) {
        UnhandledExceptionHandler( "Unknown Exception", "Unknown File", 0 );
    }
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

TBool NetworkAdapterList::CompareSubnets(NetworkAdapter* aI, NetworkAdapter* aJ)
{
    return (aI->Subnet() < aJ->Subnet());
}

void NetworkAdapterList::HandleInterfaceListChanged()
{
    iListLock.Wait();
    std::vector<NetworkAdapter*>* list = Os::NetworkListAdapters(Net::Stack::InitParams().UseLoopbackNetworkAdapter(), "NetworkAdapterList");
    TIpAddress oldAddress = (iCurrent==NULL ? 0 : iCurrent->Address());
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

    // determine adds and/or removes from list
    std::vector<NetworkAdapter*> oldSubnetsObj(iSubnets->begin(), iSubnets->end());
    std::vector<NetworkAdapter*> newSubnetsObj(subnets->begin(), subnets->end());
    std::vector<NetworkAdapter*>* oldSubnets = &oldSubnetsObj;
    std::vector<NetworkAdapter*>* newSubnets = &newSubnetsObj;
    std::vector<NetworkAdapter*> added;
    std::vector<NetworkAdapter*> removed;
    std::vector<NetworkAdapter*> adapterChanged;

    std::sort(oldSubnets->begin(), oldSubnets->end(), CompareSubnets);
    std::sort(newSubnets->begin(), newSubnets->end(), CompareSubnets);

    if (oldSubnets->size() == 0 && newSubnets->size() > 0) {
        for (TUint i=0; i < newSubnets->size(); i++) {
            added.push_back((*newSubnets)[i]);
        }
    }
    else if (oldSubnets->size() > 0 && newSubnets->size() == 0) {
        for (TUint i=0; i < oldSubnets->size(); i++) {
            removed.push_back((*oldSubnets)[i]);
        }
    }
    else {
        TUint j = 0;
        for (TUint i=0; i < newSubnets->size(); i++) {
            while (j < oldSubnets->size() && (*oldSubnets)[j]->Subnet() < (*newSubnets)[i]->Subnet()) {
                removed.push_back((*oldSubnets)[j]);
                j++;
            }
            if (j < oldSubnets->size() && (*oldSubnets)[j]->Subnet() == (*newSubnets)[i]->Subnet()) {
                if ((*oldSubnets)[j]->Address() != (*newSubnets)[i]->Address()) {
                    adapterChanged.push_back((*newSubnets)[i]);
                }
                j++;
            }
        }
        if (j < oldSubnets->size()) {
            while (j < oldSubnets->size()) {
                removed.push_back((*oldSubnets)[j]);
                j++;
            }
        }
        j = 0;
        for (TUint i=0; i < oldSubnets->size(); i++) {
            while (j < newSubnets->size() && (*newSubnets)[j]->Subnet() < (*oldSubnets)[i]->Subnet()) {
                added.push_back((*newSubnets)[j]);
                j++;
            }
            if (j < newSubnets->size() && (*newSubnets)[j]->Subnet() == (*oldSubnets)[i]->Subnet()) {
                j++;
            }
        }
        if (j < newSubnets->size()) {
            while (j < newSubnets->size()) {
                added.push_back((*newSubnets)[j]);
                j++;
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

    // Notify added/removed callbacks.
    if (removed.size() > 0) {
        for (TUint i=0; i < removed.size(); i++) {
            TraceAdapter("NetworkAdapter removed", *removed[i]);
            RunSubnetCallbacks(iListenersRemoved, *removed[i]);
        }
    }
    if (added.size() > 0) {
        for (TUint i=0; i < added.size(); i++) {
            TraceAdapter("NetworkAdapter added", *added[i]);
            RunSubnetCallbacks(iListenersAdded, *added[i]);
        }
    }

    // Notify network adapter changed callbacks.
    if (adapterChanged.size() > 0) {
        for (TUint i=0; i < adapterChanged.size(); i++) {
            TraceAdapter("NetworkAdapter changed", *adapterChanged[i]);
            RunSubnetCallbacks(iListenersAdapterChanged, *adapterChanged[i]);
        }
    }
}

void NetworkAdapterList::RunCallbacks(Map& aMap)
{
    static const TUint kDelaysMs[] = { 100, 200, 400, 800, 1600, 3200, 5000, 10000, 20000, 20000, 30000 }; // roughly 90s worth of retries
    for (TUint i=0; i<sizeof(kDelaysMs)/sizeof(kDelaysMs[0]); i++) {
        try {
            DoRunCallbacks(aMap);
            return;
        }
        catch (NetworkError&) {
            LOG2(kNetwork, kError, "TempFailureRetry: error handling adapter change, try again in %ums\n", kDelaysMs[i]);
            Thread::Sleep(kDelaysMs[i]);
        }
    }
    THROW(NetworkError);

}

void NetworkAdapterList::DoRunCallbacks(Map& aMap)
{
    iListenerLock.Wait();
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second();
        it++;
    }
    iListenerLock.Signal();
}

void NetworkAdapterList::RunSubnetCallbacks(MapNetworkAdapter& aMap, NetworkAdapter& aAdapter)
{
    iListenerLock.Wait();
    MapNetworkAdapter::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second(aAdapter);
        it++;
    }
    iListenerLock.Signal();
}

void NetworkAdapterList::TraceAdapter(const TChar* aPrefix, NetworkAdapter& aAdapter)
{ // static
    Endpoint ep(0, aAdapter.Address());
    Bws<Endpoint::kMaxAddressBytes> addr;
    ep.AppendAddress(addr);
    LOG(kTrace, "%s: %s(%s)\n", aPrefix, aAdapter.Name(), (const TChar*)addr.Ptr());
}

void NetworkAdapterList::ListObjectDetails() const
{
    Log::Print("  NetworkAdapterList: addr=%p\n", this);
}
