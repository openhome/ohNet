#include <OpenHome/Media/Pipeline/DelayReservoir.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DelayReservoir

DelayReservoir::DelayReservoir(IPipelineElementUpstream& aUpstream, TUint aThreadPriority, TUint aMaxStreamCount)
    : iUpstream(aUpstream)
    , iMaxStreamCount(aMaxStreamCount)
    , iMaxJiffies(0)
    , iLock("DLY1")
    , iSem("DLY2", 0)
    , iExit(false)
{
    iPullerThread = new ThreadFunctor("DelayReservoir",
                                      MakeFunctor(*this, &DelayReservoir::PullerThread),
                                      aThreadPriority);
    iPullerThread->Start();
}

DelayReservoir::~DelayReservoir()
{
    delete iPullerThread;
}

TUint DelayReservoir::SizeInJiffies() const
{
    return Jiffies();
}

inline TBool DelayReservoir::IsFull() const
{
    return ((Jiffies() >= iMaxJiffies && iMaxJiffies > 0) ||
            DecodedStreamCount() == iMaxStreamCount);
}

void DelayReservoir::PullerThread()
{
    do {
        Msg* msg = iUpstream.Pull();
        iLock.Wait();
        DoEnqueue(msg);
        TBool isFull = IsFull();
        if (isFull) {
            iSem.Clear();
        }
        iLock.Signal();
        if (isFull) {
            iSem.Wait();
        }
    } while (!iExit);
}

Msg* DelayReservoir::Pull()
{
    auto msg = DoDequeue();
    iLock.Wait();
    if (!IsFull()) {
        iSem.Signal();
    }
    iLock.Signal();
    return msg;
}

void DelayReservoir::ProcessMsgIn(MsgDelay* aMsg)
{
    iMaxJiffies = aMsg->DelayJiffies();
}

void DelayReservoir::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iExit = true;
}
