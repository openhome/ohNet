#ifndef HEADER_DVZAPPORGTESTBASIC1CPP
#define HEADER_DVZAPPORGTESTBASIC1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for zapp.org:TestBasic:1
 */
class DvServiceZappOrgTestBasic1Cpp : public DvService
{
public:
    virtual ~DvServiceZappOrgTestBasic1Cpp() {}
    void SetPropertyVarUint(uint32_t aValue);
    void GetPropertyVarUint(uint32_t& aValue);
    void SetPropertyVarInt(int32_t aValue);
    void GetPropertyVarInt(int32_t& aValue);
    void SetPropertyVarBool(bool aValue);
    void GetPropertyVarBool(bool& aValue);
    void SetPropertyVarStr(const std::string& aValue);
    void GetPropertyVarStr(std::string& aValue);
    void SetPropertyVarBin(const std::string& aValue);
    void GetPropertyVarBin(std::string& aValue);
protected:
    DvServiceZappOrgTestBasic1Cpp(DvDeviceStd& aDevice);
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
private:
    DvServiceZappOrgTestBasic1Cpp();
    void DoIncrement(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDecrement(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoToggle(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoEchoString(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoEchoBinary(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetUint(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetUint(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetInt(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetInt(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBool(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetBool(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetMultiple(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetString(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetString(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBinary(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetBinary(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTBASIC1CPP

