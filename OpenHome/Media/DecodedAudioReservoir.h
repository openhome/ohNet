#ifndef HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/AudioReservoir.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class IClockPuller;

class DecodedAudioReservoir : public AudioReservoir
{
    friend class SuiteReservoirHistory;
public:
    DecodedAudioReservoir(TUint aMaxSize, IClockPuller& aClockPuller);
    TUint SizeInJiffies() const;
private: // from MsgReservoir
    void ProcessMsgIn(MsgAudioPcm* aMsg);
    void ProcessMsgIn(MsgSilence* aMsg);
    Msg* ProcessMsgOut(MsgTrack* aMsg);
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private: // from AudioReservoir
    TUint Size() const;
private:
    void DoProcessMsgIn();
    Msg* DoProcessMsgOut(MsgAudio* aMsg);
private:
    static const TUint kUtilisationSamplePeriodJiffies = Jiffies::kPerSecond;
    IClockPuller& iClockPuller;
    Mutex iLock;
    TUint64 iJiffiesUntilNextUsageReport;
    Thread* iThreadExcludeBlock;
    TBool iTrackIsPullable;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
