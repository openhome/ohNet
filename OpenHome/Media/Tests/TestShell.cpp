#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Net/Private/ShellCommandDebug.h>
#include <OpenHome/Net/Private/ShellCommandQuit.h>
#include <OpenHome/Net/Private/ShellCommandWatchDog.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

#define SIMPLE_TEST_DECLARATION(x)  \
    extern void x();                \
    static void Shell##x(CpStack&, DvStack&, const std::vector<Brn>&) { x(); } \

SIMPLE_TEST_DECLARATION(TestAudioReservoir);
SIMPLE_TEST_DECLARATION(TestContentProcessor);
SIMPLE_TEST_DECLARATION(TestIdProvider);
SIMPLE_TEST_DECLARATION(TestFiller);
SIMPLE_TEST_DECLARATION(TestToneGenerator);
SIMPLE_TEST_DECLARATION(TestMuteManager);
SIMPLE_TEST_DECLARATION(TestVolumeManager);
SIMPLE_TEST_DECLARATION(TestMsg);
SIMPLE_TEST_DECLARATION(TestPipeline);
SIMPLE_TEST_DECLARATION(TestPreDriver);
SIMPLE_TEST_DECLARATION(TestProtocolHttp);
SIMPLE_TEST_DECLARATION(TestReporter);
SIMPLE_TEST_DECLARATION(TestStarvationMonitor);
SIMPLE_TEST_DECLARATION(TestStopper);
SIMPLE_TEST_DECLARATION(TestStore);
SIMPLE_TEST_DECLARATION(TestSupply);
SIMPLE_TEST_DECLARATION(TestTrackDatabase);
SIMPLE_TEST_DECLARATION(TestTrackInspector);
SIMPLE_TEST_DECLARATION(TestVariableDelay);

static const TUint kTimeout = 60; // initial timeout for TestShell. This is increased  by testharness once running.

extern void TestCodec(Environment& aEnv, const std::vector<Brn>& aArgs);
static void ShellTestCodec(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs)
{
    TestCodec(aCpStack.Env(), aArgs);
}

extern void TestUpnpErrors(CpStack& aCpStack, DvStack& aDvStack);
static void ShellTestUpnpErrors(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/)
{
    TestUpnpErrors(aCpStack, aDvStack);
}


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
    shellTests.push_back(ShellTest("TestContentProcessor", ShellTestContentProcessor));
    shellTests.push_back(ShellTest("TestIdProvider", ShellTestIdProvider));
    shellTests.push_back(ShellTest("TestFiller", ShellTestFiller));
    shellTests.push_back(ShellTest("TestToneGenerator", ShellTestToneGenerator));
    shellTests.push_back(ShellTest("TestMuteManager", ShellTestMuteManager));
    shellTests.push_back(ShellTest("TestVolumeManager", ShellTestVolumeManager));
    shellTests.push_back(ShellTest("TestMsg", ShellTestMsg));
    shellTests.push_back(ShellTest("TestPipeline", ShellTestPipeline));
    shellTests.push_back(ShellTest("TestPreDriver", ShellTestPreDriver));
    shellTests.push_back(ShellTest("TestProtocolHttp", ShellTestProtocolHttp));
    shellTests.push_back(ShellTest("TestReporter", ShellTestReporter));
    shellTests.push_back(ShellTest("TestStarvationMonitor", ShellTestStarvationMonitor));
    shellTests.push_back(ShellTest("TestStopper", ShellTestStopper));
    shellTests.push_back(ShellTest("TestStore", ShellTestStore));
    shellTests.push_back(ShellTest("TestSupply", ShellTestSupply));
    shellTests.push_back(ShellTest("TestTrackDatabase", ShellTestTrackDatabase));
    shellTests.push_back(ShellTest("TestTrackInspector", ShellTestTrackInspector));
    shellTests.push_back(ShellTest("TestVariableDelay", ShellTestVariableDelay));
    shellTests.push_back(ShellTest("TestCodec", ShellTestCodec));
    shellTests.push_back(ShellTest("TestUpnpErrors", ShellTestUpnpErrors));
    ShellCommandRun* cmdRun = new ShellCommandRun(*cpStack, *dvStack, *shell, shellTests);

    ShellCommandDebug* cmdDebug = new ShellCommandDebug(*shell);
    ShellCommandQuit* cmdQuit = new ShellCommandQuit(*shell, *blocker);
    ShellCommandWatchDog* cmdWatchDog = new ShellCommandWatchDog(*shell, kTimeout);
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
