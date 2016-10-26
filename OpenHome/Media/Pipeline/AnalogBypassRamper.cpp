#include <OpenHome/Media/Pipeline/AnalogBypassRamper.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint AnalogBypassRamper::kSupportedMsgTypes =   eMode
                                                     | eDrain
                                                     | eStreamInterrupted
                                                     | eHalt
                                                     | eDecodedStream
                                                     | eAudioPcm
                                                     | eSilence
                                                     | eQuit;

AnalogBypassRamper::AnalogBypassRamper(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream)
    : PipelineElement(kSupportedMsgTypes)
    , iMsgFactory(aMsgFactory)
    , iUpstream(aUpstream)
    , iLock("MPMT")
    , iVolumeRamper(nullptr)
    , iMsgDrain(nullptr)
    , iMsgHalt(nullptr)
    , iHalting(false)
    , iHalted(false)
    , iAnalogBypassEnabled(false)
{
}

AnalogBypassRamper::~AnalogBypassRamper()
{
    if (iMsgDrain != nullptr) {
        iMsgDrain->RemoveRef();
    }
    if (iMsgHalt != nullptr) {
        iMsgHalt->RemoveRef();
    }
}

void AnalogBypassRamper::SetVolumeRamper(IAnalogBypassVolumeRamper& aVolumeRamper)
{
    iVolumeRamper = &aVolumeRamper;
}

Msg* AnalogBypassRamper::Pull()
{
    Msg* msg = iUpstream.Pull();
    AutoMutex _(iLock);
    iHalting = false;
    msg = msg->Process(*this);
    return msg;
}

Msg* AnalogBypassRamper::ProcessMsg(MsgDrain* aMsg)
{
    ASSERT(iMsgDrain == nullptr);
    iHalting = true;
    iMsgDrain = aMsg;
    return iMsgFactory.CreateMsgDrain(MakeFunctor(*this, &AnalogBypassRamper::Drained));
}

Msg* AnalogBypassRamper::ProcessMsg(MsgHalt* aMsg)
{
    ASSERT(iMsgHalt == nullptr);
    iHalting = true;
    iMsgHalt = aMsg;
    return iMsgFactory.CreateMsgHalt(aMsg->Id(), MakeFunctor(*this, &AnalogBypassRamper::Halted));
}

Msg* AnalogBypassRamper::ProcessMsg(MsgDecodedStream* aMsg)
{
    iAnalogBypassEnabled = aMsg->StreamInfo().AnalogBypass();
    return aMsg;
}

Msg* AnalogBypassRamper::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (iAnalogBypassEnabled) {
        const TUint rampMultiplier = aMsg->MedianRampMultiplier();
        LOG(kVolume, "AnalogBypassRamper::ProcessMsg(MsgAudioPcm*) iAnalogBypassEnabled rampMultiplier: %u\n", rampMultiplier);
        iVolumeRamper->ApplyVolumeMultiplier(rampMultiplier);
    }
    else if (iHalted) {
        LOG(kVolume, "AnalogBypassRamper::ProcessMsg(MsgAudioPcm*) iHalted rampMultiplier: %u\n", IAnalogBypassVolumeRamper::kMultiplierFull);
        iHalted = false;
        iVolumeRamper->ApplyVolumeMultiplier(IAnalogBypassVolumeRamper::kMultiplierFull);
    }
    return aMsg;
}

Msg* AnalogBypassRamper::ProcessMsg(MsgSilence* aMsg)
{
    if (iAnalogBypassEnabled) {
        LOG(kVolume, "AnalogBypassRamper::ProcessMsg(MsgSilence*) iAnalogBypassEnabled rampMultiplier: %u\n", IAnalogBypassVolumeRamper::kMultiplierZero);
        iVolumeRamper->ApplyVolumeMultiplier(IAnalogBypassVolumeRamper::kMultiplierZero);
    }
    return aMsg;
}

void AnalogBypassRamper::Drained()
{
    AutoMutex _(iLock);
    CheckForHalted();
    ASSERT(iMsgDrain != nullptr);
    iMsgDrain->ReportDrained();
    iMsgDrain->RemoveRef();
    iMsgDrain = nullptr;
}

void AnalogBypassRamper::Halted()
{
    AutoMutex _(iLock);
    CheckForHalted();
    ASSERT(iMsgHalt != nullptr);
    iMsgHalt->ReportHalted();
    iMsgHalt->RemoveRef();
    iMsgHalt = nullptr;
}

void AnalogBypassRamper::CheckForHalted()
{
    if (iHalting) {
        LOG(kVolume, "AnalogBypassRamper::CheckForHalted iHalting, rampMultiplier: %u\n", IAnalogBypassVolumeRamper::kMultiplierZero);
        iHalted = true;
        iVolumeRamper->ApplyVolumeMultiplier(IAnalogBypassVolumeRamper::kMultiplierZero);
    }
}
