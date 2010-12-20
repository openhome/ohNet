#include <Std/DvOpenhomeOrgTestColorLight1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

DvProviderOpenhomeOrgTestColorLight1Cpp::DvProviderOpenhomeOrgTestColorLight1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "openhome.org", "TestColorLight", 1)
{
    
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::EnableActionGetName()
{
    Zapp::Action* action = new Zapp::Action("GetName");
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::EnableActionSetColor()
{
    Zapp::Action* action = new Zapp::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Red"));
    action->AddInputParameter(new ParameterUint("Green"));
    action->AddInputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1Cpp::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::EnableActionGetColor()
{
    Zapp::Action* action = new Zapp::Action("GetColor");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::EnableActionGetMaxColors()
{
    Zapp::Action* action = new Zapp::Action("GetMaxColors");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetMaxColors);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respFriendlyName;
    GetName(aVersion, respFriendlyName);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterFriendlyName(aInvocation, "FriendlyName");
    Brn buf_FriendlyName((const TByte*)respFriendlyName.c_str(), (TUint)respFriendlyName.length());
    respWriterFriendlyName.Write(buf_FriendlyName);
    aInvocation.InvocationWriteStringEnd("FriendlyName");
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Red = aInvocation.InvocationReadUint("Red");
    uint32_t Green = aInvocation.InvocationReadUint("Green");
    uint32_t Blue = aInvocation.InvocationReadUint("Blue");
    aInvocation.InvocationReadEnd();
    SetColor(aVersion, Red, Green, Blue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respRed;
    uint32_t respGreen;
    uint32_t respBlue;
    GetColor(aVersion, respRed, respGreen, respBlue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterRed(aInvocation, "Red");
    respWriterRed.Write(respRed);
    InvocationResponseUint respWriterGreen(aInvocation, "Green");
    respWriterGreen.Write(respGreen);
    InvocationResponseUint respWriterBlue(aInvocation, "Blue");
    respWriterBlue.Write(respBlue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::DoGetMaxColors(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respRed;
    uint32_t respGreen;
    uint32_t respBlue;
    GetMaxColors(aVersion, respRed, respGreen, respBlue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterRed(aInvocation, "Red");
    respWriterRed.Write(respRed);
    InvocationResponseUint respWriterGreen(aInvocation, "Green");
    respWriterGreen.Write(respGreen);
    InvocationResponseUint respWriterBlue(aInvocation, "Blue");
    respWriterBlue.Write(respBlue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::GetName(uint32_t /*aVersion*/, std::string& /*aFriendlyName*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::SetColor(uint32_t /*aVersion*/, uint32_t /*aRed*/, uint32_t /*aGreen*/, uint32_t /*aBlue*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::GetColor(uint32_t /*aVersion*/, uint32_t& /*aRed*/, uint32_t& /*aGreen*/, uint32_t& /*aBlue*/)
{
    ASSERTS();
}

void DvProviderOpenhomeOrgTestColorLight1Cpp::GetMaxColors(uint32_t /*aVersion*/, uint32_t& /*aRed*/, uint32_t& /*aGreen*/, uint32_t& /*aBlue*/)
{
    ASSERTS();
}

