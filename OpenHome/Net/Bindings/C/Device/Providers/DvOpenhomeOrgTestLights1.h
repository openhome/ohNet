/**
 * Provider for the openhome.org:TestLights:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGTESTLIGHTS1_C
#define HEADER_DVOPENHOMEORGTESTLIGHTS1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgTestLights1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetCount action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetCount
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetCount)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aCount);
/**
 * Callback which runs when the GetRoom action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetRoom
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[out] aRoomName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetRoom)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, char** aRoomName);
/**
 * Callback which runs when the GetName action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetName
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[out] aFriendlyName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetName)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, char** aFriendlyName);
/**
 * Callback which runs when the GetPosition action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetPosition
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[out] aX
 * @param[out] aY
 * @param[out] aZ
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetPosition)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ);
/**
 * Callback which runs when the SetColor action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionSetColor
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[in]  aColor
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1SetColor)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, uint32_t aColor);
/**
 * Callback which runs when the GetColor action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetColor
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[out] aColor
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetColor)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, uint32_t* aColor);
/**
 * Callback which runs when the GetColorComponents action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestLights1EnableActionGetColorComponents
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aColor
 * @param[out] aBrightness
 * @param[out] aRed
 * @param[out] aGreen
 * @param[out] aBlue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestLights1GetColorComponents)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderOpenhomeOrgTestLights1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1Destroy(THandle aProvider);


/**
 * Register a callback for the action GetCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetCount(THandle aProvider, CallbackTestLights1GetCount aCallback, void* aPtr);
/**
 * Register a callback for the action GetRoom
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetRoom(THandle aProvider, CallbackTestLights1GetRoom aCallback, void* aPtr);
/**
 * Register a callback for the action GetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetName(THandle aProvider, CallbackTestLights1GetName aCallback, void* aPtr);
/**
 * Register a callback for the action GetPosition
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetPosition(THandle aProvider, CallbackTestLights1GetPosition aCallback, void* aPtr);
/**
 * Register a callback for the action SetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionSetColor(THandle aProvider, CallbackTestLights1SetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetColor
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetColor(THandle aProvider, CallbackTestLights1GetColor aCallback, void* aPtr);
/**
 * Register a callback for the action GetColorComponents
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestLights1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestLights1EnableActionGetColorComponents(THandle aProvider, CallbackTestLights1GetColorComponents aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGTESTLIGHTS1_C

