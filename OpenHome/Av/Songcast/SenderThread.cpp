#include <OpenHome/Av/Songcast/SenderThread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

const TUint SenderThread::kMaxMsgBacklog = 100;

SenderThread::SenderThread(IPipelineElementDownstream& aDownstream,
                           TUint aThreadPriority)
    : iDownstream(aDownstream)
    , iFifo(kMaxMsgBacklog)
    , iFifoSlotsUsed(0)
    , iShutdownSem("SGSN", 0)
    , iQuit(false)
{
    ASSERT(iFifoSlotsUsed.is_lock_free());
    iThread = new ThreadFunctor("SongcastSender", MakeFunctor(*this, &SenderThread::Run), aThreadPriority);
    iThread->Start();
}

SenderThread::~SenderThread()
{
    iShutdownSem.Wait();
    delete iThread;
}

void SenderThread::Push(Msg* aMsg)
{
    ASSERT(iFifoSlotsUsed < kMaxMsgBacklog);
    iFifo.Write(aMsg);
    iFifoSlotsUsed++;
    iThread->Signal();
}

void SenderThread::Run()
{
    do {
        iThread->Wait();
        auto msg = iFifo.Read();
        iFifoSlotsUsed--;
        msg = msg->Process(*this);
        iDownstream.Push(msg);
    } while (!iQuit);
    iShutdownSem.Signal();
}

Msg* SenderThread::ProcessMsg(MsgMode* aMsg)              { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgTrack* aMsg)             { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgDrain* aMsg)             { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgDelay* aMsg)             { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgEncodedStream* aMsg)     { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgAudioEncoded* aMsg)      { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgMetaText* aMsg)          { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgStreamInterrupted* aMsg) { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgHalt* aMsg)              { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgFlush* aMsg)             { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgWait* aMsg)              { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgDecodedStream* aMsg)     { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgBitRate* aMsg)           { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgAudioPcm* aMsg)          { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgSilence* aMsg)           { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgPlayable* aMsg)          { return aMsg; }
Msg* SenderThread::ProcessMsg(MsgQuit* aMsg)
{
    Log::Print("++ SenderThread::ProcessMsg(MsgQuit* )\n");
    iQuit = true;
    return aMsg;
}
