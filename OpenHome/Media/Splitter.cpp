#include <OpenHome/Media/Splitter.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Splitter

Splitter::Splitter(IPipelineElement& aUpstreamElement, IPipelineBranch& aBranch)
    : iUpstreamElement(aUpstreamElement)
    , iBranch(aBranch)
    , iLock("SPLT")
    , iEnabled(false)
{
}

void Splitter::SetEnabled(TBool aEnabled)
{
    iLock.Wait();
    iEnabled = aEnabled;
    iLock.Signal();
}

Msg* Splitter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    iLock.Wait();
    if (iEnabled) {
        Msg* copy = msg->Process(*this);
        iBranch.AddMsg(copy);
    }
    iLock.Signal();
    return msg;
}

Msg* Splitter::ProcessMsg(MsgAudioPcm* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg->Clone();
}

Msg* Splitter::ProcessMsg(MsgPlayable* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgAudioFormat* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgTrack* aMsg)
{
    aMsg->AddRef();
    return aMsg;
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

Msg* Splitter::ProcessMsg(MsgFlush* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}

Msg* Splitter::ProcessMsg(MsgQuit* aMsg)
{
    aMsg->AddRef();
    return aMsg;
}
