#include <Core/DvZappOrgTestWidget1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderZappOrgTestWidget1::SetPropertyReadWriteRegister0(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister0, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadWriteRegister0(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister0->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadWriteRegister1(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister1, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadWriteRegister1(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister1->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadWriteRegister2(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister2, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadWriteRegister2(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister2->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadWriteRegister3(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister3, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadWriteRegister3(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister3->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadOnlyRegister4(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister4, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadOnlyRegister4(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister4->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadOnlyRegister5(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister5, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadOnlyRegister5(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister5->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadOnlyRegister6(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister6, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadOnlyRegister6(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister6->Value();
}

TBool DvProviderZappOrgTestWidget1::SetPropertyReadOnlyRegister7(TUint aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister7, aValue);
}

void DvProviderZappOrgTestWidget1::GetPropertyReadOnlyRegister7(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister7->Value();
}

DvProviderZappOrgTestWidget1::DvProviderZappOrgTestWidget1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestWidget", 1)
{
    
    iPropertyReadWriteRegister0 = new PropertyUint(new ParameterUint("ReadWriteRegister0"));
    iService->AddProperty(iPropertyReadWriteRegister0); // passes ownership
    iPropertyReadWriteRegister1 = new PropertyUint(new ParameterUint("ReadWriteRegister1"));
    iService->AddProperty(iPropertyReadWriteRegister1); // passes ownership
    iPropertyReadWriteRegister2 = new PropertyUint(new ParameterUint("ReadWriteRegister2"));
    iService->AddProperty(iPropertyReadWriteRegister2); // passes ownership
    iPropertyReadWriteRegister3 = new PropertyUint(new ParameterUint("ReadWriteRegister3"));
    iService->AddProperty(iPropertyReadWriteRegister3); // passes ownership
    iPropertyReadOnlyRegister4 = new PropertyUint(new ParameterUint("ReadOnlyRegister4"));
    iService->AddProperty(iPropertyReadOnlyRegister4); // passes ownership
    iPropertyReadOnlyRegister5 = new PropertyUint(new ParameterUint("ReadOnlyRegister5"));
    iService->AddProperty(iPropertyReadOnlyRegister5); // passes ownership
    iPropertyReadOnlyRegister6 = new PropertyUint(new ParameterUint("ReadOnlyRegister6"));
    iService->AddProperty(iPropertyReadOnlyRegister6); // passes ownership
    iPropertyReadOnlyRegister7 = new PropertyUint(new ParameterUint("ReadOnlyRegister7"));
    iService->AddProperty(iPropertyReadOnlyRegister7); // passes ownership
}

void DvProviderZappOrgTestWidget1::EnableActionSetReadWriteRegister()
{
    Zapp::Action* action = new Zapp::Action("SetReadWriteRegister");
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1::DoSetReadWriteRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1::EnableActionGetWidgetClass()
{
    Zapp::Action* action = new Zapp::Action("GetWidgetClass");
    action->AddOutputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1::DoGetWidgetClass);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1::DoSetReadWriteRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    TUint RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetReadWriteRegister(resp, aVersion, RegisterIndex, RegisterValue);
}

void DvProviderZappOrgTestWidget1::DoGetWidgetClass(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respWidgetClass(aInvocation, "WidgetClass");
    GetWidgetClass(resp, aVersion, respWidgetClass);
}

void DvProviderZappOrgTestWidget1::SetReadWriteRegister(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aRegisterIndex*/, TUint /*aRegisterValue*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidget1::GetWidgetClass(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aWidgetClass*/)
{
    ASSERTS();
}

