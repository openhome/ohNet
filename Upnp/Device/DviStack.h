/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_DVI_STACK
#define HEADER_DVI_STACK

#include <ZappTypes.h>
#include <Stack.h>
#include <DviServerUpnp.h>
#include <DviDevice.h>
#include <DviSubscription.h>

#include <vector>

namespace Zapp {

class DviStack : private IStack
{
public:
    DviStack();
    static TUint BootId();
    static TUint NextBootId();
    static void UpdateBootId();
    static DviServerUpnp& ServerUpnp();
    static DviDeviceMap& DeviceMap();
    static DviSubscriptionManager& SubscriptionManager();
private:
    ~DviStack();
    static DviStack* Self();
private:
    TUint iBootId;
    TUint iNextBootId;
    DviServerUpnp* iDviServerUpnp;
    DviDeviceMap* iDviDeviceMap;
    DviSubscriptionManager* iSubscriptionManager;
};

} // namespace Zapp

#endif // HEADER_DVI_STACK
