#ifndef HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class EncodedAudioReservoir : public AudioReservoir
{
public:
    EncodedAudioReservoir(TUint aMaxSize, TUint aMaxSessionCount, TUint aMaxStreamCount);
    TUint SizeInBytes() const;
private: // from AudioReservoir
    TBool IsFull() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgSession* aMsg);
    void ProcessMsgIn(MsgEncodedStream* aMsg);
    void ProcessMsgIn(MsgAudioEncoded* aMsg);
private:
    const TUint iMaxBytes;
    const TUint iMaxSessionCount;
    const TUint iMaxStreamCount;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
