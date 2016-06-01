#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Media {

class IRewinder
{
public:
    virtual void Rewind() = 0;
    virtual void Stop() = 0;
};

class RewinderReservoir;

/* Class which buffers data for recognition (in case seeking back to the start
   of the data is required due to a failed recognition that pulls on the
   stream).
   Starts buffering data when a MsgEncodedStream is received, and continues
   buffering until TryStop is called or a new MsgEncodedStream is received
   (i.e., the entire stream was pulled before being recognised).
   If a seek (back to start) is received, Rewinder starts passing msgs from
   start of its FIFO.
*/

class Rewinder : public IPipelineElementUpstream, private IMsgProcessor, public IRewinder, private IStreamHandler, private INonCopyable
{
public:
    static const TUint kMaxEncodedAudioMsgs = 50; // allows ~400k of data for content recognition
                                                  // hard-coded on assumption that only buggy codecs would demand more
public:
    Rewinder(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement);
    ~Rewinder();
private:
    void TryBuffer(Msg* aMsg);
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgTrack* aMsg) override;
    Msg* ProcessMsg(MsgDrain* aMsg) override;
    Msg* ProcessMsg(MsgDelay* aMsg) override;
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
    Msg* ProcessMsg(MsgStreamInterrupted* aMsg) override;
    Msg* ProcessMsg(MsgMetaText* aMsg) override;
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgFlush* aMsg) override;
    Msg* ProcessMsg(MsgWait* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsg(MsgBitRate* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
    Msg* ProcessMsg(MsgPlayable* aMsg) override;
    Msg* ProcessMsg(MsgQuit* aMsg) override;
public: // from IRewinder
    void Rewind() override;
    void Stop() override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IStreamHandler* iStreamHandler;
    TBool iBuffering;
    Mutex iLock;
    RewinderReservoir* iQueueCurrent;    // new Msgs still to be passed on
    RewinderReservoir* iQueueNext;       // Msgs passed on but buffered in case of rewind
};

} // namespace Media
} // namespace OpenHome

