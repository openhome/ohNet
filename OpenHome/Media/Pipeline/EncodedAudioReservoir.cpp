#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMaxSize, TUint aMaxStreamCount)
    : AudioReservoir(aMaxSize, aMaxStreamCount)
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

TUint EncodedAudioReservoir::StreamCount() const
{
    return EncodedStreamCount();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
    BlockIfFull();
}
