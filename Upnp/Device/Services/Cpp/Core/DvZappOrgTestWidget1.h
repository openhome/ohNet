#ifndef HEADER_DVZAPPORGTESTWIDGET1
#define HEADER_DVZAPPORGTESTWIDGET1

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
 * Provider for the zapp.org:TestWidget:1 UPnP service
 * @ingroup Providers
 */
class DvProviderZappOrgTestWidget1 : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestWidget1() {}
    /**
     * Set the value of the ReadWriteRegister0 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadWriteRegister0(TUint aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister0 property
     */
    void GetPropertyReadWriteRegister0(TUint& aValue);
    /**
     * Set the value of the ReadWriteRegister1 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadWriteRegister1(TUint aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister1 property
     */
    void GetPropertyReadWriteRegister1(TUint& aValue);
    /**
     * Set the value of the ReadWriteRegister2 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadWriteRegister2(TUint aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister2 property
     */
    void GetPropertyReadWriteRegister2(TUint& aValue);
    /**
     * Set the value of the ReadWriteRegister3 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadWriteRegister3(TUint aValue);
    /**
     * Get a copy of the value of the ReadWriteRegister3 property
     */
    void GetPropertyReadWriteRegister3(TUint& aValue);
    /**
     * Set the value of the ReadOnlyRegister4 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadOnlyRegister4(TUint aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister4 property
     */
    void GetPropertyReadOnlyRegister4(TUint& aValue);
    /**
     * Set the value of the ReadOnlyRegister5 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadOnlyRegister5(TUint aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister5 property
     */
    void GetPropertyReadOnlyRegister5(TUint& aValue);
    /**
     * Set the value of the ReadOnlyRegister6 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadOnlyRegister6(TUint aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister6 property
     */
    void GetPropertyReadOnlyRegister6(TUint& aValue);
    /**
     * Set the value of the ReadOnlyRegister7 property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReadOnlyRegister7(TUint aValue);
    /**
     * Get a copy of the value of the ReadOnlyRegister7 property
     */
    void GetPropertyReadOnlyRegister7(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestWidget1(DvDevice& aDevice);
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
    virtual void SetReadWriteRegister(IInvocationResponse& aResponse, TUint aVersion, TUint aRegisterIndex, TUint aRegisterValue);
    /**
     * GetWidgetClass action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetWidgetClass action for the owning device.
     * Must be implemented iff EnableActionGetWidgetClass was called.
     */
    virtual void GetWidgetClass(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aWidgetClass);
private:
    DvProviderZappOrgTestWidget1();
    void DoSetReadWriteRegister(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetWidgetClass(IDviInvocation& aInvocation, TUint aVersion);
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

#endif // HEADER_DVZAPPORGTESTWIDGET1

