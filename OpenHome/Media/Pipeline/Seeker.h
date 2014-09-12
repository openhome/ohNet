#ifndef HEADER_PIPELINE_SEEKER
#define HEADER_PIPELINE_SEEKER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    Seeker(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, ISeeker& aSeeker, TUint aRampDuration);
    virtual ~Seeker();
    TBool Seek(TUint aTrackId, TUint aStreamId, TUint aSecondsAbsolute, TBool aRampDown);
public: // from IPipelineElementUpstream
    Msg* Pull();
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
private: // from ISeekObserver
    void NotifySeekComplete(TUint aHandle, TUint aFlushId);
private:
    void DoSeek();
    Msg* ProcessFlushable(Msg* aMsg);
    Msg* ProcessAudio(MsgAudio* aMsg);
    void NewStream();
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
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    ISeeker& iSeeker;
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
    TUint iTrackId;
    TUint iStreamId;
    TBool iStreamIsSeekable;
    TUint64 iStreamPosJiffies;
    TUint64 iFlushEndJiffies;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SEEKER
