#ifndef HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class EncodedAudioReservoir : public AudioReservoir, public IPipelineElementDownstream
{
public:
    EncodedAudioReservoir(TUint aMaxSize);
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private: // from AudioReservoir
    TUint Size() const;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_ENCODED_AUDIO_RESERVOIR
