#pragma once

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
    SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory, IPipelinePropertyObserver& aObserver);
    ~SpotifyReporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISpotifyReporter
    TUint64 SubSamples() override;
    TUint64 SubSamplesDiff(TUint64 aPrevSamples) override;
private: // from ITrackChangeObserver
    // FIXME - when this is called, output a new MsgTrack (it's fine to increment its ID), but do not mark it as start-of-stream to stop upstream elements going into new-stream-detect behaviour
    // and also output a new MsgDecodedStream, if available/seen (using the same ID as last seen MsgDecodedStream (for Spotify!)).
    void TrackChanged(TrackFactory& aTrackFactory, IPipelineIdProvider& aIdProvider, const Brx& aMetadata, TUint aStartMs) override;
    // FIXME - can try removing this interface implementation completely, as outputting the two messages above should now allow correct reporting of all elements.
private: // from IPipelinePropertyObserver
    void NotifyMode(const Brx& aMode, const ModeInfo& aInfo) override;
    void NotifyTrack(Track& aTrack, const Brx& aMode, TBool aStartOfStream) override;
    void NotifyMetaText(const Brx& aText) override;
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds) override;
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo) override;
    // FIXME - can also derive from new pipeline element classes and only implement subset of IMsgProcessor methods that are actually required.
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
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private:
    // Expects duration of form: H+:MM:SS[.F0/F1]
    static TUint ParseDurationMs(const Brx& aDuration);
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgFactory& iMsgFactory;
    // FIXME - if removing implementation of above interfaces, can probably also remove iPropertyObserver, track duration, one or more of the subsample counters and iInterceptMode. And maybe also iChannels/iSampleRate if storing a pointer to a MsgDecodedStream.
    IPipelinePropertyObserver& iPropertyObserver;
    TUint iTrackDurationMs;
    TUint64 iTrackOffsetSubSamples;
    TUint64 iReporterSubSampleStart;
    Track* iTrackPending;
    TBool iMsgDecodedStreamPending;
    MsgDecodedStream* iDecodedStream;
    TUint iChannels;
    TUint iSampleRate;
    TUint64 iSubSamples;
    TBool iInterceptMode;
    Mutex iLock;
};

} // namespace Media
} // namespace OpenHome

