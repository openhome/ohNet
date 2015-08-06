#ifndef HEADER_PIPELINE_SAMPLE_REPORTER
#define HEADER_PIPELINE_SAMPLE_REPORTER

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/Reporter.h>

namespace OpenHome {
namespace Media {

class ISpotifyReporter
{
public:
    virtual TUint64 SubSamples() = 0;
    virtual TUint64 SubSamplesDiff(TUint64 aPrevSubSamples) = 0;
    virtual ~ISpotifyReporter() {}
};

class ITrackChangeObserver
{
public:
    virtual void TrackChanged(TrackFactory& aTrackFactory, IPipelineIdProvider& aIdProvider, const Brx& aMetadata, TUint aStartMs) = 0;
    virtual ~ITrackChangeObserver() {}
};

/*
 * Element to report number of samples seen since last MsgMode.
 */
class SpotifyReporter : public IPipelineElementUpstream, public ISpotifyReporter, public ITrackChangeObserver, public IPipelinePropertyObserver, private IMsgProcessor, private INonCopyable
{
private:
    static const Brn kInterceptMode;
public:
    SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISpotifyReporter
    TUint64 SubSamples() override;
    TUint64 SubSamplesDiff(TUint64 aPrevSamples) override;
private: // from ITrackChangeObserver
    void TrackChanged(TrackFactory& aTrackFactory, IPipelineIdProvider& aIdProvider, const Brx& aMetadata, TUint aStartMs) override;
private: // from IPipelinePropertyObserver
    void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    // Expects duration of form: H+:MM:SS[.F0/F1]
    static TUint ParseDurationMs(const Brx& aDuration);
private:
    IPipelineElementUpstream& iUpstreamElement;
    IPipelinePropertyObserver& iPropertyObserver;
    TUint iTrackDurationMs;
    TUint64 iTrackOffsetSubSamples;
    TUint64 iReporterSubSampleStart;
    TUint iChannels;
    TUint iSampleRate;
    TUint64 iSubSamples;
    TBool iInterceptMode;
    Mutex iLock;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SAMPLE_REPORTER
