/**
 * Provider for the linn.co.uk:Time:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKTIME1_C
#define HEADER_DVLINNCOUKTIME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkTime1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Time action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkTime1EnableActionTime
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaTrackCount
 * @param[out] aaDuration
 * @param[out] aaSeconds
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTime1Time)(void* aPtr, uint32_t aVersion, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkTime1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 */
DllExport void DvProviderLinnCoUkTime1Destroy(THandle aProvider);

/**
 * Register a callback for the action Time
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkTime1EnableActionTime(THandle aProvider, CallbackTime1Time aCallback, void* aPtr);

/**
 * Set the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkTime1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkTime1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkTime1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkTime1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Seconds property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Seconds property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKTIME1_C

