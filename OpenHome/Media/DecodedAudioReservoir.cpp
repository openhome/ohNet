#include <OpenHome/Media/DecodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(TUint aMaxSize)
    : AudioReservoir(aMaxSize)
{
}

TUint DecodedAudioReservoir::Size() const
{
    return Jiffies();
}
