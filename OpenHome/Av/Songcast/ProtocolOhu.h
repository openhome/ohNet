#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>
#include <OpenHome/Private/Network.h>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Media {
    class TrackFactory;
}
namespace Av {

class IOhmMsgFactory;

class ProtocolOhu : public ProtocolOhBase
{
    static const TUint kTimerLeaveTimeoutMs = 50;
    static const TUint kMaxSlaveCount = 4;
public:
    ProtocolOhu(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory, const Brx& aMode);
    ~ProtocolOhu();
private: // from ProtocolOhBase
    Media::ProtocolStreamResult Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) override;
    void ProcessTimestamps(const OhmMsgAudio& aMsg, TBool& aDiscard) override;
private: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
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
    Timer* iTimerLeave;
    TBool iLeaving;
    TBool iStopped;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    Bws<kMaxFrameBytes> iMessageBuffer;
    TUint iNextFlushId;
};

} // namespace Av
} // namespace OpenHome

