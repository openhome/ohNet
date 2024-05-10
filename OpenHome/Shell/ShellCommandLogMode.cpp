#include <OpenHome/Private/ShellCommandLogMode.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;

// ShellCommandLogMode

static const TChar kShellCommandLogMode[] = "logmode";

ShellCommandLogMode::ShellCommandLogMode(Shell& aShell, IShellLogMode& aMode)
    : iShell(aShell)
    , iMode(aMode)
{
    iShell.AddCommandHandler(kShellCommandLogMode, *this);
}

ShellCommandLogMode::~ShellCommandLogMode()
{
    iShell.RemoveCommandHandler(kShellCommandLogMode);
}

void ShellCommandLogMode::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for \'logmode\' command\n"));
        return;
    }
    else {
        if (aArgs[0] == Brn("shell")) {
            iMode.SetLogMode(EShellLogMode::eShell);
        }
        else if (aArgs[0] == Brn("all")) {
            iMode.SetLogMode(EShellLogMode::eAll);
        }
        else {
           aResponse.Write(Brn("Unknown argument for \'logmode\' command\n"));
        }
    }
}

void ShellCommandLogMode::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("logmode [shell|all]\n"));
    aResponse.Write(Brn("  Output options for debugging logs. \'all\' mode will print logs to RS232 and flash\n"));
    aResponse.Write(Brn("  \'shell\' mode will print logs to shell only\n"));
    aResponse.Write(Brn("  \'all\' mode will additionally print logs to RS232 and flash\n"));
    aResponse.Write(Brn("  Note that this will be set to shell by default and will reset on disconnect\n"));
}
