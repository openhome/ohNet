#include <OpenHome/Media/Skipper.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

Skipper::Skipper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iLock("SKIP")
    , iState(ERunning)
    , iRampDuration(aRampDuration)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kRampMax)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iTrackId(UINT_MAX)
    , iStreamId(UINT_MAX)
    , iStreamHandler(NULL)
{
}

Skipper::~Skipper()
{
}

void Skipper::RemoveCurrentStream(TBool aRampDown)
{
    iLock.Wait();
    (void)TryRemoveCurrentStream(aRampDown);
    iLock.Signal();
}

TBool Skipper::TryRemoveStream(TUint aTrackId, TUint aStreamId, TBool aRampDown)
{
    AutoMutex a(iLock);
    if (iTrackId == aTrackId && iStreamId == aStreamId) {
        return TryRemoveCurrentStream(aRampDown);
    }
    return false;
}

Msg* Skipper::Pull()
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

Msg* Skipper::ProcessMsg(MsgTrack* aMsg)
{
    NewStream();
    iTrackId = aMsg->IdPipeline();
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgEncodedStream* aMsg)
{
    NewStream();
    iStreamId = aMsg->StreamId();
    iStreamHandler = aMsg->StreamHandler();
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Skipper::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* Skipper::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        ASSERT(iState == EFlushing);
        aMsg->RemoveRef();
        iTargetFlushId = MsgFlush::kIdInvalid;
        return NULL;
    }
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERT(iState == ERunning);
    return aMsg;
}

Msg* Skipper::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Skipper::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessAudio(aMsg);
}

Msg* Skipper::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Skipper::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}

TBool Skipper::TryRemoveCurrentStream(TBool aRampDown)
{
    EState state = iState;
    if (!aRampDown) {
        StartFlushing(false); // if we don't need to ramp down we should already be halted (so don't need to generate another MsgHalt)
    }
    else if (iState == ERunning) {
        iState = ERamping;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kRampMax;
    }
    return (state != iState);
}

void Skipper::StartFlushing(TBool aSendHalt)
{
    if (aSendHalt) {
        iQueue.Enqueue(iMsgFactory.CreateMsgHalt()); /* inform downstream parties (StarvationMonitor)
                                                        that any subsequent break in audio is expected */
    }
    iState = EFlushing;
    iTargetFlushId = (iStreamHandler==NULL? MsgFlush::kIdInvalid : iStreamHandler->TryStop(iTrackId, iStreamId));
}

Msg* Skipper::ProcessFlushable(Msg* aMsg)
{
    if (iState == EFlushing) {
        aMsg->RemoveRef();
        return NULL;
    }
    return aMsg;
}

Msg* Skipper::ProcessAudio(MsgAudio* aMsg)
{
    if (iState == ERamping) {
        MsgAudio* split;
        if (aMsg->Jiffies() > iRemainingRampSize) {
            split = aMsg->Split(iRemainingRampSize);
            if (split != NULL) {
                split->RemoveRef(); // we're going to flush the rest of the stream so no need to add split to iQueue
            }
        }
        split = NULL;
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EDown, split);
        if (split != NULL) {
            iQueue.EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            StartFlushing(true);
        }
        return aMsg;
    }

    return ProcessFlushable(aMsg);
}

void Skipper::NewStream()
{
    iRemainingRampSize = 0;
    iCurrentRampValue = Ramp::kRampMax;
    iState = ERunning;
}
