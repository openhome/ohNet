#include <OpenHome/Media/Pipeline/SampleRateValidator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;


const TUint SampleRateValidator::kSupportedMsgTypes =   eMode
                                                      | eTrack
                                                      | eDrain
                                                      | eDelay
                                                      | eEncodedStream
                                                      | eMetatext
                                                      | eStreamInterrupted
                                                      | eHalt
                                                      | eFlush
                                                      | eWait
                                                      | eDecodedStream
                                                      | eBitRate
                                                      | eAudioPcm
                                                      | eSilence
                                                      | eQuit;

SampleRateValidator::SampleRateValidator(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iDownstream(aDownstreamElement)
    , iAnimator(nullptr)
    , iTargetFlushId(MsgFlush::kIdInvalid)
    , iFlushing(false)
    , iOutputMsgDelayOnAnimatorDelayChange(false)
    , iDelayJiffies(0)
    , iAnimatorDelayJiffies(0)
{
}

void SampleRateValidator::SetAnimator(IPipelineAnimator& aPipelineAnimator)
{
    iAnimator = &aPipelineAnimator;
}

void SampleRateValidator::Push(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    if (msg != nullptr) {
        iDownstream.Push(msg);
    }
}

Msg* SampleRateValidator::ProcessMsg(MsgMode* aMsg)
{
    iFlushing = false;
    iOutputMsgDelayOnAnimatorDelayChange = false;
    iAnimatorDelayJiffies = 0;
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgTrack* aMsg)
{
    iFlushing = false;
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgDelay* aMsg)
{
    iOutputMsgDelayOnAnimatorDelayChange = true;
    if (aMsg->AnimatorDelayJiffies() == iAnimatorDelayJiffies) {
        return aMsg;
    }
    iDelayJiffies = aMsg->DelayJiffies();
    aMsg->RemoveRef();
    return iMsgFactory.CreateMsgDelay(iDelayJiffies, iAnimatorDelayJiffies);
}

Msg* SampleRateValidator::ProcessMsg(MsgMetaText* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgFlush* aMsg)
{
    if (iTargetFlushId != MsgFlush::kIdInvalid && iTargetFlushId == aMsg->Id()) {
        iTargetFlushId = MsgFlush::kIdInvalid;
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}

Msg* SampleRateValidator::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    try {
        ASSERT(iAnimator != nullptr);
        const TUint animatorDelayJiffies = iAnimator->PipelineAnimatorDelayJiffies(streamInfo.SampleRate(),
                                                                                   streamInfo.BitDepth(),
                                                                                   streamInfo.NumChannels());
        iFlushing = false;
        if (iAnimatorDelayJiffies != animatorDelayJiffies) {
            iAnimatorDelayJiffies = animatorDelayJiffies;
            if (iOutputMsgDelayOnAnimatorDelayChange) {
                iDownstream.Push(iMsgFactory.CreateMsgDelay(iDelayJiffies, iAnimatorDelayJiffies));
            }
        }
    }
    catch (SampleRateUnsupported&) {
        iFlushing = true;
        IStreamHandler* streamHandler = streamInfo.StreamHandler();
        const TUint streamId = streamInfo.StreamId();
        if (streamHandler != nullptr) {
            (void)streamHandler->OkToPlay(streamId);
            iTargetFlushId = streamHandler->TryStop(streamId);
        }
    }
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgAudioPcm* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessMsg(MsgSilence* aMsg)
{
    return ProcessFlushable(aMsg);
}

Msg* SampleRateValidator::ProcessFlushable(Msg* aMsg)
{
    if (iFlushing) {
        aMsg->RemoveRef();
        return nullptr;
    }
    return aMsg;
}
