#ifndef HEADER_DVUPNPORGSWITCHPOWER1
#define HEADER_DVUPNPORGSWITCHPOWER1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:SwitchPower:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgSwitchPower1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgSwitchPower1() {}
    /**
     * Set the value of the Status property
     *
     * Can only be called if EnablePropertyStatus has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStatus(TBool aValue);
    /**
     * Get a copy of the value of the Status property
     *
     * Can only be called if EnablePropertyStatus has previously been called.
     */
    void GetPropertyStatus(TBool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgSwitchPower1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgSwitchPower1(DviDevice& aDevice);
    /**
     * Enable the Status property.
     */
    void EnablePropertyStatus();
    /**
     * Signal that the action SetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * SetTarget must be overridden if this is called.
     */
    void EnableActionSetTarget();
    /**
     * Signal that the action GetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * GetTarget must be overridden if this is called.
     */
    void EnableActionGetTarget();
    /**
     * Signal that the action GetStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * GetStatus must be overridden if this is called.
     */
    void EnableActionGetStatus();
private:
    /**
     * SetTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetTarget action for the owning device.
     * Must be implemented iff EnableActionSetTarget was called.
     */
    virtual void SetTarget(IDvInvocation& aInvocation, TBool anewTargetValue);
    /**
     * GetTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTarget action for the owning device.
     * Must be implemented iff EnableActionGetTarget was called.
     */
    virtual void GetTarget(IDvInvocation& aInvocation, IDvInvocationResponseBool& aRetTargetValue);
    /**
     * GetStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStatus action for the owning device.
     * Must be implemented iff EnableActionGetStatus was called.
     */
    virtual void GetStatus(IDvInvocation& aInvocation, IDvInvocationResponseBool& aResultStatus);
private:
    DvProviderUpnpOrgSwitchPower1();
    void Construct();
    void DoSetTarget(IDviInvocation& aInvocation);
    void DoGetTarget(IDviInvocation& aInvocation);
    void DoGetStatus(IDviInvocation& aInvocation);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGSWITCHPOWER1

