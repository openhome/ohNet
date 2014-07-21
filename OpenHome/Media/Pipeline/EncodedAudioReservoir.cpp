#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMaxSize)
    : AudioReservoir(aMaxSize)
{
}

TUint EncodedAudioReservoir::SizeInBytes() const
{
    return EncodedBytes();
}

TUint EncodedAudioReservoir::Size() const
{
    return EncodedBytes();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
    BlockIfFull();
}
