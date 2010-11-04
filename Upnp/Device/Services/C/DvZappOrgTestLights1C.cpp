#include <C/DvZappOrgTestLights1.h>
#include <Core/DvZappOrgTestLights1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderZappOrgTestLights1C : public DvProviderZappOrgTestLights1
{
public:
    DvProviderZappOrgTestLights1C(DvDevice& aDevice);
    void EnableActionGetCount(CallbackTestLights1GetCount aCallback, void* aPtr);
    void EnableActionGetRoom(CallbackTestLights1GetRoom aCallback, void* aPtr);
    void EnableActionGetName(CallbackTestLights1GetName aCallback, void* aPtr);
    void EnableActionGetPosition(CallbackTestLights1GetPosition aCallback, void* aPtr);
    void EnableActionSetColor(CallbackTestLights1SetColor aCallback, void* aPtr);
    void EnableActionGetColor(CallbackTestLights1GetColor aCallback, void* aPtr);
    void EnableActionGetColorComponents(CallbackTestLights1GetColorComponents aCallback, void* aPtr);
private:
    void GetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aCount);
    void GetRoom(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aRoomName);
    void GetName(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aFriendlyName);
    void GetPosition(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aX, IInvocationResponseUint& aY, IInvocationResponseUint& aZ);
    void SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, TUint aColor);
    void GetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aColor);
    void GetColorComponents(IInvocationResponse& aResponse, TUint aVersion, TUint aColor, IInvocationResponseUint& aBrightness, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
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

DvProviderZappOrgTestLights1C::DvProviderZappOrgTestLights1C(DvDevice& aDevice)
    : DvProviderZappOrgTestLights1(aDevice)
{
}

void DvProviderZappOrgTestLights1C::EnableActionGetCount(CallbackTestLights1GetCount aCallback, void* aPtr)
{
    iCallbackGetCount = aCallback;
    iPtrGetCount = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetCount();
}

void DvProviderZappOrgTestLights1C::EnableActionGetRoom(CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    iCallbackGetRoom = aCallback;
    iPtrGetRoom = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetRoom();
}

void DvProviderZappOrgTestLights1C::EnableActionGetName(CallbackTestLights1GetName aCallback, void* aPtr)
{
    iCallbackGetName = aCallback;
    iPtrGetName = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetName();
}

void DvProviderZappOrgTestLights1C::EnableActionGetPosition(CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    iCallbackGetPosition = aCallback;
    iPtrGetPosition = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetPosition();
}

void DvProviderZappOrgTestLights1C::EnableActionSetColor(CallbackTestLights1SetColor aCallback, void* aPtr)
{
    iCallbackSetColor = aCallback;
    iPtrSetColor = aPtr;
    DvProviderZappOrgTestLights1::EnableActionSetColor();
}

void DvProviderZappOrgTestLights1C::EnableActionGetColor(CallbackTestLights1GetColor aCallback, void* aPtr)
{
    iCallbackGetColor = aCallback;
    iPtrGetColor = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetColor();
}

void DvProviderZappOrgTestLights1C::EnableActionGetColorComponents(CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    iCallbackGetColorComponents = aCallback;
    iPtrGetColorComponents = aPtr;
    DvProviderZappOrgTestLights1::EnableActionGetColorComponents();
}

void DvProviderZappOrgTestLights1C::GetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aCount)
{
    uint32_t Count;
    ASSERT(iCallbackGetCount != NULL);
    if (0 != iCallbackGetCount(iPtrGetCount, aVersion, &Count)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCount.Write(Count);
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::GetRoom(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aRoomName)
{
    char* RoomName;
    ASSERT(iCallbackGetRoom != NULL);
    if (0 != iCallbackGetRoom(iPtrGetRoom, aVersion, aIndex, &RoomName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufRoomName((const TChar*)RoomName);
    ZappFreeExternal(RoomName);
    aRoomName.Write(bufRoomName);
    aRoomName.WriteFlush();
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::GetName(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aFriendlyName)
{
    char* FriendlyName;
    ASSERT(iCallbackGetName != NULL);
    if (0 != iCallbackGetName(iPtrGetName, aVersion, aIndex, &FriendlyName)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufFriendlyName((const TChar*)FriendlyName);
    ZappFreeExternal(FriendlyName);
    aFriendlyName.Write(bufFriendlyName);
    aFriendlyName.WriteFlush();
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::GetPosition(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aX, IInvocationResponseUint& aY, IInvocationResponseUint& aZ)
{
    uint32_t X;
    uint32_t Y;
    uint32_t Z;
    ASSERT(iCallbackGetPosition != NULL);
    if (0 != iCallbackGetPosition(iPtrGetPosition, aVersion, aIndex, &X, &Y, &Z)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aX.Write(X);
    aY.Write(Y);
    aZ.Write(Z);
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, TUint aColor)
{
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, aVersion, aIndex, aColor)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::GetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aColor)
{
    uint32_t Color;
    ASSERT(iCallbackGetColor != NULL);
    if (0 != iCallbackGetColor(iPtrGetColor, aVersion, aIndex, &Color)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aColor.Write(Color);
    aResponse.End();
}

void DvProviderZappOrgTestLights1C::GetColorComponents(IInvocationResponse& aResponse, TUint aVersion, TUint aColor, IInvocationResponseUint& aBrightness, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
{
    uint32_t Brightness;
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetColorComponents != NULL);
    if (0 != iCallbackGetColorComponents(iPtrGetColorComponents, aVersion, aColor, &Brightness, &Red, &Green, &Blue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aBrightness.Write(Brightness);
    aRed.Write(Red);
    aGreen.Write(Green);
    aBlue.Write(Blue);
    aResponse.End();
}



THandle DvProviderZappOrgTestLights1Create(DvDeviceC aDevice)
{
	return new DvProviderZappOrgTestLights1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderZappOrgTestLights1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService);
}

void DvProviderZappOrgTestLights1EnableActionGetCount(THandle aService, CallbackTestLights1GetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetCount(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionGetRoom(THandle aService, CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetRoom(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionGetName(THandle aService, CallbackTestLights1GetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetName(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionGetPosition(THandle aService, CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetPosition(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionSetColor(THandle aService, CallbackTestLights1SetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionSetColor(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionGetColor(THandle aService, CallbackTestLights1GetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetColor(aCallback, aPtr);
}

void DvProviderZappOrgTestLights1EnableActionGetColorComponents(THandle aService, CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderZappOrgTestLights1C*>(aService)->EnableActionGetColorComponents(aCallback, aPtr);
}

