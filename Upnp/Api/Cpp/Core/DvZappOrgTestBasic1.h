#ifndef HEADER_DVZAPPORGTESTBASIC1
#define HEADER_DVZAPPORGTESTBASIC1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for zapp.org:TestBasic:1
 */
class DvProviderZappOrgTestBasic1 : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestBasic1() {}
    TBool SetPropertyVarUint(TUint aValue);
    void GetPropertyVarUint(TUint& aValue);
    TBool SetPropertyVarInt(TInt aValue);
    void GetPropertyVarInt(TInt& aValue);
    TBool SetPropertyVarBool(TBool aValue);
    void GetPropertyVarBool(TBool& aValue);
    TBool SetPropertyVarStr(const Brx& aValue);
    void GetPropertyVarStr(Brhz& aValue);
    TBool SetPropertyVarBin(const Brx& aValue);
    void GetPropertyVarBin(Brh& aValue);
protected:
    DvProviderZappOrgTestBasic1(DvDevice& aDevice);
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
    virtual void Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult);
    virtual void Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult);
    virtual void Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult);
    virtual void EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult);
    virtual void EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult);
    virtual void SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    virtual void GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint);
    virtual void SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    virtual void GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt);
    virtual void SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    virtual void GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool);
    virtual void SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    virtual void SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    virtual void GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr);
    virtual void SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    virtual void GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin);
    virtual void ToggleBool(IInvocationResponse& aResponse, TUint aVersion);
private:
    DvProviderZappOrgTestBasic1();
    void DoIncrement(IDvInvocation& aInvocation, TUint aVersion);
    void DoDecrement(IDvInvocation& aInvocation, TUint aVersion);
    void DoToggle(IDvInvocation& aInvocation, TUint aVersion);
    void DoEchoString(IDvInvocation& aInvocation, TUint aVersion);
    void DoEchoBinary(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetUint(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetUint(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetInt(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetInt(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBool(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetBool(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetMultiple(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetString(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetString(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBinary(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetBinary(IDvInvocation& aInvocation, TUint aVersion);
    void DoToggleBool(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTBASIC1

