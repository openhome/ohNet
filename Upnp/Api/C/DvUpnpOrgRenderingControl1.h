#ifndef HEADER_DVUPNPORGRENDERINGCONTROL1_C
#define HEADER_DVUPNPORGRENDERINGCONTROL1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackRenderingControl1ListPresets)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, char** aCurrentPresetNameList);
typedef int32_t (*CallbackRenderingControl1SelectPreset)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aPresetName);
typedef int32_t (*CallbackRenderingControl1GetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
typedef int32_t (*CallbackRenderingControl1SetBrightness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
typedef int32_t (*CallbackRenderingControl1GetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentContrast);
typedef int32_t (*CallbackRenderingControl1SetContrast)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
typedef int32_t (*CallbackRenderingControl1GetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
typedef int32_t (*CallbackRenderingControl1SetSharpness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
typedef int32_t (*CallbackRenderingControl1GetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
typedef int32_t (*CallbackRenderingControl1SetRedVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
typedef int32_t (*CallbackRenderingControl1GetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
typedef int32_t (*CallbackRenderingControl1SetGreenVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
typedef int32_t (*CallbackRenderingControl1GetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
typedef int32_t (*CallbackRenderingControl1SetBlueVideoGain)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
typedef int32_t (*CallbackRenderingControl1GetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetRedVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetGreenVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1SetBlueVideoBlackLevel)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
typedef int32_t (*CallbackRenderingControl1GetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
typedef int32_t (*CallbackRenderingControl1SetColorTemperature)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
typedef int32_t (*CallbackRenderingControl1GetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl1SetHorizontalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
typedef int32_t (*CallbackRenderingControl1GetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
typedef int32_t (*CallbackRenderingControl1SetVerticalKeystone)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
typedef int32_t (*CallbackRenderingControl1GetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
typedef int32_t (*CallbackRenderingControl1SetMute)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
typedef int32_t (*CallbackRenderingControl1GetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl1SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl1GetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
typedef int32_t (*CallbackRenderingControl1SetVolumeDB)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
typedef int32_t (*CallbackRenderingControl1GetVolumeDBRange)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
typedef int32_t (*CallbackRenderingControl1GetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
typedef int32_t (*CallbackRenderingControl1SetLoudness)(void* aPtr, uint32_t aVersion, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);

DllExport THandle DvProviderUpnpOrgRenderingControl1Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgRenderingControl1Destroy(THandle aProvider);

DllExport void DvProviderUpnpOrgRenderingControl1EnableActionListPresets(THandle aProvider, CallbackRenderingControl1ListPresets aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl1SelectPreset aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl1GetBrightness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl1SetBrightness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetContrast(THandle aProvider, CallbackRenderingControl1GetContrast aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetContrast(THandle aProvider, CallbackRenderingControl1SetContrast aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl1GetSharpness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl1SetSharpness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetMute(THandle aProvider, CallbackRenderingControl1GetMute aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetMute(THandle aProvider, CallbackRenderingControl1SetMute aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolume(THandle aProvider, CallbackRenderingControl1GetVolume aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVolume(THandle aProvider, CallbackRenderingControl1SetVolume aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl1GetLoudness aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgRenderingControl1EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl1SetLoudness aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgRenderingControl1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgRenderingControl1GetPropertyLastChange(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL1_C

