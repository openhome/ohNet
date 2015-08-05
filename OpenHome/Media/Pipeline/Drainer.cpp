#include <OpenHome/Media/Pipeline/Drainer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Functor.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint Drainer::kSupportedMsgTypes =   eMode
                                          | eSession
                                          | eTrack
                                          | eDrain
                                          | eDelay
                                          | eEncodedStream
                                          | eAudioEncoded
                                          | eMetatext
                                          | eStreamInterrupted
                                          | eHalt
                                          | eWait
                                          | eDecodedStream
                                          | eAudioPcm
                                          | eSilence
                                          | eQuit;

Drainer::Drainer(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iUpstream(aUpstream)
    , iLock("DRAI")
    , iSem("DRAI", 0)
    , iStreamHandler(NULL)
    , iGenerateDrainMsg(false)
    , iWaitForDrained(false)
    , iIgnoreNextStarving(false)
{
}

Msg* Drainer::Pull()
{
    if (iWaitForDrained) {
        iSem.Wait();
        iWaitForDrained = false; // no synchronisation required - is only accessed in this function
    }
    {
        AutoMutex _(iLock);
        if (iGenerateDrainMsg) {
            iIgnoreNextStarving = true;
            iGenerateDrainMsg = false;
            iWaitForDrained = true;
            return iMsgFactory.CreateMsgDrain(MakeFunctor(*this, &Drainer::PipelineDrained));
        }
    }
    Msg* msg = iUpstream.Pull();
    iLock.Wait();
    msg = msg->Process(*this);
    iLock.Signal();
    return msg;
}

Msg* Drainer::ProcessMsg(MsgHalt* aMsg)
{
    iGenerateDrainMsg = true;
    return aMsg;
}

Msg* Drainer::ProcessMsg(MsgDecodedStream* aMsg)
{
    iStreamHandler = aMsg->StreamInfo().StreamHandler();
    auto msg = iMsgFactory.CreateMsgDecodedStream(aMsg, this);
    aMsg->RemoveRef();
    return msg;
}

EStreamPlay Drainer::OkToPlay(TUint /*aStreamId*/)
{
    ASSERTS();
    return ePlayNo;
}

TUint Drainer::TrySeek(TUint /*aStreamId*/, TUint64 /*aOffset*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

TUint Drainer::TryStop(TUint /*aStreamId*/)
{
    ASSERTS();
    return MsgFlush::kIdInvalid;
}

void Drainer::NotifyStarving(const Brx& aMode, TUint aStreamId)
{
    iLock.Wait();
    auto streamHandler = iStreamHandler;
    iLock.Signal();
    if (streamHandler != nullptr) {
        streamHandler->NotifyStarving(aMode, aStreamId);
    }
    iLock.Wait();
    if (iIgnoreNextStarving) {
        iIgnoreNextStarving = false;
    }
    else {
        iGenerateDrainMsg = true;
    }
    iLock.Signal();
}

void Drainer::PipelineDrained()
{
    iSem.Signal();
}
