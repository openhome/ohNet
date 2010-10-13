#include <C/DvZappOrgTestLights1.h>
#include <Core/DvZappOrgTestLights1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceZappOrgTestLights1C : public DvServiceZappOrgTestLights1
{
public:
    DvServiceZappOrgTestLights1C(DvDevice& aDevice);
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

DvServiceZappOrgTestLights1C::DvServiceZappOrgTestLights1C(DvDevice& aDevice)
    : DvServiceZappOrgTestLights1(aDevice)
{
}

void DvServiceZappOrgTestLights1C::EnableActionGetCount(CallbackTestLights1GetCount aCallback, void* aPtr)
{
    iCallbackGetCount = aCallback;
    iPtrGetCount = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetCount();
}

void DvServiceZappOrgTestLights1C::EnableActionGetRoom(CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    iCallbackGetRoom = aCallback;
    iPtrGetRoom = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetRoom();
}

void DvServiceZappOrgTestLights1C::EnableActionGetName(CallbackTestLights1GetName aCallback, void* aPtr)
{
    iCallbackGetName = aCallback;
    iPtrGetName = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetName();
}

void DvServiceZappOrgTestLights1C::EnableActionGetPosition(CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    iCallbackGetPosition = aCallback;
    iPtrGetPosition = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetPosition();
}

void DvServiceZappOrgTestLights1C::EnableActionSetColor(CallbackTestLights1SetColor aCallback, void* aPtr)
{
    iCallbackSetColor = aCallback;
    iPtrSetColor = aPtr;
    DvServiceZappOrgTestLights1::EnableActionSetColor();
}

void DvServiceZappOrgTestLights1C::EnableActionGetColor(CallbackTestLights1GetColor aCallback, void* aPtr)
{
    iCallbackGetColor = aCallback;
    iPtrGetColor = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetColor();
}

void DvServiceZappOrgTestLights1C::EnableActionGetColorComponents(CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    iCallbackGetColorComponents = aCallback;
    iPtrGetColorComponents = aPtr;
    DvServiceZappOrgTestLights1::EnableActionGetColorComponents();
}

void DvServiceZappOrgTestLights1C::GetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aCount)
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

void DvServiceZappOrgTestLights1C::GetRoom(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aRoomName)
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

void DvServiceZappOrgTestLights1C::GetName(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aFriendlyName)
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

void DvServiceZappOrgTestLights1C::GetPosition(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aX, IInvocationResponseUint& aY, IInvocationResponseUint& aZ)
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

void DvServiceZappOrgTestLights1C::SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, TUint aColor)
{
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, aVersion, aIndex, aColor)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceZappOrgTestLights1C::GetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aColor)
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

void DvServiceZappOrgTestLights1C::GetColorComponents(IInvocationResponse& aResponse, TUint aVersion, TUint aColor, IInvocationResponseUint& aBrightness, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
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



THandle DvServiceZappOrgTestLights1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceZappOrgTestLights1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceZappOrgTestLights1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService);
}

void DvServiceZappOrgTestLights1EnableActionGetCount(THandle aService, CallbackTestLights1GetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetCount(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionGetRoom(THandle aService, CallbackTestLights1GetRoom aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetRoom(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionGetName(THandle aService, CallbackTestLights1GetName aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetName(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionGetPosition(THandle aService, CallbackTestLights1GetPosition aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetPosition(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionSetColor(THandle aService, CallbackTestLights1SetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionSetColor(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionGetColor(THandle aService, CallbackTestLights1GetColor aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetColor(aCallback, aPtr);
}

void DvServiceZappOrgTestLights1EnableActionGetColorComponents(THandle aService, CallbackTestLights1GetColorComponents aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceZappOrgTestLights1C*>(aService)->EnableActionGetColorComponents(aCallback, aPtr);
}

