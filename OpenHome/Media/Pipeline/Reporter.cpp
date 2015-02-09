#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Reporter

const Brn Reporter::kNullMetaText("");

Reporter::Reporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver)
    : iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iTimeInvalid(true)
    , iSeconds(0)
    , iJiffies(0)
    , iTrackDurationSeconds(0)
{
}

Reporter::~Reporter()
{
}

Msg* Reporter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

Msg* Reporter::ProcessMsg(MsgMode* aMsg)
{
    iMode.Replace(aMsg->Mode());
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgTrack* aMsg)
{
    iSeconds = 0;
    iJiffies = 0;
    iObserver.NotifyTrack(aMsg->Track(), iMode);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgDelay* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERTS(); // don't expect to see MsgEncodedStream at this stage of the pipeline
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* Reporter::ProcessMsg(MsgMetaText* aMsg)
{
    iObserver.NotifyMetaText(aMsg->MetaText());
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgHalt* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgFlush at this stage of the pipeline
    return NULL;
}

Msg* Reporter::ProcessMsg(MsgWait* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iTimeInvalid = true;
    iTrackDurationSeconds = (TUint)(streamInfo.TrackLength() / Jiffies::kPerSecond);
    TUint64 jiffies = (streamInfo.SampleStart() * Jiffies::kPerSecond) / streamInfo.SampleRate();
    iSeconds = (TUint)(jiffies / Jiffies::kPerSecond);
    iJiffies = jiffies % Jiffies::kPerSecond;
    iObserver.NotifyStreamInfo(streamInfo);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    TBool reportChange = false;
    if (iTimeInvalid) {
        const TUint64 offset = aMsg->TrackOffset() + aMsg->Jiffies();
        iSeconds = (TUint)(offset / Jiffies::kPerSecond);
        iJiffies = offset % Jiffies::kPerSecond;
        iTimeInvalid = false;
        reportChange = true;
    }
    else {
        iJiffies += aMsg->Jiffies();
        while (iJiffies > Jiffies::kPerSecond) {
            reportChange = true;
            iSeconds++;
            iJiffies -= Jiffies::kPerSecond;
        }
    }
    if (reportChange) {
        iObserver.NotifyTime(iSeconds, iTrackDurationSeconds);
    }
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgSilence* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS(); // don't expect to see MsgPlayable in the pipeline
    return NULL;
}

Msg* Reporter::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
