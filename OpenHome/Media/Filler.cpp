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

Filler::Filler(IPipelineElementDownstream& aPipeline, IPipelineIdTracker& aIdTracker, IFlushIdProvider& aFlushIdProvider,
               MsgFactory& aMsgFactory, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver,
               TUint aThreadPriority, TUint aDefaultDelay)
    : Thread("Filler", aThreadPriority)
    , iLock("FILL")
    , iPipeline(aPipeline)
    , iPipelineIdTracker(aIdTracker)
    , iFlushIdProvider(aFlushIdProvider)
    , iMsgFactory(aMsgFactory)
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
                    iPipeline.Push(iMsgFactory.CreateMsgFlush(iNextFlushId));
                    iNextFlushId = MsgFlush::kIdInvalid;
                }
                iLock.Signal();
                if (!wait) {
                    break;
                }
                if (sendHalt) {
                    iPipeline.Push(iMsgFactory.CreateMsgHalt(iNextHaltId));
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
                iPipeline.Push(iMsgFactory.CreateMsgMode(Brn("null"), false, true, NULL));
                iPipeline.Push(iMsgFactory.CreateMsgSession());
                iChangedMode = true;
                iPipeline.Push(iMsgFactory.CreateMsgTrack(*iNullTrack));
                iPipelineIdTracker.AddStream(iNullTrack->Id(), NullTrackStreamHandler::kNullTrackStreamId, false /* play later */);
                iPipeline.Push(iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, NullTrackStreamHandler::kNullTrackStreamId, false /* not seekable */, true /* live */, &iNullTrackStreamHandler));
                iPipeline.Push(iMsgFactory.CreateMsgMetaText(Brx::Empty()));
                iPipeline.Push(iMsgFactory.CreateMsgDelay(iDefaultDelay));
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
                    iPipeline.Push(iMsgFactory.CreateMsgMode(iActiveUriProvider->Mode(), supportsLatency, realTime, iActiveUriProvider->ClockPuller()));
                    if (!supportsLatency) {
                        iPipeline.Push(iMsgFactory.CreateMsgDelay(iDefaultDelay));
                    }
                    iChangedMode = false;
                }
                iLock.Signal();
                ASSERT(iTrack != NULL);
                iPipeline.Push(iMsgFactory.CreateMsgSession());
                LOG(kMedia, "> iUriStreamer->DoStream(%u)\n", iTrack->Id());
                ProtocolStreamResult res = iUriStreamer->DoStream(*iTrack);
                if (res == EProtocolErrorNotSupported) {
                    LOG(kMedia, "Filler::Run Track %u not supported. URI: ", iTrack->Id());
                    LOG(kMedia, iTrack->Uri());
                    LOG(kMedia, "\n");
                }
                else if (res == EProtocolStreamErrorUnrecoverable) {
                    LOG(kMedia, "Filler::Run Track %u had unrecoverable error. URI: ", iTrack->Id());
                    LOG(kMedia, iTrack->Uri());
                    LOG(kMedia, "\n");
                }
                LOG(kMedia, "< iUriStreamer->DoStream(%u)\n", iTrack->Id());
            }
        }
    }
    catch (ThreadKill&) {
    }
    iQuit = true;
    iPipeline.Push(iMsgFactory.CreateMsgQuit());
}

void Filler::Push(Msg* aMsg)
{
    aMsg = aMsg->Process(*this);
    if (aMsg != NULL) {
        iPipeline.Push(aMsg);
    }
}

Msg* Filler::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgEncodedStream* aMsg)
{
    iPipelineIdTracker.AddStream(iTrack->Id(), aMsg->StreamId(), (iTrackPlayStatus==ePlayYes));
    iTrackPlayStatus = ePlayYes; /* first stream in a track should take play status from UriProvider;
                                    subsequent streams should be played immediately */
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgAudioEncoded* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgFlush* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgSilence* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS();
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgQuit* aMsg)
{
    ASSERTS();
    return aMsg;
}


// Filler::NullTrackStreamHandler

EStreamPlay Filler::NullTrackStreamHandler::OkToPlay(TUint /*aStreamId*/)
{
    return ePlayLater;
}

TUint Filler::NullTrackStreamHandler::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint Filler::NullTrackStreamHandler::TryStop(TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

void Filler::NullTrackStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/)
{
}
