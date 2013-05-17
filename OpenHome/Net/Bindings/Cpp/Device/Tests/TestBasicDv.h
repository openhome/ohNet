#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

namespace OpenHome {
class Environment;
namespace Net {

class DvDeviceStd;
class ProviderTestBasic;
    
class DeviceBasic
{
public:
    enum EProtocol {
        eProtocolNone
       ,eProtocolUpnp
    };
public:
    DeviceBasic(Environment& aEnv, EProtocol aProtocol);
    ~DeviceBasic();
    DvDeviceStd& Device();
private:
    DvDeviceStd* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICDV
