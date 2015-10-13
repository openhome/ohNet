#include <OpenHome/Media/Pipeline/ClockPullerManual.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/ClockPuller.h>
#include <OpenHome/Media/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint ClockPullerManual::kSupportedMsgTypes =   eMode
                                                    | eTrack
                                                    | eDrain
                                                    | eDelay
                                                    | eEncodedStream
                                                    | eMetatext
                                                    | eStreamInterrupted
                                                    | eHalt
                                                    | eFlush
                                                    | eWait
                                                    | eDecodedStream
                                                    | eBitRate
                                                    | eAudioPcm
                                                    | eSilence
                                                    | eQuit;

const TChar ClockPullerManual::kShellCommand[] = "clock_pull";

ClockPullerManual::ClockPullerManual(IPipelineElementUpstream& aUpstream, Net::IShell& aShell)
    : PipelineElement(kSupportedMsgTypes)
    , iLock("CPLM")
    , iUpstream(aUpstream)
    , iShell(aShell)
    , iEnabled(false)
    , iMultiplier(IPullableClock::kNominalFreq)
{
    iShell.AddCommandHandler(kShellCommand, *this);
}

ClockPullerManual::~ClockPullerManual()
{
    iShell.RemoveCommandHandler(kShellCommand);
}

Msg* ClockPullerManual::Pull()
{
    Msg* msg = iUpstream.Pull();
    msg = msg->Process(*this);
    return msg;
}

Msg* ClockPullerManual::ProcessMsg(MsgMode* aMsg)
{
    auto pullers = aMsg->ClockPullers();
    AutoMutex _(iLock);
    iEnabled = (pullers.ReservoirLeft()  != nullptr ||
                pullers.ReservoirRight() != nullptr ||
                pullers.Timestamp()      != nullptr);
    if (iEnabled && iMultiplier != IPullableClock::kNominalFreq) {
        LOG(kPipeline, "Manual clock pull suppressed for mode with automatic clock puller\n");
    }
    return aMsg;
}

Msg* ClockPullerManual::ProcessMsg(MsgAudioPcm* aMsg)
{
    ProcessAudio(aMsg);
    return aMsg;
}

Msg* ClockPullerManual::ProcessMsg(MsgSilence* aMsg)
{
    ProcessAudio(aMsg);
    return aMsg;
}

void ClockPullerManual::ProcessAudio(MsgAudio* aAudio)
{
    AutoMutex _(iLock);
    if (!iEnabled) {
        return;
    }
    aAudio->SetClockPull(iMultiplier);
}

void ClockPullerManual::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for \'clock_pull\' command\n"));
        return;
    }
    if (aArgs[0].Bytes() < 3 || aArgs[0][0] < '0' || aArgs[0][0] > '1' || aArgs[0][1] != '.') {
        aResponse.Write(Brn("Error: multiplier must be in the form [0|1].[fraction]\n"));
        return;
    }
    TUint64 mult = IPullableClock::kNominalFreq;
    mult *= aArgs[0][0] - '0';
    TUint div = 1;
    for (TUint i=2; i<aArgs[0].Bytes(); i++) {
        mult *= 10;
        mult += ((TUint64)aArgs[0][i] - '0') * IPullableClock::kNominalFreq;
        div *= 10;
    }
    mult /= div;
    iMultiplier = (TUint)mult;
    Log::Print("Setting multiplier to %08x\n", iMultiplier);
}

void ClockPullerManual::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("clock_pull [multiplier]\n"));
    aResponse.Write(Brn("  set clock pull multiplier\n"));
    aResponse.Write(Brn("  [multiplier] is a float in the range (0..2)\n"));
    aResponse.Write(Brn("  ...which only applies to sources that don't normally support clock pulling\n"));
}
