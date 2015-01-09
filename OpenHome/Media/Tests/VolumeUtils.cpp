#include <OpenHome/Media/Tests/VolumeUtils.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

void VolumePrinter::SetVolume(TUint aVolume)
{
    Log::Print("Volume: %u\n", aVolume);
}

void BalancePrinter::SetBalance(TInt aBalance)
{
    Log::Print("Balance: %d\n", aBalance);
}

void MutePrinter::Mute()
{
    Log::Print("Volume: muted\n");
}

void MutePrinter::Unmute()
{
    Log::Print("Volume: unmuted\n");
}

