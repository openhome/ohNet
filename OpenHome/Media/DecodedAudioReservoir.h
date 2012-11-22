#ifndef HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class DecodedAudioReservoir : public AudioReservoir
{
    friend class SuiteDecodedAudioReservoir;
public:
    DecodedAudioReservoir(TUint aMaxSize);
private: // from AudioReservoir
    TUint Size() const;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
