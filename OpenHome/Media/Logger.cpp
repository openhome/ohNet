#include <OpenHome/Media/Logger.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

#undef LOG_METADATA /* Track metadata and stream metatext are huge.  They tend to
                       drown out all other logging and reporting them slows pipeline
                       progress to a crawl. */

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
    ASSERT_DEBUG(msg->iRefCount > 0);
    (void)msg->Process(*this);
    return msg;
}

void Logger::Push(Msg* aMsg)
{
    (void)aMsg->Process(*this);
    iDownstreamElement->Push(aMsg);
}

Msg* Logger::ProcessMsg(MsgMode* aMsg)
{
    if (IsEnabled(EMsgMode)) {
        Log::Print("Pipeline (%s): mode {mode:", iId);
        Log::Print(aMsg->Mode());
        Log::Print(", supportsLatency: %u, realTime: %u\n", aMsg->SupportsLatency(), aMsg->IsRealTime());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgTrack* aMsg)
{
    if (IsEnabled(EMsgTrack)) {
        Log::Print("Pipeline (%s): track {uri:", iId);
        Log::Print(aMsg->Track().Uri());
        Log::Print(", metaData: ");
#ifdef LOG_METADATA
        Log::Print(aMsg->Track().MetaData());
#else
        Log::Print("(omitted)");
#endif
        Log::Print(", id: %u, pipelineId: %u}\n", aMsg->Track().Id(), aMsg->IdPipeline());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgDelay* aMsg)
{
    if (IsEnabled(EMsgDelay)) {
        const TUint jiffies = aMsg->DelayJiffies();
        Log::Print("Pipeline (%s): delay {jiffies: %x, ms: %u}\n", iId, jiffies, jiffies/Jiffies::kJiffiesPerMs);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (IsEnabled(EMsgEncodedStream)) {
        Log::Print("Pipeline (%s): encoded stream {", iId);
        Log::Print(aMsg->Uri());
        Log::Print(", metaText: ");
#ifdef LOG_METADATA
        Log::Print(aMsg->MetaText());
#else
        Log::Print("(omitted)");
#endif
        Log::Print(" , totalBytes: %llu, streamId: %u, seekable: %s, live: %s}\n",
                    aMsg->TotalBytes(), aMsg->StreamId(),
                    (aMsg->Seekable()? "true" : "false"),
                    (aMsg->Live()? "true" : "false"));
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (IsEnabled(EMsgAudioEncoded)) {
        Log::Print("Pipeline (%s): encoded {bytes: %u}\n", iId, aMsg->Bytes());
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
        Log::Print("Pipeline (%s): halt { id: %u }\n", iId, aMsg->Id());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgFlush* aMsg)
{
    if (IsEnabled(EMsgFlush)) {
        Log::Print("Pipeline (%s): flush { id: %u }\n", iId, aMsg->Id());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgWait* aMsg)
{
    if (IsEnabled(EMsgWait)) {
        Log::Print("Pipeline (%s): wait\n", iId);
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