/**
 * Provider for the av.openhome.org:Info:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGINFO1_C
#define HEADER_DVAVOPENHOMEORGINFO1_C

#include <OhNetDefines.h>
#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgInfo1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Counters action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionCounters
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aTrackCount
 * @param[out] aDetailsCount
 * @param[out] aMetatextCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Counters)(void* aPtr, uint32_t aVersion, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount);
/**
 * Callback which runs when the Track action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionTrack
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Track)(void* aPtr, uint32_t aVersion, char** aUri, char** aMetadata);
/**
 * Callback which runs when the Details action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionDetails
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aDuration
 * @param[out] aBitRate
 * @param[out] aBitDepth
 * @param[out] aSampleRate
 * @param[out] aLossless
 * @param[out] aCodecName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Details)(void* aPtr, uint32_t aVersion, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName);
/**
 * Callback which runs when the Metatext action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionMetatext
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackInfo1Metatext)(void* aPtr, uint32_t aVersion, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderAvOpenhomeOrgInfo1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 */
DllExport void DvProviderAvOpenhomeOrgInfo1Destroy(THandle aProvider);

/**
 * Register a callback for the action Counters
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr);
/**
 * Register a callback for the action Track
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr);
/**
 * Register a callback for the action Details
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr);
/**
 * Register a callback for the action Metatext
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr);

/**
 * Set the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DetailsCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DetailsCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the MetatextCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the MetatextCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Uri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Uri property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Lossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Lossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the CodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyCodecName(THandle aProvider, char** aValue);
/**
 * Set the value of the Metatext property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metatext property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgInfo1GetPropertyMetatext(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGINFO1_C

