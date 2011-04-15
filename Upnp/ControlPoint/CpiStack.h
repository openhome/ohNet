/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_CPI_STACK
#define HEADER_CPI_STACK

#include <ZappTypes.h>
#include <Stack.h>
#include <CpiService.h>
#include <XmlFetcher.h>
#include <CpiSubscription.h>
#include <CpiDevice.h>

#include <vector>

namespace Zapp {

class CpiStack : public IStack
{
public:
    CpiStack();
    static Zapp::InvocationManager& InvocationManager();
    static Zapp::XmlFetchManager& XmlFetchManager();
    static CpiSubscriptionManager& SubscriptionManager();
    static CpiDeviceListUpdater& DeviceListUpdater();
private:
    ~CpiStack();
    static CpiStack* Self();
private:
    Zapp::InvocationManager* iInvocationManager;
    Zapp::XmlFetchManager* iXmlFetchManager;
    CpiSubscriptionManager* iSubscriptionManager;
    CpiDeviceListUpdater* iDeviceListUpdater;
};

} // namespace Zapp

#endif // HEADER_CPI_STACK
