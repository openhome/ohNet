/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_CPI_STACK
#define HEADER_CPI_STACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Net/Private/XmlFetcher.h>
#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Private/CpiDevice.h>

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
    static CpiActiveDevices& ActiveDevices();
    static CpiDeviceListUpdater& DeviceListUpdater();
private:
    ~CpiStack();
    static CpiStack* Self();
private:
    OpenHome::Net::InvocationManager* iInvocationManager;
    OpenHome::Net::XmlFetchManager* iXmlFetchManager;
    CpiSubscriptionManager* iSubscriptionManager;
    CpiActiveDevices* iActiveDevices;
    CpiDeviceListUpdater* iDeviceListUpdater;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPI_STACK
