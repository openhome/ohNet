#ifndef HEADER_DRIVER_SONGCAST_SENDER
#define HEADER_DRIVER_SONGCAST_SENDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
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
    TBool ProcessFragment8(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment16(const Brx& aData, TUint aNumChannels);
    TBool ProcessFragment24(const Brx& aData, TUint aNumChannels);
    void ProcessSample8(const TByte* aSample, TUint aNumChannels);
    void ProcessSample16(const TByte* aSample, TUint aNumChannels);
    void ProcessSample24(const TByte* aSample, TUint aNumChannels);
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
    void Run();
private:
    void TimerCallback();
    void SendAudio(Media::MsgPlayable* aMsg);
    void DeviceDisabled();
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
private: // from Net::IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, Net::IResourceWriter& aResourceWriter);
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
