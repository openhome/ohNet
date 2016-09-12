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

void Attenuator::SetAttenuation(TUint aAttenuation)
{
    iAttenuation = aAttenuation;
}

Msg* Attenuator::Pull()
{
    Msg* msg = iUpstreamElement.Pull()->Process(*this);

    ASSERT(msg != nullptr);
    return msg;
}

Msg* Attenuator::ProcessMsg(MsgMode* aMsg)
{
    iActive = aMsg->Mode() == Brn("RAOP");

    return aMsg;
}


Msg* Attenuator::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iActive) {
        aMsg->SetAttenuation(iAttenuation);
    }
    return aMsg;
}
