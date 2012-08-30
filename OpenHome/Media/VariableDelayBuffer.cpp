#include <OpenHome/Media/VariableDelayBuffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// VariableDelayBuffer

VariableDelayBuffer::VariableDelayBuffer(MsgFactory& aMsgFactory, TUint aMaxSizeJiffies, TUint aInitialDelay)
    : iMsgFactory(aMsgFactory)
    , iMaxJiffies(aMaxSizeJiffies)
    , iDelayJiffies(aInitialDelay)
    , iLock("VDBF")
    , iSem("VDBF", 0)
    , iDelayAdjustment(0)
{
    ASSERT(iDelayJiffies < iMaxJiffies);
    if (iDelayJiffies > 0) {
        Enqueue(iMsgFactory.CreateMsgSilence(iDelayJiffies));
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
    if (iDelayAdjustment > 0) {
        msg = iMsgFactory.CreateMsgSilence(iDelayAdjustment);
        iDelayAdjustment = 0;
    }
    else {
        iLock.Signal();
        msg = DoDequeue();
        iLock.Wait();
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

MsgAudio* VariableDelayBuffer::DoProcessMsgOut(MsgAudio* aMsg)
{
    MsgAudio* msg = aMsg;
    iLock.Wait();
    if (iDelayAdjustment < 0) {
        TUint jiffies = aMsg->Jiffies();
        if (jiffies > (TUint)(-iDelayAdjustment)) {
            MsgAudio* remaining = msg->Split(iDelayAdjustment);
            msg->RemoveRef();
            msg = remaining;
            iDelayAdjustment = 0;
        }
        else {
            iDelayAdjustment -= jiffies;
            msg->RemoveRef();
            msg = NULL;
        }
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
