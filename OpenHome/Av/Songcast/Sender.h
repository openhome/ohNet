#ifndef HEADER_SONGCAST_SENDER
#define HEADER_SONGCAST_SENDER

#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Media/PipelineObserver.h>
#include <OpenHome/Configuration/ConfigManager.h>

#include <vector>

namespace OpenHome {
namespace Net {
    class DvDeviceStandard;
}
namespace Av {

class OhmSenderDriver;
class OhmSender;
class ZoneHandler;

class Sender : public Media::IPipelineElementDownstream, private Media::IMsgProcessor, private Media::IPcmProcessor
{
    static const Brn kConfigIdEnabled;
    static const Brn kConfigIdChannel;
    static const Brn kConfigIdMode;
    static const Brn kConfigIdPreset;
    static const TInt kChannelMin = 30000;
    static const TInt kChannelMax = 65535;
    static const TInt kPresetMin = 0;
    static const TInt kPresetMax = 0x7fffffff;
    static const TInt kPresetNone = 0;
    static const TUint kSongcastPacketMs = 5;
    static const TUint kSongcastPacketJiffies = Media::Jiffies::kPerMs * kSongcastPacketMs;
    static const TUint kSongcastPacketMaxBytes = 3 * Media::DecodedAudio::kMaxNumChannels * 192 * kSongcastPacketMs;
public:
    Sender(Environment& aEnv, Net::DvDeviceStandard& aDevice, ZoneHandler& aZoneHandler, Configuration::IConfigInitialiser& aConfigInit, const Brx& aName, TUint aMinLatencyMs, const Brx& aIconFileName);
    ~Sender();
    void SetName(const Brx& aName);
    void NotifyPipelineState(Media::EPipelineState aState);
private: // from Media::IPipelineElementDownstream
    void Push(Media::Msg* aMsg);
private: // from Media::IMsgProcessor
    Media::Msg* ProcessMsg(Media::MsgMode* aMsg);
    Media::Msg* ProcessMsg(Media::MsgSession* aMsg);
    Media::Msg* ProcessMsg(Media::MsgTrack* aMsg);
    Media::Msg* ProcessMsg(Media::MsgDelay* aMsg);
    Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg);
    Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg);
    Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg);
    Media::Msg* ProcessMsg(Media::MsgHalt* aMsg);
    Media::Msg* ProcessMsg(Media::MsgFlush* aMsg);
    Media::Msg* ProcessMsg(Media::MsgWait* aMsg);
    Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg);
    Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg);
    Media::Msg* ProcessMsg(Media::MsgSilence* aMsg);
    Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg);
    Media::Msg* ProcessMsg(Media::MsgQuit* aMsg);
private:
    void ProcessAudio(Media::MsgAudio* aMsg);
    void SendPendingAudio(TBool aHalt = false);
    void ConfigEnabledChanged(Configuration::KeyValuePair<TUint>& aStringId);
    void ConfigChannelChanged(Configuration::KeyValuePair<TInt>& aValue);
    void ConfigModeChanged(Configuration::KeyValuePair<TUint>& aStringId);
    void ConfigPresetChanged(Configuration::KeyValuePair<TInt>& aValue);
private: // from IPcmProcessor
    void BeginBlock();
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    void ProcessSample24(const TByte* aSample, TUint aNumChannels);
    void EndBlock();
private:
    class PlayableCreator : private Media::IMsgProcessor
    {
    public:
        PlayableCreator(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels);
        Media::MsgPlayable* Process(Media::MsgAudio* aMsg);
    private: // from Media::IMsgProcessor
        Media::Msg* ProcessMsg(Media::MsgMode* aMsg);
        Media::Msg* ProcessMsg(Media::MsgSession* aMsg);
        Media::Msg* ProcessMsg(Media::MsgTrack* aMsg);
        Media::Msg* ProcessMsg(Media::MsgDelay* aMsg);
        Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg);
        Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg);
        Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg);
        Media::Msg* ProcessMsg(Media::MsgHalt* aMsg);
        Media::Msg* ProcessMsg(Media::MsgFlush* aMsg);
        Media::Msg* ProcessMsg(Media::MsgWait* aMsg);
        Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg);
        Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg);
        Media::Msg* ProcessMsg(Media::MsgSilence* aMsg);
        Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg);
        Media::Msg* ProcessMsg(Media::MsgQuit* aMsg);
    private:
        TUint iSampleRate;
        TUint iBitDepth;
        TUint iNumChannels;
        Media::MsgPlayable* iPlayable;
    };
private:
    OhmSenderDriver* iOhmSenderDriver;
    OhmSender* iOhmSender;
    Configuration::ConfigChoice* iConfigEnabled;
    TUint iListenerIdConfigEnabled;
    Configuration::ConfigNum* iConfigChannel;
    TUint iListenerIdConfigChannel;
    Configuration::ConfigChoice* iConfigMode;
    TUint iListenerIdConfigMode;
    Configuration::ConfigNum* iConfigPreset;
    TUint iListenerIdConfigPreset;
    std::vector<Media::MsgAudio*> iPendingAudio;
    Bws<kSongcastPacketMaxBytes> iAudioBuf;
    Media::Track* iTrack;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    const TUint iMinLatencyMs;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SONGCAST_SENDER
