#include <Core/DvOpenhomeOrgTestColorLight1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderOpenhomeOrgTestColorLight1::DvProviderOpenhomeOrgTestColorLight1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestColorLight", 1)
{
    
}

void DvProviderOpenhomeOrgTestColorLight1::EnableActionGetName()
{
    Zapp::Action* action = new Zapp::Action("GetName");
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1::EnableActionSetColor()
{
    Zapp::Action* action = new Zapp::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Red"));
    action->AddInputParameter(new ParameterUint("Green"));
    action->AddInputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1::EnableActionGetColor()
{
    Zapp::Action* action = new Zapp::Action("GetColor");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1::EnableActionGetMaxColors()
{
    Zapp::Action* action = new Zapp::Action("GetMaxColors");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1::DoGetMaxColors);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    GetName(resp, aVersion, respFriendlyName);
}

void DvProviderOpenhomeOrgTestColorLight1::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Red = aInvocation.InvocationReadUint("Red");
    TUint Green = aInvocation.InvocationReadUint("Green");
    TUint Blue = aInvocation.InvocationReadUint("Blue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColor(resp, aVersion, Red, Green, Blue);
}

void DvProviderOpenhomeOrgTestColorLight1::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    GetColor(resp, aVersion, respRed, respGreen, respBlue);
}

void DvProviderOpenhomeOrgTestColorLight1::DoGetMaxColors(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    GetMaxColors(resp, aVersion, respRed, respGreen, respBlue);
}

void DvProviderOpenhomeOrgTestColorLight1::GetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aFriendlyName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1::SetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aRed*/, TUint /*aGreen*/, TUint /*aBlue*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1::GetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aRed*/, IInvocationResponseUint& /*aGreen*/, IInvocationResponseUint& /*aBlue*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1::GetMaxColors(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aRed*/, IInvocationResponseUint& /*aGreen*/, IInvocationResponseUint& /*aBlue*/)
{
    ASSERTS();
}

