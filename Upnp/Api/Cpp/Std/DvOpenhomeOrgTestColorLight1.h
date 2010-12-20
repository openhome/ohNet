#ifndef HEADER_DVOPENHOMEORGTESTCOLORLIGHT1CPP
#define HEADER_DVOPENHOMEORGTESTCOLORLIGHT1CPP

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
 * Provider for the openhome.org:TestColorLight:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestColorLight1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestColorLight1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestColorLight1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetName must be overridden if this is called.
     */
    void EnableActionGetName();
    /**
     * Signal that the action SetColor is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetColor must be overridden if this is called.
     */
    void EnableActionSetColor();
    /**
     * Signal that the action GetColor is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetColor must be overridden if this is called.
     */
    void EnableActionGetColor();
    /**
     * Signal that the action GetMaxColors is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetMaxColors must be overridden if this is called.
     */
    void EnableActionGetMaxColors();
private:
    /**
     * GetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetName action for the owning device.
     * Must be implemented iff EnableActionGetName was called.
     */
    virtual void GetName(uint32_t aVersion, std::string& aFriendlyName);
    /**
     * SetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     * Must be implemented iff EnableActionSetColor was called.
     */
    virtual void SetColor(uint32_t aVersion, uint32_t aRed, uint32_t aGreen, uint32_t aBlue);
    /**
     * GetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     * Must be implemented iff EnableActionGetColor was called.
     */
    virtual void GetColor(uint32_t aVersion, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    /**
     * GetMaxColors action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMaxColors action for the owning device.
     * Must be implemented iff EnableActionGetMaxColors was called.
     */
    virtual void GetMaxColors(uint32_t aVersion, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
private:
    DvProviderOpenhomeOrgTestColorLight1Cpp();
    void DoGetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetMaxColors(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVOPENHOMEORGTESTCOLORLIGHT1CPP

