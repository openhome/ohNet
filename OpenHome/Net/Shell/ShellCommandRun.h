#ifndef HEADER_SHELL_COMMAND_RUN
#define HEADER_SHELL_COMMAND_RUN

#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Standard.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

class CpStack;
class DvStack;

typedef void (*ShellTestRunner)(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& aArgs);

class ShellTest
{
public:
    ShellTest(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable = false);
    const TChar* Name() const;
    void Run(CpStack& aCpStack, DvStack& aDvStack, const std::vector<Brn>& aArgs);
    TBool HelpAvailable() const;
private:
    const TChar* iName;
    ShellTestRunner iRunner;
    TBool iHelpAvailable;
};

class ShellCommandRun : private IShellCommandHandler
{
public:
    ShellCommandRun(CpStack& aCpStack, DvStack& aDvStack, Shell& aShell, std::vector<ShellTest>& aShellTests);
    ~ShellCommandRun();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    void AddTest(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable = false);
    void AddTest(ShellTest* aTest);
    void Log(const char* aMsg);
private:
    CpStack& iCpStack;
    DvStack& iDvStack;
    Shell& iShell;
    IWriter* iResponseWriter;
    typedef std::map<Brn, ShellTest*, BufferCmp> TestMap;
    TestMap iTests;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_RUN
