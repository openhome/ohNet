#ifndef HEADER_DVOPENHOMEORGTESTBASIC1
#define HEADER_DVOPENHOMEORGTESTBASIC1

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
 * Provider for the openhome.org:TestBasic:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestBasic1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestBasic1() {}
    /**
     * Set the value of the VarUint property
     *
     * Can only be called if EnablePropertyVarUint has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVarUint(TUint aValue);
    /**
     * Get a copy of the value of the VarUint property
     *
     * Can only be called if EnablePropertyVarUint has previously been called.
     */
    void GetPropertyVarUint(TUint& aValue);
    /**
     * Set the value of the VarInt property
     *
     * Can only be called if EnablePropertyVarInt has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVarInt(TInt aValue);
    /**
     * Get a copy of the value of the VarInt property
     *
     * Can only be called if EnablePropertyVarInt has previously been called.
     */
    void GetPropertyVarInt(TInt& aValue);
    /**
     * Set the value of the VarBool property
     *
     * Can only be called if EnablePropertyVarBool has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVarBool(TBool aValue);
    /**
     * Get a copy of the value of the VarBool property
     *
     * Can only be called if EnablePropertyVarBool has previously been called.
     */
    void GetPropertyVarBool(TBool& aValue);
    /**
     * Set the value of the VarStr property
     *
     * Can only be called if EnablePropertyVarStr has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVarStr(const Brx& aValue);
    /**
     * Get a copy of the value of the VarStr property
     *
     * Can only be called if EnablePropertyVarStr has previously been called.
     */
    void GetPropertyVarStr(Brhz& aValue);
    /**
     * Output the value of the VarStr property without an intermediate copy.
     *
     * Can only be called if EnablePropertyVarStr has previously been called.
     */
    void WritePropertyVarStr(IWriter& aWriter);
    /**
     * Set the value of the VarBin property
     *
     * Can only be called if EnablePropertyVarBin has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVarBin(const Brx& aValue);
    /**
     * Get a copy of the value of the VarBin property
     *
     * Can only be called if EnablePropertyVarBin has previously been called.
     */
    void GetPropertyVarBin(Brh& aValue);
    /**
     * Output the value of the VarBin property without an intermediate copy.
     *
     * Can only be called if EnablePropertyVarBin has previously been called.
     */
    void WritePropertyVarBin(IWriter& aWriter);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestBasic1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestBasic1(DviDevice& aDevice);
    /**
     * Enable the VarUint property.
     */
    void EnablePropertyVarUint();
    /**
     * Enable the VarInt property.
     */
    void EnablePropertyVarInt();
    /**
     * Enable the VarBool property.
     */
    void EnablePropertyVarBool();
    /**
     * Enable the VarStr property.
     */
    void EnablePropertyVarStr();
    /**
     * Enable the VarBin property.
     */
    void EnablePropertyVarBin();
    /**
     * Signal that the action Increment is supported.
     * The action's availability will be published in the device's service.xml.
     * Increment must be overridden if this is called.
     */
    void EnableActionIncrement();
    /**
     * Signal that the action EchoAllowedRangeUint is supported.
     * The action's availability will be published in the device's service.xml.
     * EchoAllowedRangeUint must be overridden if this is called.
     */
    void EnableActionEchoAllowedRangeUint();
    /**
     * Signal that the action Decrement is supported.
     * The action's availability will be published in the device's service.xml.
     * Decrement must be overridden if this is called.
     */
    void EnableActionDecrement();
    /**
     * Signal that the action Toggle is supported.
     * The action's availability will be published in the device's service.xml.
     * Toggle must be overridden if this is called.
     */
    void EnableActionToggle();
    /**
     * Signal that the action EchoString is supported.
     * The action's availability will be published in the device's service.xml.
     * EchoString must be overridden if this is called.
     */
    void EnableActionEchoString();
    /**
     * Signal that the action EchoAllowedValueString is supported.
     * The action's availability will be published in the device's service.xml.
     * EchoAllowedValueString must be overridden if this is called.
     */
    void EnableActionEchoAllowedValueString();
    /**
     * Signal that the action EchoBinary is supported.
     * The action's availability will be published in the device's service.xml.
     * EchoBinary must be overridden if this is called.
     */
    void EnableActionEchoBinary();
    /**
     * Signal that the action SetUint is supported.
     * The action's availability will be published in the device's service.xml.
     * SetUint must be overridden if this is called.
     */
    void EnableActionSetUint();
    /**
     * Signal that the action GetUint is supported.
     * The action's availability will be published in the device's service.xml.
     * GetUint must be overridden if this is called.
     */
    void EnableActionGetUint();
    /**
     * Signal that the action SetInt is supported.
     * The action's availability will be published in the device's service.xml.
     * SetInt must be overridden if this is called.
     */
    void EnableActionSetInt();
    /**
     * Signal that the action GetInt is supported.
     * The action's availability will be published in the device's service.xml.
     * GetInt must be overridden if this is called.
     */
    void EnableActionGetInt();
    /**
     * Signal that the action SetBool is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBool must be overridden if this is called.
     */
    void EnableActionSetBool();
    /**
     * Signal that the action GetBool is supported.
     * The action's availability will be published in the device's service.xml.
     * GetBool must be overridden if this is called.
     */
    void EnableActionGetBool();
    /**
     * Signal that the action SetMultiple is supported.
     * The action's availability will be published in the device's service.xml.
     * SetMultiple must be overridden if this is called.
     */
    void EnableActionSetMultiple();
    /**
     * Signal that the action GetMultiple is supported.
     * The action's availability will be published in the device's service.xml.
     * GetMultiple must be overridden if this is called.
     */
    void EnableActionGetMultiple();
    /**
     * Signal that the action SetString is supported.
     * The action's availability will be published in the device's service.xml.
     * SetString must be overridden if this is called.
     */
    void EnableActionSetString();
    /**
     * Signal that the action GetString is supported.
     * The action's availability will be published in the device's service.xml.
     * GetString must be overridden if this is called.
     */
    void EnableActionGetString();
    /**
     * Signal that the action SetBinary is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBinary must be overridden if this is called.
     */
    void EnableActionSetBinary();
    /**
     * Signal that the action GetBinary is supported.
     * The action's availability will be published in the device's service.xml.
     * GetBinary must be overridden if this is called.
     */
    void EnableActionGetBinary();
    /**
     * Signal that the action ToggleBool is supported.
     * The action's availability will be published in the device's service.xml.
     * ToggleBool must be overridden if this is called.
     */
    void EnableActionToggleBool();
    /**
     * Signal that the action ReportError is supported.
     * The action's availability will be published in the device's service.xml.
     * ReportError must be overridden if this is called.
     */
    void EnableActionReportError();
    /**
     * Signal that the action WriteFile is supported.
     * The action's availability will be published in the device's service.xml.
     * WriteFile must be overridden if this is called.
     */
    void EnableActionWriteFile();
    /**
     * Signal that the action Shutdown is supported.
     * The action's availability will be published in the device's service.xml.
     * Shutdown must be overridden if this is called.
     */
    void EnableActionShutdown();
private:
    /**
     * Increment action.
     *
     * Will be called when the device stack receives an invocation of the
     * Increment action for the owning device.
     * Must be implemented iff EnableActionIncrement was called.
     */
    virtual void Increment(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    /**
     * EchoAllowedRangeUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoAllowedRangeUint action for the owning device.
     * Must be implemented iff EnableActionEchoAllowedRangeUint was called.
     */
    virtual void EchoAllowedRangeUint(IDvInvocation& aInvocation, TUint aValue, IDvInvocationResponseUint& aResult);
    /**
     * Decrement action.
     *
     * Will be called when the device stack receives an invocation of the
     * Decrement action for the owning device.
     * Must be implemented iff EnableActionDecrement was called.
     */
    virtual void Decrement(IDvInvocation& aInvocation, TInt aValue, IDvInvocationResponseInt& aResult);
    /**
     * Toggle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Toggle action for the owning device.
     * Must be implemented iff EnableActionToggle was called.
     */
    virtual void Toggle(IDvInvocation& aInvocation, TBool aValue, IDvInvocationResponseBool& aResult);
    /**
     * EchoString action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoString action for the owning device.
     * Must be implemented iff EnableActionEchoString was called.
     */
    virtual void EchoString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    /**
     * EchoAllowedValueString action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoAllowedValueString action for the owning device.
     * Must be implemented iff EnableActionEchoAllowedValueString was called.
     */
    virtual void EchoAllowedValueString(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseString& aResult);
    /**
     * EchoBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoBinary action for the owning device.
     * Must be implemented iff EnableActionEchoBinary was called.
     */
    virtual void EchoBinary(IDvInvocation& aInvocation, const Brx& aValue, IDvInvocationResponseBinary& aResult);
    /**
     * SetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetUint action for the owning device.
     * Must be implemented iff EnableActionSetUint was called.
     */
    virtual void SetUint(IDvInvocation& aInvocation, TUint aValueUint);
    /**
     * GetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetUint action for the owning device.
     * Must be implemented iff EnableActionGetUint was called.
     */
    virtual void GetUint(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint);
    /**
     * SetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInt action for the owning device.
     * Must be implemented iff EnableActionSetInt was called.
     */
    virtual void SetInt(IDvInvocation& aInvocation, TInt aValueInt);
    /**
     * GetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetInt action for the owning device.
     * Must be implemented iff EnableActionGetInt was called.
     */
    virtual void GetInt(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValueInt);
    /**
     * SetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBool action for the owning device.
     * Must be implemented iff EnableActionSetBool was called.
     */
    virtual void SetBool(IDvInvocation& aInvocation, TBool aValueBool);
    /**
     * GetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBool action for the owning device.
     * Must be implemented iff EnableActionGetBool was called.
     */
    virtual void GetBool(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValueBool);
    /**
     * SetMultiple action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMultiple action for the owning device.
     * Must be implemented iff EnableActionSetMultiple was called.
     */
    virtual void SetMultiple(IDvInvocation& aInvocation, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    /**
     * GetMultiple action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMultiple action for the owning device.
     * Must be implemented iff EnableActionGetMultiple was called.
     */
    virtual void GetMultiple(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValueUint, IDvInvocationResponseInt& aValueInt, IDvInvocationResponseBool& aValueBool);
    /**
     * SetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetString action for the owning device.
     * Must be implemented iff EnableActionSetString was called.
     */
    virtual void SetString(IDvInvocation& aInvocation, const Brx& aValueStr);
    /**
     * GetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetString action for the owning device.
     * Must be implemented iff EnableActionGetString was called.
     */
    virtual void GetString(IDvInvocation& aInvocation, IDvInvocationResponseString& aValueStr);
    /**
     * SetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBinary action for the owning device.
     * Must be implemented iff EnableActionSetBinary was called.
     */
    virtual void SetBinary(IDvInvocation& aInvocation, const Brx& aValueBin);
    /**
     * GetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBinary action for the owning device.
     * Must be implemented iff EnableActionGetBinary was called.
     */
    virtual void GetBinary(IDvInvocation& aInvocation, IDvInvocationResponseBinary& aValueBin);
    /**
     * ToggleBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * ToggleBool action for the owning device.
     * Must be implemented iff EnableActionToggleBool was called.
     */
    virtual void ToggleBool(IDvInvocation& aInvocation);
    /**
     * ReportError action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReportError action for the owning device.
     * Must be implemented iff EnableActionReportError was called.
     */
    virtual void ReportError(IDvInvocation& aInvocation);
    /**
     * WriteFile action.
     *
     * Will be called when the device stack receives an invocation of the
     * WriteFile action for the owning device.
     * Must be implemented iff EnableActionWriteFile was called.
     */
    virtual void WriteFile(IDvInvocation& aInvocation, const Brx& aData, const Brx& aFileFullName);
    /**
     * Shutdown action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shutdown action for the owning device.
     * Must be implemented iff EnableActionShutdown was called.
     */
    virtual void Shutdown(IDvInvocation& aInvocation);
private:
    DvProviderOpenhomeOrgTestBasic1();
    void Construct();
    void DoIncrement(IDviInvocation& aInvocation);
    void DoEchoAllowedRangeUint(IDviInvocation& aInvocation);
    void DoDecrement(IDviInvocation& aInvocation);
    void DoToggle(IDviInvocation& aInvocation);
    void DoEchoString(IDviInvocation& aInvocation);
    void DoEchoAllowedValueString(IDviInvocation& aInvocation);
    void DoEchoBinary(IDviInvocation& aInvocation);
    void DoSetUint(IDviInvocation& aInvocation);
    void DoGetUint(IDviInvocation& aInvocation);
    void DoSetInt(IDviInvocation& aInvocation);
    void DoGetInt(IDviInvocation& aInvocation);
    void DoSetBool(IDviInvocation& aInvocation);
    void DoGetBool(IDviInvocation& aInvocation);
    void DoSetMultiple(IDviInvocation& aInvocation);
    void DoGetMultiple(IDviInvocation& aInvocation);
    void DoSetString(IDviInvocation& aInvocation);
    void DoGetString(IDviInvocation& aInvocation);
    void DoSetBinary(IDviInvocation& aInvocation);
    void DoGetBinary(IDviInvocation& aInvocation);
    void DoToggleBool(IDviInvocation& aInvocation);
    void DoReportError(IDviInvocation& aInvocation);
    void DoWriteFile(IDviInvocation& aInvocation);
    void DoShutdown(IDviInvocation& aInvocation);
private:
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGTESTBASIC1

