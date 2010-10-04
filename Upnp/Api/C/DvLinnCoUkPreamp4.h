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

DllExport THandle DvServiceLinnCoUkPreamp4Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkPreamp4Destroy(THandle aService);

DllExport void DvServiceLinnCoUkPreamp4EnableActionVolumeInc(THandle aService, CallbackPreamp4VolumeInc aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionVolumeDec(THandle aService, CallbackPreamp4VolumeDec aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetVolume(THandle aService, CallbackPreamp4SetVolume aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionVolume(THandle aService, CallbackPreamp4Volume aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetMute(THandle aService, CallbackPreamp4SetMute aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionMute(THandle aService, CallbackPreamp4Mute aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetBalance(THandle aService, CallbackPreamp4SetBalance aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionBalance(THandle aService, CallbackPreamp4Balance aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aService, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionVolumeLimit(THandle aService, CallbackPreamp4VolumeLimit aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aService, CallbackPreamp4SetStartupVolume aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionStartupVolume(THandle aService, CallbackPreamp4StartupVolume aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aService, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aService, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyVolume(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyVolume(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyMute(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyMute(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyBalance(THandle aService, int32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyBalance(THandle aService, int32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyStartupVolume(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyStartupVolume(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPREAMP4_C

