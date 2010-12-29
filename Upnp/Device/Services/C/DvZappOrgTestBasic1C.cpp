#include "DvZappOrgTestBasic1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderZappOrgTestBasic1C : public DvProvider
{
public:
    DvProviderZappOrgTestBasic1C(DvDeviceC aDevice);
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
    void EnableActionToggleBool(CallbackTestBasic1ToggleBool aCallback, void* aPtr);
    void EnableActionWriteFile(CallbackTestBasic1WriteFile aCallback, void* aPtr);
    void EnableActionShutdown(CallbackTestBasic1Shutdown aCallback, void* aPtr);
private:
    void DoIncrement(IDviInvocation& aInvocation, TUint aVersion);
    void DoDecrement(IDviInvocation& aInvocation, TUint aVersion);
    void DoToggle(IDviInvocation& aInvocation, TUint aVersion);
    void DoEchoString(IDviInvocation& aInvocation, TUint aVersion);
    void DoEchoBinary(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetUint(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetUint(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetInt(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetInt(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBool(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBool(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMultiple(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetString(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetString(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBinary(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBinary(IDviInvocation& aInvocation, TUint aVersion);
    void DoToggleBool(IDviInvocation& aInvocation, TUint aVersion);
    void DoWriteFile(IDviInvocation& aInvocation, TUint aVersion);
    void DoShutdown(IDviInvocation& aInvocation, TUint aVersion);
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
    CallbackTestBasic1ToggleBool iCallbackToggleBool;
    void* iPtrToggleBool;
    CallbackTestBasic1WriteFile iCallbackWriteFile;
    void* iPtrWriteFile;
    CallbackTestBasic1Shutdown iCallbackShutdown;
    void* iPtrShutdown;
    PropertyUint* iPropertyVarUint;
    PropertyInt* iPropertyVarInt;
    PropertyBool* iPropertyVarBool;
    PropertyString* iPropertyVarStr;
    PropertyBinary* iPropertyVarBin;
};

DvProviderZappOrgTestBasic1C::DvProviderZappOrgTestBasic1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "zapp.org", "TestBasic", 1)
{
    
    iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
    iService->AddProperty(iPropertyVarUint); // passes ownership
    iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
    iService->AddProperty(iPropertyVarInt); // passes ownership
    iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
    iService->AddProperty(iPropertyVarBool); // passes ownership
    iPropertyVarStr = new PropertyString(new ParameterString("VarStr"));
    iService->AddProperty(iPropertyVarStr); // passes ownership
    iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"));
    iService->AddProperty(iPropertyVarBin); // passes ownership
}

TBool DvProviderZappOrgTestBasic1C::SetPropertyVarUint(TUint aValue)
{
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderZappOrgTestBasic1C::GetPropertyVarUint(TUint& aValue)
{
    aValue = iPropertyVarUint->Value();
}

TBool DvProviderZappOrgTestBasic1C::SetPropertyVarInt(TInt aValue)
{
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderZappOrgTestBasic1C::GetPropertyVarInt(TInt& aValue)
{
    aValue = iPropertyVarInt->Value();
}

TBool DvProviderZappOrgTestBasic1C::SetPropertyVarBool(TBool aValue)
{
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderZappOrgTestBasic1C::GetPropertyVarBool(TBool& aValue)
{
    aValue = iPropertyVarBool->Value();
}

TBool DvProviderZappOrgTestBasic1C::SetPropertyVarStr(const Brx& aValue)
{
    return SetPropertyString(*iPropertyVarStr, aValue);
}

void DvProviderZappOrgTestBasic1C::GetPropertyVarStr(Brhz& aValue)
{
    aValue.Set(iPropertyVarStr->Value());
}

TBool DvProviderZappOrgTestBasic1C::SetPropertyVarBin(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyVarBin, aValue);
}

void DvProviderZappOrgTestBasic1C::GetPropertyVarBin(Brh& aValue)
{
    aValue.Set(iPropertyVarBin->Value());
}

void DvProviderZappOrgTestBasic1C::EnableActionIncrement(CallbackTestBasic1Increment aCallback, void* aPtr)
{
    iCallbackIncrement = aCallback;
    iPtrIncrement = aPtr;
    Zapp::Action* action = new Zapp::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionDecrement(CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    iCallbackDecrement = aCallback;
    iPtrDecrement = aPtr;
    Zapp::Action* action = new Zapp::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionToggle(CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    iCallbackToggle = aCallback;
    iPtrToggle = aPtr;
    Zapp::Action* action = new Zapp::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionEchoString(CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    iCallbackEchoString = aCallback;
    iPtrEchoString = aPtr;
    Zapp::Action* action = new Zapp::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionEchoBinary(CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    iCallbackEchoBinary = aCallback;
    iPtrEchoBinary = aPtr;
    Zapp::Action* action = new Zapp::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetUint(CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    iCallbackSetUint = aCallback;
    iPtrSetUint = aPtr;
    Zapp::Action* action = new Zapp::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionGetUint(CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    iCallbackGetUint = aCallback;
    iPtrGetUint = aPtr;
    Zapp::Action* action = new Zapp::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetInt(CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    iCallbackSetInt = aCallback;
    iPtrSetInt = aPtr;
    Zapp::Action* action = new Zapp::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionGetInt(CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    iCallbackGetInt = aCallback;
    iPtrGetInt = aPtr;
    Zapp::Action* action = new Zapp::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetBool(CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    iCallbackSetBool = aCallback;
    iPtrSetBool = aPtr;
    Zapp::Action* action = new Zapp::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionGetBool(CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    iCallbackGetBool = aCallback;
    iPtrGetBool = aPtr;
    Zapp::Action* action = new Zapp::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetMultiple(CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    iCallbackSetMultiple = aCallback;
    iPtrSetMultiple = aPtr;
    Zapp::Action* action = new Zapp::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetString(CallbackTestBasic1SetString aCallback, void* aPtr)
{
    iCallbackSetString = aCallback;
    iPtrSetString = aPtr;
    Zapp::Action* action = new Zapp::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionGetString(CallbackTestBasic1GetString aCallback, void* aPtr)
{
    iCallbackGetString = aCallback;
    iPtrGetString = aPtr;
    Zapp::Action* action = new Zapp::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionSetBinary(CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    iCallbackSetBinary = aCallback;
    iPtrSetBinary = aPtr;
    Zapp::Action* action = new Zapp::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionGetBinary(CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    iCallbackGetBinary = aCallback;
    iPtrGetBinary = aPtr;
    Zapp::Action* action = new Zapp::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionToggleBool(CallbackTestBasic1ToggleBool aCallback, void* aPtr)
{
    iCallbackToggleBool = aCallback;
    iPtrToggleBool = aPtr;
    Zapp::Action* action = new Zapp::Action("ToggleBool");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionWriteFile(CallbackTestBasic1WriteFile aCallback, void* aPtr)
{
    iCallbackWriteFile = aCallback;
    iPtrWriteFile = aPtr;
    Zapp::Action* action = new Zapp::Action("WriteFile");
    action->AddInputParameter(new ParameterString("Data"));
    action->AddInputParameter(new ParameterString("FileFullName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoWriteFile);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::EnableActionShutdown(CallbackTestBasic1Shutdown aCallback, void* aPtr)
{
    iCallbackShutdown = aCallback;
    iPtrShutdown = aPtr;
    Zapp::Action* action = new Zapp::Action("Shutdown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1C::DoShutdown);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1C::DoIncrement(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Result;
    ASSERT(iCallbackIncrement != NULL);
    if (0 != iCallbackIncrement(iPtrIncrement, aVersion, Value, &Result)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respResult(aInvocation, "Result");
    resp.Start();
    respResult.Write(Result);
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoDecrement(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t Result;
    ASSERT(iCallbackDecrement != NULL);
    if (0 != iCallbackDecrement(iPtrDecrement, aVersion, Value, &Result)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respResult(aInvocation, "Result");
    resp.Start();
    respResult.Write(Result);
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoToggle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Result;
    ASSERT(iCallbackToggle != NULL);
    if (0 != iCallbackToggle(iPtrToggle, aVersion, Value, &Result)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respResult(aInvocation, "Result");
    resp.Start();
    respResult.Write((Result!=0));
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoEchoString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    ASSERT(iCallbackEchoString != NULL);
    if (0 != iCallbackEchoString(iPtrEchoString, aVersion, (const char*)Value.Ptr(), &Result)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoEchoBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh Value;
    aInvocation.InvocationReadBinary("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t ResultLen;
    ASSERT(iCallbackEchoBinary != NULL);
    if (0 != iCallbackEchoBinary(iPtrEchoBinary, aVersion, (const char*)Value.Ptr(), Value.Bytes(), &Result, &ResultLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBinary respResult(aInvocation, "Result");
    resp.Start();
    Brh bufResult;
    bufResult.Set((const TByte*)Result, ResultLen);
    ZappFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetUint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetUint != NULL);
    if (0 != iCallbackSetUint(iPtrSetUint, aVersion, ValueUint)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoGetUint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t ValueUint;
    ASSERT(iCallbackGetUint != NULL);
    if (0 != iCallbackGetUint(iPtrGetUint, aVersion, &ValueUint)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respValueUint(aInvocation, "ValueUint");
    resp.Start();
    respValueUint.Write(ValueUint);
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetInt(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetInt != NULL);
    if (0 != iCallbackSetInt(iPtrSetInt, aVersion, ValueInt)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoGetInt(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t ValueInt;
    ASSERT(iCallbackGetInt != NULL);
    if (0 != iCallbackGetInt(iPtrGetInt, aVersion, &ValueInt)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respValueInt(aInvocation, "ValueInt");
    resp.Start();
    respValueInt.Write(ValueInt);
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBool != NULL);
    if (0 != iCallbackSetBool(iPtrSetBool, aVersion, ValueBool)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoGetBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t ValueBool;
    ASSERT(iCallbackGetBool != NULL);
    if (0 != iCallbackGetBool(iPtrGetBool, aVersion, &ValueBool)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respValueBool(aInvocation, "ValueBool");
    resp.Start();
    respValueBool.Write((ValueBool!=0));
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetMultiple(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetMultiple != NULL);
    if (0 != iCallbackSetMultiple(iPtrSetMultiple, aVersion, ValueUint, ValueInt, ValueBool)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ValueStr;
    aInvocation.InvocationReadString("ValueStr", ValueStr);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetString != NULL);
    if (0 != iCallbackSetString(iPtrSetString, aVersion, (const char*)ValueStr.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoGetString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ValueStr;
    ASSERT(iCallbackGetString != NULL);
    if (0 != iCallbackGetString(iPtrGetString, aVersion, &ValueStr)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respValueStr(aInvocation, "ValueStr");
    resp.Start();
    Brhz bufValueStr((const TChar*)ValueStr);
    ZappFreeExternal(ValueStr);
    respValueStr.Write(bufValueStr);
    respValueStr.WriteFlush();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoSetBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", ValueBin);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBinary != NULL);
    if (0 != iCallbackSetBinary(iPtrSetBinary, aVersion, (const char*)ValueBin.Ptr(), ValueBin.Bytes())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoGetBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ValueBin;
    uint32_t ValueBinLen;
    ASSERT(iCallbackGetBinary != NULL);
    if (0 != iCallbackGetBinary(iPtrGetBinary, aVersion, &ValueBin, &ValueBinLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBinary respValueBin(aInvocation, "ValueBin");
    resp.Start();
    Brh bufValueBin;
    bufValueBin.Set((const TByte*)ValueBin, ValueBinLen);
    ZappFreeExternal(ValueBin);
    respValueBin.Write(bufValueBin);
    respValueBin.WriteFlush();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoToggleBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackToggleBool != NULL);
    if (0 != iCallbackToggleBool(iPtrToggleBool, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoWriteFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Data;
    aInvocation.InvocationReadString("Data", Data);
    Brhz FileFullName;
    aInvocation.InvocationReadString("FileFullName", FileFullName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackWriteFile != NULL);
    if (0 != iCallbackWriteFile(iPtrWriteFile, aVersion, (const char*)Data.Ptr(), (const char*)FileFullName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderZappOrgTestBasic1C::DoShutdown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackShutdown != NULL);
    if (0 != iCallbackShutdown(iPtrShutdown, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderZappOrgTestBasic1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestBasic1C(aDevice);
}

void DvProviderZappOrgTestBasic1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider);
}

void DvProviderZappOrgTestBasic1EnableActionIncrement(THandle aProvider, CallbackTestBasic1Increment aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionIncrement(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionDecrement(THandle aProvider, CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionDecrement(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionToggle(THandle aProvider, CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionToggle(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionEchoString(THandle aProvider, CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionEchoString(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionEchoBinary(THandle aProvider, CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionEchoBinary(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetUint(THandle aProvider, CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetUint(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionGetUint(THandle aProvider, CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionGetUint(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetInt(THandle aProvider, CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetInt(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionGetInt(THandle aProvider, CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionGetInt(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetBool(THandle aProvider, CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetBool(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionGetBool(THandle aProvider, CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionGetBool(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetMultiple(THandle aProvider, CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetMultiple(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetString(THandle aProvider, CallbackTestBasic1SetString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetString(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionGetString(THandle aProvider, CallbackTestBasic1GetString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionGetString(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionSetBinary(THandle aProvider, CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionSetBinary(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionGetBinary(THandle aProvider, CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionGetBinary(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionToggleBool(THandle aProvider, CallbackTestBasic1ToggleBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionToggleBool(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionWriteFile(THandle aProvider, CallbackTestBasic1WriteFile aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionWriteFile(aCallback, aPtr);
}

void DvProviderZappOrgTestBasic1EnableActionShutdown(THandle aProvider, CallbackTestBasic1Shutdown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->EnableActionShutdown(aCallback, aPtr);
}

int32_t DvProviderZappOrgTestBasic1SetPropertyVarUint(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->SetPropertyVarUint(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestBasic1GetPropertyVarUint(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->GetPropertyVarUint(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestBasic1SetPropertyVarInt(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->SetPropertyVarInt(aValue)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestBasic1GetPropertyVarInt(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->GetPropertyVarInt(val);
    *aValue = val;
}

int32_t DvProviderZappOrgTestBasic1SetPropertyVarBool(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->SetPropertyVarBool((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestBasic1GetPropertyVarBool(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->GetPropertyVarBool(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderZappOrgTestBasic1SetPropertyVarStr(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->SetPropertyVarStr(buf)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestBasic1GetPropertyVarStr(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->GetPropertyVarStr(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderZappOrgTestBasic1SetPropertyVarBin(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->SetPropertyVarBin(buf)? 1 : 0);
    return 0;
}

void DvProviderZappOrgTestBasic1GetPropertyVarBin(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderZappOrgTestBasic1C*>(aProvider)->GetPropertyVarBin(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

