/**
 * Provider for the linn.co.uk:Delay:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKDELAY1_C
#define HEADER_DVLINNCOUKDELAY1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the PresetXml action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionPresetXml
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaPresetXml
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1PresetXml)(void* aPtr, uint32_t aVersion, char** aaPresetXml);
/**
 * Callback which runs when the PresetIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionPresetIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1PresetIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaIndex);
/**
 * Callback which runs when the SetPresetIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionSetPresetIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1SetPresetIndex)(void* aPtr, uint32_t aVersion, uint32_t aaIndex);
/**
 * Callback which runs when the SetPresetDelay action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionSetPresetDelay
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 * @param[in]  aaDelay
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1SetPresetDelay)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, uint32_t aaDelay);
/**
 * Callback which runs when the SetPresetVisible action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionSetPresetVisible
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 * @param[in]  aaVisible
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1SetPresetVisible)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, uint32_t aaVisible);
/**
 * Callback which runs when the SetPresetName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionSetPresetName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 * @param[in]  aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1SetPresetName)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, const char* aaName);
/**
 * Callback which runs when the DelayMinimum action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionDelayMinimum
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaDelay
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1DelayMinimum)(void* aPtr, uint32_t aVersion, uint32_t* aaDelay);
/**
 * Callback which runs when the DelayMaximum action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionDelayMaximum
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaDelay
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1DelayMaximum)(void* aPtr, uint32_t aVersion, uint32_t* aaDelay);
/**
 * Callback which runs when the PresetCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDelay1EnableActionPresetCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDelay1PresetCount)(void* aPtr, uint32_t aVersion, uint32_t* aaCount);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkDelay1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 */
DllExport void DvProviderLinnCoUkDelay1Destroy(THandle aProvider);

/**
 * Register a callback for the action PresetXml
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionPresetXml(THandle aProvider, CallbackDelay1PresetXml aCallback, void* aPtr);
/**
 * Register a callback for the action PresetIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionPresetIndex(THandle aProvider, CallbackDelay1PresetIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetPresetIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetIndex(THandle aProvider, CallbackDelay1SetPresetIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetPresetDelay
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetDelay(THandle aProvider, CallbackDelay1SetPresetDelay aCallback, void* aPtr);
/**
 * Register a callback for the action SetPresetVisible
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetVisible(THandle aProvider, CallbackDelay1SetPresetVisible aCallback, void* aPtr);
/**
 * Register a callback for the action SetPresetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionSetPresetName(THandle aProvider, CallbackDelay1SetPresetName aCallback, void* aPtr);
/**
 * Register a callback for the action DelayMinimum
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionDelayMinimum(THandle aProvider, CallbackDelay1DelayMinimum aCallback, void* aPtr);
/**
 * Register a callback for the action DelayMaximum
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionDelayMaximum(THandle aProvider, CallbackDelay1DelayMaximum aCallback, void* aPtr);
/**
 * Register a callback for the action PresetCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDelay1EnableActionPresetCount(THandle aProvider, CallbackDelay1PresetCount aCallback, void* aPtr);

/**
 * Set the value of the PresetXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDelay1SetPropertyPresetXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PresetXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkDelay1GetPropertyPresetXml(THandle aProvider, char** aValue);
/**
 * Set the value of the PresetIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDelay1SetPropertyPresetIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PresetIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDelay1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDelay1GetPropertyPresetIndex(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDELAY1_C

