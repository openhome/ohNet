#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/Flusher.h>

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

class Skipper : public IPipelineElementUpstream, private IMsgProcessor, private IStreamHandler
{
    friend class SuiteSkipper;
public:
    Skipper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aRampDuration);
    virtual ~Skipper();
    void Block();
    void Unblock();
    void RemoveCurrentStream(TBool aRampDown);
    TBool TryRemoveStream(TUint aStreamId, TBool aRampDown);
    void RemoveAll(TUint aHaltId, TBool aRampDown);
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
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    inline TBool RemoveAllPending() const;
    TBool TryRemoveCurrentStream(TBool aRampDown);
    void StartFlushing(TBool aSendHalt);
    Msg* ProcessFlushable(Msg* aMsg);
    void NewStream();
private:
    enum EState
    {
        eRunning
       ,eStarting
       ,eRamping
       ,eFlushing
    };
private:
    Flusher iFlusher;
    MsgFactory& iMsgFactory;
    Mutex iLock;
    Mutex iBlocker;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TUint iTargetFlushId;
    TUint iTargetHaltId;
    TUint iStreamId;
    IStreamHandler* iStreamHandler;
    TBool iRunning;
};

} // namespace Media
} // namespace OpenHome

