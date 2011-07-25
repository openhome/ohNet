/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_CPI_STACK
#define HEADER_CPI_STACK

#include <OhNetTypes.h>
#include <Stack.h>
#include <CpiService.h>
#include <XmlFetcher.h>
#include <CpiSubscription.h>
#include <CpiDevice.h>

#include <vector>

namespace OpenHome {
namespace Net {

class CpiStack : public IStack
{
public:
    CpiStack();
    static OpenHome::Net::InvocationManager& InvocationManager();
    static OpenHome::Net::XmlFetchManager& XmlFetchManager();
    static CpiSubscriptionManager& SubscriptionManager();
    static CpiDeviceListUpdater& DeviceListUpdater();
private:
    ~CpiStack();
    static CpiStack* Self();
private:
    OpenHome::Net::InvocationManager* iInvocationManager;
    OpenHome::Net::XmlFetchManager* iXmlFetchManager;
    CpiSubscriptionManager* iSubscriptionManager;
    CpiDeviceListUpdater* iDeviceListUpdater;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPI_STACK
