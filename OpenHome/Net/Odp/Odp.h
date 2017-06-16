#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

EXCEPTION(OdpError)
EXCEPTION(OdpUnsupported)

namespace OpenHome {
namespace Net {

class Odp
{
public:
    static const Brn kTypeAnnouncement;
    static const Brn kTypeAction;
    static const Brn kTypeActionResponse;
    static const Brn kTypeSubscribe;
    static const Brn kTypeSubscribeResponse;
    static const Brn kTypeUnsubscribe;
    static const Brn kTypeUnsubscribeResponse;
    static const Brn kTypeNotify;
    static const Brn kKeyType;
    static const Brn kKeyProtocolVersion;
    static const Brn kKeyDevices;
    static const Brn kKeyId;
    static const Brn kKeyAlias;
    static const Brn kKeyServices;
    static const Brn kKeyDevice;
    static const Brn kKeyService;
    static const Brn kKeyAction;
    static const Brn kKeyUserAgent;
    static const Brn kKeyArguments;
    static const Brn kKeyError;
    static const Brn kKeySid;
    static const Brn kKeyProperties;
    static const Brn kKeyName;
    static const Brn kKeyVersion;
    static const Brn kKeyCode;
    static const Brn kKeyDescription;
};

} // namespace Net
} // namespace OpenHome
