#ifndef HEADER_DVLINNCOUKJUKEBOX1_C
#define HEADER_DVLINNCOUKJUKEBOX1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackJukebox1SetPresetPrefix)(void* aPtr, uint32_t aVersion, const char* aaUri);
typedef int32_t (*CallbackJukebox1PresetPrefix)(void* aPtr, uint32_t aVersion, char** aaUri);
typedef int32_t (*CallbackJukebox1SetAlbumArtFileName)(void* aPtr, uint32_t aVersion, const char* aaName);
typedef int32_t (*CallbackJukebox1AlbumArtFileName)(void* aPtr, uint32_t aVersion, char** aaName);
typedef int32_t (*CallbackJukebox1SetCurrentPreset)(void* aPtr, uint32_t aVersion, uint32_t aaPreset);
typedef int32_t (*CallbackJukebox1CurrentPreset)(void* aPtr, uint32_t aVersion, uint32_t* aaPreset);
typedef int32_t (*CallbackJukebox1PresetMetaData)(void* aPtr, uint32_t aVersion, uint32_t aaPreset, char** aaMetaData);
typedef int32_t (*CallbackJukebox1LoadManifest)(void* aPtr, uint32_t aVersion, uint32_t* aaTotalPresets);

DllExport THandle DvServiceLinnCoUkJukebox1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkJukebox1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkJukebox1EnableActionSetPresetPrefix(THandle aService, CallbackJukebox1SetPresetPrefix aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionPresetPrefix(THandle aService, CallbackJukebox1PresetPrefix aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionSetAlbumArtFileName(THandle aService, CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionAlbumArtFileName(THandle aService, CallbackJukebox1AlbumArtFileName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionSetCurrentPreset(THandle aService, CallbackJukebox1SetCurrentPreset aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionCurrentPreset(THandle aService, CallbackJukebox1CurrentPreset aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionPresetMetaData(THandle aService, CallbackJukebox1PresetMetaData aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkJukebox1EnableActionLoadManifest(THandle aService, CallbackJukebox1LoadManifest aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkJukebox1SetPropertyCurrentPreset(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkJukebox1GetPropertyCurrentPreset(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkJukebox1SetPropertyPresetPrefix(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkJukebox1GetPropertyPresetPrefix(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkJukebox1SetPropertyAlbumArtFileName(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkJukebox1GetPropertyAlbumArtFileName(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKJUKEBOX1_C

