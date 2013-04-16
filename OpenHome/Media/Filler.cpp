#include <OpenHome/Media/Filler.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/IdProvider.h>
#include <OpenHome/Media/Protocol/Protocol.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProvider

const Brx& UriProvider::Style() const
{
    return iStyle;
}

UriProvider::UriProvider(const TChar* aStyle)
    : iStyle(aStyle)
{
}

UriProvider::~UriProvider()
{
}


// Filler

Filler::Filler(ISupply& aSupply, IPipelineIdTracker& aIdTracker)
    : Thread("Fill")
    , iLock("FILL")
    , iSupply(aSupply)
    , iPipelineIdTracker(aIdTracker)
    , iActiveUriProvider(NULL)
    , iUriStreamer(NULL)
    , iStopped(true)
    , iGetPrevious(false)
    , iQuit(false)
{
}

Filler::~Filler()
{
    Kill();
    Join();
}

void Filler::Add(UriProvider& aUriProvider)
{
    iUriProviders.push_back(&aUriProvider);
}

void Filler::Start(IUriStreamer& aUriStreamer)
{
    iUriStreamer = &aUriStreamer;
    Thread::Start();
}

void Filler::Play(const Brx& aStyle, const Brx& aProviderId)
{
    AutoMutex a(iLock);
    iActiveUriProvider = NULL;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        UriProvider* uriProvider = iUriProviders[i];
        if (uriProvider->Style() == aStyle) {
            iActiveUriProvider = uriProvider;
            break;
        }
    }
    if (iActiveUriProvider == NULL) {
        iStopped = true;
        THROW(FillerInvalidStyle);
    }
    iActiveUriProvider->Begin(aProviderId);
    iStopped = false;
    iGetPrevious = false;
    Signal();
}

void Filler::Stop()
{
    iLock.Wait();
    iStopped = true;
    iGetPrevious = false;
    Signal();
    iLock.Signal();
}

void Filler::Next()
{
    iLock.Wait();
    iGetPrevious = false;
    iStopped = false;
    Signal();
    iLock.Signal();
}

void Filler::Prev()
{
    iLock.Wait();
    iGetPrevious = true;
    iStopped = false;
    Signal();
    iLock.Signal();
}

void Filler::Run()
{
    while (!iQuit) {
        for (;;) {
            iLock.Wait();
            const TBool wait = iStopped;
            iLock.Signal();
            if (!wait) {
                break;
            }
            Wait();
        }
        iLock.Wait();
        if (iActiveUriProvider == NULL) {
            iLock.Signal();
            continue;
        }
        iStyle.Replace(iActiveUriProvider->Style());
        iTrackPlayStatus = (iGetPrevious? iActiveUriProvider->GetPrev(iTrackUri, iProviderId) :
                                          iActiveUriProvider->GetNext(iTrackUri, iProviderId));
        iGetPrevious = false;
        iLock.Signal();
        if (iTrackPlayStatus == ePlayNo) {
            // FIXME - iSupply.OutputHalt ??
            iStopped = true;
        }
        else {
            (void)iUriStreamer->DoStream(iTrackUri);
        }
    }
}

void Filler::OutputTrack(const Brx& aUri, TUint aTrackId)
{
    iTrackId = aTrackId;
    iSupply.OutputTrack(aUri, aTrackId);
}

void Filler::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    iPipelineIdTracker.AddStream(iStyle, iProviderId, iTrackId, aStreamId, (iTrackPlayStatus==ePlayYes));
    iSupply.OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
}

void Filler::OutputData(const Brx& aData)
{
    iSupply.OutputData(aData);
}

void Filler::OutputMetadata(const Brx& aMetadata)
{
    iSupply.OutputMetadata(aMetadata);
}

void Filler::OutputFlush(TUint aFlushId)
{
    iSupply.OutputFlush(aFlushId);
}

void Filler::OutputQuit()
{
    iQuit = true;
    iSupply.OutputQuit();
    Signal();
}
