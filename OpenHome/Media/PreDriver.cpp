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
    , iFormat(NULL)
    , iPendingFormatChange(NULL)
    , iPendingHalt(NULL)
    , iHalted(true)
    , iShutdownSem("PDSD", 0)
{
}

PreDriver::~PreDriver()
{
    iShutdownSem.Wait();
    if (iFormat != NULL) {
        iFormat->RemoveRef();
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
    const AudioFormat& format = iFormat->Format();
    MsgPlayable* playable = aMsg->CreatePlayable(format.SampleRate(), format.BitDepth(), format.NumChannels());
    return AddPlayable(playable);
}

Msg* PreDriver::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // we're the only generator of MsgPlayable so don't expect them to appear from upstream
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgAudioFormat* aMsg)
{
    const AudioFormat& format = iFormat->Format();
    if (iFormat != NULL &&
        aMsg->Format().SampleRate() == format.SampleRate() &&
        aMsg->Format().BitDepth() == format.BitDepth()) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return NULL;
    }
    if (iFormat != NULL) {
        iFormat->RemoveRef();
    }
    iFormat = aMsg;
    iFormat->AddRef();
    TUint jiffies = iMaxPlayableJiffies;
    const TUint jiffiesPerSample = Jiffies::JiffiesPerSample(iFormat->Format().SampleRate());
    iMaxPlayableBytes = Jiffies::BytesFromJiffies(jiffies, jiffiesPerSample, iFormat->Format().NumChannels(), iFormat->Format().BitDepth() / 8);
    if (iHalted) {
        ASSERT(iPlayable == NULL);
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

Msg* PreDriver::ProcessMsg(MsgAudioStream* aMsg)
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
