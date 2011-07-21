/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_DVI_STACK
#define HEADER_DVI_STACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/DviServerUpnp.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Net/Private/DviServerWebSocket.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Bonjour.h>

#include <vector>

namespace OpenHome {
namespace Net {

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
    static IMdnsProvider* MdnsProvider();
private:
    ~DviStack();
    static DviStack* Self();
private:
    TUint iBootId;
    TUint iNextBootId;
    DviServerUpnp* iDviServerUpnp;
    DviDeviceMap* iDviDeviceMap;
    DviSubscriptionManager* iSubscriptionManager;
    DviServerWebSocket* iDviServerWebSocket;
    IMdnsProvider* iMdns;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_STACK
