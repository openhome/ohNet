#include <OpenHome/Media/Tests/TestShell.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Net/Private/ShellCommandQuit.h>
#include <OpenHome/Net/Private/ShellCommandWatchDog.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Media;

void OpenHome::Media::ExecuteTestShell(Net::InitialisationParams* aInitParams, std::vector<ShellTest>& aTests)
{
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    TIpAddress addr = (*subnetList)[0]->Address();
    Endpoint endpt(0, addr);
    Endpoint::AddressBuf buf;
    endpt.AppendAddress(buf);
    Log::Print("Connect to %s.%u then 'help' for options\n\n", buf.Ptr(), Shell::kServerPortDefault);
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = nullptr;
    DvStack* dvStack = nullptr;
    lib->StartCombined(subnet, cpStack, dvStack);

    Shell* shell = new Shell(cpStack->Env());
    Semaphore* blocker = new Semaphore("BLCK", 0);

    ShellCommandRun* cmdRun = new ShellCommandRun(*cpStack, *dvStack, *shell, aTests);

    ShellCommandDebug* cmdDebug = new ShellCommandDebug(*shell);
    ShellCommandQuit* cmdQuit = new ShellCommandQuit(*shell, *blocker);
    ShellCommandWatchDog* cmdWatchDog = new ShellCommandWatchDog(*shell, kTestShellTimeout);
    blocker->Wait();
    // control never reaches here
    delete blocker;
    delete cmdWatchDog;
    delete cmdQuit;
    delete cmdDebug;
    delete cmdRun;
    delete shell;
    delete lib;
}
