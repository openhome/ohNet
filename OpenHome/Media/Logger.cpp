#include <OpenHome/Media/Logger.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

//  Logger

Logger::Logger(IPipelineElementUpstream& aUpstreamElement, const TChar* aId)
    : iUpstreamElement(&aUpstreamElement)
    , iDownstreamElement(NULL)
    , iId(aId)
    , iEnabled(false)
    , iFilter(EMsgAll)
    , iShutdownSem("PDSD", 0)
{
}

Logger::Logger(const TChar* aId, IPipelineElementDownstream& aDownstreamElement)
    : iUpstreamElement(NULL)
    , iDownstreamElement(&aDownstreamElement)
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
    Msg* msg = iUpstreamElement->Pull();
    (void)msg->Process(*this);
    return msg;
}

void Logger::Push(Msg* aMsg)
{
    (void)aMsg->Process(*this);
    iDownstreamElement->Push(aMsg);
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

Msg* Logger::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (IsEnabled(EMsgEncodedStream)) {
        Log::Print("Pipeline (%s): encoded stream {", iId);
        Log::Print(aMsg->Uri());
        Log::Print(", metaText: ");
        Log::Print(aMsg->MetaText());
        Log::Print(" , totalBytes: %llu, streamId: %u, seekable: %s, live: %s}\n",
                    aMsg->TotalBytes(), aMsg->StreamId(),
                    (aMsg->Seekable()? "true" : "false"),
                    (aMsg->Live()? "true" : "false"));
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

Msg* Logger::ProcessMsg(MsgDecodedStream* aMsg)
{
    if (IsEnabled(EMsgDecodedStream)) {
        const DecodedStreamInfo& stream = aMsg->StreamInfo();
        Log::Print("Pipeline (%s): audio format {streamId: %u, bitRate: %u, bitDepth: %u, sampleRate: %u, codec: ",
                    iId, stream.StreamId(), stream.BitRate(), stream.BitDepth(), stream.SampleRate());
        Log::Print(stream.CodecName());
        Log::Print(", trackLength: %llu, sampleStart: %u, lossless: %s}\n", stream.TrackLength(), stream.SampleStart(), (stream.Lossless()? "true" : "false"));
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
