#include <OpenHome/Media/Pipeline/EncodedAudioReservoir.h>
#include <OpenHome/Types.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// EncodedAudioReservoir

EncodedAudioReservoir::EncodedAudioReservoir(TUint aMsgCount, TUint aMaxSessionCount, TUint aMaxStreamCount)
    : iMsgCount(aMsgCount)
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
    return (EncodedAudioCount() > iMsgCount         ||
            EncodedStreamCount() >= iMaxStreamCount ||
            SessionCount() >= iMaxSessionCount);
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
