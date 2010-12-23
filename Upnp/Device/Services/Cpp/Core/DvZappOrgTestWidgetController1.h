#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1

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
 * Provider for the zapp.org:TestWidgetController:1 UPnP service
 * @ingroup Providers
 */
class DvProviderZappOrgTestWidgetController1 : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestWidgetController1() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestWidgetController1(DvDevice& aDevice);
    /**
     * Signal that the action CreateWidget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCreateWidget must be overridden if this is called.
     */
    void EnableActionCreateWidget();
    /**
     * Signal that the action RemoveWidget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoRemoveWidget must be overridden if this is called.
     */
    void EnableActionRemoveWidget();
    /**
     * Signal that the action SetWidgetRegister is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetWidgetRegister must be overridden if this is called.
     */
    void EnableActionSetWidgetRegister();
    /**
     * Signal that the action GetWidgetRegister is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetWidgetRegister must be overridden if this is called.
     */
    void EnableActionGetWidgetRegister();
private:
    /**
     * CreateWidget action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateWidget action for the owning device.
     * Must be implemented iff EnableActionCreateWidget was called.
     */
    virtual void CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aWidgetClass);
    /**
     * RemoveWidget action.
     *
     * Will be called when the device stack receives an invocation of the
     * RemoveWidget action for the owning device.
     * Must be implemented iff EnableActionRemoveWidget was called.
     */
    virtual void RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    /**
     * SetWidgetRegister action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetWidgetRegister action for the owning device.
     * Must be implemented iff EnableActionSetWidgetRegister was called.
     */
    virtual void SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue);
    /**
     * GetWidgetRegister action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetWidgetRegister action for the owning device.
     * Must be implemented iff EnableActionGetWidgetRegister was called.
     */
    virtual void GetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, IInvocationResponseUint& aRegisterValue);
private:
    DvProviderZappOrgTestWidgetController1();
    void DoCreateWidget(IDviInvocation& aInvocation, TUint aVersion);
    void DoRemoveWidget(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1

