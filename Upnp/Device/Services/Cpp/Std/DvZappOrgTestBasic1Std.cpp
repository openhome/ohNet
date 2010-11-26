#include <Std/DvZappOrgTestBasic1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderZappOrgTestBasic1Cpp::SetPropertyVarUint(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVarUint, aValue);
}

void DvProviderZappOrgTestBasic1Cpp::GetPropertyVarUint(uint32_t& aValue)
{
    aValue = iPropertyVarUint->Value();
}

bool DvProviderZappOrgTestBasic1Cpp::SetPropertyVarInt(int32_t aValue)
{
    return SetPropertyInt(*iPropertyVarInt, aValue);
}

void DvProviderZappOrgTestBasic1Cpp::GetPropertyVarInt(int32_t& aValue)
{
    aValue = iPropertyVarInt->Value();
}

bool DvProviderZappOrgTestBasic1Cpp::SetPropertyVarBool(bool aValue)
{
    return SetPropertyBool(*iPropertyVarBool, aValue);
}

void DvProviderZappOrgTestBasic1Cpp::GetPropertyVarBool(bool& aValue)
{
    aValue = iPropertyVarBool->Value();
}

bool DvProviderZappOrgTestBasic1Cpp::SetPropertyVarStr(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyVarStr, buf);
}

void DvProviderZappOrgTestBasic1Cpp::GetPropertyVarStr(std::string& aValue)
{
    const Brx& val = iPropertyVarStr->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderZappOrgTestBasic1Cpp::SetPropertyVarBin(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyVarBin, buf);
}

void DvProviderZappOrgTestBasic1Cpp::GetPropertyVarBin(std::string& aValue)
{
    const Brx& val = iPropertyVarBin->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderZappOrgTestBasic1Cpp::DvProviderZappOrgTestBasic1Cpp(DvDeviceStd& aDevice)
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

void DvProviderZappOrgTestBasic1Cpp::EnableActionIncrement()
{
    Zapp::Action* action = new Zapp::Action("Increment");
    action->AddInputParameter(new ParameterUint("Value"));
    action->AddOutputParameter(new ParameterUint("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoIncrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionDecrement()
{
    Zapp::Action* action = new Zapp::Action("Decrement");
    action->AddInputParameter(new ParameterInt("Value"));
    action->AddOutputParameter(new ParameterInt("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoDecrement);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionToggle()
{
    Zapp::Action* action = new Zapp::Action("Toggle");
    action->AddInputParameter(new ParameterBool("Value"));
    action->AddOutputParameter(new ParameterBool("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoToggle);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionEchoString()
{
    Zapp::Action* action = new Zapp::Action("EchoString");
    action->AddInputParameter(new ParameterString("Value"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoEchoString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionEchoBinary()
{
    Zapp::Action* action = new Zapp::Action("EchoBinary");
    action->AddInputParameter(new ParameterBinary("Value"));
    action->AddOutputParameter(new ParameterBinary("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoEchoBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetUint()
{
    Zapp::Action* action = new Zapp::Action("SetUint");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionGetUint()
{
    Zapp::Action* action = new Zapp::Action("GetUint");
    action->AddOutputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoGetUint);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetInt()
{
    Zapp::Action* action = new Zapp::Action("SetInt");
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionGetInt()
{
    Zapp::Action* action = new Zapp::Action("GetInt");
    action->AddOutputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoGetInt);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetBool()
{
    Zapp::Action* action = new Zapp::Action("SetBool");
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionGetBool()
{
    Zapp::Action* action = new Zapp::Action("GetBool");
    action->AddOutputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoGetBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetMultiple()
{
    Zapp::Action* action = new Zapp::Action("SetMultiple");
    action->AddInputParameter(new ParameterRelated("ValueUint", *iPropertyVarUint));
    action->AddInputParameter(new ParameterRelated("ValueInt", *iPropertyVarInt));
    action->AddInputParameter(new ParameterRelated("ValueBool", *iPropertyVarBool));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetMultiple);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetString()
{
    Zapp::Action* action = new Zapp::Action("SetString");
    action->AddInputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionGetString()
{
    Zapp::Action* action = new Zapp::Action("GetString");
    action->AddOutputParameter(new ParameterRelated("ValueStr", *iPropertyVarStr));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoGetString);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionSetBinary()
{
    Zapp::Action* action = new Zapp::Action("SetBinary");
    action->AddInputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoSetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionGetBinary()
{
    Zapp::Action* action = new Zapp::Action("GetBinary");
    action->AddOutputParameter(new ParameterRelated("ValueBin", *iPropertyVarBin));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoGetBinary);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionToggleBool()
{
    Zapp::Action* action = new Zapp::Action("ToggleBool");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoToggleBool);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionWriteFile()
{
    Zapp::Action* action = new Zapp::Action("WriteFile");
    action->AddInputParameter(new ParameterString("Data"));
    action->AddInputParameter(new ParameterString("FileFullName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoWriteFile);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::EnableActionShutdown()
{
    Zapp::Action* action = new Zapp::Action("Shutdown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestBasic1Cpp::DoShutdown);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestBasic1Cpp::DoIncrement(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoDecrement(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoToggle(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoEchoString(IDviInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoEchoBinary(IDviInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteBinaryEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoSetUint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t ValueUint = aInvocation.InvocationReadUint("ValueUint");
    aInvocation.InvocationReadEnd();
    SetUint(aVersion, ValueUint);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoGetUint(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoSetInt(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t ValueInt = aInvocation.InvocationReadInt("ValueInt");
    aInvocation.InvocationReadEnd();
    SetInt(aVersion, ValueInt);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoGetInt(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoSetBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool ValueBool = aInvocation.InvocationReadBool("ValueBool");
    aInvocation.InvocationReadEnd();
    SetBool(aVersion, ValueBool);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoGetBool(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoSetMultiple(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoSetString(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoGetString(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueStr;
    GetString(aVersion, respValueStr);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValueStr(aInvocation, "ValueStr");
    Brn buf_ValueStr((const TByte*)respValueStr.c_str(), (TUint)respValueStr.length());
    respWriterValueStr.Write(buf_ValueStr);
    aInvocation.InvocationWriteStringEnd("ValueStr");
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoSetBinary(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderZappOrgTestBasic1Cpp::DoGetBinary(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValueBin;
    GetBinary(aVersion, respValueBin);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriterValueBin(aInvocation, "ValueBin");
    Brn buf_ValueBin((const TByte*)respValueBin.c_str(), (TUint)respValueBin.length());
    respWriterValueBin.Write(buf_ValueBin);
    aInvocation.InvocationWriteBinaryEnd("ValueBin");
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoToggleBool(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    ToggleBool(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoWriteFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Data;
    aInvocation.InvocationReadString("Data", buf_Data);
    std::string Data((const char*)buf_Data.Ptr(), buf_Data.Bytes());
    Brhz buf_FileFullName;
    aInvocation.InvocationReadString("FileFullName", buf_FileFullName);
    std::string FileFullName((const char*)buf_FileFullName.Ptr(), buf_FileFullName.Bytes());
    aInvocation.InvocationReadEnd();
    WriteFile(aVersion, Data, FileFullName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::DoShutdown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Shutdown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestBasic1Cpp::Increment(uint32_t /*aVersion*/, uint32_t /*aValue*/, uint32_t& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::Decrement(uint32_t /*aVersion*/, int32_t /*aValue*/, int32_t& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::Toggle(uint32_t /*aVersion*/, bool /*aValue*/, bool& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::EchoString(uint32_t /*aVersion*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::EchoBinary(uint32_t /*aVersion*/, const std::string& /*aValue*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetUint(uint32_t /*aVersion*/, uint32_t /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::GetUint(uint32_t /*aVersion*/, uint32_t& /*aValueUint*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetInt(uint32_t /*aVersion*/, int32_t /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::GetInt(uint32_t /*aVersion*/, int32_t& /*aValueInt*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetBool(uint32_t /*aVersion*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::GetBool(uint32_t /*aVersion*/, bool& /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetMultiple(uint32_t /*aVersion*/, uint32_t /*aValueUint*/, int32_t /*aValueInt*/, bool /*aValueBool*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetString(uint32_t /*aVersion*/, const std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::GetString(uint32_t /*aVersion*/, std::string& /*aValueStr*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::SetBinary(uint32_t /*aVersion*/, const std::string& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::GetBinary(uint32_t /*aVersion*/, std::string& /*aValueBin*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::ToggleBool(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::WriteFile(uint32_t /*aVersion*/, const std::string& /*aData*/, const std::string& /*aFileFullName*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestBasic1Cpp::Shutdown(uint32_t /*aVersion*/)
{
    ASSERTS();
}

