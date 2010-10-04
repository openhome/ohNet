#include <C/DvUpnpOrgRenderingControl1.h>
#include <Core/DvUpnpOrgRenderingControl1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgRenderingControl1C : public DvServiceUpnpOrgRenderingControl1
{
public:
    DvServiceUpnpOrgRenderingControl1C(DvDevice& aDevice);
    void EnableActionListPresets(CallbackRenderingControl1ListPresets aCallback, void* aPtr);
    void EnableActionSelectPreset(CallbackRenderingControl1SelectPreset aCallback, void* aPtr);
    void EnableActionGetBrightness(CallbackRenderingControl1GetBrightness aCallback, void* aPtr);
    void EnableActionSetBrightness(CallbackRenderingControl1SetBrightness aCallback, void* aPtr);
    void EnableActionGetContrast(CallbackRenderingControl1GetContrast aCallback, void* aPtr);
    void EnableActionSetContrast(CallbackRenderingControl1SetContrast aCallback, void* aPtr);
    void EnableActionGetSharpness(CallbackRenderingControl1GetSharpness aCallback, void* aPtr);
    void EnableActionSetSharpness(CallbackRenderingControl1SetSharpness aCallback, void* aPtr);
    void EnableActionGetRedVideoGain(CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr);
    void EnableActionSetRedVideoGain(CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr);
    void EnableActionGetGreenVideoGain(CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr);
    void EnableActionSetGreenVideoGain(CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr);
    void EnableActionGetBlueVideoGain(CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr);
    void EnableActionSetBlueVideoGain(CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr);
    void EnableActionGetRedVideoBlackLevel(CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetRedVideoBlackLevel(CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetColorTemperature(CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr);
    void EnableActionSetColorTemperature(CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr);
    void EnableActionGetHorizontalKeystone(CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionSetHorizontalKeystone(CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionGetVerticalKeystone(CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr);
    void EnableActionSetVerticalKeystone(CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr);
    void EnableActionGetMute(CallbackRenderingControl1GetMute aCallback, void* aPtr);
    void EnableActionSetMute(CallbackRenderingControl1SetMute aCallback, void* aPtr);
    void EnableActionGetVolume(CallbackRenderingControl1GetVolume aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackRenderingControl1SetVolume aCallback, void* aPtr);
    void EnableActionGetVolumeDB(CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr);
    void EnableActionSetVolumeDB(CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr);
    void EnableActionGetVolumeDBRange(CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr);
    void EnableActionGetLoudness(CallbackRenderingControl1GetLoudness aCallback, void* aPtr);
    void EnableActionSetLoudness(CallbackRenderingControl1SetLoudness aCallback, void* aPtr);
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
private:
    CallbackRenderingControl1ListPresets iCallbackListPresets;
    void* iPtrListPresets;
    CallbackRenderingControl1SelectPreset iCallbackSelectPreset;
    void* iPtrSelectPreset;
    CallbackRenderingControl1GetBrightness iCallbackGetBrightness;
    void* iPtrGetBrightness;
    CallbackRenderingControl1SetBrightness iCallbackSetBrightness;
    void* iPtrSetBrightness;
    CallbackRenderingControl1GetContrast iCallbackGetContrast;
    void* iPtrGetContrast;
    CallbackRenderingControl1SetContrast iCallbackSetContrast;
    void* iPtrSetContrast;
    CallbackRenderingControl1GetSharpness iCallbackGetSharpness;
    void* iPtrGetSharpness;
    CallbackRenderingControl1SetSharpness iCallbackSetSharpness;
    void* iPtrSetSharpness;
    CallbackRenderingControl1GetRedVideoGain iCallbackGetRedVideoGain;
    void* iPtrGetRedVideoGain;
    CallbackRenderingControl1SetRedVideoGain iCallbackSetRedVideoGain;
    void* iPtrSetRedVideoGain;
    CallbackRenderingControl1GetGreenVideoGain iCallbackGetGreenVideoGain;
    void* iPtrGetGreenVideoGain;
    CallbackRenderingControl1SetGreenVideoGain iCallbackSetGreenVideoGain;
    void* iPtrSetGreenVideoGain;
    CallbackRenderingControl1GetBlueVideoGain iCallbackGetBlueVideoGain;
    void* iPtrGetBlueVideoGain;
    CallbackRenderingControl1SetBlueVideoGain iCallbackSetBlueVideoGain;
    void* iPtrSetBlueVideoGain;
    CallbackRenderingControl1GetRedVideoBlackLevel iCallbackGetRedVideoBlackLevel;
    void* iPtrGetRedVideoBlackLevel;
    CallbackRenderingControl1SetRedVideoBlackLevel iCallbackSetRedVideoBlackLevel;
    void* iPtrSetRedVideoBlackLevel;
    CallbackRenderingControl1GetGreenVideoBlackLevel iCallbackGetGreenVideoBlackLevel;
    void* iPtrGetGreenVideoBlackLevel;
    CallbackRenderingControl1SetGreenVideoBlackLevel iCallbackSetGreenVideoBlackLevel;
    void* iPtrSetGreenVideoBlackLevel;
    CallbackRenderingControl1GetBlueVideoBlackLevel iCallbackGetBlueVideoBlackLevel;
    void* iPtrGetBlueVideoBlackLevel;
    CallbackRenderingControl1SetBlueVideoBlackLevel iCallbackSetBlueVideoBlackLevel;
    void* iPtrSetBlueVideoBlackLevel;
    CallbackRenderingControl1GetColorTemperature iCallbackGetColorTemperature;
    void* iPtrGetColorTemperature;
    CallbackRenderingControl1SetColorTemperature iCallbackSetColorTemperature;
    void* iPtrSetColorTemperature;
    CallbackRenderingControl1GetHorizontalKeystone iCallbackGetHorizontalKeystone;
    void* iPtrGetHorizontalKeystone;
    CallbackRenderingControl1SetHorizontalKeystone iCallbackSetHorizontalKeystone;
    void* iPtrSetHorizontalKeystone;
    CallbackRenderingControl1GetVerticalKeystone iCallbackGetVerticalKeystone;
    void* iPtrGetVerticalKeystone;
    CallbackRenderingControl1SetVerticalKeystone iCallbackSetVerticalKeystone;
    void* iPtrSetVerticalKeystone;
    CallbackRenderingControl1GetMute iCallbackGetMute;
    void* iPtrGetMute;
    CallbackRenderingControl1SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackRenderingControl1GetVolume iCallbackGetVolume;
    void* iPtrGetVolume;
    CallbackRenderingControl1SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackRenderingControl1GetVolumeDB iCallbackGetVolumeDB;
    void* iPtrGetVolumeDB;
    CallbackRenderingControl1SetVolumeDB iCallbackSetVolumeDB;
    void* iPtrSetVolumeDB;
    CallbackRenderingControl1GetVolumeDBRange iCallbackGetVolumeDBRange;
    void* iPtrGetVolumeDBRange;
    CallbackRenderingControl1GetLoudness iCallbackGetLoudness;
    void* iPtrGetLoudness;
    CallbackRenderingControl1SetLoudness iCallbackSetLoudness;
    void* iPtrSetLoudness;
};

DvServiceUpnpOrgRenderingControl1C::DvServiceUpnpOrgRenderingControl1C(DvDevice& aDevice)
    : DvServiceUpnpOrgRenderingControl1(aDevice)
{
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionListPresets(CallbackRenderingControl1ListPresets aCallback, void* aPtr)
{
    iCallbackListPresets = aCallback;
    iPtrListPresets = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionListPresets();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSelectPreset(CallbackRenderingControl1SelectPreset aCallback, void* aPtr)
{
    iCallbackSelectPreset = aCallback;
    iPtrSelectPreset = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSelectPreset();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetBrightness(CallbackRenderingControl1GetBrightness aCallback, void* aPtr)
{
    iCallbackGetBrightness = aCallback;
    iPtrGetBrightness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetBrightness();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetBrightness(CallbackRenderingControl1SetBrightness aCallback, void* aPtr)
{
    iCallbackSetBrightness = aCallback;
    iPtrSetBrightness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetBrightness();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetContrast(CallbackRenderingControl1GetContrast aCallback, void* aPtr)
{
    iCallbackGetContrast = aCallback;
    iPtrGetContrast = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetContrast();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetContrast(CallbackRenderingControl1SetContrast aCallback, void* aPtr)
{
    iCallbackSetContrast = aCallback;
    iPtrSetContrast = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetContrast();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetSharpness(CallbackRenderingControl1GetSharpness aCallback, void* aPtr)
{
    iCallbackGetSharpness = aCallback;
    iPtrGetSharpness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetSharpness();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetSharpness(CallbackRenderingControl1SetSharpness aCallback, void* aPtr)
{
    iCallbackSetSharpness = aCallback;
    iPtrSetSharpness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetSharpness();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetRedVideoGain(CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr)
{
    iCallbackGetRedVideoGain = aCallback;
    iPtrGetRedVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetRedVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetRedVideoGain(CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr)
{
    iCallbackSetRedVideoGain = aCallback;
    iPtrSetRedVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetRedVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetGreenVideoGain(CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackGetGreenVideoGain = aCallback;
    iPtrGetGreenVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetGreenVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetGreenVideoGain(CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackSetGreenVideoGain = aCallback;
    iPtrSetGreenVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetGreenVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetBlueVideoGain(CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackGetBlueVideoGain = aCallback;
    iPtrGetBlueVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetBlueVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetBlueVideoGain(CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackSetBlueVideoGain = aCallback;
    iPtrSetBlueVideoGain = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetBlueVideoGain();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetRedVideoBlackLevel(CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetRedVideoBlackLevel = aCallback;
    iPtrGetRedVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetRedVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetRedVideoBlackLevel(CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetRedVideoBlackLevel = aCallback;
    iPtrSetRedVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetRedVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetGreenVideoBlackLevel = aCallback;
    iPtrGetGreenVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetGreenVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetGreenVideoBlackLevel = aCallback;
    iPtrSetGreenVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetGreenVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetBlueVideoBlackLevel = aCallback;
    iPtrGetBlueVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetBlueVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetBlueVideoBlackLevel = aCallback;
    iPtrSetBlueVideoBlackLevel = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetBlueVideoBlackLevel();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetColorTemperature(CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr)
{
    iCallbackGetColorTemperature = aCallback;
    iPtrGetColorTemperature = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetColorTemperature();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetColorTemperature(CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr)
{
    iCallbackSetColorTemperature = aCallback;
    iPtrSetColorTemperature = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetColorTemperature();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetHorizontalKeystone(CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackGetHorizontalKeystone = aCallback;
    iPtrGetHorizontalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetHorizontalKeystone();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetHorizontalKeystone(CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackSetHorizontalKeystone = aCallback;
    iPtrSetHorizontalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetHorizontalKeystone();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetVerticalKeystone(CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackGetVerticalKeystone = aCallback;
    iPtrGetVerticalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetVerticalKeystone();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetVerticalKeystone(CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackSetVerticalKeystone = aCallback;
    iPtrSetVerticalKeystone = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetVerticalKeystone();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetMute(CallbackRenderingControl1GetMute aCallback, void* aPtr)
{
    iCallbackGetMute = aCallback;
    iPtrGetMute = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetMute();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetMute(CallbackRenderingControl1SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetMute();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetVolume(CallbackRenderingControl1GetVolume aCallback, void* aPtr)
{
    iCallbackGetVolume = aCallback;
    iPtrGetVolume = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetVolume();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetVolume(CallbackRenderingControl1SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetVolume();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetVolumeDB(CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr)
{
    iCallbackGetVolumeDB = aCallback;
    iPtrGetVolumeDB = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetVolumeDB();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetVolumeDB(CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr)
{
    iCallbackSetVolumeDB = aCallback;
    iPtrSetVolumeDB = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetVolumeDB();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetVolumeDBRange(CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr)
{
    iCallbackGetVolumeDBRange = aCallback;
    iPtrGetVolumeDBRange = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetVolumeDBRange();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionGetLoudness(CallbackRenderingControl1GetLoudness aCallback, void* aPtr)
{
    iCallbackGetLoudness = aCallback;
    iPtrGetLoudness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionGetLoudness();
}

void DvServiceUpnpOrgRenderingControl1C::EnableActionSetLoudness(CallbackRenderingControl1SetLoudness aCallback, void* aPtr)
{
    iCallbackSetLoudness = aCallback;
    iPtrSetLoudness = aPtr;
    DvServiceUpnpOrgRenderingControl1::EnableActionSetLoudness();
}

void DvServiceUpnpOrgRenderingControl1C::ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList)
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

void DvServiceUpnpOrgRenderingControl1C::SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName)
{
    ASSERT(iCallbackSelectPreset != NULL);
    if (0 != iCallbackSelectPreset(iPtrSelectPreset, aVersion, aInstanceID, (const char*)aPresetName.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness)
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

void DvServiceUpnpOrgRenderingControl1C::SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness)
{
    ASSERT(iCallbackSetBrightness != NULL);
    if (0 != iCallbackSetBrightness(iPtrSetBrightness, aVersion, aInstanceID, aDesiredBrightness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast)
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

void DvServiceUpnpOrgRenderingControl1C::SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast)
{
    ASSERT(iCallbackSetContrast != NULL);
    if (0 != iCallbackSetContrast(iPtrSetContrast, aVersion, aInstanceID, aDesiredContrast)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness)
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

void DvServiceUpnpOrgRenderingControl1C::SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness)
{
    ASSERT(iCallbackSetSharpness != NULL);
    if (0 != iCallbackSetSharpness(iPtrSetSharpness, aVersion, aInstanceID, aDesiredSharpness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain)
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

void DvServiceUpnpOrgRenderingControl1C::SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain)
{
    ASSERT(iCallbackSetRedVideoGain != NULL);
    if (0 != iCallbackSetRedVideoGain(iPtrSetRedVideoGain, aVersion, aInstanceID, aDesiredRedVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain)
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

void DvServiceUpnpOrgRenderingControl1C::SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain)
{
    ASSERT(iCallbackSetGreenVideoGain != NULL);
    if (0 != iCallbackSetGreenVideoGain(iPtrSetGreenVideoGain, aVersion, aInstanceID, aDesiredGreenVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain)
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

void DvServiceUpnpOrgRenderingControl1C::SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain)
{
    ASSERT(iCallbackSetBlueVideoGain != NULL);
    if (0 != iCallbackSetBlueVideoGain(iPtrSetBlueVideoGain, aVersion, aInstanceID, aDesiredBlueVideoGain)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl1C::SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel)
{
    ASSERT(iCallbackSetRedVideoBlackLevel != NULL);
    if (0 != iCallbackSetRedVideoBlackLevel(iPtrSetRedVideoBlackLevel, aVersion, aInstanceID, aDesiredRedVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl1C::SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel)
{
    ASSERT(iCallbackSetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackSetGreenVideoBlackLevel(iPtrSetGreenVideoBlackLevel, aVersion, aInstanceID, aDesiredGreenVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel)
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

void DvServiceUpnpOrgRenderingControl1C::SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel)
{
    ASSERT(iCallbackSetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackSetBlueVideoBlackLevel(iPtrSetBlueVideoBlackLevel, aVersion, aInstanceID, aDesiredBlueVideoBlackLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature)
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

void DvServiceUpnpOrgRenderingControl1C::SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature)
{
    ASSERT(iCallbackSetColorTemperature != NULL);
    if (0 != iCallbackSetColorTemperature(iPtrSetColorTemperature, aVersion, aInstanceID, aDesiredColorTemperature)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone)
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

void DvServiceUpnpOrgRenderingControl1C::SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone)
{
    ASSERT(iCallbackSetHorizontalKeystone != NULL);
    if (0 != iCallbackSetHorizontalKeystone(iPtrSetHorizontalKeystone, aVersion, aInstanceID, aDesiredHorizontalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone)
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

void DvServiceUpnpOrgRenderingControl1C::SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone)
{
    ASSERT(iCallbackSetVerticalKeystone != NULL);
    if (0 != iCallbackSetVerticalKeystone(iPtrSetVerticalKeystone, aVersion, aInstanceID, aDesiredVerticalKeystone)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute)
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

void DvServiceUpnpOrgRenderingControl1C::SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute)
{
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredMute)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume)
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

void DvServiceUpnpOrgRenderingControl1C::SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume)
{
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume)
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

void DvServiceUpnpOrgRenderingControl1C::SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume)
{
    ASSERT(iCallbackSetVolumeDB != NULL);
    if (0 != iCallbackSetVolumeDB(iPtrSetVolumeDB, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredVolume)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgRenderingControl1C::GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue)
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

void DvServiceUpnpOrgRenderingControl1C::GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness)
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

void DvServiceUpnpOrgRenderingControl1C::SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness)
{
    ASSERT(iCallbackSetLoudness != NULL);
    if (0 != iCallbackSetLoudness(iPtrSetLoudness, aVersion, aInstanceID, (const char*)aChannel.Ptr(), aDesiredLoudness)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceUpnpOrgRenderingControl1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgRenderingControl1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgRenderingControl1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService);
}

void DvServiceUpnpOrgRenderingControl1EnableActionListPresets(THandle aService, CallbackRenderingControl1ListPresets aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionListPresets(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSelectPreset(THandle aService, CallbackRenderingControl1SelectPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSelectPreset(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetBrightness(THandle aService, CallbackRenderingControl1GetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetBrightness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetBrightness(THandle aService, CallbackRenderingControl1SetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetBrightness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetContrast(THandle aService, CallbackRenderingControl1GetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetContrast(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetContrast(THandle aService, CallbackRenderingControl1SetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetContrast(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetSharpness(THandle aService, CallbackRenderingControl1GetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetSharpness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetSharpness(THandle aService, CallbackRenderingControl1SetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetSharpness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoGain(THandle aService, CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetRedVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoGain(THandle aService, CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetRedVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(THandle aService, CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetGreenVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(THandle aService, CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetGreenVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(THandle aService, CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetBlueVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(THandle aService, CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetBlueVideoGain(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(THandle aService, CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetRedVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(THandle aService, CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetRedVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(THandle aService, CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetGreenVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(THandle aService, CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetBlueVideoBlackLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetColorTemperature(THandle aService, CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetColorTemperature(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetColorTemperature(THandle aService, CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetColorTemperature(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(THandle aService, CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetHorizontalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(THandle aService, CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetHorizontalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(THandle aService, CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetVerticalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(THandle aService, CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetVerticalKeystone(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetMute(THandle aService, CallbackRenderingControl1GetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetMute(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetMute(THandle aService, CallbackRenderingControl1SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetMute(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetVolume(THandle aService, CallbackRenderingControl1GetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetVolume(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetVolume(THandle aService, CallbackRenderingControl1SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetVolume(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDB(THandle aService, CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetVolumeDB(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetVolumeDB(THandle aService, CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetVolumeDB(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(THandle aService, CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetVolumeDBRange(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionGetLoudness(THandle aService, CallbackRenderingControl1GetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionGetLoudness(aCallback, aPtr);
}

void DvServiceUpnpOrgRenderingControl1EnableActionSetLoudness(THandle aService, CallbackRenderingControl1SetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->EnableActionSetLoudness(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgRenderingControl1SetPropertyLastChange(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->SetPropertyLastChange(buf);
    return 0;
}

void DvServiceUpnpOrgRenderingControl1GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgRenderingControl1C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

