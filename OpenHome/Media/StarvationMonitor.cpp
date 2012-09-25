#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// StarvationMonitor

StarvationMonitor::StarvationMonitor(MsgFactory& aMsgFactory, IPipelineElement& aUpstreamElement, TUint aNormalSize, TUint aStarvationThreshold, TUint aGorgeSize, TUint aRampUpSize)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iNormalMax(aNormalSize)
    , iStarvationThreshold(aStarvationThreshold)
    , iGorgeSize(aGorgeSize)
    , iRampUpSize(aRampUpSize)
    , iLock("STRV")
    , iSemIn("STR1", 0)
    , iSemOut("STR2", 0)
    , iStatus(EBuffering)
    , iCurrentRampValue(Ramp::kRampMax)
    , iPlannedHalt(true)
    , iExit(false)
{
    ASSERT(iStarvationThreshold < iNormalMax);
    ASSERT(iNormalMax < iGorgeSize);
    ASSERT(iRampUpSize < iGorgeSize);
    iThread = new ThreadFunctor("STRV", MakeFunctor(*this, &StarvationMonitor::PullerThread), kPriorityNormal); // FIXME - want a priority that's higher that ohNet's threads
    iThread->Start();
}

StarvationMonitor::~StarvationMonitor()
{
    // FIXME - check that thread has exited
    delete iThread;
}

void StarvationMonitor::PullerThread()
{
    do {
        Msg* msg = iUpstreamElement.Pull();
        Enqueue(msg);
    } while (!iExit);
}

void StarvationMonitor::Enqueue(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iNormalMax is queued.
    DoEnqueue(aMsg);
    iLock.Wait();
    TBool isFull = (iStatus != EBuffering && Jiffies() >= iNormalMax);
    if (iStatus == EBuffering && Jiffies() >= iGorgeSize) {
        if (iPlannedHalt) {
            iStatus = ERunning;
            iPlannedHalt = false;
        }
        else {
            iStatus = ERampingUp;
            ASSERT(iCurrentRampValue == Ramp::kRampMin);
            iRemainingRampSize = iRampUpSize;
        }
        iSemOut.Signal();
        isFull = true;
    }
    if (iExit) {
        iSemOut.Signal();
    }
    iLock.Signal();
    if (isFull) {
        iSemIn.Wait();
    }
}

Msg* StarvationMonitor::Pull()
{
    Msg* msg;
    iLock.Wait();
    const TUint jiffies = Jiffies();
    if (iStatus == EBuffering && jiffies == 0 && !iPlannedHalt ) {
        iLock.Signal();
        return iMsgFactory.CreateMsgHalt(); // signal that we won't be providing any more audio for a while
    }
    TBool wait = false;
    if (iStatus == EBuffering) {
        if (jiffies == 0 && iPlannedHalt) {
            wait = IsEmpty(); // allow reading of the halt msg which should be the last item in the queue
        }
        else if (jiffies < iGorgeSize) {
            wait = true;
        }
    }
    iLock.Signal();
    if (wait) {
        iSemOut.Wait();
    }
    msg = DoDequeue();
    return msg;
}

MsgAudio* StarvationMonitor::DoProcessMsgOut(MsgAudio* aMsg)
{
    iLock.Wait();
    ASSERT(iStatus != EBuffering);
    TUint remainingSize = Jiffies();
    if (!iPlannedHalt && (remainingSize < iStarvationThreshold) && (iStatus == ERunning)) {
        iStatus = ERampingDown;
        iRampDownDuration = remainingSize + aMsg->Jiffies();
        ASSERT(iCurrentRampValue == Ramp::kRampMax);
        iRemainingRampSize = iRampDownDuration;
    }
    if (iStatus == ERampingDown) {
        Ramp(aMsg, iRampDownDuration, Ramp::EDown);
        if (iCurrentRampValue == Ramp::kRampMin) {
            iStatus = EBuffering;
        }
        if (remainingSize == 0) {
            ASSERT(iCurrentRampValue == Ramp::kRampMin);
        }
    }
    else if (iStatus == ERampingUp) {
        Ramp(aMsg, iRampUpSize, Ramp::EUp);
        if (iCurrentRampValue == Ramp::kRampMax) {
            iStatus = ERunning;
        }
    }

    remainingSize = Jiffies(); // re-calculate this as Ramp() can cause a msg to be split with a fragment re-queued
    if (remainingSize == 0) {
        iStatus = EBuffering;
    }
    if ((remainingSize < iNormalMax) && (remainingSize + aMsg->Jiffies() >= iNormalMax)) {
        iSemIn.Signal();
    }
    iLock.Signal();

    return aMsg;
}

void StarvationMonitor::Ramp(MsgAudio* aMsg, TUint aRampDuration, Ramp::EDirection aDirection)
{
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, aRampDuration, aDirection, split);
    if (split != NULL) {
        EnqueueAtHead(split);
    }
    iRemainingRampSize -= aMsg->Jiffies();
}

void StarvationMonitor::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iLock.Wait();
    iPlannedHalt = true;
    iLock.Signal();
}

void StarvationMonitor::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect flushes to propogate this far down the pipeline
}

void StarvationMonitor::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iLock.Wait();
    iExit = true;
    iLock.Signal();
}

Msg* StarvationMonitor::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

Msg* StarvationMonitor::ProcessMsgOut(MsgSilence* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

TBool StarvationMonitor::EnqueueWouldBlock() const
{
    AutoMutex a(iLock);
    const TUint jiffies = Jiffies();
    if (iStatus == EBuffering) {
        if (jiffies >= iGorgeSize) {
           return true;
        }
    }
    else if (jiffies >= iNormalMax) {
        return true;
    }
    return false;
}

TBool StarvationMonitor::PullWouldBlock() const
{
    AutoMutex a(iLock);
    if (IsEmpty() || (iStatus == EBuffering && Jiffies() < iGorgeSize)) {
        return true;
    }
    return false;
}
