#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class IClockPuller;

class DecodedAudioReservoir : public AudioReservoir
{
    friend class SuiteReservoirHistory;
public:
    DecodedAudioReservoir(TUint aMaxSize, TUint aMaxStreamCount);
    TUint SizeInJiffies() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    void ProcessMsgIn(MsgAudioPcm* aMsg) override;
    void ProcessMsgIn(MsgSilence* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgDrain* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsgOut(MsgSilence* aMsg) override;
private: // from AudioReservoir
    TBool IsFull() const override;
private:
    void DoProcessMsgIn();
    Msg* DoProcessMsgOut(MsgAudio* aMsg);
private:
    static const TUint kUtilisationSamplePeriodJiffies = Jiffies::kPerSecond / 10;
    IClockPullerReservoir* iClockPuller;
    Mutex iLock;
    const TUint iMaxJiffies;
    const TUint iMaxStreamCount;
    TUint64 iJiffiesUntilNextUsageReport;
    Thread* iThreadExcludeBlock;
};

} // namespace Media
} // namespace OpenHome

