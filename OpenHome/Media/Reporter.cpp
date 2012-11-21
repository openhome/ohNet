#include <OpenHome/Media/Reporter.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>

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

Msg* Reporter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

Msg* Reporter::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS(); /* only expect to deal with decoded audio at this stage of the pipeline */
    return NULL;
}

Msg* Reporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    TBool reportChange = false;
    if (iTimeInvalid) {
        const TUint64 offset = aMsg->TrackOffset() + aMsg->Jiffies();
        iSeconds = (TUint)(offset / Jiffies::kJiffiesPerSecond);
        iJiffies = offset % Jiffies::kJiffiesPerSecond;
        iTimeInvalid = false;
        reportChange = true;
    }
    else {
        iJiffies += aMsg->Jiffies();
        while (iJiffies > Jiffies::kJiffiesPerSecond) {
            reportChange = true;
            iSeconds++;
            iJiffies -= Jiffies::kJiffiesPerSecond;
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

Msg* Reporter::ProcessMsg(MsgAudioFormat* aMsg)
{
    iTimeInvalid = true;
    iTrackDurationSeconds = (TUint)(aMsg->Format().TrackLength() / Jiffies::kJiffiesPerSecond);
    iObserver.NotifyAudioFormat(aMsg->Format());
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgTrack* aMsg)
{
    iSeconds = 0;
    iJiffies = 0;
    iObserver.NotifyTrack();
    iObserver.NotifyMetaText(kNullMetaText);
    return aMsg;
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

Msg* Reporter::ProcessMsg(MsgQuit* aMsg)
{
    return aMsg;
}
