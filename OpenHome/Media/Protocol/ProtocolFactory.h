#ifndef HEADER_PIPELINE_PROTOCOL_FACTORY
#define HEADER_PIPELINE_PROTOCOL_FACTORY

#include <OpenHome/OhNetTypes.h>

namespace OpenHome {
    class Environment;
    class Brx;
namespace Av {
    class IRaopDiscovery;
    class UdpServerManager;
}
namespace Media {

class Protocol;

class ProtocolFactory
{
public:
    static Protocol* NewHttp(Environment& aEnv);
    static Protocol* NewFile(Environment& aEnv);
    static Protocol* NewTone(Environment& aEnv);
    static Protocol* NewRtsp(Environment& aEnv, const Brx& aGuid);
    static Protocol* NewRaop(Environment& aEnv, Av::IRaopDiscovery& aDiscovery, Av::UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId); // FIXME
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PROTOCOL_FACTORY
