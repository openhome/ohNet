#ifndef HEADER_TESTBASICDVC
#define HEADER_TESTBASICDVC

#include <C/DvDevice.h>

namespace OpenHome {
namespace Net {

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

} // namespace Net
} // namespace OpenHome

#endif // HEADER_TESTBASICDVC
