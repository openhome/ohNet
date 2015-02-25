#ifndef HEADER_PIPELINE_PROTOCOL_FACTORY
#define HEADER_PIPELINE_PROTOCOL_FACTORY

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
    class Brx;
namespace Configuration {
    class IStoreReadOnly;
    class IConfigInitialiser;
}
namespace Av {
    class Credentials;
}
namespace Media {

class Protocol;

class ProtocolFactory
{
public:
    static Protocol* NewHls(Environment& aEnv, const Brx& aUserAgent);
    static Protocol* NewHttp(Environment& aEnv);
    static Protocol* NewHttps(Environment& aEnv);
    static Protocol* NewFile(Environment& aEnv);
    static Protocol* NewTone(Environment& aEnv);
    static Protocol* NewRtsp(Environment& aEnv, const Brx& aGuid);
    static Protocol* NewTidal(Environment& aEnv, const Brx& aToken, Av::Credentials& aCredentialsManager, Configuration::IConfigInitialiser& aConfigInitialiser);
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_PROTOCOL_FACTORY
