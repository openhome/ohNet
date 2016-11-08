/**
 * Proxy for openhome.org:SubscriptionLongPoll:1
 */
#ifndef HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1_C
#define HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>
#include <OpenHome/Net/C/Async.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CpProxyOpenhomeOrgSubscriptionLongPoll1
 * @ingroup Proxies
 * @{
 */

/**
 * Constructor.
 * Creates an instance of CpProxyOpenhomeOrgSubscriptionLongPoll1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 */
DllExport void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aClientId
 * @param[in]  aUdn
 * @param[in]  aService
 * @param[in]  aRequestedDuration
 * @param[out] aSid
 * @param[out] aDuration
 *
 * @return  0 if the function succeeded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncSubscribe(THandle aHandle, const char* aClientId, const char* aUdn, const char* aService, uint32_t aRequestedDuration, char** aSid, uint32_t* aDuration);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aClientId
 * @param[in]  aUdn
 * @param[in]  aService
 * @param[in]  aRequestedDuration
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginSubscribe(THandle aHandle, const char* aClientId, const char* aUdn, const char* aService, uint32_t aRequestedDuration, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSid
 * @param[out] aDuration
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndSubscribe(THandle aHandle, OhNetHandleAsync aAsync, char** aSid, uint32_t* aDuration);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aSid
 *
 * @return  0 if the function succeeded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncUnsubscribe(THandle aHandle, const char* aSid);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aSid
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginUnsubscribe(THandle aHandle, const char* aSid, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndUnsubscribe(THandle aHandle, OhNetHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aSid
 * @param[in]  aRequestedDuration
 * @param[out] aDuration
 *
 * @return  0 if the function succeeded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncRenew(THandle aHandle, const char* aSid, uint32_t aRequestedDuration, uint32_t* aDuration);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aSid
 * @param[in]  aRequestedDuration
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginRenew(THandle aHandle, const char* aSid, uint32_t aRequestedDuration, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aDuration
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndRenew(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aDuration);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aClientId
 * @param[out] aUpdates
 *
 * @return  0 if the function succeeded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1SyncGetPropertyUpdates(THandle aHandle, const char* aClientId, char** aUpdates);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aClientId
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1BeginGetPropertyUpdates(THandle aHandle, const char* aClientId, OhNetCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyOpenhomeOrgSubscriptionLongPoll1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aUpdates
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t STDCALL CpProxyOpenhomeOrgSubscriptionLongPoll1EndGetPropertyUpdates(THandle aHandle, OhNetHandleAsync aAsync, char** aUpdates);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1_C

