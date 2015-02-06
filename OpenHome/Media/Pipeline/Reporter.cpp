#include <OpenHome/Media/Pipeline/Reporter.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// Reporter

const Brn Reporter::kNullMetaText("");

Reporter::Reporter(IPipelineElementUpstream& aUpstreamElement, IPipelinePropertyObserver& aObserver, TUint aObserverThreadPriority)
    : iLock("RPTR")
    , iUpstreamElement(aUpstreamElement)
    , iObserver(aObserver)
    , iMsgTrack(NULL)
    , iMsgDecodedStreamInfo(NULL)
    , iMsgMetaText(NULL)
    , iSeconds(0)
    , iJiffies(0)
    , iTrackDurationSeconds(0)
    , iNotifyTime(false)
{
    iThread = new ThreadFunctor("ReporterObserver", MakeFunctor(*this, &Reporter::ObserverThread), aObserverThreadPriority);
    iThread->Start();
}

Reporter::~Reporter()
{
    delete iThread;
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
    iMode.Replace(aMsg->Mode());
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
    iThread->Signal();
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
    iThread->Signal();
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
    iThread->Signal();
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
        iThread->Signal();
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

void Reporter::ObserverThread()
{
    for (;;) {
        iThread->Wait();
        iLock.Wait();
        if (iMsgTrack != NULL) {
            MsgTrack* msg = iMsgTrack;
            iMsgTrack = NULL;
            iLock.Signal();
            iObserver.NotifyTrack(msg->Track(), iModeTrack);
            msg->RemoveRef();
            iLock.Wait();
        }
        if (iMsgDecodedStreamInfo != NULL) {
            MsgDecodedStream* msg = iMsgDecodedStreamInfo;
            iMsgDecodedStreamInfo = NULL;
            iLock.Signal();
            iObserver.NotifyStreamInfo(msg->StreamInfo());
            msg->RemoveRef();
            iLock.Wait();
        }
        if (iMsgMetaText != NULL) {
            MsgMetaText* msg = iMsgMetaText;
            iMsgMetaText = NULL;
            iLock.Signal();
            iObserver.NotifyMetaText(msg->MetaText());
            msg->RemoveRef();
            iLock.Wait();
        }
        if (iNotifyTime) {
            const TUint seconds = iSeconds;
            const TUint trackDurationSeconds = iTrackDurationSeconds;
            iNotifyTime = false;
            iLock.Signal();
            iObserver.NotifyTime(seconds, trackDurationSeconds);
            iLock.Wait();
        }
        iLock.Signal();
    }
}
