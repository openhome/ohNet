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

class IVariableDelayObserver
{
public:
    virtual ~IVariableDelayObserver() {}
    virtual void NotifyDelayApplied(TUint aJiffies) = 0;
};

class VariableDelayBase : public PipelineElement, public IPipelineElementUpstream
{
    static const TUint kMaxMsgSilenceDuration = Jiffies::kPerMs * 5;
    friend class SuiteVariableDelay;
    friend class SuiteVariableDelayLeft;
    friend class SuiteVariableDelayRight;
    static const TUint kSupportedMsgTypes;
public:
    virtual ~VariableDelayBase();
protected:
    VariableDelayBase(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration, const TChar* aId);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
protected:
    void HandleDelayChange(TUint aNewDelay);
    inline const TChar* Status() const;
private:
    Msg* NextMsg();
    void ApplyAnimatorOverride();
    void RampMsg(MsgAudio* aMsg);
    void ResetStatusAndRamp();
    void SetupRamp();
protected: // from PipelineElement (IMsgProcessor)
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    virtual void LocalDelayApplied() = 0;
private:
    enum EStatus
    {
        EStarting
       ,ERunning
       ,ERampingDown
       ,ERampedDown
       ,ERampingUp
    };
protected:
    MsgFactory& iMsgFactory;
    Mutex iLock;
    IClockPuller* iClockPuller;
    TUint iDelayJiffies;
private:
    IPipelineElementUpstream& iUpstreamElement;
    const TUint iRampDuration;
    const TChar* iId;
    MsgQueueLite iQueue;
    TInt iDelayAdjustment;
    EStatus iStatus;
    Ramp::EDirection iRampDirection;
    TBool iWaitForAudioBeforeGeneratingSilence;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    BwsMode iMode;
    MsgDecodedStream* iDecodedStream;
};

class VariableDelayLeft : public VariableDelayBase, public IVariableDelayObserver
{
public:
    VariableDelayLeft(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration, TUint aDownstreamDelay);
private: // from PipelineElement (IMsgProcessor)
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
private: // from VariableDelayBase
    void LocalDelayApplied() override;
private: // from IVariableDelayObserver
    void NotifyDelayApplied(TUint aJiffies) override;
private:
    void StartClockPuller();
private:
    const TUint iDownstreamDelay; // leave this much delay for downstream
    TUint iDownstreamDelayCurrent;
};

class VariableDelayRight : public VariableDelayBase
{
public:
    VariableDelayRight(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration, IVariableDelayObserver& aObserver, TUint aMinDelay);
    void OverrideAnimatorLatency(TUint aJiffies); // 0 => do not override
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from PipelineElement (IMsgProcessor)
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
private: // from VariableDelayBase
    void LocalDelayApplied() override;
private:
    void ApplyAnimatorOverride();
private:
    IVariableDelayObserver& iObserver;
    const TUint iMinDelay;
    TUint iDelayJiffiesTotal;
    TUint iAnimatorLatencyOverride;
    TBool iAnimatorOverridePending;
};

} // namespace Media
} // namespace OpenHome

