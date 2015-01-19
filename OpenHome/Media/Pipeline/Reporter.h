#ifndef HEADER_PIPELINE_REPORTER
#define HEADER_PIPELINE_REPORTER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class IPipelinePropertyObserver
{
public:
    virtual void NotifyTrack(Track& aTrack, const Brx& aMode, TUint aIdPipeline) = 0;
    virtual void NotifyMetaText(const Brx& aText) = 0;
    virtual void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) = 0;
    virtual void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) = 0;
};

/*
Element which reports state changes in pipeline.
Is passive - it reports on Msgs but doesn't create/destroy/edit them.
*/

class Reporter : public IPipelineElementUpstream, private IMsgProcessor, private INonCopyable
{
    static const Brn kNullMetaText;
public:
    Reporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver);
    virtual ~Reporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
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
    IPipelinePropertyObserver& iObserver;
    TBool iTimeInvalid;
    TUint iSeconds;
    TUint iJiffies; // Fraction of a second
    TUint iTrackDurationSeconds;
    BwsMode iMode;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_REPORTER
