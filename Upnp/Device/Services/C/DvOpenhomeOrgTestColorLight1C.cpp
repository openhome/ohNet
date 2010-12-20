#include <C/DvOpenhomeOrgTestColorLight1.h>
#include <Core/DvOpenhomeOrgTestColorLight1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderOpenhomeOrgTestColorLight1C : public DvProviderOpenhomeOrgTestColorLight1
{
public:
    DvProviderOpenhomeOrgTestColorLight1C(DvDevice& aDevice);
    void EnableActionGetName(CallbackTestColorLight1GetName aCallback, void* aPtr);
    void EnableActionSetColor(CallbackTestColorLight1SetColor aCallback, void* aPtr);
    void EnableActionGetColor(CallbackTestColorLight1GetColor aCallback, void* aPtr);
    void EnableActionGetMaxColors(CallbackTestColorLight1GetMaxColors aCallback, void* aPtr);
private:
    void GetName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFriendlyName);
    void SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aRed, TUint aGreen, TUint aBlue);
    void GetColor(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
    void GetMaxColors(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
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

DvProviderOpenhomeOrgTestColorLight1C::DvProviderOpenhomeOrgTestColorLight1C(DvDevice& aDevice)
    : DvProviderOpenhomeOrgTestColorLight1(aDevice)
{
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetName(CallbackTestColorLight1GetName aCallback, void* aPtr)
{
    iCallbackGetName = aCallback;
    iPtrGetName = aPtr;
    DvProviderOpenhomeOrgTestColorLight1::EnableActionGetName();
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionSetColor(CallbackTestColorLight1SetColor aCallback, void* aPtr)
{
    iCallbackSetColor = aCallback;
    iPtrSetColor = aPtr;
    DvProviderOpenhomeOrgTestColorLight1::EnableActionSetColor();
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetColor(CallbackTestColorLight1GetColor aCallback, void* aPtr)
{
    iCallbackGetColor = aCallback;
    iPtrGetColor = aPtr;
    DvProviderOpenhomeOrgTestColorLight1::EnableActionGetColor();
}

void DvProviderOpenhomeOrgTestColorLight1C::EnableActionGetMaxColors(CallbackTestColorLight1GetMaxColors aCallback, void* aPtr)
{
    iCallbackGetMaxColors = aCallback;
    iPtrGetMaxColors = aPtr;
    DvProviderOpenhomeOrgTestColorLight1::EnableActionGetMaxColors();
}

void DvProviderOpenhomeOrgTestColorLight1C::GetName(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFriendlyName)
{
    char* FriendlyName;
    ASSERT(iCallbackGetName != NULL);
    if (0 != iCallbackGetName(iPtrGetName, aVersion, &FriendlyName)) {
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

void DvProviderOpenhomeOrgTestColorLight1C::SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aRed, TUint aGreen, TUint aBlue)
{
    ASSERT(iCallbackSetColor != NULL);
    if (0 != iCallbackSetColor(iPtrSetColor, aVersion, aRed, aGreen, aBlue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderOpenhomeOrgTestColorLight1C::GetColor(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
{
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetColor != NULL);
    if (0 != iCallbackGetColor(iPtrGetColor, aVersion, &Red, &Green, &Blue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aRed.Write(Red);
    aGreen.Write(Green);
    aBlue.Write(Blue);
    aResponse.End();
}

void DvProviderOpenhomeOrgTestColorLight1C::GetMaxColors(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue)
{
    uint32_t Red;
    uint32_t Green;
    uint32_t Blue;
    ASSERT(iCallbackGetMaxColors != NULL);
    if (0 != iCallbackGetMaxColors(iPtrGetMaxColors, aVersion, &Red, &Green, &Blue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aRed.Write(Red);
    aGreen.Write(Green);
    aBlue.Write(Blue);
    aResponse.End();
}



THandle DvProviderOpenhomeOrgTestColorLight1Create(DvDeviceC aDevice)
{
	return new DvProviderOpenhomeOrgTestColorLight1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
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

