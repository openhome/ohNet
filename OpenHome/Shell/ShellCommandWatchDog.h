#ifndef HEADER_SHELL_COMMAND_WATCHDOG
#define HEADER_SHELL_COMMAND_WATCHDOG

#include <OpenHome/Private/Shell.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

#include <cstdlib>
#include <vector>

namespace OpenHome {

class IWriter;

class ShellCommandWatchDog : private IShellCommandHandler
{
class WatchDog;

public:
    ShellCommandWatchDog(Shell& aShell, TUint aWatchdogTimeoutSeconds);
    ~ShellCommandWatchDog();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Shell&      iShell;
    WatchDog*   iWatchDog;
};

} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_WATCHDOG
