#include <OpenHome/Media/Utils/ClockPullerManual.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TChar ClockPullerManual::kShellCommand[] = "clock_pull";

ClockPullerManual::ClockPullerManual(IPullableClock& aPullableClock, Net::IShell& aShell)
    : iPullableClock(aPullableClock)
    , iShell(aShell)
{
    iShell.AddCommandHandler(kShellCommand, *this);
}

ClockPullerManual::~ClockPullerManual()
{
    iShell.RemoveCommandHandler(kShellCommand);
}

void ClockPullerManual::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for \'clock_pull\' command\n"));
        return;
    }
    if (aArgs[0].Bytes() < 3 || aArgs[0][0] < '0' || aArgs[0][0] > '1' || aArgs[0][1] != '.') {
        aResponse.Write(Brn("Error: multiplier must be in the form [0|1].[fraction]\n"));
        return;
    }
    TUint64 mult = IPullableClock::kNominalFreq;
    mult *= aArgs[0][0] - '0';
    TUint div = 1;
    for (TUint i=2; i<aArgs[0].Bytes(); i++) {
        mult *= 10;
        mult += ((TUint64)aArgs[0][i] - '0') * IPullableClock::kNominalFreq;
        div *= 10;
    }
    mult /= div;
    Log::Print("Setting multiplier to %08x\n", mult);
    iPullableClock.PullClock((TUint)mult);
}

void ClockPullerManual::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("clock_pull [multiplier]\n"));
    aResponse.Write(Brn("  set clock pull multiplier\n"));
    aResponse.Write(Brn("  [multiplier] is a float in the range (0..2)\n"));
    aResponse.Write(Brn("  ...which only applies to sources that don't normally support clock pulling\n"));
}
