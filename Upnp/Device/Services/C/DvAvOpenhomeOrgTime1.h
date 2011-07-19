/**
 * Provider for the av.openhome.org:Time:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGTIME1_C
#define HEADER_DVAVOPENHOMEORGTIME1_C

#include <OhNetDefines.h>
#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgTime1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Time action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgTime1EnableActionTime
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aTrackCount
 * @param[out] aDuration
 * @param[out] aSeconds
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTime1Time)(void* aPtr, uint32_t aVersion, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgTime1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgTime1Destroy(THandle aProvider);

/**
 * Register a callback for the action Time
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgTime1EnableActionTime(THandle aProvider, CallbackTime1Time aCallback, void* aPtr);

/**
 * Set the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertyTrackCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertyTrackCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertyDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Duration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertyDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Seconds property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgTime1SetPropertySeconds(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Seconds property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgTime1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgTime1GetPropertySeconds(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGTIME1_C

