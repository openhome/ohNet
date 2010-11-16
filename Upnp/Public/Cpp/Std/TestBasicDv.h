#ifndef HEADER_TESTBASICDV
#define HEADER_TESTBASICDV

namespace Zapp {

class DvDeviceStd;
class ProviderTestBasic;
    
class DeviceBasic
{
public:
    DeviceBasic();
    ~DeviceBasic();
    DvDeviceStd& Device();
private:
    DvDeviceStd* iDevice;
    ProviderTestBasic* iTestBasic;
};

} // namespace Zapp

#endif // HEADER_TESTBASICDV
