#ifndef HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1CPP
#define HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1CPP

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
 * Provider for the openhome.org:TestDimmableLight:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestDimmableLight1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestDimmableLight1Cpp() {}
    /**
     * Set the value of the A_ARG_Level property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyA_ARG_Level(uint32_t aValue);
    /**
     * Get a copy of the value of the A_ARG_Level property
     */
    void GetPropertyA_ARG_Level(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestDimmableLight1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * GetLevel must be overridden if this is called.
     */
    void EnableActionGetLevel();
    /**
     * Signal that the action SetLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetLevel must be overridden if this is called.
     */
    void EnableActionSetLevel();
private:
    /**
     * GetLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLevel action for the owning device.
     * Must be implemented iff EnableActionGetLevel was called.
     */
    virtual void GetLevel(uint32_t aVersion, uint32_t& aLevel);
    /**
     * SetLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetLevel action for the owning device.
     * Must be implemented iff EnableActionSetLevel was called.
     */
    virtual void SetLevel(uint32_t aVersion, uint32_t aLevel);
private:
    DvProviderOpenhomeOrgTestDimmableLight1Cpp();
    void DoGetLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetLevel(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Zapp

#endif // HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1CPP

