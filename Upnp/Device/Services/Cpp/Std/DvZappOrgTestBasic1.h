#ifndef HEADER_DVZAPPORGTESTBASIC1CPP
#define HEADER_DVZAPPORGTESTBASIC1CPP

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
 * Provider for the zapp.org:TestBasic:1 UPnP service
 * @ingroup Providers
 */
class DvProviderZappOrgTestBasic1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestBasic1Cpp() {}
    /**
     * Set the value of the VarUint property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarUint(uint32_t aValue);
    /**
     * Get a copy of the value of the VarUint property
     */
    void GetPropertyVarUint(uint32_t& aValue);
    /**
     * Set the value of the VarInt property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarInt(int32_t aValue);
    /**
     * Get a copy of the value of the VarInt property
     */
    void GetPropertyVarInt(int32_t& aValue);
    /**
     * Set the value of the VarBool property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarBool(bool aValue);
    /**
     * Get a copy of the value of the VarBool property
     */
    void GetPropertyVarBool(bool& aValue);
    /**
     * Set the value of the VarStr property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarStr(const std::string& aValue);
    /**
     * Get a copy of the value of the VarStr property
     */
    void GetPropertyVarStr(std::string& aValue);
    /**
     * Set the value of the VarBin property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVarBin(const std::string& aValue);
    /**
     * Get a copy of the value of the VarBin property
     */
    void GetPropertyVarBin(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderZappOrgTestBasic1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Increment is supported.
     * The action's availability will be published in the device's service.xml.
     * Increment must be overridden if this is called.
     */
    void EnableActionIncrement();
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
    virtual void Increment(uint32_t aVersion, uint32_t aValue, uint32_t& aResult);
    /**
     * Decrement action.
     *
     * Will be called when the device stack receives an invocation of the
     * Decrement action for the owning device.
     * Must be implemented iff EnableActionDecrement was called.
     */
    virtual void Decrement(uint32_t aVersion, int32_t aValue, int32_t& aResult);
    /**
     * Toggle action.
     *
     * Will be called when the device stack receives an invocation of the
     * Toggle action for the owning device.
     * Must be implemented iff EnableActionToggle was called.
     */
    virtual void Toggle(uint32_t aVersion, bool aValue, bool& aResult);
    /**
     * EchoString action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoString action for the owning device.
     * Must be implemented iff EnableActionEchoString was called.
     */
    virtual void EchoString(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    /**
     * EchoBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * EchoBinary action for the owning device.
     * Must be implemented iff EnableActionEchoBinary was called.
     */
    virtual void EchoBinary(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    /**
     * SetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetUint action for the owning device.
     * Must be implemented iff EnableActionSetUint was called.
     */
    virtual void SetUint(uint32_t aVersion, uint32_t aValueUint);
    /**
     * GetUint action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetUint action for the owning device.
     * Must be implemented iff EnableActionGetUint was called.
     */
    virtual void GetUint(uint32_t aVersion, uint32_t& aValueUint);
    /**
     * SetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetInt action for the owning device.
     * Must be implemented iff EnableActionSetInt was called.
     */
    virtual void SetInt(uint32_t aVersion, int32_t aValueInt);
    /**
     * GetInt action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetInt action for the owning device.
     * Must be implemented iff EnableActionGetInt was called.
     */
    virtual void GetInt(uint32_t aVersion, int32_t& aValueInt);
    /**
     * SetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBool action for the owning device.
     * Must be implemented iff EnableActionSetBool was called.
     */
    virtual void SetBool(uint32_t aVersion, bool aValueBool);
    /**
     * GetBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBool action for the owning device.
     * Must be implemented iff EnableActionGetBool was called.
     */
    virtual void GetBool(uint32_t aVersion, bool& aValueBool);
    /**
     * SetMultiple action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMultiple action for the owning device.
     * Must be implemented iff EnableActionSetMultiple was called.
     */
    virtual void SetMultiple(uint32_t aVersion, uint32_t aValueUint, int32_t aValueInt, bool aValueBool);
    /**
     * SetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetString action for the owning device.
     * Must be implemented iff EnableActionSetString was called.
     */
    virtual void SetString(uint32_t aVersion, const std::string& aValueStr);
    /**
     * GetString action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetString action for the owning device.
     * Must be implemented iff EnableActionGetString was called.
     */
    virtual void GetString(uint32_t aVersion, std::string& aValueStr);
    /**
     * SetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBinary action for the owning device.
     * Must be implemented iff EnableActionSetBinary was called.
     */
    virtual void SetBinary(uint32_t aVersion, const std::string& aValueBin);
    /**
     * GetBinary action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBinary action for the owning device.
     * Must be implemented iff EnableActionGetBinary was called.
     */
    virtual void GetBinary(uint32_t aVersion, std::string& aValueBin);
    /**
     * ToggleBool action.
     *
     * Will be called when the device stack receives an invocation of the
     * ToggleBool action for the owning device.
     * Must be implemented iff EnableActionToggleBool was called.
     */
    virtual void ToggleBool(uint32_t aVersion);
    /**
     * WriteFile action.
     *
     * Will be called when the device stack receives an invocation of the
     * WriteFile action for the owning device.
     * Must be implemented iff EnableActionWriteFile was called.
     */
    virtual void WriteFile(uint32_t aVersion, const std::string& aData, const std::string& aFileFullName);
    /**
     * Shutdown action.
     *
     * Will be called when the device stack receives an invocation of the
     * Shutdown action for the owning device.
     * Must be implemented iff EnableActionShutdown was called.
     */
    virtual void Shutdown(uint32_t aVersion);
private:
    DvProviderZappOrgTestBasic1Cpp();
    void DoIncrement(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDecrement(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoToggle(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEchoString(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEchoBinary(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetUint(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetUint(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetInt(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetInt(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBool(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetBool(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetMultiple(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetString(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetString(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBinary(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetBinary(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoToggleBool(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoWriteFile(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoShutdown(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTBASIC1CPP

