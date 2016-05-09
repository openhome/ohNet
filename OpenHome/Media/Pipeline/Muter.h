#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/MuteManager.h>

namespace OpenHome {
namespace Media {

/*
    Count (un)mute calls
    Treat user mutes separately
    only unmute when both counts reach zero
    know #jiffies downstream
    callback that a mute is applied after passing on that many samples of silence
    if halted, send MsgDrain to determine when downstream buffers are empty
*/

class Muter : public PipelineElement, public IPipelineElementUpstream, public IMute, private INonCopyable
{
    friend class SuiteMuter;

    static const TUint kSupportedMsgTypes;
public:
    Muter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream, TUint aRampDuration);
    void SetAnimator(IPipelineAnimator& aPipelineAnimator);
public: // from IMute
    void Mute() override;
    void Unmute() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    void PlayingSilence();
    void PipelineHalted();
private:
    enum EState
    {
        eRunning
       ,eRampingDown
       ,eRampingUp
       ,eMuting      // ramped down, waiting for animator to start playing silence
       ,eMuted       // ramped down, animator playing silence
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstream;
    IPipelineAnimator* iAnimator;
    Mutex iLock;
    Semaphore iSemMuted;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    TUint iJiffiesUntilMute;
    MsgQueueLite iQueue; // empty unless we have to split a msg during a ramp
    TBool iHalting;
    TBool iHalted;
};

} // namespace Media
} // namespace OpenHome

