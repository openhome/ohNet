#include <OpenHome/Av/Utils/DriverSongcastSender.h>
#include "IconDriverSongcastSender.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;


// DriverSongcastSender

const Brn DriverSongcastSender::kSenderIconFileName("SongcastSenderIcon");

const TUint DriverSongcastSender::kSupportedMsgTypes =   eMode
                                                       | eDrain
                                                       | eHalt
                                                       | eDecodedStream
                                                       | ePlayable
                                                       | eQuit;

DriverSongcastSender::DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvStack& aDvStack, const Brx& aName, TUint aChannel)
    : PipelineElement(kSupportedMsgTypes)
    , iPipeline(aPipeline)
    , iMaxMsgSizeJiffies(aMaxMsgSizeJiffies)
    , iEnv(aDvStack.Env())
    , iDeviceDisabled("DSCS", 0)
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffiesToSend(aMaxMsgSizeJiffies)
    , iTimerFrequencyMs(Jiffies::ToMs(aMaxMsgSizeJiffies))
    , iLastTimeUs(0)
    , iTimeOffsetUs(0)
    , iPlayable(nullptr)
    , iAudioSent(false)
    , iQuit(false)
{
    ASSERT(aMaxMsgSizeJiffies % Jiffies::kPerMs == 0);
    iOhmSenderDriver = new OhmSenderDriver(iEnv, nullptr, nullptr);

    Bws<64> udn("Driver-");
    udn.Append(aName);
    Log::Print("Songcasting driver is ");
    Log::Print(udn);
    Log::Print("\n");
    iDevice = new Net::DvDeviceStandard(aDvStack, udn, *this);
    iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Songcast");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", "Songcasting Driver (media player test)");
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "ohMediaPlayer");
    iDevice->SetAttribute("Upnp.ModelName", "ohMediaPlayer");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iZoneHandler = new ZoneHandler(iEnv, udn);

    iOhmSender = new OhmSender(iEnv, *iDevice, *iOhmSenderDriver, *iZoneHandler, kPriorityHigh, udn, aChannel, kSongcastLatencyMs, false/*unicast*/);
    iOhmSender->SetEnabled(true);
    iDevice->SetEnabled();
    iTimer = new Timer(iEnv, MakeFunctor(*this, &DriverSongcastSender::TimerCallback), "DriverSongcastSender");
    iThread = new ThreadFunctor("PipelineAnimator", MakeFunctor(*this, &DriverSongcastSender::DriverThread), kPrioritySystemHighest);
    iThread->Start();
    iTimer->FireIn(1); // first callback has special case behaviour so it doesn't really matter how soon we run
}

DriverSongcastSender::~DriverSongcastSender()
{
    delete iThread;
    delete iTimer;
    iDevice->SetDisabled(MakeFunctor(*this, &DriverSongcastSender::DeviceDisabled));
    iDeviceDisabled.Wait();
    delete iOhmSender;
    delete iOhmSenderDriver;
    delete iDevice;
    delete iZoneHandler;
}

void DriverSongcastSender::DriverThread()
{
    // pull the first (assumed non-audio) msg here so that any delays populating the pipeline don't affect timing calculations below.
    Msg* msg = iPipeline.Pull();
    (void)msg->Process(*this);

    TUint64 now = OsTimeInUs(iEnv.OsCtx());
    try {
        while(!iQuit) {
            if (iAudioSent) {
                TBool noWait = false;
                // skip the first packet, and any time the clock value wraps
                if (iLastTimeUs == 0 || iLastTimeUs >= now) {
                    iTimer->FireIn(iTimerFrequencyMs);
                }
                else {
                    TUint nextTimerMs = iTimerFrequencyMs;
                    TInt diff = (TInt)(now - iLastTimeUs) - (iTimerFrequencyMs * 1000); // the difference in usec from where we should be
                    iTimeOffsetUs -= diff; // increment running offset

                    // determine new timer value based upon current offset from ideal
                    if (iTimeOffsetUs < -1000) { // we are late
                        TUint32 timeOffsetMs = ((TUint32)(-iTimeOffsetUs))/1000;
                        if (timeOffsetMs > 8 * iTimerFrequencyMs) {
                            // we're miles behind, probably as a result of drop-outs
                            // don't even try to catch up
                            iTimeOffsetUs = 0;
                        }
                        else if (timeOffsetMs > iTimerFrequencyMs) {
                            // callback is more than a full cycle late; try pulling more audio imediately
                            noWait = true;
                        }
                        else {
                            nextTimerMs = iTimerFrequencyMs + timeOffsetMs;
                        }
                    }
                    else if (iTimeOffsetUs > 1000) { // we are early
                        nextTimerMs = iTimerFrequencyMs+1;
                    }
                    else { // we are about on time
                        nextTimerMs = iTimerFrequencyMs;
                    }
                    iTimer->FireIn(nextTimerMs);
                }
                if (noWait) {
                    iLastTimeUs += iMaxMsgSizeJiffies;
                }
                else {
                    iLastTimeUs = now;
                    iThread->Wait();
                }
                now = OsTimeInUs(iEnv.OsCtx());
                iAudioSent = false;
                iJiffiesToSend = iMaxMsgSizeJiffies;
            }
            if (iPlayable != nullptr) {
                SendAudio(iPlayable);
            }
            else {
                Msg* msg = iPipeline.Pull();
                (void)msg->Process(*this);
            }
        }
    }
    catch (ThreadKill&) {}

    // pull until the pipeline is emptied
    while (!iQuit) {
        Msg* msg = iPipeline.Pull();
        (void)msg->Process(*this);
        if (iPlayable != nullptr) {
            iPlayable->RemoveRef();
        }
    }
}

void DriverSongcastSender::TimerCallback()
{
    iThread->Signal();
}

void DriverSongcastSender::SendAudio(MsgPlayable* aMsg)
{
    iPlayable = nullptr;
    const TUint numSamples = aMsg->Bytes() / ((iBitDepth/8) * iNumChannels);
    TUint jiffies = numSamples * iJiffiesPerSample;
    if (jiffies >= iJiffiesToSend) {
        iAudioSent = true;
        if (jiffies > iJiffiesToSend) {
            jiffies = iJiffiesToSend;
            const TUint bytes = Jiffies::ToBytes(jiffies, iJiffiesPerSample, iNumChannels, (iBitDepth/8));
            if (bytes == 0) {
                iPlayable = aMsg;
                return;
            }
            iPlayable = aMsg->Split(bytes);
        }
    }
    iJiffiesToSend -= jiffies;
    ProcessorPcmBufTest pcmProcessor;
    aMsg->Read(pcmProcessor);
    Brn buf = pcmProcessor.Buf();
    const TUint numSubsamples = buf.Bytes() / (iBitDepth/8);
    iOhmSenderDriver->SendAudio(buf.Ptr(), numSubsamples * (iBitDepth/8));
    aMsg->RemoveRef();
}

void DriverSongcastSender::DeviceDisabled()
{
    iDeviceDisabled.Signal();
}

Msg* DriverSongcastSender::ProcessMsg(MsgMode* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* DriverSongcastSender::ProcessMsg(MsgDrain* aMsg)
{
    return aMsg;
}

Msg* DriverSongcastSender::ProcessMsg(MsgHalt* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* DriverSongcastSender::ProcessMsg(MsgDecodedStream* aMsg)
{
    const DecodedStreamInfo& stream = aMsg->StreamInfo();
    iSampleRate = stream.SampleRate();
    iNumChannels = stream.NumChannels();
    TUint reportedChannels = iNumChannels;
    if (reportedChannels == 1) {
        reportedChannels = 2;   // output mono as stereo
    }
    iBitDepth = stream.BitDepth();
    iJiffiesPerSample = Jiffies::PerSample(iSampleRate);
    iOhmSenderDriver->SetAudioFormat(iSampleRate, stream.BitRate(), reportedChannels,
                                     iBitDepth, stream.Lossless(), stream.CodecName(),
                                     stream.SampleStart());
    aMsg->RemoveRef();
    return nullptr;
}

Msg* DriverSongcastSender::ProcessMsg(MsgPlayable* aMsg)
{
    SendAudio(aMsg);
    return nullptr;
}

Msg* DriverSongcastSender::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    aMsg->RemoveRef();
    return nullptr;
}

void DriverSongcastSender::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, Net::IResourceWriter& aResourceWriter)
{
    if (aUriTail == kSenderIconFileName) {
        aResourceWriter.WriteResourceBegin(sizeof(kIconDriverSongcastSender), kIconDriverSongcastSenderMimeType);
        aResourceWriter.WriteResource(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender));
        aResourceWriter.WriteResourceEnd();
    }
}
