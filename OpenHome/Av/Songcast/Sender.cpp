#include <OpenHome/Av/Songcast/Sender.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Av/Songcast/ProtocolOhm.h> // for IUnicastOverrideObserver
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
               Optional<IOhmTimestamper> aTimestamper,
               Configuration::IConfigInitialiser& aConfigInit,
               TUint aThreadPriority,
               const Brx& aName,
               TUint aMinLatencyMs,
               const Brx& aSongcastMode,
               IUnicastOverrideObserver& aUnicastOverrideObserver)
    : iAudioBuf(nullptr)
    , iSampleRate(0)
    , iMinLatencyMs(aMinLatencyMs)
    , iSongcastMode(aSongcastMode)
    , iUnicastOverrideObserver(aUnicastOverrideObserver)
    , iEnabled(true)
    , iUserEnabledInitialised(false)
    , iStreamForbidden(false)
    , iFirstChannelIndex(0)
{
    const TInt defaultChannel = (TInt)aEnv.Random(kChannelMax, kChannelMin);
    iOhmSenderDriver = new OhmSenderDriver(aEnv, aTimestamper);
    // create sender with default configuration.  CongfigVals below will each call back on construction, allowing these to be updated
    iOhmSender = new OhmSender(aEnv, aDevice, *iOhmSenderDriver, aZoneHandler, aThreadPriority,
                               aName, defaultChannel, aMinLatencyMs, false/*unicast*/);

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

void Sender::SetImageUri(const Brx& aUri)
{
    iOhmSender->SetImageUri(aUri);
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
    const TBool wasEnabled = iEnabled;
    iEnabled = (aMsg->Mode() != iSongcastMode);
    if (wasEnabled && !iEnabled) {
        SendPendingAudio(true);
        iOhmSender->EnableUnicastOverride(true);
        iUnicastOverrideObserver.UnicastOverrideEnabled();
    }
    else if (!wasEnabled && iEnabled) {
        iOhmSender->EnableUnicastOverride(false);
        iUnicastOverrideObserver.UnicastOverrideDisabled();
    }
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
    const TUint latencyMs = Jiffies::ToMs(aMsg->DelayJiffies());
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
    iOhmSender->NotifyAudioPlaying(false);
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
    iStreamForbidden = (streamInfo.Multiroom() == Multiroom::Forbidden);

    const TUint bitDepth = std::min(streamInfo.BitDepth(), (TUint)24); /* 32-bit audio is assumed to be padded
                                                                          and converted to 24-bit before transmission */
    const TUint numChannels = streamInfo.NumChannels();
    const TUint64 samplesTotal = streamInfo.TrackLength() / Jiffies::PerSample(iSampleRate);
    iFirstChannelIndex = FirstChannelToSend(numChannels);

    iOhmSender->SetTrackPosition(samplesTotal, streamInfo.SampleStart());
    iOhmSenderDriver->SetAudioFormat(iSampleRate, streamInfo.BitRate(), std::min(numChannels, (TUint)2),
                                     bitDepth, streamInfo.Lossless(), streamInfo.CodecName(),
                                     streamInfo.SampleStart());
    iOhmSender->NotifyBroadcastAllowed(!iStreamForbidden);

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
    if (iStreamForbidden) {
        aMsg->RemoveRef();
        return;
    }
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
    PlayableCreator pc;
    for (TUint i=0; i<iPendingAudio.size(); i++) {
        MsgPlayable* playable = pc.Process(iPendingAudio[i]);
        playable->Read(*this);
        playable->RemoveRef();
    }
    iOhmSenderDriver->SendAudio(msg, aHalt);
    iAudioBuf = nullptr;
    iPendingAudio.clear();
    iOhmSender->NotifyAudioPlaying(true);
}

void Sender::ConfigEnabledChanged(KeyValuePair<TUint>& aStringId)
{
    const TBool configEnabled = (aStringId.Value() == eStringIdYes);
    if (!iUserEnabledInitialised || configEnabled != iUserEnabled) {
        iUserEnabledInitialised = true;
        iUserEnabled = configEnabled;
        iOhmSender->SetEnabled(configEnabled);
    }
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

// FIXME: review how this mapping is generated
TUint Sender::FirstChannelToSend(TUint aNumChannels)
{
    return (aNumChannels < 10) ? 0 : 8;
}

void Sender::ProcessFragment(const Brx& aData, TUint aNumChannels, TUint aBytesPerSample)
{
    const TByte* src = aData.Ptr() + aBytesPerSample*iFirstChannelIndex;
    const TUint stride = aBytesPerSample * aNumChannels;
    const TUint numSamples = aData.Bytes() / stride;
    const TUint dstBytesPerSample = std::min(aBytesPerSample, (TUint)3);
    const TUint totalBytesToCopy = numSamples * 2 * dstBytesPerSample;
    TByte* dst = const_cast<TByte*>(iAudioBuf->Ptr()) + iAudioBuf->Bytes();

    ASSERT(iAudioBuf->BytesRemaining() >= totalBytesToCopy);

    for (TUint i=0; i<numSamples; i++) {
        memcpy(dst, src, dstBytesPerSample);
        memcpy(dst + dstBytesPerSample, src + aBytesPerSample, dstBytesPerSample);
        src += stride;
        dst += 2*dstBytesPerSample;
    }
    iAudioBuf->SetBytes(iAudioBuf->Bytes() + totalBytesToCopy);
}

void Sender::BeginBlock()
{
    ASSERT(iAudioBuf);
}

void Sender::ProcessFragment8(const Brx& aData, TUint aNumChannels)
{
    ProcessFragment(aData, aNumChannels, 1);
}

void Sender::ProcessFragment16(const Brx& aData, TUint aNumChannels)
{
    ProcessFragment(aData, aNumChannels, 2);
}

void Sender::ProcessFragment24(const Brx& aData, TUint aNumChannels)
{
    ProcessFragment(aData, aNumChannels, 3);
}

void Sender::ProcessFragment32(const Brx& aData, TUint aNumChannels)
{
    ProcessFragment(aData, aNumChannels, 4);
}

void Sender::EndBlock()
{
}

void Sender::Flush()
{
}


// Sender::PlayableCreator

Sender::PlayableCreator::PlayableCreator()
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
    iPlayable = aMsg->CreatePlayable();
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
