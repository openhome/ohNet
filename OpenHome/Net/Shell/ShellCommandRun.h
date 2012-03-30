#ifndef HEADER_SHELL_COMMAND_RUN
#define HEADER_SHELL_COMMAND_RUN

#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Net {

class ShellCommandRun : private IShellCommandHandler, private INonCopyable
{
public:
    ShellCommandRun(Shell& aShell);
    ~ShellCommandRun();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
private:
    void Log(const char* aMsg);
private:
    Shell& iShell;
    IWriter* iResponseWriter;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_RUN
