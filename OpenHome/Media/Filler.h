#ifndef HEADER_PIPELINE_FILLER
#define HEADER_PIPELINE_FILLER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/Protocol/Protocol.h>

#include <vector>

EXCEPTION(FillerInvalidStyle);
EXCEPTION(UriProviderInvalidId);

namespace OpenHome {
namespace Media {

typedef Bws<32> BwsStyle;
typedef Bws<32> BwsProviderId;
typedef Bws<1024> BwsTrackUri;

class UriProvider
{
public:
    const Brx& Style() const;
    virtual void Begin(const Brx& aProviderId) = 0;
    virtual EStreamPlay GetNext(BwsTrackUri& aUrl, BwsProviderId& aProviderId) = 0;
    virtual EStreamPlay GetPrev(BwsTrackUri& aUrl, BwsProviderId& aProviderId) = 0;
protected:
    UriProvider(const TChar* aStyle);
private:
    BwsStyle iStyle;
};

class Filler : private Thread, public ISupply
{
public:
    Filler(ISupply& aSupply, IPipelineIdTracker& aPipelineIdTracker);
    ~Filler();
    void Add(UriProvider& aUriProvider);
    void Start(IUriStreamer& aUriStreamer);
    void Play(const Brx& aStyle, const Brx& aProviderId);
    void Stop();
    void Next();
    void Prev();
private: // from Thread
    void Run();
private: // from ISupply
    void OutputTrack(const Brx& aUri, TUint aTrackId);
    void OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId);
    void OutputData(const Brx& aData);
    void OutputMetadata(const Brx& aMetadata);
    void OutputFlush(TUint aFlushId);
    void OutputQuit();
private:
    Mutex iLock;
    ISupply& iSupply;
    IPipelineIdTracker& iPipelineIdTracker;
    std::vector<UriProvider*> iUriProviders;
    UriProvider* iActiveUriProvider;
    IUriStreamer* iUriStreamer;
    BwsTrackUri iTrackUri;
    TUint iTrackId;
    BwsStyle iStyle;
    BwsProviderId iProviderId;
    TBool iStopped;
    TBool iGetPrevious;
    TBool iQuit;
    EStreamPlay iTrackPlayStatus;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_FILLER
