#include <C/DvUpnpOrgRenderingControl2.h>
#include <Core/DvUpnpOrgRenderingControl2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgRenderingControl2C : public DvProviderUpnpOrgRenderingControl2
{
public:
    DvProviderUpnpOrgRenderingControl2C(DvDevice& aDevice);
    void EnableActionListPresets(CallbackRenderingControl2ListPresets aCallback, void* aPtr);
    void EnableActionSelectPreset(CallbackRenderingControl2SelectPreset aCallback, void* aPtr);
    void EnableActionGetBrightness(CallbackRenderingControl2GetBrightness aCallback, void* aPtr);
    void EnableActionSetBrightness(CallbackRenderingControl2SetBrightness aCallback, void* aPtr);
    void EnableActionGetContrast(CallbackRenderingControl2GetContrast aCallback, void* aPtr);
    void EnableActionSetContrast(CallbackRenderingControl2SetContrast aCallback, void* aPtr);
    void EnableActionGetSharpness(CallbackRenderingControl2GetSharpness aCallback, void* aPtr);
    void EnableActionSetSharpness(CallbackRenderingControl2SetSharpness aCallback, void* aPtr);
    void EnableActionGetRedVideoGain(CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr);
    void EnableActionSetRedVideoGain(CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr);
    void EnableActionGetGreenVideoGain(CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr);
    void EnableActionSetGreenVideoGain(CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr);
    void EnableActionGetBlueVideoGain(CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr);
    void EnableActionSetBlueVideoGain(CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr);
    void EnableActionGetRedVideoBlackLevel(CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetRedVideoBlackLevel(CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetColorTemperature(CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr);
    void EnableActionSetColorTemperature(CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr);
    void EnableActionGetHorizontalKeystone(CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionSetHorizontalKeystone(CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionGetVerticalKeystone(CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr);
    void EnableActionSetVerticalKeystone(CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr);
    void EnableActionGetMute(CallbackRenderingControl2GetMute aCallback, void* aPtr);
    void EnableActionSetMute(CallbackRenderingControl2SetMute aCallback, void* aPtr);
    void EnableActionGetVolume(CallbackRenderingControl2GetVolume aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackRenderingControl2SetVolume aCallback, void* aPtr);
    void EnableActionGetVolumeDB(CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr);
    void EnableActionSetVolumeDB(CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr);
    void EnableActionGetVolumeDBRange(CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr);
    void EnableActionGetLoudness(CallbackRenderingControl2GetLoudness aCallback, void* aPtr);
    void EnableActionSetLoudness(CallbackRenderingControl2SetLoudness aCallback, void* aPtr);
    void EnableActionGetStateVariables(CallbackRenderingControl2GetStateVariables aCallback, void* aPtr);
    void EnableActionSetStateVariables(CallbackRenderingControl2SetStateVariables aCallback, void* aPtr);
private:
    void ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList);
    void SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName);
    void GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness);
    void SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness);
    void GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast);
    void SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast);
    void GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness);
    void SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness);
    void GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain);
    void SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain);
    void GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain);
    void SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain);
    void GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain);
    void SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain);
    void GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel);
    void SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel);
    void GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel);
    void SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel);
    void GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel);
    void SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel);
    void GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature);
    void SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature);
    void GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone);
    void SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone);
    void GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone);
    void SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone);
    void GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute);
    void SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute);
    void GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume);
    void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume);
    void GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume);
    void SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume);
    void GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue);
    void GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness);
    void SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness);
    void GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs);
    void SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList);
private:
    CallbackRenderingControl2ListPresets iCallbackListPresets;
    void* iPtrListPresets;
    CallbackRenderingControl2SelectPreset iCallbackSelectPreset;
    void* iPtrSelectPreset;
    CallbackRenderingControl2GetBrightness iCallbackGetBrightness;
    void* iPtrGetBrightness;
    CallbackRenderingControl2SetBrightness iCallbackSetBrightness;
    void* iPtrSetBrightness;
    CallbackRenderingControl2GetContrast iCallbackGetContrast;
    void* iPtrGetContrast;
    CallbackRenderingControl2SetContrast iCallbackSetContrast;
    void* iPtrSetContrast;
    CallbackRenderingControl2GetSharpness iCallbackGetSharpness;
    void* iPtrGetSharpness;
    CallbackRenderingControl2SetSharpness iCallbackSetSharpness;
    void* iPtrSetSharpness;
    CallbackRenderingControl2GetRedVideoGain iCallbackGetRedVideoGain;
    void* iPtrGetRedVideoGain;
    CallbackRenderingControl2SetRedVideoGain iCallbackSetRedVideoGain;
    void* iPtrSetRedVideoGain;
    CallbackRenderingControl2GetGreenVideoGain iCallbackGetGreenVideoGain;
    void* iPtrGetGreenVideoGain;
    CallbackRenderingControl2SetGreenVideoGain iCallbackSetGreenVideoGain;
    void* iPtrSetGreenVideoGain;
    CallbackRenderingControl2GetBlueVideoGain iCallbackGetBlueVideoGain;
    void* iPtrGetBlueVideoGain;
    CallbackRenderingControl2SetBlueVideoGain iCallbackSetBlueVideoGain;
    void* iPtrSetBlueVideoGain;
    CallbackRenderingControl2GetRedVideoBlackLevel iCallbackGetRedVideoBlackLevel;
    void* iPtrGetRedVideoBlackLevel;
    CallbackRenderingControl2SetRedVideoBlackLevel iCallbackSetRedVideoBlackLevel;
    void* iPtrSetRedVideoBlackLevel;
    CallbackRenderingControl2GetGreenVideoBlackLevel iCallbackGetGreenVideoBlackLevel;
    void* iPtrGetGreenVideoBlackLevel;
    CallbackRenderingControl2SetGreenVideoBlackLevel iCallbackSetGreenVideoBlackLevel;
    void* iPtrSetGreenVideoBlackLevel;
    CallbackRenderingControl2GetBlueVideoBlackLevel iCallbackGetBlueVideoBlackLevel;
    void* iPtrGetBlueVideoBlackLevel;
    CallbackRenderingControl2SetBlueVideoBlackLevel iCallbackSetBlueVideoBlackLevel;
    void* iPtrSetBlueVideoBlackLevel;
    CallbackRenderingControl2GetColorTemperature iCallbackGetColorTemperature;
    void* iPtrGetColorTemperature;
    CallbackRenderingControl2SetColorTemperature iCallbackSetColorTemperature;
    void* iPtrSetColorTemperature;
    CallbackRenderingControl2GetHorizontalKeystone iCallbackGetHorizontalKeystone;
    void* iPtrGetHorizontalKeystone;
    CallbackRenderingControl2SetHorizontalKeystone iCallbackSetHorizontalKeystone;
    void* iPtrSetHorizontalKeystone;
    CallbackRenderingControl2GetVerticalKeystone iCallbackGetVerticalKeystone;
    void* iPtrGetVerticalKeystone;
    CallbackRenderingControl2SetVerticalKeystone iCallbackSetVerticalKeystone;
    void* iPtrSetVerticalKeystone;
    CallbackRenderingControl2GetMute iCallbackGetMute;
    void* iPtrGetMute;
    CallbackRenderingControl2SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackRenderingControl2GetVolume iCallbackGetVolume;
    void* iPtrGetVolume;
    CallbackRenderingControl2SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackRenderingControl2GetVolumeDB iCallbackGetVolumeDB;
    void* iPtrGetVolumeDB;
    CallbackRenderingControl2SetVolumeDB iCallbackSetVolumeDB;
    void* iPtrSetVolumeDB;
    CallbackRenderingControl2GetVolumeDBRange iCallbackGetVolumeDBRange;
    void* iPtrGetVolumeDBRange;
    CallbackRenderingControl2GetLoudness iCallbackGetLoudness;
    void* iPtrGetLoudness;
    CallbackRenderingControl2SetLoudness iCallbackSetLoudness;
    void* iPtrSetLoudness;
    CallbackRenderingControl2GetStateVariables iCallbackGetStateVariables;
    void* iPtrGetStateVariables;
    CallbackRenderingControl2SetStateVariables iCallbackSetStateVariables;
    void* iPtrSetStateVariables;
};

DvProviderUpnpOrgRenderingControl2C::DvProviderUpnpOrgRenderingControl2C(DvDevice& aDevice)
    : DvProviderUpnpOrgRenderingControl2(aDevice)
{
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionListPresets(CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    iCallbackListPresets = aCallback;
    iPtrListPresets = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionListPresets();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSelectPreset(CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    iCallbackSelectPreset = aCallback;
    iPtrSelectPreset = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSelectPreset();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBrightness(CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    iCallbackGetBrightness = aCallback;
    iPtrGetBrightness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetBrightness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBrightness(CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    iCallbackSetBrightness = aCallback;
    iPtrSetBrightness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetBrightness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetContrast(CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    iCallbackGetContrast = aCallback;
    iPtrGetContrast = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetContrast();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetContrast(CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    iCallbackSetContrast = aCallback;
    iPtrSetContrast = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetContrast();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetSharpness(CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    iCallbackGetSharpness = aCallback;
    iPtrGetSharpness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetSharpness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetSharpness(CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    iCallbackSetSharpness = aCallback;
    iPtrSetSharpness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetSharpness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetRedVideoGain(CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    iCallbackGetRedVideoGain = aCallback;
    iPtrGetRedVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetRedVideoGain(CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    iCallbackSetRedVideoGain = aCallback;
    iPtrSetRedVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetGreenVideoGain(CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackGetGreenVideoGain = aCallback;
    iPtrGetGreenVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetGreenVideoGain(CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackSetGreenVideoGain = aCallback;
    iPtrSetGreenVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBlueVideoGain(CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackGetBlueVideoGain = aCallback;
    iPtrGetBlueVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBlueVideoGain(CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackSetBlueVideoGain = aCallback;
    iPtrSetBlueVideoGain = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoGain();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetRedVideoBlackLevel(CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetRedVideoBlackLevel = aCallback;
    iPtrGetRedVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetRedVideoBlackLevel(CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetRedVideoBlackLevel = aCallback;
    iPtrSetRedVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetGreenVideoBlackLevel = aCallback;
    iPtrGetGreenVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetGreenVideoBlackLevel = aCallback;
    iPtrSetGreenVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetBlueVideoBlackLevel = aCallback;
    iPtrGetBlueVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetBlueVideoBlackLevel = aCallback;
    iPtrSetBlueVideoBlackLevel = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoBlackLevel();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetColorTemperature(CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    iCallbackGetColorTemperature = aCallback;
    iPtrGetColorTemperature = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetColorTemperature();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetColorTemperature(CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    iCallbackSetColorTemperature = aCallback;
    iPtrSetColorTemperature = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetColorTemperature();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetHorizontalKeystone(CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackGetHorizontalKeystone = aCallback;
    iPtrGetHorizontalKeystone = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetHorizontalKeystone();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetHorizontalKeystone(CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackSetHorizontalKeystone = aCallback;
    iPtrSetHorizontalKeystone = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetHorizontalKeystone();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVerticalKeystone(CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackGetVerticalKeystone = aCallback;
    iPtrGetVerticalKeystone = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetVerticalKeystone();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVerticalKeystone(CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackSetVerticalKeystone = aCallback;
    iPtrSetVerticalKeystone = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetVerticalKeystone();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetMute(CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    iCallbackGetMute = aCallback;
    iPtrGetMute = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetMute();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetMute(CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetMute();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolume(CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    iCallbackGetVolume = aCallback;
    iPtrGetVolume = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetVolume();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVolume(CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetVolume();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolumeDB(CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    iCallbackGetVolumeDB = aCallback;
    iPtrGetVolumeDB = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDB();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVolumeDB(CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    iCallbackSetVolumeDB = aCallback;
    iPtrSetVolumeDB = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetVolumeDB();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolumeDBRange(CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    iCallbackGetVolumeDBRange = aCallback;
    iPtrGetVolumeDBRange = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDBRange();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetLoudness(CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    iCallbackGetLoudness = aCallback;
    iPtrGetLoudness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetLoudness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetLoudness(CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    iCallbackSetLoudness = aCallback;
    iPtrSetLoudness = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetLoudness();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetStateVariables(CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionGetStateVariables();
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetStateVariables(CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    DvProviderUpnpOrgRenderingControl2::EnableActionSetStateVariables();
}

void DvProviderUpnpOrgRenderingControl2C::ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList)
{
    char* CurrentPresetNameList;
    ASSERT(iCallbackListPresets != NULL);
    if (0 != iCallbackListPresets(iPtrListPresets, aVersion, aInstanceID, &CurrentPresetNameList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufCurrentPresetNameList((const TChar*)CurrentPresetNameList);
    ZappFreeExternal(CurrentPresetNameList);
    aCurrentPresetNameList.Write(bufCurrentPresetNameList);
    aCurrentPresetNameList.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName)
{
    ASSERT(iCallbackSelectPreset != NULL);
    if (0 != iCallbackSelectPreset(iPtrSelectPreset, aVersion, aInstanceID, (const char*)aPresetName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness)
{
    uint32_t CurrentBrightness;
    ASSERT(iCallbackGetBrightness != NULL);
    if (0 != iCallbackGetBrightness(iPtrGetBrightness, aVersion, aInstanceID, &CurrentBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentBrightness.Write(CurrentBrightness);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness)
{
    ASSERT(iCallbackSetBrightness != NULL);
    if (0 != iCallbackSetBrightness(iPtrSetBrightness, aVersion, aInstanceID, aDesiredBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast)
{
    uint32_t CurrentContrast;
    ASSERT(iCallbackGetContrast != NULL);
    if (0 != iCallbackGetContrast(iPtrGetContrast, aVersion, aInstanceID, &CurrentContrast)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentContrast.Write(CurrentContrast);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast)
{
    ASSERT(iCallbackSetContrast != NULL);
    if (0 != iCallbackSetContrast(iPtrSetContrast, aVersion, aInstanceID, aDesiredContrast)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness)
{
    uint32_t CurrentSharpness;
    ASSERT(iCallbackGetSharpness != NULL);
    if (0 != iCallbackGetSharpness(iPtrGetSharpness, aVersion, aInstanceID, &CurrentSharpness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentSharpness.Write(CurrentSharpness);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness)
{
    ASSERT(iCallbackSetSharpness != NULL);
    if (0 != iCallbackSetSharpness(iPtrSetSharpness, aVersion, aInstanceID, aDesiredSharpness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain)
{
    uint32_t CurrentRedVideoGain;
    ASSERT(iCallbackGetRedVideoGain != NULL);
    if (0 != iCallbackGetRedVideoGain(iPtrGetRedVideoGain, aVersion, aInstanceID, &CurrentRedVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentRedVideoGain.Write(CurrentRedVideoGain);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    ASSERT(iCallbackSetRedVideoGain != NULL);
    if (0 != iCallbackSetRedVideoGain(iPtrSetRedVideoGain, aVersion, aInstanceID, aDesiredRedVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain)
{
    uint32_t CurrentGreenVideoGain;
    ASSERT(iCallbackGetGreenVideoGain != NULL);
    if (0 != iCallbackGetGreenVideoGain(iPtrGetGreenVideoGain, aVersion, aInstanceID, &CurrentGreenVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentGreenVideoGain.Write(CurrentGreenVideoGain);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    ASSERT(iCallbackSetGreenVideoGain != NULL);
    if (0 != iCallbackSetGreenVideoGain(iPtrSetGreenVideoGain, aVersion, aInstanceID, aDesiredGreenVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain)
{
    uint32_t CurrentBlueVideoGain;
    ASSERT(iCallbackGetBlueVideoGain != NULL);
    if (0 != iCallbackGetBlueVideoGain(iPtrGetBlueVideoGain, aVersion, aInstanceID, &CurrentBlueVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentBlueVideoGain.Write(CurrentBlueVideoGain);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    ASSERT(iCallbackSetBlueVideoGain != NULL);
    if (0 != iCallbackSetBlueVideoGain(iPtrSetBlueVideoGain, aVersion, aInstanceID, aDesiredBlueVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel)
{
    uint32_t CurrentRedVideoBlackLevel;
    ASSERT(iCallbackGetRedVideoBlackLevel != NULL);
    if (0 != iCallbackGetRedVideoBlackLevel(iPtrGetRedVideoBlackLevel, aVersion, aInstanceID, &CurrentRedVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentRedVideoBlackLevel.Write(CurrentRedVideoBlackLevel);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    ASSERT(iCallbackSetRedVideoBlackLevel != NULL);
    if (0 != iCallbackSetRedVideoBlackLevel(iPtrSetRedVideoBlackLevel, aVersion, aInstanceID, aDesiredRedVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel)
{
    uint32_t CurrentGreenVideoBlackLevel;
    ASSERT(iCallbackGetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackGetGreenVideoBlackLevel(iPtrGetGreenVideoBlackLevel, aVersion, aInstanceID, &CurrentGreenVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentGreenVideoBlackLevel.Write(CurrentGreenVideoBlackLevel);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    ASSERT(iCallbackSetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackSetGreenVideoBlackLevel(iPtrSetGreenVideoBlackLevel, aVersion, aInstanceID, aDesiredGreenVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel)
{
    uint32_t CurrentBlueVideoBlackLevel;
    ASSERT(iCallbackGetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackGetBlueVideoBlackLevel(iPtrGetBlueVideoBlackLevel, aVersion, aInstanceID, &CurrentBlueVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentBlueVideoBlackLevel.Write(CurrentBlueVideoBlackLevel);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    ASSERT(iCallbackSetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackSetBlueVideoBlackLevel(iPtrSetBlueVideoBlackLevel, aVersion, aInstanceID, aDesiredBlueVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature)
{
    uint32_t CurrentColorTemperature;
    ASSERT(iCallbackGetColorTemperature != NULL);
    if (0 != iCallbackGetColorTemperature(iPtrGetColorTemperature, aVersion, aInstanceID, &CurrentColorTemperature)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentColorTemperature.Write(CurrentColorTemperature);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature)
{
    ASSERT(iCallbackSetColorTemperature != NULL);
    if (0 != iCallbackSetColorTemperature(iPtrSetColorTemperature, aVersion, aInstanceID, aDesiredColorTemperature)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone)
{
    int32_t CurrentHorizontalKeystone;
    ASSERT(iCallbackGetHorizontalKeystone != NULL);
    if (0 != iCallbackGetHorizontalKeystone(iPtrGetHorizontalKeystone, aVersion, aInstanceID, &CurrentHorizontalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentHorizontalKeystone.Write(CurrentHorizontalKeystone);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    ASSERT(iCallbackSetHorizontalKeystone != NULL);
    if (0 != iCallbackSetHorizontalKeystone(iPtrSetHorizontalKeystone, aVersion, aInstanceID, aDesiredHorizontalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone)
{
    int32_t CurrentVerticalKeystone;
    ASSERT(iCallbackGetVerticalKeystone != NULL);
    if (0 != iCallbackGetVerticalKeystone(iPtrGetVerticalKeystone, aVersion, aInstanceID, &CurrentVerticalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentVerticalKeystone.Write(CurrentVerticalKeystone);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    ASSERT(iCallbackSetVerticalKeystone != NULL);
    if (0 != iCallbackSetVerticalKeystone(iPtrSetVerticalKeystone, aVersion, aInstanceID, aDesiredVerticalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute)
{
    uint32_t CurrentMute;
    ASSERT(iCallbackGetMute != NULL);
    if (0 != iCallbackGetMute(iPtrGetMute, aVersion, aInstanceID, (const char*)aChannel.Ptr(), &CurrentMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentMute.Write((CurrentMute!=0));
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume)
{
    uint32_t CurrentVolume;
    ASSERT(iCallbackGetVolume != NULL);
    if (0 != iCallbackGetVolume(iPtrGetVolume, aVersion, aInstanceID, (const char*)aChannel.Ptr(), &CurrentVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentVolume.Write(CurrentVolume);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume)
{
    int32_t CurrentVolume;
    ASSERT(iCallbackGetVolumeDB != NULL);
    if (0 != iCallbackGetVolumeDB(iPtrGetVolumeDB, aVersion, aInstanceID, (const char*)aChannel.Ptr(), &CurrentVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentVolume.Write(CurrentVolume);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    ASSERT(iCallbackSetVolumeDB != NULL);
    if (0 != iCallbackSetVolumeDB(iPtrSetVolumeDB, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue)
{
    int32_t MinValue;
    int32_t MaxValue;
    ASSERT(iCallbackGetVolumeDBRange != NULL);
    if (0 != iCallbackGetVolumeDBRange(iPtrGetVolumeDBRange, aVersion, aInstanceID, (const char*)aChannel.Ptr(), &MinValue, &MaxValue)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aMinValue.Write(MinValue);
    aMaxValue.Write(MaxValue);
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness)
{
    uint32_t CurrentLoudness;
    ASSERT(iCallbackGetLoudness != NULL);
    if (0 != iCallbackGetLoudness(iPtrGetLoudness, aVersion, aInstanceID, (const char*)aChannel.Ptr(), &CurrentLoudness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aCurrentLoudness.Write((CurrentLoudness!=0));
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    ASSERT(iCallbackSetLoudness != NULL);
    if (0 != iCallbackSetLoudness(iPtrSetLoudness, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredLoudness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs)
{
    char* StateVariableValuePairs;
    ASSERT(iCallbackGetStateVariables != NULL);
    if (0 != iCallbackGetStateVariables(iPtrGetStateVariables, aVersion, aInstanceID, (const char*)aStateVariableList.Ptr(), &StateVariableValuePairs)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufStateVariableValuePairs((const TChar*)StateVariableValuePairs);
    ZappFreeExternal(StateVariableValuePairs);
    aStateVariableValuePairs.Write(bufStateVariableValuePairs);
    aStateVariableValuePairs.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgRenderingControl2C::SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList)
{
    char* StateVariableList;
    ASSERT(iCallbackSetStateVariables != NULL);
    if (0 != iCallbackSetStateVariables(iPtrSetStateVariables, aVersion, aInstanceID, (const char*)aRenderingControlUDN.Ptr(), (const char*)aServiceType.Ptr(), (const char*)aServiceId.Ptr(), (const char*)aStateVariableValuePairs.Ptr(), &StateVariableList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufStateVariableList((const TChar*)StateVariableList);
    ZappFreeExternal(StateVariableList);
    aStateVariableList.Write(bufStateVariableList);
    aStateVariableList.WriteFlush();
    aResponse.End();
}



THandle DvProviderUpnpOrgRenderingControl2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgRenderingControl2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgRenderingControl2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider);
}

void DvProviderUpnpOrgRenderingControl2EnableActionListPresets(THandle aProvider, CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionListPresets(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSelectPreset(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBrightness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBrightness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(THandle aProvider, CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetContrast(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(THandle aProvider, CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetContrast(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetSharpness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetSharpness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetRedVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetRedVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetGreenVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetGreenVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBlueVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBlueVideoGain(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetRedVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetRedVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetColorTemperature(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetColorTemperature(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetHorizontalKeystone(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetHorizontalKeystone(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVerticalKeystone(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVerticalKeystone(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetMute(THandle aProvider, CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetMute(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetMute(THandle aProvider, CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(THandle aProvider, CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolume(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(THandle aProvider, CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolumeDB(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVolumeDB(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolumeDBRange(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetLoudness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetLoudness(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aProvider, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetStateVariables(aCallback, aPtr);
}

void DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aProvider, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

