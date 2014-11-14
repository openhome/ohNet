#ifndef HEADER_PIPELINE_FILLER
#define HEADER_PIPELINE_FILLER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>

#include <limits.h>
#include <vector>

EXCEPTION(FillerInvalidMode);
EXCEPTION(UriProviderInvalidId);

namespace OpenHome {
namespace Media {

class IClockPuller;

class UriProvider
{
public:
    virtual ~UriProvider();
    const Brx& Mode() const;
    TBool SupportsLatency() const;
    TBool IsRealTime() const;
    virtual IClockPuller* ClockPuller();
    virtual void Begin(TUint aTrackId) = 0;
    virtual void BeginLater(TUint aTrackId) = 0; // Queue a track but return ePlayLater when OkToPlay() is called
    virtual EStreamPlay GetNext(Track*& aTrack) = 0;
    virtual TUint CurrentTrackId() const = 0; // Id of last delivered track.  Or of pending track requested via Begin or Move[After|Before]
    virtual TBool MoveNext() = 0; // returns true if GetNext would return a non-NULL track and ePlayYes
    virtual TBool MovePrevious() = 0; // returns true if GetNext would return a non-NULL track and ePlayYes
protected:
    UriProvider(const TChar* aMode, TBool aSupportsLatency, TBool aRealTime);
private:
    BwsMode iMode;
    TBool iSupportsLatency;
    TBool iRealTime;
};

class Filler : private Thread, public ISupply
{
    static const TUint kPrefetchTrackIdInvalid = UINT_MAX;
public:
    Filler(ISupply& aSupply, IPipelineIdTracker& aPipelineIdTracker, IFlushIdProvider& aFlushIdProvider, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver, TUint aDefaultDelay);
    ~Filler();
    void Add(UriProvider& aUriProvider);
    void Start(IUriStreamer& aUriStreamer);
    void Quit();
    void Play(const Brx& aMode, TUint aTrackId);
    void PlayLater(const Brx& aMode, TUint aTrackId);
    TUint Stop(); // Stops filler and encourages protocols to stop.  Returns haltId iff filler was active
    TUint Flush(); // Stops filler, encourages protocols to stop.  Returns flushId.  MsgFlush will be delivered once protocol is stopped.
    TBool Next(const Brx& aMode);
    TBool Prev(const Brx& aMode);
    TBool IsStopped() const;
    TUint NullTrackId() const;
private:
    void UpdateActiveUriProvider(const Brx& aMode);
    TUint StopLocked();
private: // from Thread
    void Run();
private: // from ISupply
    void OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller) override;
    void OutputSession() override;
    void OutputTrack(Track& aTrack, TUint aTrackId) override;
    void OutputDelay(TUint aJiffies) override;
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId) override;
    void OutputPcmStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId, const PcmStreamInfo& aPcmStream) override;
    void OutputData(const Brx& aData) override;
    void OutputMetadata(const Brx& aMetadata) override;
    void OutputFlush(TUint aFlushId) override;
    void OutputWait() override;
    void OutputHalt(TUint aHaltId) override;
    void OutputQuit() override;
private:
    class NullTrackStreamHandler : public IStreamHandler
    {
    public:
        static const TUint kNullTrackId = 0;
        static const TUint kNullTrackStreamId = 1;
    private: // from IStreamHandler
        EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
        TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
        TUint TryStop(TUint aTrackId, TUint aStreamId);
        TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
        void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
    };
private:
    mutable Mutex iLock;
    ISupply& iSupply;
    IPipelineIdTracker& iPipelineIdTracker;
    IFlushIdProvider& iFlushIdProvider;
    std::vector<UriProvider*> iUriProviders;
    UriProvider* iActiveUriProvider;
    IUriStreamer* iUriStreamer;
    Track* iTrack;
    TUint iTrackId;
    TBool iStopped;
    TBool iSendHalt;
    TBool iQuit;
    TBool iChangedMode;
    EStreamPlay iTrackPlayStatus;
    TUint iNextHaltId;
    TUint iNextFlushId;
    Track* iNullTrack; // delivered when uri provider cannot return a Track
    NullTrackStreamHandler iNullTrackStreamHandler;
    IStreamPlayObserver& iStreamPlayObserver;
    const TUint iDefaultDelay;
    TUint iPrefetchTrackId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_FILLER
