#include <OpenHome/Media/Sender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/OhmSender.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/StringIds.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Configuration;

// Sender

const Brn Sender::kConfigIdEnabled("sender.enabled");
const Brn Sender::kConfigIdChannel("sender.channel");
const Brn Sender::kConfigIdMode("sender.mode");
const Brn Sender::kConfigIdPreset("sender.preset");

Sender::Sender(Environment& aEnv, Net::DvDeviceStandard& aDevice, Av::ZoneHandler& aZoneHandler, IConfigManagerWriter& aConfigManager, const Brx& aName, TUint aLatencyMs, const Brx& aIconFileName)
    : iTrack(NULL)
    , iSampleRate(0)
    , iBitDepth(0)
    , iNumChannels(0)
{
    const TInt defaultChannel = (TInt)aEnv.Random(kChannelMax, kChannelMin);
    iOhmSenderDriver = new Av::OhmSenderDriver(aEnv);
    // create sender with default configuration.  CongfigVals below will each call back on construction, allowing these to be updated
    iOhmSender = new Av::OhmSender(aEnv, aDevice, *iOhmSenderDriver, aZoneHandler, aName, defaultChannel, aLatencyMs, false/*unicast*/, aIconFileName);

    iConfigChannel = new ConfigNum(aConfigManager, kConfigIdChannel, kChannelMin, kChannelMax, defaultChannel);
    iListenerIdConfigChannel = iConfigChannel->Subscribe(MakeFunctorConfigNum(*this, &Sender::ConfigChannelChanged));

    std::vector<TUint> choices;
    choices.push_back(eStringIdSongcastModeMulticast);
    choices.push_back(eStringIdSongcastModeUnicast);
    iConfigMode = new ConfigChoice(aConfigManager, kConfigIdMode, choices, eStringIdSongcastModeUnicast);
    iListenerIdConfigMode = iConfigMode->Subscribe(MakeFunctorConfigChoice(*this, &Sender::ConfigModeChanged));

    iConfigPreset = new ConfigNum(aConfigManager, kConfigIdPreset, kPresetMin, kPresetMax, kPresetNone);
    iListenerIdConfigPreset = iConfigPreset->Subscribe(MakeFunctorConfigNum(*this, &Sender::ConfigPresetChanged));

    choices.clear();
    choices.push_back(eStringIdYes);
    choices.push_back(eStringIdNo);
    iConfigEnabled = new ConfigChoice(aConfigManager, kConfigIdEnabled, choices, eStringIdYes);
    iListenerIdConfigEnabled = iConfigEnabled->Subscribe(MakeFunctorConfigChoice(*this, &Sender::ConfigEnabledChanged));

    iPendingAudio.reserve(100); // arbitrarily chosen value.  Doesn't need to prevent any reallocation, just avoid regular churn early on
}

Sender::~Sender()
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
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
    if (msg != NULL) {
        msg->RemoveRef();
    }
}

Msg* Sender::ProcessMsg(MsgTrack* aMsg)
{
    if (iTrack != NULL) {
        iTrack->RemoveRef();
    }
    iTrack = &aMsg->Track();
    iTrack->AddRef();
    return aMsg;
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

Msg* Sender::ProcessMsg(MsgHalt* aMsg)
{
    SendPendingAudio();
    // FIXME - no way to pass this through OhmSender
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgFlush* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgDecodedStream* aMsg)
{
    ASSERT(iTrack != NULL);
    const DecodedStreamInfo& streamInfo = aMsg->StreamInfo();
    iSampleRate = streamInfo.SampleRate();
    iBitDepth = streamInfo.BitDepth();
    iNumChannels = streamInfo.NumChannels();

    // send any pending audio in case the stream msg indicates a discontinuity in the track (probably after a seek?)
    SendPendingAudio();

    const TUint64 samplesTotal = streamInfo.TrackLength() / Jiffies::JiffiesPerSample(streamInfo.SampleRate());
    iOhmSender->SetTrack(iTrack->Uri(), iTrack->MetaData(), samplesTotal, streamInfo.SampleStart());
    iOhmSenderDriver->SetAudioFormat(iSampleRate, streamInfo.BitRate(), iNumChannels, iBitDepth, streamInfo.Lossless(), streamInfo.CodecName());

    return aMsg;
}

Msg* Sender::ProcessMsg(MsgAudioPcm* aMsg)
{
    ProcessAudio(aMsg);
    return NULL;
}

Msg* Sender::ProcessMsg(MsgSilence* aMsg)
{
    ProcessAudio(aMsg);
    return NULL;
}

Msg* Sender::ProcessMsg(MsgPlayable* aMsg)
{
    ASSERTS(); // don't expect this msg at this stage of the pipeline
    return aMsg;
}

Msg* Sender::ProcessMsg(MsgQuit* aMsg)
{
    SendPendingAudio();
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
        remaining = (newJiffies == kSongcastPacketJiffies? NULL : msg->Split(newJiffies - kSongcastPacketJiffies));
        iPendingAudio.push_back(msg);
        SendPendingAudio();
        msg = remaining;
        newJiffies = (remaining==NULL? 0 : remaining->Jiffies());
    } while (remaining != NULL && newJiffies >= kSongcastPacketJiffies);
    if (remaining != NULL) {
        iPendingAudio.push_back(remaining);
    }
}

void Sender::SendPendingAudio()
{
    iAudioBuf.SetBytes(0);
    PlayableCreator pc(iSampleRate, iBitDepth, iNumChannels);
    for (TUint i=0; i<iPendingAudio.size(); i++) {
        MsgPlayable* playable = pc.Process(iPendingAudio[i]);
        playable->Read(*this);
        playable->RemoveRef();
    }
    if (iAudioBuf.Bytes() != 0) {
        iOhmSenderDriver->SendAudio(iAudioBuf.Ptr(), iAudioBuf.Bytes());
    }
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
}

TBool Sender::ProcessFragment8(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf.Append(aData);
    return true;
}

TBool Sender::ProcessFragment16(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf.Append(aData);
    return true;
}

TBool Sender::ProcessFragment24(const Brx& aData, TUint /*aNumChannels*/)
{
    iAudioBuf.Append(aData);
    return true;
}

void Sender::ProcessSample8(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, aNumChannels);
    iAudioBuf.Append(sample);
}

void Sender::ProcessSample16(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 2*aNumChannels);
    iAudioBuf.Append(sample);
}

void Sender::ProcessSample24(const TByte* aSample, TUint aNumChannels)
{
    Brn sample(aSample, 3*aNumChannels);
    iAudioBuf.Append(sample);
}

void Sender::EndBlock()
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
    iPlayable = NULL;
    (void)aMsg->Process(*this);
    return iPlayable;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgTrack* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgEncodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgAudioEncoded* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgMetaText* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgHalt* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgFlush* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgDecodedStream* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgAudioPcm* aMsg)
{
    iPlayable = aMsg->CreatePlayable();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgSilence* aMsg)
{
    iPlayable = aMsg->CreatePlayable(iSampleRate, iBitDepth, iNumChannels);
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgPlayable* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}

Msg* Sender::PlayableCreator::ProcessMsg(MsgQuit* /*aMsg*/)
{
    ASSERTS();
    return NULL;
}
