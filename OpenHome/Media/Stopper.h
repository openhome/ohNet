#ifndef HEADER_PIPELINE_STOPPER
#define HEADER_PIPELINE_STOPPER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Msg.h>

namespace OpenHome {
namespace Media {

class IPipelineElement
{
public:
    virtual Msg* Pull() = 0;
};

class IStopperObserver
{
public:
    virtual void PipelineHalted() = 0;
    virtual void PipelineFlushed() = 0;
};
    
class Stopper : public IPipelineElement, private IMsgProcessor
{
public:
    Stopper(IStopperObserver& aObserver, IPipelineElement& aUpstreamElement);
    void Start(TUint aRampDuration);
    void BeginHalt(TUint aRampDuration);
    void BeginFlush();
public: // from IPipelineElement
    Msg* Pull();
private: // from IMsgProcessor
    Msg* ProcessMsg(MsgAudioPcm* aMsg);
    Msg* ProcessMsg(MsgSilence* aMsg);
    Msg* ProcessMsg(MsgPlayable* aMsg);
    Msg* ProcessMsg(MsgTrack* aMsg);
    Msg* ProcessMsg(MsgMetaText* aMsg);
    Msg* ProcessMsg(MsgHalt* aMsg);
    Msg* ProcessMsg(MsgFlush* aMsg);
private:
    Msg* ProcessMsgAudio(MsgAudio* aMsg);
    void Ramp(MsgAudio* aMsg, Ramp::EDirection aDirection);
private:
    enum EState
    {
        ERunning
       ,EHalted
       ,EStarting
       ,EHalting
       ,EFlushing
    };
private:
    static const TUint kMaxStoredMsg = 2;
    IStopperObserver& iObserver;
    IPipelineElement& iUpstreamElement;
    Mutex iLock;
    Semaphore iSem;
    EState iState;
    TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_STOPPER
