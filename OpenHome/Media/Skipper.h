#ifndef HEADER_PIPELINE_SKIPPER
#define HEADER_PIPELINE_SKIPPER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which skips to the end of a track
If the track is playing when *RemoveStream() is called, it is first ramped down
...followed by calling IStreamHandler::TryStop to attempt to stop delivery of the current stream
...followed by pulling/discarding all remaining content for that stream
If the pipeline is paused when *RemoveStream() is called, we move straight to pulling/discarding
If TryStop returned a valid flush id, the MsgFlush with this id is consumed
*/

class Skipper : public IPipelineElementUpstream, private IMsgProcessor
{
    friend class SuiteSkipper;
public:
    Skipper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration);
    virtual ~Skipper();
    void RemoveCurrentStream(TBool aRampDown);
    TBool TryRemoveStream(TUint aTrackId, TUint aStreamId, TBool aRampDown);
public: // from IPipelineElementUpstream
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    TBool TryRemoveCurrentStream(TBool aRampDown);
    void StartFlushing(TBool aSendHalt);
    Msg* ProcessFlushable(Msg* aMsg);
    Msg* ProcessAudio(MsgAudio* aMsg);
    void NewStream();
private:
    enum EState
    {
        ERunning
       ,ERamping
       ,EFlushing
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    Mutex iLock;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iTargetFlushId;
    TUint iTrackId;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_SKIPPER
