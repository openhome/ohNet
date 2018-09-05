#ifndef HEADER_DVOPENHOMEORGTESTBASIC1CPP
#define HEADER_DVOPENHOMEORGTESTBASIC1CPP

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
 * Provider for the openhome.org:TestBasic:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestBasic1Cpp : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestBasic1Cpp() {}
    /**
     * Set the value of the VarUint property
     *
     * Can only be called if EnablePropertyVarUint has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarUint(uint32_t aValue);
    /**
     * Get a copy of the value of the VarUint property
     *
     * Can only be called if EnablePropertyVarUint has previously been called.
     */
    void GetPropertyVarUint(uint32_t& aValue);
    /**
     * Set the value of the VarInt property
     *
     * Can only be called if EnablePropertyVarInt has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarInt(int32_t aValue);
    /**
     * Get a copy of the value of the VarInt property
     *
     * Can only be called if EnablePropertyVarInt has previously been called.
     */
    void GetPropertyVarInt(int32_t& aValue);
    /**
     * Set the value of the VarBool property
     *
     * Can only be called if EnablePropertyVarBool has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarBool(bool aValue);
    /**
     * Get a copy of the value of the VarBool property
     *
     * Can only be called if EnablePropertyVarBool has previously been called.
     */
    void GetPropertyVarBool(bool& aValue);
    /**
     * Set the value of the VarStr property
     *
     * Can only be called if EnablePropertyVarStr has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarStr(const std::string& aValue);
    /**
     * Get a copy of the value of the VarStr property
     *
     * Can only be called if EnablePropertyVarStr has previously been called.
     */
    void GetPropertyVarStr(std::string& aValue);
    /**
     * Set the value of the VarBin property
     *
     * Can only be called if EnablePropertyVarBin has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarBin(const std::string& aValue);
    /**
     * Get a copy of the value of the VarBin property
     *
     * Can only be called if EnablePropertyVarBin has previously been called.
     */
    void GetPropertyVarBin(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestBasic1Cpp(DvDeviceStd& aDevice);
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
    virtual void Increment(IDvInvocationStd& aInvocation, uint32_t aValue, uint32_t& aResult);
    /**
     * EchoAllowedRangeUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoAllowedRangeUint action for the owning device.
     * Must be implemented iff EnableActionEchoAllowedRangeUint was called.
     */
    virtual void EchoAllowedRangeUint(IDvInvocationStd& aInvocation, uint32_t aValue, uint32_t& aResult);
    /**
     * Decrement action.
     *
     * Will be called when the device stack receives an invocation of the
     * Decrement action for the owning device.
     * Must be implemented iff EnableActionDecrement was called.
     */
    virtual void Decrement(IDvInvocationStd& aInvocation, int32_t aValue, int32_t& aResult);
    /**
     * Toggle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Toggle action for the owning device.
     * Must be implemented iff EnableActionToggle was called.
     */
    virtual void Toggle(IDvInvocationStd& aInvocation, bool aValue, bool& aResult);
    /**
     * EchoString action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoString action for the owning device.
     * Must be implemented iff EnableActionEchoString was called.
     */
    virtual void EchoString(IDvInvocationStd& aInvocation, const std::string& aValue, std::string& aResult);
    /**
     * EchoAllowedValueString action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoAllowedValueString action for the owning device.
     * Must be implemented iff EnableActionEchoAllowedValueString was called.
     */
    virtual void EchoAllowedValueString(IDvInvocationStd& aInvocation, const std::string& aValue, std::string& aResult);
    /**
     * EchoBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoBinary action for the owning device.
     * Must be implemented iff EnableActionEchoBinary was called.
     */
    virtual void EchoBinary(IDvInvocationStd& aInvocation, const std::string& aValue, std::string& aResult);
    /**
     * SetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetUint action for the owning device.
     * Must be implemented iff EnableActionSetUint was called.
     */
    virtual void SetUint(IDvInvocationStd& aInvocation, uint32_t aValueUint);
    /**
     * GetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetUint action for the owning device.
     * Must be implemented iff EnableActionGetUint was called.
     */
    virtual void GetUint(IDvInvocationStd& aInvocation, uint32_t& aValueUint);
    /**
     * SetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInt action for the owning device.
     * Must be implemented iff EnableActionSetInt was called.
     */
    virtual void SetInt(IDvInvocationStd& aInvocation, int32_t aValueInt);
    /**
     * GetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetInt action for the owning device.
     * Must be implemented iff EnableActionGetInt was called.
     */
    virtual void GetInt(IDvInvocationStd& aInvocation, int32_t& aValueInt);
    /**
     * SetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBool action for the owning device.
     * Must be implemented iff EnableActionSetBool was called.
     */
    virtual void SetBool(IDvInvocationStd& aInvocation, bool aValueBool);
    /**
     * GetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBool action for the owning device.
     * Must be implemented iff EnableActionGetBool was called.
     */
    virtual void GetBool(IDvInvocationStd& aInvocation, bool& aValueBool);
    /**
     * SetMultiple action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMultiple action for the owning device.
     * Must be implemented iff EnableActionSetMultiple was called.
     */
    virtual void SetMultiple(IDvInvocationStd& aInvocation, uint32_t aValueUint, int32_t aValueInt, bool aValueBool);
    /**
     * GetMultiple action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMultiple action for the owning device.
     * Must be implemented iff EnableActionGetMultiple was called.
     */
    virtual void GetMultiple(IDvInvocationStd& aInvocation, uint32_t& aValueUint, int32_t& aValueInt, bool& aValueBool);
    /**
     * SetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetString action for the owning device.
     * Must be implemented iff EnableActionSetString was called.
     */
    virtual void SetString(IDvInvocationStd& aInvocation, const std::string& aValueStr);
    /**
     * GetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetString action for the owning device.
     * Must be implemented iff EnableActionGetString was called.
     */
    virtual void GetString(IDvInvocationStd& aInvocation, std::string& aValueStr);
    /**
     * SetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBinary action for the owning device.
     * Must be implemented iff EnableActionSetBinary was called.
     */
    virtual void SetBinary(IDvInvocationStd& aInvocation, const std::string& aValueBin);
    /**
     * GetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBinary action for the owning device.
     * Must be implemented iff EnableActionGetBinary was called.
     */
    virtual void GetBinary(IDvInvocationStd& aInvocation, std::string& aValueBin);
    /**
     * ToggleBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * ToggleBool action for the owning device.
     * Must be implemented iff EnableActionToggleBool was called.
     */
    virtual void ToggleBool(IDvInvocationStd& aInvocation);
    /**
     * ReportError action.
     *
     * Will be called when the device stack receives an invocation of the
     * ReportError action for the owning device.
     * Must be implemented iff EnableActionReportError was called.
     */
    virtual void ReportError(IDvInvocationStd& aInvocation);
    /**
     * WriteFile action.
     *
     * Will be called when the device stack receives an invocation of the
     * WriteFile action for the owning device.
     * Must be implemented iff EnableActionWriteFile was called.
     */
    virtual void WriteFile(IDvInvocationStd& aInvocation, const std::string& aData, const std::string& aFileFullName);
    /**
     * Shutdown action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shutdown action for the owning device.
     * Must be implemented iff EnableActionShutdown was called.
     */
    virtual void Shutdown(IDvInvocationStd& aInvocation);
private:
    DvProviderOpenhomeOrgTestBasic1Cpp();
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

#endif // HEADER_DVOPENHOMEORGTESTBASIC1CPP

