#include "DvOpenhomeOrgTestBasic1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarUint(TUint aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarUint(TUint& aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    aValue = iPropertyVarUint->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarInt(TInt aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarInt(TInt& aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    aValue = iPropertyVarInt->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarBool(TBool aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarBool(TBool& aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    aValue = iPropertyVarBool->Value();
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarStr(const Brx& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    return SetPropertyString(*iPropertyVarStr, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarStr(Brhz& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    aValue.Set(iPropertyVarStr->Value());
}

void DvProviderOpenhomeOrgTestBasic1::WritePropertyVarStr(IWriter& aWriter)
{
    iPropertyVarStr->Write(aWriter);
}

TBool DvProviderOpenhomeOrgTestBasic1::SetPropertyVarBin(const Brx& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    return SetPropertyBinary(*iPropertyVarBin, aValue);
}

void DvProviderOpenhomeOrgTestBasic1::GetPropertyVarBin(Brh& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    aValue.Set(iPropertyVarBin->Value());
}

void DvProviderOpenhomeOrgTestBasic1::WritePropertyVarBin(IWriter& aWriter)
{
    iPropertyVarBin->Write(aWriter);
}

DvProviderOpenhomeOrgTestBasic1::DvProviderOpenhomeOrgTestBasic1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestBasic", 1)
{
    Construct();
}

DvProviderOpenhomeOrgTestBasic1::DvProviderOpenhomeOrgTestBasic1(DviDevice& aDevice)
    : DvProvider(aDevice, "openhome.org", "TestBasic", 1)
{
    Construct();
}

void DvProviderOpenhomeOrgTestBasic1::Construct()
{
    iPropertyVarUint = NULL;
    iPropertyVarInt = NULL;
    iPropertyVarBool = NULL;
    iPropertyVarStr = NULL;
    iPropertyVarBin = NULL;
}

void DvProviderOpenhomeOrgTestBasic1::EnablePropertyVarUint()
{
    iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
    iService->AddProperty(iPropertyVarUint); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1::EnablePropertyVarInt()
{
    iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
    iService->AddProperty(iPropertyVarInt); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1::EnablePropertyVarBool()
{
    iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
    iService->AddProperty(iPropertyVarBool); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1::EnablePropertyVarStr()
{
    iPropertyVarStr = new PropertyString(new ParameterString("VarStr"));
    iService->AddProperty(iPropertyVarStr); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1::EnablePropertyVarBin()
{
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

void DvProviderOpenhomeOrgTestBasic1::EnableActionEchoAllowedRangeUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoAllowedRangeUint");
    action->AddInputParameter(new ParameterUint("Value", 10, 20));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoEchoAllowedRangeUint);
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

void DvProviderOpenhomeOrgTestBasic1::EnableActionEchoAllowedValueString()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoEchoAllowedValueString);
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

void DvProviderOpenhomeOrgTestBasic1::EnableActionGetMultiple()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMultiple");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoGetMultiple);
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

void DvProviderOpenhomeOrgTestBasic1::EnableActionReportError()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReportError");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1::DoReportError);
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

void DvProviderOpenhomeOrgTestBasic1::DoIncrement(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respResult(aInvocation, "Result");
    Increment(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoAllowedRangeUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respResult(aInvocation, "Result");
    EchoAllowedRangeUint(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoDecrement(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respResult(aInvocation, "Result");
    Decrement(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoToggle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respResult(aInvocation, "Result");
    Toggle(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    EchoString(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoAllowedValueString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Value;
    aInvocation.InvocationReadString("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    EchoAllowedValueString(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoEchoBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brh Value;
    aInvocation.InvocationReadBinary("Value", Value);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBinary respResult(aInvocation, "Result");
    EchoBinary(invocation, Value, respResult);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetUint(invocation, ValueUint);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValueUint(aInvocation, "ValueUint");
    GetUint(invocation, respValueUint);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetInt(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetInt(invocation, ValueInt);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetInt(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respValueInt(aInvocation, "ValueInt");
    GetInt(invocation, respValueInt);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBool(invocation, ValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValueBool(aInvocation, "ValueBool");
    GetBool(invocation, respValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetMultiple(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint ValueUint = aInvocation.InvocationReadUint("ValueUint");
    TInt ValueInt = aInvocation.InvocationReadInt("ValueInt");
    TBool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetMultiple(invocation, ValueUint, ValueInt, ValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetMultiple(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValueUint(aInvocation, "ValueUint");
    DviInvocationResponseInt respValueInt(aInvocation, "ValueInt");
    DviInvocationResponseBool respValueBool(aInvocation, "ValueBool");
    GetMultiple(invocation, respValueUint, respValueInt, respValueBool);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ValueStr;
    aInvocation.InvocationReadString("ValueStr", ValueStr);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetString(invocation, ValueStr);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValueStr(aInvocation, "ValueStr");
    GetString(invocation, respValueStr);
}

void DvProviderOpenhomeOrgTestBasic1::DoSetBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brh ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", ValueBin);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBinary(invocation, ValueBin);
}

void DvProviderOpenhomeOrgTestBasic1::DoGetBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBinary respValueBin(aInvocation, "ValueBin");
    GetBinary(invocation, respValueBin);
}

void DvProviderOpenhomeOrgTestBasic1::DoToggleBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ToggleBool(invocation);
}

void DvProviderOpenhomeOrgTestBasic1::DoReportError(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ReportError(invocation);
}

void DvProviderOpenhomeOrgTestBasic1::DoWriteFile(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Data;
    aInvocation.InvocationReadString("Data", Data);
    Brhz FileFullName;
    aInvocation.InvocationReadString("FileFullName", FileFullName);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    WriteFile(invocation, Data, FileFullName);
}

void DvProviderOpenhomeOrgTestBasic1::DoShutdown(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Shutdown(invocation);
}

void DvProviderOpenhomeOrgTestBasic1::Increment(IDvInvocation& /*aResponse*/, TUint /*aValue*/, IDvInvocationResponseUint& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoAllowedRangeUint(IDvInvocation& /*aResponse*/, TUint /*aValue*/, IDvInvocationResponseUint& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Decrement(IDvInvocation& /*aResponse*/, TInt /*aValue*/, IDvInvocationResponseInt& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Toggle(IDvInvocation& /*aResponse*/, TBool /*aValue*/, IDvInvocationResponseBool& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoString(IDvInvocation& /*aResponse*/, const Brx& /*aValue*/, IDvInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoAllowedValueString(IDvInvocation& /*aResponse*/, const Brx& /*aValue*/, IDvInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::EchoBinary(IDvInvocation& /*aResponse*/, const Brx& /*aValue*/, IDvInvocationResponseBinary& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetUint(IDvInvocation& /*aResponse*/, TUint /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetUint(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetInt(IDvInvocation& /*aResponse*/, TInt /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetInt(IDvInvocation& /*aResponse*/, IDvInvocationResponseInt& /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetBool(IDvInvocation& /*aResponse*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetBool(IDvInvocation& /*aResponse*/, IDvInvocationResponseBool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetMultiple(IDvInvocation& /*aResponse*/, TUint /*aValueUint*/, TInt /*aValueInt*/, TBool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetMultiple(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValueUint*/, IDvInvocationResponseInt& /*aValueInt*/, IDvInvocationResponseBool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetString(IDvInvocation& /*aResponse*/, const Brx& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetString(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::SetBinary(IDvInvocation& /*aResponse*/, const Brx& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::GetBinary(IDvInvocation& /*aResponse*/, IDvInvocationResponseBinary& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::ToggleBool(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::ReportError(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::WriteFile(IDvInvocation& /*aResponse*/, const Brx& /*aData*/, const Brx& /*aFileFullName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1::Shutdown(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

