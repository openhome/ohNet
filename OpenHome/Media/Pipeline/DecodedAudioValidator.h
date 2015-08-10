#ifndef HEADER_DECODED_AUDIO_VALIDATOR
#define HEADER_DECODED_AUDIO_VALIDATOR

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class DecodedAudioValidator : public PipelineElement, public IPipelineElementUpstream, public IPipelineElementDownstream
{
    static const TUint kSupportedMsgTypes;
public:
    DecodedAudioValidator(IPipelineElementUpstream& aUpstream, const TChar* aId);
    DecodedAudioValidator(const TChar* aId, IPipelineElementDownstream& aDownstream);
    void SetEnabled(); /* Normally enabled by default.
                          Can disable manually to limit testing to certain points in the pipeline */
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    IPipelineElementUpstream* iUpstream;
    IPipelineElementDownstream* iDownstream;
    const TChar* iId;
    TUint64 iStreamPos;
    TBool iExpectDecodedStreamBeforeAudio;
    TBool iEnabled;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_DECODED_AUDIO_VALIDATOR
