/**
 * Provider for the openhome.org:TestColorLight:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGTESTCOLORLIGHT1_C
#define HEADER_DVOPENHOMEORGTESTCOLORLIGHT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgTestColorLight1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestColorLight1EnableActionGetName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aFriendlyName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestColorLight1GetName)(void* aPtr, uint32_t aVersion, char** aFriendlyName);
/**
 * Callback which runs when the SetColor action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestColorLight1EnableActionSetColor
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRed
 * @param[in]  aGreen
 * @param[in]  aBlue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestColorLight1SetColor)(void* aPtr, uint32_t aVersion, uint32_t aRed, uint32_t aGreen, uint32_t aBlue);
/**
 * Callback which runs when the GetColor action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestColorLight1EnableActionGetColor
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestColorLight1GetColor)(void* aPtr, uint32_t aVersion, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);
/**
 * Callback which runs when the GetMaxColors action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestColorLight1EnableActionGetMaxColors
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestColorLight1GetMaxColors)(void* aPtr, uint32_t aVersion, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderOpenhomeOrgTestColorLight1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestColorLight1Create
 */
DllExport void DvProviderOpenhomeOrgTestColorLight1Destroy(THandle aProvider);

/**
 * Register a callback for the action GetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestColorLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestColorLight1EnableActionGetName(THandle aProvider, CallbackTestColorLight1GetName aCallback, void* aPtr);
/**
 * Register a callback for the action SetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestColorLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestColorLight1EnableActionSetColor(THandle aProvider, CallbackTestColorLight1SetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestColorLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestColorLight1EnableActionGetColor(THandle aProvider, CallbackTestColorLight1GetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetMaxColors
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestColorLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestColorLight1EnableActionGetMaxColors(THandle aProvider, CallbackTestColorLight1GetMaxColors aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGTESTCOLORLIGHT1_C

