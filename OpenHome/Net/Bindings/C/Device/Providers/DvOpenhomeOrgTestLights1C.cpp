#include "DvOpenhomeOrgTestLights1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
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
    void DoGetCount(IDviInvocation& aInvocation);
    void DoGetRoom(IDviInvocation& aInvocation);
    void DoGetName(IDviInvocation& aInvocation);
    void DoGetPosition(IDviInvocation& aInvocation);
    void DoSetColor(IDviInvocation& aInvocation);
    void DoGetColor(IDviInvocation& aInvocation);
    void DoGetColorComponents(IDviInvocation& aInvocation);
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

void DvProviderOpenhomeOrgTestLights1C::DoGetCount(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Count;
    ASSERT(iCallbackGetCount != NULL);
    if (0 != iCallbackGetCount(iPtrGetCount, invocationC, invocationCPtr, &Count)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCount(aInvocation, "Count");
    invocation.StartResponse();
    respCount.Write(Count);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetRoom(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* RoomName;
    ASSERT(iCallbackGetRoom != NULL);
    if (0 != iCallbackGetRoom(iPtrGetRoom, invocationC, invocationCPtr, Index, &RoomName)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respRoomName(aInvocation, "RoomName");
    invocation.StartResponse();
    Brhz bufRoomName((const TChar*)RoomName);
    OhNetFreeExternal(RoomName);
    respRoomName.Write(bufRoomName);
    respRoomName.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetName(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* FriendlyName;
    ASSERT(iCallbackGetName != NULL);
    if (0 != iCallbackGetName(iPtrGetName, invocationC, invocationCPtr, Index, &FriendlyName)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respFriendlyName(aInvocation, "FriendlyName");
    invocation.StartResponse();
    Brhz bufFriendlyName((const TChar*)FriendlyName);
    OhNetFreeExternal(FriendlyName);
    respFriendlyName.Write(bufFriendlyName);
    respFriendlyName.WriteFlush();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetPosition(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t X;
    uint32_t Y;
    uint32_t Z;
    ASSERT(iCallbackGetPosition != NULL);
    if (0 != iCallbackGetPosition(iPtrGetPosition, invocationC, invocationCPtr, Index, &X, &Y, &Z)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respX(aInvocation, "X");
    DviInvocationResponseUint respY(aInvocation, "Y");
    DviInvocationResponseUint respZ(aInvocation, "Z");
    invocation.StartResponse();
    respX.Write(X);
    respY.Write(Y);
    respZ.Write(Z);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoSetColor(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, invocationC, invocationCPtr, Index, Color)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetColor(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Index = aInvocation.InvocationReadUint("Index");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Color;
    ASSERT(iCallbackGetColor != NULL);
    if (0 != iCallbackGetColor(iPtrGetColor, invocationC, invocationCPtr, Index, &Color)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respColor(aInvocation, "Color");
    invocation.StartResponse();
    respColor.Write(Color);
    invocation.EndResponse();
}

void DvProviderOpenhomeOrgTestLights1C::DoGetColorComponents(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Color = aInvocation.InvocationReadUint("Color");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Brightness;
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetColorComponents != NULL);
    if (0 != iCallbackGetColorComponents(iPtrGetColorComponents, invocationC, invocationCPtr, Color, &Brightness, &Red, &Green, &Blue)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respBrightness(aInvocation, "Brightness");
    DviInvocationResponseUint respRed(aInvocation, "Red");
    DviInvocationResponseUint respGreen(aInvocation, "Green");
    DviInvocationResponseUint respBlue(aInvocation, "Blue");
    invocation.StartResponse();
    respBrightness.Write(Brightness);
    respRed.Write(Red);
    respGreen.Write(Green);
    respBlue.Write(Blue);
    invocation.EndResponse();
}



THandle STDCALL DvProviderOpenhomeOrgTestLights1Create(DvDeviceC aDevice)
{
    return new DvProviderOpenhomeOrgTestLights1C(aDevice);
}

void STDCALL DvProviderOpenhomeOrgTestLights1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetCount(THandle aProvider, CallbackTestLights1GetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetCount(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetRoom(THandle aProvider, CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetRoom(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetName(THandle aProvider, CallbackTestLights1GetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetName(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetPosition(THandle aProvider, CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetPosition(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionSetColor(THandle aProvider, CallbackTestLights1SetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionSetColor(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetColor(THandle aProvider, CallbackTestLights1GetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetColor(aCallback, aPtr);
}

void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetColorComponents(THandle aProvider, CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderOpenhomeOrgTestLights1C*>(aProvider)->EnableActionGetColorComponents(aCallback, aPtr);
}

