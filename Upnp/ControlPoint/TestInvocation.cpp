// Test for service/action invocation
// Builds a list of providers of the ConnectionManager service
// ... then checks how many times GetProtocolInfo can be run on each device in a second

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
static TUint gActionCount = 0;


// very basic example
class DeviceList
{
public:
    DeviceList();
    ~DeviceList();
    void Stop();
    void TestSync();
    void Poll();
    TUint Count() const;
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void TimerExpired();
    void GetProtocolInfoComplete(IAsync& aAsync);
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    TBool iStopped;
    Semaphore iPollStop;
    TUint iStopTimeMs;
    CpProxyUpnpOrgConnectionManager1* iConnMgr;
    Brh iExpectedSink;
};


DeviceList::DeviceList()
    : iLock("DLMX")
    , iStopped(false)
    , iPollStop("SDPS", 0)
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

void DeviceList::TestSync()
{
    // trivial validation of the sync wrappers to all APIs
    // single sync call to whichever device happens to be first in our list
    if (iList.size() == 0) {
        Print("No devices found, so nothing to test\n");
        return;
    }
    CpDevice* device = iList[0];
    Print("Sync call to device ");
    Print(device->Udn());
    Print("\n");
    iConnMgr = new CpProxyUpnpOrgConnectionManager1(*device);
    Brh source;
    Brh sink;
    try {
        iConnMgr->SyncGetProtocolInfo(source, sink);
    }
    catch(ProxyError) {}
#if 0
    Print("source is ");
    Print(source);
    Print("\nsink is ");
    Print(sink);
    Print("\n");
#endif
    delete iConnMgr;
}

void DeviceList::Poll()
{
    Timer timer(MakeFunctor(*this, &DeviceList::TimerExpired));
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceList::GetProtocolInfoComplete);
    Brh tmp;
    const TUint count = iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        TUint countBefore = gActionCount;
        Print("Device ");
        Print(device->Udn());
        iConnMgr = new CpProxyUpnpOrgConnectionManager1(*device);
        iStopTimeMs = Os::TimeInMs() + kDevicePollMs;
        timer.FireIn(kDevicePollMs);
        for (TUint j=0; j<Stack::InitParams().NumActionInvokerThreads(); j++) {
            iConnMgr->BeginGetProtocolInfo(callback);
        }
        iPollStop.Wait();
        Print("    %u\n", gActionCount - countBefore);
        delete iConnMgr;
        iExpectedSink.TransferTo(tmp);
    }
}

TUint DeviceList::Count() const
{
    return iList.size();
}

void DeviceList::TimerExpired()
{
    iPollStop.Signal();
}

void DeviceList::GetProtocolInfoComplete(IAsync& aAsync)
{
    if (Os::TimeInMs() > iStopTimeMs) {
        return;
    }
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceList::GetProtocolInfoComplete);
    iConnMgr->BeginGetProtocolInfo(callback);

    Brh source;
    Brh sink;
    iConnMgr->EndGetProtocolInfo(aAsync, source, sink); // throws if invocation failed
    gActionCount++;
    if (sink.Bytes() == 0) {
        ASSERT(iExpectedSink.Bytes() == 0);
    }
    else {
        if (iExpectedSink.Bytes() == 0) {
            sink.TransferTo(iExpectedSink);
        }
        else {
            ASSERT(sink == iExpectedSink);
        }
    }
}

void DeviceList::Added(CpDevice& aDevice)
{
    AutoMutex a(iLock);
    if (!iStopped) {
        iList.push_back(&aDevice);
        ASSERT(aDevice==aDevice);
        ASSERT(!(aDevice!=aDevice));
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
    FunctorAsync dummy;
    /* Set an empty handler for errors to avoid test output being swamped by expected
       errors from invocations we interrupt at the end of each device's 1s timeslice */
    aInitParams->SetAsyncErrorHandler(dummy);
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
    const Brn uuid("7076436f-6e65-1063-8074-000da201f542");
    CpDeviceListUpnpUuid* list = new CpDeviceListUpnpUuid(uuid, added, removed);
#endif
    Blocker* blocker = new Blocker;
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    deviceList->Stop();

    TUint startTime = Os::TimeInMs();
    //deviceList->TestSync();
    deviceList->Poll();

    const TUint count = deviceList->Count();
    Print("\n%u actions invoked on %u devices (avg %u) in %u seconds\n",
                        gActionCount, count, (count==0? 0 : gActionCount/count), (Os::TimeInMs()-startTime+500)/1000);

    delete list;
    delete deviceList;

    UpnpLibrary::Close();
}
