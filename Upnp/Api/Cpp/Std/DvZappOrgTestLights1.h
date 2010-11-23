#ifndef HEADER_DVZAPPORGTESTLIGHTS1CPP
#define HEADER_DVZAPPORGTESTLIGHTS1CPP

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
 * Provider for the zapp.org:TestLights:1 UPnP service
 */
class DvProviderZappOrgTestLights1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestLights1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestLights1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetCount is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetCount must be overridden if this is called.
     */
    void EnableActionGetCount();
    /**
     * Signal that the action GetRoom is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRoom must be overridden if this is called.
     */
    void EnableActionGetRoom();
    /**
     * Signal that the action GetName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetName must be overridden if this is called.
     */
    void EnableActionGetName();
    /**
     * Signal that the action GetPosition is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetPosition must be overridden if this is called.
     */
    void EnableActionGetPosition();
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
     * Signal that the action GetColorComponents is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetColorComponents must be overridden if this is called.
     */
    void EnableActionGetColorComponents();
private:
    /**
     * GetCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCount action for the owning device.
     * Must be implemented iff EnableActionGetCount was called.
     */
    virtual void GetCount(uint32_t aVersion, uint32_t& aCount);
    /**
     * GetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRoom action for the owning device.
     * Must be implemented iff EnableActionGetRoom was called.
     */
    virtual void GetRoom(uint32_t aVersion, uint32_t aIndex, std::string& aRoomName);
    /**
     * GetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetName action for the owning device.
     * Must be implemented iff EnableActionGetName was called.
     */
    virtual void GetName(uint32_t aVersion, uint32_t aIndex, std::string& aFriendlyName);
    /**
     * GetPosition action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPosition action for the owning device.
     * Must be implemented iff EnableActionGetPosition was called.
     */
    virtual void GetPosition(uint32_t aVersion, uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    /**
     * SetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     * Must be implemented iff EnableActionSetColor was called.
     */
    virtual void SetColor(uint32_t aVersion, uint32_t aIndex, uint32_t aColor);
    /**
     * GetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     * Must be implemented iff EnableActionGetColor was called.
     */
    virtual void GetColor(uint32_t aVersion, uint32_t aIndex, uint32_t& aColor);
    /**
     * GetColorComponents action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColorComponents action for the owning device.
     * Must be implemented iff EnableActionGetColorComponents was called.
     */
    virtual void GetColorComponents(uint32_t aVersion, uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
private:
    DvProviderZappOrgTestLights1Cpp();
    void DoGetCount(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetPosition(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorComponents(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTLIGHTS1CPP

