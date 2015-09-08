#include <OpenHome/Media/Utils/Aggregator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Aggregator

const TUint Aggregator::kSupportedMsgTypes =   eMode
                                             | eDrain
                                             | eHalt
                                             | eDecodedStream
                                             | ePlayable
                                             | eQuit;

Aggregator::Aggregator(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iMaxPlayableJiffies(aMaxPlayableJiffies)
    , iMaxPlayableBytes(0)
    , iPlayable(nullptr)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iPending(nullptr)
    , iRecalculateMaxPlayable(false)
{
}

Aggregator::~Aggregator()
{
    if (iPlayable != nullptr) {
        iPlayable->RemoveRef();
    }
    if (iPending != nullptr) {
        iPending->RemoveRef();
    }
}

Msg* Aggregator::Pull()
{
    Msg* msg;
    do {
        const TBool requireFullPlayable = (iPending != nullptr);
        msg = NextStoredMsg(requireFullPlayable);
        if (msg == nullptr) {
            msg = iUpstreamElement.Pull();
            ASSERT(msg != nullptr);
            msg = msg->Process(*this);
        }
    } while (msg == nullptr);
    return msg;
}

Msg* Aggregator::NextStoredMsg(TBool aDeliverShortPlayable)
{
    Msg* msg = nullptr;
    if (iPlayable != nullptr) {
        const TUint bytes = iPlayable->Bytes();
        if (bytes > iMaxPlayableBytes) {
            msg = iPlayable;
            iPlayable = iPlayable->Split(iMaxPlayableBytes);
        }
        else if (bytes == iMaxPlayableBytes || aDeliverShortPlayable) {
            msg = iPlayable;
            iPlayable = nullptr;
        }
    }
    if (msg == nullptr && iPending != nullptr) {
        msg = iPending;
        iPending = nullptr;
        if (iRecalculateMaxPlayable) {
            CalculateMaxPlayable();
            iRecalculateMaxPlayable = false;
        }
    }
    return msg;
}

void Aggregator::CalculateMaxPlayable()
{
    TUint jiffies = iMaxPlayableJiffies;
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(iSampleRate);
    iMaxPlayableBytes = Jiffies::BytesFromJiffies(jiffies, jiffiesPerSample, iNumChannels, iBitDepth/8);
}

Msg* Aggregator::ProcessMsg(MsgMode* aMsg)
{
    ASSERT(iPending == nullptr);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iPending == nullptr);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    if (stream.SampleRate()  == iSampleRate &&
        stream.BitDepth()    == iBitDepth &&
        stream.NumChannels() == iNumChannels) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return nullptr;
    }
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();
    iRecalculateMaxPlayable = true;

    ASSERT(iPending == nullptr);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgPlayable* aMsg)
{
    Msg* ret = nullptr;
    if (iPlayable == nullptr) {
        if (aMsg->Bytes() < iMaxPlayableBytes) {
            iPlayable = aMsg;
        }
        else if (aMsg->Bytes() == iMaxPlayableBytes) {
            ret = aMsg;
        }
        else {
            iPlayable = aMsg->Split(iMaxPlayableBytes);
            ret = aMsg;
        }
    }
    else {
        iPlayable->Add(aMsg);
        const TUint bytes = iPlayable->Bytes();
        if (bytes == iMaxPlayableBytes) {
            ret = iPlayable;
            iPlayable = nullptr;
        }
        else if (bytes > iMaxPlayableBytes) {
            ret = iPlayable;
            iPlayable = iPlayable->Split(iMaxPlayableBytes);
        }
    }
    return ret;
}
