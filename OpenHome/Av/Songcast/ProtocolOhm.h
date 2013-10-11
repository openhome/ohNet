#ifndef HEADER_PROTOCOL_OHM
#define HEADER_PROTOCOL_OHM

#include <OpenHome/OhNetTypes.h>
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
	ProtocolOhm(Environment& aEnv, IOhmMsgFactory& aMsgFactory, Media::TrackFactory& aTrackFactory, IOhmTimestamper& aTimestamper, const Brx& aMode);
    ~ProtocolOhm();
private: // from ProtocolOhBase
    void Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint);
private: // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_PROTOCOL_OHM
