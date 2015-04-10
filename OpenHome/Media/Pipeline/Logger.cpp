#include <OpenHome/Media/Pipeline/Logger.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

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
    ASSERT(msg != NULL);
    ASSERT_DEBUG(msg->iRefCount > 0);
    (void)msg->Process(*this);
    return msg;
}

void Logger::Push(Msg* aMsg)
{
    ASSERT(aMsg != NULL);
    (void)aMsg->Process(*this);
    iDownstreamElement->Push(aMsg);
}

Msg* Logger::ProcessMsg(MsgMode* aMsg)
{
    if (IsEnabled(EMsgMode)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): mode {mode:", iId);
        iBuf.Append(aMsg->Mode());
        iBuf.AppendPrintf(", supportsLatency: %u, realTime: %u}\n", aMsg->SupportsLatency(), aMsg->IsRealTime());
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgSession* aMsg)
{
    if (IsEnabled(EMsgSession)) {
        Log::Print("Pipeline (%s): session\n", iId);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgTrack* aMsg)
{
    if (IsEnabled(EMsgTrack)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): track {uri:", iId);
        iBuf.Append(aMsg->Track().Uri());
        iBuf.Append(", metaData: ");
#ifdef LOG_METADATA
        iBuf.Append(aMsg->Track().MetaData());
#else
        iBuf.Append("(omitted)");
#endif
        iBuf.AppendPrintf(", id: %u, startOfStream: %u}\n", aMsg->Track().Id(), aMsg->StartOfStream());
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgDelay* aMsg)
{
    if (IsEnabled(EMsgDelay)) {
        const TUint jiffies = aMsg->DelayJiffies();
        Log::Print("Pipeline (%s): delay {jiffies: %x, ms: %u}\n", iId, jiffies, jiffies/Jiffies::kPerMs);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (IsEnabled(EMsgEncodedStream)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): encodedStream {", iId);
        iBuf.Append(aMsg->Uri());
        iBuf.Append(", metaText: ");
#ifdef LOG_METADATA
        iBuf.Append(aMsg->MetaText());
#else
        iBuf.Append("(omitted)");
#endif
        iBuf.AppendPrintf(" , totalBytes: %llu, streamId: %u, seekable: %s, live: %s}\n",
                          aMsg->TotalBytes(), aMsg->StreamId(),
                          (aMsg->Seekable()? "true" : "false"),
                          (aMsg->Live()? "true" : "false"));
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (IsEnabled(EMsgAudioEncoded)) {
        Log::Print("Pipeline (%s): audioEncoded {bytes: %u}\n", iId, aMsg->Bytes());
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgMetaText* aMsg)
{
    if (IsEnabled(EMsgMetaText)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): metaText {", iId);
        iBuf.Append(aMsg->MetaText());
        iBuf.AppendPrintf("}\n");
        Log::Print(iBuf);
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
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): decodedStream {streamId: %u, bitRate: %u, bitDepth: %u, sampleRate: %u, codec: ",
                           iId, stream.StreamId(), stream.BitRate(), stream.BitDepth(), stream.SampleRate());
        iBuf.Append(stream.CodecName());
        iBuf.AppendPrintf(", trackLength: %llu, sampleStart: %u, lossless: %s}\n", stream.TrackLength(), stream.SampleStart(), (stream.Lossless()? "true" : "false"));
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgAudioPcm* aMsg)
{
    if (IsEnabled(EMsgAudioPcm)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): audioPcm {jiffies: %u}", iId, aMsg->Jiffies());
        LogRamp(aMsg->Ramp());
        iBuf.Append("\n");
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgSilence* aMsg)
{
    if (IsEnabled(EMsgSilence)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): silence {jiffies: %u}", iId, aMsg->Jiffies());
        LogRamp(aMsg->Ramp());
        iBuf.Append("\n");
        Log::Print(iBuf);
    }
    return aMsg;
}

Msg* Logger::ProcessMsg(MsgPlayable* aMsg)
{
    if (IsEnabled(EMsgPlayable)) {
        iBuf.SetBytes(0);
        iBuf.AppendPrintf("Pipeline (%s): playable {bytes: %u}", iId, aMsg->Bytes());
        LogRamp(aMsg->Ramp());
        iBuf.Append("\n");
        Log::Print(iBuf);
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
        iBuf.AppendPrintf(", {ramp: [%08x..%08x]}", aRamp.Start(), aRamp.End());
    }
}

TBool Logger::IsEnabled(EMsgType aType) const
{
    if (iEnabled && (iFilter & aType) == aType) {
        return true;
    }
    return false;
}
