#ifndef HEADER_DVOPENHOMEORGOHNET1
#define HEADER_DVOPENHOMEORGOHNET1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the openhome.org:OhNet:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgOhNet1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgOhNet1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgOhNet1(DvDevice& aDevice);
    /**
     * Signal that the action GetWebSocketPort is supported.
     * The action's availability will be published in the device's service.xml.
     * GetWebSocketPort must be overridden if this is called.
     */
    void EnableActionGetWebSocketPort();
private:
    /**
     * GetWebSocketPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetWebSocketPort action for the owning device.
     * Must be implemented iff EnableActionGetWebSocketPort was called.
     */
    virtual void GetWebSocketPort(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aPort);
private:
    DvProviderOpenhomeOrgOhNet1();
    void DoGetWebSocketPort(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVOPENHOMEORGOHNET1

