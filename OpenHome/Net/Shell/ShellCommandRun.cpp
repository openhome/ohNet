#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestBuffer();
static void RunTestBuffer(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestBuffer(); }

extern void TestThread();
static void RunTestThread(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestThread(); }

extern void TestFifo();
static void RunTestFifo(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestFifo(); }

extern void TestQueue();
static void RunTestQueue(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestQueue(); }

extern void TestTextUtils();
static void RunTestTextUtils(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestTextUtils(); }

extern void TestNetwork(const std::vector<Brn>& aArgs);
static void RunTestNetwork(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs) { TestNetwork(aArgs); }

extern void TestTimer();
static void RunTestTimer(CpStack& /*aCpStack*/, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestTimer(); }

extern void TestSsdpMListen(Environment& aEnv, const std::vector<Brn>& aArgs);
static void RunTestSsdpMListen(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs) { TestSsdpMListen(aCpStack.Env(), aArgs); }

extern void TestSsdpUListen(Environment& aEnv, const std::vector<Brn>& aArgs);
static void RunTestSsdpUListen(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs) { TestSsdpUListen(aCpStack.Env(), aArgs); }

extern void TestDeviceList(CpStack& aCpStack, const std::vector<Brn>& aArgs);
static void RunTestDeviceList(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& aArgs) { TestDeviceList(aCpStack, aArgs); }

extern void TestInvocation(CpStack& aCpStack);
static void RunTestInvocation(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestInvocation(aCpStack); }

extern void TestSubscription(CpStack& aCpStack);
static void RunTestSubscription(CpStack& aCpStack, DvStack& /*aDvStack*/, const std::vector<Brn>& /*aArgs*/) { TestSubscription(aCpStack); }

extern void TestCpDeviceDv(CpStack& aCpStack, DvStack& aDvStack);
static void RunTestCpDeviceDv(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/) { TestCpDeviceDv(aCpStack, aDvStack); }

extern void TestDviDiscovery(DvStack& aDvStack);
static void RunTestDviDiscovery(CpStack& /*aCpStack*/, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/) { TestDviDiscovery(aDvStack); }

extern void TestDviDeviceList(CpStack& aCpStack, DvStack& aDvStack);
static void RunTestDviDeviceList(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/) { TestDviDeviceList(aCpStack, aDvStack); }

extern void TestDvInvocation(CpStack& aCpStack, DvStack& aDvStack);
static void RunTestDvInvocation(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/) { TestDvInvocation(aCpStack, aDvStack); }

extern void TestDvSubscription(CpStack& aCpStack, DvStack& aDvStack);
static void RunTestDvSubscription(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& /*aArgs*/) { TestDvSubscription(aCpStack, aDvStack); }


// ShellCommandRun

static const TChar kShellCommandRun[] = "run";

ShellCommandRun::ShellCommandRun(CpStack& aCpStack, DvStack& aDvStack, Shell& aShell)
    : iCpStack(aCpStack)
    , iDvStack(aDvStack)
    , iShell(aShell)
    , iResponseWriter(NULL)
{
    iShell.AddCommandHandler(kShellCommandRun, *this);
    AddTest("TestBuffer", RunTestBuffer);
    AddTest("TestThread", RunTestThread);
    AddTest("TestFifo", RunTestFifo);
    AddTest("TestQueue", RunTestQueue);
    AddTest("TestTextUtils", RunTestTextUtils);
    AddTest("TestNetwork", RunTestNetwork, true);
    AddTest("TestTimer", RunTestTimer);
    AddTest("TestSsdpMListen", RunTestSsdpMListen, true);
    AddTest("TestSsdpUListen", RunTestSsdpUListen, true);
    AddTest("TestDeviceList", RunTestDeviceList, true);
    AddTest("TestInvocation", RunTestInvocation);
    AddTest("TestSubscription", RunTestSubscription);
    AddTest("TestCpDeviceDv", RunTestCpDeviceDv);
    AddTest("TestDviDiscovery", RunTestDviDiscovery);
    AddTest("TestDviDeviceList", RunTestDviDeviceList);
    AddTest("TestDvInvocation", RunTestDvInvocation);
    AddTest("TestDvSubscription", RunTestDvSubscription);
}

ShellCommandRun::~ShellCommandRun()
{
    iShell.RemoveCommandHandler(kShellCommandRun);
    TestMap::iterator it = iTests.begin();
    while (it != iTests.end()) {
        delete it->second;
        it++;
    }
}

void ShellCommandRun::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    iResponseWriter = &aResponse;
    FunctorMsg logger = MakeFunctorMsg(*this, &OpenHome::Net::ShellCommandRun::Log);
    OpenHome::TestFramework::SetPrinter(logger);
    if (aArgs.size() == 0) {
        aResponse.Write(Brn("No program specified for command \'run\'\n"));
        return;
    }
    Brn program = aArgs[0];
    TestMap::iterator it = iTests.find(program);
    if (it != iTests.end()) {
        it->second->Run(aArgs);
    }
    else {
        aResponse.Write(Brn("Unexpected test name for command \'run\': "));
        aResponse.Write(program);
        aResponse.Write(Brn("\n"));
    }
    iResponseWriter = NULL;
}

void ShellCommandRun::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("Run a unit test.  Options are:\n"));
    TestMap::iterator it = iTests.begin();
    while (it != iTests.end()) {
        Test* test = it->second;
        aResponse.Write(Brn("  "));
        aResponse.Write(Brn(test->Name()));
        if (test->HelpAvailable()) {
            aResponse.Write(Brn(" (--help for arguments)"));
        }
        aResponse.Write(Brn("\n"));
        it++;
    }
}

void ShellCommandRun::AddTest(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable)
{
    AddTest(new Test(iCpStack, iDvStack, aName, aRunner, aHelpAvailable));
}

void ShellCommandRun::AddTest(Test* aTest)
{
    Brn name(aTest->Name());
    iTests.insert(std::pair<Brn, Test*>(name, aTest));
}

void ShellCommandRun::Log(const char* aMsg)
{
    Brn msg(aMsg);
    iResponseWriter->Write(msg);
}


// ShellCommandRun::Test

ShellCommandRun::Test::Test(CpStack& aCpStack, DvStack& aDvStack, const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable)
    : iCpStack(aCpStack)
    , iDvStack(aDvStack)
    , iName(aName)
    , iRunner(aRunner)
    , iHelpAvailable(aHelpAvailable)
{
}

const TChar* ShellCommandRun::Test::Name() const
{
    return iName;
}

void ShellCommandRun::Test::Run(const std::vector<Brn>& aArgs)
{
    iRunner(iCpStack, iDvStack, aArgs);
}

TBool ShellCommandRun::Test::HelpAvailable() const
{
    return iHelpAvailable;
}
