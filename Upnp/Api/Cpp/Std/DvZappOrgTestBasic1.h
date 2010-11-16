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
 * Base Device for zapp.org:TestBasic:1
 */
class DvProviderZappOrgTestBasic1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestBasic1Cpp() {}
    bool SetPropertyVarUint(uint32_t aValue);
    void GetPropertyVarUint(uint32_t& aValue);
    bool SetPropertyVarInt(int32_t aValue);
    void GetPropertyVarInt(int32_t& aValue);
    bool SetPropertyVarBool(bool aValue);
    void GetPropertyVarBool(bool& aValue);
    bool SetPropertyVarStr(const std::string& aValue);
    void GetPropertyVarStr(std::string& aValue);
    bool SetPropertyVarBin(const std::string& aValue);
    void GetPropertyVarBin(std::string& aValue);
protected:
    DvProviderZappOrgTestBasic1Cpp(DvDeviceStd& aDevice);
    void EnableActionIncrement();
    void EnableActionDecrement();
    void EnableActionToggle();
    void EnableActionEchoString();
    void EnableActionEchoBinary();
    void EnableActionSetUint();
    void EnableActionGetUint();
    void EnableActionSetInt();
    void EnableActionGetInt();
    void EnableActionSetBool();
    void EnableActionGetBool();
    void EnableActionSetMultiple();
    void EnableActionSetString();
    void EnableActionGetString();
    void EnableActionSetBinary();
    void EnableActionGetBinary();
    void EnableActionToggleBool();
private:
    virtual void Increment(uint32_t aVersion, uint32_t aValue, uint32_t& aResult);
    virtual void Decrement(uint32_t aVersion, int32_t aValue, int32_t& aResult);
    virtual void Toggle(uint32_t aVersion, bool aValue, bool& aResult);
    virtual void EchoString(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    virtual void EchoBinary(uint32_t aVersion, const std::string& aValue, std::string& aResult);
    virtual void SetUint(uint32_t aVersion, uint32_t aValueUint);
    virtual void GetUint(uint32_t aVersion, uint32_t& aValueUint);
    virtual void SetInt(uint32_t aVersion, int32_t aValueInt);
    virtual void GetInt(uint32_t aVersion, int32_t& aValueInt);
    virtual void SetBool(uint32_t aVersion, bool aValueBool);
    virtual void GetBool(uint32_t aVersion, bool& aValueBool);
    virtual void SetMultiple(uint32_t aVersion, uint32_t aValueUint, int32_t aValueInt, bool aValueBool);
    virtual void SetString(uint32_t aVersion, const std::string& aValueStr);
    virtual void GetString(uint32_t aVersion, std::string& aValueStr);
    virtual void SetBinary(uint32_t aVersion, const std::string& aValueBin);
    virtual void GetBinary(uint32_t aVersion, std::string& aValueBin);
    virtual void ToggleBool(uint32_t aVersion);
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
private:
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTBASIC1CPP

