/**
 * Provider for the av.openhome.org:Info:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGINFO1_C
#define HEADER_DVAVOPENHOMEORGINFO1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

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
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionCounters
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aTrackCount
 * @param[out] aDetailsCount
 * @param[out] aMetatextCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackInfo1Counters)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount);
/**
 * Callback which runs when the Track action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionTrack
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackInfo1Track)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aUri, char** aMetadata);
/**
 * Callback which runs when the Details action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionDetails
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aDuration
 * @param[out] aBitRate
 * @param[out] aBitDepth
 * @param[out] aSampleRate
 * @param[out] aLossless
 * @param[out] aCodecName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackInfo1Details)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName);
/**
 * Callback which runs when the Metatext action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgInfo1EnableActionMetatext
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackInfo1Metatext)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgInfo1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1Destroy(THandle aProvider);

/**
 * Enable the TrackCount property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyTrackCount(THandle aProvider);
/**
 * Enable the DetailsCount property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyDetailsCount(THandle aProvider);
/**
 * Enable the MetatextCount property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatextCount(THandle aProvider);
/**
 * Enable the Uri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyUri(THandle aProvider);
/**
 * Enable the Metadata property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetadata(THandle aProvider);
/**
 * Enable the Duration property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyDuration(THandle aProvider);
/**
 * Enable the BitRate property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyBitRate(THandle aProvider);
/**
 * Enable the BitDepth property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyBitDepth(THandle aProvider);
/**
 * Enable the SampleRate property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertySampleRate(THandle aProvider);
/**
 * Enable the Lossless property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyLossless(THandle aProvider);
/**
 * Enable the CodecName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyCodecName(THandle aProvider);
/**
 * Enable the Metatext property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatext(THandle aProvider);

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
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionCounters(THandle aProvider, CallbackInfo1Counters aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionTrack(THandle aProvider, CallbackInfo1Track aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionDetails(THandle aProvider, CallbackInfo1Details aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1EnableActionMetatext(THandle aProvider, CallbackInfo1Metatext aCallback, void* aPtr);

/**
 * Set the value of the TrackCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyTrackCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyTrackCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DetailsCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyDetailsCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyDetailsCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DetailsCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyDetailsCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyDetailsCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the MetatextCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatextCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetatextCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the MetatextCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatextCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetatextCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the Duration property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyDuration has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Duration property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyDuration has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitRate property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyBitRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitRate property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyBitRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyBitRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BitDepth property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyBitDepth has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BitDepth property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyBitDepth has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyBitDepth(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SampleRate property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertySampleRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertySampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SampleRate property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertySampleRate has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertySampleRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Lossless property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyLossless has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Lossless property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyLossless has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyLossless(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the CodecName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyCodecName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CodecName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyCodecName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyCodecName(THandle aProvider, char** aValue);
/**
 * Set the value of the Metatext property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatext has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgInfo1SetPropertyMetatext(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metatext property
 *
 * Can only be called if DvProviderAvOpenhomeOrgInfo1EnablePropertyMetatext has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgInfo1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgInfo1GetPropertyMetatext(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGINFO1_C

