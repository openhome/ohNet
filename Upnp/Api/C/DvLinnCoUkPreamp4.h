/**
 * Provider for the linn.co.uk:Preamp:4 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPREAMP4_C
#define HEADER_DVLINNCOUKPREAMP4_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the VolumeInc action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionVolumeInc
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4VolumeInc)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the VolumeDec action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionVolumeDec
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4VolumeDec)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SetVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aaVolume);
/**
 * Callback which runs when the Volume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4Volume)(void* aPtr, uint32_t aVersion, uint32_t* aaVolume);
/**
 * Callback which runs when the SetMute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetMute)(void* aPtr, uint32_t aVersion, uint32_t aaMute);
/**
 * Callback which runs when the Mute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4Mute)(void* aPtr, uint32_t aVersion, uint32_t* aaMute);
/**
 * Callback which runs when the SetBalance action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetBalance
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaBalance
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetBalance)(void* aPtr, uint32_t aVersion, int32_t aaBalance);
/**
 * Callback which runs when the Balance action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionBalance
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaBalance
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4Balance)(void* aPtr, uint32_t aVersion, int32_t* aaBalance);
/**
 * Callback which runs when the SetVolumeLimit action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaVolumeLimit
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetVolumeLimit)(void* aPtr, uint32_t aVersion, uint32_t aaVolumeLimit);
/**
 * Callback which runs when the VolumeLimit action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionVolumeLimit
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaVolumeLimit
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4VolumeLimit)(void* aPtr, uint32_t aVersion, uint32_t* aaVolumeLimit);
/**
 * Callback which runs when the SetStartupVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStartupVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetStartupVolume)(void* aPtr, uint32_t aVersion, uint32_t aaStartupVolume);
/**
 * Callback which runs when the StartupVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionStartupVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStartupVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4StartupVolume)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupVolume);
/**
 * Callback which runs when the SetStartupVolumeEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStartupVolumeEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4SetStartupVolumeEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaStartupVolumeEnabled);
/**
 * Callback which runs when the StartupVolumeEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStartupVolumeEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPreamp4StartupVolumeEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupVolumeEnabled);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkPreamp4Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 */
DllExport void DvProviderLinnCoUkPreamp4Destroy(THandle aProvider);

/**
 * Register a callback for the action VolumeInc
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeInc(THandle aProvider, CallbackPreamp4VolumeInc aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeDec
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeDec(THandle aProvider, CallbackPreamp4VolumeDec aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetVolume(THandle aProvider, CallbackPreamp4SetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action Volume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolume(THandle aProvider, CallbackPreamp4Volume aCallback, void* aPtr);
/**
 * Register a callback for the action SetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetMute(THandle aProvider, CallbackPreamp4SetMute aCallback, void* aPtr);
/**
 * Register a callback for the action Mute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionMute(THandle aProvider, CallbackPreamp4Mute aCallback, void* aPtr);
/**
 * Register a callback for the action SetBalance
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetBalance(THandle aProvider, CallbackPreamp4SetBalance aCallback, void* aPtr);
/**
 * Register a callback for the action Balance
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionBalance(THandle aProvider, CallbackPreamp4Balance aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolumeLimit
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetVolumeLimit(THandle aProvider, CallbackPreamp4SetVolumeLimit aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeLimit
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionVolumeLimit(THandle aProvider, CallbackPreamp4VolumeLimit aCallback, void* aPtr);
/**
 * Register a callback for the action SetStartupVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolume(THandle aProvider, CallbackPreamp4SetStartupVolume aCallback, void* aPtr);
/**
 * Register a callback for the action StartupVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionStartupVolume(THandle aProvider, CallbackPreamp4StartupVolume aCallback, void* aPtr);
/**
 * Register a callback for the action SetStartupVolumeEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionSetStartupVolumeEnabled(THandle aProvider, CallbackPreamp4SetStartupVolumeEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action StartupVolumeEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPreamp4EnableActionStartupVolumeEnabled(THandle aProvider, CallbackPreamp4StartupVolumeEnabled aCallback, void* aPtr);

/**
 * Set the value of the Volume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Volume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyVolume(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Mute property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Mute property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyMute(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Balance property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Balance property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyBalance(THandle aProvider, int32_t* aValue);
/**
 * Set the value of the VolumeLimit property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeLimit property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the StartupVolume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StartupVolume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyStartupVolume(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the StartupVolumeEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkPreamp4SetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StartupVolumeEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkPreamp4Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkPreamp4GetPropertyStartupVolumeEnabled(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPREAMP4_C

