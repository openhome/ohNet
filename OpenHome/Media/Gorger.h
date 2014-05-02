#ifndef HEADER_PIPELINE_GORGER
#define HEADER_PIPELINE_GORGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

/*
Element which reduces the chances of drop-outs by buffering audio
- When we first start playing audio of a new mode
- After a drop-out
- After an expected break in audio

Not all sources of audio are appropriate for this.
MsgMode's IsRealTime() identifies sources where it is not desirable to introduce extra delay at this stage of the pipeline.
*/

class Gorger : private MsgReservoir, public IPipelineElementUpstream, private IStreamHandler
{
    friend class SuiteGorger;
public:
    Gorger(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aGorgeSize);
    ~Gorger();
public: // from IPipelineElementUpstream
    Msg* Pull();
    void PullerThread();
    void Enqueue(Msg* aMsg);
private:
    void SetGorging(TBool aGorging);
private: // from MsgReservoir
    void ProcessMsgIn(MsgMode* aMsg);
    void ProcessMsgIn(MsgHalt* aMsg);
    void ProcessMsgIn(MsgQuit* aMsg);
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg);
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
    void NotifyStarving(const Brx& aMode, TUint aTrackId, TUint aStreamId);
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstreamElement;
    ThreadFunctor* iThread;
    TUint iGorgeSize;
    Mutex iLock;
    Semaphore iSemOut;
    IStreamHandler* iStreamHandler;
    TBool iCanGorge;
    TBool iGorging;
    TBool iQuit;
    BwsMode iMode;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_GORGER
