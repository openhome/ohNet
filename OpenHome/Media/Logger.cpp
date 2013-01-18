#include <OpenHome/Media/Logger.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

//  Logger

Logger::Logger(IPipelineElementUpstream& aUpstreamElement, const TChar* aId)
    : iUpstreamElement(aUpstreamElement)
    , iId(aId)
    , iEnabled(false)
    , iFilter(EMsgAll)
    , iShutdownSem("PDSD", 0)
{
}

Logger::~Logger()
{
    iShutdownSem.Wait();
}

void Logger::SetEnabled(TBool aEnabled)
{
    iEnabled = aEnabled;
}

void Logger::SetFilter(TUint aMsgTypes)
{
    iFilter = aMsgTypes;
}

Msg* Logger::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

Msg* Logger::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (IsEnabled(EMsgAudioEncoded)) {
        Log::Print("Pipeline (%s): encoded {bytes: %u}\n", iId, aMsg->Bytes());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (IsEnabled(EMsgAudioPcm)) {
        Log::Print("Pipeline (%s): audioPcm {jiffies: %u}", iId, aMsg->Jiffies());
        LogRamp(aMsg->Ramp());
        Log::Print("\n");
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgSilence* aMsg)
{
    if (IsEnabled(EMsgSilence)) {
        Log::Print("Pipeline (%s): silence {jiffies: %u}", iId, aMsg->Jiffies());
        LogRamp(aMsg->Ramp());
        Log::Print("\n");
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgPlayable* aMsg)
{
    if (IsEnabled(EMsgPlayable)) {
        Log::Print("Pipeline (%s): playable {bytes: %u}", iId, aMsg->Bytes());
        LogRamp(aMsg->Ramp());
        Log::Print("\n");
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgAudioFormat* aMsg)
{
    if (IsEnabled(EMsgAudioFormat)) {
        const AudioFormat& af = aMsg->Format();
        Log::Print("Pipeline (%s): audio format {bitRate: %u, bitDepth: %u, sampleRate: %u, codec: ", iId, af.BitRate(), af.BitDepth(), af.SampleRate());
        Log::Print(af.CodecName());
        Log::Print(", trackLength: %llu, lossless: %s}\n", af.TrackLength(), (af.Lossless()? "true" : "false"));
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgTrack* aMsg)
{
    if (IsEnabled(EMsgTrack)) {
        Log::Print("Pipeline (%s): track\n", iId);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (IsEnabled(EMsgAudioFormat)) {
        Log::Print("Pipeline (%s): metaText {", iId);
        Log::Print(aMsg->Uri());
        Log::Print(", ");
        Log::Print(aMsg->MetaText());
        Log::Print("}\n");
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgMetaText* aMsg)
{
    if (IsEnabled(EMsgMetaText)) {
        Log::Print("Pipeline (%s): metaText {", iId);
        Log::Print(aMsg->MetaText());
        Log::Print("}\n");
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgHalt* aMsg)
{
    if (IsEnabled(EMsgHalt)) {
        Log::Print("Pipeline (%s): halt\n", iId);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgFlush* aMsg)
{
    if (IsEnabled(EMsgFlush)) {
        Log::Print("Pipeline (%s): flush\n", iId);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgQuit* aMsg)
{
    if (IsEnabled(EMsgQuit)) {
        Log::Print("Pipeline (%s): quit\n", iId);
    }
    iShutdownSem.Signal();
    return aMsg;
}

void Logger::LogRamp(const Media::Ramp& aRamp)
{
    if (aRamp.IsEnabled()) {
        Log::Print(", {ramp: [%08x..%08x]}", aRamp.Start(), aRamp.End());
    }
}

TBool Logger::IsEnabled(EMsgType aType) const
{
    if (iEnabled && (iFilter & aType) == aType) {
        return true;
    }
    return false;
}
