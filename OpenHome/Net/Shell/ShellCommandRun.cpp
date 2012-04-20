#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestBuffer();
static void RunTestBuffer(const std::vector<Brn>& /*aArgs*/) { TestBuffer(); }

extern void TestThread();
static void RunTestThread(const std::vector<Brn>& /*aArgs*/) { TestThread(); }

extern void TestFifo();
static void RunTestFifo(const std::vector<Brn>& /*aArgs*/) { TestFifo(); }

extern void TestQueue();
static void RunTestQueue(const std::vector<Brn>& /*aArgs*/) { TestQueue(); }

extern void TestNetwork(const std::vector<Brn>& aArgs);
static void RunTestNetwork(const std::vector<Brn>& aArgs) { TestNetwork(aArgs); }

extern void TestTimer();
static void RunTestTimer(const std::vector<Brn>& /*aArgs*/) { TestTimer(); }

extern void TestSsdpMListen(const std::vector<Brn>& aArgs);
static void RunTestSsdpMListen(const std::vector<Brn>& aArgs) { TestSsdpMListen(aArgs); }

extern void TestSsdpUListen(const std::vector<Brn>& aArgs);
static void RunTestSsdpUListen(const std::vector<Brn>& aArgs) { TestSsdpUListen(aArgs); }

extern void TestDeviceList(const std::vector<Brn>& aArgs);
static void RunTestDeviceList(const std::vector<Brn>& aArgs) { TestDeviceList(aArgs); }

extern void TestInvocation();
static void RunTestInvocation(const std::vector<Brn>& /*aArgs*/) { TestInvocation(); }

extern void TestSubscription();
static void RunTestSubscription(const std::vector<Brn>& /*aArgs*/) { TestSubscription(); }

extern void TestCpDeviceDv();
static void RunTestCpDeviceDv(const std::vector<Brn>& /*aArgs*/) { TestCpDeviceDv(); }

extern void TestDviDiscovery();
static void RunTestDviDiscovery(const std::vector<Brn>& /*aArgs*/) { TestDviDiscovery(); }

extern void TestDviDeviceList();
static void RunTestDviDeviceList(const std::vector<Brn>& /*aArgs*/) { TestDviDeviceList(); }

extern void TestDvInvocation();
static void RunTestDvInvocation(const std::vector<Brn>& /*aArgs*/) { TestDvInvocation(); }

extern void TestDvSubscription();
static void RunTestDvSubscription(const std::vector<Brn>& /*aArgs*/) { TestDvSubscription(); }


// ShellCommandRun

static const TChar kShellCommandRun[] = "run";

ShellCommandRun::ShellCommandRun(Shell& aShell)
    : iShell(aShell)
    , iResponseWriter(NULL)
{
    iShell.AddCommandHandler(kShellCommandRun, *this);
    AddTest("TestBuffer", RunTestBuffer);
    AddTest("TestThread", RunTestThread);
    AddTest("TestFifo", RunTestFifo);
    AddTest("TestQueue", RunTestQueue);
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
    AddTest(new Test(aName, aRunner, aHelpAvailable));
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

ShellCommandRun::Test::Test(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable)
    : iName(aName)
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
    iRunner(aArgs);
}

TBool ShellCommandRun::Test::HelpAvailable() const
{
    return iHelpAvailable;
}
