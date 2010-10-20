#include <Std/DvZappOrgTestWidget1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister0(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister0, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister0(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister0->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister1(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister1, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister1(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister1->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister2(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister2, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister2(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister2->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadWriteRegister3(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister3, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadWriteRegister3(uint32_t& aValue)
{
    aValue = iPropertyReadWriteRegister3->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister4(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister4, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister4(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister4->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister5(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister5, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister5(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister5->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister6(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister6, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister6(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister6->Value();
}

void DvServiceZappOrgTestWidget1Cpp::SetPropertyReadOnlyRegister7(uint32_t aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister7, aValue);
}

void DvServiceZappOrgTestWidget1Cpp::GetPropertyReadOnlyRegister7(uint32_t& aValue)
{
    aValue = iPropertyReadOnlyRegister7->Value();
}

DvServiceZappOrgTestWidget1Cpp::DvServiceZappOrgTestWidget1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestWidget", 1)
{
    Functor empty;
    iPropertyReadWriteRegister0 = new PropertyUint(new ParameterUint("ReadWriteRegister0"), empty);
    iService->AddProperty(iPropertyReadWriteRegister0); // passes ownership
    iPropertyReadWriteRegister1 = new PropertyUint(new ParameterUint("ReadWriteRegister1"), empty);
    iService->AddProperty(iPropertyReadWriteRegister1); // passes ownership
    iPropertyReadWriteRegister2 = new PropertyUint(new ParameterUint("ReadWriteRegister2"), empty);
    iService->AddProperty(iPropertyReadWriteRegister2); // passes ownership
    iPropertyReadWriteRegister3 = new PropertyUint(new ParameterUint("ReadWriteRegister3"), empty);
    iService->AddProperty(iPropertyReadWriteRegister3); // passes ownership
    iPropertyReadOnlyRegister4 = new PropertyUint(new ParameterUint("ReadOnlyRegister4"), empty);
    iService->AddProperty(iPropertyReadOnlyRegister4); // passes ownership
    iPropertyReadOnlyRegister5 = new PropertyUint(new ParameterUint("ReadOnlyRegister5"), empty);
    iService->AddProperty(iPropertyReadOnlyRegister5); // passes ownership
    iPropertyReadOnlyRegister6 = new PropertyUint(new ParameterUint("ReadOnlyRegister6"), empty);
    iService->AddProperty(iPropertyReadOnlyRegister6); // passes ownership
    iPropertyReadOnlyRegister7 = new PropertyUint(new ParameterUint("ReadOnlyRegister7"), empty);
    iService->AddProperty(iPropertyReadOnlyRegister7); // passes ownership
}

void DvServiceZappOrgTestWidget1Cpp::EnableActionSetReadWriteRegister()
{
    Zapp::Action* action = new Zapp::Action("SetReadWriteRegister");
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestWidget1Cpp::DoSetReadWriteRegister);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestWidget1Cpp::DoSetReadWriteRegister(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    uint32_t RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    SetReadWriteRegister(aVersion, RegisterIndex, RegisterValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceZappOrgTestWidget1Cpp::SetReadWriteRegister(uint32_t /*aVersion*/, uint32_t /*aRegisterIndex*/, uint32_t /*aRegisterValue*/)
{
    ASSERTS();
}

