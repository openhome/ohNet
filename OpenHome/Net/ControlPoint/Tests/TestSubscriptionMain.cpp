#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestSubscription();

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCp(subnet);

    TestSubscription();

    UpnpLibrary::Close();
}
