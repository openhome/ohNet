#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/ProtocolOhBase.h>

namespace OpenHome {
    class Environment;
namespace Media {
    class TrackFactory;
}
namespace Av {

class IOhmMsgFactory;
class IOhmTimestamper;

class ProtocolOhm : public ProtocolOhBase
{
public:
    ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aMsgFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper* aTimestamper, const Brx& aMode);
private: // from ProtocolOhBase
    Media::ProtocolStreamResult Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) override;
private: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private:
    TUint iNextFlushId;
    TBool iStopped;
};

} // namespace Av
} // namespace OpenHome

