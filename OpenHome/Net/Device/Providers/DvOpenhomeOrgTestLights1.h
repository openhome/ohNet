#ifndef HEADER_DVOPENHOMEORGTESTLIGHTS1
#define HEADER_DVOPENHOMEORGTESTLIGHTS1

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
 * Provider for the openhome.org:TestLights:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestLights1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestLights1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestLights1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestLights1(DviDevice& aDevice);
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
    virtual void GetCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aCount);
    /**
     * GetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRoom action for the owning device.
     * Must be implemented iff EnableActionGetRoom was called.
     */
    virtual void GetRoom(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aRoomName);
    /**
     * GetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetName action for the owning device.
     * Must be implemented iff EnableActionGetName was called.
     */
    virtual void GetName(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aFriendlyName);
    /**
     * GetPosition action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetPosition action for the owning device.
     * Must be implemented iff EnableActionGetPosition was called.
     */
    virtual void GetPosition(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aX, IDvInvocationResponseUint& aY, IDvInvocationResponseUint& aZ);
    /**
     * SetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     * Must be implemented iff EnableActionSetColor was called.
     */
    virtual void SetColor(IDvInvocation& aInvocation, TUint aIndex, TUint aColor);
    /**
     * GetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     * Must be implemented iff EnableActionGetColor was called.
     */
    virtual void GetColor(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseUint& aColor);
    /**
     * GetColorComponents action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColorComponents action for the owning device.
     * Must be implemented iff EnableActionGetColorComponents was called.
     */
    virtual void GetColorComponents(IDvInvocation& aInvocation, TUint aColor, IDvInvocationResponseUint& aBrightness, IDvInvocationResponseUint& aRed, IDvInvocationResponseUint& aGreen, IDvInvocationResponseUint& aBlue);
private:
    DvProviderOpenhomeOrgTestLights1();
    void Construct();
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

#endif // HEADER_DVOPENHOMEORGTESTLIGHTS1

