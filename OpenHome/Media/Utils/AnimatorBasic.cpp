#include <OpenHome/Media/Utils/AnimatorBasic.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

PriorityArbitratorAnimator::PriorityArbitratorAnimator(TUint aOpenHomeMax)
    : iOpenHomeMax(aOpenHomeMax)
{
}

TUint PriorityArbitratorAnimator::Priority(const TChar* /*aId*/, TUint aRequested, TUint aHostMax)
{
    ASSERT(aRequested == iOpenHomeMax);
    return aHostMax;
}

TUint PriorityArbitratorAnimator::OpenHomeMin() const
{
    return iOpenHomeMax;
}

TUint PriorityArbitratorAnimator::OpenHomeMax() const
{
    return iOpenHomeMax;
}

TUint PriorityArbitratorAnimator::HostRange() const
{
    return 1;
}

const TUint AnimatorBasic::kSupportedMsgTypes =   eMode
                                                | eDrain
                                                | eHalt
                                                | eDecodedStream
                                                | ePlayable
                                                | eQuit;

AnimatorBasic::AnimatorBasic(Environment& aEnv, IPipeline& aPipeline, TBool aPullable)
    : PipelineElement(kSupportedMsgTypes)
    , iPipeline(aPipeline)
    , iSem("DRVB", 0)
    , iOsCtx(aEnv.OsCtx())
    , iPullable(aPullable)
    , iSampleRate(0)
    , iPlayable(nullptr)
    , iPullValue(IPullableClock::kNominalFreq)
    , iQuit(false)
{
    iPipeline.SetAnimator(*this);
    iThread = new ThreadFunctor("PipelineAnimator", MakeFunctor(*this, &AnimatorBasic::DriverThread), kPrioritySystemHighest);
    iThread->Start();
}

AnimatorBasic::~AnimatorBasic()
{
    delete iThread;
}

void AnimatorBasic::DriverThread()
{
    // pull the first (assumed non-audio) msg here so that any delays populating the pipeline don't affect timing calculations below.
    Msg* msg = iPipeline.Pull();
    ASSERT(msg != nullptr);
    (void)msg->Process(*this);

    TUint64 now = OsTimeInUs(iOsCtx);
    iLastTimeUs = now;
    iNextTimerDuration = kTimerFrequencyMs;
    iPendingJiffies = kTimerFrequencyMs * Jiffies::kPerMs;
    try {
        for (;;) {
            while (iPendingJiffies > 0) {
                if (iPlayable != nullptr) {
                    ProcessAudio(iPlayable);
                }
                else {
                    Msg* msg = iPipeline.Pull();
                    msg = msg->Process(*this);
                    ASSERT(msg == nullptr);
                }
            }
            if (iQuit) {
                break;
            }
            iLastTimeUs = now;
            if (iNextTimerDuration != 0) {
                try {
                    iSem.Wait(iNextTimerDuration);
                }
                catch (Timeout&) {}
            }
            iNextTimerDuration = kTimerFrequencyMs;
            now = OsTimeInUs(iOsCtx);
            const TUint diffMs = ((TUint)(now - iLastTimeUs + 500)) / 1000;
            if (diffMs > 100) { // assume delay caused by drop-out.  process regular amount of audio
                iPendingJiffies = kTimerFrequencyMs * Jiffies::kPerMs;
            }
            else {
                iPendingJiffies = diffMs * Jiffies::kPerMs;
                if (iPullValue != IPullableClock::kNominalFreq) {
                    TInt64 pending64 = iPullValue * iPendingJiffies;
                    pending64 /= IPullableClock::kNominalFreq;
                    //Log::Print("iPendingJiffies=%08x, pull=%08x\n", iPendingJiffies, pending64); // FIXME
                    //TInt pending = (TInt)iPendingJiffies + (TInt)pending64;
                    //Log::Print("Pulled clock, now want %u jiffies (%ums, %d%%) extra\n", (TUint)pending, pending/Jiffies::kPerMs, (pending-(TInt)iPendingJiffies)/iPendingJiffies); // FIXME
                    iPendingJiffies = (TUint)pending64;
                }
            }
        }
    }
    catch (ThreadKill&) {}

    // pull until the pipeline is emptied
    while (!iQuit) {
        Msg* msg = iPipeline.Pull();
        msg = msg->Process(*this);
        ASSERT(msg == nullptr);
        if (iPlayable != nullptr) {
            iPlayable->RemoveRef();
        }
    }
}

void AnimatorBasic::ProcessAudio(MsgPlayable* aMsg)
{
    iPlayable = nullptr;
    const TUint numSamples = aMsg->Bytes() / ((iBitDepth/8) * iNumChannels);
    TUint jiffies = numSamples * iJiffiesPerSample;
    if (jiffies > iPendingJiffies) {
        jiffies = iPendingJiffies;
        const TUint bytes = Jiffies::ToBytes(jiffies, iJiffiesPerSample, iNumChannels, (iBitDepth/8));
        if (bytes == 0) {
            iPendingJiffies = 0;
            iPlayable = aMsg;
            return;
        }
        iPlayable = aMsg->Split(bytes);
    }
    iPendingJiffies -= jiffies;
    aMsg->RemoveRef();
}

Msg* AnimatorBasic::ProcessMsg(MsgMode* aMsg)
{
    iPullValue = IPullableClock::kNominalFreq;
    aMsg->RemoveRef();
    return nullptr;
}

Msg* AnimatorBasic::ProcessMsg(MsgDrain* aMsg)
{
    if (iPlayable != nullptr) {
        iPlayable->RemoveRef();
        iPlayable = nullptr;
    }
    if (iSampleRate != 0) {
        PullClock(iSampleRate, IPullableClock::kNominalFreq);
    }
    aMsg->ReportDrained();
    aMsg->RemoveRef();
    return nullptr;
}

Msg* AnimatorBasic::ProcessMsg(MsgHalt* aMsg)
{
    iPendingJiffies = 0;
    iNextTimerDuration = 0;
    aMsg->ReportHalted();
    aMsg->RemoveRef();
    return nullptr;
}

Msg* AnimatorBasic::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iSampleRate = stream.SampleRate();
    iNumChannels = stream.NumChannels();
    iBitDepth = stream.BitDepth();
    iJiffiesPerSample = Jiffies::PerSample(iSampleRate);
    aMsg->RemoveRef();
    return nullptr;
}

Msg* AnimatorBasic::ProcessMsg(MsgPlayable* aMsg)
{
    if (aMsg->ClockPullMultiplier() != IPullableClock::kPullNone) {
        PullClock(iSampleRate, aMsg->ClockPullMultiplier());
    }
    ProcessAudio(aMsg);
    return nullptr;
}

Msg* AnimatorBasic::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    iPendingJiffies = 0;
    iNextTimerDuration = 0;
    aMsg->RemoveRef();
    return nullptr;
}

void AnimatorBasic::PullClock(TUint /*aSampleRate*/, TUint aMultiplier)
{
    if (!iPullable || iPullValue == aMultiplier) {
        return;
    }
    iPullValue = aMultiplier;
    LOG(kPipeline, "AnimatorBasic::PullClock now at %u%%\n", (TUint)((iPullValue * 100) / IPullableClock::kNominalFreq));
}

TUint AnimatorBasic::PipelineAnimatorBufferJiffies()
{
    return 0;
}

TUint AnimatorBasic::PipelineAnimatorDelayJiffies(TUint /*aSampleRate*/, TUint /*aBitDepth*/, TUint /*aNumChannels*/)
{
    return 0;
}
