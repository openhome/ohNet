#include "DvOpenhomeOrgTestBasic1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderOpenhomeOrgTestBasic1Cpp::SetPropertyVarUint(uint32_t aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetPropertyVarUint(uint32_t& aValue)
{
    ASSERT(iPropertyVarUint != NULL);
    aValue = iPropertyVarUint->Value();
}

bool DvProviderOpenhomeOrgTestBasic1Cpp::SetPropertyVarInt(int32_t aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetPropertyVarInt(int32_t& aValue)
{
    ASSERT(iPropertyVarInt != NULL);
    aValue = iPropertyVarInt->Value();
}

bool DvProviderOpenhomeOrgTestBasic1Cpp::SetPropertyVarBool(bool aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetPropertyVarBool(bool& aValue)
{
    ASSERT(iPropertyVarBool != NULL);
    aValue = iPropertyVarBool->Value();
}

bool DvProviderOpenhomeOrgTestBasic1Cpp::SetPropertyVarStr(const std::string& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyVarStr, buf);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetPropertyVarStr(std::string& aValue)
{
    ASSERT(iPropertyVarStr != NULL);
    const Brx& val = iPropertyVarStr->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderOpenhomeOrgTestBasic1Cpp::SetPropertyVarBin(const std::string& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyVarBin, buf);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetPropertyVarBin(std::string& aValue)
{
    ASSERT(iPropertyVarBin != NULL);
    const Brx& val = iPropertyVarBin->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderOpenhomeOrgTestBasic1Cpp::DvProviderOpenhomeOrgTestBasic1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestBasic", 1)
{
    iPropertyVarUint = NULL;
    iPropertyVarInt = NULL;
    iPropertyVarBool = NULL;
    iPropertyVarStr = NULL;
    iPropertyVarBin = NULL;
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnablePropertyVarUint()
{
    iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
    iService->AddProperty(iPropertyVarUint); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnablePropertyVarInt()
{
    iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
    iService->AddProperty(iPropertyVarInt); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnablePropertyVarBool()
{
    iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
    iService->AddProperty(iPropertyVarBool); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnablePropertyVarStr()
{
    iPropertyVarStr = new PropertyString(new ParameterString("VarStr"));
    iService->AddProperty(iPropertyVarStr); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnablePropertyVarBin()
{
    iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"));
    iService->AddProperty(iPropertyVarBin); // passes ownership
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionIncrement()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionEchoAllowedRangeUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoAllowedRangeUint");
    action->AddInputParameter(new ParameterUint("Value", 10, 20));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoAllowedRangeUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionDecrement()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionToggle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionEchoString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionEchoAllowedValueString()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoAllowedValueString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionEchoBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetUint()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetInt()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetInt()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetMultiple()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetMultiple()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMultiple");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetString()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionSetBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionGetBinary()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionToggleBool()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ToggleBool");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionWriteFile()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("WriteFile");
    action->AddInputParameter(new ParameterString("Data"));
    action->AddInputParameter(new ParameterString("FileFullName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoWriteFile);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EnableActionShutdown()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shutdown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestBasic1Cpp::DoShutdown);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoIncrement(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    uint32_t respResult;
    DvInvocationStd invocation(aInvocation);
    Increment(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoAllowedRangeUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    uint32_t respResult;
    DvInvocationStd invocation(aInvocation);
    EchoAllowedRangeUint(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoDecrement(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    int32_t respResult;
    DvInvocationStd invocation(aInvocation);
    Decrement(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoToggle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    bool respResult;
    DvInvocationStd invocation(aInvocation);
    Toggle(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Value;
    aInvocation.InvocationReadString("Value", buf_Value);
    std::string Value((const char*)buf_Value.Ptr(), buf_Value.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    DvInvocationStd invocation(aInvocation);
    EchoString(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoAllowedValueString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Value;
    aInvocation.InvocationReadString("Value", buf_Value);
    std::string Value((const char*)buf_Value.Ptr(), buf_Value.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    DvInvocationStd invocation(aInvocation);
    EchoAllowedValueString(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoEchoBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brh buf_Value;
    aInvocation.InvocationReadBinary("Value", buf_Value);
    std::string Value((const char*)buf_Value.Ptr(), buf_Value.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    DvInvocationStd invocation(aInvocation);
    EchoBinary(invocation, Value, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBinary respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteBinaryEnd("Result");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetUint(invocation, ValueUint);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetUint(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValueUint;
    DvInvocationStd invocation(aInvocation);
    GetUint(invocation, respValueUint);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValueUint(aInvocation, "ValueUint");
    respWriterValueUint.Write(respValueUint);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetInt(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetInt(invocation, ValueInt);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetInt(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValueInt;
    DvInvocationStd invocation(aInvocation);
    GetInt(invocation, respValueInt);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterValueInt(aInvocation, "ValueInt");
    respWriterValueInt.Write(respValueInt);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBool(invocation, ValueBool);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValueBool;
    DvInvocationStd invocation(aInvocation);
    GetBool(invocation, respValueBool);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValueBool(aInvocation, "ValueBool");
    respWriterValueBool.Write(respValueBool);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetMultiple(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t ValueUint = aInvocation.InvocationReadUint("ValueUint");
    int32_t ValueInt = aInvocation.InvocationReadInt("ValueInt");
    bool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetMultiple(invocation, ValueUint, ValueInt, ValueBool);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetMultiple(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValueUint;
    int32_t respValueInt;
    bool respValueBool;
    DvInvocationStd invocation(aInvocation);
    GetMultiple(invocation, respValueUint, respValueInt, respValueBool);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValueUint(aInvocation, "ValueUint");
    respWriterValueUint.Write(respValueUint);
    DviInvocationResponseInt respWriterValueInt(aInvocation, "ValueInt");
    respWriterValueInt.Write(respValueInt);
    DviInvocationResponseBool respWriterValueBool(aInvocation, "ValueBool");
    respWriterValueBool.Write(respValueBool);
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ValueStr;
    aInvocation.InvocationReadString("ValueStr", buf_ValueStr);
    std::string ValueStr((const char*)buf_ValueStr.Ptr(), buf_ValueStr.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetString(invocation, ValueStr);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetString(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueStr;
    DvInvocationStd invocation(aInvocation);
    GetString(invocation, respValueStr);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValueStr(aInvocation, "ValueStr");
    Brn buf_ValueStr((const TByte*)respValueStr.c_str(), (TUint)respValueStr.length());
    respWriterValueStr.Write(buf_ValueStr);
    aInvocation.InvocationWriteStringEnd("ValueStr");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoSetBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brh buf_ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", buf_ValueBin);
    std::string ValueBin((const char*)buf_ValueBin.Ptr(), buf_ValueBin.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBinary(invocation, ValueBin);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoGetBinary(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueBin;
    DvInvocationStd invocation(aInvocation);
    GetBinary(invocation, respValueBin);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBinary respWriterValueBin(aInvocation, "ValueBin");
    Brn buf_ValueBin((const TByte*)respValueBin.c_str(), (TUint)respValueBin.length());
    respWriterValueBin.Write(buf_ValueBin);
    aInvocation.InvocationWriteBinaryEnd("ValueBin");
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoToggleBool(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    ToggleBool(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoWriteFile(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Data;
    aInvocation.InvocationReadString("Data", buf_Data);
    std::string Data((const char*)buf_Data.Ptr(), buf_Data.Bytes());
    Brhz buf_FileFullName;
    aInvocation.InvocationReadString("FileFullName", buf_FileFullName);
    std::string FileFullName((const char*)buf_FileFullName.Ptr(), buf_FileFullName.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    WriteFile(invocation, Data, FileFullName);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::DoShutdown(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Shutdown(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::Increment(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/, uint32_t& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EchoAllowedRangeUint(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/, uint32_t& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::Decrement(IDvInvocationStd& /*aInvocation*/, int32_t /*aValue*/, int32_t& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::Toggle(IDvInvocationStd& /*aInvocation*/, bool /*aValue*/, bool& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EchoString(IDvInvocationStd& /*aInvocation*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EchoAllowedValueString(IDvInvocationStd& /*aInvocation*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::EchoBinary(IDvInvocationStd& /*aInvocation*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetUint(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetUint(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetInt(IDvInvocationStd& /*aInvocation*/, int32_t /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetInt(IDvInvocationStd& /*aInvocation*/, int32_t& /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetBool(IDvInvocationStd& /*aInvocation*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetBool(IDvInvocationStd& /*aInvocation*/, bool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetMultiple(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValueUint*/, int32_t /*aValueInt*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetMultiple(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValueUint*/, int32_t& /*aValueInt*/, bool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetString(IDvInvocationStd& /*aInvocation*/, const std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetString(IDvInvocationStd& /*aInvocation*/, std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::SetBinary(IDvInvocationStd& /*aInvocation*/, const std::string& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::GetBinary(IDvInvocationStd& /*aInvocation*/, std::string& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::ToggleBool(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::WriteFile(IDvInvocationStd& /*aInvocation*/, const std::string& /*aData*/, const std::string& /*aFileFullName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestBasic1Cpp::Shutdown(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

