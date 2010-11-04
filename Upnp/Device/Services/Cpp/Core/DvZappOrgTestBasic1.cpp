#include <Core/DvZappOrgTestBasic1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderZappOrgTestBasic1::SetPropertyVarUint(TUint aValue)
{
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderZappOrgTestBasic1::GetPropertyVarUint(TUint& aValue)
{
    aValue = iPropertyVarUint->Value();
}

TBool DvProviderZappOrgTestBasic1::SetPropertyVarInt(TInt aValue)
{
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderZappOrgTestBasic1::GetPropertyVarInt(TInt& aValue)
{
    aValue = iPropertyVarInt->Value();
}

TBool DvProviderZappOrgTestBasic1::SetPropertyVarBool(TBool aValue)
{
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderZappOrgTestBasic1::GetPropertyVarBool(TBool& aValue)
{
    aValue = iPropertyVarBool->Value();
}

TBool DvProviderZappOrgTestBasic1::SetPropertyVarStr(const Brx& aValue)
{
    return SetPropertyString(*iPropertyVarStr, aValue);
}

void DvProviderZappOrgTestBasic1::GetPropertyVarStr(Brhz& aValue)
{
    aValue.Set(iPropertyVarStr->Value());
}

TBool DvProviderZappOrgTestBasic1::SetPropertyVarBin(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyVarBin, aValue);
}

void DvProviderZappOrgTestBasic1::GetPropertyVarBin(Brh& aValue)
{
    aValue.Set(iPropertyVarBin->Value());
}

DvProviderZappOrgTestBasic1::DvProviderZappOrgTestBasic1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestBasic", 1)
{
    Functor empty;
    iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"), empty);
    iService->AddProperty(iPropertyVarUint); // passes ownership
    iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"), empty);
    iService->AddProperty(iPropertyVarInt); // passes ownership
    iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"), empty);
    iService->AddProperty(iPropertyVarBool); // passes ownership
    iPropertyVarStr = new PropertyString(new ParameterString("VarStr"), empty);
    iService->AddProperty(iPropertyVarStr); // passes ownership
    iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"), empty);
    iService->AddProperty(iPropertyVarBin); // passes ownership
}

void DvProviderZappOrgTestBasic1::EnableActionIncrement()
{
    Zapp::Action* action = new Zapp::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionDecrement()
{
    Zapp::Action* action = new Zapp::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionToggle()
{
    Zapp::Action* action = new Zapp::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionEchoString()
{
    Zapp::Action* action = new Zapp::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionEchoBinary()
{
    Zapp::Action* action = new Zapp::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetUint()
{
    Zapp::Action* action = new Zapp::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionGetUint()
{
    Zapp::Action* action = new Zapp::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetInt()
{
    Zapp::Action* action = new Zapp::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionGetInt()
{
    Zapp::Action* action = new Zapp::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetBool()
{
    Zapp::Action* action = new Zapp::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionGetBool()
{
    Zapp::Action* action = new Zapp::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetMultiple()
{
    Zapp::Action* action = new Zapp::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetString()
{
    Zapp::Action* action = new Zapp::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionGetString()
{
    Zapp::Action* action = new Zapp::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionSetBinary()
{
    Zapp::Action* action = new Zapp::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionGetBinary()
{
    Zapp::Action* action = new Zapp::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::EnableActionToggleBool()
{
    Zapp::Action* action = new Zapp::Action("ToggleBool");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderZappOrgTestBasic1::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1::DoIncrement(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respResult(aInvocation, "Result");
    Increment(resp, aVersion, Value, respResult);
}

void DvProviderZappOrgTestBasic1::DoDecrement(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respResult(aInvocation, "Result");
    Decrement(resp, aVersion, Value, respResult);
}

void DvProviderZappOrgTestBasic1::DoToggle(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respResult(aInvocation, "Result");
    Toggle(resp, aVersion, Value, respResult);
}

void DvProviderZappOrgTestBasic1::DoEchoString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResult(aInvocation, "Result");
    EchoString(resp, aVersion, Value, respResult);
}

void DvProviderZappOrgTestBasic1::DoEchoBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh Value;
    aInvocation.InvocationReadBinary("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respResult(aInvocation, "Result");
    EchoBinary(resp, aVersion, Value, respResult);
}

void DvProviderZappOrgTestBasic1::DoSetUint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetUint(resp, aVersion, ValueUint);
}

void DvProviderZappOrgTestBasic1::DoGetUint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respValueUint(aInvocation, "ValueUint");
    GetUint(resp, aVersion, respValueUint);
}

void DvProviderZappOrgTestBasic1::DoSetInt(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInt(resp, aVersion, ValueInt);
}

void DvProviderZappOrgTestBasic1::DoGetInt(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respValueInt(aInvocation, "ValueInt");
    GetInt(resp, aVersion, respValueInt);
}

void DvProviderZappOrgTestBasic1::DoSetBool(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBool(resp, aVersion, ValueBool);
}

void DvProviderZappOrgTestBasic1::DoGetBool(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValueBool(aInvocation, "ValueBool");
    GetBool(resp, aVersion, respValueBool);
}

void DvProviderZappOrgTestBasic1::DoSetMultiple(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetMultiple(resp, aVersion, ValueUint, ValueInt, ValueBool);
}

void DvProviderZappOrgTestBasic1::DoSetString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ValueStr;
    aInvocation.InvocationReadString("ValueStr", ValueStr);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetString(resp, aVersion, ValueStr);
}

void DvProviderZappOrgTestBasic1::DoGetString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValueStr(aInvocation, "ValueStr");
    GetString(resp, aVersion, respValueStr);
}

void DvProviderZappOrgTestBasic1::DoSetBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", ValueBin);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBinary(resp, aVersion, ValueBin);
}

void DvProviderZappOrgTestBasic1::DoGetBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respValueBin(aInvocation, "ValueBin");
    GetBinary(resp, aVersion, respValueBin);
}

void DvProviderZappOrgTestBasic1::DoToggleBool(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ToggleBool(resp, aVersion);
}

void DvProviderZappOrgTestBasic1::Increment(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/, IInvocationResponseUint& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::Decrement(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/, IInvocationResponseInt& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::Toggle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/, IInvocationResponseBool& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::EchoString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValue*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::EchoBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValue*/, IInvocationResponseBinary& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetUint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::GetUint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetInt(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::GetInt(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseInt& /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::GetBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetMultiple(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValueUint*/, TInt /*aValueInt*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::GetString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::SetBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::GetBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1::ToggleBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

