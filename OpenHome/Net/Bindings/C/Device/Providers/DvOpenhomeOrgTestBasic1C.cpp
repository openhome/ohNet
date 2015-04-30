#include "DvOpenhomeOrgTestBasic1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderOpenhomeOrgTestBasic1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgTestBasic1C(DvDeviceC aDevice);
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
    void EnablePropertyVarUint();
    void EnablePropertyVarInt();
    void EnablePropertyVarBool();
    void EnablePropertyVarStr();
    void EnablePropertyVarBin();
    void EnableActionIncrement(CallbackTestBasic1Increment aCallback, void* aPtr);
    void EnableActionEchoAllowedRangeUint(CallbackTestBasic1EchoAllowedRangeUint aCallback, void* aPtr);
    void EnableActionDecrement(CallbackTestBasic1Decrement aCallback, void* aPtr);
    void EnableActionToggle(CallbackTestBasic1Toggle aCallback, void* aPtr);
    void EnableActionEchoString(CallbackTestBasic1EchoString aCallback, void* aPtr);
    void EnableActionEchoAllowedValueString(CallbackTestBasic1EchoAllowedValueString aCallback, void* aPtr);
    void EnableActionEchoBinary(CallbackTestBasic1EchoBinary aCallback, void* aPtr);
    void EnableActionSetUint(CallbackTestBasic1SetUint aCallback, void* aPtr);
    void EnableActionGetUint(CallbackTestBasic1GetUint aCallback, void* aPtr);
    void EnableActionSetInt(CallbackTestBasic1SetInt aCallback, void* aPtr);
    void EnableActionGetInt(CallbackTestBasic1GetInt aCallback, void* aPtr);
    void EnableActionSetBool(CallbackTestBasic1SetBool aCallback, void* aPtr);
    void EnableActionGetBool(CallbackTestBasic1GetBool aCallback, void* aPtr);
    void EnableActionSetMultiple(CallbackTestBasic1SetMultiple aCallback, void* aPtr);
    void EnableActionGetMultiple(CallbackTestBasic1GetMultiple aCallback, void* aPtr);
    void EnableActionSetString(CallbackTestBasic1SetString aCallback, void* aPtr);
    void EnableActionGetString(CallbackTestBasic1GetString aCallback, void* aPtr);
    void EnableActionSetBinary(CallbackTestBasic1SetBinary aCallback, void* aPtr);
    void EnableActionGetBinary(CallbackTestBasic1GetBinary aCallback, void* aPtr);
    void EnableActionToggleBool(CallbackTestBasic1ToggleBool aCallback, void* aPtr);
    void EnableActionWriteFile(CallbackTestBasic1WriteFile aCallback, void* aPtr);
    void EnableActionShutdown(CallbackTestBasic1Shutdown aCallback, void* aPtr);
private:
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
    void DoWriteFile(IDviInvocation& aInvocation);
    void DoShutdown(IDviInvocation& aInvocation);
private:
    CallbackTestBasic1Increment iCallbackIncrement;
    void* iPtrIncrement;
    CallbackTestBasic1EchoAllowedRangeUint iCallbackEchoAllowedRangeUint;
    void* iPtrEchoAllowedRangeUint;
    CallbackTestBasic1Decrement iCallbackDecrement;
    void* iPtrDecrement;
    CallbackTestBasic1Toggle iCallbackToggle;
    void* iPtrToggle;
    CallbackTestBasic1EchoString iCallbackEchoString;
    void* iPtrEchoString;
    CallbackTestBasic1EchoAllowedValueString iCallbackEchoAllowedValueString;
    void* iPtrEchoAllowedValueString;
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
    CallbackTestBasic1GetMultiple iCallbackGetMultiple;
    void* iPtrGetMultiple;
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

DvProviderOpenhomeOrgTestBasic1C::DvProviderOpenhomeOrgTestBasic1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "TestBasic", 1)
{
    iPropertyVarUint = NULL;
    iPropertyVarInt = NULL;
    iPropertyVarBool = NULL;
    iPropertyVarStr = NULL;
    iPropertyVarBin = NULL;
}

TBool DvProviderOpenhomeOrgTestBasic1C::SetPropertyVarUint(TUint aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderOpenhomeOrgTestBasic1C::GetPropertyVarUint(TUint& aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    aValue = iPropertyVarUint->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1C::SetPropertyVarInt(TInt aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderOpenhomeOrgTestBasic1C::GetPropertyVarInt(TInt& aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    aValue = iPropertyVarInt->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1C::SetPropertyVarBool(TBool aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderOpenhomeOrgTestBasic1C::GetPropertyVarBool(TBool& aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    aValue = iPropertyVarBool->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1C::SetPropertyVarStr(const Brx& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    return SetPropertyString(*iPropertyVarStr, aValue);
}

void DvProviderOpenhomeOrgTestBasic1C::GetPropertyVarStr(Brhz& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    aValue.Set(iPropertyVarStr->Value());
}

TBool DvProviderOpenhomeOrgTestBasic1C::SetPropertyVarBin(const Brx& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    return SetPropertyBinary(*iPropertyVarBin, aValue);
}

void DvProviderOpenhomeOrgTestBasic1C::GetPropertyVarBin(Brh& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    aValue.Set(iPropertyVarBin->Value());
}

void DvProviderOpenhomeOrgTestBasic1C::EnablePropertyVarUint()
{
    iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
    iService->AddProperty(iPropertyVarUint); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1C::EnablePropertyVarInt()
{
    iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
    iService->AddProperty(iPropertyVarInt); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1C::EnablePropertyVarBool()
{
    iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
    iService->AddProperty(iPropertyVarBool); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1C::EnablePropertyVarStr()
{
    iPropertyVarStr = new PropertyString(new ParameterString("VarStr"));
    iService->AddProperty(iPropertyVarStr); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1C::EnablePropertyVarBin()
{
    iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"));
    iService->AddProperty(iPropertyVarBin); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionIncrement(CallbackTestBasic1Increment aCallback, void* aPtr)
{
    iCallbackIncrement = aCallback;
    iPtrIncrement = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionEchoAllowedRangeUint(CallbackTestBasic1EchoAllowedRangeUint aCallback, void* aPtr)
{
    iCallbackEchoAllowedRangeUint = aCallback;
    iPtrEchoAllowedRangeUint = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoAllowedRangeUint");
    action->AddInputParameter(new ParameterUint("Value", 10, 20));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoEchoAllowedRangeUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionDecrement(CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    iCallbackDecrement = aCallback;
    iPtrDecrement = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionToggle(CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    iCallbackToggle = aCallback;
    iPtrToggle = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionEchoString(CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    iCallbackEchoString = aCallback;
    iPtrEchoString = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionEchoAllowedValueString(CallbackTestBasic1EchoAllowedValueString aCallback, void* aPtr)
{
    iCallbackEchoAllowedValueString = aCallback;
    iPtrEchoAllowedValueString = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoAllowedValueString");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"One";
    allowedValues[index++] = (TChar*)"Two";
    allowedValues[index++] = (TChar*)"Three";
    allowedValues[index++] = (TChar*)"Four";
    action->AddInputParameter(new ParameterString("Value", allowedValues, 4));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoEchoAllowedValueString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionEchoBinary(CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    iCallbackEchoBinary = aCallback;
    iPtrEchoBinary = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetUint(CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    iCallbackSetUint = aCallback;
    iPtrSetUint = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetUint(CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    iCallbackGetUint = aCallback;
    iPtrGetUint = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetInt(CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    iCallbackSetInt = aCallback;
    iPtrSetInt = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetInt(CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    iCallbackGetInt = aCallback;
    iPtrGetInt = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetBool(CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    iCallbackSetBool = aCallback;
    iPtrSetBool = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetBool(CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    iCallbackGetBool = aCallback;
    iPtrGetBool = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetMultiple(CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    iCallbackSetMultiple = aCallback;
    iPtrSetMultiple = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetMultiple(CallbackTestBasic1GetMultiple aCallback, void* aPtr)
{
    iCallbackGetMultiple = aCallback;
    iPtrGetMultiple = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMultiple");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetString(CallbackTestBasic1SetString aCallback, void* aPtr)
{
    iCallbackSetString = aCallback;
    iPtrSetString = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetString(CallbackTestBasic1GetString aCallback, void* aPtr)
{
    iCallbackGetString = aCallback;
    iPtrGetString = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionSetBinary(CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    iCallbackSetBinary = aCallback;
    iPtrSetBinary = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionGetBinary(CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    iCallbackGetBinary = aCallback;
    iPtrGetBinary = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionToggleBool(CallbackTestBasic1ToggleBool aCallback, void* aPtr)
{
    iCallbackToggleBool = aCallback;
    iPtrToggleBool = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ToggleBool");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionWriteFile(CallbackTestBasic1WriteFile aCallback, void* aPtr)
{
    iCallbackWriteFile = aCallback;
    iPtrWriteFile = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("WriteFile");
    action->AddInputParameter(new ParameterString("Data"));
    action->AddInputParameter(new ParameterString("FileFullName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoWriteFile);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::EnableActionShutdown(CallbackTestBasic1Shutdown aCallback, void* aPtr)
{
    iCallbackShutdown = aCallback;
    iPtrShutdown = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shutdown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1C::DoShutdown);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1C::DoIncrement(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Result;
    ASSERT(iCallbackIncrement != NULL);
    if (0 != iCallbackIncrement(iPtrIncrement, invocationC, invocationCPtr, Value, &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respResult(aInvocation, "Result");
    invocation.StartResponse();
    respResult.Write(Result);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoEchoAllowedRangeUint(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Result;
    ASSERT(iCallbackEchoAllowedRangeUint != NULL);
    if (0 != iCallbackEchoAllowedRangeUint(iPtrEchoAllowedRangeUint, invocationC, invocationCPtr, Value, &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respResult(aInvocation, "Result");
    invocation.StartResponse();
    respResult.Write(Result);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoDecrement(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t Result;
    ASSERT(iCallbackDecrement != NULL);
    if (0 != iCallbackDecrement(iPtrDecrement, invocationC, invocationCPtr, Value, &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respResult(aInvocation, "Result");
    invocation.StartResponse();
    respResult.Write(Result);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoToggle(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Result;
    ASSERT(iCallbackToggle != NULL);
    if (0 != iCallbackToggle(iPtrToggle, invocationC, invocationCPtr, Value, &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respResult(aInvocation, "Result");
    invocation.StartResponse();
    respResult.Write((Result!=0));
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoEchoString(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    ASSERT(iCallbackEchoString != NULL);
    if (0 != iCallbackEchoString(iPtrEchoString, invocationC, invocationCPtr, (const char*)Value.Ptr(), &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoEchoAllowedValueString(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    ASSERT(iCallbackEchoAllowedValueString != NULL);
    if (0 != iCallbackEchoAllowedValueString(iPtrEchoAllowedValueString, invocationC, invocationCPtr, (const char*)Value.Ptr(), &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoEchoBinary(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brh Value;
    aInvocation.InvocationReadBinary("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t ResultLen;
    ASSERT(iCallbackEchoBinary != NULL);
    if (0 != iCallbackEchoBinary(iPtrEchoBinary, invocationC, invocationCPtr, (const char*)Value.Ptr(), Value.Bytes(), &Result, &ResultLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBinary respResult(aInvocation, "Result");
    invocation.StartResponse();
    Brh bufResult;
    bufResult.Set((const TByte*)Result, ResultLen);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetUint(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetUint != NULL);
    if (0 != iCallbackSetUint(iPtrSetUint, invocationC, invocationCPtr, ValueUint)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetUint(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t ValueUint;
    ASSERT(iCallbackGetUint != NULL);
    if (0 != iCallbackGetUint(iPtrGetUint, invocationC, invocationCPtr, &ValueUint)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValueUint(aInvocation, "ValueUint");
    invocation.StartResponse();
    respValueUint.Write(ValueUint);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetInt(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetInt != NULL);
    if (0 != iCallbackSetInt(iPtrSetInt, invocationC, invocationCPtr, ValueInt)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetInt(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t ValueInt;
    ASSERT(iCallbackGetInt != NULL);
    if (0 != iCallbackGetInt(iPtrGetInt, invocationC, invocationCPtr, &ValueInt)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respValueInt(aInvocation, "ValueInt");
    invocation.StartResponse();
    respValueInt.Write(ValueInt);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetBool(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBool != NULL);
    if (0 != iCallbackSetBool(iPtrSetBool, invocationC, invocationCPtr, ValueBool)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetBool(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t ValueBool;
    ASSERT(iCallbackGetBool != NULL);
    if (0 != iCallbackGetBool(iPtrGetBool, invocationC, invocationCPtr, &ValueBool)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValueBool(aInvocation, "ValueBool");
    invocation.StartResponse();
    respValueBool.Write((ValueBool!=0));
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetMultiple(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetMultiple != NULL);
    if (0 != iCallbackSetMultiple(iPtrSetMultiple, invocationC, invocationCPtr, ValueUint, ValueInt, ValueBool)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetMultiple(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t ValueUint;
    int32_t ValueInt;
    uint32_t ValueBool;
    ASSERT(iCallbackGetMultiple != NULL);
    if (0 != iCallbackGetMultiple(iPtrGetMultiple, invocationC, invocationCPtr, &ValueUint, &ValueInt, &ValueBool)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValueUint(aInvocation, "ValueUint");
    DviInvocationResponseInt respValueInt(aInvocation, "ValueInt");
    DviInvocationResponseBool respValueBool(aInvocation, "ValueBool");
    invocation.StartResponse();
    respValueUint.Write(ValueUint);
    respValueInt.Write(ValueInt);
    respValueBool.Write((ValueBool!=0));
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetString(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ValueStr;
    aInvocation.InvocationReadString("ValueStr", ValueStr);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetString != NULL);
    if (0 != iCallbackSetString(iPtrSetString, invocationC, invocationCPtr, (const char*)ValueStr.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetString(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ValueStr;
    ASSERT(iCallbackGetString != NULL);
    if (0 != iCallbackGetString(iPtrGetString, invocationC, invocationCPtr, &ValueStr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respValueStr(aInvocation, "ValueStr");
    invocation.StartResponse();
    Brhz bufValueStr((const TChar*)ValueStr);
    OhNetFreeExternal(ValueStr);
    respValueStr.Write(bufValueStr);
    respValueStr.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoSetBinary(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brh ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", ValueBin);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBinary != NULL);
    if (0 != iCallbackSetBinary(iPtrSetBinary, invocationC, invocationCPtr, (const char*)ValueBin.Ptr(), ValueBin.Bytes())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoGetBinary(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ValueBin;
    uint32_t ValueBinLen;
    ASSERT(iCallbackGetBinary != NULL);
    if (0 != iCallbackGetBinary(iPtrGetBinary, invocationC, invocationCPtr, &ValueBin, &ValueBinLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBinary respValueBin(aInvocation, "ValueBin");
    invocation.StartResponse();
    Brh bufValueBin;
    bufValueBin.Set((const TByte*)ValueBin, ValueBinLen);
    OhNetFreeExternal(ValueBin);
    respValueBin.Write(bufValueBin);
    respValueBin.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoToggleBool(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackToggleBool != NULL);
    if (0 != iCallbackToggleBool(iPtrToggleBool, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoWriteFile(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Data;
    aInvocation.InvocationReadString("Data", Data);
    Brhz FileFullName;
    aInvocation.InvocationReadString("FileFullName", FileFullName);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackWriteFile != NULL);
    if (0 != iCallbackWriteFile(iPtrWriteFile, invocationC, invocationCPtr, (const char*)Data.Ptr(), (const char*)FileFullName.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestBasic1C::DoShutdown(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackShutdown != NULL);
    if (0 != iCallbackShutdown(iPtrShutdown, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}



THandle STDCALL DvProviderOpenhomeOrgTestBasic1Create(DvDeviceC aDevice)
{
    return new DvProviderOpenhomeOrgTestBasic1C(aDevice);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionIncrement(THandle aProvider, CallbackTestBasic1Increment aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionIncrement(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedRangeUint(THandle aProvider, CallbackTestBasic1EchoAllowedRangeUint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionEchoAllowedRangeUint(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionDecrement(THandle aProvider, CallbackTestBasic1Decrement aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionDecrement(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionToggle(THandle aProvider, CallbackTestBasic1Toggle aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionToggle(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoString(THandle aProvider, CallbackTestBasic1EchoString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionEchoString(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedValueString(THandle aProvider, CallbackTestBasic1EchoAllowedValueString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionEchoAllowedValueString(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoBinary(THandle aProvider, CallbackTestBasic1EchoBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionEchoBinary(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetUint(THandle aProvider, CallbackTestBasic1SetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetUint(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetUint(THandle aProvider, CallbackTestBasic1GetUint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetUint(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetInt(THandle aProvider, CallbackTestBasic1SetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetInt(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetInt(THandle aProvider, CallbackTestBasic1GetInt aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetInt(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetBool(THandle aProvider, CallbackTestBasic1SetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetBool(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetBool(THandle aProvider, CallbackTestBasic1GetBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetBool(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetMultiple(THandle aProvider, CallbackTestBasic1SetMultiple aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetMultiple(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetMultiple(THandle aProvider, CallbackTestBasic1GetMultiple aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetMultiple(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetString(THandle aProvider, CallbackTestBasic1SetString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetString(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetString(THandle aProvider, CallbackTestBasic1GetString aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetString(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetBinary(THandle aProvider, CallbackTestBasic1SetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionSetBinary(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetBinary(THandle aProvider, CallbackTestBasic1GetBinary aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionGetBinary(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionToggleBool(THandle aProvider, CallbackTestBasic1ToggleBool aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionToggleBool(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionWriteFile(THandle aProvider, CallbackTestBasic1WriteFile aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionWriteFile(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionShutdown(THandle aProvider, CallbackTestBasic1Shutdown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnableActionShutdown(aCallback, aPtr);
}

int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->SetPropertyVarUint(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarUint(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->GetPropertyVarUint(val);
    *aValue = val;
}

int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->SetPropertyVarInt(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarInt(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->GetPropertyVarInt(val);
    *aValue = val;
}

int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->SetPropertyVarBool((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarBool(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->GetPropertyVarBool(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarStr(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->SetPropertyVarStr(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarStr(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->GetPropertyVarStr(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarBin(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->SetPropertyVarBin(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarBin(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->GetPropertyVarBin(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarUint(THandle aProvider)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnablePropertyVarUint();
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarInt(THandle aProvider)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnablePropertyVarInt();
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBool(THandle aProvider)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnablePropertyVarBool();
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarStr(THandle aProvider)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnablePropertyVarStr();
}

void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBin(THandle aProvider)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestBasic1C*>(aProvider)->EnablePropertyVarBin();
}

