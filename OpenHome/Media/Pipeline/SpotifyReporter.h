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

class IDidlLiteWriter
{
public:
    static const TUint kMaxBytes = kTrackMetaDataMaxBytes;
public:
    // Implementor must omit any attributes with value 0.
    virtual void WriteDidlLite(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const = 0;
    virtual ~IDidlLiteWriter() {}
};

class ITrackChangeObserver
{
public:
    virtual void TrackChanged(TrackFactory& aTrackFactory, const Brx& aUri, const IDidlLiteWriter& aWriter, TUint aDurationMs) = 0;
    virtual ~ITrackChangeObserver() {}
};

/*
 * Element to report number of samples seen since last MsgMode.
 */
class SpotifyReporter : public PipelineElement, public IPipelineElementUpstream, public ISpotifyReporter, public ITrackChangeObserver, private INonCopyable
{
private:
    static const TUint kSupportedMsgTypes;
    static const Brn kInterceptMode;
public:
    SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory);
    ~SpotifyReporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISpotifyReporter
    TUint64 SubSamples() override;
    TUint64 SubSamplesDiff(TUint64 aPrevSamples) override;
public: // from ITrackChangeObserver
    void TrackChanged(TrackFactory& aTrackFactory, const Brx& aUri, const IDidlLiteWriter& aWriter, TUint aDurationMs) override;
private: // PipelineElement
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    void ClearDecodedStreamLocked();
    void UpdateDecodedStreamLocked(MsgDecodedStream& aMsg);
    TUint64 TrackLengthJiffiesLocked() const;
    MsgDecodedStream* CreateMsgDecodedStreamLocked() const;
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgFactory& iMsgFactory;
    TUint iTrackDurationMs;
    TUint64 iTrackOffsetSamples;
    Track* iTrackPending;
    TBool iMsgDecodedStreamPending;
    MsgDecodedStream* iDecodedStream;
    TUint64 iSubSamples;
    TBool iInterceptMode;
    Mutex iLock;
};

} // namespace Media
} // namespace OpenHome
