#ifndef HEADER_PIPELINE_REWINDER
#define HEADER_PIPELINE_REWINDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Private/Fifo.h>

namespace OpenHome {
namespace Media {

/* Class which buffers data for recognition (in case seeking back to the start
   of the data is required due to a failed recognition that pulls on the
   stream).
   Starts buffering data when a MsgEncodedStream is received, and continues
   buffering until TryStop is called or a new MsgEncodedStream is received
   (i.e., the entire stream was pulled before being recognised).
   If a seek (back to start) is received, Rewinder starts passing msgs from
   start of its FIFO.
*/

class Rewinder : public IPipelineElementUpstream, private IMsgProcessor, private IStreamHandler, private INonCopyable
{
public:
    Rewinder(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aSlots);
    ~Rewinder();
private:
    MsgAudioEncoded* GetAudioFromCurrent();
    static void DrainFifo(Fifo<MsgAudioEncoded*>& aFifo);
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
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    IStreamHandler* iStreamHandler;
    TBool iBuffering;
    Fifo<MsgAudioEncoded*>* iFifoCurrent;    // new Msgs still to be passed on
    Fifo<MsgAudioEncoded*>* iFifoNext;       // Msgs passed on but buffered in case of rewind
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_REWINDER
