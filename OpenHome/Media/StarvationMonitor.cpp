#include <OpenHome/Media/StarvationMonitor.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// StarvationMonitor

StarvationMonitor::StarvationMonitor(MsgFactory& aMsgFactory, TUint aSize, TUint aStarvationThreshold, TUint aGorgeSize, TUint aRampUpSize)
    : iNormalMax(aSize)
    , iStarvationThreshold(aStarvationThreshold)
    , iGorgeSize(aGorgeSize)
    , iRampUpSize(aRampUpSize)
    , iLock("STRV")
    , iSemIn("STR1", 0)
    , iSemOut("STR2", 0)
    , iStatus(ERunning)
    , iCurrentRampValue(Ramp::kRampMax)
    , iPlannedHalt(false)
{
    ASSERT(iStarvationThreshold < iNormalMax);
    ASSERT(iNormalMax < iGorgeSize);
    Enqueue(aMsgFactory.CreateMsgSilence(aSize));
}

void StarvationMonitor::Enqueue(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iMaxJiffies is queued.
    DoEnqueue(aMsg);
    iLock.Wait();
    TBool isFull = (iStatus != EStarving && Jiffies() >= iNormalMax);
    if (iStatus == EStarving && Jiffies() >= iGorgeSize) {
        iStatus = ERampingUp;
        ASSERT(iCurrentRampValue == Ramp::kRampMin);
        iRemainingRampSize = iRampUpSize;
        iSemOut.Signal();
        isFull = true;
    }
    iLock.Signal();
    if (isFull) {
        iSemIn.Wait();
    }
}

Msg* StarvationMonitor::Pull()
{
    iLock.Wait();
    const TBool wait = (iStatus == EStarving && Jiffies() < iGorgeSize);
    iLock.Signal();
    if (wait) {
        iSemOut.Wait();
    }
    Msg* msg = DoDequeue();
    return msg;
}

MsgAudio* StarvationMonitor::DoProcessMsgOut(MsgAudio* aMsg)
{
    ASSERT(iStatus != EStarving);
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
            iStatus = EStarving;
        }
    }
    else if (iStatus == ERampingUp) {
        Ramp(aMsg, iRampUpSize, Ramp::EUp);
        if (iCurrentRampValue == Ramp::kRampMax) {
            iStatus = ERunning;
        }
    }

    remainingSize = Jiffies();
    if ((remainingSize < iNormalMax) && (remainingSize + aMsg->Jiffies() >= iNormalMax)) {
        iSemIn.Signal();
    }

    return aMsg;
}

void StarvationMonitor::Ramp(MsgAudio* aMsg, TUint aRampDuration, Ramp::EDirection aDirection)
{
    TUint jiffies = aMsg->Jiffies();
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, aRampDuration, aDirection, split);
    if (split != NULL) {
        EnqueueAtHead(split);
    }
    iRemainingRampSize -= jiffies;
}

void StarvationMonitor::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iPlannedHalt = true;
}

void StarvationMonitor::ProcessMsgIn(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect flushes to propogate this far down the pipeline
}

Msg* StarvationMonitor::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

Msg* StarvationMonitor::ProcessMsgOut(MsgSilence* aMsg)
{
    return DoProcessMsgOut(aMsg);
}
