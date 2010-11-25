#ifndef HEADER_CPDEVICEDV
#define HEADER_CPDEVICEDV

#include <Core/CpDevice.h>

namespace Zapp {

class DvDevice;
class CpiDeviceDv;

/**
 * Control point device which communicates directly with a device stack's device
 * @ingroup ControlPoint
 */
class CpDeviceDv : public CpDevice
{
public:
    /**
     * Factory function.  Use this instead of the c'tor
     *
     * @param[in] aDevice  The device stack device to control
     */
    static CpDeviceDv* New(DvDevice& aDevice);
private:
    /**
     * Not for external use.  Use CpDeviceDv::New() instead
     */
    CpDeviceDv(CpiDeviceDv& aDevice);
    /**
     * Not for external use.  Use RemoveRef() instead.
     */
    ~CpDeviceDv();
};

} // namespace Zapp

#endif // HEADER_CPDEVICEDV
