#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class DecodedAudioReservoir : public AudioReservoir, private IStreamHandler
{
    friend class SuiteReservoirHistory;
public:
    DecodedAudioReservoir(MsgFactory& aMsgFactory, TUint aMaxSize, TUint aMaxStreamCount);
    TUint SizeInJiffies() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgMode* aMsg) override;
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgDrain* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    void ProcessMsgIn(MsgAudioPcm* aMsg) override;
    void ProcessMsgIn(MsgSilence* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
private: // from AudioReservoir
    TBool IsFull() const override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    Mutex iLock;
    const TUint iMaxJiffies;
    const TUint iMaxStreamCount;
    IClockPuller* iClockPuller;
    IStreamHandler* iStreamHandler;
};

} // namespace Media
} // namespace OpenHome

