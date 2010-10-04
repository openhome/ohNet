// Test for service subscription
// Builds a list of providers of the (Zapp) UI service
// ... then checks how many times we can (un)subscribe (to changes in the
//     service's state variables) on each device in a second

#include <TestFramework.h>
#include <ZappTypes.h>
#include <Discovery.h>
#include <Thread.h>
#include <Timer.h>
#include <Core/CpDevice.h>
#include <Core/CpDeviceUpnp.h>
#include <Stack.h>
#include <Os.h>
#include <Core/FunctorCpDevice.h>
#include <Core/CpUpnpOrgConnectionManager1.h>

#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;

const TUint kDevicePollMs = 1000;
static TUint gSubscriptionCount = 0;

class DeviceList
{
public:
    DeviceList();
    ~DeviceList();
    void Stop();
    void Poll();
    TUint Count() const;
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void InitialNotificationComplete();
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    TBool iStopped;
    Semaphore iSem;
};


DeviceList::DeviceList()
    : iLock("DLMX")
    , iStopped(false)
    , iSem("DLSM", 0)
{
}

DeviceList::~DeviceList()
{
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
        iList[i] = NULL;
    }
}

void DeviceList::Stop()
{
    iStopped = true;
}

void DeviceList::Poll()
{
    Functor updatesComplete = MakeFunctor(*this, &DeviceList::InitialNotificationComplete);
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        TUint countBefore = gSubscriptionCount;
        Print("Device ");
        Print(device->Udn());
        CpProxyUpnpOrgConnectionManager1* connMgr = new CpProxyUpnpOrgConnectionManager1(*device);
        connMgr->SetPropertyChanged(updatesComplete);
        TUint startTime = Os::TimeInMs();
        while(true) {
            iSem.Clear();
            connMgr->Subscribe();
            try {
                iSem.Wait(kDevicePollMs+1);
            }
            catch(Timeout&) {}
            connMgr->Unsubscribe();
            if (Os::TimeInMs() - startTime > kDevicePollMs) {
                break;
            }
            gSubscriptionCount++;
        }
        Print("    %u\n", gSubscriptionCount - countBefore);
        delete connMgr;
    }
}

TUint DeviceList::Count() const
{
    return iList.size();
}

void DeviceList::InitialNotificationComplete()
{
    iSem.Signal();
}

void DeviceList::Added(CpDevice& aDevice)
{
    AutoMutex a(iLock);
    if (!iStopped) {
        iList.push_back(&aDevice);
        aDevice.AddRef();
    }
}

void DeviceList::Removed(CpDevice& aDevice)
{
    if (iStopped) {
        return;
    }

    AutoMutex a(iLock);
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        if (device->Udn() == aDevice.Udn()) {
            iList[i] = NULL;
            iList.erase(iList.begin()+i);
            device->RemoveRef();
            break;
        }
    }
}


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCp();

    Debug::SetLevel(Debug::kNone);
    DeviceList* deviceList = new DeviceList;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &DeviceList::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &DeviceList::Removed);
    const Brn domainName("upnp.org");
    const Brn serviceType("ConnectionManager");
#if 1
    const TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
#else
    const Brn uuid("896659847466-a4badbeaacbc-737837");
    CpDeviceListUpnpUuid* list = new CpDeviceListUpnpUuid(uuid, added, removed);
#endif
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    deviceList->Stop();

    TUint startTime = Os::TimeInMs();
    deviceList->Poll();

    const TUint count = deviceList->Count();
    Print("\n%u subscriptions on %u devices (avg %u) in %u seconds\n",
                        gSubscriptionCount, count, (count==0? 0 : gSubscriptionCount/count), (Os::TimeInMs()-startTime+500)/1000);

    delete list;
    delete deviceList;

    UpnpLibrary::Close();
}
