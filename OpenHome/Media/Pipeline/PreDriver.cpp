#include <OpenHome/Media/Pipeline/PreDriver.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// PreDriver

const TUint PreDriver::kSupportedMsgTypes =   eMode
                                            | eDrain
                                            | eStreamInterrupted
                                            | eHalt
                                            | eDecodedStream
                                            | eAudioPcm
                                            | eSilence
                                            | eQuit;

PreDriver::PreDriver(IPipelineElementUpstream& aUpstreamElement)
    : PipelineElement(kSupportedMsgTypes)
    , iUpstreamElement(aUpstreamElement)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iShutdownSem("PDSD", 0)
    , iSilenceSinceLastDrain(0)
    , iSilenceSincePcm(false)
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
        ASSERT(msg != nullptr);
        const TBool silenceSincePcm = iSilenceSincePcm;
        msg = msg->Process(*this);
        if (silenceSincePcm && !iSilenceSincePcm) {
            const TUint ms = Jiffies::ToMs(iSilenceSinceLastDrain);
            LOG(kPipeline, "PreDriver: silence since last drain - %ums\n", ms);
        }
    } while (msg == nullptr);
    return msg;
}

Msg* PreDriver::ProcessMsg(MsgDrain* aMsg)
{
    iSilenceSinceLastDrain = 0;
    iSilenceSincePcm = false;
    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* PreDriver::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    if (stream.SampleRate()  == iSampleRate &&
        stream.BitDepth()    == iBitDepth   &&
        stream.NumChannels() == iNumChannels) {
        // no change in format.  Discard this msg
        aMsg->RemoveRef();
        return nullptr;
    }
    iSampleRate = stream.SampleRate();
    iBitDepth = stream.BitDepth();
    iNumChannels = stream.NumChannels();

    return aMsg;
}

Msg* PreDriver::ProcessMsg(MsgAudioPcm* aMsg)
{
    iSilenceSincePcm = false;
    return aMsg->CreatePlayable();
}

Msg* PreDriver::ProcessMsg(MsgSilence* aMsg)
{
    iSilenceSincePcm = true;
    iSilenceSinceLastDrain += aMsg->Jiffies();
    return aMsg->CreatePlayable();
}

Msg* PreDriver::ProcessMsg(MsgQuit* aMsg)
{
    iShutdownSem.Signal();
    return aMsg;
}
