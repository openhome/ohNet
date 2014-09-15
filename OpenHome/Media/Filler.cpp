#include <OpenHome/Media/Filler.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/IdManager.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// UriProvider

const Brx& UriProvider::Mode() const
{
    return iMode;
}

TBool UriProvider::SupportsLatency() const
{
    return iSupportsLatency;
}

TBool UriProvider::IsRealTime() const
{
    return iRealTime;
}

IClockPuller* UriProvider::ClockPuller()
{
    return NULL;
}

UriProvider::UriProvider(const TChar* aMode, TBool aSupportsLatency, TBool aRealTime)
    : iMode(aMode)
    , iSupportsLatency(aSupportsLatency)
    , iRealTime(aRealTime)
{
}

UriProvider::~UriProvider()
{
}


// Filler

Filler::Filler(ISupply& aSupply, IPipelineIdTracker& aIdTracker, IFlushIdProvider& aFlushIdProvider, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver, TUint aDefaultDelay)
    : Thread("Filler", kPriorityVeryHigh-3)
    , iLock("FILL")
    , iSupply(aSupply)
    , iPipelineIdTracker(aIdTracker)
    , iFlushIdProvider(aFlushIdProvider)
    , iActiveUriProvider(NULL)
    , iUriStreamer(NULL)
    , iTrack(NULL)
    , iStopped(true)
    , iSendHalt(false)
    , iQuit(false)
    , iChangedMode(true)
    , iNextHaltId(MsgHalt::kIdNone + 1)
    , iNextFlushId(MsgFlush::kIdInvalid)
    , iStreamPlayObserver(aStreamPlayObserver)
    , iDefaultDelay(aDefaultDelay)
    , iPrefetchTrackId(kPrefetchTrackIdInvalid)
{
    iNullTrack = aTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
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
    const TUint haltId = StopLocked();
    Signal();
    return haltId;
}

TUint Filler::Flush()
{
    AutoMutex a(iLock);
    (void)StopLocked();
    if (iNextFlushId == MsgFlush::kIdInvalid) {
        iNextFlushId = iFlushIdProvider.NextFlushId();
    }
    Signal();
    return iNextFlushId;
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
    UriProvider* prevUriProvider = iActiveUriProvider;
    iActiveUriProvider = NULL;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        UriProvider* uriProvider = iUriProviders[i];
        if (uriProvider->Mode() == aMode) {
            iActiveUriProvider = uriProvider;
            break;
        }
    }
    iChangedMode = iChangedMode || (prevUriProvider != iActiveUriProvider);
    if (iActiveUriProvider == NULL) {
        iStopped = true;
        THROW(FillerInvalidMode);
    }
}

TUint Filler::StopLocked()
{
    TUint haltId = MsgHalt::kIdNone;
    LOG(kMedia, "Filler::StopLocked iStopped=%u\n", iStopped);
    if (!iStopped) {
        haltId = ++iNextHaltId;
        iStopped = true;
        iSendHalt = true;
    }
    iUriStreamer->Interrupt(true);
    return haltId;
}

void Filler::Run()
{
    try {
        Wait();
        for (;;) {
            for (;;) {
                iLock.Wait();
                const TBool wait = iStopped;
                const TBool sendHalt = iSendHalt;
                iSendHalt = false;
                if (iNextFlushId != MsgFlush::kIdInvalid) {
                    iSupply.OutputFlush(iNextFlushId);
                    iNextFlushId = MsgFlush::kIdInvalid;
                }
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
            LOG(kMedia, "FILLER: iActiveUriProvider->GetNext() returned trackId=%u, status=%d\n", iTrack? iTrack->Id() : 0, iTrackPlayStatus);
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
            if (iTrackPlayStatus == ePlayNo) {
                OutputMode(Brn("null"), false, true, NULL);
                OutputSession();
                iChangedMode = true;
                iSupply.OutputTrack(*iNullTrack, NullTrackStreamHandler::kNullTrackId);
                iPipelineIdTracker.AddStream(iNullTrack->Id(), NullTrackStreamHandler::kNullTrackId, NullTrackStreamHandler::kNullTrackStreamId, false /* play later */);
                iSupply.OutputStream(Brx::Empty(), 0, false /* not seekable */, true /* live */, iNullTrackStreamHandler, NullTrackStreamHandler::kNullTrackStreamId);
                OutputDelay(iDefaultDelay);
                iSendHalt = false;
                iStopped = true;
                iLock.Signal();
            }
            else {
                iUriStreamer->Interrupt(false); // FIXME - this could incorrectly over-ride a call to Interrupt() that was scheduled between Wait() and iLock being acquired
                ASSERT(!iStopped); // measure whether the above FIXME occurs in normal use
                if (iChangedMode) {
                    const TBool supportsLatency = iActiveUriProvider->SupportsLatency();
                    const TBool realTime = iActiveUriProvider->IsRealTime();
                    ASSERT(!supportsLatency || realTime); /* VariableDelay handling of NotifyStarving would be
                                                             hard/impossible if the Gorger was allowed to buffer
                                                             content between the two VariableDelays */
                    OutputMode(iActiveUriProvider->Mode(), supportsLatency, realTime, iActiveUriProvider->ClockPuller());
                    if (!supportsLatency) {
                        OutputDelay(iDefaultDelay);
                    }
                    iChangedMode = false;
                }
                iLock.Signal();
                ASSERT(iTrack != NULL);
                OutputSession();
                LOG(kMedia, "> iUriStreamer->DoStream(%u)\n", iTrack->Id());
                (void)iUriStreamer->DoStream(*iTrack);
                LOG(kMedia, "< iUriStreamer->DoStream(%u)\n", iTrack->Id());
            }
        }
    }
    catch (ThreadKill&) {
    }
    iQuit = true;
    iSupply.OutputQuit();
}

void Filler::OutputMode(const Brx& aMode, TBool aSupportsLatency, TBool aRealTime, IClockPuller* aClockPuller)
{
    if (!iQuit) {
        iSupply.OutputMode(aMode, aSupportsLatency, aRealTime, aClockPuller);
    }
}

void Filler::OutputSession()
{
    if (!iQuit) {
        iSupply.OutputSession();
    }
}

void Filler::OutputTrack(Track& aTrack, TUint aTrackId)
{
    if (!iQuit) {
        iTrackId = aTrackId;
        iSupply.OutputTrack(aTrack, aTrackId);
    }
}

void Filler::OutputDelay(TUint aJiffies)
{
    if (!iQuit) {
        iSupply.OutputDelay(aJiffies);
    }
}

void Filler::OutputStream(const Brx& aUri, TUint64 aTotalBytes, TBool aSeekable, TBool aLive, IStreamHandler& aStreamHandler, TUint aStreamId)
{
    if (!iQuit) {
        iPipelineIdTracker.AddStream(iTrack->Id(), iTrackId, aStreamId, (iTrackPlayStatus==ePlayYes));
        iTrackPlayStatus = ePlayYes; /* first stream in a track should take play status from UriProvider;
                                        subsequent streams should be played immediately */
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
