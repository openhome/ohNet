#ifndef HEADER_CPDEVICEDV
#define HEADER_CPDEVICEDV

#include <OpenHome/Net/Core/CpDevice.h>

namespace OpenHome {
namespace Net {

class DvDevice;
class CpiDeviceDv;
class CpStack;

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
    static CpDeviceDv* New(CpStack& aCpStack, DvDevice& aDevice);
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

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPDEVICEDV
