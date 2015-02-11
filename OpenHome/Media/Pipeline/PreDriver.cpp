#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PreDriver

PreDriver::PreDriver(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iShutdownSem("PDSD", 0)
{
}

PreDriver::~PreDriver()
{
    iShutdownSem.Wait();
}

Msg* PreDriver::Pull()
{
    Msg* msg;
    do {
        msg = iUpstreamElement.Pull();
        ASSERT(msg != NULL);
        msg = msg->Process(*this);
    } while (msg == NULL);
    return msg;
}

Msg* PreDriver::ProcessMsg(MsgMode* aMsg)
{
    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* PreDriver::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
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
    return aMsg;
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
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    if (stream.SampleRate()  == iSampleRate &&
        stream.BitDepth()    == iBitDepth   &&
        stream.NumChannels() == iNumChannels) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return NULL;
    }
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();

    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg->CreatePlayable();
}

Msg* PreDriver::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg->CreatePlayable(iSampleRate, iBitDepth, iNumChannels);
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
