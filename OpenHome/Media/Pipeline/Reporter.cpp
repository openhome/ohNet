#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Pipeline/ElementObserver.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Reporter

const Brn Reporter::kNullMetaText("");

Reporter::Reporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver, IPipelineElementObserverThread& aObserverThread)
    : iLock("RPTR")
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iObserverThread(aObserverThread)
    , iMsgMode(NULL)
    , iMsgTrack(NULL)
    , iMsgDecodedStreamInfo(NULL)
    , iMsgMetaText(NULL)
    , iSeconds(0)
    , iJiffies(0)
    , iTrackDurationSeconds(0)
    , iNotifyTime(false)
{
    iEventId = iObserverThread.Register(MakeFunctor(*this, &Reporter::EventCallback));
}

Reporter::~Reporter()
{
    if (iMsgMode != NULL) {
        iMsgMode->RemoveRef();
    }
    if (iMsgTrack != NULL) {
        iMsgTrack->RemoveRef();
    }
    if (iMsgDecodedStreamInfo != NULL) {
        iMsgDecodedStreamInfo->RemoveRef();
    }
    if (iMsgMetaText != NULL) {
        iMsgMetaText->RemoveRef();
    }
}

Msg* Reporter::Pull()
{
    Msg* msg = iUpstreamElement.Pull();
    (void)msg->Process(*this);
    return msg;
}

Msg* Reporter::ProcessMsg(MsgMode* aMsg)
{
    AutoMutex _(iLock);
    iMode.Replace(aMsg->Mode());
    if (iMsgMode != NULL) {
        iMsgMode->RemoveRef();
    }
    iMsgMode = aMsg;
    iMsgMode->AddRef();
    if (iMsgTrack != NULL) {
        iMsgTrack->RemoveRef();
        iMsgTrack = NULL;
    }
    if (iMsgDecodedStreamInfo != NULL) {
        iMsgDecodedStreamInfo->RemoveRef();
        iMsgDecodedStreamInfo = NULL;
    }
    if (iMsgMetaText != NULL) {
        iMsgMetaText->RemoveRef();
        iMsgMetaText = NULL;
    }
    iNotifyTime = false;
    iObserverThread.Schedule(iEventId);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgSession* aMsg)
{
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgTrack* aMsg)
{
    AutoMutex _(iLock);
    if (iMsgTrack != NULL) {
        iMsgTrack->RemoveRef();
    }
    iMsgTrack = aMsg;
    iMsgTrack->AddRef();
    iModeTrack.Replace(iMode);
    if (aMsg->StartOfStream()) {
        if (iMsgDecodedStreamInfo != NULL) {
            iMsgDecodedStreamInfo->RemoveRef();
            iMsgDecodedStreamInfo = NULL;
        }
        if (iMsgMetaText != NULL) {
            iMsgMetaText->RemoveRef();
            iMsgMetaText = NULL;
        }
        iNotifyTime = false;
    }
    iObserverThread.Schedule(iEventId);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgChangeInput* aMsg)
{
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
    AutoMutex _(iLock);
    if (iMsgMetaText != NULL) {
        iMsgMetaText->RemoveRef();
    }
    iMsgMetaText = aMsg;
    iMsgMetaText->AddRef();
    iObserverThread.Schedule(iEventId);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgStreamInterrupted* aMsg)
{
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
    AutoMutex _(iLock);
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iTrackDurationSeconds = (TUint)(streamInfo.TrackLength() / Jiffies::kPerSecond);
    TUint64 jiffies = (streamInfo.SampleStart() * Jiffies::kPerSecond) / streamInfo.SampleRate();
    iSeconds = (TUint)(jiffies / Jiffies::kPerSecond);
    iJiffies = jiffies % Jiffies::kPerSecond;
    if (iMsgDecodedStreamInfo != NULL) {
        iMsgDecodedStreamInfo->RemoveRef();
    }
    iMsgDecodedStreamInfo = aMsg;
    iMsgDecodedStreamInfo->AddRef();
    iNotifyTime = true;
    iObserverThread.Schedule(iEventId);
    return aMsg;
}

Msg* Reporter::ProcessMsg(MsgAudioPcm* aMsg)
{
    AutoMutex _(iLock);
    TBool reportChange = false;
    iJiffies += aMsg->Jiffies();
    while (iJiffies > Jiffies::kPerSecond) {
        reportChange = true;
        iSeconds++;
        iJiffies -= Jiffies::kPerSecond;
    }
    if (reportChange) {
        iNotifyTime= true;
        iObserverThread.Schedule(iEventId);
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

void Reporter::EventCallback()
{
    iLock.Wait();
    MsgMode* msgMode = iMsgMode;
    iMsgMode = NULL;
    MsgTrack* msgTrack = iMsgTrack;
    BwsMode modeTrack(iModeTrack);
    iMsgTrack = NULL;
    MsgDecodedStream* msgStream = iMsgDecodedStreamInfo;
    iMsgDecodedStreamInfo = NULL;
    MsgMetaText* msgMetatext = iMsgMetaText;
    iMsgMetaText = NULL;
    const TUint seconds = iSeconds;
    const TUint trackDurationSeconds = iTrackDurationSeconds;
    const TBool notifyTime = iNotifyTime;
    iNotifyTime = false;
    iLock.Signal();

    if (msgMode != NULL) {
        iObserver.NotifyMode(msgMode->Mode(), msgMode->Info());
        msgMode->RemoveRef();
    }
    if (msgTrack != NULL) {
        iObserver.NotifyTrack(msgTrack->Track(), modeTrack, msgTrack->StartOfStream());
        msgTrack->RemoveRef();
    }
    if (msgStream != NULL) {
        iObserver.NotifyStreamInfo(msgStream->StreamInfo());
        msgStream->RemoveRef();
    }
    if (msgMetatext != NULL) {
        iObserver.NotifyMetaText(msgMetatext->MetaText());
        msgMetatext->RemoveRef();
    }
    if (notifyTime) {
        iObserver.NotifyTime(seconds, trackDurationSeconds);
    }
}
