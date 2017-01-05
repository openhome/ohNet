#include <OpenHome/Private/ShellCommandRun.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// ShellCommandRun

static const TChar kShellCommandRun[] = "run";

ShellCommandRun::ShellCommandRun(CpStack& aCpStack, DvStack& aDvStack, Shell& aShell, std::vector<ShellTest>& aShellTests)
    : iCpStack(aCpStack)
    , iDvStack(aDvStack)
    , iShell(aShell)
    , iResponseWriter(NULL)
{
    iShell.AddCommandHandler(kShellCommandRun, *this);

    for ( std::vector<ShellTest>::iterator i = aShellTests.begin() ; i != aShellTests.end() ; ++i )
        AddTest(new ShellTest(*i));
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
    FunctorMsg logger = MakeFunctorMsg(*this, &OpenHome::ShellCommandRun::Log);
    OpenHome::TestFramework::SetPrinter(logger);
    if (aArgs.size() == 0) {
        aResponse.Write(Brn("No program specified for command \'run\'\n"));
        return;
    }
    Brn program = aArgs[0];
    TestMap::iterator it = iTests.find(program);
    if (it != iTests.end()) {
        it->second->Run(iCpStack, iDvStack, aArgs);
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
        ShellTest* test = it->second;
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
    AddTest(new ShellTest(aName, aRunner, aHelpAvailable));
}

void ShellCommandRun::AddTest(ShellTest* aTest)
{
    Brn name(aTest->Name());
    iTests.insert(std::pair<Brn, ShellTest*>(name, aTest));
}

void ShellCommandRun::Log(const char* aMsg)
{
    Brn msg(aMsg);
    iResponseWriter->Write(msg);
}


// ShellTest

ShellTest::ShellTest(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable)
    : iName(aName)
    , iRunner(aRunner)
    , iHelpAvailable(aHelpAvailable)
{
}

const TChar* ShellTest::Name() const
{
    return iName;
}

void ShellTest::Run(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& aArgs)
{
    iRunner(aCpStack, aDvStack, aArgs);
}

TBool ShellTest::HelpAvailable() const
{
    return iHelpAvailable;
}
