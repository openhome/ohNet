#include <Std/DvZappOrgTestWidgetController1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderZappOrgTestWidgetController1Cpp::DvProviderZappOrgTestWidgetController1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestWidgetController", 1)
{
    
}

void DvProviderZappOrgTestWidgetController1Cpp::EnableActionCreateWidget()
{
    Zapp::Action* action = new Zapp::Action("CreateWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1Cpp::DoCreateWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1Cpp::EnableActionRemoveWidget()
{
    Zapp::Action* action = new Zapp::Action("RemoveWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1Cpp::DoRemoveWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1Cpp::EnableActionSetWidgetRegister()
{
    Zapp::Action* action = new Zapp::Action("SetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1Cpp::DoSetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1Cpp::EnableActionGetWidgetRegister()
{
    Zapp::Action* action = new Zapp::Action("GetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddOutputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1Cpp::DoGetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1Cpp::DoCreateWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", buf_WidgetUdn);
    std::string WidgetUdn((const char*)buf_WidgetUdn.Ptr(), buf_WidgetUdn.Bytes());
    uint32_t WidgetClass = aInvocation.InvocationReadUint("WidgetClass");
    aInvocation.InvocationReadEnd();
    CreateWidget(aVersion, WidgetUdn, WidgetClass);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidgetController1Cpp::DoRemoveWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", buf_WidgetUdn);
    std::string WidgetUdn((const char*)buf_WidgetUdn.Ptr(), buf_WidgetUdn.Bytes());
    aInvocation.InvocationReadEnd();
    RemoveWidget(aVersion, WidgetUdn);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidgetController1Cpp::DoSetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", buf_WidgetUdn);
    std::string WidgetUdn((const char*)buf_WidgetUdn.Ptr(), buf_WidgetUdn.Bytes());
    uint32_t RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    uint32_t RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    SetWidgetRegister(aVersion, WidgetUdn, RegisterIndex, RegisterValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidgetController1Cpp::DoGetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", buf_WidgetUdn);
    std::string WidgetUdn((const char*)buf_WidgetUdn.Ptr(), buf_WidgetUdn.Bytes());
    uint32_t RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    aInvocation.InvocationReadEnd();
    uint32_t respRegisterValue;
    GetWidgetRegister(aVersion, WidgetUdn, RegisterIndex, respRegisterValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterRegisterValue(aInvocation, "RegisterValue");
    respWriterRegisterValue.Write(respRegisterValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidgetController1Cpp::CreateWidget(uint32_t /*aVersion*/, const std::string& /*aWidgetUdn*/, uint32_t /*aWidgetClass*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1Cpp::RemoveWidget(uint32_t /*aVersion*/, const std::string& /*aWidgetUdn*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1Cpp::SetWidgetRegister(uint32_t /*aVersion*/, const std::string& /*aWidgetUdn*/, uint32_t /*aRegisterIndex*/, uint32_t /*aRegisterValue*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1Cpp::GetWidgetRegister(uint32_t /*aVersion*/, const std::string& /*aWidgetUdn*/, uint32_t /*aRegisterIndex*/, uint32_t& /*aRegisterValue*/)
{
    ASSERTS();
}

