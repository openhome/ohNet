#ifndef HEADER_PIPELINE_FILLER
#define HEADER_PIPELINE_FILLER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>

#include <vector>

EXCEPTION(FillerInvalidMode);
EXCEPTION(UriProviderInvalidId);

namespace OpenHome {
namespace Media {

class UriProvider
{
public:
    virtual ~UriProvider();
    const Brx& Mode() const;
    virtual void Begin(TUint aTrackId) = 0;
    virtual void BeginLater(TUint aTrackId) = 0; // Queue a track but return ePlayLater when OkToPlay() is called
    virtual EStreamPlay GetNext(Track*& aTrack) = 0;
    virtual TUint CurrentTrackId() const = 0; // Id of last delivered track.  Or of pending track requested via Begin or Move[After|Before]
    virtual TBool MoveNext() = 0; // returns true if GetNext would return a non-NULL track and ePlayYes
    virtual TBool MovePrevious() = 0; // returns true if GetNext would return a non-NULL track and ePlayYes
protected:
    UriProvider(const TChar* aMode);
private:
    BwsMode iMode;
};

class Filler : private Thread, public ISupply
{
public:
    Filler(ISupply& aSupply, IPipelineIdTracker& aPipelineIdTracker);
    ~Filler();
    void Add(UriProvider& aUriProvider);
    void Start(IUriStreamer& aUriStreamer);
    void Play(const Brx& aMode, TUint aTrackId);
    void PlayLater(const Brx& aMode, TUint aTrackId);
    TUint Stop(); // returns Id of MsgHalt which will (eventually) be generated
    void StopNoHalt(); // use during shutdown only
    TBool Next(const Brx& aMode);
    TBool Prev(const Brx& aMode);
    TBool IsStopped() const;
private:
    void UpdateActiveUriProvider(const Brx& aMode);
private: // from Thread
    void Run();
private: // from ISupply
    void OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputHalt(TUint aHaltId);
    void OutputQuit();
private:
    mutable Mutex iLock;
    ISupply& iSupply;
    IPipelineIdTracker& iPipelineIdTracker;
    std::vector<UriProvider*> iUriProviders;
    UriProvider* iActiveUriProvider;
    IUriStreamer* iUriStreamer;
    Track* iTrack;
    TUint iTrackId;
    TBool iStopped;
    TBool iSendHalt;
    TBool iGetPrevious;
    TBool iQuit;
    EStreamPlay iTrackPlayStatus;
    TUint iNextHaltId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_FILLER
