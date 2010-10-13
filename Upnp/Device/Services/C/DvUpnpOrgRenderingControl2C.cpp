#include <C/DvUpnpOrgRenderingControl2.h>
#include <Core/DvUpnpOrgRenderingControl2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgRenderingControl2C : public DvServiceUpnpOrgRenderingControl2
{
public:
    DvServiceUpnpOrgRenderingControl2C(DvDevice& aDevice);
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

DvServiceUpnpOrgRenderingControl2C::DvServiceUpnpOrgRenderingControl2C(DvDevice& aDevice)
    : DvServiceUpnpOrgRenderingControl2(aDevice)
{
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionListPresets(CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    iCallbackListPresets = aCallback;
    iPtrListPresets = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionListPresets();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSelectPreset(CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    iCallbackSelectPreset = aCallback;
    iPtrSelectPreset = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSelectPreset();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetBrightness(CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    iCallbackGetBrightness = aCallback;
    iPtrGetBrightness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetBrightness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetBrightness(CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    iCallbackSetBrightness = aCallback;
    iPtrSetBrightness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetBrightness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetContrast(CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    iCallbackGetContrast = aCallback;
    iPtrGetContrast = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetContrast();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetContrast(CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    iCallbackSetContrast = aCallback;
    iPtrSetContrast = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetContrast();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetSharpness(CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    iCallbackGetSharpness = aCallback;
    iPtrGetSharpness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetSharpness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetSharpness(CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    iCallbackSetSharpness = aCallback;
    iPtrSetSharpness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetSharpness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetRedVideoGain(CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    iCallbackGetRedVideoGain = aCallback;
    iPtrGetRedVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetRedVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetRedVideoGain(CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    iCallbackSetRedVideoGain = aCallback;
    iPtrSetRedVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetRedVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetGreenVideoGain(CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackGetGreenVideoGain = aCallback;
    iPtrGetGreenVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetGreenVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetGreenVideoGain(CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackSetGreenVideoGain = aCallback;
    iPtrSetGreenVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetGreenVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetBlueVideoGain(CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackGetBlueVideoGain = aCallback;
    iPtrGetBlueVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetBlueVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetBlueVideoGain(CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackSetBlueVideoGain = aCallback;
    iPtrSetBlueVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetBlueVideoGain();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetRedVideoBlackLevel(CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetRedVideoBlackLevel = aCallback;
    iPtrGetRedVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetRedVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetRedVideoBlackLevel(CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetRedVideoBlackLevel = aCallback;
    iPtrSetRedVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetRedVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetGreenVideoBlackLevel = aCallback;
    iPtrGetGreenVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetGreenVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetGreenVideoBlackLevel = aCallback;
    iPtrSetGreenVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetGreenVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetBlueVideoBlackLevel = aCallback;
    iPtrGetBlueVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetBlueVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetBlueVideoBlackLevel = aCallback;
    iPtrSetBlueVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetBlueVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetColorTemperature(CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    iCallbackGetColorTemperature = aCallback;
    iPtrGetColorTemperature = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetColorTemperature();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetColorTemperature(CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    iCallbackSetColorTemperature = aCallback;
    iPtrSetColorTemperature = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetColorTemperature();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetHorizontalKeystone(CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackGetHorizontalKeystone = aCallback;
    iPtrGetHorizontalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetHorizontalKeystone();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetHorizontalKeystone(CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackSetHorizontalKeystone = aCallback;
    iPtrSetHorizontalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetHorizontalKeystone();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetVerticalKeystone(CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackGetVerticalKeystone = aCallback;
    iPtrGetVerticalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetVerticalKeystone();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetVerticalKeystone(CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackSetVerticalKeystone = aCallback;
    iPtrSetVerticalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetVerticalKeystone();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetMute(CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    iCallbackGetMute = aCallback;
    iPtrGetMute = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetMute();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetMute(CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetMute();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetVolume(CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    iCallbackGetVolume = aCallback;
    iPtrGetVolume = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetVolume();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetVolume(CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetVolume();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetVolumeDB(CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    iCallbackGetVolumeDB = aCallback;
    iPtrGetVolumeDB = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetVolumeDB();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetVolumeDB(CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    iCallbackSetVolumeDB = aCallback;
    iPtrSetVolumeDB = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetVolumeDB();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetVolumeDBRange(CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    iCallbackGetVolumeDBRange = aCallback;
    iPtrGetVolumeDBRange = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetVolumeDBRange();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetLoudness(CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    iCallbackGetLoudness = aCallback;
    iPtrGetLoudness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetLoudness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetLoudness(CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    iCallbackSetLoudness = aCallback;
    iPtrSetLoudness = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetLoudness();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionGetStateVariables(CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionGetStateVariables();
}

void DvServiceUpnpOrgRenderingControl2C::EnableActionSetStateVariables(CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    DvServiceUpnpOrgRenderingControl2::EnableActionSetStateVariables();
}

void DvServiceUpnpOrgRenderingControl2C::ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList)
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

void DvServiceUpnpOrgRenderingControl2C::SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName)
{
    ASSERT(iCallbackSelectPreset != NULL);
    if (0 != iCallbackSelectPreset(iPtrSelectPreset, aVersion, aInstanceID, (const char*)aPresetName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness)
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

void DvServiceUpnpOrgRenderingControl2C::SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness)
{
    ASSERT(iCallbackSetBrightness != NULL);
    if (0 != iCallbackSetBrightness(iPtrSetBrightness, aVersion, aInstanceID, aDesiredBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast)
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

void DvServiceUpnpOrgRenderingControl2C::SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast)
{
    ASSERT(iCallbackSetContrast != NULL);
    if (0 != iCallbackSetContrast(iPtrSetContrast, aVersion, aInstanceID, aDesiredContrast)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness)
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

void DvServiceUpnpOrgRenderingControl2C::SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness)
{
    ASSERT(iCallbackSetSharpness != NULL);
    if (0 != iCallbackSetSharpness(iPtrSetSharpness, aVersion, aInstanceID, aDesiredSharpness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain)
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

void DvServiceUpnpOrgRenderingControl2C::SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    ASSERT(iCallbackSetRedVideoGain != NULL);
    if (0 != iCallbackSetRedVideoGain(iPtrSetRedVideoGain, aVersion, aInstanceID, aDesiredRedVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain)
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

void DvServiceUpnpOrgRenderingControl2C::SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    ASSERT(iCallbackSetGreenVideoGain != NULL);
    if (0 != iCallbackSetGreenVideoGain(iPtrSetGreenVideoGain, aVersion, aInstanceID, aDesiredGreenVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain)
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

void DvServiceUpnpOrgRenderingControl2C::SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    ASSERT(iCallbackSetBlueVideoGain != NULL);
    if (0 != iCallbackSetBlueVideoGain(iPtrSetBlueVideoGain, aVersion, aInstanceID, aDesiredBlueVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl2C::SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    ASSERT(iCallbackSetRedVideoBlackLevel != NULL);
    if (0 != iCallbackSetRedVideoBlackLevel(iPtrSetRedVideoBlackLevel, aVersion, aInstanceID, aDesiredRedVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl2C::SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    ASSERT(iCallbackSetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackSetGreenVideoBlackLevel(iPtrSetGreenVideoBlackLevel, aVersion, aInstanceID, aDesiredGreenVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl2C::SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    ASSERT(iCallbackSetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackSetBlueVideoBlackLevel(iPtrSetBlueVideoBlackLevel, aVersion, aInstanceID, aDesiredBlueVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature)
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

void DvServiceUpnpOrgRenderingControl2C::SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature)
{
    ASSERT(iCallbackSetColorTemperature != NULL);
    if (0 != iCallbackSetColorTemperature(iPtrSetColorTemperature, aVersion, aInstanceID, aDesiredColorTemperature)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone)
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

void DvServiceUpnpOrgRenderingControl2C::SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    ASSERT(iCallbackSetHorizontalKeystone != NULL);
    if (0 != iCallbackSetHorizontalKeystone(iPtrSetHorizontalKeystone, aVersion, aInstanceID, aDesiredHorizontalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone)
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

void DvServiceUpnpOrgRenderingControl2C::SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    ASSERT(iCallbackSetVerticalKeystone != NULL);
    if (0 != iCallbackSetVerticalKeystone(iPtrSetVerticalKeystone, aVersion, aInstanceID, aDesiredVerticalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute)
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

void DvServiceUpnpOrgRenderingControl2C::SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume)
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

void DvServiceUpnpOrgRenderingControl2C::SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume)
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

void DvServiceUpnpOrgRenderingControl2C::SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    ASSERT(iCallbackSetVolumeDB != NULL);
    if (0 != iCallbackSetVolumeDB(iPtrSetVolumeDB, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue)
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

void DvServiceUpnpOrgRenderingControl2C::GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness)
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

void DvServiceUpnpOrgRenderingControl2C::SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    ASSERT(iCallbackSetLoudness != NULL);
    if (0 != iCallbackSetLoudness(iPtrSetLoudness, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredLoudness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl2C::GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs)
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

void DvServiceUpnpOrgRenderingControl2C::SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList)
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



THandle DvServiceUpnpOrgRenderingControl2Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgRenderingControl2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgRenderingControl2Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService);
}

void DvServiceUpnpOrgRenderingControl2EnableActionListPresets(THandle aService, CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionListPresets(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aService, CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSelectPreset(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aService, CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetBrightness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aService, CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetBrightness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetContrast(THandle aService, CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetContrast(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetContrast(THandle aService, CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetContrast(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aService, CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetSharpness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aService, CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetSharpness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aService, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetRedVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aService, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetRedVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aService, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetGreenVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aService, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetGreenVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aService, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetBlueVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aService, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetBlueVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aService, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetRedVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aService, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetRedVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aService, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetColorTemperature(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aService, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetColorTemperature(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aService, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetHorizontalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aService, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetHorizontalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aService, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetVerticalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aService, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetVerticalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetMute(THandle aService, CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetMute(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetMute(THandle aService, CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetMute(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetVolume(THandle aService, CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetVolume(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetVolume(THandle aService, CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetVolume(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aService, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetVolumeDB(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aService, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetVolumeDB(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aService, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetVolumeDBRange(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aService, CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetLoudness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aService, CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetLoudness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aService, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionGetStateVariables(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aService, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgRenderingControl2SetPropertyLastChange(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->SetPropertyLastChange(buf);
    return 0;
}

void DvServiceUpnpOrgRenderingControl2GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgRenderingControl2C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

