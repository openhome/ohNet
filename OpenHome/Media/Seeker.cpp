#include <OpenHome/Media/Seeker.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

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
    , iCurrentRampValue(Ramp::kRampMax)
    , iSeekSeconds(UINT_MAX)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iStreamHandler(NULL)
{
}

Seeker::~Seeker()
{
}

TBool Seeker::Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute, TBool aRampDown)
{
    AutoMutex a(iLock);
    if (iState != ERunning || iTrackId != aTrackId || iStreamId != aStreamId) {
        return false;
    }

    iSeekSeconds = aSecondsAbsolute;

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
        iCurrentRampValue = Ramp::kRampMax;
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

Msg* Seeker::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
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

Msg* Seeker::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERT(iState == ERunning);
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgTrack* aMsg)
{
    NewStream();
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgEncodedStream* aMsg)
{
    NewStream();
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    return aMsg;
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
        iCurrentRampValue = Ramp::kRampMin;
        return NULL;
    }
    return aMsg;
}

Msg* Seeker::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

void Seeker::DoSeek()
{
    iTargetFlushId = iSeeker.TrySeek(iTrackId, iStreamId, iSeekSeconds);
    if (iTargetFlushId == MsgFlush::kIdInvalid) {
        if (iState != ERunning) {
            iState = ERampingUp;
            iRemainingRampSize = iRampDuration;
            iCurrentRampValue = Ramp::kRampMin;
        }
    }
    else {
        iState = EFlushing;
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
    iCurrentRampValue = Ramp::kRampMax;
    iState = ERunning;
}
