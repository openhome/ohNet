// Test for service/action invocation
// Builds a list of providers of the ConnectionManager service
// ... then checks how many times GetProtocolInfo can be run on each device in a second

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Cpp/CpDeviceUpnp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Cpp/FunctorCpDevice.h>
#include <OpenHome/Net/Cpp/CpUpnpOrgConnectionManager1.h>
#include <OpenHome/Net/Private/Globals.h>

#include <string>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

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
    void Added(CpDeviceCpp& aDevice);
    void Removed(CpDeviceCpp& aDevice);
private:
    void TimerExpired();
    void GetProtocolInfoComplete(IAsync& aAsync);
private:
    Mutex iLock;
    std::vector<CpDeviceCpp*> iList;
    TBool iStopped;
    Semaphore iPollStop;
    TUint iStopTimeMs;
    CpProxyUpnpOrgConnectionManager1Cpp* iConnMgr;
    std::string iExpectedSink;
};


DeviceList::DeviceList()
    : iLock("DLMX")
    , iStopped(false)
    , iPollStop("SDPS", 0)
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

void DeviceList::TestSync()
{
    // trivial validation of the sync wrappers to all APIs
    // single sync call to whichever device happens to be first in our list
    if (iList.size() == 0) {
        Print("No devices found, so nothing to test\n");
        return;
    }
    CpDeviceCpp* device = iList[0];
    Print("Sync call to device %s\n", device->Udn().c_str());
    CpProxyUpnpOrgConnectionManager1Cpp* connMgr = new CpProxyUpnpOrgConnectionManager1Cpp(*device);
    std::string source;
    std::string sink;
    try {
        connMgr->SyncGetProtocolInfo(source, sink);
    }
    catch(ProxyError) {}
#if 1
    Print("source is %s\nsink is %s\n", source.c_str(), sink.c_str());
#endif
    delete connMgr;

}

void DeviceList::Poll()
{
    Timer timer(*gEnv, MakeFunctor(*this, &DeviceList::TimerExpired), "TestInvocationStd");
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceList::GetProtocolInfoComplete);
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDeviceCpp* device = iList[i];
        TUint countBefore = gActionCount;
        Print("Device %s", device->Udn().c_str());
        iConnMgr = new CpProxyUpnpOrgConnectionManager1Cpp(*device);
        iStopTimeMs = Os::TimeInMs(gEnv->OsCtx()) + kDevicePollMs;
        timer.FireIn(kDevicePollMs);
        for (TUint j=0; j<gEnv->InitParams()->NumActionInvokerThreads(); j++) {
            iConnMgr->BeginGetProtocolInfo(callback);
        }
        iPollStop.Wait();
        Print("    %u\n", gActionCount - countBefore);
        delete iConnMgr;
        iExpectedSink.clear();
    }
}

TUint DeviceList::Count() const
{
    return (TUint)iList.size();
}

void DeviceList::TimerExpired()
{
    iPollStop.Signal();
}

void DeviceList::GetProtocolInfoComplete(IAsync& aAsync)
{
    if (Os::TimeInMs(gEnv->OsCtx()) > iStopTimeMs) {
        return;
    }
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceList::GetProtocolInfoComplete);
    iConnMgr->BeginGetProtocolInfo(callback);

    std::string source;
    std::string sink;
    iConnMgr->EndGetProtocolInfo(aAsync, source, sink); // throws if invocation failed
    iLock.Wait();
    gActionCount++;
    if (sink.length() == 0) {
        ASSERT(iExpectedSink.length() == 0);
    }
    else {
        if (iExpectedSink.length() == 0) {
            iExpectedSink.assign(sink);
        }
        else {
            //ASSERT(sink.compare(iExpectedSink) == 0);
            // can't use the above assertion.  aVia Media Renderer sometimes responds with two copies of its supported protocols
        }
    }
    iLock.Signal();
}

void DeviceList::Added(CpDeviceCpp& aDevice)
{
    AutoMutex a(iLock);
    if (!iStopped) {
        iList.push_back(&aDevice);
        ASSERT(aDevice==aDevice);
        ASSERT(!(aDevice!=aDevice));
        aDevice.AddRef();
    }
}

void DeviceList::Removed(CpDeviceCpp& aDevice)
{
    if (iStopped) {
        return;
    }

    AutoMutex a(iLock);
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDeviceCpp* device = iList[i];
        if (device->Udn() == aDevice.Udn()) {
            iList[i] = NULL;
            iList.erase(iList.begin()+i);
            device->RemoveRef();
            break;
        }
    }
}


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    FunctorAsync dummy;
    /* Set an empty handler for errors to avoid test output being swamped by expected
       errors from invocations we interrupt at the end of each device's 1s timeslice */
    aInitParams->SetAsyncErrorHandler(dummy);
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    Debug::SetLevel(Debug::kNone);
    DeviceList* deviceList = new DeviceList;
    FunctorCpDeviceCpp added = MakeFunctorCpDeviceCpp(*deviceList, &DeviceList::Added);
    FunctorCpDeviceCpp removed = MakeFunctorCpDeviceCpp(*deviceList, &DeviceList::Removed);
    std::string domainName("upnp.org");
    std::string serviceType("ConnectionManager");
#if 1
    const TUint ver = 1;
    CpDeviceListCppUpnpServiceType* list =
                new CpDeviceListCppUpnpServiceType(domainName, serviceType, ver, added, removed);
#else
    const std::string uuid("896659847466-8000600fe800-737837");
    CpDeviceListCppUpnpUuid* list = new CpDeviceListCppUpnpUuid(uuid, added, removed);
#endif
    Blocker* blocker = new Blocker(*gEnv);
    blocker->Wait(aInitParams->MsearchTimeSecs());
    delete blocker;
    deviceList->Stop();

    TUint startTime = Os::TimeInMs(gEnv->OsCtx());
    deviceList->TestSync();
    deviceList->Poll();

    const TUint count = deviceList->Count();
    Print("\n%u actions invoked on %u devices (avg %u) in %u seconds\n",
                        gActionCount, count, (count==0? 0 : gActionCount/count), (Os::TimeInMs(gEnv->OsCtx())-startTime+500)/1000);

    delete list;
    delete deviceList;

    UpnpLibrary::Close();
}
