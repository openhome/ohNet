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

TBool UriProvider::SupportsNext() const
{
    return iSupportsNext;
}

TBool UriProvider::SupportsPrev() const
{
    return iSupportsPrev;
}

IClockPuller* UriProvider::ClockPuller()
{
    return nullptr;
}

UriProvider::UriProvider(const TChar* aMode,
    LatencySupport aLatency, RealTimeSupport aRealTime,
    NextSupport aNextSupported, PrevSupport aPrevSupported)
    : iMode(aMode)
    , iSupportsLatency(aLatency == LatencySupported)
    , iRealTime(aRealTime == RealTimeSupported)
    , iSupportsNext(aNextSupported == NextSupported)
    , iSupportsPrev(aPrevSupported == PrevSupported)
{
}

UriProvider::~UriProvider()
{
}


// Filler

Filler::Filler(IPipelineElementDownstream& aPipeline, IPipelineIdTracker& aIdTracker, IFlushIdProvider& aFlushIdProvider,
               MsgFactory& aMsgFactory, TrackFactory& aTrackFactory, IStreamPlayObserver& aStreamPlayObserver,
               IPipelineIdProvider& aIdProvider, TUint aThreadPriority, TUint aDefaultDelay)
    : Thread("Filler", aThreadPriority)
    , iLock("FILL")
    , iPipeline(aPipeline)
    , iPipelineIdTracker(aIdTracker)
    , iFlushIdProvider(aFlushIdProvider)
    , iMsgFactory(aMsgFactory)
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
    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<256> buf("Filler::Play(");
        buf.Append(aMode);
        buf.AppendPrintf(", %u)\n", aTrackId);
        Log::Print(buf);
    }
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->Begin(aTrackId);
    iStopped = false;
    Signal();
}

void Filler::PlayLater(const Brx& aMode, TUint aTrackId)
{
    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<256> buf("Filler::PlayLater(");
        buf.Append(aMode);
        buf.AppendPrintf(", %u)\n", aTrackId);
        Log::Print(buf);
    }
    AutoMutex a(iLock);
    UpdateActiveUriProvider(aMode);
    iActiveUriProvider->BeginLater(aTrackId);
    iPrefetchTrackId = aTrackId;
    iStopped = false;
    Signal();
}

TUint Filler::Stop()
{
    LOG(kMedia, "Filler::Stop()\n");
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
    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<256> buf("Filler::Next(");
        buf.Append(aMode);
        buf.Append(")\n");
        Log::Print(buf);
    }
    TBool ret = false;
    iLock.Wait();
    if (iActiveUriProvider != nullptr && iActiveUriProvider->Mode() == aMode) {
        ret = iActiveUriProvider->MoveNext();
        iStopped = false;
        Signal();
    }
    iLock.Signal();
    return ret;
}

TBool Filler::Prev(const Brx& aMode)
{
    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<256> buf("Filler::Prev(");
        buf.Append(aMode);
        buf.Append(")\n");
        Log::Print(buf);
    }
    TBool ret = false;
    iLock.Wait();
    if (iActiveUriProvider != nullptr && iActiveUriProvider->Mode() == aMode) {
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
    iActiveUriProvider = nullptr;
    for (TUint i=0; i<iUriProviders.size(); i++) {
        UriProvider* uriProvider = iUriProviders[i];
        if (uriProvider->Mode() == aMode) {
            iActiveUriProvider = uriProvider;
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
    if (iPendingHaltId == MsgHalt::kIdInvalid) {
        iPendingHaltId = ++iNextHaltId;
        iStopped = true;
        iChangedMode = true; // Skipper::RemoveAll() relies on MsgMode being sent following a MsgHalt
    }
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
                iPipeline.Push(iMsgFactory.CreateMsgMode(Brn("null"), false, true, nullptr, false, false));
                iChangedMode = true;
                iPipeline.Push(iMsgFactory.CreateMsgTrack(*iNullTrack));
                iPipelineIdTracker.AddStream(iNullTrack->Id(), NullTrackStreamHandler::kNullTrackStreamId, false /* play later */);
                iPipeline.Push(iMsgFactory.CreateMsgEncodedStream(Brx::Empty(), Brx::Empty(), 0, NullTrackStreamHandler::kNullTrackStreamId, false /* not seekable */, true /* live */, &iNullTrackStreamHandler));
                iPipeline.Push(iMsgFactory.CreateMsgMetaText(Brx::Empty()));
                iPipeline.Push(iMsgFactory.CreateMsgDelay(iDefaultDelay));
                iStopped = true;
                iLock.Signal();
            }
            else {
                iUriStreamer->Interrupt(false);
                if (iChangedMode) {
                    const TBool supportsLatency = iActiveUriProvider->SupportsLatency();
                    const TBool realTime = iActiveUriProvider->IsRealTime();
                    ASSERT(!supportsLatency || realTime); /* VariableDelay handling of NotifyStarving would be
                                                             hard/impossible if the Gorger was allowed to buffer
                                                             content between the two VariableDelays */
                    iPipeline.Push(iMsgFactory.CreateMsgMode(iActiveUriProvider->Mode(), supportsLatency, realTime, iActiveUriProvider->ClockPuller(),
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
    iPipelineIdTracker.AddStream(iTrack->Id(), aMsg->StreamId(), (iTrackPlayStatus==ePlayYes));
    iTrackPlayStatus = ePlayYes; /* first stream in a track should take play status from UriProvider;
                                    subsequent streams should be played immediately */
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

TUint Filler::NullTrackStreamHandler::TryStop(TUint /*aStreamId*/)
{
    return MsgFlush::kIdInvalid;
}

void Filler::NullTrackStreamHandler::NotifyStarving(const Brx& /*aMode*/, TUint /*aStreamId*/, TBool /*aStarving*/)
{
}
