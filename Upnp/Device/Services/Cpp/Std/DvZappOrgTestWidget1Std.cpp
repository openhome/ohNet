#include <Std/DvZappOrgTestWidget1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister0(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister0, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister0(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister0->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister1(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister1, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister1(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister1->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister2(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister2, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister2(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister2->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister3(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadWriteRegister3, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister3(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister3->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister4(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister4, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister4(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister4->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister5(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister5, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister5(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister5->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister6(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister6, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister6(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister6->Value();
}

bool DvProviderZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister7(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyReadOnlyRegister7, aValue);
}

void DvProviderZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister7(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister7->Value();
}

DvProviderZappOrgTestWidget1Cpp::DvProviderZappOrgTestWidget1Cpp(DvDeviceStd& aDevice)
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

void DvProviderZappOrgTestWidget1Cpp::EnableActionSetReadWriteRegister()
{
    Zapp::Action* action = new Zapp::Action("SetReadWriteRegister");
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1Cpp::DoSetReadWriteRegister);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1Cpp::EnableActionGetWidgetClass()
{
    Zapp::Action* action = new Zapp::Action("GetWidgetClass");
    action->AddOutputParameter(new ParameterUint("WidgetClass"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestWidget1Cpp::DoGetWidgetClass);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestWidget1Cpp::DoSetReadWriteRegister(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    uint32_t RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    SetReadWriteRegister(aVersion, RegisterIndex, RegisterValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidget1Cpp::DoGetWidgetClass(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respWidgetClass;
    GetWidgetClass(aVersion, respWidgetClass);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterWidgetClass(aInvocation, "WidgetClass");
    respWriterWidgetClass.Write(respWidgetClass);
	aInvocation.InvocationWriteEnd();
}

void DvProviderZappOrgTestWidget1Cpp::SetReadWriteRegister(uint32_t /*aVersion*/, uint32_t /*aRegisterIndex*/, uint32_t /*aRegisterValue*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestWidget1Cpp::GetWidgetClass(uint32_t /*aVersion*/, uint32_t& /*aWidgetClass*/)
{
    ASSERTS();
}

