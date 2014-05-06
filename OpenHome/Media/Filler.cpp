#include <OpenHome/Media/Filler.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/IdManager.h>
#include <OpenHome/Media/Protocol/Protocol.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProvider

const Brx& UriProvider::Mode() const
{
    return iMode;
}

UriProvider::UriProvider(const TChar* aMode)
    : iMode(aMode)
{
}

UriProvider::~UriProvider()
{
}


// Filler

Filler::Filler(ISupply& aSupply, IPipelineIdTracker& aIdTracker, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver)
    : Thread("Filler")
    , iLock("FILL")
    , iSupply(aSupply)
    , iPipelineIdTracker(aIdTracker)
    , iActiveUriProvider(NULL)
    , iUriStreamer(NULL)
    , iTrack(NULL)
    , iStopped(true)
    , iSendHalt(false)
    , iQuit(false)
    , iNextHaltId(MsgHalt::kIdNone + 1)
    , iStreamPlayObserver(aStreamPlayObserver)
    , iPrefetchTrackId(kPrefetchTrackIdInvalid)
{
    iNullTrack = aTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty(), NULL, false);
}

Filler::~Filler()
{
    ASSERT(iQuit);
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iNullTrack->RemoveRef();
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

void Filler::Quit()
{
    Kill();
    Join();
}

void Filler::Play(const Brx& aMode, TUint aTrackId)
{
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->Begin(aTrackId);
    iStopped = false;
    Signal();
}

void Filler::PlayLater(const Brx& aMode, TUint aTrackId)
{
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->BeginLater(aTrackId);
    iPrefetchTrackId = aTrackId;
    iStopped = false;
    Signal();
}

TUint Filler::Stop()
{
    AutoMutex a(iLock);
    TUint haltId = MsgHalt::kIdNone;
    if (!iStopped) {
        haltId = ++iNextHaltId;
        iStopped = true;
        iSendHalt = true;
    }
    iUriStreamer->Interrupt(true);
    Signal();
    return haltId;
}

TBool Filler::Next(const Brx& aMode)
{
    TBool ret = false;
    iLock.Wait();
    if (iActiveUriProvider != NULL && iActiveUriProvider->Mode() == aMode) {
        ret = iActiveUriProvider->MoveNext();
        iStopped = false;
        Signal();
    }
    iLock.Signal();
    return ret;
}

TBool Filler::Prev(const Brx& aMode)
{
    TBool ret = false;
    iLock.Wait();
    if (iActiveUriProvider != NULL && iActiveUriProvider->Mode() == aMode) {
        ret = iActiveUriProvider->MovePrevious();
        iStopped = false;
        Signal();
    }
    iLock.Signal();
    return ret;
}

TBool Filler::IsStopped() const
{
    iLock.Wait();
    const TBool stopped = iStopped;
    iLock.Signal();
    return stopped;
}

TUint Filler::NullTrackId() const
{
    return iNullTrack->Id();
}

void Filler::UpdateActiveUriProvider(const Brx& aMode)
{
    iActiveUriProvider = NULL;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        UriProvider* uriProvider = iUriProviders[i];
        if (uriProvider->Mode() == aMode) {
            iActiveUriProvider = uriProvider;
            break;
        }
    }
    if (iActiveUriProvider == NULL) {
        iStopped = true;
        THROW(FillerInvalidMode);
    }
}

void Filler::Run()
{
    try {
        BwsMode mode;
        Wait();
        for (;;) {
            for (;;) {
                iLock.Wait();
                const TBool wait = iStopped;
                const TBool sendHalt = iSendHalt;
                iSendHalt = false;
                iLock.Signal();
                if (!wait) {
                    break;
                }
                if (sendHalt) {
                    iSupply.OutputHalt(iNextHaltId);
                }
                Wait();
            }
            iLock.Wait();
            if (iActiveUriProvider == NULL) {
                iLock.Signal();
                continue;
            }
            if (iTrack != NULL) {
                iTrack->RemoveRef();
                iTrack = NULL;
            }
            iTrackPlayStatus = iActiveUriProvider->GetNext(iTrack);
            TBool failed = false;
            if (iPrefetchTrackId == Track::kIdNone) {
                failed = (iTrack != NULL);
            }
            else if (iPrefetchTrackId != kPrefetchTrackIdInvalid) {
                failed = (iTrack == NULL || iTrack->Id() != iPrefetchTrackId);
            }
            if (failed) {
                iStreamPlayObserver.NotifyTrackFailed(iPrefetchTrackId);
            }
            /* assume that if the uri provider has returned a track then ProtocolManager
                will call OutputTrack, causing Stopper to later call iStreamPlayObserver */
            iPrefetchTrackId = kPrefetchTrackIdInvalid;
            mode.Replace(iActiveUriProvider->Mode());
            if (iTrackPlayStatus == ePlayNo) {
                iSupply.OutputTrack(*iNullTrack, NullTrackStreamHandler::kNullTrackId, Brx::Empty());
                iPipelineIdTracker.AddStream(iNullTrack->Id(), NullTrackStreamHandler::kNullTrackId, NullTrackStreamHandler::kNullTrackStreamId, false /* play later */);
                iSupply.OutputStream(Brx::Empty(), 0, false /* not seekable */, true /* live */, iNullTrackStreamHandler, NullTrackStreamHandler::kNullTrackStreamId);
                iSendHalt = false;
                iStopped = true;
                iLock.Signal();
            }
            else {
                iUriStreamer->Interrupt(false); // FIXME - this could incorrectly over-ride a call to Interrupt() that was scheduled between Wait() and iLock being acquired
                ASSERT(!iStopped); // measure whether the above FIXME occurs in normal use
                iLock.Signal();
                ASSERT(iTrack != NULL);
                (void)iUriStreamer->DoStream(*iTrack, mode);
            }
        }
    }
    catch (ThreadKill&) {
    }
    iQuit = true;
    iSupply.OutputQuit();
}

void Filler::OutputTrack(Track& aTrack, TUint aTrackId, const Brx& aMode)
{
    if (!iQuit) {
        iTrackId = aTrackId;
        iSupply.OutputTrack(aTrack, aTrackId, aMode);
    }
}

void Filler::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    if (!iQuit) {
        iPipelineIdTracker.AddStream(iTrack->Id(), iTrackId, aStreamId, (iTrackPlayStatus==ePlayYes));
        iSupply.OutputStream(aUri, aTotalBytes, aSeekable, aLive, aStreamHandler, aStreamId);
    }
}

void Filler::OutputData(const Brx& aData)
{
    if (!iQuit) {
        iSupply.OutputData(aData);
    }
}

void Filler::OutputMetadata(const Brx& aMetadata)
{
    if (!iQuit) {
        iSupply.OutputMetadata(aMetadata);
    }
}

void Filler::OutputFlush(TUint aFlushId)
{
    if (!iQuit) {
        iSupply.OutputFlush(aFlushId);
    }
}

void Filler::OutputWait()
{
    if (!iQuit) {
        iSupply.OutputWait();
    }
}

void Filler::OutputHalt(TUint aHaltId)
{
    if (!iQuit) {
        iSupply.OutputHalt(aHaltId);
    }
}

void Filler::OutputQuit()
{
    ASSERTS();
}


// Filler::NullTrackStreamHandler

EStreamPlay Filler::NullTrackStreamHandler::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return ePlayLater;
}

TUint Filler::NullTrackStreamHandler::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint Filler::NullTrackStreamHandler::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

TBool Filler::NullTrackStreamHandler::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}

void Filler::NullTrackStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aTrackId*/, TUint /*aStreamId*/)
{
}
