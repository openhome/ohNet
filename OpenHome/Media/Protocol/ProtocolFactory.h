#pragma once

#include <OpenHome/Types.h>

namespace OpenHome {
    class Environment;
    class Brx;
    class IUnixTimestamp;
namespace Configuration {
    class IStoreReadOnly;
    class IConfigInitialiser;
}
namespace Av {
    class Credentials;
    class IMediaPlayer;
}
namespace Media {

class Protocol;
class IServerObserver;

class ProtocolFactory
{
public:
    static Protocol* NewHls(Environment& aEnv, const Brx& aUserAgent);
    static Protocol* NewHttp(Environment& aEnv, const Brx& aUserAgent); // UA is optional so can be empty
    static Protocol* NewHttp(Environment& aEnv, const Brx& aUserAgent, IServerObserver& aServerObserver); // UA is optional so can be empty
    static Protocol* NewHttps(Environment& aEnv);
    static Protocol* NewFile(Environment& aEnv);
    static Protocol* NewTone(Environment& aEnv);
    static Protocol* NewRtsp(Environment& aEnv, const Brx& aGuid);
    static Protocol* NewTidal(Environment& aEnv, const Brx& aToken, Av::IMediaPlayer& aMediaPlayer);
    static Protocol* NewQobuz(const Brx& aAppId, const Brx& aAppSecret, Av::IMediaPlayer& aMediaPlayer);
    static Protocol* NewCalmRadio(Environment& aEnv, const Brx& aUserAgent, Av::IMediaPlayer& aMediaPlayer); // UA is optional so can be empty
};

} // namespace Media
} // namespace OpenHome

