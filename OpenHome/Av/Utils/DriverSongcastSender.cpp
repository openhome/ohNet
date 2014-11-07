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


// ProcessorPcmBufPackedDualMono

ProcessorPcmBufPackedDualMono::ProcessorPcmBufPackedDualMono()
{
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment8(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment16(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

TBool ProcessorPcmBufPackedDualMono::ProcessFragment24(const Brx& /*aData*/, TUint /*aNumChannels*/)
{
    return false;
}

void ProcessorPcmBufPackedDualMono::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        for (TUint i=0; i<aNumChannels; i++) {
            Brn sampleBuf(aSample, 1);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, aNumChannels);
        ProcessFragment(sample);
    }
}

void ProcessorPcmBufPackedDualMono::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        const TByte* sampleStart = aSample;
        TByte sample[2] = { 0 };
        for (TUint i=0; i<aNumChannels; i++) {
            aSample = sampleStart;
            sample[0] = *aSample;
            aSample++;
            sample[1] = *aSample;
            aSample++;
            Brn sampleBuf(sample, 2);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, 2*aNumChannels);
        ProcessFragment(sample);
    }
}

void ProcessorPcmBufPackedDualMono::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    if (aNumChannels == 1) {
        aNumChannels = 2;
        const TByte* sampleStart = aSample;
        TByte sample[3] = { 0 };
        for (TUint i=0; i<aNumChannels; i++) {
            aSample = sampleStart;
            sample[0] = *aSample;
            aSample++;
            sample[1] = *aSample;
            aSample++;
            sample[2] = *aSample;
            aSample++;
            Brn sampleBuf(sample, 3);
            ProcessFragment(sampleBuf);
        }
    }
    else {
        Brn sample(aSample, 3*aNumChannels);
        ProcessFragment(sample);
    }
}


// DriverSongcastSender

const Brn DriverSongcastSender::kSenderIconFileName("SongcastSenderIcon");

DriverSongcastSender::DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvStack& aDvStack, const Brx& aName, TUint aChannel)
    : Thread("SongcastingDriver")
    , iPipeline(aPipeline)
    , iMaxMsgSizeJiffies(aMaxMsgSizeJiffies)
    , iEnv(aDvStack.Env())
    , iDeviceDisabled("DSCS", 0)
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffiesToSend(aMaxMsgSizeJiffies)
    , iTimerFrequencyMs(aMaxMsgSizeJiffies / Jiffies::kPerMs)
    , iLastTimeUs(0)
    , iTimeOffsetUs(0)
    , iPlayable(NULL)
    , iAudioSent(false)
    , iQuit(false)
{
    ASSERT(aMaxMsgSizeJiffies % Jiffies::kPerMs == 0);
    iOhmSenderDriver = new OhmSenderDriver(iEnv);

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

    iOhmSender = new OhmSender(iEnv, *iDevice, *iOhmSenderDriver, *iZoneHandler, udn, aChannel, kSongcastLatencyMs, false/*unicast*/, kSenderIconFileName);
    iOhmSender->SetEnabled(true);
    iDevice->SetEnabled();
    iTimer = new Timer(iEnv, MakeFunctor(*this, &DriverSongcastSender::TimerCallback), "DriverSongcastSender");
    Start();
    iTimer->FireIn(1); // first callback has special case behaviour so it doesn't really matter how soon we run
}

DriverSongcastSender::~DriverSongcastSender()
{
    Join();
    delete iTimer;
    iDevice->SetDisabled(MakeFunctor(*this, &DriverSongcastSender::DeviceDisabled));
    iDeviceDisabled.Wait();
    delete iOhmSender;
    delete iOhmSenderDriver;
    delete iDevice;
    delete iZoneHandler;
}

void DriverSongcastSender::Run()
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
                    Wait();
                }
                now = OsTimeInUs(iEnv.OsCtx());
                iAudioSent = false;
                iJiffiesToSend = iMaxMsgSizeJiffies;
            }
            if (iPlayable != NULL) {
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
        if (iPlayable != NULL) {
            iPlayable->RemoveRef();
        }
    }
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
    ProcessorPcmBufPackedDualMono pcmProcessor;
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
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgSession* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
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

Msg* DriverSongcastSender::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return NULL;
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
    iJiffiesPerSample = Jiffies::JiffiesPerSample(iSampleRate);
    iOhmSenderDriver->SetAudioFormat(iSampleRate, stream.BitRate(), reportedChannels, iBitDepth, stream.Lossless(), stream.CodecName());
    aMsg->RemoveRef();
    return NULL;
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

Msg* DriverSongcastSender::ProcessMsg(MsgQuit* aMsg)
{
    iQuit = true;
    aMsg->RemoveRef();
    return NULL;
}

void DriverSongcastSender::WriteResource(const Brx& aUriTail, TIpAddress /*aInterface*/, std::vector<char*>& /*aLanguageList*/, Net::IResourceWriter& aResourceWriter)
{
    if (aUriTail == kSenderIconFileName) {
        aResourceWriter.WriteResourceBegin(sizeof(kIconDriverSongcastSender), kIconDriverSongcastSenderMimeType);
        aResourceWriter.WriteResource(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender));
        aResourceWriter.WriteResourceEnd();
    }
}
