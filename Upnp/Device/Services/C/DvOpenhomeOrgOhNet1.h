/**
 * Provider for the openhome.org:OhNet:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGOHNET1_C
#define HEADER_DVOPENHOMEORGOHNET1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgOhNet1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetWebSocketPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgOhNet1EnableActionGetWebSocketPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aPort
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackOhNet1GetWebSocketPort)(void* aPtr, uint32_t aVersion, uint32_t* aPort);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderOpenhomeOrgOhNet1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgOhNet1Create
 */
DllExport void DvProviderOpenhomeOrgOhNet1Destroy(THandle aProvider);

/**
 * Register a callback for the action GetWebSocketPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgOhNet1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgOhNet1EnableActionGetWebSocketPort(THandle aProvider, CallbackOhNet1GetWebSocketPort aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGOHNET1_C

