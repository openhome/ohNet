#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP

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
 * Provider for the zapp.org:TestWidgetController:1 UPnP service
 */
class DvProviderZappOrgTestWidgetController1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestWidgetController1Cpp() {}
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestWidgetController1Cpp(DvDeviceStd& aDevice);
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
    virtual void CreateWidget(uint32_t aVersion, const std::string& aWidgetUdn);
    /**
     * RemoveWidget action.
     *
     * Will be called when the device stack receives an invocation of the
     * RemoveWidget action for the owning device.
     * Must be implemented iff EnableActionRemoveWidget was called.
     */
    virtual void RemoveWidget(uint32_t aVersion, const std::string& aWidgetUdn);
    /**
     * SetWidgetRegister action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetWidgetRegister action for the owning device.
     * Must be implemented iff EnableActionSetWidgetRegister was called.
     */
    virtual void SetWidgetRegister(uint32_t aVersion, const std::string& aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue);
    /**
     * GetWidgetRegister action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetWidgetRegister action for the owning device.
     * Must be implemented iff EnableActionGetWidgetRegister was called.
     */
    virtual void GetWidgetRegister(uint32_t aVersion, const std::string& aWidgetUdn, uint32_t aRegisterIndex, uint32_t& aRegisterValue);
private:
    DvProviderZappOrgTestWidgetController1Cpp();
    void DoCreateWidget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRemoveWidget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetWidgetRegister(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetWidgetRegister(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP

