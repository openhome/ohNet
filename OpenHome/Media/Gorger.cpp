#include <OpenHome/Media/Gorger.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Gorger

Gorger::Gorger(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aGorgeSize)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iGorgeSize(aGorgeSize)
    , iLock("GORG")
    , iSemOut("SGRG", 0)
    , iStreamHandler(NULL)
    , iCanGorge(false)
    , iGorging(false)
    , iQuit(false)
{
    iThread = new ThreadFunctor("Gorger", MakeFunctor(*this, &Gorger::PullerThread), kPriorityVeryHigh-1); // FIXME - review thread priorities
    iThread->Start();
}

Gorger::~Gorger()
{
    delete iThread;
}

Msg* Gorger::Pull()
{
    iLock.Wait();
    const TBool wait = (iGorging && Jiffies() < iGorgeSize && !iQuit);
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
    if (iGorging && Jiffies() >= iGorgeSize) {
        iGorging = false;
        iSemOut.Signal();
    }
    iLock.Signal();
}

void Gorger::SetGorging(TBool aGorging)
{
    const TBool unblockPuller = (iGorging && !aGorging);
    iGorging = aGorging;
    if (unblockPuller) {
        iSemOut.Signal();
    }
}

void Gorger::ProcessMsgIn(MsgMode* aMsg)
{
    iLock.Wait();
    iMode.Replace(aMsg->Mode());
    iCanGorge = !aMsg->IsRealTime();
    SetGorging(iCanGorge);
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLock.Wait();
    if (iCanGorge) {
        SetGorging(true);
    }
    iLock.Signal();
}

void Gorger::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iLock.Wait();
    iQuit = true;
    iSemOut.Signal();
    iLock.Signal();
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
    return msg;
}

EStreamPlay Gorger::OkToPlay(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return ePlayNo;
}

TUint Gorger::TrySeek(TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Gorger::TryStop(TUint /*aTrackId*/, TUint /*aStreamId*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TBool Gorger::TryGet(IWriter& /*aWriter*/, TUint /*aTrackId*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    // Not expected to be called.  Content at this stage of the pipeline is guaranteed to be played.
    ASSERTS();
    return false;
}

void Gorger::NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    if (aMode == iMode && !iGorging && iCanGorge) {
        iGorging = true;
        iThread->Signal();
    }
    iLock.Signal();
    if (iStreamHandler != NULL) {
        iStreamHandler->NotifyStarving(aMode, aTrackId, aStreamId);
    }
}
