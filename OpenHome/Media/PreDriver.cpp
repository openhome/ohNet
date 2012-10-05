#include <OpenHome/Media/PreDriver.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PreDriver

PreDriver::PreDriver(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstreamElement)
    : iMsgFactory(aMsgFactory)
    , iUpstreamElement(aUpstreamElement)
    , iFormat(NULL)
    , iPendingFormatChange(NULL)
    , iHalted(true)
{
}

PreDriver::~PreDriver()
{
    if (iFormat != NULL) {
        iFormat->RemoveRef();
    }
    ASSERT(iPendingFormatChange == NULL);
}

Msg* PreDriver::Pull()
{
    Msg* msg;
    do {
        if (iPendingFormatChange != NULL) {
            msg = iPendingFormatChange;
            iPendingFormatChange = NULL;
        }
        else {
            msg = iUpstreamElement.Pull();
            msg = msg->Process(*this);
        }
    } while (msg == NULL);
    return msg;
}

Msg* PreDriver::ProcessMsg(MsgAudioPcm* aMsg)
{
    iHalted = false;
    MsgPlayable* playable = aMsg->CreatePlayable();
    return playable;
}

Msg* PreDriver::ProcessMsg(MsgSilence* aMsg)
{
    iHalted = false;
    const AudioFormat& format = iFormat->Format();
    MsgPlayable* playable = aMsg->CreatePlayable(format.SampleRate(), format.NumChannels());
    return playable;
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
    if (iHalted) {
        return aMsg;
    }
    iHalted = true;
    iPendingFormatChange = aMsg;
    return iMsgFactory.CreateMsgHalt();
}

Msg* PreDriver::ProcessMsg(MsgTrack* aMsg)
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
    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to encounter MsgFlush this far down the pipeline
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
