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

TBool UriProvider::SupportsNext() const
{
    return iSupportsNext;
}

TBool UriProvider::SupportsPrev() const
{
    return iSupportsPrev;
}

ModeClockPullers UriProvider::ClockPullers()
{
    return ModeClockPullers();
}

TBool UriProvider::IsValid(TUint /*aTrackId*/) const
{
    return true;
}

void UriProvider::MoveTo(const Brx& /*aCommand*/)
{
    THROW(FillerInvalidCommand);
}

void UriProvider::Interrupt(TBool /*aInterrupt*/)
{
}

UriProvider::UriProvider(const TChar* aMode, Latency aLatency,
                        Next aNextSupported, Prev aPrevSupported)
    : iMode(aMode)
    , iSupportsLatency(aLatency == Latency::Supported)
    , iSupportsNext(aNextSupported == Next::Supported)
    , iSupportsPrev(aPrevSupported == Prev::Supported)
{
}

UriProvider::~UriProvider()
{
}


// Filler

Filler::Filler(IPipelineElementDownstream& aPipeline, IPipelineIdTracker& aIdTracker,
               IPipelineIdManager& aPipelineIdManager, IFlushIdProvider& aFlushIdProvider,
               MsgFactory& aMsgFactory, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver,
               IPipelineIdProvider& aIdProvider, TUint aThreadPriority, TUint aDefaultDelay)
    : Thread("Filler", aThreadPriority)
    , iLock("FIL1")
    , iPipeline(aPipeline)
    , iPipelineIdTracker(aIdTracker)
    , iPipelineIdManager(aPipelineIdManager)
    , iFlushIdProvider(aFlushIdProvider)
    , iMsgFactory(aMsgFactory)
    , iLockUriProvider("FIL2")
    , iActiveUriProvider(nullptr)
    , iUriStreamer(nullptr)
    , iTrack(nullptr)
    , iStopped(true)
    , iQuit(false)
    , iChangedMode(true)
    , iWaitingForAudio(false)
    , iNoAudioBeforeNextTrack(false)
    , iNextHaltId(MsgHalt::kIdNone + 1)
    , iPendingHaltId(MsgHalt::kIdInvalid)
    , iNextFlushId(MsgFlush::kIdInvalid)
    , iNullTrackStreamHandler(aIdProvider)
    , iStreamPlayObserver(aStreamPlayObserver)
    , iDefaultDelay(aDefaultDelay)
    , iPrefetchTrackId(kPrefetchTrackIdInvalid)
{
    iNullTrack = aTrackFactory.CreateTrack(Brx::Empty(), Brx::Empty());
}

Filler::~Filler()
{
    ASSERT(iQuit);
    if (iTrack != nullptr) {
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
    LOG(kPipeline, "> Filler::Quit()\n");
    (void)Stop();
    Kill();
    iUriStreamer->Interrupt(true);
    Join();
}

void Filler::Play(const Brx& aMode, TUint aTrackId)
{
    LOG(kMedia, "Filler::Play(%.*s, %u)\n", PBUF(aMode), aTrackId);
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->Begin(aTrackId);
    iStopped = false;
    Signal();
}

void Filler::PlayLater(const Brx& aMode, TUint aTrackId)
{
    LOG(kMedia, "Filler::PlayLater(%.*s, %u)\n", PBUF(aMode), aTrackId);
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->BeginLater(aTrackId);
    iPrefetchTrackId = aTrackId;
    iStopped = false;
    Signal();
}

void Filler::Play(const Brx& aMode, const Brx& aCommand)
{
    LOG(kMedia, "Filler::Play(%.*s, %.*s)\n", PBUF(aMode), PBUF(aCommand));
    AutoMutex _(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->MoveTo(aCommand);
    iStopped = false;
    Signal();
}

TUint Filler::Stop()
{
    LOG(kMedia, "Filler::Stop()\n");
    {
        AutoMutex _(iLockUriProvider);
        if (iActiveUriProvider != nullptr) {
            iActiveUriProvider->Interrupt(true);
        }
    }
    AutoMutex a(iLock);
    const TUint haltId = StopLocked();
    Signal();
    return haltId;
}

TUint Filler::Flush()
{
    {
        AutoMutex _(iLockUriProvider);
        if (iActiveUriProvider != nullptr) {
            iActiveUriProvider->Interrupt(true);
        }
    }
    AutoMutex a(iLock);
    (void)StopLocked();
    if (iNextFlushId == MsgFlush::kIdInvalid) {
        iNextFlushId = iFlushIdProvider.NextFlushId();
    }
    Signal();
    return iNextFlushId;
}

void Filler::Next(const Brx& aMode)
{
    LOG(kMedia, "Filler::Next(%.*s)\n", PBUF(aMode));
    iLock.Wait();
    if (iActiveUriProvider != nullptr && iActiveUriProvider->Mode() == aMode) {
        iActiveUriProvider->MoveNext();
        iStopped = false;
        Signal();
    }
    iLock.Signal();
}

void Filler::Prev(const Brx& aMode)
{
    LOG(kMedia, "Filler::Prev(%.*s)\n", PBUF(aMode));
    iLock.Wait();
    if (iActiveUriProvider != nullptr && iActiveUriProvider->Mode() == aMode) {
        iActiveUriProvider->MovePrevious();
        iStopped = false;
        Signal();
    }
    iLock.Signal();
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
    iActiveUriProvider = nullptr;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        UriProvider* uriProvider = iUriProviders[i];
        if (uriProvider->Mode() == aMode) {
            if (prevUriProvider != nullptr) {
                prevUriProvider->Interrupt(false);
            }
            iLockUriProvider.Wait();
            iActiveUriProvider = uriProvider;
            iLockUriProvider.Signal();
            break;
        }
    }
    iChangedMode = iChangedMode || (prevUriProvider != iActiveUriProvider);
    if (iActiveUriProvider == nullptr) {
        iStopped = true;
        THROW(FillerInvalidMode);
    }
}

TUint Filler::StopLocked()
{
    LOG(kMedia, "Filler::StopLocked iStopped=%u\n", iStopped);
    {
        AutoMutex _(iLockUriProvider);
        if (iActiveUriProvider != nullptr) {
            iActiveUriProvider->Interrupt(false);
        }
    }
    if (iPendingHaltId == MsgHalt::kIdInvalid) {
        iPendingHaltId = ++iNextHaltId;
    }
    iStopped = true;
    iChangedMode = true;
    if (iWaitingForAudio) {
        iUriStreamer->Interrupt(true);
        iNoAudioBeforeNextTrack = true;
    }
    return iPendingHaltId;
}

void Filler::Run()
{
    try {
        Wait();
        for (;;) {
            for (;;) {
                iLock.Wait();
                const TBool wait = iStopped;
                if (iNextFlushId != MsgFlush::kIdInvalid) {
                    iPipeline.Push(iMsgFactory.CreateMsgFlush(iNextFlushId));
                    iNextFlushId = MsgFlush::kIdInvalid;
                }
                if (iPendingHaltId != MsgHalt::kIdInvalid) {
                    iPipeline.Push(iMsgFactory.CreateMsgHalt(iPendingHaltId));
                    iPendingHaltId = MsgHalt::kIdInvalid;
                }
                iLock.Signal();
                if (!wait) {
                    break;
                }
                Wait();
            }
            iLock.Wait();
            if (iActiveUriProvider == nullptr) {
                iLock.Signal();
                continue;
            }
            if (iTrack != nullptr) {
                iTrack->RemoveRef();
                iTrack = nullptr;
            }
            iTrackPlayStatus = iActiveUriProvider->GetNext(iTrack);
            LOG(kMedia, "FILLER: iActiveUriProvider->GetNext() returned trackId=%u, status=%d\n", iTrack? iTrack->Id() : 0, iTrackPlayStatus);
            TBool failed = false;
            if (iPrefetchTrackId == Track::kIdNone) {
                failed = (iTrack != nullptr);
            }
            else if (iPrefetchTrackId != kPrefetchTrackIdInvalid) {
                failed = (iTrack == nullptr || iTrack->Id() != iPrefetchTrackId);
            }
            if (failed) {
                iStreamPlayObserver.NotifyTrackFailed(iPrefetchTrackId);
            }
            /* assume that if the uri provider has returned a track then ProtocolManager
                will call OutputTrack, causing Stopper to later call iStreamPlayObserver */
            iPrefetchTrackId = kPrefetchTrackIdInvalid;
            if (iTrackPlayStatus == ePlayNo) {
                iChangedMode = true;
                iStopped = true;
                iLock.Signal();
                iPipeline.Push(iMsgFactory.CreateMsgMode(Brn("null"), false, ModeClockPullers(), false, false));
                iPipeline.Push(iMsgFactory.CreateMsgTrack(*iNullTrack));
                iPipelineIdTracker.AddStream(iNullTrack->Id(), NullTrackStreamHandler::kNullTrackStreamId, false /* play later */);
                iPipeline.Push(iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, 0, NullTrackStreamHandler::kNullTrackStreamId, false /* not seekable */, true /* live */, Multiroom::Forbidden, &iNullTrackStreamHandler));
                iPipeline.Push(iMsgFactory.CreateMsgMetaText(Brx::Empty()));
                iPipeline.Push(iMsgFactory.CreateMsgDelay(iDefaultDelay));
            }
            else {
                iLock.Signal();
                iUriStreamer->Interrupt(false);
                iLock.Wait();
                if (iChangedMode) {
                    const TBool supportsLatency = iActiveUriProvider->SupportsLatency();
                    iPipeline.Push(iMsgFactory.CreateMsgMode(iActiveUriProvider->Mode(), supportsLatency, iActiveUriProvider->ClockPullers(),
                                                             iActiveUriProvider->SupportsNext(), iActiveUriProvider->SupportsPrev()));
                    if (!supportsLatency) {
                        iPipeline.Push(iMsgFactory.CreateMsgDelay(iDefaultDelay));
                    }
                    iChangedMode = false;
                }
                iWaitingForAudio = true;
                iNoAudioBeforeNextTrack = false;
                iLock.Signal();
                ASSERT(iTrack != nullptr);
                LOG(kMedia, "> iUriStreamer->DoStream(%u)\n", iTrack->Id());
                CheckForKill();
                ProtocolStreamResult res = iUriStreamer->DoStream(*iTrack);
                if (res == EProtocolErrorNotSupported) {
                    LOG(kPipeline, "Filler::Run Track %u not supported. URI: %.*s\n",
                                   iTrack->Id(), PBUF(iTrack->Uri()));
                }
                else if (res == EProtocolStreamErrorUnrecoverable) {
                    LOG(kPipeline, "Filler::Run Track %u had unrecoverable error. URI: %.*s\n",
                                   iTrack->Id(), PBUF(iTrack->Uri()));
                }
                LOG(kMedia, "< iUriStreamer->DoStream(%u)\n", iTrack->Id());
            }
        }
    }
    catch (ThreadKill&) {
    }
    iQuit = true;
    if (iNextFlushId != MsgFlush::kIdInvalid) {
        iPipeline.Push(iMsgFactory.CreateMsgFlush(iNextFlushId));
    }
    if (iPendingHaltId != MsgHalt::kIdInvalid) {
        iPipeline.Push(iMsgFactory.CreateMsgHalt(iPendingHaltId));
    }
    iPipeline.Push(iMsgFactory.CreateMsgQuit());
}

void Filler::Push(Msg* aMsg)
{
    iLock.Wait();
    aMsg = aMsg->Process(*this);
    iLock.Signal();
    if (aMsg != nullptr) {
        iPipeline.Push(aMsg);
    }
}

Msg* Filler::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgTrack* aMsg)
{
    iWaitingForAudio = true;
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgEncodedStream* aMsg)
{
    iWaitingForAudio = true;
    const TUint trackId = iTrack->Id();
    iPipelineIdTracker.AddStream(trackId, aMsg->StreamId(), (iTrackPlayStatus==ePlayYes));
    if (iActiveUriProvider->IsValid(trackId)) {
        iTrackPlayStatus = ePlayYes; /* first stream in a track should take play status from UriProvider;
                                        subsequent streams should be played immediately */

    }
    else {
        iPipelineIdManager.InvalidateAt(trackId);
    }
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (iNoAudioBeforeNextTrack) {
        aMsg->RemoveRef();
        return nullptr;
    }
    iWaitingForAudio = false;
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgMetaText* aMsg)
{
    if (iNoAudioBeforeNextTrack) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* Filler::ProcessMsg(MsgStreamInterrupted* aMsg)
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

Msg* Filler::ProcessMsg(MsgBitRate* aMsg)
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

Filler::NullTrackStreamHandler::NullTrackStreamHandler(IPipelineIdProvider& aIdProvider)
    : iIdProvider(aIdProvider)
{
}

EStreamPlay Filler::NullTrackStreamHandler::OkToPlay(TUint aStreamId)
{
    (void)iIdProvider.OkToPlay(aStreamId);
    return ePlayLater;
}

TUint Filler::NullTrackStreamHandler::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    return MsgFlush::kIdInvalid;
}

TUint Filler::NullTrackStreamHandler::TryDiscard(TUint /*aJiffies*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Filler::NullTrackStreamHandler::TryStop(TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

void Filler::NullTrackStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}
