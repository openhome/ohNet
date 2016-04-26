#include <OpenHome/Media/Pipeline/StarvationRamper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/FlywheelRamper.h>
#include <OpenHome/Media/Pipeline/StarvationMonitor.h> // FIXME - for IStarvationMonitorObserver
#include <OpenHome/Media/Pipeline/ElementObserver.h>
#include <OpenHome/Media/Debug.h>
//#include <OpenHome/Private/Timer.h>
//#include <OpenHome/Net/Private/Globals.h>

#include <algorithm>
#include <atomic>

using namespace OpenHome;
using namespace OpenHome::Media;

class FlywheelPlayableCreator : private IMsgProcessor
{
public:
    FlywheelPlayableCreator();
    MsgPlayable* CreatePlayable(Msg* aAudio);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override                 { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgTrack* aMsg) override                { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgDrain* aMsg) override                { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgDelay* aMsg) override                { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override        { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override         { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgMetaText* aMsg) override             { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override    { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgHalt* aMsg) override                 { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgFlush* aMsg) override                { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgWait* aMsg) override                 { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override        { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgBitRate* aMsg) override              { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override             { ASSERTS(); return aMsg; }
    Msg* ProcessMsg(MsgQuit* aMsg) override                 { ASSERTS(); return aMsg; }
private:
    MsgPlayable* iPlayable;
};


FlywheelPlayableCreator::FlywheelPlayableCreator()
    : iPlayable(nullptr)
{
}

MsgPlayable* FlywheelPlayableCreator::CreatePlayable(Msg* aAudio)
{
    iPlayable = nullptr;
    (void)aAudio->Process(*this);
    return iPlayable;
}

Msg* FlywheelPlayableCreator::ProcessMsg(MsgAudioPcm* aMsg)
{
    aMsg->ClearRamp();
    iPlayable = aMsg->CreatePlayable();
    return nullptr;
}

Msg* FlywheelPlayableCreator::ProcessMsg(MsgSilence* aMsg)
{
    aMsg->ClearRamp();
    iPlayable = aMsg->CreatePlayable();
    return nullptr;
}


// FlywheelInput

FlywheelInput::FlywheelInput(TUint aMaxJiffies)
{
    const TUint minJiffiesPerSample = Jiffies::PerSample(kMaxSampleRate);
    const TUint numSamples = (aMaxJiffies + minJiffiesPerSample - 1) / minJiffiesPerSample;
    const TUint channelBytes = numSamples * kSubsampleBytes;
    const TUint bytes = channelBytes * kMaxChannels;
    iPtr = new TByte[bytes];
}

FlywheelInput::~FlywheelInput()
{
    delete[] iPtr;
}

const Brx& FlywheelInput::Prepare(MsgQueue& aQueue, TUint aJiffies, TUint aSampleRate, TUint /*aBitDepth*/, TUint aNumChannels)
{
    ASSERT(aNumChannels < kMaxChannels);
    const TUint numSamples = aJiffies / Jiffies::PerSample(aSampleRate);
    const TUint channelBytes = numSamples * kSubsampleBytes;
    TByte* p = iPtr;
    for (TUint i=0; i<aNumChannels; i++) {
        iChannelPtr[i] = p;
        p += channelBytes;
    }

    FlywheelPlayableCreator playableCreator;
    while (!aQueue.IsEmpty()) {
        MsgPlayable* playable = playableCreator.CreatePlayable(aQueue.Dequeue());
        playable->Read(*this);
        playable->RemoveRef();
    }

    const TUint bytes = channelBytes * aNumChannels;
    iBuf.Set(iPtr, bytes);
    return iBuf;
}

void FlywheelInput::BeginBlock()
{
}

inline void FlywheelInput::AppendSubsample8(TByte*& aDest, const TByte*& aSrc)
{
    *aDest++ = *aSrc++;
    *aDest++ = 0;
    *aDest++ = 0;
    *aDest++ = 0;
}

inline void FlywheelInput::AppendSubsample16(TByte*& aDest, const TByte*& aSrc)
{
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
    *aDest++ = 0;
    *aDest++ = 0;
}

inline void FlywheelInput::AppendSubsample24(TByte*& aDest, const TByte*& aSrc)
{
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
    *aDest++ = 0;
}

inline void FlywheelInput::AppendSubsample32(TByte*& aDest, const TByte*& aSrc)
{
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
    *aDest++ = *aSrc++;
}

void FlywheelInput::ProcessFragment8(const Brx& aData, TUint aNumChannels)
{
    const TByte* src = aData.Ptr();
    const TUint numSamples = aData.Bytes() / aNumChannels;
    for (TUint i=0; i<numSamples; i++) {
        for (TUint j=0; j<aNumChannels; j++) {
            AppendSubsample8(iChannelPtr[j], src);
        }
    }
}

void FlywheelInput::ProcessFragment16(const Brx& aData, TUint aNumChannels)
{
    const TByte* src = aData.Ptr();
    const TUint numSubsamples = aData.Bytes() / 2;
    const TUint numSamples = numSubsamples / aNumChannels;
    for (TUint i=0; i<numSamples; i++) {
        for (TUint j=0; j<aNumChannels; j++) {
            AppendSubsample16(iChannelPtr[j], src);
        }
    }
}

void FlywheelInput::ProcessFragment24(const Brx& aData, TUint aNumChannels)
{
    const TByte* src = aData.Ptr();
    const TUint numSubsamples = aData.Bytes() / 3;
    const TUint numSamples = numSubsamples / aNumChannels;
    for (TUint i=0; i<numSamples; i++) {
        for (TUint j=0; j<aNumChannels; j++) {
            AppendSubsample24(iChannelPtr[j], src);
        }
    }
}

void FlywheelInput::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    const TByte* src = aData.Ptr();
    const TUint numSubsamples = aData.Bytes() / 4;
    const TUint numSamples = numSubsamples / aNumChannels;
    for (TUint i=0; i<numSamples; i++) {
        for (TUint j=0; j<aNumChannels; j++) {
            AppendSubsample32(iChannelPtr[j], src);
        }
    }
}

void FlywheelInput::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    for (TUint j=0; j<aNumChannels; j++) {
        AppendSubsample8(iChannelPtr[j], aSample);
    }
}

void FlywheelInput::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    for (TUint j=0; j<aNumChannels; j++) {
        AppendSubsample16(iChannelPtr[j], aSample);
    }
}

void FlywheelInput::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    for (TUint j=0; j<aNumChannels; j++) {
        AppendSubsample24(iChannelPtr[j], aSample);
    }
}

void FlywheelInput::ProcessSample32(const TByte* aSample, TUint aNumChannels)
{
    for (TUint j=0; j<aNumChannels; j++) {
        AppendSubsample32(iChannelPtr[j], aSample);
    }
}

void FlywheelInput::EndBlock()
{
}

void FlywheelInput::Flush()
{
}


// RampGenerator

RampGenerator::RampGenerator(MsgFactory& aMsgFactory, TUint aInputJiffies, TUint aRampJiffies, TUint aThreadPriority)
    : iMsgFactory(aMsgFactory)
    , iRampJiffies(aRampJiffies)
    , iSem("FWRG", 0)
    , iRecentAudio(nullptr)
    , iSampleRate(0)
    , iNumChannels(0)
    , iCurrentRampValue(Ramp::kMax)
    , iRemainingRampSize(0)
{
    ASSERT(iActive.is_lock_free());
    iActive.store(false);

    iFlywheelRamper = new FlywheelRamperManager(*this, aInputJiffies, aRampJiffies);

    const TUint minJiffiesPerSample = Jiffies::PerSample(kMaxSampleRate);
    const TUint numSamples = (FlywheelRamperManager::kMaxOutputJiffiesBlockSize + minJiffiesPerSample - 1) / minJiffiesPerSample;
    const TUint channelBytes = numSamples * kSubsampleBytes;
    const TUint bytes = channelBytes * kMaxChannels;
    iFlywheelAudio = new Bwh(bytes);

    iThread = new ThreadFunctor("FlywheelRamper",
                                MakeFunctor(*this, &RampGenerator::FlywheelRamperThread),
                                aThreadPriority);
    iThread->Start();
}

RampGenerator::~RampGenerator()
{
    ASSERT(iQueue.IsEmpty());
    delete iThread;
    delete iFlywheelAudio;
    delete iFlywheelRamper;
}

void RampGenerator::Start(const Brx& aRecentAudio, TUint aSampleRate, TUint aNumChannels, TUint aCurrentRampValue)
{
    iRecentAudio = &aRecentAudio;
    iSampleRate = aSampleRate;
    iNumChannels = aNumChannels;
    iCurrentRampValue = aCurrentRampValue;
    iRemainingRampSize = iRampJiffies;
    (void)iSem.Clear();
    iActive.store(true);
    iThread->Signal();
}

TBool RampGenerator::TryGetAudio(Msg*& aMsg)
{
    if (!iActive.load() && iQueue.IsEmpty()) {
        return false;
    }
    iSem.Wait();
    if (!iActive.load() && iQueue.IsEmpty()) {
        return false;
    }
    aMsg = iQueue.Dequeue();
    return true;
}

void RampGenerator::FlywheelRamperThread()
{
    try {
        for (;;) {
            iThread->Wait();
            iFlywheelRamper->Ramp(*iRecentAudio, iSampleRate, iNumChannels);
            iActive.store(false);
            iSem.Signal();
        }
    }
    catch (ThreadKill&) {
    }
}

void RampGenerator::BeginBlock()
{
    iFlywheelAudio->SetBytes(0);
}

void RampGenerator::ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessFragment32(const Brx& aData, TUint /*aNumChannels*/)
{
    iFlywheelAudio->Append(aData);
    //Log::Print("++ RampGenerator::ProcessFragment32 numSamples=%u\n", aData.Bytes() / 8);
#if 0
    if (aNumChannels == 2) {
        const TByte* p = aData.Ptr();
        static const TUint stride = 8;
        const TUint samples = aData.Bytes() / stride;
        ASSERT(aData.Bytes() % stride == 0);
        for (TUint i=0; i<samples; i++) {
            TByte b[stride];
            for (TUint j=0; j<stride; j++) {
                b[j] = *p++;
            }
            Log::Print("  %02x%02x%02x%02x  %02x%02x%02x%02x\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
        }
    }
#endif
}

void RampGenerator::ProcessSample8(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessSample16(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessSample24(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::ProcessSample32(const TByte* /*aSample*/, TUint /*aNumChannels*/)
{
    // FlywheelRamper outputs 32-bit fragments only
    ASSERTS();
}

void RampGenerator::EndBlock()
{
    auto audio = iMsgFactory.CreateMsgAudioPcm(*iFlywheelAudio, iNumChannels, iSampleRate, 32, AudioDataEndian::Big, MsgAudioPcm::kTrackOffsetInvalid);
    if (iCurrentRampValue == Ramp::kMin) {
        audio->SetMuted();
    }
    else {
        MsgAudio* split;
        iCurrentRampValue = audio->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EDown, split);
        ASSERT(split == nullptr);
    }
    iQueue.Enqueue(audio);
    iSem.Signal();
}

void RampGenerator::Flush()
{
    ASSERTS();
}


// StarvationRamper

const TUint StarvationRamper::kTrainingJiffies    = Jiffies::kPerMs * 1;
const TUint StarvationRamper::kRampDownJiffies    = Jiffies::kPerMs * 20;
const TUint StarvationRamper::kMaxAudioOutJiffies = Jiffies::kPerMs * 5;

StarvationRamper::StarvationRamper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream,
                                   IStarvationMonitorObserver& aObserver,
                                   IPipelineElementObserverThread& aObserverThread, TUint aSizeJiffies,
                                   TUint aThreadPriority, TUint aRampUpSize, TUint aMaxStreamCount)
    : iMsgFactory(aMsgFactory)
    , iUpstream(aUpstream)
    , iObserver(aObserver)
    , iObserverThread(aObserverThread)
    , iSizeJiffies(aSizeJiffies)
    , iRampUpJiffies(aRampUpSize)
    , iMaxStreamCount(aMaxStreamCount)
    , iLock("SRM1")
    , iSem("SRM2", 0)
    , iFlywheelInput(kTrainingJiffies)
    , iRecentAudioJiffies(0)
    , iStreamHandler(nullptr)
    , iState(State::Halted)
    , iStarving(false)
    , iExit(false)
    , iStreamId(IPipelineIdProvider::kStreamIdInvalid)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iCurrentRampValue(Ramp::kMin)
    , iRemainingRampSize(0)
    , iLastPulledAudioRampValue(Ramp::kMax)
    , iLastEventBuffering(false)
{
    ASSERT(iEventBuffering.is_lock_free());
    iEventId = iObserverThread.Register(MakeFunctor(*this, &StarvationRamper::EventCallback));
    iEventBuffering.store(false); // ensure SetBuffering call below detects a state change
    SetBuffering(true);

    iRampGenerator = new RampGenerator(aMsgFactory, kTrainingJiffies, kRampDownJiffies, aThreadPriority);
    iPullerThread = new ThreadFunctor("StarvationRamper",
                                      MakeFunctor(*this, &StarvationRamper::PullerThread),
                                      aThreadPriority-1);
    iPullerThread->Start();
}

StarvationRamper::~StarvationRamper()
{
    delete iPullerThread;
    delete iRampGenerator;
}

inline TBool StarvationRamper::IsFull() const
{
    return (Jiffies() >= iSizeJiffies || DecodedStreamCount() == iMaxStreamCount);
}

void StarvationRamper::PullerThread()
{
    do {
        Msg* msg = iUpstream.Pull();
        iLock.Wait();
        DoEnqueue(msg);
        TBool isFull = IsFull();
        if (isFull) {
            iSem.Clear();
        }
        iLock.Signal();
        if (isFull) {
            iSem.Wait();
        }
    } while (!iExit);
}

void StarvationRamper::StartFlywheelRamp()
{
//    const TUint startTime = Time::Now(*gEnv);
    if (iRecentAudioJiffies > kTrainingJiffies) {
        TUint excess = iRecentAudioJiffies - kTrainingJiffies;
        while (excess > 0) {
            MsgAudio* audio = static_cast<MsgAudio*>(iRecentAudio.Dequeue());
            if (audio->Jiffies() > excess) {
                MsgAudio* remaining = audio->Split(excess);
                iRecentAudio.EnqueueAtHead(remaining);
            }
            const TUint msgJiffies = audio->Jiffies();
            excess -= msgJiffies;
            iRecentAudioJiffies -= msgJiffies;
            audio->RemoveRef();
        }
    }
    else {
        TInt remaining = kTrainingJiffies - iRecentAudioJiffies;
        while (remaining > 0) {
            TUint size = std::min((TUint)remaining, kMaxAudioOutJiffies);
            auto silence = iMsgFactory.CreateMsgSilence(size, iSampleRate, iBitDepth, iNumChannels);
            iRecentAudio.EnqueueAtHead(silence);
            remaining -= size;
            iRecentAudioJiffies += size;
        }
    }

    const Brx& recentSamples = iFlywheelInput.Prepare(iRecentAudio, iRecentAudioJiffies, iSampleRate, iBitDepth, iNumChannels);
//    const TUint prepEnd = Time::Now(*gEnv);
    iRecentAudioJiffies = 0;

    TUint rampStart = iCurrentRampValue;
    /*if (rampStart == Ramp::kMax) {
        rampStart = iLastPulledAudioRampValue;
    }*/
    LOG(kPipeline, "StarvationRamper::StartFlywheelRamp rampStart=%08x\n", rampStart);
    iRampGenerator->Start(recentSamples, iSampleRate, iNumChannels, rampStart);
//    const TUint flywheelEnd = Time::Now(*gEnv);
    iState = State::RampingDown;
//    Log::Print("StarvationRamper::StartFlywheelRamp rampStart=%08x, prepTime=%ums, flywheelTime=%ums\n", rampStart, prepEnd - startTime, flywheelEnd - prepEnd);
}

void StarvationRamper::NewStream()
{
    iState = State::Starting;
    iRecentAudio.Clear();
    iRecentAudioJiffies = 0;
    iStreamId = IPipelineIdProvider::kStreamIdInvalid;
    iLastPulledAudioRampValue = Ramp::kMax;
}

void StarvationRamper::ProcessAudioOut(MsgAudio* aMsg)
{
    if (iStarving) {
        iStarving = false;
        iStreamHandler->NotifyStarving(iMode, iStreamId, false);
    }

    if (aMsg->Jiffies() > kMaxAudioOutJiffies) {
        Msg* split = aMsg->Split(kMaxAudioOutJiffies);
        EnqueueAtHead(split);
    }

    iLastPulledAudioRampValue = aMsg->Ramp().End();

    iRecentAudio.Enqueue(aMsg);
    aMsg->AddRef();
    iRecentAudioJiffies += aMsg->Jiffies();
    if (iRecentAudioJiffies >= kTrainingJiffies) {
        MsgAudio* msg = static_cast<MsgAudio*>(iRecentAudio.Dequeue());
        iRecentAudioJiffies -= msg->Jiffies();
        if (iRecentAudioJiffies >= kTrainingJiffies) {
            msg->RemoveRef();
        }
        else {
            iRecentAudio.EnqueueAtHead(msg);
            iRecentAudioJiffies += msg->Jiffies();
        }
    }
}

void StarvationRamper::SetBuffering(TBool aBuffering)
{
    const TBool prev = iEventBuffering.exchange(aBuffering);
    if (prev != aBuffering) {
        iObserverThread.Schedule(iEventId);
    }
}

void StarvationRamper::EventCallback()
{
    const TBool buffering = iEventBuffering.load();
    if (buffering != iLastEventBuffering) {
        iObserver.NotifyStarvationMonitorBuffering(buffering);
        iLastEventBuffering = buffering;
    }
}

Msg* StarvationRamper::Pull()
{
    if (IsEmpty()) {
        SetBuffering(true);
        if (   (iState == State::Running ||
               (iState == State::RampingUp && iCurrentRampValue != Ramp::kMin))
            && !iExit) {
            StartFlywheelRamp();
            iStarving = true;
            iStreamHandler->NotifyStarving(iMode, iStreamId, true);
        }
    }

    Msg* msg = nullptr;
    if (iRampGenerator->TryGetAudio(msg)) {
        return msg;
    }
    else if (iState == State::RampingDown) {
        iState = State::RampingUp;
        iCurrentRampValue = Ramp::kMin;
        iRemainingRampSize = iRampUpJiffies;
        return iMsgFactory.CreateMsgHalt();
    }

    msg = DoDequeue();
    iLock.Wait();
    if (!IsFull()) {
        iSem.Signal();
    }
    iLock.Signal();
    return msg;
}

void StarvationRamper::ProcessMsgIn(MsgMode* /*aMsg*/)
{
    NewStream();
}

void StarvationRamper::ProcessMsgIn(MsgTrack* /*aMsg*/)
{
    NewStream();
}

void StarvationRamper::ProcessMsgIn(MsgHalt* /*aMsg*/)
{
    iState = State::Halted;
}

void StarvationRamper::ProcessMsgIn(MsgDecodedStream* aMsg)
{
    NewStream();

    auto streamInfo = aMsg->StreamInfo();
    iStreamId = streamInfo.StreamId();
    iStreamHandler = streamInfo.StreamHandler();
    iSampleRate = streamInfo.SampleRate();
    iBitDepth = streamInfo.BitDepth();
    iNumChannels = streamInfo.NumChannels();
}

void StarvationRamper::ProcessMsgIn(MsgAudioPcm* /*aMsg*/)
{
    if (iState == State::Starting || iState == State::Halted) {
        iState = State::Running;
    }
}

void StarvationRamper::ProcessMsgIn(MsgSilence* /*aMsg*/)
{
    if (iState == State::Halted) {
        iState = State::Starting;
    }
}

void StarvationRamper::ProcessMsgIn(MsgQuit* /*aMsg*/)
{
    iExit = true;
}

Msg* StarvationRamper::ProcessMsgOut(MsgMode* aMsg)
{
    iMode.Replace(aMsg->Mode());
    return aMsg;
}

Msg* StarvationRamper::ProcessMsgOut(MsgHalt* aMsg)
{
    // set Halted state on both entry and exit of this msg
    // ...on entry to avoid us starting a ramp down before outputting a Halt
    // ...on exit in case Halted state from entry was reset by outputting Audio
    iState = State::Halted;
    return aMsg;
}

Msg* StarvationRamper::ProcessMsgOut(MsgDecodedStream* aMsg)
{
    iCurrentRampValue = Ramp::kMax;
    return aMsg;
}

Msg* StarvationRamper::ProcessMsgOut(MsgAudioPcm* aMsg)
{
    ProcessAudioOut(aMsg);
    SetBuffering(false);

    if (iState == State::RampingUp && iRemainingRampSize > 0) {
        if (aMsg->Jiffies() > iRemainingRampSize) {
            MsgAudio* remaining = aMsg->Split(iRemainingRampSize);
            EnqueueAtHead(remaining);
        }
        MsgAudio* split;
        iCurrentRampValue = aMsg->SetRamp(iCurrentRampValue, iRemainingRampSize, Ramp::EUp, split);
        if (split != nullptr) {
            EnqueueAtHead(split);
        }
        if (iRemainingRampSize == 0) {
            iState = State::Running;
        }
    }

    return aMsg;
}

Msg* StarvationRamper::ProcessMsgOut(MsgSilence* aMsg)
{
    ProcessAudioOut(aMsg);
    return aMsg;
}
