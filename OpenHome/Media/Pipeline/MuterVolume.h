#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/MuteManager.h>

namespace OpenHome {
namespace Media {

class IVolumeRamper
{
public:
    enum class Status
    {
        eInProgress,
        eComplete
    };
public:
    virtual Status BeginMute() = 0;
    virtual Status StepMute(TUint aJiffies) = 0;
    virtual void SetMuted() = 0;
    virtual Status BeginUnmute() = 0;
    virtual Status StepUnmute(TUint aJiffies) = 0;
    virtual void SetUnmuted() = 0;
    virtual ~IVolumeRamper() {}
};

/*
    Similar to Muter but ramps volume rather than samples.
*/

class MuterVolume : public PipelineElement, public IPipelineElementUpstream, public IMute, private INonCopyable
{
    friend class SuiteMuterVolume;

    static const TUint kSupportedMsgTypes;
    static const TUint kJiffiesUntilMute;
public:
    MuterVolume(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream);
    void Start(IVolumeRamper& aVolumeRamper);
public: // from IMute
    void Mute() override;
    void Unmute() override;
private: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgHalt* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
    Msg* ProcessMsg(MsgSilence* aMsg) override;
private:
    void ProcessAudio(MsgAudio* aMsg);
    void PipelineHalted();
private:
    enum class State
    {
        eRunning,
        eMutingRamp,
        eMutingWait,
        eUnmutingRamp,
        eMuted
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstream;
    IVolumeRamper* iVolumeRamper;
    Mutex iLock;
    Semaphore iSemMuted;
    State iState;
    TUint iJiffiesUntilMute;
    TBool iHalted;
};

class VolumeRamperStub : public IVolumeRamper
{
private: // from IVolumeRamper
    IVolumeRamper::Status BeginMute()                       { return IVolumeRamper::Status::eComplete; }
    IVolumeRamper::Status StepMute(TUint /*aJiffies*/)      { return IVolumeRamper::Status::eComplete; }
    void SetMuted()                                         {}
    IVolumeRamper::Status BeginUnmute()                     { return IVolumeRamper::Status::eComplete; }
    IVolumeRamper::Status StepUnmute(TUint /*aJiffies*/)    { return IVolumeRamper::Status::eComplete; }
    void SetUnmuted()                                       {}
};

} // namespace Media
} // namespace OpenHome

