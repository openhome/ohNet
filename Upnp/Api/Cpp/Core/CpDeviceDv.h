#ifndef HEADER_CPDEVICEDV
#define HEADER_CPDEVICEDV

#include <Core/CpDevice.h>

namespace Zapp {

class DvDevice;
class CpiDeviceDv;

class CpDeviceDv : public CpDevice
{
public:
    static CpDeviceDv* New(DvDevice& aDevice);
    ~CpDeviceDv();
private:
    CpDeviceDv(CpiDeviceDv& aDevice);
};

} // namespace Zapp

#endif // HEADER_CPDEVICEDV
