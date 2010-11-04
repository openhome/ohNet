#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2_C
#define HEADER_DVUPNPORGRENDERINGCONTROL2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackRenderingControl2ListPresets)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentPresetNameList);
typedef int32_t (*CallbackRenderingControl2SelectPreset)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aPresetName);
typedef int32_t (*CallbackRenderingControl2GetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
typedef int32_t (*CallbackRenderingControl2SetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
typedef int32_t (*CallbackRenderingControl2GetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentContrast);
typedef int32_t (*CallbackRenderingControl2SetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
typedef int32_t (*CallbackRenderingControl2GetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
typedef int32_t (*CallbackRenderingControl2SetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
typedef int32_t (*CallbackRenderingControl2GetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
typedef int32_t (*CallbackRenderingControl2SetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
typedef int32_t (*CallbackRenderingControl2GetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
typedef int32_t (*CallbackRenderingControl2SetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
typedef int32_t (*CallbackRenderingControl2GetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
typedef int32_t (*CallbackRenderingControl2SetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
typedef int32_t (*CallbackRenderingControl2GetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2SetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl2GetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
typedef int32_t (*CallbackRenderingControl2SetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
typedef int32_t (*CallbackRenderingControl2GetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl2SetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl2GetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
typedef int32_t (*CallbackRenderingControl2SetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
typedef int32_t (*CallbackRenderingControl2GetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
typedef int32_t (*CallbackRenderingControl2SetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
typedef int32_t (*CallbackRenderingControl2GetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl2SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl2GetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl2SetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl2GetVolumeDBRange)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
typedef int32_t (*CallbackRenderingControl2GetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
typedef int32_t (*CallbackRenderingControl2SetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);
typedef int32_t (*CallbackRenderingControl2GetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
typedef int32_t (*CallbackRenderingControl2SetStateVariables)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);

DllExport THandle DvProviderUpnpOrgRenderingControl2Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgRenderingControl2Destroy(THandle aProvider);

DllExport void DvProviderUpnpOrgRenderingControl2EnableActionListPresets(THandle aProvider, CallbackRenderingControl2ListPresets aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl2SelectPreset aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl2GetBrightness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl2SetBrightness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(THandle aProvider, CallbackRenderingControl2GetContrast aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(THandle aProvider, CallbackRenderingControl2SetContrast aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl2GetSharpness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl2SetSharpness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetMute(THandle aProvider, CallbackRenderingControl2GetMute aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetMute(THandle aProvider, CallbackRenderingControl2SetMute aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(THandle aProvider, CallbackRenderingControl2GetVolume aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(THandle aProvider, CallbackRenderingControl2SetVolume aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl2GetLoudness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl2SetLoudness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aProvider, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aProvider, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2_C

