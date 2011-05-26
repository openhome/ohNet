#include "DvOpenhomeOrgTestBasic1.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarUint(TUint aValue)
{
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarUint(TUint& aValue)
{
    aValue = iPropertyVarUint->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarInt(TInt aValue)
{
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarInt(TInt& aValue)
{
    aValue = iPropertyVarInt->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarBool(TBool aValue)
{
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarBool(TBool& aValue)
{
    aValue = iPropertyVarBool->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarStr(const Brx& aValue)
{
    return SetPropertyString(*iPropertyVarStr, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarStr(Brhz& aValue)
{
    aValue.Set(iPropertyVarStr->Value());
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarBin(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyVarBin, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarBin(Brh& aValue)
{
    aValue.Set(iPropertyVarBin->Value());
}

DvProviderOpenhomeOrgTestBasic1::DvProviderOpenhomeOrgTestBasic1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestBasic", 1)
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

void DvProviderOpenhomeOrgTestBasic1::EnableActionIncrement()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionDecrement()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionToggle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionEchoString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionEchoBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetInt()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetInt()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetMultiple()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionSetBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionToggleBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ToggleBool");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionWriteFile()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("WriteFile");
    action->AddInputParameter(new ParameterString("Data"));
    action->AddInputParameter(new ParameterString("FileFullName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoWriteFile);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::EnableActionShutdown()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shutdown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoShutdown);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1::DoIncrement(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respResult(aInvocation, "Result");
    Increment(resp, aVersion, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoDecrement(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respResult(aInvocation, "Result");
    Decrement(resp, aVersion, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoToggle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respResult(aInvocation, "Result");
    Toggle(resp, aVersion, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResult(aInvocation, "Result");
    EchoString(resp, aVersion, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh Value;
    aInvocation.InvocationReadBinary("Value", Value);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respResult(aInvocation, "Result");
    EchoBinary(resp, aVersion, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetUint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetUint(resp, aVersion, ValueUint);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetUint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respValueUint(aInvocation, "ValueUint");
    GetUint(resp, aVersion, respValueUint);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetInt(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetInt(resp, aVersion, ValueInt);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetInt(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respValueInt(aInvocation, "ValueInt");
    GetInt(resp, aVersion, respValueInt);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBool(resp, aVersion, ValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValueBool(aInvocation, "ValueBool");
    GetBool(resp, aVersion, respValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetMultiple(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetMultiple(resp, aVersion, ValueUint, ValueInt, ValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ValueStr;
    aInvocation.InvocationReadString("ValueStr", ValueStr);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetString(resp, aVersion, ValueStr);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValueStr(aInvocation, "ValueStr");
    GetString(resp, aVersion, respValueStr);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", ValueBin);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBinary(resp, aVersion, ValueBin);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respValueBin(aInvocation, "ValueBin");
    GetBinary(resp, aVersion, respValueBin);
}

void DvProviderOpenhomeOrgTestBasic1::DoToggleBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ToggleBool(resp, aVersion);
}

void DvProviderOpenhomeOrgTestBasic1::DoWriteFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Data;
    aInvocation.InvocationReadString("Data", Data);
    Brhz FileFullName;
    aInvocation.InvocationReadString("FileFullName", FileFullName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    WriteFile(resp, aVersion, Data, FileFullName);
}

void DvProviderOpenhomeOrgTestBasic1::DoShutdown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Shutdown(resp, aVersion);
}

void DvProviderOpenhomeOrgTestBasic1::Increment(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/, IInvocationResponseUint& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Decrement(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/, IInvocationResponseInt& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Toggle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/, IInvocationResponseBool& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValue*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValue*/, IInvocationResponseBinary& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetUint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetUint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetInt(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetInt(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseInt& /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetMultiple(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValueUint*/, TInt /*aValueInt*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetString(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetBinary(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::ToggleBool(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::WriteFile(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aData*/, const Brx& /*aFileFullName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Shutdown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

