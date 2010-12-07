#include <Core/DvZappOrgTestWidgetController1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderZappOrgTestWidgetController1::DvProviderZappOrgTestWidgetController1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestWidgetController", 1)
{
    
}

void DvProviderZappOrgTestWidgetController1::EnableActionCreateWidget()
{
    Zapp::Action* action = new Zapp::Action("CreateWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1::DoCreateWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1::EnableActionRemoveWidget()
{
    Zapp::Action* action = new Zapp::Action("RemoveWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1::DoRemoveWidget);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1::EnableActionSetWidgetRegister()
{
    Zapp::Action* action = new Zapp::Action("SetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1::DoSetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1::EnableActionGetWidgetRegister()
{
    Zapp::Action* action = new Zapp::Action("GetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddOutputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidgetController1::DoGetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidgetController1::DoCreateWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint WidgetClass = aInvocation.InvocationReadUint("WidgetClass");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    CreateWidget(resp, aVersion, WidgetUdn, WidgetClass);
}

void DvProviderZappOrgTestWidgetController1::DoRemoveWidget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    RemoveWidget(resp, aVersion, WidgetUdn);
}

void DvProviderZappOrgTestWidgetController1::DoSetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    TUint RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetWidgetRegister(resp, aVersion, WidgetUdn, RegisterIndex, RegisterValue);
}

void DvProviderZappOrgTestWidgetController1::DoGetWidgetRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respRegisterValue(aInvocation, "RegisterValue");
    GetWidgetRegister(resp, aVersion, WidgetUdn, RegisterIndex, respRegisterValue);
}

void DvProviderZappOrgTestWidgetController1::CreateWidget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/, TUint /*aWidgetClass*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1::RemoveWidget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1::SetWidgetRegister(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/, TUint /*aRegisterIndex*/, TUint /*aRegisterValue*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidgetController1::GetWidgetRegister(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/, TUint /*aRegisterIndex*/, IInvocationResponseUint& /*aRegisterValue*/)
{
    ASSERTS();
}

