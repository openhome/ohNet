#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>

#include <atomic>

namespace OpenHome {
namespace Media {

class Drainer : public PipelineElement, public IPipelineElementUpstream, private IStreamHandler, private INonCopyable
{
    friend class SuiteDrainer;

    static const TUint kSupportedMsgTypes;
public:
    Drainer(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream);
    ~Drainer();
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // from PipelineElement
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgDecodedStream* aMsg) override;
private: // from IStreamHandler
    EStreamPlay OkToPlay(TUint aStreamId) override;
    TUint TrySeek(TUint aStreamId, TUint64 aOffset) override;
    TUint TryDiscard(TUint aJiffies) override;
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstream;
    Semaphore iSem;
    Msg* iPending;
    std::atomic<IStreamHandler*> iStreamHandler;
    std::atomic<TBool> iGenerateDrainMsg;
    TBool iWaitForDrained;
};

} // namespace Media
} // namespace OpenHome

