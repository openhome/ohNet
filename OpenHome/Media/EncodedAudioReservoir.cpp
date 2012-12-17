#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMaxSize)
    : AudioReservoir(aMaxSize)
{
}

TUint EncodedAudioReservoir::Size() const
{
    return EncodedBytes();
}
