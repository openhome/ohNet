#include <Core/DvZappOrgTestLights1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

DvServiceZappOrgTestLights1::DvServiceZappOrgTestLights1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "zapp.org", "TestLights", 1)
{
    Functor empty;
}

void DvServiceZappOrgTestLights1::EnableActionGetCount()
{
    Zapp::Action* action = new Zapp::Action("GetCount");
    action->AddOutputParameter(new ParameterUint("Count"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetCount);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionGetRoom()
{
    Zapp::Action* action = new Zapp::Action("GetRoom");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("RoomName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetRoom);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionGetName()
{
    Zapp::Action* action = new Zapp::Action("GetName");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetName);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionGetPosition()
{
    Zapp::Action* action = new Zapp::Action("GetPosition");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("X"));
    action->AddOutputParameter(new ParameterUint("Y"));
    action->AddOutputParameter(new ParameterUint("Z"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetPosition);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionSetColor()
{
    Zapp::Action* action = new Zapp::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddInputParameter(new ParameterUint("Color"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoSetColor);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionGetColor()
{
    Zapp::Action* action = new Zapp::Action("GetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("Color"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetColor);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::EnableActionGetColorComponents()
{
    Zapp::Action* action = new Zapp::Action("GetColorComponents");
    action->AddInputParameter(new ParameterUint("Color"));
    action->AddOutputParameter(new ParameterUint("Brightness"));
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceZappOrgTestLights1::DoGetColorComponents);
    iService->AddAction(action, functor);
}

void DvServiceZappOrgTestLights1::DoGetCount(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCount(aInvocation, "Count");
    GetCount(resp, aVersion, respCount);
}

void DvServiceZappOrgTestLights1::DoGetRoom(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respRoomName(aInvocation, "RoomName");
    GetRoom(resp, aVersion, Index, respRoomName);
}

void DvServiceZappOrgTestLights1::DoGetName(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    GetName(resp, aVersion, Index, respFriendlyName);
}

void DvServiceZappOrgTestLights1::DoGetPosition(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceZappOrgTestLights1::DoSetColor(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColor(resp, aVersion, Index, Color);
}

void DvServiceZappOrgTestLights1::DoGetColor(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respColor(aInvocation, "Color");
    GetColor(resp, aVersion, Index, respColor);
}

void DvServiceZappOrgTestLights1::DoGetColorComponents(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceZappOrgTestLights1::GetCount(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aCount*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::GetRoom(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseString& /*aRoomName*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::GetName(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseString& /*aFriendlyName*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::GetPosition(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseUint& /*aX*/, IInvocationResponseUint& /*aY*/, IInvocationResponseUint& /*aZ*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::SetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, TUint /*aColor*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::GetColor(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aIndex*/, IInvocationResponseUint& /*aColor*/)
{
    ASSERTS();
}

void DvServiceZappOrgTestLights1::GetColorComponents(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aColor*/, IInvocationResponseUint& /*aBrightness*/, IInvocationResponseUint& /*aRed*/, IInvocationResponseUint& /*aGreen*/, IInvocationResponseUint& /*aBlue*/)
{
    ASSERTS();
}

