#include <Core/DvZappOrgTestWidgetController1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceZappOrgTestWidgetController1::DvServiceZappOrgTestWidgetController1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestWidgetController", 1)
{
    Functor empty;
}

void DvServiceZappOrgTestWidgetController1::EnableActionCreateWidget()
{
    Zapp::Action* action = new Zapp::Action("CreateWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestWidgetController1::DoCreateWidget);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestWidgetController1::EnableActionRemoveWidget()
{
    Zapp::Action* action = new Zapp::Action("RemoveWidget");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestWidgetController1::DoRemoveWidget);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestWidgetController1::EnableActionSetWidgetRegister()
{
    Zapp::Action* action = new Zapp::Action("SetWidgetRegister");
    action->AddInputParameter(new ParameterString("WidgetUdn"));
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestWidgetController1::DoSetWidgetRegister);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestWidgetController1::DoCreateWidget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    CreateWidget(resp, aVersion, WidgetUdn);
}

void DvServiceZappOrgTestWidgetController1::DoRemoveWidget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz WidgetUdn;
    aInvocation.InvocationReadString("WidgetUdn", WidgetUdn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    RemoveWidget(resp, aVersion, WidgetUdn);
}

void DvServiceZappOrgTestWidgetController1::DoSetWidgetRegister(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceZappOrgTestWidgetController1::CreateWidget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestWidgetController1::RemoveWidget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestWidgetController1::SetWidgetRegister(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aWidgetUdn*/, TUint /*aRegisterIndex*/, TUint /*aRegisterValue*/)
{
    ASSERTS();
}

