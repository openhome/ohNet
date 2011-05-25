#include "DvOpenhomeOrgTestLights1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderOpenhomeOrgTestLights1C : public DvProvider
{
public:
    DvProviderOpenhomeOrgTestLights1C(DvDeviceC aDevice);
    void EnableActionGetCount(CallbackTestLights1GetCount aCallback, void* aPtr);
    void EnableActionGetRoom(CallbackTestLights1GetRoom aCallback, void* aPtr);
    void EnableActionGetName(CallbackTestLights1GetName aCallback, void* aPtr);
    void EnableActionGetPosition(CallbackTestLights1GetPosition aCallback, void* aPtr);
    void EnableActionSetColor(CallbackTestLights1SetColor aCallback, void* aPtr);
    void EnableActionGetColor(CallbackTestLights1GetColor aCallback, void* aPtr);
    void EnableActionGetColorComponents(CallbackTestLights1GetColorComponents aCallback, void* aPtr);
private:
    void DoGetCount(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPosition(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColorComponents(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackTestLights1GetCount iCallbackGetCount;
    void* iPtrGetCount;
    CallbackTestLights1GetRoom iCallbackGetRoom;
    void* iPtrGetRoom;
    CallbackTestLights1GetName iCallbackGetName;
    void* iPtrGetName;
    CallbackTestLights1GetPosition iCallbackGetPosition;
    void* iPtrGetPosition;
    CallbackTestLights1SetColor iCallbackSetColor;
    void* iPtrSetColor;
    CallbackTestLights1GetColor iCallbackGetColor;
    void* iPtrGetColor;
    CallbackTestLights1GetColorComponents iCallbackGetColorComponents;
    void* iPtrGetColorComponents;
};

DvProviderOpenhomeOrgTestLights1C::DvProviderOpenhomeOrgTestLights1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "openhome.org", "TestLights", 1)
{
    
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetCount(CallbackTestLights1GetCount aCallback, void* aPtr)
{
    iCallbackGetCount = aCallback;
    iPtrGetCount = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetCount");
    action->AddOutputParameter(new ParameterUint("Count"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetCount);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetRoom(CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    iCallbackGetRoom = aCallback;
    iPtrGetRoom = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRoom");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("RoomName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetRoom);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetName(CallbackTestLights1GetName aCallback, void* aPtr)
{
    iCallbackGetName = aCallback;
    iPtrGetName = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetName");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterString("FriendlyName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetName);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetPosition(CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    iCallbackGetPosition = aCallback;
    iPtrGetPosition = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPosition");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("X"));
    action->AddOutputParameter(new ParameterUint("Y"));
    action->AddOutputParameter(new ParameterUint("Z"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetPosition);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionSetColor(CallbackTestLights1SetColor aCallback, void* aPtr)
{
    iCallbackSetColor = aCallback;
    iPtrSetColor = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddInputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoSetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetColor(CallbackTestLights1GetColor aCallback, void* aPtr)
{
    iCallbackGetColor = aCallback;
    iPtrGetColor = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColor");
    action->AddInputParameter(new ParameterUint("Index"));
    action->AddOutputParameter(new ParameterUint("Color"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetColor);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::EnableActionGetColorComponents(CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    iCallbackGetColorComponents = aCallback;
    iPtrGetColorComponents = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorComponents");
    action->AddInputParameter(new ParameterUint("Color"));
    action->AddOutputParameter(new ParameterUint("Brightness"));
    action->AddOutputParameter(new ParameterUint("Red"));
    action->AddOutputParameter(new ParameterUint("Green"));
    action->AddOutputParameter(new ParameterUint("Blue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderOpenhomeOrgTestLights1C::DoGetColorComponents);
    iService->AddAction(action, functor);
}

void DvProviderOpenhomeOrgTestLights1C::DoGetCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Count;
    ASSERT(iCallbackGetCount != NULL);
    if (0 != iCallbackGetCount(iPtrGetCount, aVersion, &Count)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCount(aInvocation, "Count");
    resp.Start();
    respCount.Write(Count);
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetRoom(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* RoomName;
    ASSERT(iCallbackGetRoom != NULL);
    if (0 != iCallbackGetRoom(iPtrGetRoom, aVersion, Index, &RoomName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respRoomName(aInvocation, "RoomName");
    resp.Start();
    Brhz bufRoomName((const TChar*)RoomName);
    OhNetFreeExternal(RoomName);
    respRoomName.Write(bufRoomName);
    respRoomName.WriteFlush();
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* FriendlyName;
    ASSERT(iCallbackGetName != NULL);
    if (0 != iCallbackGetName(iPtrGetName, aVersion, Index, &FriendlyName)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    resp.Start();
    Brhz bufFriendlyName((const TChar*)FriendlyName);
    OhNetFreeExternal(FriendlyName);
    respFriendlyName.Write(bufFriendlyName);
    respFriendlyName.WriteFlush();
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetPosition(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t X;
    uint32_t Y;
    uint32_t Z;
    ASSERT(iCallbackGetPosition != NULL);
    if (0 != iCallbackGetPosition(iPtrGetPosition, aVersion, Index, &X, &Y, &Z)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respX(aInvocation, "X");
    InvocationResponseUint respY(aInvocation, "Y");
    InvocationResponseUint respZ(aInvocation, "Z");
    resp.Start();
    respX.Write(X);
    respY.Write(Y);
    respZ.Write(Z);
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoSetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, aVersion, Index, Color)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetColor(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Color;
    ASSERT(iCallbackGetColor != NULL);
    if (0 != iCallbackGetColor(iPtrGetColor, aVersion, Index, &Color)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respColor(aInvocation, "Color");
    resp.Start();
    respColor.Write(Color);
    resp.End();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetColorComponents(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Brightness;
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetColorComponents != NULL);
    if (0 != iCallbackGetColorComponents(iPtrGetColorComponents, aVersion, Color, &Brightness, &Red, &Green, &Blue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respBrightness(aInvocation, "Brightness");
    InvocationResponseUint respRed(aInvocation, "Red");
    InvocationResponseUint respGreen(aInvocation, "Green");
    InvocationResponseUint respBlue(aInvocation, "Blue");
    resp.Start();
    respBrightness.Write(Brightness);
    respRed.Write(Red);
    respGreen.Write(Green);
    respBlue.Write(Blue);
    resp.End();
}



THandle DvProviderOpenhomeOrgTestLights1Create(DvDeviceC aDevice)
{
	return new DvProviderOpenhomeOrgTestLights1C(aDevice);
}

void DvProviderOpenhomeOrgTestLights1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetCount(THandle aProvider, CallbackTestLights1GetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetCount(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetRoom(THandle aProvider, CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetRoom(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetName(THandle aProvider, CallbackTestLights1GetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetName(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetPosition(THandle aProvider, CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetPosition(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionSetColor(THandle aProvider, CallbackTestLights1SetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionSetColor(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetColor(THandle aProvider, CallbackTestLights1GetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetColor(aCallback, aPtr);
}

void DvProviderOpenhomeOrgTestLights1EnableActionGetColorComponents(THandle aProvider, CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetColorComponents(aCallback, aPtr);
}

