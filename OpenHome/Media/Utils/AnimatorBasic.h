#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Media/Pipeline/Pipeline.h>

namespace OpenHome {
    class Environment;
namespace Media {

class PriorityArbitratorAnimator : public IPriorityArbitrator, private INonCopyable
{
public:
    PriorityArbitratorAnimator(TUint aOpenHomeMax);
private: // from IPriorityArbitrator
    TUint Priority(const TChar* aId, TUint aRequested, TUint aHostMax) override;
    TUint OpenHomeMin() const override;
    TUint OpenHomeMax() const override;
    TUint HostRange() const override;
private:
    const TUint iOpenHomeMax;
};

class AnimatorBasic : public PipelineElement, public IPullableClock, public IPipelineAnimator
{
    static const TUint kTimerFrequencyMs = 5;
    static const TInt64 kClockPullDefault = (1 << 29) * 100LL;
    static const TUint kSupportedMsgTypes;
public:
    AnimatorBasic(Environment& aEnv, IPipeline& aPipeline);
    ~AnimatorBasic();
private:
    void DriverThread();
    void ProcessAudio(MsgPlayable* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IPullableClock
    void PullClock(TInt32 aValue);
private: // from IPipelineAnimator
    TUint PipelineDriverDelayJiffies(TUint aSampleRateFrom, TUint aSampleRateTo) override;
private:
    IPipeline& iPipeline;
    Semaphore iSem;
    OsContext* iOsCtx;
    ThreadFunctor *iThread;
    TUint iSampleRate;
    TUint iJiffiesPerSample;
    TUint iNumChannels;
    TUint iBitDepth;
    TUint iPendingJiffies;
    TUint64 iLastTimeUs;
    TUint iNextTimerDuration;
    MsgPlayable* iPlayable;
    Mutex iPullLock;
    TInt64 iPullValue;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

