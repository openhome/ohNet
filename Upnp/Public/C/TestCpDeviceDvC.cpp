/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <TestFramework.h>
#include <C/CpDevice.h>
#include <C/CpDeviceDv.h>
#include <Debug.h>
#include <C/TestBasicDv.h>
#include <C/TestBasicCp.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;


extern "C" void OhNetTestRunner(OhNetHandleInitParams aInitParams)
{
    OhNetInitParamsSetMsearchTime(aInitParams, 1);
    OhNetInitParamsSetUseLoopbackNetworkAdapter(aInitParams);
    OhNetLibraryInitialise(aInitParams);
    Print("TestCpDeviceDvC - starting\n");
    OhNetHandleNetworkAdapterList subnetList = OhNetSubnetListCreate();
    OhNetHandleNetworkAdapter nif = OhNetSubnetAt(subnetList, 0);
    TIpAddress subnet = OhNetNetworkAdapterSubnet(nif);
    OhNetSubnetListDestroy(subnetList);
    OhNetLibraryStartCombined(subnet);

    DeviceBasicC* device = new DeviceBasicC(DeviceBasicC::eProtocolNone);
    CpDeviceC cph = CpDeviceDvCreate(device->Device());
    TestBasicCpC::TestActions(cph);
    TestBasicCpC::TestSubscriptions(cph);
    CpDeviceCRemoveRef(cph);
    delete device;

    Print("TestCpDeviceDvC - completed\n");
    OhNetLibraryClose();
}
