/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/C/CpDevice.h>
#include <OpenHome/Net/C/CpDeviceDv.h>
#include <OpenHome/Private/Debug.h>
#include "../../Device/Tests/TestBasicDv.h"
#include "TestBasicCp.h"

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
    const TUint subnet = OhNetNetworkAdapterSubnet(nif);
    OhNetSubnetListDestroy(subnetList);
    (void)OhNetLibraryStartCombined(subnet);

    DeviceBasicC* device = new DeviceBasicC(DeviceBasicC::eProtocolNone);
    CpDeviceC cph = CpDeviceDvCreate(device->Device());
    TestBasicCpC::TestActions(cph);
    TestBasicCpC::TestSubscriptions(cph);
    CpDeviceCRemoveRef(cph);
    delete device;

    Print("TestCpDeviceDvC - completed\n");
    OhNetLibraryClose();
}
