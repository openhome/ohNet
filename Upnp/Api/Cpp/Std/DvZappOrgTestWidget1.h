#ifndef HEADER_DVZAPPORGTESTWIDGET1CPP
#define HEADER_DVZAPPORGTESTWIDGET1CPP

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
 * Provider for the zapp.org:TestWidget:1 UPnP service
 * @ingroup Providers
 */
class DvProviderZappOrgTestWidget1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestWidget1Cpp() {}
    /**
     * Set the value of the ReadWriteRegister0 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadWriteRegister0(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister0 property
     */
    void GetPropertyReadWriteRegister0(uint32_t& aValue);
    /**
     * Set the value of the ReadWriteRegister1 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadWriteRegister1(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister1 property
     */
    void GetPropertyReadWriteRegister1(uint32_t& aValue);
    /**
     * Set the value of the ReadWriteRegister2 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadWriteRegister2(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister2 property
     */
    void GetPropertyReadWriteRegister2(uint32_t& aValue);
    /**
     * Set the value of the ReadWriteRegister3 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadWriteRegister3(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister3 property
     */
    void GetPropertyReadWriteRegister3(uint32_t& aValue);
    /**
     * Set the value of the ReadOnlyRegister4 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadOnlyRegister4(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister4 property
     */
    void GetPropertyReadOnlyRegister4(uint32_t& aValue);
    /**
     * Set the value of the ReadOnlyRegister5 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadOnlyRegister5(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister5 property
     */
    void GetPropertyReadOnlyRegister5(uint32_t& aValue);
    /**
     * Set the value of the ReadOnlyRegister6 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadOnlyRegister6(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister6 property
     */
    void GetPropertyReadOnlyRegister6(uint32_t& aValue);
    /**
     * Set the value of the ReadOnlyRegister7 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReadOnlyRegister7(uint32_t aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister7 property
     */
    void GetPropertyReadOnlyRegister7(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestWidget1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action SetReadWriteRegister is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetReadWriteRegister must be overridden if this is called.
     */
    void EnableActionSetReadWriteRegister();
    /**
     * Signal that the action GetWidgetClass is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetWidgetClass must be overridden if this is called.
     */
    void EnableActionGetWidgetClass();
private:
    /**
     * SetReadWriteRegister action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetReadWriteRegister action for the owning device.
     * Must be implemented iff EnableActionSetReadWriteRegister was called.
     */
    virtual void SetReadWriteRegister(uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);
    /**
     * GetWidgetClass action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetWidgetClass action for the owning device.
     * Must be implemented iff EnableActionGetWidgetClass was called.
     */
    virtual void GetWidgetClass(uint32_t aVersion, uint32_t& aWidgetClass);
private:
    DvProviderZappOrgTestWidget1Cpp();
    void DoSetReadWriteRegister(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetWidgetClass(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyReadWriteRegister0;
    PropertyUint* iPropertyReadWriteRegister1;
    PropertyUint* iPropertyReadWriteRegister2;
    PropertyUint* iPropertyReadWriteRegister3;
    PropertyUint* iPropertyReadOnlyRegister4;
    PropertyUint* iPropertyReadOnlyRegister5;
    PropertyUint* iPropertyReadOnlyRegister6;
    PropertyUint* iPropertyReadOnlyRegister7;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGET1CPP

