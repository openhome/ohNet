#include <TestFramework.h>
#include <OhNetTypes.h>
#include <Std/DvDevice.h>
#include <OhNet.h>
#include <Std/CpDeviceDv.h>
#include <Std/TestBasicDv.h>
#include <Std/TestBasicCp.h>

#include <string>
#include <vector>

using namespace OpenHome::Net;
using namespace OpenHome::Net::TestFramework;


void OpenHome::Net::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
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
