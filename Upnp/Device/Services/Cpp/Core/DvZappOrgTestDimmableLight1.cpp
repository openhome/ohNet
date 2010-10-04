#include <Core/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceZappOrgTestDimmableLight1::SetPropertyA_ARG_Level(TUint aValue)
{
    SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvServiceZappOrgTestDimmableLight1::GetPropertyA_ARG_Level(TUint& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvServiceZappOrgTestDimmableLight1::DvServiceZappOrgTestDimmableLight1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    Functor empty;
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"), empty);
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvServiceZappOrgTestDimmableLight1::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestDimmableLight1::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestDimmableLight1::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
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

