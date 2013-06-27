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
#include <OpenHome/Private/Env.h>

using namespace OpenHome;
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

DriverSongcastSender::DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Environment& aEnv, Net::DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aAdapter, TBool aMulticast)
    : Thread("DSCS")
    , iPipeline(aPipeline)
    , iMaxMsgSizeJiffies(aMaxMsgSizeJiffies)
    , iEnv(aEnv)
    , iSampleRate(0)
    , iNumChannels(0)
    , iJiffiesToSend(aMaxMsgSizeJiffies)
    , iTimerFrequencyMs(aMaxMsgSizeJiffies / Jiffies::kJiffiesPerMs)
    , iLastTimeUs(0)
    , iTimeOffsetUs(0)
    , iPlayable(NULL)
    , iAudioSent(false)
    , iQuit(false)
{
    ASSERT(aMaxMsgSizeJiffies % Jiffies::kJiffiesPerMs == 0);
    iOhmSenderDriver = new Av::OhmSenderDriver(aEnv);
    Brn imageData(kIconDriverSongcastSender, sizeof(kIconDriverSongcastSender) / sizeof(kIconDriverSongcastSender[0]));
    Brn imageMime(kIconDriverSongcastSenderMimeType);
    iOhmSender = new Av::OhmSender(iEnv, aDevice, *iOhmSenderDriver, aName, aChannel, aAdapter, kSongcastTtl, kSongcastLatencyMs, aMulticast, true, imageData, imageMime, kSongcastPreset);
    iTimer = new Timer(iEnv, MakeFunctor(*this, &DriverSongcastSender::TimerCallback));
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
    // pull the first (assumed non-audio) msg here so that any delays populating the pipeline don't affect timing calculations below.
    Msg* msg = iPipeline.Pull();
    (void)msg->Process(*this);

    TUint64 now = OsTimeInUs(iEnv.OsCtx());
    while(!iQuit) {
        if (iAudioSent) {
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
                    TInt32 timeOffsetMs = iTimeOffsetUs/1000;
                    if (timeOffsetMs < 4 * (TInt32)iTimerFrequencyMs) {
                        // we're miles behind, probably as a result of drop-outs
                        // don't even try to catch up
                        iTimeOffsetUs = 0;
                    }
                    else if (timeOffsetMs < 1-(TInt32)iTimerFrequencyMs) {
                        // in case callback is pretty late, we can only catch up so much
                        nextTimerMs = 1;
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
            iLastTimeUs = now;
            Wait();
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

Msg* DriverSongcastSender::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
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

Msg* DriverSongcastSender::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* DriverSongcastSender::ProcessMsg(MsgEncodedStream* /*aMsg*/)
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
