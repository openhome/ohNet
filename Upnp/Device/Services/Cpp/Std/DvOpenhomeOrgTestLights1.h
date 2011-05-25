#ifndef HEADER_DVOPENHOMEORGTESTLIGHTS1CPP
#define HEADER_DVOPENHOMEORGTESTLIGHTS1CPP

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the openhome.org:TestLights:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestLights1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestLights1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestLights1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetCount is supported.
     * The action's availability will be published in the device's service.xml.
     * GetCount must be overridden if this is called.
     */
    void EnableActionGetCount();
    /**
     * Signal that the action GetRoom is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRoom must be overridden if this is called.
     */
    void EnableActionGetRoom();
    /**
     * Signal that the action GetName is supported.
     * The action's availability will be published in the device's service.xml.
     * GetName must be overridden if this is called.
     */
    void EnableActionGetName();
    /**
     * Signal that the action GetPosition is supported.
     * The action's availability will be published in the device's service.xml.
     * GetPosition must be overridden if this is called.
     */
    void EnableActionGetPosition();
    /**
     * Signal that the action SetColor is supported.
     * The action's availability will be published in the device's service.xml.
     * SetColor must be overridden if this is called.
     */
    void EnableActionSetColor();
    /**
     * Signal that the action GetColor is supported.
     * The action's availability will be published in the device's service.xml.
     * GetColor must be overridden if this is called.
     */
    void EnableActionGetColor();
    /**
     * Signal that the action GetColorComponents is supported.
     * The action's availability will be published in the device's service.xml.
     * GetColorComponents must be overridden if this is called.
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
    DvProviderOpenhomeOrgTestLights1Cpp();
    void DoGetCount(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetPosition(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorComponents(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGTESTLIGHTS1CPP

