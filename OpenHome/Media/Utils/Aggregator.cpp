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
    , iPlayable(NULL)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iPending(NULL)
    , iRecalculateMaxPlayable(false)
{
}

Aggregator::~Aggregator()
{
    if (iPlayable != NULL) {
        iPlayable->RemoveRef();
    }
    if (iPending != NULL) {
        iPending->RemoveRef();
    }
}

Msg* Aggregator::Pull()
{
    Msg* msg;
    do {
        const TBool requireFullPlayable = (iPending != NULL);
        msg = NextStoredMsg(requireFullPlayable);
        if (msg == NULL) {
            msg = iUpstreamElement.Pull();
            ASSERT(msg != NULL);
            msg = msg->Process(*this);
        }
    } while (msg == NULL);
    return msg;
}

Msg* Aggregator::NextStoredMsg(TBool aDeliverShortPlayable)
{
    Msg* msg = NULL;
    if (iPlayable != NULL) {
        const TUint bytes = iPlayable->Bytes();
        if (bytes > iMaxPlayableBytes) {
            msg = iPlayable;
            iPlayable = iPlayable->Split(iMaxPlayableBytes);
        }
        else if (bytes == iMaxPlayableBytes || aDeliverShortPlayable) {
            msg = iPlayable;
            iPlayable = NULL;
        }
    }
    if (msg == NULL && iPending != NULL) {
        msg = iPending;
        iPending = NULL;
        if (iRecalculateMaxPlayable) {
            CalculateMaxPlayable();
            iRecalculateMaxPlayable = false;
        }
    }
    return msg;
}

Msg* Aggregator::AddPlayable(MsgPlayable* aPlayable)
{
    Msg* ret = NULL;
    if (iPlayable == NULL) {
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
            iPlayable = NULL;
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
    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgChangeInput* aMsg)
{
    return aMsg;
}

Msg* Aggregator::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgFlush this far down the pipeline
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgWait this far down the pipeline
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    if (stream.SampleRate()  == iSampleRate &&
        stream.BitDepth()    == iBitDepth &&
        stream.NumChannels() == iNumChannels) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return NULL;
    }
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();
    iRecalculateMaxPlayable = true;

    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* Aggregator::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Aggregator::ProcessMsg(MsgPlayable* aMsg)
{
    return AddPlayable(aMsg);
}

Msg* Aggregator::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
