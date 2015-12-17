#include <OpenHome/Media/Pipeline/Gorger.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Private/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Gorger

Gorger::Gorger(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aThreadPriority, TUint aGorgeSize)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iGorgeSize(aGorgeSize)
    , iLock("GORG")
    , iSemOut("SGRG", 0)
    , iStreamHandler(nullptr)
    , iCanGorge(false)
    , iShouldGorge(false)
    , iStartOfMode(false)
    , iGorging(false)
    , iQuit(false)
    , iPriorityMsgCount(0)
{
    iThread = new ThreadFunctor("Gorger", MakeFunctor(*this, &Gorger::PullerThread), aThreadPriority);
    iThread->Start();
}

Gorger::~Gorger()
{
    delete iThread;
}

TUint Gorger::SizeInJiffies() const
{
    return Jiffies();
}

Msg* Gorger::Pull()
{
    iLock.Wait();
    TBool wait = (iGorging && Jiffies() < iGorgeSize);
    if (wait) {
        if (iQuit || TrackCount() > 0 || DecodedStreamCount() > 0) {
            wait = false;
        }
        else {
            (void)iSemOut.Clear();
        }
    }
    iLock.Signal();
    if (wait) {
        iSemOut.Wait();
    }
    else if (IsEmpty()) {
        iThread->Signal();
    }
    Msg* msg = DoDequeue();
    iLock.Wait();
    if (   iShouldGorge
        && iPriorityMsgCount == 0
        && !iStartOfMode
        && Jiffies() < iGorgeSize
        && !(iQuit || TrackCount() > 0 || DecodedStreamCount() > 0)) {
        iShouldGorge = false;
        SetGorging(true, "Pull");
    }
    iLock.Signal();
    return msg;
}

void Gorger::PullerThread()
{
    do {
        if (!iGorging) {
            iThread->Wait();
        }
        Msg* msg = iUpstreamElement.Pull();
        Enqueue(msg);
    } while (!iQuit);
}

void Gorger::Enqueue(Msg* aMsg)
{
    DoEnqueue(aMsg);
    iLock.Wait();
    if (iGorging) {
        if (Jiffies() >= iGorgeSize) {
            iGorging = false;
            iSemOut.Signal();
        }
        else if (TrackCount() > 0 || DecodedStreamCount() > 0 || iPriorityMsgCount > 0) {
            iSemOut.Signal();
        }
    }
    iLock.Signal();
}

void Gorger::SetGorging(TBool aGorging, const TChar* aId)
{
    const TBool unblockRight = (iGorging && !aGorging);
    const TBool unblockLeft = (!iGorging && aGorging);
    LOG(kPipeline, "Gorger::SetGorging(%u) from %s.  unblockRight=%u, unblockLeft=%u\n",
                    aGorging, aId, unblockRight, unblockLeft);
    iGorging = aGorging;
    if (unblockRight) {
        iSemOut.Signal();
    }
    if (unblockLeft) {
        iThread->Signal();
    }
}

void Gorger::ProcessMsgIn(MsgMode* /*aMsg*/)
{
    iLock.Wait();
    iStartOfMode = true;
    iShouldGorge = false;
    iPriorityMsgCount++;
    SetGorging(false, "ModeIn");
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgDrain* /*aMsg*/)
{
    iLock.Wait();
    iPriorityMsgCount++;
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLock.Wait();
    iPriorityMsgCount++;
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iLock.Wait();
    iQuit = true;
    iSemOut.Signal();
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgDecodedStream* /*aMsg*/)
{
    iLock.Wait();
    iPriorityMsgCount++;
    iLock.Signal();
}

Msg* Gorger::ProcessMsgOut(MsgMode* aMsg)
{
    iLock.Wait();
    iMode.Replace(aMsg->Mode());
    iCanGorge = !aMsg->Info().IsRealTime();
    iShouldGorge = iCanGorge;
    iPriorityMsgCount--;
    iLock.Signal();
    return aMsg;
}

Msg* Gorger::ProcessMsgOut(MsgDrain* aMsg)
{
    iLock.Wait();
    iPriorityMsgCount--;
    iLock.Signal();
    return aMsg;
}

Msg* Gorger::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iLock.Wait();
    iStreamHandler = stream.StreamHandler();
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();
    iPriorityMsgCount--;
    iStartOfMode = false;
    iLock.Signal();
    return msg;
}

Msg* Gorger::ProcessMsgOut(MsgHalt* aMsg)
{
    iLock.Wait();
    iPriorityMsgCount--;
    iShouldGorge = iCanGorge;
    iLock.Signal();
    return aMsg;
}

EStreamPlay Gorger::OkToPlay(TUint /*aStreamId*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return ePlayNo;
}

TUint Gorger::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Gorger::TryStop(TUint /*aStreamId*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void Gorger::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    iLock.Wait();
    if (   aStarving
        && aMode == iMode
        && iCanGorge
        && iPriorityMsgCount == 0
        && !iStartOfMode) {
        SetGorging(true, "NotifyStarving");
    }
    iLock.Signal();
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
