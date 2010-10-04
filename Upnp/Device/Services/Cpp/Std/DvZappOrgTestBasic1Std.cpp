#include <Std/DvZappOrgTestBasic1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceZappOrgTestBasic1Cpp::SetPropertyVarUint(uint32_t aValue)
{
    SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvServiceZappOrgTestBasic1Cpp::GetPropertyVarUint(uint32_t& aValue)
{
    aValue = iPropertyVarUint->Value();
}

void DvServiceZappOrgTestBasic1Cpp::SetPropertyVarInt(int32_t aValue)
{
    SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvServiceZappOrgTestBasic1Cpp::GetPropertyVarInt(int32_t& aValue)
{
    aValue = iPropertyVarInt->Value();
}

void DvServiceZappOrgTestBasic1Cpp::SetPropertyVarBool(bool aValue)
{
    SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvServiceZappOrgTestBasic1Cpp::GetPropertyVarBool(bool& aValue)
{
    aValue = iPropertyVarBool->Value();
}

void DvServiceZappOrgTestBasic1Cpp::SetPropertyVarStr(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyVarStr, buf);
}

void DvServiceZappOrgTestBasic1Cpp::GetPropertyVarStr(std::string& aValue)
{
    const Brx& val = iPropertyVarStr->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceZappOrgTestBasic1Cpp::SetPropertyVarBin(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyBinary(*iPropertyVarBin, buf);
}

void DvServiceZappOrgTestBasic1Cpp::GetPropertyVarBin(std::string& aValue)
{
    const Brx& val = iPropertyVarBin->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceZappOrgTestBasic1Cpp::DvServiceZappOrgTestBasic1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestBasic", 1)
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

void DvServiceZappOrgTestBasic1Cpp::EnableActionIncrement()
{
    Zapp::Action* action = new Zapp::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoIncrement);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionDecrement()
{
    Zapp::Action* action = new Zapp::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoDecrement);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionToggle()
{
    Zapp::Action* action = new Zapp::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoToggle);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionEchoString()
{
    Zapp::Action* action = new Zapp::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoEchoString);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionEchoBinary()
{
    Zapp::Action* action = new Zapp::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetUint()
{
    Zapp::Action* action = new Zapp::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetUint);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionGetUint()
{
    Zapp::Action* action = new Zapp::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoGetUint);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetInt()
{
    Zapp::Action* action = new Zapp::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetInt);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionGetInt()
{
    Zapp::Action* action = new Zapp::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoGetInt);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetBool()
{
    Zapp::Action* action = new Zapp::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetBool);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionGetBool()
{
    Zapp::Action* action = new Zapp::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoGetBool);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetMultiple()
{
    Zapp::Action* action = new Zapp::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetString()
{
    Zapp::Action* action = new Zapp::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetString);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionGetString()
{
    Zapp::Action* action = new Zapp::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoGetString);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionSetBinary()
{
    Zapp::Action* action = new Zapp::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::EnableActionGetBinary()
{
    Zapp::Action* action = new Zapp::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestBasic1Cpp::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestBasic1Cpp::DoIncrement(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    uint32_t respResult;
    Increment(aVersion, Value, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoDecrement(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    int32_t respResult;
    Decrement(aVersion, Value, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoToggle(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    bool respResult;
    Toggle(aVersion, Value, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterResult(aInvocation, "Result");
    respWriterResult.Write(respResult);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoEchoString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Value;
    aInvocation.InvocationReadString("Value", buf_Value);
    std::string Value((const char*)buf_Value.Ptr(), buf_Value.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    EchoString(aVersion, Value, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoEchoBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh buf_Value;
    aInvocation.InvocationReadBinary("Value", buf_Value);
    std::string Value((const char*)buf_Value.Ptr(), buf_Value.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    EchoBinary(aVersion, Value, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteBinaryEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetUint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    SetUint(aVersion, ValueUint);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoGetUint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValueUint;
    GetUint(aVersion, respValueUint);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValueUint(aInvocation, "ValueUint");
    respWriterValueUint.Write(respValueUint);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetInt(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    SetInt(aVersion, ValueInt);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoGetInt(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValueInt;
    GetInt(aVersion, respValueInt);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterValueInt(aInvocation, "ValueInt");
    respWriterValueInt.Write(respValueInt);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetBool(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    SetBool(aVersion, ValueBool);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoGetBool(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValueBool;
    GetBool(aVersion, respValueBool);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterValueBool(aInvocation, "ValueBool");
    respWriterValueBool.Write(respValueBool);
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetMultiple(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t ValueUint = aInvocation.InvocationReadUint("ValueUint");
    int32_t ValueInt = aInvocation.InvocationReadInt("ValueInt");
    bool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    SetMultiple(aVersion, ValueUint, ValueInt, ValueBool);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ValueStr;
    aInvocation.InvocationReadString("ValueStr", buf_ValueStr);
    std::string ValueStr((const char*)buf_ValueStr.Ptr(), buf_ValueStr.Bytes());
    aInvocation.InvocationReadEnd();
    SetString(aVersion, ValueStr);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoGetString(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueStr;
    GetString(aVersion, respValueStr);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValueStr(aInvocation, "ValueStr");
    Brn buf_ValueStr((const TByte*)respValueStr.c_str(), respValueStr.length());
    respWriterValueStr.Write(buf_ValueStr);
    aInvocation.InvocationWriteStringEnd("ValueStr");
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoSetBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brh buf_ValueBin;
    aInvocation.InvocationReadBinary("ValueBin", buf_ValueBin);
    std::string ValueBin((const char*)buf_ValueBin.Ptr(), buf_ValueBin.Bytes());
    aInvocation.InvocationReadEnd();
    SetBinary(aVersion, ValueBin);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::DoGetBinary(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueBin;
    GetBinary(aVersion, respValueBin);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriterValueBin(aInvocation, "ValueBin");
    Brn buf_ValueBin((const TByte*)respValueBin.c_str(), respValueBin.length());
    respWriterValueBin.Write(buf_ValueBin);
    aInvocation.InvocationWriteBinaryEnd("ValueBin");
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestBasic1Cpp::Increment(uint32_t /*aVersion*/, uint32_t /*aValue*/, uint32_t& /*aResult*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::Decrement(uint32_t /*aVersion*/, int32_t /*aValue*/, int32_t& /*aResult*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::Toggle(uint32_t /*aVersion*/, bool /*aValue*/, bool& /*aResult*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::EchoString(uint32_t /*aVersion*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::EchoBinary(uint32_t /*aVersion*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetUint(uint32_t /*aVersion*/, uint32_t /*aValueUint*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::GetUint(uint32_t /*aVersion*/, uint32_t& /*aValueUint*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetInt(uint32_t /*aVersion*/, int32_t /*aValueInt*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::GetInt(uint32_t /*aVersion*/, int32_t& /*aValueInt*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetBool(uint32_t /*aVersion*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::GetBool(uint32_t /*aVersion*/, bool& /*aValueBool*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetMultiple(uint32_t /*aVersion*/, uint32_t /*aValueUint*/, int32_t /*aValueInt*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetString(uint32_t /*aVersion*/, const std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::GetString(uint32_t /*aVersion*/, std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::SetBinary(uint32_t /*aVersion*/, const std::string& /*aValueBin*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestBasic1Cpp::GetBinary(uint32_t /*aVersion*/, std::string& /*aValueBin*/)
{
    ASSERTS();
}

