/* Simple test of C APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>
#include <OpenHome/Net/C/CpDeviceUpnp.h>
#include <OpenHome/Net/C/CpUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/C/CpProxy.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Globals.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

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
    void GetProtocolInfoComplete(OhNetHandleAsync aAsync);
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


void STDCALL added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

void STDCALL removed(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}

void STDCALL getProtocolInfoComplete(void* aPtr, OhNetHandleAsync aAsync)
{
    reinterpret_cast<DeviceList*>(aPtr)->GetProtocolInfoComplete(aAsync);
}

void STDCALL initialNotificationComplete(void* aPtr)
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
    const TUint count = (TUint)iList.size();
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
    if (CpProxyUpnpOrgConnectionManager1SyncGetProtocolInfo(h, &source, &sink) == 0) {
        Print("source is %s\nsink is %s\n\n", source, sink);
    }
    else {
        Print("ERROR: invocation failed\n");
    }
    free(sink);
    free(source);
    CpProxyUpnpOrgConnectionManager1Destroy(h);
}

void DeviceList::PollInvoke()
{
    Timer timer(*gEnv, MakeFunctor(*this, &DeviceList::TimerExpired), "TestProxyC");
    for (TUint i=0; i<iList.size(); i++) {
        CpDeviceC device = iList[i];
        TUint countBefore = gActionCount;
        Print("Device %s", CpDeviceCUdn(device));
        iConnMgr = CpProxyUpnpOrgConnectionManager1Create(device);
        iStopTimeMs = Os::TimeInMs(gEnv->OsCtx()) + kDevicePollMs;
        timer.FireIn(kDevicePollMs);
        for (TUint j=0; j<gEnv->InitParams()->NumActionInvokerThreads(); j++) {
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
        CpProxySetPropertyChanged(connMgr, initialNotificationComplete, &sem);
        TUint startTime = Os::TimeInMs(gEnv->OsCtx());
        while(true) {
            CpProxySubscribe(connMgr);
            try {
                sem.Wait(kDevicePollMs);
            }
            catch(Timeout&) {}
            CpProxyUnsubscribe(connMgr);
            if (Os::TimeInMs(gEnv->OsCtx()) - startTime > kDevicePollMs) {
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
    return (TUint)iList.size();
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
    const TUint count = (TUint)iList.size();
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

void DeviceList::GetProtocolInfoComplete(OhNetHandleAsync aAsync)
{
    if (Os::TimeInMs(gEnv->OsCtx()) >= iStopTimeMs) {
        return;
    }
    CpProxyUpnpOrgConnectionManager1BeginGetProtocolInfo(iConnMgr, getProtocolInfoComplete, this);

    char* source;
    char* sink;
    if (0 != CpProxyUpnpOrgConnectionManager1EndGetProtocolInfo(iConnMgr, aAsync, &source, &sink)) {
        return;
    }
    iLock.Wait();
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
    iLock.Signal();
    free(source);
    free(sink);
}


extern "C" void OhNetTestRunner(OhNetHandleInitParams aInitParams)
{
    OhNetLibraryInitialise(aInitParams);
    OhNetHandleNetworkAdapterList subnetList = OhNetSubnetListCreate();
    OhNetHandleNetworkAdapter nif = OhNetSubnetAt(subnetList, 0);
    TUint subnet = OhNetNetworkAdapterSubnet(nif);
    TIpAddress subnetAddr = {.iFamily = kFamilyV4, .iV4 = subnet};
    OhNetSubnetListDestroy(subnetList);
    (void)OhNetLibraryStartCp(subnetAddr);
//    Debug::SetLevel(Debug::kService);

    DeviceList* deviceList = new DeviceList;
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("upnp.org", "ConnectionManager", 1,
                                                               added, deviceList, removed, deviceList);
    Blocker* blocker = new Blocker(*gEnv);
    blocker->Wait(OhNetInitParamsMsearchTimeSecs(aInitParams));
    delete blocker;
    deviceList->Stop();

    deviceList->InvokeSync();

    Print("\n\n");
    const TUint count = deviceList->Count();
    TUint startTime = Os::TimeInMs(gEnv->OsCtx());
    deviceList->PollInvoke();
    Print("\n%u actions invoked on %u devices (avg %u) in %u seconds\n\n",
                        gActionCount, count, (count==0? 0 : gActionCount/count), (Os::TimeInMs(gEnv->OsCtx())-startTime+500)/1000);

    startTime = Os::TimeInMs(gEnv->OsCtx());
    deviceList->PollSubscribe();
    Print("\n%u subscriptions on %u devices (avg %u) in %u seconds\n",
                        gSubscriptionCount, count, (count==0? 0 : gSubscriptionCount/count), (Os::TimeInMs(gEnv->OsCtx())-startTime+500)/1000);

    CpDeviceListDestroy(dlh);
    delete deviceList;

    OhNetLibraryClose();
}
