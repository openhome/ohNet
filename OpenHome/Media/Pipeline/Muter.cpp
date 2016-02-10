#include <OpenHome/Media/Pipeline/Muter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Functor.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint Muter::kSupportedMsgTypes =   eMode
                                        | eTrack
                                        | eDrain
                                        | eEncodedStream
                                        | eMetatext
                                        | eStreamInterrupted
                                        | eHalt
                                        | eDecodedStream
                                        | eAudioPcm
                                        | eSilence
                                        | eQuit;

Muter::Muter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream, TUint aRampDuration)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iUpstream(aUpstream)
    , iLock("MPMT")
    , iSemMuted("MPMT", 0)
    , iState(eRunning)
    , iRampDuration(aRampDuration)
    , iAnimatorBufferJiffies(0)
    , iRemainingRampSize(0)
    , iCurrentRampValue(Ramp::kMax)
    , iHalting(false)
    , iHalted(true)
{
}

void Muter::SetAnimator(IPipelineAnimator& aPipelineAnimator)
{
    iAnimatorBufferJiffies = aPipelineAnimator.PipelineAnimatorBufferJiffies();
}

void Muter::Mute()
{
    LOG(kPipeline, "Muter::Mute\n");
    TBool block = false;
    {
        AutoMutex _(iLock);
        if (iState == eRunning) {
            if (iHalted) {
                iState = eMuted;
            }
            else if (iHalting) {
                iState = eMuting;
                block = true;
            }
            else {
                iState = eRampingDown;
                iRemainingRampSize = iRampDuration;
                iCurrentRampValue = Ramp::kMax;
                block = true;
            }
        }
        else if (iState == eRampingUp) {
            if (iRemainingRampSize == iRampDuration) {
                iState = eMuted;
            }
            else {
                iState = eRampingDown;
                iRemainingRampSize = iRampDuration - iRemainingRampSize;
                block = true;
            }
        }
        else { // shouldn't be possible to be called for remaining states
            ASSERTS();
        }
        if (block) {
            (void)iSemMuted.Clear();
        }
    }
    if (block) {
        iSemMuted.Wait();
    }
}

void Muter::Unmute()
{
    LOG(kPipeline, "Muter::Unmute\n");
    AutoMutex _(iLock);
    switch (iState)
    {
    case eRunning:
    case eRampingUp:
        // not supported - error in upstream IMute?
        ASSERTS();
        break;
    case eRampingDown:
        iSemMuted.Signal();
        if (iRemainingRampSize == iRampDuration) {
            iState = eRunning;
        }
        else {
            iState = eRampingUp;
            iRemainingRampSize = iRampDuration - iRemainingRampSize;
        }
        break;
    case eMuting:
        iSemMuted.Signal();
        iHalting = false;
        iState = eRampingUp;
        iRemainingRampSize = iRampDuration;
        iCurrentRampValue = Ramp::kMin;
        break;
    case eMuted:
        if (iHalted) {
            iState = eRunning;
        }
        else {
            iState = eRampingUp;
            iRemainingRampSize = iRampDuration;
            iCurrentRampValue = Ramp::kMin;
        }
        break;
    }
}

Msg* Muter::Pull()
{
    Msg* msg;
    if (!iQueue.IsEmpty()) {
        msg = iQueue.Dequeue();
    }
    else {
        msg = iUpstream.Pull();
    }
    iLock.Wait();
    msg = msg->Process(*this);
    iLock.Signal();
    ASSERT(msg != nullptr);
    return msg;
}

Msg* Muter::ProcessMsg(MsgHalt* aMsg)
{
    auto msg = iMsgFactory.CreateMsgHalt(aMsg->Id(), MakeFunctor(*this, &Muter::PipelineHalted));
    aMsg->RemoveRef();
    iHalting = true;
    if (iState == eRampingDown) {
        iState = eMuting;
        iRemainingRampSize = 0;
        iCurrentRampValue = Ramp::kMin;
    }
    return msg;
}

Msg* Muter::ProcessMsg(MsgAudioPcm* aMsg)
{
    iHalting = iHalted = false;
    MsgAudio* msg = aMsg;
    switch (iState)
    {
    case eRunning:
        break;
    case eRampingDown:
    case eRampingUp:
    {
        MsgAudio* split;
        if (msg->Jiffies() > iRemainingRampSize && iRemainingRampSize > 0) {
            split = msg->Split(iRemainingRampSize);
            if (split != nullptr) {
                iQueue.EnqueueAtHead(split);
            }
        }
        split = nullptr;
        const Ramp::EDirection direction = (iState == eRampingDown? Ramp::EDown : Ramp::EUp);
        if (iRemainingRampSize > 0) {
            iCurrentRampValue = msg->SetRamp(iCurrentRampValue, iRemainingRampSize, direction, split);
        }
        if (iRemainingRampSize == 0) {
            if (iState == eRampingUp) {
                iState = eRunning;
            }
            else {
                iState = eMuting;
                iJiffiesUntilMute = iAnimatorBufferJiffies;
            }
        }
        if (split != nullptr) {
            iQueue.EnqueueAtHead(split);
        }
    }
        break;
    case eMuting:
    {
        const TUint size = aMsg->Jiffies();
        if (size >= iJiffiesUntilMute) {
            PlayingSilence();
        }
        else {
            iJiffiesUntilMute -= size;
        }
    }
        // fallthrough
    case eMuted:
    {
        MsgSilence* silence = iMsgFactory.CreateMsgSilence(aMsg->Jiffies());
        msg->RemoveRef();
        msg = silence;
    }
        break;
    }

    return msg;
}

Msg* Muter::ProcessMsg(MsgSilence* aMsg)
{
    switch (iState)
    {
    case eRunning:
    case eMuting:
    case eMuted:
        break;
    case eRampingDown:
        iState = eMuted;
        break;
    case eRampingUp:
        iState = eRunning;
        break;
    }
    return aMsg;
}

void Muter::PlayingSilence()
{
    iJiffiesUntilMute = 0;
    iState = eMuted;
    iSemMuted.Signal();
}

void Muter::PipelineHalted()
{
    AutoMutex _(iLock);
    if (iHalting) {
        iHalted = true;
    }
    if (iState == eMuting) {
        PlayingSilence();
    }
}
