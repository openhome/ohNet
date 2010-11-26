/**
 * Provider for the zapp.org:TestLights:1 UPnP service
 */
#ifndef HEADER_DVZAPPORGTESTLIGHTS1_C
#define HEADER_DVZAPPORGTESTLIGHTS1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderZappOrgTestLights1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetCount)(void* aPtr, uint32_t aVersion, uint32_t* aCount);
/**
 * Callback which runs when the GetRoom action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[out] aRoomName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetRoom)(void* aPtr, uint32_t aVersion, uint32_t aIndex, char** aRoomName);
/**
 * Callback which runs when the GetName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[out] aFriendlyName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetName)(void* aPtr, uint32_t aVersion, uint32_t aIndex, char** aFriendlyName);
/**
 * Callback which runs when the GetPosition action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetPosition
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[out] aX
 * @param[out] aY
 * @param[out] aZ
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetPosition)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ);
/**
 * Callback which runs when the SetColor action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionSetColor
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[in]  aColor
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1SetColor)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t aColor);
/**
 * Callback which runs when the GetColor action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetColor
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aIndex
 * @param[out] aColor
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetColor)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t* aColor);
/**
 * Callback which runs when the GetColorComponents action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestLights1EnableActionGetColorComponents
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aColor
 * @param[out] aBrightness
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestLights1GetColorComponents)(void* aPtr, uint32_t aVersion, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderZappOrgTestLights1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 */
DllExport void DvProviderZappOrgTestLights1Destroy(THandle aProvider);

/**
 * Register a callback for the action GetCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetCount(THandle aProvider, CallbackTestLights1GetCount aCallback, void* aPtr);
/**
 * Register a callback for the action GetRoom
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetRoom(THandle aProvider, CallbackTestLights1GetRoom aCallback, void* aPtr);
/**
 * Register a callback for the action GetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetName(THandle aProvider, CallbackTestLights1GetName aCallback, void* aPtr);
/**
 * Register a callback for the action GetPosition
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetPosition(THandle aProvider, CallbackTestLights1GetPosition aCallback, void* aPtr);
/**
 * Register a callback for the action SetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionSetColor(THandle aProvider, CallbackTestLights1SetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetColor(THandle aProvider, CallbackTestLights1GetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetColorComponents
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestLights1EnableActionGetColorComponents(THandle aProvider, CallbackTestLights1GetColorComponents aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTLIGHTS1_C

