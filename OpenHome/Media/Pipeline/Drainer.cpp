#include <OpenHome/Media/Pipeline/Drainer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint Drainer::kSupportedMsgTypes =   eMode
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
    , iPending(nullptr)
    , iStreamHandler(nullptr)
    , iGenerateDrainMsg(false)
    , iWaitForDrained(false)
    , iIgnoreNextStarving(false)
{
}

Drainer::~Drainer()
{
    if (iPending != nullptr) {
        iPending->RemoveRef();
    }
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
            return iMsgFactory.CreateMsgDrain(MakeFunctor(iSem, &Semaphore::Signal));
        }
    }
    Msg* msg;
    if (iPending == nullptr) {
        msg = iUpstream.Pull();
    }
    else {
        msg = iPending;
        iPending = nullptr;
    }
    {
        /* iUpstream.Pull() has unbounded duration.  If NotifyStarving() was
           called during this time, we should drain the pipeline before passing
           on the next msg. */
        AutoMutex _(iLock);
        if (iGenerateDrainMsg) {
            iIgnoreNextStarving = true;
            iGenerateDrainMsg = false;
            iWaitForDrained = true;
            iPending = msg;
            return iMsgFactory.CreateMsgDrain(MakeFunctor(iSem, &Semaphore::Signal));
        }
        msg = msg->Process(*this);
    }
    return msg;
}

Msg* Drainer::ProcessMsg(MsgHalt* aMsg)
{
    LOG(kPipeline, "Drainer enabled (MsgHalt)\n");
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

void Drainer::NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving)
{
    AutoMutex _(iLock);
    if (aStarving) {
        if (iIgnoreNextStarving) {
            iIgnoreNextStarving = false;
        }
        else {
            LOG(kPipeline, "Drainer enabled (NotifyStarving)\n");
            iGenerateDrainMsg = true;
        }
    }
    if (iStreamHandler != nullptr) {
        iStreamHandler->NotifyStarving(aMode, aStreamId, aStarving);
    }
}
