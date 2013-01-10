#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    TIpAddress addr = (*subnetList)[0]->Address();
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Print("Connect to %s.%u then 'help' for options\n\n", buf.Ptr(), Shell::kServerPort);
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    Shell* shell = new Shell(cpStack->Env());
    ShellCommandRun* cmdRun = new ShellCommandRun(*cpStack, *dvStack, *shell);
    ShellCommandDebug* cmdDebug = new ShellCommandDebug(*shell);
    Semaphore* blocker = new Semaphore("BLCK", 0);
    blocker->Wait();
    // control never reaches here
    delete blocker;
    delete cmdDebug;
    delete cmdRun;
    delete shell;

    delete lib;
}
