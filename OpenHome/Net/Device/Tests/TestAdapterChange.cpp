#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Core/CpOpenhomeOrgTestBasic1.h>
#include "TestBasicDv.h"
#include <OpenHome/Net/Private/Globals.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

namespace OpenHome {
namespace TestAdapterChange {

class CpDevices
{
public:
    CpDevices(Environment& aEnv, Semaphore& aAddedSem, const Brx& aTargetUdn);
    ~CpDevices();
    void Start();
    void SetSubnet(TIpAddress aSubnet);
    void Test();
private:
    void WaitForDeviceDiscovery();
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
    void UpdatesComplete();
private:
    Mutex iLock;
    Environment& iEnv;
    std::vector<CpDevice*> iDevices;
    Semaphore& iAddedSem;
    Semaphore iUpdatesComplete;
    const Brx& iTargetUdn;
    CpDeviceListUpnpServiceType* iDeviceList;
    const TChar* iLocation;
};

} // namespace TestAdapterChange
} // namespace OpenHome

using namespace OpenHome::TestAdapterChange;

CpDevices::CpDevices(Environment& aEnv, Semaphore& aAddedSem, const Brx& aTargetUdn)
    : iLock("DLMX")
    , iEnv(aEnv)
    , iAddedSem(aAddedSem)
    , iUpdatesComplete("DSB2", 0)
    , iTargetUdn(aTargetUdn)
    , iDeviceList(NULL)
    , iLocation(NULL)
{
}

CpDevices::~CpDevices()
{
    for (TUint i=0; i<(TUint)iDevices.size(); i++) {
        iDevices[i]->RemoveRef();
    }
    iDevices.clear();
    delete iDeviceList;
}

void CpDevices::Start()
{
    FunctorCpDevice added = MakeFunctorCpDevice(*this, &CpDevices::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*this, &CpDevices::Removed);
    Brn domainName("openhome.org");
    Brn serviceType("TestBasic");
    TUint ver = 1;
    iDeviceList = new CpDeviceListUpnpServiceType(*gCpStack, domainName, serviceType, ver, added, removed);
    WaitForDeviceDiscovery();
}

void CpDevices::SetSubnet(TIpAddress aSubnet)
{
    UpnpLibrary::SetCurrentSubnet(aSubnet);
    WaitForDeviceDiscovery();
}

void CpDevices::Test()
{
    CpProxyOpenhomeOrgTestBasic1* proxy = new CpProxyOpenhomeOrgTestBasic1(*(iDevices[0]));
    Functor functor = MakeFunctor(*this, &CpDevices::UpdatesComplete);
    proxy->SetPropertyChanged(functor);
    proxy->Subscribe();
    iUpdatesComplete.Wait(); // wait for initial event

    TInt val = iEnv.Random(0x7fffffff);
    proxy->SyncSetInt(val);
    iUpdatesComplete.Wait();
    TInt propInt;
    proxy->PropertyVarInt(propInt);
    ASSERT(propInt == val);

    delete proxy; // automatically unsubscribes
}

void CpDevices::WaitForDeviceDiscovery()
{
    (void)iAddedSem.Clear();
    iAddedSem.Wait(30*1000); // allow up to 30 seconds to issue the msearch and receive a response
    // check that we not only have a device but that its at a different location from previously
    ASSERT(iDevices.size() == 1);
    CpDevice* device = iDevices[0];
    Brh locationBuf;
    ASSERT(device->GetAttribute("Upnp.Location", locationBuf));
    const TChar* location = locationBuf.Extract();
    if (iLocation != NULL) {
        ASSERT(strcmp(location, iLocation) != 0);
    }
    iLocation = location;
}

void CpDevices::Added(CpDevice& aDevice)
{
    iLock.Wait();
    if (aDevice.Udn() == iTargetUdn) {
        iDevices.push_back(&aDevice);
        aDevice.AddRef();
        iAddedSem.Signal();
    }
    iLock.Signal();
}

void CpDevices::Removed(CpDevice& aDevice)
{
    iLock.Wait();
    for (TUint i=0; i<(TUint)iDevices.size(); i++) {
        if (iDevices[i]->Udn() == aDevice.Udn()) {
            iDevices[i]->RemoveRef();
            iDevices.erase(iDevices.begin() + i);
            break;
        }
    }
    iLock.Signal();
}

void CpDevices::UpdatesComplete()
{
    iUpdatesComplete.Signal();
}


static void LogSubnet(const TChar* aPrefix, TIpAddress aSubnet)
{
    Endpoint endpt(0, aSubnet);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("%s: subnet=%s\n", aPrefix, buf.Ptr());
}

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Debug::AddLevel(Debug::kAdapterChange);
    aInitParams->SetIncludeLoopbackNetworkAdapter();
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    ASSERT(subnetList->size() > 1);
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::StartCombined(subnet);

    Semaphore* sem = new Semaphore("TEST", 0);
    DeviceBasic* dvDevice = new DeviceBasic(*gDvStack);
    CpDevices* cpDevice = new CpDevices(*gEnv, *sem, dvDevice->Udn());
    LogSubnet("Starting", subnet);
    cpDevice->Start();
    cpDevice->Test();
    subnet = (*subnetList)[1]->Subnet();
    LogSubnet("Switching", subnet);
    cpDevice->SetSubnet(subnet);
    cpDevice->Test();
    subnet = (*subnetList)[0]->Subnet();
    LogSubnet("Switching", subnet);
    cpDevice->SetSubnet(subnet);
    cpDevice->Test();
        
    delete sem;
    delete cpDevice;
    delete dvDevice;
    UpnpLibrary::DestroySubnetList(subnetList);

    UpnpLibrary::Close();
}
