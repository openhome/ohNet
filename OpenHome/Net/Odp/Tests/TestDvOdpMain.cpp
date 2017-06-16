#include <OpenHome/Types.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestDvOdp(CpStack& aCpStack, DvStack& aDvStack);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    auto lib = new Library(aInitParams);
    auto subnetList = lib->CreateSubnetList();
    auto subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = nullptr;
    DvStack* dvStack = nullptr;
    lib->StartCombined(subnet, cpStack, dvStack);

    TestDvOdp(*cpStack, *dvStack);

    delete lib;
}
