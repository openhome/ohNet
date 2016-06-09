#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/AudioReservoir.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Private/Thread.h>

#include <atomic>

namespace OpenHome {
namespace Media {

class DecodedAudioReservoir : public AudioReservoir, private IStreamHandler
{
    friend class SuiteGorger;
public:
    DecodedAudioReservoir(MsgFactory& aMsgFactory, IFlushIdProvider& aFlushIdProvider,
                          TUint aMaxSize, TUint aMaxStreamCount, TUint aGorgeSize);
    ~DecodedAudioReservoir();
    TUint SizeInJiffies() const;
private: // from AudioReservoir
    TBool IsFull() const override;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private:
    void SetGorging(TBool aGorging, const TChar* aId);
private: // from MsgReservoir
    void ProcessMsgIn(MsgMode* aMsg) override;
    void ProcessMsgIn(MsgTrack* aMsg) override;
    void ProcessMsgIn(MsgDrain* aMsg) override;
    void ProcessMsgIn(MsgEncodedStream* aMsg) override;
    void ProcessMsgIn(MsgHalt* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    void ProcessMsgIn(MsgAudioPcm* aMsg) override;
    void ProcessMsgIn(MsgSilence* aMsg) override;
    void ProcessMsgIn(MsgQuit* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgTrack* aMsg) override;
    Msg* ProcessMsgOut(MsgDrain* aMsg) override;
    Msg* ProcessMsgOut(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgHalt* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    IFlushIdProvider& iFlushIdProvider;
    Mutex iLock;
    const TUint iMaxJiffies;
    const TUint iMaxStreamCount;
    IClockPuller* iClockPuller;
    std::atomic<IStreamHandler*> iStreamHandler;
    MsgDecodedStream *iDecodedStream;
    TUint iDiscardJiffies;
    TUint iPostDiscardFlush;
    Mutex iGorgeLock;
    TUint iGorgeSize;
    Semaphore iSemOut;
    TBool iCanGorge;
    TBool iShouldGorge;
    TBool iStartOfMode;
    TBool iGorging;
    TUint iPriorityMsgCount;
    BwsMode iMode;
};

} // namespace Media
} // namespace OpenHome

