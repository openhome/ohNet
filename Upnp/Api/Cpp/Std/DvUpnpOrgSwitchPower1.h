#ifndef HEADER_DVUPNPORGSWITCHPOWER1CPP
#define HEADER_DVUPNPORGSWITCHPOWER1CPP

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
 * Provider for the upnp.org:SwitchPower:1 UPnP service
 */
class DvProviderUpnpOrgSwitchPower1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgSwitchPower1Cpp() {}
    /**
     * Set the value of the Status property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStatus(bool aValue);
    /**
     * Get a copy of the value of the Status property
     */
    void GetPropertyStatus(bool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgSwitchPower1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action SetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetTarget must be overridden if this is called.
     */
    void EnableActionSetTarget();
    /**
     * Signal that the action GetTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetTarget must be overridden if this is called.
     */
    void EnableActionGetTarget();
    /**
     * Signal that the action GetStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetStatus must be overridden if this is called.
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
    virtual void SetTarget(uint32_t aVersion, bool anewTargetValue);
    /**
     * GetTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTarget action for the owning device.
     * Must be implemented iff EnableActionGetTarget was called.
     */
    virtual void GetTarget(uint32_t aVersion, bool& aRetTargetValue);
    /**
     * GetStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStatus action for the owning device.
     * Must be implemented iff EnableActionGetStatus was called.
     */
    virtual void GetStatus(uint32_t aVersion, bool& aResultStatus);
private:
    DvProviderUpnpOrgSwitchPower1Cpp();
    void DoSetTarget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetTarget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetStatus(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSWITCHPOWER1CPP

