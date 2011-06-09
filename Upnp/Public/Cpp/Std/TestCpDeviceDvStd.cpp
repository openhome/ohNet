#include <TestFramework.h>
#include <OhNetTypes.h>
#include <Std/DvDevice.h>
#include <OhNet.h>
#include <Std/CpDeviceDv.h>
#include <Std/TestBasicDv.h>
#include <Std/TestBasicCp.h>

#include <string>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;


void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], InitialisationParams* aInitParams)
{
    aInitParams->SetUseLoopbackNetworkInterface();
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkInterface*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCombined(subnet);

    Print("TestCpDeviceDvStd - starting\n");

    DeviceBasic* device = new DeviceBasic(DeviceBasic::eProtocolNone);
    CpDeviceDvCpp* cpDevice = CpDeviceDvCpp::New(device->Device());
    TestBasicCp::TestActions(*cpDevice);
    TestBasicCp::TestSubscriptions(*cpDevice);
    cpDevice->RemoveRef();
    delete device;

    Print("TestCpDeviceDvStd - completed\n");
    UpnpLibrary::Close();
}
