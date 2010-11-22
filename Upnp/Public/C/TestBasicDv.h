#ifndef HEADER_TESTBASICDVC
#define HEADER_TESTBASICDVC

#include <C/DvDevice.h>

namespace Zapp {

class DeviceBasicC
{
public:
    DeviceBasicC();
    ~DeviceBasicC();
    DvDeviceC Device();
private:
    DvDeviceC iDevice;
    THandle iTestBasic;
};

} // namespace Zapp

#endif // HEADER_TESTBASICDVC
