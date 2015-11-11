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
    virtual TUint64 SubSamplesDiff(TUint64 aPrevSubSamples) const = 0;
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

class IMetadataWriter
{
public:
    virtual void WriteMetadata(const IDidlLiteWriter& aWriter) = 0;
    virtual ~IMetadataWriter() {}
};

class ITrackInfoAccessor
{
public:
    virtual TUint PlaybackPositionMs() const = 0;
    virtual TUint DurationMs() const = 0;
    virtual void WriteMetadata(IMetadataWriter& aWriter) = 0;
    virtual ~ITrackInfoAccessor() {}
};

class ITrackChangeObserver
{
public:
    virtual void RegisterTrackAccessor(const Brx& aUri, ITrackInfoAccessor& aInfoAccessor) = 0;
    virtual void TrackChanged() = 0;    // Unsafe to make any calls on aInfoAccessor during this. Implementors should set a flag and call it from another thread.
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
    SpotifyReporter(IPipelineElementUpstream& aUpstreamElement, MsgFactory& aMsgFactory, TrackFactory& aTrackFactory);
    ~SpotifyReporter();
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from ISpotifyReporter
    TUint64 SubSamples() const override;
    TUint64 SubSamplesDiff(TUint64 aPrevSamples) const override;
public: // from ITrackChangeObserver
    void RegisterTrackAccessor(const Brx& aUri, ITrackInfoAccessor& aInfoAccessor) override;
    void TrackChanged() override;
private: // PipelineElement
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
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
    TrackFactory& iTrackFactory;
    BwsTrackUri iTrackUri;
    ITrackInfoAccessor* iTrackInfoAccessor;
    TBool iMsgTrackPending;
    TBool iMsgDecodedStreamPending;
    MsgDecodedStream* iDecodedStream;
    TUint64 iSubSamples;
    TBool iInterceptMode;
    TBool iPipelineTrackSeen;
    Mutex iLock;
    // SpotifyReporter will receive calls to SubSamples() methods via Spotify
    // callbacks, potentially while also calling out to the ITrackInfoAccessor.
    // To avoid deadlocks, have a separate lock for SubSamples() calls.
    mutable Mutex iLockSubsamples;
};

class MetadataWriter : public IMetadataWriter, private INonCopyable
{
public:
    MetadataWriter(IWriter& aWriter, TUint aBitDepth, TUint aChannels, TUint aSampleRate);
private: // from IMetadataWriter
    void WriteMetadata(const IDidlLiteWriter& aWriter) override;
private:
    IWriter& iWriter;
    TUint iBitDepth;
    TUint iChannels;
    TUint iSampleRate;
};

} // namespace Media
} // namespace OpenHome
