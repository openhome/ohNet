#include <OpenHome/Media/VariableDelayBuffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// VariableDelayBuffer

VariableDelayBuffer::VariableDelayBuffer(MsgFactory& aMsgFactory, TUint aMaxSizeJiffies, TUint aInitialDelay, TUint aRampTime)
    : iMsgFactory(aMsgFactory)
    , iMaxJiffies(aMaxSizeJiffies)
    , iDelayJiffies(aInitialDelay)
    , iLock("VDBF")
    , iSem("VDBF", 0)
    , iDelayAdjustment(0)
    , iStatus(EDefault)
    , iRampDirection(Ramp::ENone)
    , iRampDuration(aRampTime)
    , iCurrentRampValue(Ramp::kRampMax)
    , iRemainingRampSize(0)
{
    ASSERT(iDelayJiffies < iMaxJiffies);
    if (iDelayJiffies > 0) {
        Enqueue(iMsgFactory.CreateMsgSilence(iDelayJiffies)); // FIXME - possible benefits in splitting silence into many small blocks?
    }
}

VariableDelayBuffer::~VariableDelayBuffer()
{
}

void VariableDelayBuffer::AdjustDelay(TUint aJiffies)
{
    AutoMutex a(iLock);
    if (aJiffies == iDelayJiffies) {
        return;
    }
    ASSERT(aJiffies < iMaxJiffies);
    iDelayAdjustment += (aJiffies - iDelayJiffies);
    iDelayJiffies = aJiffies;
    iStatus = ERampingDown;
    iRampDirection = Ramp::EDown;
    ASSERT_DEBUG(iCurrentRampValue == Ramp::kRampMax);
    iRemainingRampSize = iRampDuration;
}

void VariableDelayBuffer::Enqueue(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    // Queue the next msg before checking how much data we already have in the buffer
    // This risks us going over the nominal max size for the buffer but guarantees that
    // we don't deadlock if a single message larger than iMaxJiffies is queued.
    DoEnqueue(aMsg);
    iLock.Wait();
    TBool wait = (Jiffies() + iDelayAdjustment > iDelayJiffies);
    iLock.Signal();
    if (wait) {
        iSem.Wait();
    }
}

Msg* VariableDelayBuffer::Dequeue()
{
    Msg* msg;
    iLock.Wait();
    if (iStatus == ERampedDown && iDelayAdjustment > 0) {
        msg = iMsgFactory.CreateMsgSilence(iDelayAdjustment);
        iDelayAdjustment = 0;
        iStatus = ERampingUp;
        iRampDirection = Ramp::EUp;
        ASSERT_DEBUG(iCurrentRampValue == Ramp::kRampMin);
        iRemainingRampSize = iRampDuration;
    }
    else {
        iLock.Signal();
        msg = DoDequeue();
        iLock.Wait();
    }
    iLock.Signal();
    return msg;
}

Msg* VariableDelayBuffer::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

Msg* VariableDelayBuffer::ProcessMsgOut(MsgSilence* aMsg)
{
    return DoProcessMsgOut(aMsg);
}

MsgAudio* VariableDelayBuffer::DoProcessMsgOut(MsgAudio* aMsg)
{
    MsgAudio* msg = aMsg;
    iLock.Wait();
    switch (iStatus)
    {
    case EDefault:
        // nothing to do, allow the message to be passed out unchanged
        break;
    case ERampingDown:
    {
        RampMsg(msg);
        if (iRemainingRampSize == 0) {
            iStatus = ERampedDown;
        }
    }
        break;
    case ERampedDown:
    {
        ASSERT(iDelayAdjustment < 0)
        TUint jiffies = aMsg->Jiffies();
        MsgAudio* remaining = NULL;
        if (jiffies > (TUint)(-iDelayAdjustment)) {
            remaining = msg->Split(iDelayAdjustment);
        }
        iDelayAdjustment -= jiffies;
        msg->RemoveRef();
        msg = remaining;
        if (iDelayAdjustment == 0) {
            iStatus = ERampingUp;
            iRampDirection = Ramp::EUp;
            iRemainingRampSize = iRampDuration;
        }
    }
        break;
    case ERampingUp:
    {
        RampMsg(msg);
        if (iRemainingRampSize == 0) {
            iStatus = EDefault;
        }
    }
        break;
    default:
        ASSERTS();
    }

    if (Jiffies() + iDelayAdjustment > iDelayJiffies) {
        // Too much audio in the buffer.  Block adds until more is read
        (void)iSem.Clear();
    }
    else {
        // room in the buffer.  Allow further data to be added
        iSem.Signal();
    }

    iLock.Signal();
    return msg;
}

void VariableDelayBuffer::RampMsg(MsgAudio* aMsg)
{
    TUint jiffies = aMsg->Jiffies();
    if (aMsg->Jiffies() > iRemainingRampSize) {
        MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
        EnqueueAtHead(remaining);
    }
    MsgAudio* split;
    iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRampDuration, iRampDirection, split);
    ASSERT(split == NULL); // assume we're the first point in the pipeline which applies ramps
    iRemainingRampSize -= jiffies;
}
