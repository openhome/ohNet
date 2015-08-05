#ifndef HEADER_DRIVER_SONGCAST_SENDER
#define HEADER_DRIVER_SONGCAST_SENDER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/Songcast/OhmSender.h>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {
    class ZoneHandler;
}
namespace Av {

class ProcessorPcmBufPackedDualMono : public Media::ProcessorPcmBuf
{
public:
    ProcessorPcmBufPackedDualMono();
private: // from IPcmProcessor
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels) override;
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels) override;
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels) override;
    void ProcessSample8(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample16(const TByte* aSample, TUint aNumChannels) override;
    void ProcessSample24(const TByte* aSample, TUint aNumChannels) override;
};


class DriverSongcastSender : public Thread, private Media::IMsgProcessor, private Net::IResourceManager
{
    static const TUint kSongcastTtl = 1;
    static const TUint kSongcastLatencyMs = 300;
    static const TUint kSongcastPreset = 0;
    static const Brn kSenderIconFileName;
public:
    DriverSongcastSender(Media::IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvStack& aDvStack, const Brx& aName, TUint aChannel);
    ~DriverSongcastSender();
private: // from Thread
    void Run() override;
private:
    void TimerCallback();
    void SendAudio(Media::MsgPlayable* aMsg);
    void DeviceDisabled();
private: // from Media::IMsgProcessor
    Media::Msg* ProcessMsg(Media::MsgMode* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSession* aMsg) override;
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
    Media::Msg* ProcessMsg(Media::MsgAudioPcm* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgSilence* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgPlayable* aMsg) override;
    Media::Msg* ProcessMsg(Media::MsgQuit* aMsg) override;
private: // from Net::IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, Net::IResourceWriter& aResourceWriter) override;
private:
    Media::IPipelineElementUpstream& iPipeline;
    TUint iMaxMsgSizeJiffies;
    Environment& iEnv;
    OhmSenderDriver* iOhmSenderDriver;
    OhmSender* iOhmSender;
    Net::DvDeviceStandard* iDevice;
    ZoneHandler* iZoneHandler;
    Semaphore iDeviceDisabled;
    Timer* iTimer;
    TUint iSampleRate;
    TUint iJiffiesPerSample;
    TUint iNumChannels;
    TUint iBitDepth;
    TUint iJiffiesToSend;
    TUint iTimerFrequencyMs;
    TUint64 iLastTimeUs;    // last time stamp from system
    TInt  iTimeOffsetUs;    // running offset in usec from ideal time
                            //  <0 means sender is behind
                            //  >0 means sender is ahead
    Media::MsgPlayable* iPlayable;
    TBool iAudioSent;
    TBool iQuit;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_DRIVER_SONGCAST_SENDER
