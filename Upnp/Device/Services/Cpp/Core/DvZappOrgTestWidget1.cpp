#include <Core/DvZappOrgTestWidget1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceZappOrgTestWidget1::SetPropertyReadWriteRegister0(TUint aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister0, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadWriteRegister0(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister0->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadWriteRegister1(TUint aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister1, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadWriteRegister1(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister1->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadWriteRegister2(TUint aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister2, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadWriteRegister2(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister2->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadWriteRegister3(TUint aValue)
{
    SetPropertyUint(*iPropertyReadWriteRegister3, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadWriteRegister3(TUint& aValue)
{
    aValue = iPropertyReadWriteRegister3->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadOnlyRegister4(TUint aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister4, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadOnlyRegister4(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister4->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadOnlyRegister5(TUint aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister5, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadOnlyRegister5(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister5->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadOnlyRegister6(TUint aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister6, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadOnlyRegister6(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister6->Value();
}

void DvServiceZappOrgTestWidget1::SetPropertyReadOnlyRegister7(TUint aValue)
{
    SetPropertyUint(*iPropertyReadOnlyRegister7, aValue);
}

void DvServiceZappOrgTestWidget1::GetPropertyReadOnlyRegister7(TUint& aValue)
{
    aValue = iPropertyReadOnlyRegister7->Value();
}

DvServiceZappOrgTestWidget1::DvServiceZappOrgTestWidget1(DvDevice& aDevice)
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

void DvServiceZappOrgTestWidget1::EnableActionSetReadWriteRegister()
{
    Zapp::Action* action = new Zapp::Action("SetReadWriteRegister");
    action->AddInputParameter(new ParameterUint("RegisterIndex"));
    action->AddInputParameter(new ParameterUint("RegisterValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestWidget1::DoSetReadWriteRegister);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestWidget1::DoSetReadWriteRegister(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint RegisterIndex = aInvocation.InvocationReadUint("RegisterIndex");
    TUint RegisterValue = aInvocation.InvocationReadUint("RegisterValue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetReadWriteRegister(resp, aVersion, RegisterIndex, RegisterValue);
}

void DvServiceZappOrgTestWidget1::SetReadWriteRegister(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aRegisterIndex*/, TUint /*aRegisterValue*/)
{
    ASSERTS();
}

