/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <TestFramework.h>
#include <DviDevice.h>
#include <C/DvProvider.h>
#include <C/DvOpenhomeOrgTestBasic1.h>
#include <C/CpProxy.h>
#include <C/CpOpenhomeOrgTestBasic1.h>
#include <C/CpDevice.h>
#include <C/CpDeviceUpnp.h>
#include <Ascii.h>
#include <Maths.h>
#include <Stack.h>
#include <Debug.h>
#include <C/TestBasicDv.h>
#include <C/TestBasicCp.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

class DeviceList
{
public:
    DeviceList(Semaphore& aAddedSem);
    ~DeviceList();
    void Stop();
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceC aDevice);
    void Removed(CpDeviceC aDevice);
private:
    Mutex iLock;
    std::vector<CpDeviceC> iList;
    Semaphore& iAddedSem;
};


static void added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

static void removed(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}


DeviceList::DeviceList(Semaphore& aAddedSem)
    : iLock("DLMX")
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
    ASSERT(iList.size() == 1);
    TestBasicCpC::TestSubscriptions(iList[0]);
}

void DeviceList::Added(CpDeviceC aDevice)
{
    AutoMutex a(iLock);
    iList.push_back(aDevice);
    CpDeviceCAddRef(aDevice);
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
            iList.erase(iList.begin()+i);
            CpDeviceCRemoveRef(device);
            break;
        }
    }
}


extern "C" void OhNetTestRunner(OhNetHandleInitParams aInitParams)
{
    OhNetInitParamsSetMsearchTime(aInitParams, 1);
    OhNetInitParamsSetUseLoopbackNetworkInterface(aInitParams);
    OhNetLibraryInitialise(aInitParams);
    Print("TestDvDeviceC - starting\n");
    OhNetLibraryStartCombined();
//    Debug::SetLevel(Debug::kService);

    Semaphore* sem = new Semaphore("SEM1", 0);
    DeviceBasicC* device = new DeviceBasicC;
    DeviceList* deviceList = new DeviceList(*sem);;
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("openhome.org", "TestBasic", 1,
                                                               added, deviceList, removed, deviceList);
    sem->Wait(30*1000); // allow up to 30 seconds to fine our one device
    delete sem;

    deviceList->TestActions();
    deviceList->TestSubscriptions();

    CpDeviceListDestroy(dlh);
    delete deviceList;
    delete device;

    Print("TestDvDeviceC - completed\n");
    OhNetLibraryClose();
}
