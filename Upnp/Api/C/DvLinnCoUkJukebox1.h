/**
 * Provider for the linn.co.uk:Jukebox:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKJUKEBOX1_C
#define HEADER_DVLINNCOUKJUKEBOX1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the SetPresetPrefix action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionSetPresetPrefix
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1SetPresetPrefix)(void* aPtr, uint32_t aVersion, const char* aaUri);
/**
 * Callback which runs when the PresetPrefix action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionPresetPrefix
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1PresetPrefix)(void* aPtr, uint32_t aVersion, char** aaUri);
/**
 * Callback which runs when the SetAlbumArtFileName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionSetAlbumArtFileName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1SetAlbumArtFileName)(void* aPtr, uint32_t aVersion, const char* aaName);
/**
 * Callback which runs when the AlbumArtFileName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionAlbumArtFileName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1AlbumArtFileName)(void* aPtr, uint32_t aVersion, char** aaName);
/**
 * Callback which runs when the SetCurrentPreset action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionSetCurrentPreset
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaPreset
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1SetCurrentPreset)(void* aPtr, uint32_t aVersion, uint32_t aaPreset);
/**
 * Callback which runs when the CurrentPreset action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionCurrentPreset
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaPreset
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1CurrentPreset)(void* aPtr, uint32_t aVersion, uint32_t* aaPreset);
/**
 * Callback which runs when the PresetMetaData action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionPresetMetaData
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaPreset
 * @param[out] aaMetaData
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1PresetMetaData)(void* aPtr, uint32_t aVersion, uint32_t aaPreset, char** aaMetaData);
/**
 * Callback which runs when the LoadManifest action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkJukebox1EnableActionLoadManifest
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaTotalPresets
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackJukebox1LoadManifest)(void* aPtr, uint32_t aVersion, uint32_t* aaTotalPresets);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkJukebox1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 */
DllExport void DvProviderLinnCoUkJukebox1Destroy(THandle aProvider);

/**
 * Register a callback for the action SetPresetPrefix
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionSetPresetPrefix(THandle aProvider, CallbackJukebox1SetPresetPrefix aCallback, void* aPtr);
/**
 * Register a callback for the action PresetPrefix
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionPresetPrefix(THandle aProvider, CallbackJukebox1PresetPrefix aCallback, void* aPtr);
/**
 * Register a callback for the action SetAlbumArtFileName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionSetAlbumArtFileName(THandle aProvider, CallbackJukebox1SetAlbumArtFileName aCallback, void* aPtr);
/**
 * Register a callback for the action AlbumArtFileName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionAlbumArtFileName(THandle aProvider, CallbackJukebox1AlbumArtFileName aCallback, void* aPtr);
/**
 * Register a callback for the action SetCurrentPreset
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionSetCurrentPreset(THandle aProvider, CallbackJukebox1SetCurrentPreset aCallback, void* aPtr);
/**
 * Register a callback for the action CurrentPreset
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionCurrentPreset(THandle aProvider, CallbackJukebox1CurrentPreset aCallback, void* aPtr);
/**
 * Register a callback for the action PresetMetaData
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionPresetMetaData(THandle aProvider, CallbackJukebox1PresetMetaData aCallback, void* aPtr);
/**
 * Register a callback for the action LoadManifest
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkJukebox1EnableActionLoadManifest(THandle aProvider, CallbackJukebox1LoadManifest aCallback, void* aPtr);

/**
 * Set the value of the CurrentPreset property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkJukebox1SetPropertyCurrentPreset(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CurrentPreset property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkJukebox1GetPropertyCurrentPreset(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the PresetPrefix property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkJukebox1SetPropertyPresetPrefix(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PresetPrefix property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkJukebox1GetPropertyPresetPrefix(THandle aProvider, char** aValue);
/**
 * Set the value of the AlbumArtFileName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkJukebox1SetPropertyAlbumArtFileName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the AlbumArtFileName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkJukebox1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkJukebox1GetPropertyAlbumArtFileName(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKJUKEBOX1_C

