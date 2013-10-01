#ifndef HEADER_PROTOCOL_OHMU
#define HEADER_PROTOCOL_OHMU

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Av/Songcast/OhmSocket.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {

class ProtocolOhu : public ProtocolOhBase
{
    static const TUint kMaxFrameBytes = 16*1024;
    static const TUint kAddMembershipDelayMs = 100;
    static const TUint kTimerJoinTimeoutMs = 300;
    static const TUint kTimerListenTimeoutMs = 10000;
    static const TUint kTimerLeaveTimeoutMs = 50;
    static const TUint kMaxSlaveCount = 4;
public:
    ProtocolOhu(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const Brx& aMode);
    ~ProtocolOhu();
    void SetInterface(TIpAddress aValue);
    void SetTtl(TUint aValue);
    void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
    void Stop();
private: // from ProtocolOhm
    void RequestResend(const Brx& aFrames);
private: // from Media::Protocol
    Media::ProtocolStreamResult Stream(const Brx& aUri);
private:
    void HandleAudio(const OhmHeader& aHeader);
    void HandleTrack(const OhmHeader& aHeader);
    void HandleMetatext(const OhmHeader& aHeader);
    void HandleSlave(const OhmHeader& aHeader);
    void Broadcast(OhmMsg* aMsg);
    void SendJoin();
    void SendListen();
    void SendLeave();
    void Send(TUint aType);
    void TimerLeaveExpired();
private:
    Environment& iEnv;
    IOhmMsgFactory& iFactory;
    OhmSocket iSocket;
    Srs<kMaxFrameBytes> iReadBuffer;
    Endpoint iEndpoint;
    Timer* iTimerJoin;
    Timer* iTimerListen;
    Timer* iTimerLeave;
    TBool iLeaving;
    TUint iSlaveCount;
    Endpoint iSlaveList[kMaxSlaveCount];
    Bws<kMaxFrameBytes> iMessageBuffer;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROTOCOL_OHMU
