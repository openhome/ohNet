#include <OpenHome/Net/Private/ShellCommandRun.h>
#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::Net;

const TChar kShellCommandRun[] = "run";

extern void TestBuffer();
extern void TestThread();
extern void TestFifo();
extern void TestQueue();
extern void TestNetwork(const std::vector<Brn>& aArgs);
extern void TestTimer();
extern void TestSsdpMListen(const std::vector<Brn>& aArgs);
extern void TestSsdpUListen(const std::vector<Brn>& aArgs);
extern void TestDeviceList(const std::vector<Brn>& aArgs);
extern void TestInvocation();
extern void TestSubscription();
extern void TestCpDeviceDv();
extern void TestDviDiscovery();
extern void TestDviDeviceList();
extern void TestDvInvocation();
extern void TestDvSubscription();

ShellCommandRun::ShellCommandRun(Shell& aShell)
    : iShell(aShell)
    , iResponseWriter(NULL)
{
    iShell.AddCommandHandler(kShellCommandRun, *this);
}

ShellCommandRun::~ShellCommandRun()
{
    iShell.RemoveCommandHandler(kShellCommandRun);
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
    if (program == Brn("TestBuffer")) {
        TestBuffer();
    }
    else if (program == Brn("TestThread")) {
        TestThread();
    }
    else if (program == Brn("TestFifo")) {
        TestFifo();
    }
    else if (program == Brn("TestQueue")) {
        TestQueue();
    }
    else if (program == Brn("TestNetwork")) {
        TestNetwork(aArgs);
    }
    else if (program == Brn("TestTimer")) {
        TestTimer();
    }
    else if (program == Brn("TestSsdpMListen")) {
        TestSsdpMListen(aArgs);
    }
    else if (program == Brn("TestSsdpUListen")) {
        TestSsdpUListen(aArgs);
    }
    else if (program == Brn("TestDeviceList")) {
        TestDeviceList(aArgs);
    }
    else if (program == Brn("TestInvocation")) {
        TestInvocation();
    }
    else if (program == Brn("TestSubscription")) {
        TestSubscription();
    }
    else if (program == Brn("TestCpDeviceDv")) {
        TestCpDeviceDv();
    }
    else if (program == Brn("TestDviDiscovery")) {
        TestDviDiscovery();
    }
    else if (program == Brn("TestDviDeviceList")) {
        TestDviDeviceList();
    }
    else if (program == Brn("TestDvInvocation")) {
        TestDvInvocation();
    }
    else if (program == Brn("TestDvSubscription")) {
        TestDvSubscription();
    }
    else {
        aResponse.Write(Brn("Unexpected test name for command \'run\': "));
        aResponse.Write(program);
        aResponse.Write('\n');
    }
    iResponseWriter = NULL;
}

void ShellCommandRun::Log(const char* aMsg)
{
    Brn msg(aMsg);
    iResponseWriter->Write(msg);
}
