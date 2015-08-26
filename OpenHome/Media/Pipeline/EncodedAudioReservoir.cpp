#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMsgCount, TUint aMaxStreamCount)
    : iMsgCount(aMsgCount)
    , iMaxStreamCount(aMaxStreamCount)
{
}

TUint EncodedAudioReservoir::SizeInBytes() const
{
    return EncodedBytes();
}

TBool EncodedAudioReservoir::IsFull() const
{
    return (EncodedAudioCount() > iMsgCount ||
            TrackCount() >= iMaxStreamCount ||
            EncodedStreamCount() >= iMaxStreamCount);
}

void EncodedAudioReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    BlockIfFull();
}

void EncodedAudioReservoir::ProcessMsgIn(MsgAudioEncoded* /*aMsg*/)
{
    BlockIfFull();
}
