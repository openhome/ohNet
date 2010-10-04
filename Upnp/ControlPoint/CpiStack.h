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

#include <vector>

namespace Zapp {

class CpiStack : public IStack
{
public:
    CpiStack();
    static Zapp::InvocationManager& InvocationManager();
    static Zapp::XmlFetchManager& XmlFetchManager();
    static Zapp::SubscriptionManager& SubscriptionManager();
private:
    ~CpiStack();
    static CpiStack* Self();
private:
    Zapp::InvocationManager* iInvocationManager;
    Zapp::XmlFetchManager* iXmlFetchManager;
    Zapp::SubscriptionManager* iSubscriptionManager;
};

} // namespace Zapp

#endif // HEADER_CPI_STACK
