#ifndef HEADER_PIPELINE_SAMPLE_REPORTER
#define HEADER_PIPELINE_SAMPLE_REPORTER

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>

namespace OpenHome {
namespace Media {

class ISampleReporter
{
public:
    virtual TUint SubSamples() = 0;
    virtual TUint SubSamplesDiff(TUint aPrevSubSamples) = 0;
    virtual ~ISampleReporter() {}
};

/*
 * Element to report number of samples seen since last MsgMode.
 */
class SampleReporter : public IPipelineElementUpstream, public ISampleReporter, private IMsgProcessor, private INonCopyable
{
public:
    SampleReporter(IPipelineElementUpstream& aUpstreamElement);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISampleReporter
    TUint SubSamples() override;
    TUint SubSamplesDiff(TUint aPrevSamples) override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    TUint iChannels;
    TUint iSampleRate;
    TUint iSubSamples;
    TUint iOverflowCount;
    Mutex iLock;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SAMPLE_REPORTER
