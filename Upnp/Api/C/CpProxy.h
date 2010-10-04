#ifndef HEADER_SERVICE_PROXYC
#define HEADER_SERVICE_PROXYC

#include <OsTypes.h>
#include <C/Zapp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Subscribe to be notified of changes in state variables for a given service
 * on a given device.
 *
 * This can only be used if the CreateEvented constructor was used for the service.
 * The callback passed to CreateEvented will be called when the state of the first
 * variable is available.  This is a good time to register callbacks for changes in
 * the set of variables you are interested in.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 */
DllExport void CpProxyCSubscribe(THandle aHandle);

/**
 * Unsubscribe from notifications of changes in state variables for a given
 * service on a given device.
 *
 * Unsubscription is asynchronous but no more notifications will be received
 * once this function returns.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 */
DllExport void CpProxyCUnsubscribe(THandle aHandle);

/**
 * Register a callback which will run after each group of 1..n changes to
 * state variable is processed.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 * @param[in] aCallback  The callback to run
 * @param[in] aPtr       Data to be passed to the callback
 */
DllExport void CpProxyCSetPropertyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_SERVICE_PROXYC
