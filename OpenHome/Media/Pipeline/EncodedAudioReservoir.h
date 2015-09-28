#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class EncodedAudioReservoir : public AudioReservoir
{
public:
    EncodedAudioReservoir(TUint aMsgCount, TUint aMaxStreamCount);
    TUint SizeInBytes() const;
private: // from AudioReservoir
    TBool IsFull() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgEncodedStream* aMsg);
    void ProcessMsgIn(MsgAudioEncoded* aMsg);
private:
    const TUint iMsgCount;
    const TUint iMaxStreamCount;
};

} // namespace Media
} // namespace OpenHome

