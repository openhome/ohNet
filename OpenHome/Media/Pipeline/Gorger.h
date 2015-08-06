#ifndef HEADER_PIPELINE_GORGER
#define HEADER_PIPELINE_GORGER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    Gorger(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aThreadPriority, TUint aGorgeSize);
    ~Gorger();
    TUint SizeInJiffies() const;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private:
    void PullerThread();
    void Enqueue(Msg* aMsg);
    void SetGorging(TBool aGorging);
private: // from MsgReservoir
    void ProcessMsgIn(MsgMode* aMsg) override;
    void ProcessMsgIn(MsgHalt* aMsg) override;
    void ProcessMsgIn(MsgQuit* aMsg) override;
    void ProcessMsgIn(MsgDecodedStream* aMsg) override;
    Msg* ProcessMsgOut(MsgMode* aMsg) override;
    Msg* ProcessMsgOut(MsgHalt* aMsg) override;
    Msg* ProcessMsgOut(MsgDecodedStream* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
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
    TBool iGorgeOnHaltOut;
    TBool iGorgeOnStreamOut;
    TBool iQuit;
    BwsMode iMode;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_GORGER
