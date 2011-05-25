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

using namespace OpenHome::Net;
using namespace OpenHome::Net::TestFramework;


extern "C" void OhNetTestRunner(OhNetHandleInitParams aInitParams)
{
    OhNetInitParamsSetMsearchTime(aInitParams, 1);
    OhNetInitParamsSetUseLoopbackNetworkInterface(aInitParams);
    OhNetLibraryInitialise(aInitParams);
    Print("TestCpDeviceDvC - starting\n");
    OhNetLibraryStartCombined();

    DeviceBasicC* device = new DeviceBasicC;
    CpDeviceC cph = CpDeviceDvCreate(device->Device());
    TestBasicCpC::TestActions(cph);
    TestBasicCpC::TestSubscriptions(cph);
    CpDeviceCRemoveRef(cph);
    delete device;

    Print("TestCpDeviceDvC - completed\n");
    OhNetLibraryClose();
}
