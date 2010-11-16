#include <Core/DvZappOrgTestDimmableLight1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderZappOrgTestDimmableLight1::SetPropertyA_ARG_Level(TUint aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderZappOrgTestDimmableLight1::GetPropertyA_ARG_Level(TUint& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvProviderZappOrgTestDimmableLight1::DvProviderZappOrgTestDimmableLight1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "zapp.org", "TestDimmableLight", 1)
{
    Functor empty;
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"), empty);
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvProviderZappOrgTestDimmableLight1::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderZappOrgTestDimmableLight1::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderZappOrgTestDimmableLight1::DoGetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respLevel(aInvocation, "Level");
    GetLevel(resp, aVersion, respLevel);
}

void DvProviderZappOrgTestDimmableLight1::DoSetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLevel(resp, aVersion, Level);
}

void DvProviderZappOrgTestDimmableLight1::GetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aLevel*/)
{
    ASSERTS();
}

void DvProviderZappOrgTestDimmableLight1::SetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aLevel*/)
{
    ASSERTS();
}

