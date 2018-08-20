#ifndef HEADER_UPNPC
#define HEADER_UPNPC

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/Async.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef THandle OhNetHandleNetworkAdapter;
typedef THandle OhNetHandleNetworkAdapterList;
typedef THandle OhNetHandleInitParams;

/**
 * Callback which runs when a library component has a message to deliver
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-specified data
 * @param[in] aMsg   Nul-terminated message
 */
typedef void (STDCALL *OhNetCallbackMsg)(void* aPtr, const char* aMsg);
/**
 * Callback which runs to notify a listener of a change in a library component
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-specified data
 */
typedef void (STDCALL *OhNetCallback)(void* aPtr);
/**
 * Callback which runs when a network adapter is added or removed from a subnet list.
 * @ingroup Callbacks
 *
 * @param[in] aPtr      Client-specified data
 * @param[in] aAdapter  The network adapter that was added or removed.
 */
typedef void (STDCALL *OhNetCallbackNetworkAdapter)(void* aPtr, OhNetHandleNetworkAdapter aAdapter);
/**
 * Callback pointing to function which can be used to free memory allocated by a client
 * @ingroup Callbacks
 *
 * @param[in] aPtr   Client-allocated memory to be freed
 */
typedef void (STDCALL *OhNetCallbackFreeExternal)(void* aPtr);

/**
 * @addtogroup Library
 * @ingroup Core
 * @{
 */

typedef enum EOhNetLibraryInitError
{
    eOhNetInitErrorNone
   ,eOhNetInitErrorNoMemory
   ,eOhNetInitErrorGeneral
   ,eOhNetInitErrorNetworkAddressInUse
} EOhNetLibraryInitError;

/**
 * Initialise the UPnP library.
 *
 * Must be called before any other library function.
 *
 * @param aInitParams  Initialisation options.  Ownership of these passes to the library.
 *
 * @return 0 if initialisation succeeded; non-zero otherwise
 */
DllExport int32_t STDCALL OhNetLibraryInitialise(OhNetHandleInitParams aInitParams);

/**
 * Lightweight alternative to UpnpLibraryInitialise.
 *
 * Intended for unit tests which are useful to platform porting only.
 * No class APIs other than Close() can be called if this is used.
 *
 * @param aInitParams  Initialisation options.  Only ILogOutput will be used.
 *                     Ownership of these passes to the library.
 *
 * @return 0 if initialisation succeeded; non-zero otherwise
 */
DllExport int32_t STDCALL OhNetLibraryInitialiseMinimal(OhNetHandleInitParams aInitParams);

/**
 * Start the library as a UPnP control point stack
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 *
 * @param aSubnet      Subnet address of the network adapter to use.
 */
DllExport EOhNetLibraryInitError STDCALL OhNetLibraryStartCp(TIpAddress aSubnet);

/**
 * Start the library as a UPnP device stack
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 */
DllExport EOhNetLibraryInitError STDCALL OhNetLibraryStartDv();

/**
 * Start the library as both UPnP control point and device stacks
 *
 * Must be called after OhNetLibraryInitialise but before any function from other headers
 *
 * @param aSubnet      Subnet address of the network adapter for the control point stack to use.
 *                     (The device stack operates on all adapters.)
 */
DllExport EOhNetLibraryInitError STDCALL OhNetLibraryStartCombined(TIpAddress aSubnet);

/**
 * Close the UPnP library.
 *
 * Will not fail.  No more library functions should be called after this.
 */
DllExport void STDCALL OhNetLibraryClose();

/**
 * Inform the library that the application has been suspended.
 *
 * This is necessary if the application may be paused while other processes on
 * a device continued to be executed (e.g. when an app moves to background on iOS).
 * It is typically not necessary to call this when the host device hibernates.
 */
DllExport void STDCALL OhNetLibraryNotifySuspended(void);

/**
 * Inform the library that the application has been resumed.
 *
 * This is necessary if the application may have been paused while other processes on
 * a device continued to be executed (e.g. when an app moves to background on iOS).
 * It is typically not necessary to call this when the host device resumes from hibernation.
 */
DllExport void STDCALL OhNetLibraryNotifyResumed(void);

/**
 * Force any subscriptions to be renewed.
 *
 * Only relevant to control point stack clients.
 * Probably only useful on devices with poor quality wifi.
 * Users of this should also consider calling OhNetInitParamsSetSubscriptionDuration().
 */
DllExport void STDCALL OhNetLibraryRenewSubscriptions(void);

/**
 * Override the HTTP user agent set in initialisation params
 */
DllExport void STDCALL OhNetLibrarySetHttpUserAgent(const char* aUserAgent);

/* @} */
/**
 * @addtogroup InitParams
 * @ingroup Core
 * @{
 */

/**
 * Create the initialisation parameters which must be passed to the library's initialiser
 *
 * @return  Handle to initialisation params object.
 */
DllExport OhNetHandleInitParams STDCALL OhNetInitParamsCreate();

/**
 * Destroy an object previously created by OhNetInitParamsCreate()
 *
 * @param[in] aParams          Initialisation params
 */
DllExport void STDCALL OhNetInitParamsDestroy(OhNetHandleInitParams aParams);

/**
 * Set a callback to run for any logging output
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run when the library has
 *                             data to be logged
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetLogOutput(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will be run if the library encounters an error it
 * cannot recover from.
 *
 * Suggested action if this is called is to exit the process and restart the
 * library and its owning application. Note that the string passed to the callback
 * is an error message so would be useful to log.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if a fatal error occurs
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetFatalErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will run at the start of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the start of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetAsyncBeginHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run at the end of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the end of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetAsyncEndHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run if an async opertion fails
 * Note that The library supplies a default implementation which logs these errors.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if an async opertion fails
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetAsyncErrorHandler(OhNetHandleInitParams aParams, OhNetCallbackAsync aCallback, void* aPtr);

/**
 * Set a listener for changes in the subnet being used
 *
 * This will run if the active subnet becomes unavailable or a seemingly more
 * appropriate subnet becomes available.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if the active subnet changes
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetSubnetListChangedListener(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr);

/**
 * Set a listener for when subnets are added to a subnet list
 *
 * This will run if a subnet is added to the subnet list.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if a subnet is added to the subnet list
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetSubnetAddedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr);

/**
 * Set a listener for when subnets are removed from a subnet list
 *
 * This will run if the a subnet is removed from the subnet list.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if a subnet is removed from the subnet list
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetSubnetRemovedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr);

/**
 * Set a listener for changes in the adapter being used to access a subnet.
 *
 * This will run if the network adapter used to access any given subnet changes.
 * Note that this can only be called before OhNetLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if the network adapter changes
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetNetworkAdapterChangedListener(OhNetHandleInitParams aParams, OhNetCallbackNetworkAdapter aCallback, void* aPtr);

/**
 * Set a callback which will run each time a thread exits
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run each time a thread exits
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void STDCALL OhNetInitParamsSetThreadExitHandler(OhNetHandleInitParams aParams, OhNetCallback aCallback, void* aPtr);

/**
 * Set a custom timeout for TCP connections.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater that zero
 */
DllExport void STDCALL OhNetInitParamsSetTcpConnectTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a custom time that msearch responses should be spread out over.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aSecs            Time in seconds.  Must be between 1 and 5 (inclusive)
 */
DllExport void STDCALL OhNetInitParamsSetMsearchTime(OhNetHandleInitParams aParams, uint32_t aSecs);

/**
 * Set a custom time-to-live value for msearches.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTtl             Time to live
 */
DllExport void STDCALL OhNetInitParamsSetMsearchTtl(OhNetHandleInitParams aParams, uint32_t aTtl);

/**
 * Set a custom number of threads which will be dedicated to eventing (handling
 * updates to subscribed state variables)
 *
 * A higher number of threads may allow faster processing  but will certainly
 * require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetNumEventSessionThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to fetching device/service XML.
 *
 * A higher number of threads will allow faster population of device lists but
 * will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetNumXmlFetcherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to invoking actions on devices.
 *
 * A higher number of threads will allow faster population of device lists
 * but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetNumActionInvokerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of invocations (actions) which should be pre-allocated.
 *
 * If more that this number are pending, the additional attempted invocations
 * will block until a pre-allocated slot becomes clear.
 * A higher number of invocations will decrease the likelihood and duration of
 * any UI-level delays but will also increase the peaks in RAM requirements.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumInvocations  Number of invocations.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetNumInvocations(OhNetHandleInitParams aParams, uint32_t aNumInvocations);

/**
 * Set the number of threads which should be dedicated to (un)subscribing
 * to state variables on a service + device.
 *
 * A higher number of threads may allow faster initialisation of some application
 * views but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetNumSubscriberThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the maximum time control points will wait for action invocations to begin responding.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aDurationSecs    Timeout in milliseconds.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetInvocationTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set the duration control point subscriptions will request.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aDurationSecs    Duration in seconds.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetSubscriptionDuration(OhNetHandleInitParams aParams, uint32_t aDurationSecs);

/**
 * It is possible for initial information on state variables to arrive before
 * a subscription is noted as complete.
 * Set the maximim time to wait before rejecting an event update from an unknown source.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetPendingSubscriptionTimeout(OhNetHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a callback which will be used to free memory that is allocated outside the library
 * This is intended for C# wrappers and can be ignored by most (all?) other clients
 */
DllExport void STDCALL OhNetInitParamsSetFreeExternalCallback(OhNetHandleInitParams aParams, OhNetCallbackFreeExternal aCallback);

/**
 * Limit the library to using only the loopback network interface.
 * Useful for testing but not expected to be used in production code
 */
DllExport void STDCALL OhNetInitParamsSetUseLoopbackNetworkAdapter(OhNetHandleInitParams aParams);

/**
 * Include the loopback network interface in the list of available adapters.
 * Useful for testing but not expected to be used in production code
 */
DllExport void STDCALL OhNetInitParamsSetIncludeLoopbackNetworkAdapter(OhNetHandleInitParams aParams);

/**
 * Set the maximum time between device announcements for the device stack
 */
DllExport void STDCALL OhNetInitParamsSetDvMaxUpdateTime(OhNetHandleInitParams aParams, uint32_t aSecs);

/**
 * Set the number of threads which should be dedicated to processing
 * control/eventing/presentation requests.
 *
 * A higher number of threads may allow faster response to multiple clients
 * making concurrent requests but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetDvNumServerThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to publishing changes
 * to state variables on a service + device.
 *
 * A higher number of threads may allow faster publication of changes (enabling more
 * responsive client apps) views but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetDvNumPublisherThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which will be dedicated to published changes to state
 * variables via WebSockets.
 *
 * One thread will be used per active (web browser) connection so a higher number of threads
 * will allow more concurrent clients but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void STDCALL OhNetInitParamsSetDvNumWebSocketThreads(OhNetHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the tcp port number the control point stack's UPnP event server will run on.
 *
 * The default value is 0 (meaning that the OS will assign a port).
 * You should only set this if you know the full set of services (plus their port
 * requirements) running on a device.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aPort            Port number.  0 (the default value) implies an OS-assigned port.
 */ 
DllExport void STDCALL OhNetInitParamsSetCpUpnpEventServerPort(OhNetHandleInitParams aParams, uint32_t aPort);

/**
 * Set the tcp port number the device stack's UPnP web server will run on.
 *
 * The default value is 0 (OS-assigned).
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aPort            Port number.
 */ 
DllExport void STDCALL OhNetInitParamsSetDvUpnpServerPort(OhNetHandleInitParams aParams, uint32_t aPort);

/**
 * Set the tcp port number the device stack's websocket server will run on.
 *
 * You should only rely on this (or another non-zero value) if you know the full
 * set of services (plus their port requirements) running on a device.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aPort            Port number.  0 (the default value) implies an OS-assigned port.
 */
DllExport void STDCALL OhNetInitParamsSetDvWebSocketPort(OhNetHandleInitParams aParams, uint32_t aPort);

/**
 * Enable use of Bonjour.
 *
 * All DvDevice instances with a resource manager will be published using Bonjour.
 * If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
 * Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
 * Note that enabling Bonjour will cause the device stack to run a http server on port 80, requiring root privileges on linux.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aHostName        mDNS host name
 */
DllExport void STDCALL OhNetInitParamsSetDvEnableBonjour(OhNetHandleInitParams aParams, const char* aHostName, uint8_t aRequiresMdnsCache);

/**
 * Disable control point stack inferring device removal.
 *
 * UPnP relies on devices sending regular UDP multicast messages confirming their continued availability.
 * It is reasonably easy to lose these messages on misconfigured networks.  This option allows an
 * application to disable inferred device removal altogether.  This risks device lists showing too many
 * devices but can sometime reduce customer support effort.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aLowQuality      0 => good quality networking (default); 1 => unreliable multicast reception
 */
DllExport void STDCALL OhNetInitParamsSetHostUdpIsLowQuality(OhNetHandleInitParams aParams, int32_t aLowQuality);

/**
* Set HTTP user agent string.
*
* This will be reported by any HTTP clients run by ohNet.
* It may also be used by some ohNet clients.
*
* @param[in] aParams          Initialisation params
* @param[in] aUserAgent       User agent
*/
DllExport void STDCALL OhNetInitParamsSetHttpUserAgent(OhNetHandleInitParams aParams, const char* aUserAgent);

/**
 * Query the tcp connection timeout
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  timeout (in milliseconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsTcpConnectTimeoutMs(OhNetHandleInitParams aParams);

/**
 * Query the time msearch responses are requested to be spread over
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  time (in seconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsMsearchTimeSecs(OhNetHandleInitParams aParams);

/**
 * Query the time to live value for multicast queries
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  ttl value
 */
DllExport uint32_t STDCALL OhNetInitParamsMsearchTtl(OhNetHandleInitParams aParams);

/**
 * Query the number of event session threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsNumEventSessionThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of XML fetcher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsNumXmlFetcherThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of invocation threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsNumActionInvokerThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of pre-allocated invocations
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of invocations
 */
DllExport uint32_t STDCALL OhNetInitParamsNumInvocations(OhNetHandleInitParams aParams);

/**
 * Query the number of subscriber threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsNumSubscriberThreads(OhNetHandleInitParams aParams);

/**
 * Query the timeout for action invocations.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  timeout for device to begin responding (in milliseconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsInvocationTimeoutMs(OhNetHandleInitParams aParams);

/**
 * Query the duration control points will request for subscriptions.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  requested subscription duration (in seconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsSubscriptionDurationSecs(OhNetHandleInitParams aParams);

/**
 * Query the maximum delay allowed between initial values of state variables
 * being delivered and a subscription identifier being provided
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in milliseconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsPendingSubscriptionTimeoutMs(OhNetHandleInitParams aParams);

/**
 * Query the maximum delay between device announcements (for the device stack only)
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in seconds)
 */
DllExport uint32_t STDCALL OhNetInitParamsDvMaxUpdateTimeSecs(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack server threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsDvNumServerThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack publisher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsDvNumPublisherThreads(OhNetHandleInitParams aParams);

/**
 * Query the number of device stack WebSocket threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t STDCALL OhNetInitParamsDvNumWebSocketThreads(OhNetHandleInitParams aParams);

/**
 * Query the port the control point stack's UPnP event server will run on.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  Port number.  May be 0 (meaning OS will assign a port later).
 */
DllExport uint32_t STDCALL OhNetInitParamsCpUpnpEventServerPort(OhNetHandleInitParams aParams);

/**
 * Query the port the device stack's UPnP web server will run on.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  Port number.  May be 0 (meaning OS will assign a port later).
 */
DllExport uint32_t STDCALL OhNetInitParamsDvUpnpServerPort(OhNetHandleInitParams aParams);

/**
 * Query the port the device stack's WebSocket server will run on.
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  Port number.  May be 0 (meaning OS will assign a port later).
 */
DllExport uint32_t STDCALL OhNetInitParamsDvWebSocketPort(OhNetHandleInitParams aParams);

/**
 * Query whether Bonjour is enabled
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  1 if Bonjour is enabled; 0 otherwise
 */
DllExport uint32_t STDCALL OhNetInitParamsDvIsBonjourEnabled(OhNetHandleInitParams aParams);

/**
* Query state of HostUdpIsLowQuality (so whether device lists will infer device removal)
*
* @param[in] aParams          Initialisation params
*
* @return  1 if low quality mode is enabled; 0 otherwise
*/
DllExport uint32_t STDCALL OhNetInitParamsIsHostUdpLowQuality(OhNetHandleInitParams aParams);

/* @} */

/**
 * @addtogroup NetworkAdapter
 * @ingroup Core
 * @{
 */

/**
 * Query the address of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress STDCALL OhNetNetworkAdapterAddress(OhNetHandleNetworkAdapter aNif);

/**
 * Query the subnet of a network interface is available on
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress STDCALL OhNetNetworkAdapterSubnet(OhNetHandleNetworkAdapter aNif);

/**
 * Query the netmask that a network interface is available on
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress STDCALL OhNetNetworkAdapterMask(OhNetHandleNetworkAdapter aNif);

/**
 * Query the name of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport const char* STDCALL OhNetNetworkAdapterName(OhNetHandleNetworkAdapter aNif);

/**
 * Get the full name of the network adapter.
 *
 * @return  String in the form a.b.c.d (name).
 *          The caller is responsible for freeing this by calling OhNetFree().
 */
DllExport char* STDCALL OhNetNetworkAdapterFullName(OhNetHandleNetworkAdapter aNif);

/**
 * Claim a reference to a network adapter.
 *
 * NetworkAdapter passed to a subnet added listener cannot be used outside the callback
 * unless the client claims a reference to it.
 *
 * @param[in]  aNif       NetworkAdapter originally returned to a subnet added callback.
 * @param[in] aCookie     String identifying the caller.  Needn't be unique although a
 *                        recognisable string will help in debugging the cause of any
 *                        leaked NetworkAdapter references.  The later matching call
 *                        to OhNetNetworkAdapterRemoveRef must use the same cookie.
 */
DllExport void STDCALL OhNetNetworkAdapterAddRef(OhNetHandleNetworkAdapter aNif, const char* aCookie);

/**
 * Release a reference to a network adapter.
 *
 * The network adapter will be destroyed when the last reference is released.
 * Each call to OhNetNetworkAdapterAddRef() must be matched by exactly one call to
 * OhNetNetworkAdapterRemoveRef().
 *
 * @param[in]  aNif       Network adapter to release the reference for.
 * @param[in] aCookie     String identifying the caller.  Must match an earlier cookie
 *                        used in either OhNetCurrentSubnetAdapter or OhNetNetworkAdapterAddRef.
 */
DllExport void STDCALL OhNetNetworkAdapterRemoveRef(OhNetHandleNetworkAdapter aNif, const char* aCookie);

/**
 * Create a list of all available subnets
 *
 * @return  Handle to list of subnets.  Ownership transfers to caller.
 */
DllExport OhNetHandleNetworkAdapterList STDCALL OhNetSubnetListCreate();

/**
 * Query the number of elements in a subnet list
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 *
 * @return  number of elements (subnets) in the list
 */
DllExport uint32_t STDCALL OhNetSubnetListSize(OhNetHandleNetworkAdapterList aList);

/**
 * Get a handle to the subnet at a specified position in a subnet list.
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 * @param[in] aIndex           Index into the list to return the subnet from
 *
 * @return  subnet handle
 */
DllExport OhNetHandleNetworkAdapter STDCALL OhNetSubnetAt(OhNetHandleNetworkAdapterList aList, uint32_t aIndex);

/**
 * Destroy a subnet list
 *
 * @param[in] aList            Handle returned by OhNetSubnetListCreate()
 */
DllExport void STDCALL OhNetSubnetListDestroy(OhNetHandleNetworkAdapterList aList);

/**
 * Create a list of all available network adapters
 *
 * @return  Handle to list of network adapters.  Ownership transfers to caller.
 */
DllExport OhNetHandleNetworkAdapterList STDCALL OhNetNetworkAdapterListCreate();

/**
 * Query the number of elements in a network adapter list
 *
 * @param[in] aList            Handle returned by OhNetNetworkAdapterListCreate()
 *
 * @return  number of elements (network adapters) in the list
 */
DllExport uint32_t STDCALL OhNetNetworkAdapterListSize(OhNetHandleNetworkAdapterList aList);

/**
 * Get a handle to the network adapter at a specified position in a network adapter list.
 *
 * @param[in] aList            Handle returned by OhNetNetworkAdapterListCreate()
 * @param[in] aIndex           Index into the list to return the network adapter from
 *
 * @return  network adapter handle
 */
DllExport OhNetHandleNetworkAdapter STDCALL OhNetNetworkAdapterAt(OhNetHandleNetworkAdapterList aList, uint32_t aIndex);

/**
 * Destroy a network adapter list
 *
 * @param[in] aList            Handle returned by OhNetNetworkAdapterListCreate()
 */
DllExport void STDCALL OhNetNetworkAdapterListDestroy(OhNetHandleNetworkAdapterList aList);

/**
 * Set which subnet the library should use.
 *
 * Device lists and subscriptions will be automatically updated.
 * No other subnet will be selected if aSubnet is not available
 *
 * @param aSubnet              The subnet to use
 */
DllExport void STDCALL OhNetSetCurrentSubnet(uint32_t aSubnet);

/**
 * Query which network adapter is currently selected.
 *
 * @param[in] aCookie   String identifying the caller.  Needn't be unique although a
 *                      recognisable string will help in debugging the cause of any
 *                      leaked NetworkAdapter references.  The later matching call
 *                      to RemoveRef must use the same cookie.
 *
 * @return  A pointer to the currently selected adapter with a reference claimed.
 *          Or NULL if there is no currently selected adapter.
 */
DllExport OhNetHandleNetworkAdapter STDCALL OhNetCurrentSubnetAdapter(const char* aCookie);

/**
* Force a refresh of the library's list of available network adapters
*
* This should only be required on platforms that are not capable of
* automatically detecting adapter changes.
*/
DllExport void STDCALL OhNetRefreshNetworkAdapterList();

/* @} */

/**
 * @addtogroup Memory
 * @ingroup Core
 * @{
 */

/**
 * Free memory returned by the library.
 *
 * Use of this function is optional.  Calling free() directly is acceptable.
 *
 * @param[in] aPtr             Pointer to be freed
 */
DllExport void STDCALL OhNetFree(void* aPtr);

/**
 * Free memory which was allocated by the client
 *
 * @param[in] aPtr             Memory to be freed
 */
DllExport void STDCALL OhNetFreeExternal(void* aPtr);

/* @} */

/**
 * @addtogroup Debug
 * @ingroup Core
 * @{
 */

/**
 * Enable debug logging.
 *
 * Log messages will be passed to the callback registered in OhNetInitParamsSetLogOutput.
 *
 * @param[in] aLevel           Bit(s) specifying debug level.  See OpenHome/Private/Debug.h.
 */
DllExport void STDCALL OhNetDebugSetLevel(uint64_t aLevel);

/**
 * Enable debug logging.
 *
 * Log messages will be passed to the callback registered in OhNetInitParamsSetLogOutput.
 *
 * @param[in] aSeverity        Integer specifying debug severity.  See OpenHome/Private/Debug.h.
 */
DllExport void STDCALL OhNetDebugSetSeverity(uint32_t aSeverity);

/**
 * Terminate the ohNet process after a fatal error. On some platforms, this call
 * may invoke a debugger or produce a crash dump.
 */
DllExport void STDCALL OhNetAbortProcess();

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPC
