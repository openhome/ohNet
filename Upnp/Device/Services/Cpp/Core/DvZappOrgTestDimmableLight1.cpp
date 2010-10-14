#include <Core/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceZappOrgTestDimmableLight1::DvServiceZappOrgTestDimmableLight1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    Functor empty;
}

void DvServiceZappOrgTestDimmableLight1::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterUint("Level"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterUint("Level"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1::DoGetLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respLevel(aInvocation, "Level");
    GetLevel(resp, aVersion, respLevel);
}

void DvServiceZappOrgTestDimmableLight1::DoSetLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLevel(resp, aVersion, Level);
}

void DvServiceZappOrgTestDimmableLight1::GetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aLevel*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestDimmableLight1::SetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aLevel*/)
{
    ASSERTS();
}

