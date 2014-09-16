#ifndef HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR

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
    DecodedAudioReservoir(TUint aMaxSize, TUint aMaxSessionCount, TUint aMaxStreamCount);
    TUint SizeInJiffies() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgSession* aMsg);
    void ProcessMsgIn(MsgDecodedStream* aMsg);
    void ProcessMsgIn(MsgAudioPcm* aMsg);
    void ProcessMsgIn(MsgSilence* aMsg);
    Msg* ProcessMsgOut(MsgMode* aMsg);
    Msg* ProcessMsgOut(MsgTrack* aMsg);
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg);
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private: // from AudioReservoir
    TBool IsFull() const;
private:
    void DoProcessMsgIn();
    Msg* DoProcessMsgOut(MsgAudio* aMsg);
private:
    static const TUint kUtilisationSamplePeriodJiffies = Jiffies::kPerSecond / 10;
    IClockPuller* iClockPuller;
    Mutex iLock;
    const TUint iMaxJiffies;
    const TUint iMaxSessionCount;
    const TUint iMaxStreamCount;
    TUint64 iJiffiesUntilNextUsageReport;
    Thread* iThreadExcludeBlock;
    TUint iTrackId;
    TUint iStreamId;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
