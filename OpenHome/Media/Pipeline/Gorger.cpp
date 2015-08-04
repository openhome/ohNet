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
    , iGorging(false)
    , iGorgeOnHaltOut(false)
    , iGorgeOnStreamOut(false)
    , iQuit(false)
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
        if (iQuit || SessionCount() > 0 || TrackCount() > 0 || DecodedStreamCount() > 0) {
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
        else if (SessionCount() > 0 || TrackCount() > 0 || DecodedStreamCount() > 0) {
            iSemOut.Signal();
        }
    }
    iLock.Signal();
}

void Gorger::SetGorging(TBool aGorging)
{
    const TBool unblockRight = (iGorging && !aGorging);
    const TBool unblockLeft = (!iGorging && aGorging);
    LOG(kPipeline, "Gorger::SetGorging(%u).  unblockRight=%u, unblockLeft=%u\n", aGorging, unblockRight, unblockLeft);
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
    SetGorging(false);
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgSession* /*aMsg*/)
{
    iLock.Wait();
    iGorgeOnHaltOut = false;
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLock.Wait();
    iGorgeOnHaltOut = true;
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
    iGorgeOnHaltOut = false;
    iLock.Signal();
}

Msg* Gorger::ProcessMsgOut(MsgMode* aMsg)
{
    iLock.Wait();
    iMode.Replace(aMsg->Mode());
    iCanGorge = !aMsg->Info().IsRealTime();
    iGorgeOnStreamOut = iCanGorge;
    iGorgeOnHaltOut = false;
    iLock.Signal();
    return aMsg;
}

Msg* Gorger::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iLock.Wait();
    iStreamHandler = stream.StreamHandler();
    iLock.Signal();
    MsgDecodedStream* msg = iMsgFactory.CreateMsgDecodedStream(stream.StreamId(), stream.BitRate(), stream.BitDepth(),
                                                               stream.SampleRate(), stream.NumChannels(), stream.CodecName(), 
                                                               stream.TrackLength(), stream.SampleStart(), stream.Lossless(), 
                                                               stream.Seekable(), stream.Live(), this);
    aMsg->RemoveRef();
    iLock.Wait();
    if (iGorgeOnStreamOut) {
        SetGorging(true);
        iGorgeOnStreamOut = false;
    }
    iLock.Signal();
    return msg;
}

Msg* Gorger::ProcessMsgOut(MsgHalt* aMsg)
{
    iLock.Wait();
    if (iGorgeOnHaltOut && iCanGorge) {
        SetGorging(true);
    }
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

void Gorger::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    iLock.Wait();
    if (aMode == iMode && iCanGorge) {
        SetGorging(true);
    }
    iLock.Signal();
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId);
    }
}
