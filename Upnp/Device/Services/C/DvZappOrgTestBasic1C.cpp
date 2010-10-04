#include <C/DvZappOrgTestBasic1.h>
#include <Core/DvZappOrgTestBasic1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceZappOrgTestBasic1C : public DvServiceZappOrgTestBasic1
{
public:
    DvServiceZappOrgTestBasic1C(DvDevice& aDevice);
    void EnableActionIncrement(CallbackTestBasic1Increment aCallback, void* aPtr);
    void EnableActionDecrement(CallbackTestBasic1Decrement aCallback, void* aPtr);
    void EnableActionToggle(CallbackTestBasic1Toggle aCallback, void* aPtr);
    void EnableActionEchoString(CallbackTestBasic1EchoString aCallback, void* aPtr);
    void EnableActionEchoBinary(CallbackTestBasic1EchoBinary aCallback, void* aPtr);
    void EnableActionSetUint(CallbackTestBasic1SetUint aCallback, void* aPtr);
    void EnableActionGetUint(CallbackTestBasic1GetUint aCallback, void* aPtr);
    void EnableActionSetInt(CallbackTestBasic1SetInt aCallback, void* aPtr);
    void EnableActionGetInt(CallbackTestBasic1GetInt aCallback, void* aPtr);
    void EnableActionSetBool(CallbackTestBasic1SetBool aCallback, void* aPtr);
    void EnableActionGetBool(CallbackTestBasic1GetBool aCallback, void* aPtr);
    void EnableActionSetMultiple(CallbackTestBasic1SetMultiple aCallback, void* aPtr);
    void EnableActionSetString(CallbackTestBasic1SetString aCallback, void* aPtr);
    void EnableActionGetString(CallbackTestBasic1GetString aCallback, void* aPtr);
    void EnableActionSetBinary(CallbackTestBasic1SetBinary aCallback, void* aPtr);
    void EnableActionGetBinary(CallbackTestBasic1GetBinary aCallback, void* aPtr);
private:
    void Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult);
    void Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult);
    void Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult);
    void EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult);
    void EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult);
    void SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint);
    void GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint);
    void SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt);
    void GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt);
    void SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool);
    void GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool);
    void SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool);
    void SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr);
    void GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr);
    void SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin);
    void GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin);
private:
    CallbackTestBasic1Increment iCallbackIncrement;
    void* iPtrIncrement;
    CallbackTestBasic1Decrement iCallbackDecrement;
    void* iPtrDecrement;
    CallbackTestBasic1Toggle iCallbackToggle;
    void* iPtrToggle;
    CallbackTestBasic1EchoString iCallbackEchoString;
    void* iPtrEchoString;
    CallbackTestBasic1EchoBinary iCallbackEchoBinary;
    void* iPtrEchoBinary;
    CallbackTestBasic1SetUint iCallbackSetUint;
    void* iPtrSetUint;
    CallbackTestBasic1GetUint iCallbackGetUint;
    void* iPtrGetUint;
    CallbackTestBasic1SetInt iCallbackSetInt;
    void* iPtrSetInt;
    CallbackTestBasic1GetInt iCallbackGetInt;
    void* iPtrGetInt;
    CallbackTestBasic1SetBool iCallbackSetBool;
    void* iPtrSetBool;
    CallbackTestBasic1GetBool iCallbackGetBool;
    void* iPtrGetBool;
    CallbackTestBasic1SetMultiple iCallbackSetMultiple;
    void* iPtrSetMultiple;
    CallbackTestBasic1SetString iCallbackSetString;
    void* iPtrSetString;
    CallbackTestBasic1GetString iCallbackGetString;
    void* iPtrGetString;
    CallbackTestBasic1SetBinary iCallbackSetBinary;
    void* iPtrSetBinary;
    CallbackTestBasic1GetBinary iCallbackGetBinary;
    void* iPtrGetBinary;
};

DvServiceZappOrgTestBasic1C::DvServiceZappOrgTestBasic1C(DvDevice& aDevice)
    : DvServiceZappOrgTestBasic1(aDevice)
{
}

void DvServiceZappOrgTestBasic1C::EnableActionIncrement(CallbackTestBasic1Increment aCallback, void* aPtr)
{
    iCallbackIncrement = aCallback;
    iPtrIncrement = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionIncrement();
}

void DvServiceZappOrgTestBasic1C::EnableActionDecrement(CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    iCallbackDecrement = aCallback;
    iPtrDecrement = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionDecrement();
}

void DvServiceZappOrgTestBasic1C::EnableActionToggle(CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    iCallbackToggle = aCallback;
    iPtrToggle = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionToggle();
}

void DvServiceZappOrgTestBasic1C::EnableActionEchoString(CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    iCallbackEchoString = aCallback;
    iPtrEchoString = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionEchoString();
}

void DvServiceZappOrgTestBasic1C::EnableActionEchoBinary(CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    iCallbackEchoBinary = aCallback;
    iPtrEchoBinary = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionEchoBinary();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetUint(CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    iCallbackSetUint = aCallback;
    iPtrSetUint = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetUint();
}

void DvServiceZappOrgTestBasic1C::EnableActionGetUint(CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    iCallbackGetUint = aCallback;
    iPtrGetUint = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionGetUint();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetInt(CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    iCallbackSetInt = aCallback;
    iPtrSetInt = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetInt();
}

void DvServiceZappOrgTestBasic1C::EnableActionGetInt(CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    iCallbackGetInt = aCallback;
    iPtrGetInt = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionGetInt();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetBool(CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    iCallbackSetBool = aCallback;
    iPtrSetBool = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetBool();
}

void DvServiceZappOrgTestBasic1C::EnableActionGetBool(CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    iCallbackGetBool = aCallback;
    iPtrGetBool = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionGetBool();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetMultiple(CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    iCallbackSetMultiple = aCallback;
    iPtrSetMultiple = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetMultiple();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetString(CallbackTestBasic1SetString aCallback, void* aPtr)
{
    iCallbackSetString = aCallback;
    iPtrSetString = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetString();
}

void DvServiceZappOrgTestBasic1C::EnableActionGetString(CallbackTestBasic1GetString aCallback, void* aPtr)
{
    iCallbackGetString = aCallback;
    iPtrGetString = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionGetString();
}

void DvServiceZappOrgTestBasic1C::EnableActionSetBinary(CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    iCallbackSetBinary = aCallback;
    iPtrSetBinary = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionSetBinary();
}

void DvServiceZappOrgTestBasic1C::EnableActionGetBinary(CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    iCallbackGetBinary = aCallback;
    iPtrGetBinary = aPtr;
    DvServiceZappOrgTestBasic1::EnableActionGetBinary();
}

void DvServiceZappOrgTestBasic1C::Increment(IInvocationResponse& aResponse, TUint aVersion, TUint aValue, IInvocationResponseUint& aResult)
{
    uint32_t Result;
    ASSERT(iCallbackIncrement != NULL);
    if (0 != iCallbackIncrement(iPtrIncrement, aVersion, aValue, &Result)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResult.Write(Result);
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::Decrement(IInvocationResponse& aResponse, TUint aVersion, TInt aValue, IInvocationResponseInt& aResult)
{
    int32_t Result;
    ASSERT(iCallbackDecrement != NULL);
    if (0 != iCallbackDecrement(iPtrDecrement, aVersion, aValue, &Result)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResult.Write(Result);
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::Toggle(IInvocationResponse& aResponse, TUint aVersion, TBool aValue, IInvocationResponseBool& aResult)
{
    uint32_t Result;
    ASSERT(iCallbackToggle != NULL);
    if (0 != iCallbackToggle(iPtrToggle, aVersion, aValue, &Result)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResult.Write((Result!=0));
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::EchoString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseString& aResult)
{
    char* Result;
    ASSERT(iCallbackEchoString != NULL);
    if (0 != iCallbackEchoString(iPtrEchoString, aVersion, (const char*)aValue.Ptr(), &Result)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::EchoBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValue, IInvocationResponseBinary& aResult)
{
    char* Result;
    uint32_t ResultLen;
    ASSERT(iCallbackEchoBinary != NULL);
    if (0 != iCallbackEchoBinary(iPtrEchoBinary, aVersion, (const char*)aValue.Ptr(), aValue.Bytes(), &Result, &ResultLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brh bufResult;
    bufResult.Set((const TByte*)Result, ResultLen);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetUint(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint)
{
    ASSERT(iCallbackSetUint != NULL);
    if (0 != iCallbackSetUint(iPtrSetUint, aVersion, aValueUint)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::GetUint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValueUint)
{
    uint32_t ValueUint;
    ASSERT(iCallbackGetUint != NULL);
    if (0 != iCallbackGetUint(iPtrGetUint, aVersion, &ValueUint)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aValueUint.Write(ValueUint);
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetInt(IInvocationResponse& aResponse, TUint aVersion, TInt aValueInt)
{
    ASSERT(iCallbackSetInt != NULL);
    if (0 != iCallbackSetInt(iPtrSetInt, aVersion, aValueInt)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::GetInt(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValueInt)
{
    int32_t ValueInt;
    ASSERT(iCallbackGetInt != NULL);
    if (0 != iCallbackGetInt(iPtrGetInt, aVersion, &ValueInt)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aValueInt.Write(ValueInt);
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetBool(IInvocationResponse& aResponse, TUint aVersion, TBool aValueBool)
{
    ASSERT(iCallbackSetBool != NULL);
    if (0 != iCallbackSetBool(iPtrSetBool, aVersion, aValueBool)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::GetBool(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValueBool)
{
    uint32_t ValueBool;
    ASSERT(iCallbackGetBool != NULL);
    if (0 != iCallbackGetBool(iPtrGetBool, aVersion, &ValueBool)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aValueBool.Write((ValueBool!=0));
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetMultiple(IInvocationResponse& aResponse, TUint aVersion, TUint aValueUint, TInt aValueInt, TBool aValueBool)
{
    ASSERT(iCallbackSetMultiple != NULL);
    if (0 != iCallbackSetMultiple(iPtrSetMultiple, aVersion, aValueUint, aValueInt, aValueBool)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetString(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueStr)
{
    ASSERT(iCallbackSetString != NULL);
    if (0 != iCallbackSetString(iPtrSetString, aVersion, (const char*)aValueStr.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::GetString(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValueStr)
{
    char* ValueStr;
    ASSERT(iCallbackGetString != NULL);
    if (0 != iCallbackGetString(iPtrGetString, aVersion, &ValueStr)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufValueStr((const TChar*)ValueStr);
    ZappFreeExternal(ValueStr);
    aValueStr.Write(bufValueStr);
    aValueStr.WriteFlush();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::SetBinary(IInvocationResponse& aResponse, TUint aVersion, const Brx& aValueBin)
{
    ASSERT(iCallbackSetBinary != NULL);
    if (0 != iCallbackSetBinary(iPtrSetBinary, aVersion, (const char*)aValueBin.Ptr(), aValueBin.Bytes())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestBasic1C::GetBinary(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aValueBin)
{
    char* ValueBin;
    uint32_t ValueBinLen;
    ASSERT(iCallbackGetBinary != NULL);
    if (0 != iCallbackGetBinary(iPtrGetBinary, aVersion, &ValueBin, &ValueBinLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brh bufValueBin;
    bufValueBin.Set((const TByte*)ValueBin, ValueBinLen);
    ZappFreeExternal(ValueBin);
    aValueBin.Write(bufValueBin);
    aValueBin.WriteFlush();
    aResponse.End();
}



THandle DvServiceZappOrgTestBasic1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceZappOrgTestBasic1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceZappOrgTestBasic1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService);
}

void DvServiceZappOrgTestBasic1EnableActionIncrement(THandle aService, CallbackTestBasic1Increment aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionIncrement(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionDecrement(THandle aService, CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionDecrement(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionToggle(THandle aService, CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionToggle(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionEchoString(THandle aService, CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionEchoString(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionEchoBinary(THandle aService, CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionEchoBinary(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetUint(THandle aService, CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetUint(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionGetUint(THandle aService, CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionGetUint(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetInt(THandle aService, CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetInt(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionGetInt(THandle aService, CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionGetInt(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetBool(THandle aService, CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetBool(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionGetBool(THandle aService, CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionGetBool(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetMultiple(THandle aService, CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetMultiple(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetString(THandle aService, CallbackTestBasic1SetString aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetString(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionGetString(THandle aService, CallbackTestBasic1GetString aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionGetString(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionSetBinary(THandle aService, CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionSetBinary(aCallback, aPtr);
}

void DvServiceZappOrgTestBasic1EnableActionGetBinary(THandle aService, CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->EnableActionGetBinary(aCallback, aPtr);
}

int32_t DvServiceZappOrgTestBasic1SetPropertyVarUint(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->SetPropertyVarUint(aValue);
    return 0;
}

void DvServiceZappOrgTestBasic1GetPropertyVarUint(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->GetPropertyVarUint(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestBasic1SetPropertyVarInt(THandle aService, int32_t aValue)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->SetPropertyVarInt(aValue);
    return 0;
}

void DvServiceZappOrgTestBasic1GetPropertyVarInt(THandle aService, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->GetPropertyVarInt(val);
    *aValue = val;
}

int32_t DvServiceZappOrgTestBasic1SetPropertyVarBool(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->SetPropertyVarBool((aValue!=0));
    return 0;
}

void DvServiceZappOrgTestBasic1GetPropertyVarBool(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->GetPropertyVarBool(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceZappOrgTestBasic1SetPropertyVarStr(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->SetPropertyVarStr(buf);
    return 0;
}

void DvServiceZappOrgTestBasic1GetPropertyVarStr(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->GetPropertyVarStr(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceZappOrgTestBasic1SetPropertyVarBin(THandle aService, const char* aValue, uint32_t aValueLen)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->SetPropertyVarBin(buf);
    return 0;
}

void DvServiceZappOrgTestBasic1GetPropertyVarBin(THandle aService, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvServiceZappOrgTestBasic1C*>(aService)->GetPropertyVarBin(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

