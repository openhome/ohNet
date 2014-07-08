#ifndef HEADER_PIPELINE_DRIVER_BASIC
#define HEADER_PIPELINE_DRIVER_BASIC

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Utils/ProcessorPcmUtils.h>
#include <OpenHome/Net/Core/DvDevice.h>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Media {

class DriverBasic : public Thread, private IMsgProcessor
{
    static const TUint kTimerFrequencyMs = 5;
public:
    DriverBasic(IPipelineElementUpstream& aPipeline, Environment& aEnv);
    ~DriverBasic();
private: // from Thread
    void Run();
private:
    void TimerCallback();
    void ProcessAudio(MsgPlayable* aMsg);
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
    IPipelineElementUpstream& iPipeline;
    Timer* iTimer;
    OsContext* iOsCtx;
    TUint iSampleRate;
    TUint iJiffiesPerSample;
    TUint iNumChannels;
    TUint iBitDepth;
    TUint iPendingJiffies;
    TUint64 iLastTimeUs;
    TUint iNextTimerDuration;
    MsgPlayable* iPlayable;
    TBool iQuit;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_DRIVER_BASIC
