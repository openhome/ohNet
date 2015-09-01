#ifndef HEADER_PIPELINE_MUTER
#define HEADER_PIPELINE_MUTER

#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/MuteManager.h>

namespace OpenHome {
namespace Media {

class Muter : public PipelineElement, public IPipelineElementUpstream, public IMute, private INonCopyable
{
    friend class SuiteMuter;

    static const TUint kSupportedMsgTypes;
public:
    Muter(MsgFactory& aMsgFactory, IPipelineElementUpstream& aUpstream, TUint aRampDuration);
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
    enum EState
    {
        eRunning
       ,eRampingDown
       ,eRampingUp
       ,eMuted
    };
private:
    MsgFactory& iMsgFactory;
    IPipelineElementUpstream& iUpstream;
    Mutex iLock;
    EState iState;
    const TUint iRampDuration;
    TUint iRemainingRampSize;
    TUint iCurrentRampValue;
    MsgQueue iQueue; // empty unless we have to split a msg during a ramp
    TBool iHalted;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_MUTER
