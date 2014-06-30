#ifndef HEADER_SENDER
#define HEADER_SENDER

#include <OpenHome/Media/Msg.h>
#include <OpenHome/OhNetTypes.h>
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
}
namespace Media {

class Sender : public IPipelineElementDownstream, private IMsgProcessor, private IPcmProcessor
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
    static const TUint kSongcastPacketJiffies = Jiffies::kPerMs * kSongcastPacketMs;
    static const TUint kSongcastPacketMaxBytes = 3 * DecodedAudio::kMaxNumChannels * 192 * kSongcastPacketMs;
public:
    Sender(Environment& aEnv, Net::DvDeviceStandard& aDevice, Av::ZoneHandler& aZoneHandler, Configuration::IConfigManagerInitialiser& aConfigInit, const Brx& aName, TUint aMinLatencyMs, const Brx& aIconFileName);
    ~Sender();
    void SetName(const Brx& aName);
    void NotifyPipelineState(EPipelineState aState);
private: // from IPipelineElementDownstream
    void Push(Msg* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg);
    Msg* ProcessMsg(MsgSession* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgDelay* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgWait* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    void ProcessAudio(MsgAudio* aMsg);
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
    class PlayableCreator : private IMsgProcessor
    {
    public:
        PlayableCreator(TUint aSampleRate, TUint aBitDepth, TUint aNumChannels);
        MsgPlayable* Process(MsgAudio* aMsg);
    private: // from IMsgProcessor
        Msg* ProcessMsg(MsgMode* aMsg);
        Msg* ProcessMsg(MsgSession* aMsg);
        Msg* ProcessMsg(MsgTrack* aMsg);
        Msg* ProcessMsg(MsgDelay* aMsg);
        Msg* ProcessMsg(MsgEncodedStream* aMsg);
        Msg* ProcessMsg(MsgAudioEncoded* aMsg);
        Msg* ProcessMsg(MsgMetaText* aMsg);
        Msg* ProcessMsg(MsgHalt* aMsg);
        Msg* ProcessMsg(MsgFlush* aMsg);
        Msg* ProcessMsg(MsgWait* aMsg);
        Msg* ProcessMsg(MsgDecodedStream* aMsg);
        Msg* ProcessMsg(MsgAudioPcm* aMsg);
        Msg* ProcessMsg(MsgSilence* aMsg);
        Msg* ProcessMsg(MsgPlayable* aMsg);
        Msg* ProcessMsg(MsgQuit* aMsg);
    private:
        TUint iSampleRate;
        TUint iBitDepth;
        TUint iNumChannels;
        MsgPlayable* iPlayable;
    };
private:
    Av::OhmSenderDriver* iOhmSenderDriver;
    Av::OhmSender* iOhmSender;
    Configuration::ConfigChoice* iConfigEnabled;
    TUint iListenerIdConfigEnabled;
    Configuration::ConfigNum* iConfigChannel;
    TUint iListenerIdConfigChannel;
    Configuration::ConfigChoice* iConfigMode;
    TUint iListenerIdConfigMode;
    Configuration::ConfigNum* iConfigPreset;
    TUint iListenerIdConfigPreset;
    std::vector<MsgAudio*> iPendingAudio;
    Bws<kSongcastPacketMaxBytes> iAudioBuf;
    Track* iTrack;
    TUint iSampleRate;
    TUint iBitDepth;
    TUint iNumChannels;
    const TUint iMinLatencyMs;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_SENDER
