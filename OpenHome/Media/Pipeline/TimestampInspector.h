#ifndef HEADER_PIPELINE_TIMESTAMP_INSPECTOR
#define HEADER_PIPELINE_TIMESTAMP_INSPECTOR

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

class IClockPuller;

class TimestampInspector : public IPipelineElementDownstream, private IMsgProcessor, private INonCopyable
{
    static const TInt kLockingMaxDeviation = Jiffies::kPerMs / 2;
    static const TUint kLockingMsgCount = 4;
    friend class SuiteTimestampInspector;
public:
    TimestampInspector(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    ~TimestampInspector();
private:
    void NewSession();
    void StreamInterrupted();
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgSession* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
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

#endif // HEADER_PIPELINE_TIMESTAMP_INSPECTOR
