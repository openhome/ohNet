#ifndef HEADER_SHELL_COMMAND_LOGMODE
#define HEADER_SHELL_COMMAND_LOGMODE

#include <OpenHome/Private/Shell.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

#include <vector>
#include <map>

namespace OpenHome {
class IWriter;

class ShellCommandLogMode : private IShellCommandHandler
{
public:
    ShellCommandLogMode(Shell& aShell, IShellLogMode& aMode);
    ~ShellCommandLogMode();
public: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Shell& iShell;
    IShellLogMode& iMode;

};

} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_LOGMODE
