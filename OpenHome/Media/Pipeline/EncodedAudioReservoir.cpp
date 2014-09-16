#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMaxSize, TUint aMaxSessionCount, TUint aMaxStreamCount)
    : iMaxBytes(aMaxSize)
    , iMaxSessionCount(aMaxSessionCount)
    , iMaxStreamCount(aMaxStreamCount)
{
}

TUint EncodedAudioReservoir::SizeInBytes() const
{
    return EncodedBytes();
}

TBool EncodedAudioReservoir::IsFull() const
{
    return (EncodedBytes() > iMaxBytes || EncodedStreamCount() >= iMaxStreamCount || SessionCount() >= iMaxSessionCount);
}

void EncodedAudioReservoir::ProcessMsgIn(MsgSession* /*aMsg*/)
{
    BlockIfFull();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    BlockIfFull();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
    BlockIfFull();
}
