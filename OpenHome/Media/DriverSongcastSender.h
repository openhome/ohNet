#ifndef HEADER_PIPELINE_DRIVER_SONGCAST_SENDER
#define HEADER_PIPELINE_DRIVER_SONGCAST_SENDER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Av/Songcast/OhmSender.h>

namespace OpenHome {
class Timer;
namespace Media {
    
class DriverSongcastSender : public Thread, private IMsgProcessor
{
    static const TUint kSongcastTtl = 1;
    static const TUint kSongcastLatencyMs = 300;
    static const TUint kSongcastPreset = 0;
public:
    DriverSongcastSender(IPipelineElementUpstream& aPipeline, TUint aMaxMsgSizeJiffies, Net::DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aAdapter);
    ~DriverSongcastSender();
private: // from Thread
    void Run();
private:
    void TimerCallback();
    void SendAudio(MsgPlayable* aMsg);
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgAudioFormat* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
    Msg* ProcessMsg(MsgQuit* aMsg);
private:
    IPipelineElementUpstream& iPipeline;
    TUint iMaxMsgSizeJiffies;
    Av::OhmSenderDriver* iOhmSenderDriver;
    Av::OhmSender* iOhmSender;
    Timer* iTimer;
    TByte* iBuf; // FIXME - uninitialised
    TUint iSampleRate;
    TUint iJiffiesPerSample;
    TUint iNumChannels;
    TUint iJiffiesToSend;
    TUint iLastSendTime;
    MsgPlayable* iPlayable;
    TBool iAudioSent;
    TBool iQuit;
    TUint iTotalBytesSent;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DRIVER_SONGCAST_SENDER
