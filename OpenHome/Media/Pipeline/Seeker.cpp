#include <OpenHome/Media/Pipeline/Seeker.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Seeker::Seeker(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISeeker& aSeeker, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iSeeker(aSeeker)
    , iLock("SEEK")
    , iState(ERunning)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMax)
    , iSeekSeconds(UINT_MAX)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
{
}

Seeker::~Seeker()
{
}

TBool Seeker::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute, TBool aRampDown)
{
    AutoMutex a(iLock);
    if (iState != ERunning || iTrackId != aTrackId || iStreamId != aStreamId || !iStreamIsSeekable) {
        return false;
    }

    iSeekSeconds = aSecondsAbsolute;
    iFlushEndJiffies = 0;

    if (iState == ERampingUp) {
        iState = ERampingDown;
        iRemainingRampSize = iRampDuration - iRemainingRampSize;
        // leave iCurrentRampValue unchanged
    }
    else if (!aRampDown || iState == EFlushing) {
        DoSeek();
    }
    else {
        iState = ERampingDown;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMax;
    }
    return true;
}

Msg* Seeker::Pull()
{
    Msg* msg;
    do {
        msg = (iQueue.IsEmpty()? iUpstreamElement.Pull() : iQueue.Dequeue());
        iLock.Wait();
        msg = msg->Process(*this);
        iLock.Signal();
    } while (msg == NULL);
    return msg;
}

Msg* Seeker::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgTrack* aMsg)
{
    NewStream();
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgEncodedStream* aMsg)
{
    NewStream();
    iStreamId = aMsg->StreamId();
    iStreamIsSeekable = aMsg->Seekable();
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Seeker::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Seeker::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == EFlushing);
        aMsg->RemoveRef();
        iTargetFlushId = MsgFlush::kIdInvalid;
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMin;
        return NULL;
    }
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iStreamPosJiffies = Jiffies::JiffiesPerSample(streamInfo.SampleRate());
    iStreamPosJiffies *= streamInfo.SampleStart();
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Seeker::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Seeker::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Seeker::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

void Seeker::NotifySeekComplete(TUint aHandle, TUint aFlushId)
{
    AutoMutex a(iLock);
    if (aHandle != iSeekHandle) {
        return;
    }
    ASSERT(iState == EFlushing);
    iTargetFlushId = aFlushId;
    if (iTargetFlushId == MsgFlush::kIdInvalid) {
        HandleSeekFail();
    }
}

void Seeker::DoSeek()
{
    iState = EFlushing; /* set this before calling StartSeek as its possible NotifySeekComplete
                           could be called from another thread before StartSeek returns. */
    iSeeker.StartSeek(iTrackId, iStreamId, iSeekSeconds, *this, iSeekHandle);
    if (iSeekHandle == ISeeker::kHandleError) {
        HandleSeekFail();
    }
    else {
        while (!iQueue.IsEmpty()) {
            iQueue.Dequeue()->RemoveRef();
        }
        iQueue.Enqueue(iMsgFactory.CreateMsgHalt()); /* inform downstream parties (StarvationMonitor)
                                                        that any subsequent break in audio is expected */
    }
}

Msg* Seeker::ProcessFlushable(Msg* aMsg)
{
    if (iState == EFlushing) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* Seeker::ProcessAudio(MsgAudio* aMsg)
{
    iStreamPosJiffies += aMsg->Jiffies();
    if (iFlushEndJiffies != 0 && iFlushEndJiffies < iStreamPosJiffies) {
        ASSERT(iState == EFlushing);
        const TUint splitJiffies = (TUint)(iStreamPosJiffies - iFlushEndJiffies);
        MsgAudio* split = aMsg->Split(aMsg->Jiffies() - splitJiffies);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
        iStreamPosJiffies -= splitJiffies;
        ASSERT(iStreamPosJiffies == iFlushEndJiffies);
    }
    if (iFlushEndJiffies == iStreamPosJiffies) {
        ASSERT(iState == EFlushing);
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMin;
    }
    if (iState == ERampingDown || iState == ERampingUp) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != NULL) {
                iQueue.EnqueueAtHead(split);
            }
        }
        split = NULL;
        const Ramp::EDirection direction = (iState == ERampingDown? Ramp::EDown : Ramp::EUp);
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, direction, split);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            if (iState == ERampingDown) {
                DoSeek();
            }
            else { // iState == ERampingUp
                iState = ERunning;
            }
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

void Seeker::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kMax;
    iState = ERunning;
    iSeekHandle = ISeeker::kHandleError;
    iStreamIsSeekable = true;
    iStreamPosJiffies = 0;
    iFlushEndJiffies = 0;
}

void Seeker::HandleSeekFail()
{
    TUint64 seekJiffies = ((TUint64)iSeekSeconds) * Jiffies::kPerSecond;
    if (seekJiffies > iStreamPosJiffies) {
        iFlushEndJiffies = seekJiffies;
        iState = EFlushing;
    }
    else {
        /* No special treatment of (seekJiffies == iStreamPosJiffies) required.
           If we happen to be at the precise seek point, we'd just ramp up anyway... */
        iState = ERampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMin;
    }
}
