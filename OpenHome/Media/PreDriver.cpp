#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PreDriver

PreDriver::PreDriver(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement, TUint aMaxPlayableJiffies)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iMaxPlayableJiffies(aMaxPlayableJiffies)
    , iMaxPlayableBytes(0)
    , iPlayable(NULL)
    , iStreamInfo(NULL)
    , iPendingFormatChange(NULL)
    , iPendingHalt(NULL)
    , iHalted(true)
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
    if (iPendingFormatChange != NULL) {
        iPendingFormatChange->RemoveRef();
    }
    if (iPendingHalt != NULL) {
        iPendingHalt->RemoveRef();
    }
}

Msg* PreDriver::Pull()
{
    Msg* msg;
    do {
        msg = NextStoredMsg();
        if (msg == NULL) {
            msg = iUpstreamElement.Pull();
            msg = msg->Process(*this);
        }
    } while (msg == NULL);
    return msg;
}

Msg* PreDriver::NextStoredMsg()
{
    Msg* msg = NULL;
    if (iPlayable != NULL) {
        const TUint bytes = iPlayable->Bytes();
        if (bytes == iMaxPlayableBytes) {
            msg = iPlayable;
            iPlayable = NULL;
        }
        else if (bytes > iMaxPlayableBytes) {
            msg = iPlayable;
            iPlayable = iPlayable->Split(iMaxPlayableBytes);
        }
        else if (iPendingHalt != NULL || iPendingFormatChange != NULL) {
            msg = iPlayable;
            iPlayable = NULL;
        }
    }
    else if (iPendingHalt != NULL) {
        msg = iPendingHalt;
        iPendingHalt = NULL;
    }
    else if (iPendingFormatChange != NULL) {
        CalculateMaxPlayable();
        msg = iPendingFormatChange;
        iPendingFormatChange = NULL;
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

Msg* PreDriver::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgAudioPcm* aMsg)
{
    iHalted = false;
    MsgPlayable* playable = aMsg->CreatePlayable();
    return AddPlayable(playable);
}

Msg* PreDriver::ProcessMsg(MsgSilence* aMsg)
{
    iHalted = false;
    const DecodedStreamInfo& stream = iStreamInfo->StreamInfo();
    MsgPlayable* playable = aMsg->CreatePlayable(stream.SampleRate(), stream.BitDepth(), stream.NumChannels());
    return AddPlayable(playable);
}

Msg* PreDriver::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // we're the only generator of MsgPlayable so don't expect them to appear from upstream
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = iStreamInfo->StreamInfo();
    if (iStreamInfo != NULL &&
        aMsg->StreamInfo().SampleRate() == stream.SampleRate() &&
        aMsg->StreamInfo().BitDepth() == stream.BitDepth()) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return NULL;
    }
    if (iStreamInfo != NULL) {
        iStreamInfo->RemoveRef();
    }
    iStreamInfo = aMsg;
    iStreamInfo->AddRef();
    if (iHalted) {
        ASSERT(iPlayable == NULL);
        CalculateMaxPlayable();
        return aMsg;
    }
    iHalted = true;
    iPendingFormatChange = aMsg;
    iPendingHalt = iMsgFactory.CreateMsgHalt();
    return NextStoredMsg();
}

Msg* PreDriver::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgEncodedStream* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgMetaText* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgHalt* aMsg)
{
    iHalted = true;
    if (iPlayable != NULL) {
        iPendingHalt = aMsg;
        Msg* msg = iPlayable;
        iPlayable = NULL;
        return msg;
    }
    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgFlush this far down the pipeline
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgQuit* aMsg)
{
    iShutdownSem.Signal();
    return aMsg;
}
