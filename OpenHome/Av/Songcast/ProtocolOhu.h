#ifndef HEADER_PROTOCOL_OHU
#define HEADER_PROTOCOL_OHU

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/PowerManager.h>

namespace OpenHome {
    class Environment;
    class IPowerManager;
    class Timer;
namespace Media {
    class TrackFactory;
}
namespace Av {

class IOhmMsgFactory;

class ProtocolOhu : public ProtocolOhBase, public IPowerHandler
{
    static const TUint kTimerLeaveTimeoutMs = 50;
    static const TUint kMaxSlaveCount = 4;
public:
    ProtocolOhu(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory, const Brx& aMode, IPowerManager& aPowerManager);
    ~ProtocolOhu();
private: // from ProtocolOhBase
    Media::ProtocolStreamResult Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) override;
private: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId) override;
private: // from IPowerHandler
    void PowerUp() override;
    void PowerDown() override;
private:
    void HandleAudio(const OhmHeader& aHeader);
    void HandleTrack(const OhmHeader& aHeader);
    void HandleMetatext(const OhmHeader& aHeader);
    void HandleSlave(const OhmHeader& aHeader);
    void Broadcast(OhmMsg* aMsg);
    void SendLeave();
    void TimerLeaveExpired();
private:
    Mutex iLeaveLock;
    IPowerManagerObserver* iPowerObserver;
    Timer* iTimerLeave;
    TBool iLeaving;
    TBool iStopped;
    TBool iActive;
    TBool iStarving;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    Bws<kMaxFrameBytes> iMessageBuffer;
    TUint iNextFlushId;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROTOCOL_OHU
