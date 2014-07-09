#ifndef HEADER_PIPELINE_AGGREGATOR
#define HEADER_PIPELINE_AGGREGATOR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Utility class which is not part of the generic pipeline.
May be used by audio drivers to combine/split audio data to a preferred duration.
May send shorter msg if format change or Halt is encountered.
*/

class Aggregator : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
    friend class SuiteAggregator;
public:
    Aggregator(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies);
    virtual ~Aggregator();
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    Msg* NextStoredMsg(TBool aDeliverShortPlayable);
    Msg* AddPlayable(MsgPlayable* aPlayable);
    void CalculateMaxPlayable();
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
    const TUint iMaxPlayableJiffies;
    TUint iMaxPlayableBytes;
    MsgPlayable* iPlayable;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    Msg* iPending;
    TBool iRecalculateMaxPlayable;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_AGGREGATOR
