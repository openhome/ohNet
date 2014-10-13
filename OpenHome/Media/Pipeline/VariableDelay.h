#ifndef HEADER_PIPELINE_VARIABLE_DELAY
#define HEADER_PIPELINE_VARIABLE_DELAY

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which introduces a delay (likely for lip syncing)
If the delay is increased, silence is introduced.
If the delay is decreased, audio (pulled from upstream) is discarded.
Before any change in delay is actioned, audio spends RampDuration ramping down.
After a delay is actioned, audio spends RampDuration ramping up.
FIXME - no handling of pause-resumes
*/
    
class VariableDelay : private MsgReservoir, public IPipelineElementUpstream, private IMsgProcessor, private IStreamHandler
{
    static const TUint kMaxMsgSilenceDuration = Jiffies::kPerMs * 5;
    friend class SuiteVariableDelay;
public:
    VariableDelay(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aDownstreamDelay, TUint aRampDuration);
    virtual ~VariableDelay();
public: // from IPipelineElementUpstream
    Msg* Pull();
private:
    MsgAudio* DoProcessAudioMsg(MsgAudio* aMsg);
    void RampMsg(MsgAudio* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aTrackId, TUint aStreamId, TUint64 aOffset, TUint aBytes);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private:
    enum EStatus
    {
        EStarting
       ,ERunning
       ,ERampingDown
       ,ERampedDown
       ,ERampingUp
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    TUint iDelayJiffies;
    Mutex iLock;
    TInt iDelayAdjustment;
    EStatus iStatus;
    Ramp::EDirection iRampDirection;
    const TUint iDownstreamDelay;
    const TUint iRampDuration;
    TBool iEnabled;
    TBool iInStream;
    TBool iWaitForAudioBeforeGeneratingSilence;
    TUint iCurrentRampValue;
    TUint iRemainingRampSize;
    BwsMode iMode;
    IStreamHandler* iStreamHandler;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_VARIABLE_DELAY
