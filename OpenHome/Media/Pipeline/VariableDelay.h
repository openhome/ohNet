#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>

namespace OpenHome {
namespace Media {

/*
Element which introduces a delay (likely for lip syncing)
If the delay is increased, silence is introduced.
If the delay is decreased, audio (pulled from upstream) is discarded.
Before any change in delay is actioned, audio spends RampDuration ramping down.
After a delay is actioned, audio spends RampDuration ramping up.
FIXME - no handling of pause-resumes
*/
    
class VariableDelay : public PipelineElement, public IPipelineElementUpstream, private IClockPullerReservoir
{
    static const TUint kMaxMsgSilenceDuration = Jiffies::kPerMs * 5;
    friend class SuiteVariableDelay;
    static const TUint kSupportedMsgTypes;
public:
    VariableDelay(const TChar* aId, MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aDownstreamDelay, TUint aMinDelay, TUint aRampDuration);
    virtual ~VariableDelay();
    void OverrideAnimatorLatency(TUint aJiffies); // 0 => do not override
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    Msg* NextMsg();
    void ApplyAnimatorOverride();
    void RampMsg(MsgAudio* aMsg);
    void ResetStatusAndRamp();
    void SetupRamp();
    void StartClockPuller();
private: // from PipelineElement (IMsgProcessor)
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private: // from IClockPullerReservoir
    void Start(TUint aExpectedPipelineJiffies) override;
    void Stop() override;
    void Reset() override;
    void NotifySize(TUint aJiffies) override;
private:
    enum EStatus
    {
        EStarting
       ,ERunning
       ,ERampingDown
       ,ERampedDown
       ,ERampingUp
    };
private:
    const TChar* iId;
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    Mutex iLock;
    MsgQueueLite iQueue;
    TUint iDelayJiffies;
    TUint iDelayJiffiesTotal;
    TInt iDelayAdjustment;
    EStatus iStatus;
    Ramp::EDirection iRampDirection;
    const TUint iDownstreamDelay;
    const TUint iMinDelay;
    const TUint iRampDuration;
    TBool iWaitForAudioBeforeGeneratingSilence;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    BwsMode iMode;
    IClockPuller* iClockPuller;
    MsgDecodedStream* iDecodedStream;
    TUint iAnimatorLatencyOverride;
    TBool iAnimatorOverridePending;
};

} // namespace Media
} // namespace OpenHome

