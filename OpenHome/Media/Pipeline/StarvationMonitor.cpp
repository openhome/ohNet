#include <OpenHome/Media/Pipeline/StarvationMonitor.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

#include <atomic>
#include <limits.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// StarvationMonitor

StarvationMonitor::StarvationMonitor(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement,
                                     IStarvationMonitorObserver& aObserver, IPipelineElementObserverThread& aObserverThread,
                                     TUint aThreadPriority, TUint aNormalSize, TUint aStarvationThreshold, TUint aRampUpSize, TUint aMaxStreamCount)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iObserverThread(aObserverThread)
    , iClockPuller(nullptr)
    , iNormalMax(aNormalSize)
    , iStarvationThreshold(aStarvationThreshold)
    , iRampUpSize(aRampUpSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iLock("STRV")
    , iSemIn("STR1", 0)
    , iSemOut("STR2", 0)
    , iCurrentRampValue(Ramp::kMax)
    , iPlannedHalt(true)
    , iHaltDelivered(false)
    , iExit(false)
    , iPriorityMsgCount(0)
    , iJiffiesUntilNextHistoryPoint(kUtilisationSamplePeriodJiffies)
    , iStreamHandler(nullptr)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iRampUntilStreamOutCount(0)
    , iLastEventBuffering(false)
{
    ASSERT(iStarvationThreshold < iNormalMax);
    ASSERT(iEventBuffering.is_lock_free());
    iEventId = iObserverThread.Register(MakeFunctor(*this, &StarvationMonitor::EventCallback));
    UpdateStatus(EBuffering);
    iThread = new ThreadFunctor("StarvationMonitor", MakeFunctor(*this, &StarvationMonitor::PullerThread), aThreadPriority);
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
    ASSERT(aMsg != nullptr);
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iNormalMax is queued.
    iLock.Wait();
    const TUint oldPriorityMsgCount = iPriorityMsgCount;
    DoEnqueue(aMsg);
    TBool isFull = (DecodedStreamCount() > iMaxStreamCount || (iStatus != EBuffering && Jiffies() >= iNormalMax));
    if (iStatus == EBuffering && Jiffies() >= iNormalMax) {
        iHaltDelivered = false;
        if (iPlannedHalt) {
            UpdateStatus(ERunning);
            iPlannedHalt = false;
        }
        else {
            UpdateStatus(ERampingUp);
            iCurrentRampValue = Ramp::kMin;
            iRemainingRampSize = iRampUpSize;
        }
        iSemOut.Signal();
        isFull = true;
    }
    if (iPriorityMsgCount > oldPriorityMsgCount) {
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
    if (iStatus == EBuffering && jiffies == 0 && !iPlannedHalt && !iHaltDelivered) {
        iHaltDelivered = true;
        iLock.Signal();
        return iMsgFactory.CreateMsgHalt(); // signal that we won't be providing any more audio for a while
    }
    TBool wait = false;
    if (iStatus == EBuffering && iPriorityMsgCount == 0) {
        if (jiffies == 0 && iPlannedHalt && !iHaltDelivered) {
            wait = IsEmpty(); // allow reading of the halt msg which should be the last item in the queue
        }
        else {
            wait = true;
        }
        iSemOut.Clear(); /* Its possible for Enqueue to signal iSemOut repeatedly.
                            It is safe to clear any past signals here as Enqueue will try
                            to take iLock before signalling again. */
    }
    iLock.Signal();
    if (wait) {
        iSemOut.Wait();
    }
    iHaltDelivered = false;
    msg = DoDequeue();
    return msg;
}

MsgAudio* StarvationMonitor::ProcessAudioOut(MsgAudio* aMsg)
{
    if (aMsg->Jiffies() > kMaxAudioPullSize) {
        MsgAudio* remaining = aMsg->Split(kMaxAudioPullSize);
        EnqueueAtHead(remaining);
    }
    if (iClockPuller != nullptr) {
        if (iJiffiesUntilNextHistoryPoint < aMsg->Jiffies()) {
            MsgAudio* remaining = aMsg->Split(static_cast<TUint>(iJiffiesUntilNextHistoryPoint));
            EnqueueAtHead(remaining);
        }
        iJiffiesUntilNextHistoryPoint -= aMsg->Jiffies();
        if (iJiffiesUntilNextHistoryPoint == 0) {
            iClockPuller->NotifySizeStarvationMonitor(Jiffies());
            iJiffiesUntilNextHistoryPoint = kUtilisationSamplePeriodJiffies;
        }
    }

    return aMsg;
}

void StarvationMonitor::Ramp(MsgAudio* aMsg, Ramp::EDirection aDirection)
{
    ASSERT(iRemainingRampSize > 0);
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, aDirection, split);
    if (split != nullptr) {
        EnqueueAtHead(split);
    }
}

void StarvationMonitor::UpdateStatus(EStatus aStatus)
{
#if 0
    const TChar* status;
    switch (aStatus)
    {
    case ERunning:
        status = "Running";
        break;
    case ERampingDown:
        status = "RampingDown";
        break;
    case EBuffering:
        status = "Buffering";
        break;
    case ERampingUp:
        status = "RampingUp";
        break;
    default:
        status = "unknown(!)";
        break;
    }
    Log::Print("StarvationMonitor, updating status to %s\n", status);
#endif
    if (aStatus == EBuffering) {
        if (iStreamHandler != nullptr) {
            iStreamHandler->NotifyStarving(iMode, iStreamId);
        }
        iEventBuffering.store(true);
        iObserverThread.Schedule(iEventId);
        if (iClockPuller != nullptr) {
            iClockPuller->StopStarvationMonitor();
        }
    }
    else if (iStatus == EBuffering) {
        iEventBuffering.store(false);
        iObserverThread.Schedule(iEventId);
        if (iClockPuller != nullptr) {
            iClockPuller->StartStarvationMonitor(iNormalMax, kUtilisationSamplePeriodJiffies);
        }
    }
    iStatus = aStatus;
}

void StarvationMonitor::EventCallback()
{
    const TBool buffering = iEventBuffering.load();
    if (buffering != iLastEventBuffering) {
        iObserver.NotifyStarvationMonitorBuffering(buffering);
        iLastEventBuffering = buffering;
    }
}

void StarvationMonitor::ProcessMsgIn(MsgChangeInput* /*aMsg*/)
{
    iPriorityMsgCount++;
}

void StarvationMonitor::ProcessMsgIn(MsgStreamInterrupted* /*aMsg*/)
{
    iRampUntilStreamOutCount = DecodedStreamCount() + 1;
    if (iStatus == EBuffering || iStatus == ERampingDown) {
        return;
    }
    if (iStatus == ERunning) {
        iCurrentRampValue = Ramp::kMax;
    }
    iRampDownDuration = Jiffies();
    iRemainingRampSize = iRampDownDuration;
    UpdateStatus(ERampingDown);
}

void StarvationMonitor::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iPlannedHalt = true;
}

void StarvationMonitor::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect flushes to propogate this far down the pipeline
}

void StarvationMonitor::ProcessMsgIn(MsgWait* /*aMsg*/)
{
    ASSERTS(); // don't expect MsgWait to propogate this far down the pipeline
}

void StarvationMonitor::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iExit = true;
    iPriorityMsgCount++;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgMode* aMsg)
{
    iMode.Replace(aMsg->Mode());
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    if (iClockPuller != nullptr) {
        iClockPuller->StopStarvationMonitor();
    }
    iClockPuller = aMsg->ClockPuller();
    if (iClockPuller != nullptr) {
        iClockPuller->StartStarvationMonitor(iNormalMax, kUtilisationSamplePeriodJiffies);
    }
    return aMsg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgChangeInput* aMsg)
{
    iLock.Wait();
    iPriorityMsgCount--;
    iLock.Signal();
    return aMsg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    iStreamHandler = aMsg->StreamInfo().StreamHandler();
    iStreamId = aMsg->StreamInfo().StreamId();
    if (iClockPuller != nullptr) {
        iClockPuller->NewStreamStarvationMonitor(iStreamId);
    }
    iJiffiesUntilNextHistoryPoint = kUtilisationSamplePeriodJiffies;
    if (iRampUntilStreamOutCount > 0) {
        iRampUntilStreamOutCount--;
    }
    return aMsg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    MsgAudio* msg = ProcessAudioOut(aMsg);

    iLock.Wait();
    ASSERT(iPriorityMsgCount > 0 || iStatus != EBuffering);
    TUint remainingSize = Jiffies();
    TBool enteredBuffering = false;
    if (!iPlannedHalt && (remainingSize < iStarvationThreshold) && (iStatus == ERunning)) {
        UpdateStatus(ERampingDown);
        iRampDownDuration = remainingSize + msg->Jiffies();
        iCurrentRampValue = Ramp::kMax;
        iRemainingRampSize = iRampDownDuration;
    }
    if (iStatus == ERampingDown) {
        Ramp(msg, Ramp::EDown);
        if (iRemainingRampSize == 0) {
            UpdateStatus(EBuffering);
            enteredBuffering = true;
        }
        if (Jiffies() == 0) { // Ramp() can cause a msg to be split, meaning that remainingSize is inaccurate
            ASSERT(iCurrentRampValue == Ramp::kMin);
        }
    }
    else if (iStatus == ERampingUp) {
        Ramp(msg, Ramp::EUp);
        /* don't check iCurrentRampValue here.  If our ramp up intersects with a ramp down
           from further up the pipeline, our ramp will end at a value less than Ramp::kMax */
        if (iRemainingRampSize == 0) {
            iCurrentRampValue = Ramp::kMax;
            UpdateStatus(ERunning);
        }
    }

    remainingSize = Jiffies(); // re-calculate this as Ramp() can cause a msg to be split with a fragment re-queued
    if (remainingSize == 0 && iStatus != EBuffering) {
        UpdateStatus(EBuffering);
        enteredBuffering = true;
    }
    if (((remainingSize < iNormalMax) && (remainingSize + msg->Jiffies() >= iNormalMax)) ||
        (enteredBuffering && (remainingSize >= iNormalMax))) {
        iSemIn.Signal();
    }
    iLock.Signal();

    return msg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgSilence* aMsg)
{
    MsgAudio* msg = ProcessAudioOut(aMsg);

    iLock.Wait();
    TBool enteredBuffering = false;
    if (iStatus == ERampingDown && iRampUntilStreamOutCount > 0) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
        UpdateStatus(EBuffering);
        enteredBuffering = true;
    }
    else if (iStatus == ERampingUp) {
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
        UpdateStatus(ERunning);
    }

    const TUint remainingSize = Jiffies();
    if (((remainingSize < iNormalMax) && (remainingSize + msg->Jiffies() >= iNormalMax)) ||
        (enteredBuffering && (remainingSize >= iNormalMax))) {
        iSemIn.Signal();
    }
    iLock.Signal();

    return msg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgHalt* aMsg)
{
    iLock.Wait();
    iHaltDelivered = true;
    iLock.Signal();
    return aMsg;
}

Msg* StarvationMonitor::ProcessMsgOut(MsgQuit* aMsg)
{
    iLock.Wait();
    iPriorityMsgCount--;
    iLock.Signal();
    return aMsg;
}

TBool StarvationMonitor::EnqueueWouldBlock() const
{
    AutoMutex a(iLock);
    return (Jiffies() >= iNormalMax);
}

TBool StarvationMonitor::PullWouldBlock() const
{
    AutoMutex a(iLock);
    if (IsEmpty() || (iStatus == EBuffering && Jiffies() < iNormalMax && iPriorityMsgCount == 0)) {
        return true;
    }
    return false;
}
