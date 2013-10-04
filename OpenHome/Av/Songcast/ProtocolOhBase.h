#ifndef HEADER_PROTOCOL_OHBASE
#define HEADER_PROTOCOL_OHBASE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>

#include <vector>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {

class IOhmTimestamper
{
public:
    virtual ~IOhmTimestamper() {}
    virtual TUint Timestamp() = 0;
};

class OhmMsgAudioBlob;
class OhmMsg;

class ProtocolOhBase : public Media::Protocol, private IOhmMsgProcessor
{
    static const TUint kMaxRepairBacklogFrames = 200;
    static const TUint kMaxRepairMissedFrames = 20;
    static const TUint kInitialRepairTimeoutMs = 10;
    static const TUint kSubsequentRepairTimeoutMs = 30;
protected:
    ProtocolOhBase(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const TChar* aSupportedScheme, const Brx& aMode);
    ~ProtocolOhBase();
    void Add(OhmMsg* aMsg);
    void ResendSeen();
private:
    virtual void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) = 0;
    virtual void RequestResend(const Brx& aFrames) = 0; // FIXME - ohm & ohu have identical implementations of this
private: // from Media::Protocol
    Media::ProtocolStreamResult Stream(const Brx& aUri);
private:
    void RepairReset();
    void TimerRepairExpired();
    TBool RepairBegin(OhmMsgAudioBlob& aMsg);
    TBool Repair(OhmMsgAudioBlob& aMsg);
    void OutputAudio(OhmMsgAudioBlob& aMsg);
private: // from IOhmMsgProcessor
    void Process(OhmMsgAudio& aMsg);
    void Process(OhmMsgAudioBlob& aMsg);
    void Process(OhmMsgTrack& aMsg);
    void Process(OhmMsgMetatext& aMsg);
protected:
    Environment& iEnv;
    IOhmMsgFactory& iMsgFactory;
private:
    Mutex iMutexTransport;
    Media::TrackFactory& iTrackFactory;
    IOhmTimestamper& iTimestamper;
    Brn iSupportedScheme;
    Media::BwsMode iMode;
    Uri iUri; // only used inside Stream() but too large to put on the stack
    TUint iFrame;
    TBool iRunning;
    TBool iRepairing;
    TBool iStreamMsgDue;
    OhmMsgAudioBlob* iRepairFirst;
    std::vector<OhmMsgAudioBlob*> iRepairFrames;
    Timer* iTimerRepair;
    Bws<Media::EncodedAudio::kMaxBytes> iFrameBuf;
    TUint iAddr; // FIXME - should listen for subnet changes and update this value
    Media::BwsTrackUri iTrackUri;
};

class DefaultTimestamper : public IOhmTimestamper, private INonCopyable // trivial implementation that just returns the current time
{
public:
    DefaultTimestamper(Environment& aEnv);
private: // from IOhmTimestamper
    TUint Timestamp();
private:
    Environment& iEnv;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROTOCOL_OHBASE
