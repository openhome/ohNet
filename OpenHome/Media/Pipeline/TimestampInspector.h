#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class IClockPuller;

class TimestampInspector : public PipelineElement, public IPipelineElementDownstream, private INonCopyable
{
    static const TInt kLockingMaxDeviation = Jiffies::kPerMs / 2;
    static const TUint kLockingMsgCount = 4;
    static const TUint kSupportedMsgTypes;
    friend class SuiteTimestampInspector;
public:
    TimestampInspector(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    ~TimestampInspector();
private:
    void StreamInterrupted();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    MsgFactory& iMsgFactory;
    IPipelineElementDownstream& iDownstreamElement;
    IClockPuller* iClockPuller;
    MsgDecodedStream* iDecodedStream;
    TBool iCheckForTimestamp;
    TBool iStreamIsTimestamped;
    TBool iLockedToStream;
    TBool iCalculateTimestampDelta;
    TUint iLockingMaxDeviation;
    TUint iMsgsTillLock;
    TInt iTimestampDelta;
    TUint64 iDiscardedJiffies;
};

} // namespace Media
} // namespace OpenHome

