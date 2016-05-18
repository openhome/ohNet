#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class DecodedAudioReservoir : public AudioReservoir, private IClockPullerReservoir
{
    friend class SuiteReservoirHistory;
public:
    DecodedAudioReservoir(MsgFactory& aMsgFactory, TUint aMaxSize, TUint aMaxStreamCount);
    TUint SizeInJiffies() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    void ProcessMsgIn(MsgAudioPcm* aMsg) override;
    void ProcessMsgIn(MsgSilence* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgDrain* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
private: // from AudioReservoir
    TBool IsFull() const override;
private: // from IClockPullerReservoir
    void Start(TUint aExpectedDecodedReservoirJiffies) override;
    void Stop() override;
    void Reset() override;
    void NotifySize(TUint aJiffies) override;
private:
    MsgFactory& iMsgFactory;
    Mutex iLockClockPuller;
    IClockPullerReservoir* iClockPuller;
    const TUint iMaxJiffies;
    const TUint iMaxStreamCount;
    TBool iClockPullerStarted;
};

} // namespace Media
} // namespace OpenHome

