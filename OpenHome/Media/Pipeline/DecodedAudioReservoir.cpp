#include <OpenHome/Media/Pipeline/DecodedAudioReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Debug.h>

#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DecodedAudioReservoir

DecodedAudioReservoir::DecodedAudioReservoir(MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider,
                                             TUint aMaxSize, TUint aMaxStreamCount, TUint aGorgeSize)
    : iMsgFactory(aMsgFactory)
    , iFlushIdProvider(aFlushIdProvider)
    , iLock("DCR1")
    , iMaxJiffies(aMaxSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iClockPuller(nullptr)
    , iStreamHandler(nullptr)
    , iDecodedStream(nullptr)
    , iDiscardJiffies(0)
    , iPostDiscardFlush(MsgFlush::kIdInvalid)
    , iGorgeLock("DCR2")
    , iGorgeSize(aGorgeSize)
    , iSemOut("DCR3", 0)
    , iCanGorge(false)
    , iShouldGorge(false)
    , iStartOfMode(false)
    , iGorging(false)
    , iPriorityMsgCount(0)
{
}

DecodedAudioReservoir::~DecodedAudioReservoir()
{
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
}

TUint DecodedAudioReservoir::SizeInJiffies() const
{
    return Jiffies();
}

Msg* DecodedAudioReservoir::Pull()
{
    TBool wait = false;
    {
        AutoMutex _(iGorgeLock);
        TBool wait = (iGorging && Jiffies() < iGorgeSize);
        if (wait) {
            (void)iSemOut.Clear();
        }
    }

    if (wait) {
        iSemOut.Wait();
    }
    Msg* msg = AudioReservoir::Pull();

    {
        AutoMutex _(iGorgeLock);
        if (iShouldGorge
            && iPriorityMsgCount == 0
            && !iStartOfMode
            && Jiffies() < iGorgeSize) {
            iShouldGorge = false;
            SetGorging(true, "Pull");
        }
    }

    return msg;
}

void DecodedAudioReservoir::Push(Msg* aMsg)
{
    iGorgeLock.Wait();
    const TUint oldPriorityMsgCount = iPriorityMsgCount;
    iGorgeLock.Signal();
    
    DoEnqueue(aMsg);
    
    iGorgeLock.Wait();
    if (iGorging) {
        if (Jiffies() >= iGorgeSize) {
            iGorging = false;
            iSemOut.Signal();
        }
        else if (oldPriorityMsgCount == 0 && iPriorityMsgCount > 0) {
            iGorging = false;
            iShouldGorge = true;
            iSemOut.Signal();
        }
    }
    iGorgeLock.Signal();
}

TBool DecodedAudioReservoir::IsFull() const
{
    return (Jiffies() > iMaxJiffies         ||
            TrackCount() >= iMaxStreamCount ||
            DecodedStreamCount() >= iMaxStreamCount);
}

void DecodedAudioReservoir::HandleBlocked()
{
    AutoMutex _(iGorgeLock);
    if (iGorging && Jiffies() >= iGorgeSize) {
        iGorging = false;
        iSemOut.Signal();
    }
}

void DecodedAudioReservoir::SetGorging(TBool aGorging, const TChar* aId)
{
    const TBool unblockRight = (iGorging && !aGorging);
    LOG(kPipeline, "Gorger::SetGorging(%u) from %s.  unblockRight=%u\n",
                   aGorging, aId, unblockRight);
    iGorging = aGorging;
    if (unblockRight) {
        iSemOut.Signal();
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgMode* aMsg)
{
    {
        AutoMutex _(iLock);
        if (iClockPuller != nullptr) {
            iClockPuller->Stop();
        }
        iClockPuller = aMsg->ClockPullers().PipelineBuffer();

        iStartOfMode = true;
        iShouldGorge = false;
        iPriorityMsgCount++;
    }
    iGorgeLock.Wait();
    SetGorging(false, "ModeIn");
    iGorgeLock.Signal();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDrain* /*aMsg*/)
{
    iLock.Wait();
    if (iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    iLock.Signal();
    iGorgeLock.Wait();
    iPriorityMsgCount++;
    iGorgeLock.Signal();
}

void DecodedAudioReservoir::ProcessMsgIn(MsgEncodedStream* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    BlockIfFull();
    iPriorityMsgCount++;
}

void DecodedAudioReservoir::ProcessMsgIn(MsgAudioPcm* aMsg)
{
    BlockIfFull();
    AutoMutex _(iLock);
    if (iClockPuller != nullptr) {
        aMsg->SetObserver(*iClockPuller);
    }
}

void DecodedAudioReservoir::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    ASSERTS(); // don't expect anything upstream to be generating silence
}

void DecodedAudioReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iPriorityMsgCount++; // last msg to be handled so we don't bother decrementing count on way out
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgMode* aMsg)
{
    iGorgeLock.Wait();
    iMode.Replace(aMsg->Mode());
    iCanGorge = !aMsg->Info().SupportsLatency();
    iShouldGorge = iCanGorge;
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgTrack* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDrain* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgEncodedStream* aMsg)
{
    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iGorgeLock.Signal();

    iStreamHandler.store(aMsg->StreamHandler());
    auto msg = iMsgFactory.CreateMsgEncodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    iStreamHandler.store(aMsg->StreamInfo().StreamHandler());
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    if (iDecodedStream != nullptr) {
        iDecodedStream->RemoveRef();
    }
    iDecodedStream = aMsg;

    iGorgeLock.Wait();
    iPriorityMsgCount--;
    iStartOfMode = false;
    iGorgeLock.Signal();

    return msg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgHalt* aMsg)
{
    iGorgeLock.Wait();
    iShouldGorge = iCanGorge;
    iPriorityMsgCount--;
    iShouldGorge = iCanGorge;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgFlush* aMsg)
{
    iGorgeLock.Wait();
    iShouldGorge = iCanGorge;
    iGorgeLock.Signal();
    return aMsg;
}

Msg* DecodedAudioReservoir::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    if (iDiscardJiffies == 0) {
        return aMsg;
    }

    if (aMsg->Jiffies() > iDiscardJiffies) {
        auto split = aMsg->Split(iDiscardJiffies);
        EnqueueAtHead(split);
    }
    if (aMsg->Jiffies() > iDiscardJiffies) {
        iDiscardJiffies = 0;
    }
    else {
        iDiscardJiffies -= aMsg->Jiffies();
    }
    Msg* ret = nullptr;
    if (iDiscardJiffies == 0) {
        auto s = iDecodedStream->StreamInfo();
        const TUint64 sampleStart = (aMsg->TrackOffset() + aMsg->Jiffies()) / Jiffies::PerSample(s.SampleRate());
        auto stream = iMsgFactory.CreateMsgDecodedStream(s.StreamId(), s.BitRate(), s.BitDepth(), s.SampleRate(),
                                                         s.NumChannels(), s.CodecName(), s.TrackLength(),
                                                         sampleStart, s.Lossless(), s.Seekable(), s.Live(),
                                                         s.AnalogBypass(), s.StreamHandler());
        EnqueueAtHead(stream);

        ret = iMsgFactory.CreateMsgFlush(iPostDiscardFlush);
        iPostDiscardFlush = MsgFlush::kIdInvalid;
    }
    aMsg->RemoveRef();
    return ret;
}

EStreamPlay DecodedAudioReservoir::OkToPlay(TUint aStreamId)
{
    auto streamHandler = iStreamHandler.load();
    if (streamHandler == nullptr) {
        return ePlayNo;
    }
    return streamHandler->OkToPlay(aStreamId);
}

TUint DecodedAudioReservoir::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint DecodedAudioReservoir::TryDiscard(TUint aJiffies)
{
    if (aJiffies > Jiffies()) {
        return MsgFlush::kIdInvalid;
    }
    iDiscardJiffies += aJiffies;
    iPostDiscardFlush = iFlushIdProvider.NextFlushId();
    return iPostDiscardFlush;
}

TUint DecodedAudioReservoir::TryStop(TUint aStreamId)
{
    auto streamHandler = iStreamHandler.load();
    if (streamHandler == nullptr) {
        return MsgFlush::kIdInvalid;
    }
    const TUint flushId = streamHandler->TryStop(aStreamId);
    AutoMutex _(iLock);
    if (flushId != MsgFlush::kIdInvalid && iClockPuller != nullptr) {
        iClockPuller->Stop();
    }
    return flushId;
}

void DecodedAudioReservoir::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    {
        AutoMutex __(iGorgeLock);
        if (aStarving
            && aMode == iMode
            && iCanGorge
            && !iStartOfMode
            && Jiffies() < iGorgeSize) {
            if (iPriorityMsgCount == 0) {
                SetGorging(true, "NotifyStarving");
            }
            else {
                iShouldGorge = iCanGorge;
            }
        }
    }
    auto streamHandler = iStreamHandler.load();
    if (streamHandler != nullptr) {
        streamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
