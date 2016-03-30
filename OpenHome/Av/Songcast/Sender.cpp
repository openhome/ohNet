#include <OpenHome/Av/Songcast/Sender.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/StringIds.h>
#include <OpenHome/Media/ClockPuller.h>

#include <vector>
#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;


enum StringIdsSongcastMode
{
    eStringIdSongcastModeMulticast
   ,eStringIdSongcastModeUnicast
};

// Sender

const Brn Sender::kConfigIdEnabled("Sender.Enabled");
const Brn Sender::kConfigIdChannel("Sender.Channel");
const Brn Sender::kConfigIdMode("Sender.Mode");
const Brn Sender::kConfigIdPreset("Sender.Preset");

Sender::Sender(Environment& aEnv,
               Net::DvDeviceStandard& aDevice,
               ZoneHandler& aZoneHandler,
               IOhmTimestamper* aTimestamper,
               IOhmTimestampMapper* aTsMapper,
               Configuration::IConfigInitialiser& aConfigInit,
               TUint aThreadPriority,
               const Brx& aName,
               TUint aMinLatencyMs,
               const Brx& aIconFileName)
    : iAudioBuf(nullptr)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
    , iMinLatencyMs(aMinLatencyMs)
{
    const TInt defaultChannel = (TInt)aEnv.Random(kChannelMax, kChannelMin);
    iOhmSenderDriver = new OhmSenderDriver(aEnv, aTimestamper, aTsMapper);
    // create sender with default configuration.  CongfigVals below will each call back on construction, allowing these to be updated
    iOhmSender = new OhmSender(aEnv, aDevice, *iOhmSenderDriver, aZoneHandler, aThreadPriority,
                               aName, defaultChannel, aMinLatencyMs, false/*unicast*/, aIconFileName);

    iConfigChannel = new ConfigNum(aConfigInit, kConfigIdChannel, kChannelMin, kChannelMax, defaultChannel);
    iListenerIdConfigChannel = iConfigChannel->Subscribe(MakeFunctorConfigNum(*this, &Sender::ConfigChannelChanged));

    std::vector<TUint> choices;
    choices.push_back(eStringIdSongcastModeMulticast);
    choices.push_back(eStringIdSongcastModeUnicast);
    iConfigMode = new ConfigChoice(aConfigInit, kConfigIdMode, choices, eStringIdSongcastModeUnicast);
    iListenerIdConfigMode = iConfigMode->Subscribe(MakeFunctorConfigChoice(*this, &Sender::ConfigModeChanged));

    iConfigPreset = new ConfigNum(aConfigInit, kConfigIdPreset, kPresetMin, kPresetMax, kPresetNone);
    iListenerIdConfigPreset = iConfigPreset->Subscribe(MakeFunctorConfigNum(*this, &Sender::ConfigPresetChanged));

    choices.clear();
    choices.push_back(eStringIdNo);
    choices.push_back(eStringIdYes);
    iConfigEnabled = new ConfigChoice(aConfigInit, kConfigIdEnabled, choices, eStringIdYes);
    iListenerIdConfigEnabled = iConfigEnabled->Subscribe(MakeFunctorConfigChoice(*this, &Sender::ConfigEnabledChanged));

    iPendingAudio.reserve(100); // arbitrarily chosen value.  Doesn't need to prevent any reallocation, just avoid regular churn early on
}

Sender::~Sender()
{
    delete iOhmSender;
    delete iOhmSenderDriver;
    iConfigEnabled->Unsubscribe(iListenerIdConfigEnabled);
    delete iConfigEnabled;
    iConfigChannel->Unsubscribe(iListenerIdConfigChannel);
    delete iConfigChannel;
    iConfigMode->Unsubscribe(iListenerIdConfigMode);
    delete iConfigMode;
    iConfigPreset->Unsubscribe(iListenerIdConfigPreset);
    delete iConfigPreset;
}

void Sender::SetName(const Brx& aName)
{
    iOhmSender->SetName(aName);
}

void Sender::NotifyPipelineState(EPipelineState aState)
{
    iOhmSender->NotifyAudioPlaying(aState == EPipelinePlaying);
}

void Sender::Push(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    if (msg != nullptr) {
        msg->RemoveRef();
    }
}

Msg* Sender::ProcessMsg(MsgMode* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgTrack* aMsg)
{
    SendPendingAudio();
    Track& track = aMsg->Track();
    iOhmSender->SetTrack(track.Uri(), track.MetaData());
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgDrain* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgDelay* aMsg)
{
    SendPendingAudio();
    const TUint latencyMs = aMsg->DelayJiffies() / Jiffies::kPerMs;
    iOhmSender->SetLatency(std::max(latencyMs, iMinLatencyMs));
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgEncodedStream* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgAudioEncoded* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgMetaText* aMsg)
{
    // don't bother to send pending audio.  It doesn't matter if metatext is processed very slightly out of order
    // (in fact its unavoidable since only audio frames are numbered.  songcast protocol offers no guarantees about
    // when metadata is received/processed relative to text.)
    iOhmSender->SetMetatext(aMsg->MetaText());
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgStreamInterrupted* aMsg)
{
    // FIXME - no way to tell a songcast receiver about a discontinuity that requires a ramp down
    SendPendingAudio(true);
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgHalt* aMsg)
{
    SendPendingAudio(true);
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgFlush* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgWait* aMsg)
{
    SendPendingAudio(true);
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgDecodedStream* aMsg)
{
    // send any pending audio in case the stream msg indicates a discontinuity in the track (probably after a seek?)
    SendPendingAudio();

    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iSampleRate = streamInfo.SampleRate();
    iBitDepth = streamInfo.BitDepth();
    iNumChannels = streamInfo.NumChannels();
    const TUint64 samplesTotal = streamInfo.TrackLength() / Jiffies::JiffiesPerSample(iSampleRate);
    iOhmSender->SetTrackPosition(samplesTotal, streamInfo.SampleStart());
    iOhmSenderDriver->SetAudioFormat(iSampleRate, streamInfo.BitRate(), iNumChannels,
                                     iBitDepth, streamInfo.Lossless(), streamInfo.CodecName(),
                                     streamInfo.SampleStart());

    return aMsg;
}

Msg* Sender::ProcessMsg(MsgBitRate* aMsg)
{
    aMsg->RemoveRef();
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgAudioPcm* aMsg)
{
    ASSERT(iSampleRate != 0);
    ProcessAudio(aMsg);
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgSilence* aMsg)
{
    ASSERT(iSampleRate != 0);
    ProcessAudio(aMsg);
    return nullptr;
}

Msg* Sender::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgQuit* aMsg)
{
    SendPendingAudio(true);
    return aMsg;
}

void Sender::ProcessAudio(MsgAudio* aMsg)
{
    TUint jiffies = 0;
    for (TUint i=0; i<iPendingAudio.size(); i++) {
        jiffies += iPendingAudio[i]->Jiffies();
    }
    TUint newJiffies = jiffies + aMsg->Jiffies();
    if (newJiffies < kSongcastPacketJiffies) {
        iPendingAudio.push_back(aMsg);
        return;
    }
    MsgAudio* msg = aMsg;
    MsgAudio* remaining;
    do {
        remaining = (newJiffies == kSongcastPacketJiffies? nullptr : msg->Split(kSongcastPacketJiffies - jiffies));
        iPendingAudio.push_back(msg);
        SendPendingAudio();
        msg = remaining;
        jiffies = 0;
        newJiffies = (remaining==nullptr? 0 : remaining->Jiffies());
    } while (remaining != nullptr && newJiffies >= kSongcastPacketJiffies);
    if (remaining != nullptr) {
        iPendingAudio.push_back(remaining);
    }
}

void Sender::SendPendingAudio(TBool aHalt)
{
    auto msg = iOhmSenderDriver->CreateAudio();
    iAudioBuf = &(msg->Audio());
    iAudioBuf->SetBytes(0);
    PlayableCreator pc(iSampleRate, iBitDepth, iNumChannels);
    for (TUint i=0; i<iPendingAudio.size(); i++) {
        MsgPlayable* playable = pc.Process(iPendingAudio[i]);
        playable->Read(*this);
        playable->RemoveRef();
    }
    iOhmSenderDriver->SendAudio(msg, aHalt);
    iAudioBuf = nullptr;
    iPendingAudio.clear();
}

void Sender::ConfigEnabledChanged(KeyValuePair<TUint>& aStringId)
{
    const TBool enabled = (aStringId.Value() == eStringIdYes);
    iOhmSender->SetEnabled(enabled);
}

void Sender::ConfigChannelChanged(KeyValuePair<TInt>& aKvp)
{
    iOhmSender->SetChannel(aKvp.Value());
}

void Sender::ConfigModeChanged(KeyValuePair<TUint>& aStringId)
{
    const TBool multicast = (aStringId.Value() == eStringIdSongcastModeMulticast);
    iOhmSender->SetMulticast(multicast);
}

void Sender::ConfigPresetChanged(KeyValuePair<TInt>& aKvp)
{
    iOhmSender->SetPreset(aKvp.Value());
}

void Sender::BeginBlock()
{
    ASSERT(iAudioBuf);
}

void Sender::ProcessFragment8(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf->Append(aData);
}

void Sender::ProcessFragment16(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf->Append(aData);
}

void Sender::ProcessFragment24(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf->Append(aData);
}

void Sender::ProcessFragment32(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf->Append(aData);
}

void Sender::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, aNumChannels);
    iAudioBuf->Append(sample);
}

void Sender::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 2*aNumChannels);
    iAudioBuf->Append(sample);
}

void Sender::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 3*aNumChannels);
    iAudioBuf->Append(sample);
}

void Sender::ProcessSample32(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 4*aNumChannels);
    iAudioBuf->Append(sample);
}

void Sender::EndBlock()
{
}

void Sender::Flush()
{
}


// Sender::PlayableCreator

Sender::PlayableCreator::PlayableCreator(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels)
    : iSampleRate(aSampleRate)
    , iBitDepth(aBitDepth)
    , iNumChannels(aNumChannels)
{
}

MsgPlayable* Sender::PlayableCreator::Process(MsgAudio* aMsg)
{
    iPlayable = nullptr;
    (void)aMsg->Process(*this);
    return iPlayable;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgMode* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgDrain* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgDelay* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgStreamInterrupted* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgWait* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgBitRate* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgAudioPcm* aMsg)
{
    iPlayable = aMsg->CreatePlayable();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgSilence* aMsg)
{
    iPlayable = aMsg->CreatePlayable(iSampleRate, iBitDepth, iNumChannels);
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS();
    return nullptr;
}
