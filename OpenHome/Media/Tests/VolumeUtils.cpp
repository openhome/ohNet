#include <OpenHome/Media/Tests/VolumeUtils.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

TUint VolumeProfileDummy::MaxVolume() const
{
    return 100;
}

TUint VolumeProfileDummy::VolumeUnity() const
{
    return 80;
}

TUint VolumeProfileDummy::VolumeSteps() const
{
    return MaxVolume();  // [0..100] in steps of 1
}

TUint VolumeProfileDummy::VolumeMilliDbPerStep() const
{
    return 1024;
}

TInt VolumeProfileDummy::MaxBalance() const
{
    return 15;
}

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

