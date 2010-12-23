/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/Zapp.h>
#include <ZappTypes.h>
#include <TestFramework.h>
#include <DviDevice.h>
#include <C/DvProvider.h>
#include <C/DvZappOrgTestBasic1C.h>
#include <C/CpProxy.h>
#include <C/CpZappOrgTestBasic1C.h>
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

using namespace Zapp;
using namespace Zapp::TestFramework;

class DeviceList
{
public:
    DeviceList();
    ~DeviceList();
    void Stop();
    void TestActions();
    void TestSubscriptions();
    void Added(CpDeviceC aDevice);
    void Removed(CpDeviceC aDevice);
private:
    Mutex iLock;
    std::vector<CpDeviceC> iList;
};


static void added(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Added(aDevice);
}

static void removed(void* aPtr, CpDeviceC aDevice)
{
    reinterpret_cast<DeviceList*>(aPtr)->Removed(aDevice);
}


DeviceList::DeviceList()
    : iLock("DLMX")
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
    ASSERT(iList.size() == 1);
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


extern "C" void ZappTestRunner(ZappHandleInitParams aInitParams)
{
    ZappInitParamsSetMsearchTime(aInitParams, 1);
    ZappInitParamsSetUseLoopbackNetworkInterface(aInitParams);
    ZappLibraryInitialise(aInitParams);
    Print("TestDvDeviceC - starting\n");
    ZappLibraryStartCombined();
//    Debug::SetLevel(Debug::kService);

    DeviceBasicC* device = new DeviceBasicC;
    DeviceList* deviceList = new DeviceList;
    HandleCpDeviceList dlh = CpDeviceListCreateUpnpServiceType("zapp.org", "TestBasic", 1,
                                                               added, deviceList, removed, deviceList);
    Blocker* blocker = new Blocker;
    blocker->Wait(ZappInitParamsMsearchTimeSecs(aInitParams));
    delete blocker;

    deviceList->TestActions();
    deviceList->TestSubscriptions();

    CpDeviceListDestroy(dlh);
    delete deviceList;
    delete device;

    Print("TestDvDeviceC - completed\n");
    ZappLibraryClose();
}
