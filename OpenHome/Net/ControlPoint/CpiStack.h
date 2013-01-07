/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_CPI_STACK
#define HEADER_CPI_STACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Private/Standard.h>

#include <vector>

namespace OpenHome {
namespace Net {

class InvocationManager;
class XmlFetchManager;
class CpiSubscriptionManager;
class CpiDeviceListUpdater;

class CpStack : public IStack, private INonCopyable
{
public:
    CpStack(Stack& aStack);
    Stack& GetStack() { return iStack; }
    OpenHome::Net::InvocationManager& InvocationManager();
    OpenHome::Net::XmlFetchManager& XmlFetchManager();
    CpiSubscriptionManager& SubscriptionManager();
    CpiDeviceListUpdater& DeviceListUpdater();
private:
    ~CpStack();
private:
    OpenHome::Net::Stack& iStack;
    OpenHome::Net::InvocationManager* iInvocationManager;
    OpenHome::Net::XmlFetchManager* iXmlFetchManager;
    CpiSubscriptionManager* iSubscriptionManager;
    CpiDeviceListUpdater* iDeviceListUpdater;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPI_STACK
