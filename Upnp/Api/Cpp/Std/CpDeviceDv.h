#ifndef HEADER_CPDEVICEDVCPP
#define HEADER_CPDEVICEDVCPP

#include <Std/CpDevice.h>

namespace Zapp {

class DvDeviceStd;
class CpiDeviceDv;

/**
 * Control point device which communicates directly with a device stack's device
 */
class CpDeviceDvCpp : public CpDeviceCpp
{
public:
    /**
     * Factory function.  Use this instead of the c'tor
     *
     * @param[in] aDevice  The device stack device to control
     */
    static CpDeviceDvCpp* New(DvDeviceStd& aDevice);
private:
    /**
     * Not for external use.  Use CpDeviceDv::New() instead
     */
    CpDeviceDvCpp(CpiDeviceDv& aDevice);
    /**
     * Not for external use.  Use RemoveRef() instead.
     */
    ~CpDeviceDvCpp();
};

} // namespace Zapp

#endif // HEADER_CPDEVICEDVCPP
