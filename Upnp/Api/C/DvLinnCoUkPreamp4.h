#ifndef HEADER_DVLINNCOUKPREAMP4_C
#define HEADER_DVLINNCOUKPREAMP4_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackPreamp4VolumeInc)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackPreamp4VolumeDec)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackPreamp4SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aaVolume);
typedef int32_t (*CallbackPreamp4Volume)(void* aPtr, uint32_t aVersion, uint32_t* aaVolume);
typedef int32_t (*CallbackPreamp4SetMute)(void* aPtr, uint32_t aVersion, uint32_t aaMute);
typedef int32_t (*CallbackPreamp4Mute)(void* aPtr, uint32_t aVersion, uint32_t* aaMute);
typedef int32_t (*CallbackPreamp4SetBalance)(void* aPtr, uint32_t aVersion, int32_t aaBalance);
typedef int32_t (*CallbackPreamp4Balance)(void* aPtr, uint32_t aVersion, int32_t* aaBalance);
typedef int32_t (*CallbackPreamp4SetVolumeLimit)(void* aPtr, uint32_t aVersion, uint32_t aaVolumeLimit);
typedef int32_t (*CallbackPreamp4VolumeLimit)(void* aPtr, uint32_t aVersion, uint32_t* aaVolumeLimit);
typedef int32_t (*CallbackPreamp4SetStartupVolume)(void* aPtr, uint32_t aVersion, uint32_t aaStartupVolume);
typedef int32_t (*CallbackPreamp4StartupVolume)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupVolume);
typedef int32_t (*CallbackPreamp4SetStartupVolumeEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaStartupVolumeEnabled);
typedef int32_t (*CallbackPreamp4StartupVolumeEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupVolumeEnabled);

DllExport THandle DvProviderLinnCoUkPreamp4Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkPreamp4Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeInc(THandle aProvider, CallbackPreamp4VolumeInc aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeDec(THandle aProvider, CallbackPreamp4VolumeDec aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetVolume(THandle aProvider, CallbackPreamp4SetVolume aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolume(THandle aProvider, CallbackPreamp4Volume aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetMute(THandle aProvider, CallbackPreamp4SetMute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionMute(THandle aProvider, CallbackPreamp4Mute aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetBalance(THandle aProvider, CallbackPreamp4SetBalance aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionBalance(THandle aProvider, CallbackPreamp4Balance aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aProvider, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(THandle aProvider, CallbackPreamp4VolumeLimit aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aProvider, CallbackPreamp4SetStartupVolume aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionStartupVolume(THandle aProvider, CallbackPreamp4StartupVolume aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aProvider, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aProvider, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyVolume(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyMute(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyBalance(THandle aProvider, int32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPREAMP4_C

