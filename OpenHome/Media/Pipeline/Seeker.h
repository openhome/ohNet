#ifndef HEADER_PIPELINE_SEEKER
#define HEADER_PIPELINE_SEEKER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Flusher.h>

namespace OpenHome {
namespace Media {

/*
Element which facilitates seeking within a track
If the track is playing when Seek() is called, it is first ramped down
...once ramped down (or immediately if the pipeline is paused), ISeeker::TrySeek() is called
...if TrySeek returns an invalid flush id, the seek wasn't possible
...if TrySeek returns a valid flush id, data is pulled/discarded until we pull a flush with the target id
...the track is ramped up when we restart playing
Calls to Seek() are ignored if a previous seek is in progress
If TrySeek returned a valid flush id, the MsgFlush with this id is consumed
*/

class Seeker : public IPipelineElementUpstream, private IMsgProcessor, private ISeekObserver
{
    friend class SuiteSeeker;
public:
    Seeker(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISeeker& aSeeker, ISeekRestreamer& aRestreamer, TUint aRampDuration);
    virtual ~Seeker();
    TBool Seek(TUint aStreamId, TUint aSecondsAbsolute, TBool aRampDown);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from ISeekObserver
    void NotifySeekComplete(TUint aHandle, TUint aFlushId) override;
private:
    void DoSeek();
    Msg* ProcessFlushable(Msg* aMsg);
    void HandleSeekFail();
private:
    enum EState
    {
        ERunning
       ,ERampingDown
       ,ERampingUp
       ,EFlushing
    };
private:
    Flusher iFlusher;
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    ISeeker& iSeeker;
    ISeekRestreamer& iRestreamer;
    Mutex iLock;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    TUint iSampleRate;
    TUint iSeekSeconds;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iSeekHandle;
    TUint iTargetFlushId;
    BwsMode iMode;
    TUint iTrackId;
    TUint iStreamId;
    TBool iStreamIsSeekable;
    TUint64 iStreamPosJiffies;
    TUint64 iFlushEndJiffies;
    TUint iSeekConsecutiveFailureCount;
    MsgDecodedStream* iMsgStream;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SEEKER
