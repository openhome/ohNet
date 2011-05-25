#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

namespace OpenHome {
namespace Net {

class DvDeviceStdStandard;
class ProviderTestBasic;
    
class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
    DvDeviceStdStandard& Device();
private:
    DvDeviceStdStandard* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICDV
