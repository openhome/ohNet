#ifndef HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class EncodedAudioReservoir : public AudioReservoir
{
public:
    EncodedAudioReservoir(TUint aMaxSize);
    TUint SizeInBytes() const;
private: // from AudioReservoir
    TUint Size() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgAudioEncoded* aMsg);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
