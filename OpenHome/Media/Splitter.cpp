#include <OpenHome/Media/Splitter.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Splitter

Splitter::Splitter(IPipelineElementUpstream& aUpstreamElement)
    : iUpstreamElement(aUpstreamElement)
    , iBranch(NULL)
{
}

Splitter::~Splitter()
{
}

IPipelineElementDownstream* Splitter::SetPipelineBranch(IPipelineElementDownstream& aBranch)
{
    IPipelineElementDownstream* prev = iBranch;
    iBranch = &aBranch;
    return prev;
}

Msg* Splitter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    if (iBranch != NULL) {
        Msg* copy = msg->Process(*this);
        iBranch->Push(copy);
    }
    return msg;
}

Msg* Splitter::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgEncodedStream* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* Splitter::ProcessMsg(MsgMetaText* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgFlush at this stage of the pipeline
    return NULL;
}

Msg* Splitter::ProcessMsg(MsgWait* /*aMsg*/)
{
    // FIXME - should add a ref and return aMsg.
    // Splitter should then have a ProcessMsgOut set of routines which can
    // remove a reference for the original aMsg and return NULL.
    // The Pull() method should ensure than a NULL value is skipped and never
    // passed downstream.
    ASSERTS();
    return NULL;
}

Msg* Splitter::ProcessMsg(MsgDecodedStream* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Splitter::ProcessMsg(MsgQuit* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}
