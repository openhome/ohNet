#include "DvOpenhomeOrgTestLights1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderOpenhomeOrgTestLights1::DvProviderOpenhomeOrgTestLights1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestLights", 1)
{
    
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetCount()
{
    Zapp::Action* action = new Zapp::Action("GetCount");
    action->AddOutputParameter(new ParameterUint("Count"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetCount);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetRoom()
{
    Zapp::Action* action = new Zapp::Action("GetRoom");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("RoomName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetRoom);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetName()
{
    Zapp::Action* action = new Zapp::Action("GetName");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetPosition()
{
    Zapp::Action* action = new Zapp::Action("GetPosition");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("X"));
    action->AddOutputParameter(new ParameterUint("Y"));
    action->AddOutputParameter(new ParameterUint("Z"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetPosition);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionSetColor()
{
    Zapp::Action* action = new Zapp::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddInputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetColor()
{
    Zapp::Action* action = new Zapp::Action("GetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::EnableActionGetColorComponents()
{
    Zapp::Action* action = new Zapp::Action("GetColorComponents");
    action->AddInputParameter(new ParameterUint("Color"));
    action->AddOutputParameter(new ParameterUint("Brightness"));
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1::DoGetColorComponents);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1::DoGetCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCount(aInvocation, "Count");
    GetCount(resp, aVersion, respCount);
}

void DvProviderOpenhomeOrgTestLights1::DoGetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respRoomName(aInvocation, "RoomName");
    GetRoom(resp, aVersion, Index, respRoomName);
}

void DvProviderOpenhomeOrgTestLights1::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    GetName(resp, aVersion, Index, respFriendlyName);
}

void DvProviderOpenhomeOrgTestLights1::DoGetPosition(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respX(aInvocation, "X");
    InvocationResponseUint respY(aInvocation, "Y");
    InvocationResponseUint respZ(aInvocation, "Z");
    GetPosition(resp, aVersion, Index, respX, respY, respZ);
}

void DvProviderOpenhomeOrgTestLights1::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColor(resp, aVersion, Index, Color);
}

void DvProviderOpenhomeOrgTestLights1::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respColor(aInvocation, "Color");
    GetColor(resp, aVersion, Index, respColor);
}

void DvProviderOpenhomeOrgTestLights1::DoGetColorComponents(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respBrightness(aInvocation, "Brightness");
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    GetColorComponents(resp, aVersion, Color, respBrightness, respRed, respGreen, respBlue);
}

void DvProviderOpenhomeOrgTestLights1::GetCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aCount*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::GetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseString& /*aRoomName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::GetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseString& /*aFriendlyName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::GetPosition(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseUint& /*aX*/, IInvocationResponseUint& /*aY*/, IInvocationResponseUint& /*aZ*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::SetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, TUint /*aColor*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::GetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseUint& /*aColor*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1::GetColorComponents(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aColor*/, IInvocationResponseUint& /*aBrightness*/, IInvocationResponseUint& /*aRed*/, IInvocationResponseUint& /*aGreen*/, IInvocationResponseUint& /*aBlue*/)
{
    ASSERTS();
}

