#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Net/Private/DviStack.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestDvLpec(CpStack& aCpStack, DvStack& aDvStack);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetDvNumLpecThreads(2);
    aInitParams->SetDvLpecServerPort(2324);
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);
    dvStack->Start();

    TestDvLpec(*cpStack, *dvStack);

    delete lib;
}
