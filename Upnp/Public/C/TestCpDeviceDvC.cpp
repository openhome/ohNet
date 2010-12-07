/* Simple test of C Device APIs
   Written in C++ to give us access to classes like Mutex, blocker, std::vector
   ...but C versions of all APIs being tested are used
*/

#include <C/Zapp.h>
#include <ZappTypes.h>
#include <TestFramework.h>
#include <C/CpDevice.h>
#include <C/CpDeviceDv.h>
#include <Debug.h>
#include <C/TestBasicDv.h>
#include <C/TestBasicCp.h>

using namespace Zapp;
using namespace Zapp::TestFramework;


extern "C" void ZappTestRunner(ZappHandleInitParams aInitParams)
{
    ZappInitParamsSetMsearchTime(aInitParams, 1);
    ZappInitParamsSetUseLoopbackNetworkInterface(aInitParams);
    ZappLibraryInitialise(aInitParams);
    Print("TestCpDeviceDvC - starting\n");
    ZappLibraryStartCombined();

    DeviceBasicC* device = new DeviceBasicC;
    CpDeviceC cph = CpDeviceDvCreate(device->Device());
    TestBasicCpC::TestActions(cph);
    TestBasicCpC::TestSubscriptions(cph);
    CpDeviceCRemoveRef(cph);
    delete device;

    Print("TestCpDeviceDvC - completed\n");
    ZappLibraryClose();
}
