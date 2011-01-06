#ifndef HEADER_DVOPENHOMEORGTESTCOLORLIGHT1
#define HEADER_DVOPENHOMEORGTESTCOLORLIGHT1

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
 * Provider for the openhome.org:TestColorLight:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestColorLight1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestColorLight1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestColorLight1(DvDevice& aDevice);
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
    virtual void GetName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFriendlyName);
    /**
     * SetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     * Must be implemented iff EnableActionSetColor was called.
     */
    virtual void SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aRed, TUint aGreen, TUint aBlue);
    /**
     * GetColor action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     * Must be implemented iff EnableActionGetColor was called.
     */
    virtual void GetColor(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
    /**
     * GetMaxColors action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMaxColors action for the owning device.
     * Must be implemented iff EnableActionGetMaxColors was called.
     */
    virtual void GetMaxColors(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
private:
    DvProviderOpenhomeOrgTestColorLight1();
    void DoGetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMaxColors(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVOPENHOMEORGTESTCOLORLIGHT1

