#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestFriendlyNameManager(CpStack& aCpStack, DvStack& aDvStack);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetDvUpnpServerPort(0);
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    TestFriendlyNameManager(*cpStack, *dvStack);

    delete lib;
}
