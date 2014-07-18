#ifndef HEADER_PIPELINE_RAMPER
#define HEADER_PIPELINE_RAMPER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which applies a ramp up at the start of a stream when necessary.
Is NOT responsible for all ramping.  Many other elements also apply ramps in other circumstances.
*/

class Ramper : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
    friend class SuiteRamper;
public:
    Ramper(IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration);
    virtual ~Ramper();
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    Msg* ProcessAudio(MsgAudio* aMsg);
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iUpstreamElement;
    TUint iTrackId;
    TUint iStreamId;
    TBool iRamping;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_RAMPER
