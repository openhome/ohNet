#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

namespace OpenHome {
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
    DeviceBasic(EProtocol aProtocol);
    ~DeviceBasic();
    DvDeviceStd& Device();
private:
    DvDeviceStd* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICDV
