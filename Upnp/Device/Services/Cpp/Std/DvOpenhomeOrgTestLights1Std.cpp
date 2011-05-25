#include "DvOpenhomeOrgTestLights1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

DvProviderOpenhomeOrgTestLights1Cpp::DvProviderOpenhomeOrgTestLights1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestLights", 1)
{
    
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetCount()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCount");
    action->AddOutputParameter(new ParameterUint("Count"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetCount);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetRoom()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRoom");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("RoomName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetRoom);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetName");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetPosition()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPosition");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("X"));
    action->AddOutputParameter(new ParameterUint("Y"));
    action->AddOutputParameter(new ParameterUint("Z"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetPosition);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionSetColor()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddInputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetColor()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::EnableActionGetColorComponents()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorComponents");
    action->AddInputParameter(new ParameterUint("Color"));
    action->AddOutputParameter(new ParameterUint("Brightness"));
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1Cpp::DoGetColorComponents);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respCount;
    GetCount(aVersion, respCount);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCount(aInvocation, "Count");
    respWriterCount.Write(respCount);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    std::string respRoomName;
    GetRoom(aVersion, Index, respRoomName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterRoomName(aInvocation, "RoomName");
    Brn buf_RoomName((const TByte*)respRoomName.c_str(), (TUint)respRoomName.length());
    respWriterRoomName.Write(buf_RoomName);
    aInvocation.InvocationWriteStringEnd("RoomName");
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    std::string respFriendlyName;
    GetName(aVersion, Index, respFriendlyName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterFriendlyName(aInvocation, "FriendlyName");
    Brn buf_FriendlyName((const TByte*)respFriendlyName.c_str(), (TUint)respFriendlyName.length());
    respWriterFriendlyName.Write(buf_FriendlyName);
    aInvocation.InvocationWriteStringEnd("FriendlyName");
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetPosition(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    uint32_t respX;
    uint32_t respY;
    uint32_t respZ;
    GetPosition(aVersion, Index, respX, respY, respZ);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterX(aInvocation, "X");
    respWriterX.Write(respX);
    InvocationResponseUint respWriterY(aInvocation, "Y");
    respWriterY.Write(respY);
    InvocationResponseUint respWriterZ(aInvocation, "Z");
    respWriterZ.Write(respZ);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Index = aInvocation.InvocationReadUint("Index");
    uint32_t Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    SetColor(aVersion, Index, Color);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    uint32_t respColor;
    GetColor(aVersion, Index, respColor);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterColor(aInvocation, "Color");
    respWriterColor.Write(respColor);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::DoGetColorComponents(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    uint32_t respBrightness;
    uint32_t respRed;
    uint32_t respGreen;
    uint32_t respBlue;
    GetColorComponents(aVersion, Color, respBrightness, respRed, respGreen, respBlue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterBrightness(aInvocation, "Brightness");
    respWriterBrightness.Write(respBrightness);
    InvocationResponseUint respWriterRed(aInvocation, "Red");
    respWriterRed.Write(respRed);
    InvocationResponseUint respWriterGreen(aInvocation, "Green");
    respWriterGreen.Write(respGreen);
    InvocationResponseUint respWriterBlue(aInvocation, "Blue");
    respWriterBlue.Write(respBlue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetCount(uint32_t /*aVersion*/, uint32_t& /*aCount*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetRoom(uint32_t /*aVersion*/, uint32_t /*aIndex*/, std::string& /*aRoomName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetName(uint32_t /*aVersion*/, uint32_t /*aIndex*/, std::string& /*aFriendlyName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetPosition(uint32_t /*aVersion*/, uint32_t /*aIndex*/, uint32_t& /*aX*/, uint32_t& /*aY*/, uint32_t& /*aZ*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::SetColor(uint32_t /*aVersion*/, uint32_t /*aIndex*/, uint32_t /*aColor*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetColor(uint32_t /*aVersion*/, uint32_t /*aIndex*/, uint32_t& /*aColor*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestLights1Cpp::GetColorComponents(uint32_t /*aVersion*/, uint32_t /*aColor*/, uint32_t& /*aBrightness*/, uint32_t& /*aRed*/, uint32_t& /*aGreen*/, uint32_t& /*aBlue*/)
{
    ASSERTS();
}

