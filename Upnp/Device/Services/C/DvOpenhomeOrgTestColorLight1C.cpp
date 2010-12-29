#include "DvOpenhomeOrgTestColorLight1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderOpenhomeOrgTestColorLight1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgTestColorLight1C(DvDeviceC aDevice);
    void EnableActionGetName(CallbackTestColorLight1GetName aCallback, void* aPtr);
    void EnableActionSetColor(CallbackTestColorLight1SetColor aCallback, void* aPtr);
    void EnableActionGetColor(CallbackTestColorLight1GetColor aCallback, void* aPtr);
    void EnableActionGetMaxColors(CallbackTestColorLight1GetMaxColors aCallback, void* aPtr);
private:
    void DoGetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMaxColors(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTestColorLight1GetName iCallbackGetName;
    void* iPtrGetName;
    CallbackTestColorLight1SetColor iCallbackSetColor;
    void* iPtrSetColor;
    CallbackTestColorLight1GetColor iCallbackGetColor;
    void* iPtrGetColor;
    CallbackTestColorLight1GetMaxColors iCallbackGetMaxColors;
    void* iPtrGetMaxColors;
};

DvProviderOpenhomeOrgTestColorLight1C::DvProviderOpenhomeOrgTestColorLight1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "TestColorLight", 1)
{
    
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetName(CallbackTestColorLight1GetName aCallback, void* aPtr)
{
    iCallbackGetName = aCallback;
    iPtrGetName = aPtr;
    Zapp::Action* action = new Zapp::Action("GetName");
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1C::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionSetColor(CallbackTestColorLight1SetColor aCallback, void* aPtr)
{
    iCallbackSetColor = aCallback;
    iPtrSetColor = aPtr;
    Zapp::Action* action = new Zapp::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Red"));
    action->AddInputParameter(new ParameterUint("Green"));
    action->AddInputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1C::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetColor(CallbackTestColorLight1GetColor aCallback, void* aPtr)
{
    iCallbackGetColor = aCallback;
    iPtrGetColor = aPtr;
    Zapp::Action* action = new Zapp::Action("GetColor");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1C::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetMaxColors(CallbackTestColorLight1GetMaxColors aCallback, void* aPtr)
{
    iCallbackGetMaxColors = aCallback;
    iPtrGetMaxColors = aPtr;
    Zapp::Action* action = new Zapp::Action("GetMaxColors");
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestColorLight1C::DoGetMaxColors);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestColorLight1C::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* FriendlyName;
    ASSERT(iCallbackGetName != NULL);
    if (0 != iCallbackGetName(iPtrGetName, aVersion, &FriendlyName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    resp.Start();
    Brhz bufFriendlyName((const TChar*)FriendlyName);
    ZappFreeExternal(FriendlyName);
    respFriendlyName.Write(bufFriendlyName);
    respFriendlyName.WriteFlush();
    resp.End();
}

void DvProviderOpenhomeOrgTestColorLight1C::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Red = aInvocation.InvocationReadUint("Red");
    TUint Green = aInvocation.InvocationReadUint("Green");
    TUint Blue = aInvocation.InvocationReadUint("Blue");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, aVersion, Red, Green, Blue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderOpenhomeOrgTestColorLight1C::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetColor != NULL);
    if (0 != iCallbackGetColor(iPtrGetColor, aVersion, &Red, &Green, &Blue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    resp.Start();
    respRed.Write(Red);
    respGreen.Write(Green);
    respBlue.Write(Blue);
    resp.End();
}

void DvProviderOpenhomeOrgTestColorLight1C::DoGetMaxColors(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetMaxColors != NULL);
    if (0 != iCallbackGetMaxColors(iPtrGetMaxColors, aVersion, &Red, &Green, &Blue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    resp.Start();
    respRed.Write(Red);
    respGreen.Write(Green);
    respBlue.Write(Blue);
    resp.End();
}



THandle DvProviderOpenhomeOrgTestColorLight1Create(DvDeviceC aDevice)
{
	return new DvProviderOpenhomeOrgTestColorLight1C(aDevice);
}

void DvProviderOpenhomeOrgTestColorLight1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgTestColorLight1C*>(aProvider);
}

void DvProviderOpenhomeOrgTestColorLight1EnableActionGetName(THandle aProvider, CallbackTestColorLight1GetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestColorLight1C*>(aProvider)->EnableActionGetName(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestColorLight1EnableActionSetColor(THandle aProvider, CallbackTestColorLight1SetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestColorLight1C*>(aProvider)->EnableActionSetColor(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestColorLight1EnableActionGetColor(THandle aProvider, CallbackTestColorLight1GetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestColorLight1C*>(aProvider)->EnableActionGetColor(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestColorLight1EnableActionGetMaxColors(THandle aProvider, CallbackTestColorLight1GetMaxColors aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestColorLight1C*>(aProvider)->EnableActionGetMaxColors(aCallback, aPtr);
}

