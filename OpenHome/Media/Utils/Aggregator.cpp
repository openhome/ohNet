#include <OpenHome/Media/Utils/Aggregator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Aggregator

Aggregator::Aggregator(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies)
    : iUpstreamElement(aUpstreamElement)
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

Msg* Aggregator::AddPlayable(MsgPlayable* aPlayable)
{
    Msg* ret = nullptr;
    if (iPlayable == nullptr) {
        if (aPlayable->Bytes() < iMaxPlayableBytes) {
            iPlayable = aPlayable;
        }
        else if (aPlayable->Bytes() == iMaxPlayableBytes) {
            ret = aPlayable;
        }
        else {
            iPlayable = aPlayable->Split(iMaxPlayableBytes);
            ret = aPlayable;
        }
    }
    else {
        iPlayable->Add(aPlayable);
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

Msg* Aggregator::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgChangeInput* aMsg)
{
    return aMsg;
}

Msg* Aggregator::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iPending == nullptr);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgFlush this far down the pipeline
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgWait this far down the pipeline
    return nullptr;
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

Msg* Aggregator::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Aggregator::ProcessMsg(MsgPlayable* aMsg)
{
    return AddPlayable(aMsg);
}

Msg* Aggregator::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
