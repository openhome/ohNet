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
    DecodedAudioReservoir(IPipelineElementUpstream& aUpstreamElement, TUint aMaxSize);
    ~DecodedAudioReservoir();
private: // from AudioReservoir
    TUint Size() const;
private: // from MsgQueueFlushable
    void ProcessMsgIn(MsgQuit* aMsg);
private:
    void PullerThread();
private:
    IPipelineElementUpstream& iUpstreamElement;
    ThreadFunctor* iThread;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
