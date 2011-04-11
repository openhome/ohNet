#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

namespace Zapp {

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

} // namespace Zapp

#endif // HEADER_TESTBASICDV
