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
#include <OpenHome/Net/Private/DviPropertyUpdateCollection.h>
#include <OpenHome/Private/Standard.h>

#include <vector>

namespace OpenHome {
namespace Net {

class DvStack : private IStack, private INonCopyable
{
public:
    DvStack(Stack& aStack);
    OpenHome::Net::Stack& Stack() { return iStack; }
    TUint BootId();
    TUint NextBootId();
    void UpdateBootId();
    DviServerUpnp& ServerUpnp();
    DviDeviceMap& DeviceMap();
    DviSubscriptionManager& SubscriptionManager();
    IMdnsProvider* MdnsProvider();
    DviPropertyUpdateCollection& PropertyUpdateCollection();
private:
    ~DvStack();
private:
    OpenHome::Net::Stack& iStack;
    TUint iBootId;
    TUint iNextBootId;
    DviServerUpnp* iDviServerUpnp;
    DviDeviceMap* iDviDeviceMap;
    DviSubscriptionManager* iSubscriptionManager;
    DviServerWebSocket* iDviServerWebSocket;
    IMdnsProvider* iMdns;
    DviPropertyUpdateCollection* iPropertyUpdateCollection;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVI_STACK
