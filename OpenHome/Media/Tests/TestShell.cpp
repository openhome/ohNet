#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Net/Private/ShellCommandQuit.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

#define SIMPLE_TEST_DECLARATION(x)  \
    extern void x();                \
    static void Shell##x(CpStack&, DvStack&, const std::vector<Brn>&) { x(); } \

SIMPLE_TEST_DECLARATION(TestAudioReservoir);
SIMPLE_TEST_DECLARATION(TestMsg);
SIMPLE_TEST_DECLARATION(TestPipeline);
SIMPLE_TEST_DECLARATION(TestPreDriver);
SIMPLE_TEST_DECLARATION(TestReporter);
SIMPLE_TEST_DECLARATION(TestStarvationMonitor);
SIMPLE_TEST_DECLARATION(TestStopper);
SIMPLE_TEST_DECLARATION(TestSupply);
SIMPLE_TEST_DECLARATION(TestVariableDelay);

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
    Semaphore* blocker = new Semaphore("BLCK", 0);

    std::vector<ShellTest> shellTests;
    shellTests.push_back(ShellTest("TestAudioReservoir", ShellTestAudioReservoir));
    shellTests.push_back(ShellTest("TestMsg", ShellTestMsg));
    shellTests.push_back(ShellTest("TestPipeline", ShellTestPipeline));
    shellTests.push_back(ShellTest("TestPreDriver", ShellTestPreDriver));
    shellTests.push_back(ShellTest("TestReporter", ShellTestReporter));
    shellTests.push_back(ShellTest("TestStarvationMonitor", ShellTestStarvationMonitor));
    shellTests.push_back(ShellTest("TestStopper", ShellTestStopper));
    shellTests.push_back(ShellTest("TestSupply", ShellTestSupply));
    shellTests.push_back(ShellTest("TestVariableDelay", ShellTestVariableDelay));
    ShellCommandRun* cmdRun = new ShellCommandRun(*cpStack, *dvStack, *shell, shellTests);

    ShellCommandDebug* cmdDebug = new ShellCommandDebug(*shell);
    ShellCommandQuit* cmdQuit = new ShellCommandQuit(*shell, *blocker);
    blocker->Wait();
    // control never reaches here
    delete blocker;
    delete cmdQuit;
    delete cmdDebug;
    delete cmdRun;
    delete shell;

    delete lib;
}

