#include <TestFramework.h>
#include <ZappTypes.h>
#include <Std/DvDevice.h>
#include <Zapp.h>
#include <Std/CpDeviceDv.h>
#include <Std/TestBasicDv.h>
#include <Std/TestBasicCp.h>

#include <string>
#include <vector>

using namespace Zapp;
using namespace Zapp::TestFramework;


void Zapp::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    UpnpLibrary::StartCombined();

    Print("TestCpDeviceDvStd - starting\n");

    DeviceBasic* device = new DeviceBasic;
    CpDeviceDvCpp* cpDevice = CpDeviceDvCpp::New(device->Device());
    TestBasicCp::TestActions(*cpDevice);
    TestBasicCp::TestSubscriptions(*cpDevice);
    cpDevice->RemoveRef();
    delete device;

    Print("TestCpDeviceDv - completed\n");
    UpnpLibrary::Close();
}
