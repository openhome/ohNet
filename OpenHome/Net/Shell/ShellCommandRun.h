#ifndef HEADER_SHELL_COMMAND_RUN
#define HEADER_SHELL_COMMAND_RUN

#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Standard.h>

#include <vector>
#include <map>

namespace OpenHome {
namespace Net {

typedef void (*ShellTestRunner)(const std::vector<Brn>& aArgs);

class ShellCommandRun : private IShellCommandHandler
{
public:
    ShellCommandRun(Shell& aShell);
    ~ShellCommandRun();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    class Test
    {
    public:
        Test(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable);
        const TChar* Name() const;
        void Run(const std::vector<Brn>& aArgs);
        TBool HelpAvailable() const;
    private:
        const TChar* iName;
        ShellTestRunner iRunner;
        TBool iHelpAvailable;
    };
private:
    void AddTest(const TChar* aName, ShellTestRunner aRunner, TBool aHelpAvailable = false);
    void AddTest(Test* aTest);
    void Log(const char* aMsg);
private:
    Shell& iShell;
    IWriter* iResponseWriter;
    typedef std::map<Brn, Test*, BufferCmp> TestMap;
    TestMap iTests;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_RUN
