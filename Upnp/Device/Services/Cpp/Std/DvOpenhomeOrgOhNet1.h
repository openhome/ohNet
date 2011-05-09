#ifndef HEADER_DVOPENHOMEORGOHNET1CPP
#define HEADER_DVOPENHOMEORGOHNET1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

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
class DvProviderOpenhomeOrgOhNet1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgOhNet1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgOhNet1Cpp(DvDeviceStd& aDevice);
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
    virtual void GetWebSocketPort(uint32_t aVersion, uint32_t& aPort);
private:
    DvProviderOpenhomeOrgOhNet1Cpp();
    void DoGetWebSocketPort(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVOPENHOMEORGOHNET1CPP

