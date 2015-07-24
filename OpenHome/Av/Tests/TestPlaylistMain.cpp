#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestPlaylist(CpStack& aCpStack, DvStack& aDvStack);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetDvUpnpServerPort(0);
    aInitParams->SetUseLoopbackNetworkAdapter();
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = nullptr;
    DvStack* dvStack = nullptr;
    lib->StartCombined(subnet, cpStack, dvStack);

    TestPlaylist(*cpStack, *dvStack);

    delete lib;
}
