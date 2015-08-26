#include <OpenHome/Av/Songcast/Splitter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;

// Splitter

Splitter::Splitter(IPipelineElementDownstream& aBranch, const Brx& aSongcastMode)
    : iUpstream(nullptr)
    , iBranch(aBranch)
    , iSongcastMode(aSongcastMode)
    , iBranchEnabled(true)
{
}

void Splitter::SetUpstream(IPipelineElementUpstream& aUpstream)
{
    iUpstream = &aUpstream;
}

Msg* Splitter::Pull()
{
    Msg* msg = iUpstream->Pull();
    (void)msg->Process(*this);
    if (iBranchEnabled) {
        Msg* copy = MsgCloner::NewRef(*msg);
        iBranch.Push(copy);
    }
    return msg;
}

Msg* Splitter::ProcessMsg(MsgMode* aMsg)
{
    iBranchEnabled = (aMsg->Mode() != iSongcastMode);
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgTrack* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgEncodedStream* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return nullptr;
}

Msg* Splitter::ProcessMsg(MsgMetaText* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgFlush at this stage of the pipeline
    return nullptr;
}

Msg* Splitter::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgDecodedStream* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Splitter::ProcessMsg(MsgQuit* aMsg)
{
    iBranchEnabled = true;
    return aMsg;
}


// Splitter::MsgCloner

Msg* Splitter::MsgCloner::NewRef(Msg& aMsg)
{ // static
    MsgCloner self;
    return aMsg.Process(self);
}

Splitter::MsgCloner::MsgCloner()
{
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgMode* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgDrain* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgDelay* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgMetaText* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgWait* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgDecodedStream* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Splitter::MsgCloner::ProcessMsg(MsgQuit* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}
