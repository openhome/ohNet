/**
 * Provider for the openhome.org:SubscriptionLongPoll:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1_C
#define HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgSubscriptionLongPoll1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Subscribe action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionSubscribe
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aClientId
 * @param[in]  aUdn
 * @param[in]  aService
 * @param[in]  aRequestedDuration
 * @param[out] aSid
 * @param[out] aDuration
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSubscriptionLongPoll1Subscribe)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aClientId, const char* aUdn, const char* aService, uint32_t aRequestedDuration, char** aSid, uint32_t* aDuration);
/**
 * Callback which runs when the Unsubscribe action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionUnsubscribe
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSid
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSubscriptionLongPoll1Unsubscribe)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSid);
/**
 * Callback which runs when the Renew action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionRenew
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSid
 * @param[in]  aRequestedDuration
 * @param[out] aDuration
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSubscriptionLongPoll1Renew)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSid, uint32_t aRequestedDuration, uint32_t* aDuration);
/**
 * Callback which runs when the GetPropertyUpdates action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionGetPropertyUpdates
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aClientId
 * @param[out] aUpdates
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSubscriptionLongPoll1GetPropertyUpdates)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aClientId, char** aUpdates);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgSubscriptionLongPoll1Create
 */
DllExport void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1Destroy(THandle aProvider);


/**
 * Register a callback for the action Subscribe
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionSubscribe(THandle aProvider, CallbackSubscriptionLongPoll1Subscribe aCallback, void* aPtr);
/**
 * Register a callback for the action Unsubscribe
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionUnsubscribe(THandle aProvider, CallbackSubscriptionLongPoll1Unsubscribe aCallback, void* aPtr);
/**
 * Register a callback for the action Renew
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionRenew(THandle aProvider, CallbackSubscriptionLongPoll1Renew aCallback, void* aPtr);
/**
 * Register a callback for the action GetPropertyUpdates
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgSubscriptionLongPoll1EnableActionGetPropertyUpdates(THandle aProvider, CallbackSubscriptionLongPoll1GetPropertyUpdates aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGSUBSCRIPTIONLONGPOLL1_C

