// Test for service subscription
// Builds a list of providers of the (ohNet) UI service
// ... then checks how many times we can (un)subscribe (to changes in the
//     service's state variables) on each device in a second

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Core/CpUpnpOrgConnectionManager1.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

const TUint kDevicePollMs = 1000;
static TUint gSubscriptionCount = 0;

class DeviceList
{
public:
    DeviceList(Environment& aEnv);
    ~DeviceList();
    void Stop();
    void Poll();
    TUint Count() const;
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void InitialNotificationComplete();
private:
    Environment& iEnv;
    Mutex iLock;
    std::vector<CpDevice*> iList;
    TBool iStopped;
    Semaphore iSem;
};


DeviceList::DeviceList(Environment& aEnv)
    : iEnv(aEnv)
    , iLock("DLMX")
    , iStopped(false)
    , iSem("DLSM", 0)
{
}

DeviceList::~DeviceList()
{
    const TUint count = (TUint)iList.size();
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
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        TUint countBefore = gSubscriptionCount;
        Print("Device ");
        Print(device->Udn());
        CpProxyUpnpOrgConnectionManager1* connMgr = new CpProxyUpnpOrgConnectionManager1(*device);
        connMgr->SetPropertyChanged(updatesComplete);
        TUint startTime = Os::TimeInMs(iEnv.OsCtx());
        while(true) {
            iSem.Clear();
            connMgr->Subscribe();
            try {
                iSem.Wait(kDevicePollMs+1);
            }
            catch(Timeout&) {}
            connMgr->Unsubscribe();
            if (Os::TimeInMs(iEnv.OsCtx()) - startTime > kDevicePollMs) {
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
    return (TUint)iList.size();
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
    const TUint count = (TUint)iList.size();
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


void TestSubscription(CpStack& aCpStack)
{
    gSubscriptionCount = 0; // reset this here in case we're run multiple times via TestShell
    Debug::SetLevel(Debug::kNone);
    Environment& env = aCpStack.Env();
    DeviceList* deviceList = new DeviceList(env);
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &DeviceList::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &DeviceList::Removed);
    const Brn domainName("upnp.org");
    const Brn serviceType("ConnectionManager");
#if 1
    const TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(aCpStack, domainName, serviceType, ver, added, removed);
#else
    const Brn uuid("896659847466-a4badbeaacbc-737837");
    CpDeviceListUpnpUuid* list = new CpDeviceListUpnpUuid(aCpStack, uuid, added, removed);
#endif
    Blocker* blocker = new Blocker(env);
    blocker->Wait(env.InitParams()->MsearchTimeSecs());
    delete blocker;
    deviceList->Stop();

    TUint startTime = Os::TimeInMs(env.OsCtx());
    deviceList->Poll();

    const TUint count = deviceList->Count();
    Print("\n%u subscriptions on %u devices (avg %u) in %u seconds\n",
                        gSubscriptionCount, count, (count==0? 0 : gSubscriptionCount/count), (Os::TimeInMs(env.OsCtx())-startTime+500)/1000);

    delete list;
    delete deviceList;
}
