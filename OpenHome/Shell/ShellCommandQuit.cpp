#include <OpenHome/Private/ShellCommandQuit.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;

// ShellCommandQuit

static const TChar kShellCommandQuit[] = "quit";

ShellCommandQuit::ShellCommandQuit(Shell& aShell, Semaphore& aBlocker)
    : iShell(aShell)
    , iBlocker(aBlocker)
{
    iShell.AddCommandHandler(kShellCommandQuit, *this);
}

ShellCommandQuit::~ShellCommandQuit()
{
    iShell.RemoveCommandHandler(kShellCommandQuit);
}

void ShellCommandQuit::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() > 0 ) {
        aResponse.Write(Brn("Quit command does not take any arguments!\n"));
        return;
    }
    iBlocker.Signal();
}

void ShellCommandQuit::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("Terminate shell.\n"));
}

