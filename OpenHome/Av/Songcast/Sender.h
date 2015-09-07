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
class IOhmTimestamper;
class IOhmTimestampMapper;

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
    Sender(Environment& aEnv,
           Net::DvDeviceStandard& aDevice,
           ZoneHandler& aZoneHandler,
           IOhmTimestamper* aTimestamper,
           IOhmTimestampMapper* aTsMapper,
           Configuration::IConfigInitialiser& aConfigInit,
           const Brx& aName,
           TUint aMinLatencyMs,
           const Brx& aIconFileName);
    ~Sender();
    void SetName(const Brx& aName);
    void NotifyPipelineState(Media::EPipelineState aState);
private: // from Media::IPipelineElementDownstream
    void Push(Media::Msg* aMsg) override;
private: // from Media::IMsgProcessor
    Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgTrack* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDrain* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDelay* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgStreamInterrupted* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgHalt* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgFlush* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgWait* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgBitRate* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
private:
    void ProcessAudio(Media::MsgAudio* aMsg);
    void SendPendingAudio(TBool aHalt = false);
    void ConfigEnabledChanged(Configuration::KeyValuePair<TUint>& aStringId);
    void ConfigChannelChanged(Configuration::KeyValuePair<TInt>& aValue);
    void ConfigModeChanged(Configuration::KeyValuePair<TUint>& aStringId);
    void ConfigPresetChanged(Configuration::KeyValuePair<TInt>& aValue);
private: // from IPcmProcessor
    void BeginBlock() override;
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
    void EndBlock() override;
private:
    class PlayableCreator : private Media::IMsgProcessor
    {
    public:
        PlayableCreator(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels);
        Media::MsgPlayable* Process(Media::MsgAudio* aMsg);
    private: // from Media::IMsgProcessor
        Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgTrack* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDrain* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDelay* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgEncodedStream* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgAudioEncoded* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgMetaText* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgStreamInterrupted* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgHalt* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgFlush* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgWait* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgDecodedStream* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgBitRate* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
        Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
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
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    const TUint iMinLatencyMs;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SONGCAST_SENDER
