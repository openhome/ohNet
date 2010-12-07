/**
 * Provider for the linn.co.uk:Info:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKINFO1_C
#define HEADER_DVLINNCOUKINFO1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkInfo1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Counters action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkInfo1EnableActionCounters
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaTrackCount
 * @param[out] aaDetailsCount
 * @param[out] aaMetatextCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Counters)(void* aPtr, uint32_t aVersion, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount);
/**
 * Callback which runs when the Track action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkInfo1EnableActionTrack
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaUri
 * @param[out] aaMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Track)(void* aPtr, uint32_t aVersion, char** aaUri, char** aaMetadata);
/**
 * Callback which runs when the Details action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkInfo1EnableActionDetails
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaDuration
 * @param[out] aaBitRate
 * @param[out] aaBitDepth
 * @param[out] aaSampleRate
 * @param[out] aaLossless
 * @param[out] aaCodecName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Details)(void* aPtr, uint32_t aVersion, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName);
/**
 * Callback which runs when the Metatext action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkInfo1EnableActionMetatext
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaMetatext
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Metatext)(void* aPtr, uint32_t aVersion, char** aaMetatext);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkInfo1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 */
DllExport void DvProviderLinnCoUkInfo1Destroy(THandle aProvider);

/**
 * Register a callback for the action Counters
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr);
/**
 * Register a callback for the action Track
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr);
/**
 * Register a callback for the action Details
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr);
/**
 * Register a callback for the action Metatext
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr);

/**
 * Set the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DetailsCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DetailsCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the MetatextCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the MetatextCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Uri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Uri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Lossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Lossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the CodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyCodecName(THandle aProvider, char** aValue);
/**
 * Set the value of the Metatext property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metatext property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkInfo1GetPropertyMetatext(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKINFO1_C

