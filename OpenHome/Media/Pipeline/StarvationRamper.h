#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>

#include <cstdint>
#include <atomic>

namespace OpenHome {
namespace Media {

class IStarvationRamperObserver
{
public:
    virtual void NotifyStarvationRamperBuffering(TBool aBuffering) = 0;
};

class FlywheelInput : public IPcmProcessor
{
    static const TUint kMaxSampleRate = 192000;
    static const TUint kMaxChannels = 8;
    static const TUint kSubsampleBytes = 4;
public:
    FlywheelInput(TUint aMaxJiffies);
    ~FlywheelInput();
    const Brx& Prepare(MsgQueueLite& aQueue, TUint aJiffies, TUint aSampleRate, TUint aBitDepth, TUint aNumChannels);
private:
    inline static void AppendSubsample8(TByte*& aDest, const TByte*& aSrc);
    inline static void AppendSubsample16(TByte*& aDest, const TByte*& aSrc);
    inline static void AppendSubsample24(TByte*& aDest, const TByte*& aSrc);
    inline static void AppendSubsample32(TByte*& aDest, const TByte*& aSrc);
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample32(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
    void Flush() override;
private:
    TByte* iPtr;
    Brn iBuf;
    TByte* iChannelPtr[kMaxChannels];
};

class FlywheelRamperManager;

class RampGenerator : public IPcmProcessor
{
    static const TUint kMaxSampleRate = 192000; // FIXME - duplicated in FlywheelInput
    static const TUint kMaxChannels = 8;
    static const TUint kSubsampleBytes = 4;
public:
    RampGenerator(MsgFactory& iMsgFactory, TUint aInputJiffies, TUint aRampJiffies, TUint aThreadPriority);
    ~RampGenerator();
    void Start(const Brx& aRecentAudio, TUint aSampleRate, TUint aNumChannels, TUint aCurrentRampValue);
    TBool TryGetAudio(Msg*& aMsg); // returns false / nullptr when all msgs generated & returned
private:
    void FlywheelRamperThread();
private: // from IPcmProcessor
    void BeginBlock() override;
    void ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessFragment32(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample32(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
    void Flush() override;
private:
    MsgFactory& iMsgFactory;
    const TUint iRampJiffies;
    Semaphore iSem;
    FlywheelRamperManager* iFlywheelRamper;
    Thread* iThread;
    Bwh* iFlywheelAudio;
    MsgQueue iQueue;
    const Brx* iRecentAudio;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    std::atomic<bool> iActive;
};

class IStarvationMonitorObserver;
class IPipelineElementObserverThread;

class StarvationRamper : public MsgReservoir, public IPipelineElementUpstream
{
    friend class SuiteStarvationRamper;
    static const TUint kTrainingJiffies;
    static const TUint kRampDownJiffies;
    static const TUint kMaxAudioOutJiffies;
public:
    StarvationRamper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream,
                     IStarvationRamperObserver& aObserver,
                     IPipelineElementObserverThread& aObserverThread, TUint aSizeJiffies,
                     TUint aThreadPriority, TUint aRampUpSize, TUint aMaxStreamCount);
    ~StarvationRamper();
    TUint SizeInJiffies() const;
private:
    inline TBool IsFull() const;
    void PullerThread();
    void StartFlywheelRamp();
    void NewStream();
    void ProcessAudioOut(MsgAudio* aMsg);
    void SetBuffering(TBool aBuffering);
    void EventCallback();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from MsgReservoir
    void ProcessMsgIn(MsgDelay* aMsg) override;
    void ProcessMsgIn(MsgQuit* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgTrack* aMsg) override;
    Msg* ProcessMsgOut(MsgDelay* aMsg) override;
    Msg* ProcessMsgOut(MsgHalt* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsgOut(MsgSilence* aMsg) override;
private:
    enum class State {
        Starting,
        Running,
        Halted,
        RampingUp,
        RampingDown
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstream;
    IStarvationRamperObserver& iObserver;
    IPipelineElementObserverThread& iObserverThread;
    TUint iMaxJiffies;
    const TUint iRampUpJiffies;
    const TUint iMaxStreamCount;
    Mutex iLock;
    Semaphore iSem;
    FlywheelInput iFlywheelInput;
    RampGenerator* iRampGenerator;
    ThreadFunctor* iPullerThread;
    MsgQueueLite iRecentAudio;
    TUint iRecentAudioJiffies;
    IStreamHandler* iStreamHandler;
    State iState;
    TBool iRunning;
    TBool iStarving;
    TBool iExit;
    BwsMode iMode;
    TUint iStreamId;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    TUint iLastPulledAudioRampValue;
    TUint iEventId;
    std::atomic<bool> iEventBuffering;
    TBool iLastEventBuffering;
};

} //namespace Media
} // namespace OpenHome
