#include <OpenHome/Media/Pipeline/Attenuator.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Attenuator
const TUint Attenuator::kSupportedMsgTypes =   eMode
                                         | eTrack
                                         | eDrain
                                         | eDelay
                                         | eMetatext
                                         | eStreamInterrupted
                                         | eHalt
                                         | eWait
                                         | eDecodedStream
                                         | eBitRate
                                         | eAudioPcm
                                         | eSilence
                                         | eQuit;

Attenuator::Attenuator(IPipelineElementUpstream& aUpstreamElement)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iAttenuation(kUnityAttenuation)
    , iActive(false)
{
}

Attenuator::~Attenuator()
{
}

void Attenuator::SetAttenuation(TUint aAttenuation)
{
    Log::Print("Attenuator::SetAttenuation(%d)\n", aAttenuation);
    iAttenuation = aAttenuation;
}

Msg* Attenuator::Pull()
{
    Msg* msg;
    if (!iQueue.IsEmpty()) {
        msg = iQueue.Dequeue();
    }
    else {
        msg = iUpstreamElement.Pull();
    }
    msg = msg->Process(*this);
    ASSERT(msg != nullptr);
    return msg;
}

Msg* Attenuator::ProcessMsg(MsgMode* aMsg)
{
    Log::Print("Attenuator::ProcessMsg("); Log::Print(aMsg->Mode()); Log::Print(")\n");
    if (aMsg->Mode() == Brn("RAOP")) {
        iActive = true;
    }
    else {
        iActive = false;
    }
    return aMsg;
}


Msg* Attenuator::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iActive) {
        aMsg->SetAttenuation(iAttenuation);
    }
    return aMsg;
}
