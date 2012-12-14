#include <OpenHome/Media/EncodedAudioReservoir.h>
#include <OpenHome/OhNetTypes.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMaxSize)
    : AudioReservoir(aMaxSize)
{
}

void EncodedAudioReservoir::Push(Msg* aMsg)
{
    (void)Enqueue(aMsg);
}

TUint EncodedAudioReservoir::Size() const
{
    return EncodedBytes();
}
