#ifndef HEADER_DVOPENHOMEORGTESTLIGHTS1CPP
#define HEADER_DVOPENHOMEORGTESTLIGHTS1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

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
    virtual void GetCount(IDvInvocationStd& aInvocation, uint32_t& aCount);
    /**
     * GetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRoom action for the owning device.
     * Must be implemented iff EnableActionGetRoom was called.
     */
    virtual void GetRoom(IDvInvocationStd& aInvocation, uint32_t aIndex, std::string& aRoomName);
    /**
     * GetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetName action for the owning device.
     * Must be implemented iff EnableActionGetName was called.
     */
    virtual void GetName(IDvInvocationStd& aInvocation, uint32_t aIndex, std::string& aFriendlyName);
    /**
     * GetPosition action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPosition action for the owning device.
     * Must be implemented iff EnableActionGetPosition was called.
     */
    virtual void GetPosition(IDvInvocationStd& aInvocation, uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    /**
     * SetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     * Must be implemented iff EnableActionSetColor was called.
     */
    virtual void SetColor(IDvInvocationStd& aInvocation, uint32_t aIndex, uint32_t aColor);
    /**
     * GetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     * Must be implemented iff EnableActionGetColor was called.
     */
    virtual void GetColor(IDvInvocationStd& aInvocation, uint32_t aIndex, uint32_t& aColor);
    /**
     * GetColorComponents action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColorComponents action for the owning device.
     * Must be implemented iff EnableActionGetColorComponents was called.
     */
    virtual void GetColorComponents(IDvInvocationStd& aInvocation, uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
private:
    DvProviderOpenhomeOrgTestLights1Cpp();
    void DoGetCount(IDviInvocation& aInvocation);
    void DoGetRoom(IDviInvocation& aInvocation);
    void DoGetName(IDviInvocation& aInvocation);
    void DoGetPosition(IDviInvocation& aInvocation);
    void DoSetColor(IDviInvocation& aInvocation);
    void DoGetColor(IDviInvocation& aInvocation);
    void DoGetColorComponents(IDviInvocation& aInvocation);
private:
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGTESTLIGHTS1CPP

