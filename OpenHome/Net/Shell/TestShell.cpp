#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    UpnpLibrary::Initialise(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = UpnpLibrary::CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    TIpAddress addr = (*subnetList)[0]->Address();
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Using network adapter %s\n\n", buf.Ptr());
    UpnpLibrary::DestroySubnetList(subnetList);
    UpnpLibrary::StartCombined(subnet);

    Shell* shell = new Shell();
    ShellCommandRun* cmdRun = new ShellCommandRun(*shell);
    Semaphore* blocker = new Semaphore("BLCK", 0);
    blocker->Wait();
    // control never reaches here
    delete blocker;
    delete cmdRun;
    delete shell;

    UpnpLibrary::Close();
}
