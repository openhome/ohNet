#include <OpenHome/Media/DriverSongcastSender.h>
#include "IconDriverSongcastSender.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Private/Timer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// DriverSongcastSender

DriverSongcastSender::DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aAdapter)
    : Thread("DSCS")
    , iPipeline(aPipeline)
    , iMaxMsgSizeJiffies(aMaxMsgSizeJiffies)
    , iBuf(NULL)
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffiesToSend(Jiffies::kJiffiesPerMs)
    , iLastSendTime(0)
    , iPlayable(NULL)
    , iAudioSent(false)
    , iQuit(false)
    , iTotalBytesSent(0)
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
    const TUint numSamples = aMsg->Bytes() / (DecodedAudio::kBytesPerSubsample * iNumChannels);
    TUint jiffies = numSamples * iJiffiesPerSample;
    if (jiffies >= iJiffiesToSend) {
        iAudioSent = true;
        if (jiffies > iJiffiesToSend) {
            jiffies = iJiffiesToSend;
            const TUint bytes = Jiffies::BytesFromJiffies(jiffies, iJiffiesPerSample, iNumChannels, DecodedAudio::kBytesPerSubsample);
            if (bytes == 0) {
                iPlayable = aMsg;
                return;
            }
            iPlayable = aMsg->Split(bytes);
        }
    }
    iJiffiesToSend -= jiffies;
    aMsg->CopyTo(iBuf);
    iTotalBytesSent += aMsg->Bytes();
//    Log::Print("SendAudio sending %d bytes (%d total)\n", aMsg->Bytes(), iTotalBytesSent);
    iOhmSenderDriver->SendAudio(iBuf, aMsg->Bytes());
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
    iJiffiesPerSample = Jiffies::JiffiesPerSample(iSampleRate);
    TUint jiffies = iMaxMsgSizeJiffies;
    const TUint bufMaxSize = Jiffies::BytesFromJiffies(jiffies, iJiffiesPerSample, iNumChannels, DecodedAudio::kBytesPerSubsample);
    delete[] iBuf;
    iBuf = new TByte[bufMaxSize];
    iOhmSenderDriver->SetAudioFormat(fmt.SampleRate(), fmt.BitRate(), fmt.NumChannels(), fmt.BitDepth(), fmt.Lossless(), fmt.CodecName());
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
