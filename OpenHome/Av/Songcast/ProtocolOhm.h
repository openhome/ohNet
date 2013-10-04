#ifndef HEADER_PROTOCOL_OHM
#define HEADER_PROTOCOL_OHM

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

class ProtocolOhm : public ProtocolOhBase
{
    static const TUint kMaxFrameBytes = 16*1024;
    static const TUint kAddMembershipDelayMs = 100;
    static const TUint kTimerJoinTimeoutMs = 300;
    static const TUint kTimerListenTimeoutMs = 10000;
public:
	ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aMsgFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const Brx& aMode);
    ~ProtocolOhm();
	void Stop();
private: // from ProtocolOhBase
    void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
    void RequestResend(const Brx& aFrames);
private: // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    void SendJoin();
    void SendListen();
    void Send(TUint aType);
private:
    OhmSocket iSocket;
    Srs<kMaxFrameBytes> iReadBuffer;
    Endpoint iEndpoint;
    Timer* iTimerJoin;
    Timer* iTimerListen;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROTOCOL_OHM
