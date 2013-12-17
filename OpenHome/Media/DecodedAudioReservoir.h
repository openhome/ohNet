#ifndef HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
#define HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/AudioReservoir.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
namespace Media {

class DecodedAudioReservoir : public AudioReservoir
{
    friend class SuiteReservoirHistory;
public:
    DecodedAudioReservoir(TUint aMaxSize);
private: // from MsgQueueFlushable
    void ProcessMsgIn(MsgAudioPcm* aMsg);
    void ProcessMsgIn(MsgSilence* aMsg);
    Msg* ProcessMsgOut(MsgAudioPcm* aMsg);
    Msg* ProcessMsgOut(MsgSilence* aMsg);
private: // from AudioReservoir
    TUint Size() const;
private:
    void DoProcessMsgIn();
    Msg* DoProcessMsgOut(MsgAudio* aMsg);
private:
    static const TUint kMaxUtilisationSamplePoints = 20;
    static const TUint kUtilisationSamplePeriodJiffies = Jiffies::kJiffiesPerSecond;
    Mutex iLock;
    TUint64 iHistory[kMaxUtilisationSamplePoints]; // past avg reservoir sizes
    TUint iHistoryCount;
    TUint iHistoryNextIndex;
    TUint64 iJiffiesUntilNextHistoryPoint;
    Thread* iThreadExcludeBlock;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DECODED_AUDIO_RESERVOIR
