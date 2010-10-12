/* Simple test of C APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/Zapp.h>
#include <C/CpDevice.h>
#include <C/CpDeviceUpnp.h>
#include <C/CpUpnpOrgConnectionManager1.h>
#include <C/CpProxy.h>
#include <C/Async.h>
#include <ZappTypes.h>
#include <TestFramework.h>
#include <Os.h>
#include <Thread.h>
#include <Stack.h>
#include <Debug.h>

#include <stdlib.h>
#include <string.h>

using namespace Zapp;
using namespace Zapp::TestFramework;

const TUint kDevicePollMs = 1000;
static TUint gActionCount = 0;
static TUint gSubscriptionCount = 0;

class DeviceList
{
public:
    DeviceList();
    ~DeviceList();
    void Stop();
    void InvokeSync();
    void PollInvoke();
    void PollSubscribe();
    TUint Count() const;
    void Added(CpDeviceC aDevice);
    void Removed(CpDeviceC aDevice);
    void GetProtocolInfoComplete(ZappHandleAsync aAsync);
private:
    void TimerExpired();
private:
    Mutex iLock;
    std::vector<CpDeviceC> iList;
    TBool iStopped;

    // for PollInvoke
    Semaphore iPollStop;
    TUint iStopTimeMs;
    THandle iConnMgr;
    char* iExpectedSink;
};


void added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

void removed(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}

void getProtocolInfoComplete(void* aPtr, ZappHandleAsync aAsync)
{
    reinterpret_cast<DeviceList*>(aPtr)->GetProtocolInfoComplete(aAsync);
}

void initialNotificationComplete(void* aPtr)
{
    reinterpret_cast<Semaphore*>(aPtr)->Signal();
}


DeviceList::DeviceList()
    : iLock("DLMX")
    , iStopped(false)
    , iPollStop("SDPS", 0)
	, iExpectedSink(NULL)
{
}

DeviceList::~DeviceList()
{
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        CpDeviceCRemoveRef(iList[i]);
    }
}

void DeviceList::Stop()
{
    iStopped = true;
}

void DeviceList::InvokeSync()
{
    // trivial validation of the sync wrappers to all APIs
    // single sync call to whichever device happens to be first in our list
    if (iList.size() == 0) {
        Print("No devices found, so nothing to test\n");
        return;
    }
    CpDeviceC device = iList[0];
    Print("Sync call to device %s\n", CpDeviceCUdn(device));
    THandle h = CpProxyUpnpOrgConnectionManager1Create(device);
    char* source;
    char* sink;
    CpProxyUpnpOrgConnectionManager1SyncGetProtocolInfo(h, &source, &sink);
    Print("source is %s\nsink is %s\n\n", source, sink);
    free(sink);
    free(source);
    CpProxyUpnpOrgConnectionManager1Destroy(h);
}

void DeviceList::PollInvoke()
{
    Timer timer(MakeFunctor(*this, &DeviceList::TimerExpired));
    for (TUint i=0; i<iList.size(); i++) {
        CpDeviceC device = iList[i];
        TUint countBefore = gActionCount;
        Print("Device %s", CpDeviceCUdn(device));
        iConnMgr = CpProxyUpnpOrgConnectionManager1Create(device);
        iStopTimeMs = Os::TimeInMs() + kDevicePollMs;
        timer.FireIn(kDevicePollMs);
        for (TUint j=0; j<Stack::InitParams().NumActionInvokerThreads(); j++) {
            CpProxyUpnpOrgConnectionManager1BeginGetProtocolInfo(iConnMgr, getProtocolInfoComplete, this);
        }
        iPollStop.Wait();
        Print("    %u\n", gActionCount - countBefore);
        CpProxyUpnpOrgConnectionManager1Destroy(iConnMgr);
        free(iExpectedSink);
        iExpectedSink = NULL;
    }
}

void DeviceList::PollSubscribe()
{
    Semaphore sem("DLSM", 0);
    for (TUint i=0; i<iList.size(); i++) {
        CpDeviceC device = iList[i];
        TUint countBefore = gSubscriptionCount;
        Print("Device %s", CpDeviceCUdn(device));
        THandle connMgr = CpProxyUpnpOrgConnectionManager1Create(device);
        CpProxyCSetPropertyChanged(connMgr, initialNotificationComplete, &sem);
        TUint startTime = Os::TimeInMs();
        while(true) {
            CpProxyCSubscribe(connMgr);
            try {
                sem.Wait(kDevicePollMs);
            }
            catch(Timeout&) {}
            CpProxyCUnsubscribe(connMgr);
            if (Os::TimeInMs() - startTime > kDevicePollMs) {
                break;
            }
            gSubscriptionCount++;
        }
        Print("    %u\n", gSubscriptionCount - countBefore);
        CpProxyUpnpOrgConnectionManager1Destroy(connMgr);
    }
}

TUint DeviceList::Count() const
{
    return iList.size();
}

void DeviceList::Added(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    if (!iStopped) {
        iList.push_back(aDevice);
        CpDeviceCAddRef(aDevice);
    }
}

void DeviceList::Removed(CpDeviceC aDevice)
{
    if (iStopped) {
        return;
    }

    AutoMutex a(iLock);
    const TUint count = iList.size();
    const char* udn = CpDeviceCUdn(aDevice);
    for (TUint i=0; i<count; i++) {
        CpDeviceC device = iList[i];
        if (0 == strcmp(CpDeviceCUdn(device), udn)) {
            iList.erase(iList.begin()+i);
            CpDeviceCRemoveRef(device);
            break;
        }
    }
}

void DeviceList::TimerExpired()
{
    iPollStop.Signal();
}

void DeviceList::GetProtocolInfoComplete(ZappHandleAsync aAsync)
{
    if (Os::TimeInMs() >= iStopTimeMs) {
        return;
    }
    CpProxyUpnpOrgConnectionManager1BeginGetProtocolInfo(iConnMgr, getProtocolInfoComplete, this);

    char* source;
    char* sink;
    if (0 != CpProxyUpnpOrgConnectionManager1EndGetProtocolInfo(iConnMgr, aAsync, &source, &sink)) {
        return;
    }
    gActionCount++;
    if (sink == NULL) {
        ASSERT(iExpectedSink == NULL);
    }
    else {
        if (iExpectedSink == NULL) {
            iExpectedSink = sink;
            sink = NULL;
        }
        else {
            if (0 != strcmp(sink, iExpectedSink)) {
                Print("Expected %s\n...got %s\n", (iExpectedSink? iExpectedSink : "(null)"), (sink? sink : "(null)"));
            }
        }
    }
    free(source);
    free(sink);
}


extern "C" void ZappTestRunner(ZappHandleInitParams aInitParams)
{
    ZappLibraryInitialise(aInitParams);
    ZappLibraryStartCp();
//    Debug::SetLevel(Debug::kService);

    DeviceList* deviceList = new DeviceList;
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("upnp.org", "ConnectionManager", 1,
                                                               added, deviceList, removed, deviceList);
    Blocker* blocker = new Blocker;
    blocker->Wait(ZappInitParamsMsearchTimeSecs(aInitParams));
    delete blocker;
    deviceList->Stop();

    deviceList->InvokeSync();

    Print("\n\n");
    const TUint count = deviceList->Count();
    TUint startTime = Os::TimeInMs();
    deviceList->PollInvoke();
    Print("\n%u actions invoked on %u devices (avg %u) in %u seconds\n\n",
                        gActionCount, count, (count==0? 0 : gActionCount/count), (Os::TimeInMs()-startTime+500)/1000);

    startTime = Os::TimeInMs();
    deviceList->PollSubscribe();
    Print("\n%u subscriptions on %u devices (avg %u) in %u seconds\n",
                        gSubscriptionCount, count, (count==0? 0 : gSubscriptionCount/count), (Os::TimeInMs()-startTime+500)/1000);

    CpDeviceListDestroy(dlh);
    delete deviceList;

    ZappLibraryClose();
}
