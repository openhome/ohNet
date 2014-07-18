/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_CPI_STACK
#define HEADER_CPI_STACK

#include <OpenHome/Types.h>
#include <OpenHome/Private/Env.h>
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
    CpStack(Environment& aEnv);
    Environment& Env() { return iEnv; }
    OpenHome::Net::InvocationManager& InvocationManager();
    OpenHome::Net::XmlFetchManager& XmlFetchManager();
    CpiSubscriptionManager& SubscriptionManager();
    CpiDeviceListUpdater& DeviceListUpdater();
private:
    ~CpStack();
private:
    OpenHome::Environment& iEnv;
    OpenHome::Net::InvocationManager* iInvocationManager;
    OpenHome::Net::XmlFetchManager* iXmlFetchManager;
    CpiSubscriptionManager* iSubscriptionManager;
    CpiDeviceListUpdater* iDeviceListUpdater;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPI_STACK
