#ifndef HEADER_PIPELINE_REPORTER
#define HEADER_PIPELINE_REPORTER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class IPipelinePropertyObserver
{
public:
    virtual void NotifyTrack(const Brx& aUri, TUint aIdPipeline) = 0;
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
    Msg* Pull();
private: // IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iUpstreamElement;
    IPipelinePropertyObserver& iObserver;
    TBool iTimeInvalid;
    TUint iSeconds;
    TUint iJiffies; // Fraction of a second
    TUint iTrackDurationSeconds;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_REPORTER
