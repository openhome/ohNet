/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/C/CpStack.h>
#include <OpenHome/Net/C/DvStack.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/C/DvOpenhomeOrgTestBasic1.h>
#include <OpenHome/Net/C/CpOpenhomeOrgTestBasic1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Debug.h>
#include "TestBasicDv.h"
#include "../../ControlPoint/Tests/TestBasicCp.h"

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceList
{
public:
    DeviceList(const char* aTargetUdn, Semaphore& aAddedSem);
    ~DeviceList();
    void Stop();
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceC aDevice);
    void Removed(CpDeviceC aDevice);
private:
    Mutex iLock;
    std::vector<CpDeviceC> iList;
    const char* iTargetUdn;
    Semaphore& iAddedSem;
};


static void STDCALL added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

static void STDCALL removed(void* /*aPtr*/, CpDeviceC /*aDevice*/)
{
    /* The device stack sends byebyes then alives for each newly enabled device.
       These can be interleaved with responses to a msearch and can cause tests to misbehave,
       thinking a device has been removed.  The simplest way to work around this is to say
       our test guarantees that a device remains available as long as its needed then take
       advantage of this by ignoring device removed callbacks. */
    //reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}


DeviceList::DeviceList(const char* aTargetUdn, Semaphore& aAddedSem)
    : iLock("DLMX")
    , iTargetUdn(aTargetUdn)
    , iAddedSem(aAddedSem)
{
}

DeviceList::~DeviceList()
{
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDeviceCRemoveRef(iList[i]);
    }
}

void DeviceList::TestActions()
{
    size_t size = iList.size();
    if (size != 1)
    {
        Print("TestDvDeviceC - Assertion failed. Expected to find 1 device, but got %d.\n", size);
    }    
    ASSERT(size == 1);
    TestBasicCpC::TestActions(iList[0]);
}

void DeviceList::TestSubscriptions()
{
    size_t size = iList.size();
    if (size != 1)
    {
        Print("TestDvDeviceC - Assertion failed. Expected to find 1 device, but got %d.\n", size);
    }    
    ASSERT(size == 1);
    TestBasicCpC::TestSubscriptions(iList[0]);
}

void DeviceList::Added(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    if (strcmp(CpDeviceCUdn(aDevice), iTargetUdn) != 0) {
        return;
    }
    if (iList.size() == 0) {
        iList.push_back(aDevice);
        CpDeviceCAddRef(aDevice);
    }
    iAddedSem.Signal();
}

void DeviceList::Removed(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    const TUint count = (TUint)iList.size();
    const char* udn = CpDeviceCUdn(aDevice);
    for (TUint i=0; i<count; i++) {
        CpDeviceC device = iList[i];
        if (0 == strcmp(CpDeviceCUdn(device), udn)) {
            Print("Received byebye, removing device %s from list\n", udn);
            iList.erase(iList.begin()+i);
            CpDeviceCRemoveRef(device);
            break;
        }
    }
}


extern "C" void OhNetTestRunner(OhNetHandleInitParams aInitParams)
{
    OhNetInitParamsSetMsearchTime(aInitParams, 1);
    OhNetInitParamsSetUseLoopbackNetworkAdapter(aInitParams);
    OhNetInitParamsSetDvUpnpServerPort(aInitParams, 0);
    OhNetLibraryInitialise(aInitParams);
    Print("TestDvDeviceC - starting\n");
    OhNetHandleNetworkAdapterList subnetList = OhNetSubnetListCreate();
    OhNetHandleNetworkAdapter nif = OhNetSubnetAt(subnetList, 0);
    TIpAddress subnetAddr;
    subnetAddr.iFamily = kFamilyV4;
    subnetAddr.iV4 = OhNetNetworkAdapterSubnet(nif);
    OhNetSubnetListDestroy(subnetList);
    (void)OhNetLibraryStartCombined(subnetAddr);
//    Debug::SetLevel(Debug::kService);

    Semaphore* sem = new Semaphore("SEM1", 0);
    DeviceBasicC* device = new DeviceBasicC(DeviceBasicC::eProtocolUpnp);
    const char* udn;
    uint32_t ignore;
    DvDeviceGetUdn(device->Device(), &udn, &ignore);
    DeviceList* deviceList = new DeviceList(udn, *sem);
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("openhome.org", "TestBasic", 1,
                                                               added, deviceList, removed, deviceList);
    sem->Wait(30*1000); // allow up to 30 seconds to find our one device

    deviceList->TestActions();
    deviceList->TestSubscriptions();

    CpDeviceListDestroy(dlh);
    delete sem;
    delete deviceList;
    delete device;

    Print("TestDvDeviceC - completed\n");
    OhNetLibraryClose();
}
