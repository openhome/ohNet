#include <OpenHome/Media/Pipeline/MuterVolume.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Functor.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint MuterVolume::kSupportedMsgTypes =   eMode
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
const TUint MuterVolume::kJiffiesUntilMute = 10 * Jiffies::kPerMs;

MuterVolume::MuterVolume(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iUpstream(aUpstream)
    , iVolumeRamper(nullptr)
    , iLock("MPMT")
    , iSemMuted("MPMT", 0)
    , iState(State::eRunning)
    , iHalted(true)
{
}

void MuterVolume::Start(IVolumeRamper& aVolumeRamper)
{
    AutoMutex _(iLock);
    iVolumeRamper = &aVolumeRamper;
    if (iState == State::eMuted) {
        iVolumeRamper->SetMuted();
    }
}

void MuterVolume::Mute()
{
    LOG(kPipeline, "MuterVolume::Mute\n");
    TBool block = false;
    {
        AutoMutex _(iLock);
        if (iVolumeRamper == nullptr) { // not yet Start()ed
            iState = State::eMuted;
        }
        else {
            switch (iState)
            {
            case State::eMutingRamp:
            case State::eMutingWait:
            case State::eMuted:
                break;
            case State::eRunning:
            case State::eUnmutingRamp:
                if (iHalted) {
                    iState = State::eMuted;
                    iVolumeRamper->SetMuted();
                }
                else if (iVolumeRamper->BeginMute() == IVolumeRamper::Status::eComplete) {
                    iState = State::eMuted;
                }
                else {
                    iState = State::eMutingRamp;
                    block = true;
                }
                break;
            }

            if (block) {
                (void)iSemMuted.Clear();
            }
        }
    }
    if (block) {
        iSemMuted.Wait();
    }
}

void MuterVolume::Unmute()
{
    LOG(kPipeline, "MuterVolume::Unmute\n");
    AutoMutex _(iLock);
    if (iVolumeRamper == nullptr) { // not yet Start()ed
        iState = State::eRunning;
    }
    else {
        switch (iState)
        {
        case State::eRunning:
        case State::eUnmutingRamp:
            break;
        case State::eMutingRamp:
        case State::eMutingWait:
            iSemMuted.Signal();
            // fall through
        case State::eMuted:
            if (iHalted) {
                iState = State::eRunning;
                iVolumeRamper->SetUnmuted();
            }
            else if (iVolumeRamper->BeginUnmute() == IVolumeRamper::Status::eComplete) {
                iState = State::eRunning;
            }
            else {
                iState = State::eUnmutingRamp;
            }
            break;
        }
    }
}

Msg* MuterVolume::Pull()
{
    Msg* msg = iUpstream.Pull();
    iLock.Wait();
    msg = msg->Process(*this);
    iLock.Signal();
    return msg;
}

Msg* MuterVolume::ProcessMsg(MsgHalt* aMsg)
{
    auto msg = iMsgFactory.CreateMsgHalt(aMsg->Id(), MakeFunctor(*this, &MuterVolume::PipelineHalted));
    aMsg->RemoveRef();
    return msg;
}

Msg* MuterVolume::ProcessMsg(MsgAudioPcm* aMsg)
{
    iHalted = false;
    ProcessAudio(aMsg);
    return aMsg;
}

Msg* MuterVolume::ProcessMsg(MsgSilence* aMsg)
{
    ProcessAudio(aMsg);
    return aMsg;
}

void MuterVolume::ProcessAudio(MsgAudio* aMsg)
{
    const auto jiffies = aMsg->Jiffies();
    switch (iState)
    {
    case State::eMutingRamp:
        if (iVolumeRamper->StepMute(jiffies) == IVolumeRamper::Status::eComplete) {
            iState = State::eMutingWait;
            iJiffiesUntilMute = kJiffiesUntilMute;
        }
        break;
    case State::eUnmutingRamp:
        if (iVolumeRamper->StepUnmute(jiffies) == IVolumeRamper::Status::eComplete) {
            iState = State::eRunning;
        }
        break;
    case State::eMutingWait:
        if (iJiffiesUntilMute > jiffies) {
            iJiffiesUntilMute -= jiffies;
        }
        else {
            iJiffiesUntilMute = 0;
            iState = State::eMuted;
            iSemMuted.Signal();
        }
        break;
    default:
        break;
    }
}

void MuterVolume::PipelineHalted()
{
    AutoMutex _(iLock);
    iHalted = true;
    iJiffiesUntilMute = 0;
    iSemMuted.Signal();
    switch (iState)
    {
    case State::eRunning:
        break;
    case State::eMutingRamp:
    case State::eMutingWait:
        iState = State::eMuted;
        iVolumeRamper->SetMuted();
        break;
    case State::eUnmutingRamp:
        iState = State::eRunning;
        iVolumeRamper->SetUnmuted();
        break;
    case State::eMuted:
        break;
    }
}
