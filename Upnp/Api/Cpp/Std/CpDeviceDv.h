#ifndef HEADER_CPDEVICEDVCPP
#define HEADER_CPDEVICEDVCPP

#include <Std/CpDevice.h>

namespace Zapp {

class DvDeviceStd;
class CpiDeviceDv;

class CpDeviceDvCpp : public CpDeviceCpp
{
public:
    static CpDeviceDvCpp* New(DvDeviceStd& aDevice);
    ~CpDeviceDvCpp();
private:
    CpDeviceDvCpp(CpiDeviceDv& aDevice);
};

} // namespace Zapp

#endif // HEADER_CPDEVICEDVCPP
