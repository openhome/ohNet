#ifndef HEADER_PIPELINE_PROTOCOL_FACTORY
#define HEADER_PIPELINE_PROTOCOL_FACTORY

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
    class Brx;
namespace Configuration {
    class IConfigInitialiser;
}
namespace Media {

class Protocol;

class ProtocolFactory
{
public:
    static Protocol* NewHttp(Environment& aEnv);
    static Protocol* NewHttps(Environment& aEnv);
    static Protocol* NewFile(Environment& aEnv);
    static Protocol* NewTone(Environment& aEnv);
    static Protocol* NewRtsp(Environment& aEnv, const Brx& aGuid);
    static Protocol* NewTidal(Environment& aEnv, const Brx& aToken, const Brx& aRsaPrivateKey, Configuration::IConfigInitialiser& aConfigInitialiser);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PROTOCOL_FACTORY
