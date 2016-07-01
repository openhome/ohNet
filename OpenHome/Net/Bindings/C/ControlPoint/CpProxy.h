#ifndef HEADER_SERVICE_PROXYC
#define HEADER_SERVICE_PROXYC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/C/Service.h>
#include <OpenHome/Net/C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a proxy that will be manually populated with actions/properties
 *
 * In most cases, clients should create proxy instances for specific services instead.
 *
 * @param[in] aDomain   Domain (vendor) name
 * @param[in] aName     Service name
 * @param[in] aVersion  Version number
 * @param[in] aDevice   Handle to the device the proxy will communicate with / operate on
 *
 * @return  Handle to the new (empty) proxy
 */
DllExport THandle STDCALL CpProxyCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice);

/**
 * Destroy a proxy (only useful to clients who have called CpProxyCreate)
 *
 * @param[in] aProxy  Returned by CpProxyCreate
 */
DllExport void STDCALL CpProxyDestroy(THandle aProxy);

/**
 * Retrieve the handle to the underlying service (only useful to clients who have called CpProxyCreate)
 *
 * @param[in] aProxy  Returned by CpProxyCreate
 *
 * @return  Handle to the underlying service
 */
DllExport THandle STDCALL CpProxyService(THandle aProxy);

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
 *
 * @return  0 on success; -1 on unrecoverable error (service with no properties)
 */
DllExport int32_t STDCALL CpProxySubscribe(THandle aHandle);

/**
 * Unsubscribe from notifications of changes in state variables for a given
 * service on a given device.
 *
 * Unsubscription is asynchronous but no more notifications will be received
 * once this function returns.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 */
DllExport void STDCALL CpProxyUnsubscribe(THandle aHandle);

/**
 * Register a callback which will run after each group of 1..n changes to
 * state variable is processed.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 * @param[in] aCallback  The callback to run
 * @param[in] aPtr       Data to be passed to the callback
 */
DllExport void STDCALL CpProxySetPropertyChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Register a callback which will run when the state of all properties becomes available.
 * This is often the first point at which UI elements can be fully initialised.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 * @param[in] aCallback  The callback to run
 * @param[in] aPtr       Data to be passed to the callback
 */
DllExport void STDCALL CpProxySetPropertyInitialEvent(THandle aHandle, OhNetCallback aCallback, void* aPtr);

/**
 * Query which service version the remote device implements.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 *
 * @return  Service version
 */
DllExport uint32_t STDCALL CpProxyVersion(THandle aHandle);

/**
 * Must be called before reading the value of a property.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 */
DllExport void STDCALL CpProxyPropertyReadLock(THandle aHandle);

/**
 * Must be called once for each call to CpProxyReadLock() (after reading the value of a property).
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 */
DllExport void STDCALL CpProxyPropertyReadUnlock(THandle aHandle);

/**
 * Add a property to a service.
 * Will normally only be called by auto-generated code.
 *
 * @param[in] aHandle    Returned from [service]CreateEvented
 * @param[in] aProperty  Returned from ServicePropertyCreate[type]
 */
DllExport void STDCALL CpProxyAddProperty(THandle aHandle, ServiceProperty aProperty);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_SERVICE_PROXYC
