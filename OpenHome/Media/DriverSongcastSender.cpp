#include <OpenHome/Media/DriverSongcastSender.h>
#include "IconDriverSongcastSender.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DriverSongcastSender

DriverSongcastSender::DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aAdapter)
    : Thread("DSCS")
    , iPipeline(aPipeline)
    , iMaxMsgSizeJiffies(aMaxMsgSizeJiffies)
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffiesToSend(Jiffies::kJiffiesPerMs)
    , iLastSendTime(0)
    , iPlayable(NULL)
    , iAudioSent(false)
    , iQuit(false)
{
    iOhmSenderDriver = new Av::OhmSenderDriver();
    Brn imageData(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender) / sizeof(kIconDriverSongcastSender[0]));
    Brn imageMime(kIconDriverSongcastSenderMimeType);
    iOhmSender = new Av::OhmSender(aDevice, *iOhmSenderDriver, aName, aChannel, aAdapter, kSongcastTtl, kSongcastLatencyMs, false, true, imageData, imageMime, kSongcastPreset);
    iTimer = new Timer(MakeFunctor(*this, &DriverSongcastSender::TimerCallback));
    Start();
    iTimer->FireIn(1); // first callback has special case behaviour so it doesn't really matter how soon we run
}

DriverSongcastSender::~DriverSongcastSender()
{
    Join();
    delete iTimer;
    delete iOhmSender;
    delete iOhmSenderDriver;
}

void DriverSongcastSender::Run()
{
    do {
        if (iAudioSent) {
            iTimer->FireIn(5);
            Wait();
            iAudioSent = false;
            const TUint timeNow = Os::TimeInMs();
            if (iLastSendTime != 0) {
                iJiffiesToSend += (timeNow - iLastSendTime) * Jiffies::kJiffiesPerMs; // FIXME - very low priority but doesn't handle clock wrapping
            }
//            Log::Print("%ums on, trying to send %dms of data\n", timeNow - iLastSendTime, iJiffiesToSend/Jiffies::kJiffiesPerMs);
            iLastSendTime = timeNow;
        }
        if (iPlayable != NULL) {
            SendAudio(iPlayable);
        }
        else {
            Msg* msg = iPipeline.Pull();
            (void)msg->Process(*this);
        }
    } while (!iQuit);
}

void DriverSongcastSender::TimerCallback()
{
    Signal();
}

void DriverSongcastSender::SendAudio(MsgPlayable* aMsg)
{
    iPlayable = NULL;
    const TUint numSamples = aMsg->Bytes() / ((iBitDepth/8) * iNumChannels);
    TUint jiffies = numSamples * iJiffiesPerSample;
    if (jiffies >= iJiffiesToSend) {
        iAudioSent = true;
        if (jiffies > iJiffiesToSend) {
            jiffies = iJiffiesToSend;
            const TUint bytes = Jiffies::BytesFromJiffies(jiffies, iJiffiesPerSample, iNumChannels, (iBitDepth/8));
            if (bytes == 0) {
                iPlayable = aMsg;
                return;
            }
            iPlayable = aMsg->Split(bytes);
        }
    }
    iJiffiesToSend -= jiffies;
    ProcessorPcmBufPacked pcmProcessor;
    aMsg->Read(pcmProcessor);
    Brn buf = pcmProcessor.Buf();
    const TUint numSubsamples = buf.Bytes() / (iBitDepth/8);
    iOhmSenderDriver->SendAudio(buf.Ptr(), numSubsamples * (iBitDepth/8));
    aMsg->RemoveRef();
}

Msg* DriverSongcastSender::ProcessMsg(MsgAudioPcm* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgSilence* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgPlayable* aMsg)
{
    SendAudio(aMsg);
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgAudioFormat* aMsg)
{
    const AudioFormat& fmt = aMsg->Format();
    iSampleRate = fmt.SampleRate();
    iNumChannels = fmt.NumChannels();
    iBitDepth = fmt.BitDepth();
    iJiffiesPerSample = Jiffies::JiffiesPerSample(iSampleRate);
    iOhmSenderDriver->SetAudioFormat(iSampleRate, fmt.BitRate(), iNumChannels, iBitDepth, fmt.Lossless(), fmt.CodecName());
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->RemoveRef();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    aMsg->RemoveRef();
    return NULL;
}
