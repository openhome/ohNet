#include "DvOpenhomeOrgTestDimmableLight1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderOpenhomeOrgTestDimmableLight1::SetPropertyA_ARG_Level(TUint aValue)
{
    return SetPropertyUint(*iPropertyA_ARG_Level, aValue);
}

void DvProviderOpenhomeOrgTestDimmableLight1::GetPropertyA_ARG_Level(TUint& aValue)
{
    aValue = iPropertyA_ARG_Level->Value();
}

DvProviderOpenhomeOrgTestDimmableLight1::DvProviderOpenhomeOrgTestDimmableLight1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestDimmableLight", 1)
{
    
    iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
    iService->AddProperty(iPropertyA_ARG_Level); // passes ownership
}

void DvProviderOpenhomeOrgTestDimmableLight1::EnableActionGetLevel()
{
    Zapp::Action* action = new Zapp::Action("GetLevel");
    action->AddOutputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1::DoGetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1::EnableActionSetLevel()
{
    Zapp::Action* action = new Zapp::Action("SetLevel");
    action->AddInputParameter(new ParameterRelated("Level", *iPropertyA_ARG_Level));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestDimmableLight1::DoSetLevel);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestDimmableLight1::DoGetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respLevel(aInvocation, "Level");
    GetLevel(resp, aVersion, respLevel);
}

void DvProviderOpenhomeOrgTestDimmableLight1::DoSetLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Level = aInvocation.InvocationReadUint("Level");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLevel(resp, aVersion, Level);
}

void DvProviderOpenhomeOrgTestDimmableLight1::GetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aLevel*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestDimmableLight1::SetLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aLevel*/)
{
    ASSERTS();
}

