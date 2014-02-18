#ifndef HEADER_PIPELINE_DRIVER_SONGCAST_SENDER
#define HEADER_PIPELINE_DRIVER_SONGCAST_SENDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Media/ProcessorPcmUtils.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/Songcast/OhmSender.h>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {
    class ZoneHandler;
}
namespace Media {

class ProcessorPcmBufPackedDualMono : public ProcessorPcmBuf
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


class DriverSongcastSender : public Thread, private IMsgProcessor, private Net::IResourceManager
{
    static const TUint kSongcastTtl = 1;
    static const TUint kSongcastLatencyMs = 300;
    static const TUint kSongcastPreset = 0;
    static const Brn kSenderIconFileName;
public:
    DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvStack& aDvStack, const Brx& aName, TUint aChannel);
    ~DriverSongcastSender();
private: // from Thread
    void Run();
private:
    void TimerCallback();
    void SendAudio(MsgPlayable* aMsg);
    void DeviceDisabled();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgEncodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioEncoded* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgDecodedStream* aMsg);
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private: // from Net::IResourceManager
    void WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, Net::IResourceWriter& aResourceWriter);
private:
    IPipelineElementUpstream& iPipeline;
    TUint iMaxMsgSizeJiffies;
    Environment& iEnv;
    Av::OhmSenderDriver* iOhmSenderDriver;
    Av::OhmSender* iOhmSender;
    Net::DvDeviceStandard* iDevice;
    Av::ZoneHandler* iZoneHandler;
    Semaphore iDeviceDisabled;
    Timer* iTimer;
    TByte* iBuf;
    TByte* iBufPacked;
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
    MsgPlayable* iPlayable;
    TBool iAudioSent;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DRIVER_SONGCAST_SENDER
