#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PreDriver

PreDriver::PreDriver(IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies)
    : iUpstreamElement(aUpstreamElement)
    , iMaxPlayableJiffies(aMaxPlayableJiffies)
    , iMaxPlayableBytes(0)
    , iPlayable(NULL)
    , iStreamInfo(NULL)
    , iPending(NULL)
    , iRecalculateMaxPlayable(false)
    , iShutdownSem("PDSD", 0)
{
}

PreDriver::~PreDriver()
{
    iShutdownSem.Wait();
    if (iStreamInfo != NULL) {
        iStreamInfo->RemoveRef();
    }
    if (iPlayable != NULL) {
        iPlayable->RemoveRef();
    }
    if (iPending != NULL) {
        iPending->RemoveRef();
    }
}

Msg* PreDriver::Pull()
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

Msg* PreDriver::NextStoredMsg(TBool aDeliverShortPlayable)
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

Msg* PreDriver::AddPlayable(MsgPlayable* aPlayable)
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

void PreDriver::CalculateMaxPlayable()
{
    TUint jiffies = iMaxPlayableJiffies;
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(iStreamInfo->StreamInfo().SampleRate());
    iMaxPlayableBytes = Jiffies::BytesFromJiffies(jiffies, jiffiesPerSample, iStreamInfo->StreamInfo().NumChannels(), iStreamInfo->StreamInfo().BitDepth() / 8);
}

Msg* PreDriver::ProcessMsg(MsgMode* aMsg)
{
    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* PreDriver::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* PreDriver::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgFlush this far down the pipeline
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgWait this far down the pipeline
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (iStreamInfo != NULL) {
        const DecodedStreamInfo& stream = iStreamInfo->StreamInfo();
        if (aMsg->StreamInfo().SampleRate() == stream.SampleRate() &&
            aMsg->StreamInfo().BitDepth() == stream.BitDepth() &&
            aMsg->StreamInfo().NumChannels() == stream.NumChannels()) {
                // no change in format.  Discard this msg
                aMsg->RemoveRef();
                return NULL;
        }
        iStreamInfo->RemoveRef();
    }
    iStreamInfo = aMsg;
    iStreamInfo->AddRef();
    iRecalculateMaxPlayable = true;

    ASSERT(iPending == NULL);
    iPending = aMsg;
    return NextStoredMsg(true);
}

Msg* PreDriver::ProcessMsg(MsgAudioPcm* aMsg)
{
    MsgPlayable* playable = aMsg->CreatePlayable();
    return AddPlayable(playable);
}

Msg* PreDriver::ProcessMsg(MsgSilence* aMsg)
{
    const DecodedStreamInfo& stream = iStreamInfo->StreamInfo();
    MsgPlayable* playable = aMsg->CreatePlayable(stream.SampleRate(), stream.BitDepth(), stream.NumChannels());
    return AddPlayable(playable);
}

Msg* PreDriver::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // we're the only generator of MsgPlayable so don't expect them to appear from upstream
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgQuit* aMsg)
{
    iShutdownSem.Signal();
    return aMsg;
}
