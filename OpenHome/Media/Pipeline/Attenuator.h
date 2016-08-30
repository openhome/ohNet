#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/VolumeManager.h>
#include <atomic>

namespace OpenHome {
namespace Media {

class IAttenuator
{
public:
    static const TUint kUnityAttenuation = 256;
public:
    virtual void SetAttenuation(TUint aAttenuation) = 0;
    virtual ~IAttenuator() {}
};

/*
Element which sets attenuation value in PCM audio message:
*/

class Attenuator : public PipelineElement, public IPipelineElementUpstream, public IAttenuator, private INonCopyable
{
    static const TUint kSupportedMsgTypes;
public:
    Attenuator(IPipelineElementUpstream& aUpstreamElement);
    virtual ~Attenuator();
//    void SetAttenuation(TUint16 aAttenuation);
public: // from IAttenuator
    void SetAttenuation(TUint aAttenuation) override;
public: // from IPipelineElementUpstream
    Msg* Pull() override;
private: // IMsgProcessor
    Msg* ProcessMsg(MsgMode* aMsg) override;
    Msg* ProcessMsg(MsgAudioPcm* aMsg) override;
private:
    IPipelineElementUpstream& iUpstreamElement;
    MsgQueueLite iQueue;
    TUint16 iAttenuation;
    std::atomic<TBool> iActive;
};

} // namespace Media
} // namespace OpenHome

