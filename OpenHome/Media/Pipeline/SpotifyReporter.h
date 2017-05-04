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
    virtual TUint64 SubSamples() const = 0;
    virtual ~ISpotifyReporter() {}
};

class ISpotifyMetadata
{
public:
    // FIXME - omit what isn't required from this interface.
    virtual const Brx& PlaybackSource() const = 0;
    virtual const Brx& PlaybackSourceUri() const = 0;
    virtual const Brx& Track() const = 0;
    virtual const Brx& TrackUri() const = 0;
    virtual const Brx& Artist() const = 0;
    virtual const Brx& ArtistUri() const = 0;
    virtual const Brx& Album() const = 0;
    virtual const Brx& AlbumUri() const = 0;
    virtual const Brx& AlbumCoverUri() const = 0;
    virtual const Brx& AlbumCoverUrl() const = 0;
    virtual TUint DurationMs() const = 0;
    virtual void Destroy() = 0;
    virtual ~ISpotifyMetadata() {}
};

class ISpotifyTrackObserver
{
public:
    virtual void TrackChanged(Media::ISpotifyMetadata* aMetadata) = 0;
    virtual void TrackOffsetChanged(TUint aOffsetMs) = 0;
    virtual void FlushTrackState() = 0;
    virtual ~ISpotifyTrackObserver() {}
};

class SpotifyDidlLiteWriter : private INonCopyable
{
private:
    // H+:MM:SS[.F0/F1]
    // Fraction of seconds is fixed (value is in milliseconds, so F0 is always
    // 3 bytes, and F1 always has value 1000, i.e., is 4 bytes).
    // Everything else apart from hours is fixed. Assume no track will ever be
    // >99 hours, so hours requires 2 bytes.
    // Therefore, need enough bytes for string of form: 12:34:56.789/1000
    static const TUint kMaxDurationBytes = 17;
public:
    SpotifyDidlLiteWriter(const Brx& aUri, ISpotifyMetadata& aMetadata);
    void Write(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const;
private:
    void SetDurationString(Bwx& aBuf) const;
    void WriteRes(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const;
    void WriteOptionalAttributes(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate) const;
protected:
    const BwsTrackUri iUri;
    const ISpotifyMetadata& iMetadata;
};

/**
 * Helper class to store start offset expressed in milliseconds or samples.
 * Each call to either of the Set() methods overwrites any value set (be it in
 * milliseconds or samples) in a previous call.
 */
class StartOffset
{
public:
    StartOffset();
    void SetMs(TUint aOffsetMs);
    TUint64 OffsetSample(TUint aSampleRate) const;
private:
    TUint iOffsetMs;
};

/*
 * Element to report number of samples seen since last MsgMode.
 */
class SpotifyReporter : public PipelineElement, public IPipelineElementUpstream, public ISpotifyReporter, public ISpotifyTrackObserver, private INonCopyable
{
private:
    static const TUint kSupportedMsgTypes;
    static const Brn kInterceptMode;
public:
    SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory, TrackFactory& aTrackFactory);
    ~SpotifyReporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISpotifyReporter
    TUint64 SubSamples() const override;
public: // from ISpotifyTrackObserver
    void TrackChanged(Media::ISpotifyMetadata* aMetadata) override;
    void TrackOffsetChanged(TUint aOffsetMs) override;
    void FlushTrackState() override;
private: // PipelineElement
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    void ClearDecodedStream();
    void UpdateDecodedStream(MsgDecodedStream& aMsg);
    TUint64 TrackLengthJiffiesLocked() const;
    MsgDecodedStream* CreateMsgDecodedStreamLocked() const;
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgFactory& iMsgFactory;
    TrackFactory& iTrackFactory;
    StartOffset iStartOffset;
    TUint iTrackDurationMs;
    BwsTrackUri iTrackUri;
    ISpotifyMetadata* iMetadata;
    TBool iMsgDecodedStreamPending;
    MsgDecodedStream* iDecodedStream;
    TUint64 iSubSamples;
    TBool iInterceptMode;
    TBool iPipelineTrackSeen;
    mutable Mutex iLock;
};

} // namespace Media
} // namespace OpenHome
