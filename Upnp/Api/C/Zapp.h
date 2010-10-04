#ifndef HEADER_UPNPC
#define HEADER_UPNPC

#include <OsTypes.h>
#include <C/Async.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef THandle ZappHandleNetworkInterface;
typedef THandle ZappHandleNetworkInterfaceList;
typedef THandle ZappHandleInitParams;

/**
 * Callback which runs when a library component has a message to deliver
 *
 * @param[in] aPtr   Client-specified data
 * @param[in] aMsg   Nul-terminated message
 */
typedef void (*ZappCallbackMsg)(void* aPtr, const char* aMsg);
/**
 * Callback which runs to notify a listener of a change in a library component
 *
 * @param[in] aPtr   Client-specified data
 */
typedef void (*ZappCallback)(void* aPtr);
/**
 * Callback pointing to function which can be used to free memory allocated by a client
 *
 * @param[in] aPtr   Client-allocated memory to be freed
 */
typedef void (*ZappCallbackFreeExternal)(void* aPtr);

/**
 * Initialise the UPnP library.
 *
 * Must be called before any other library function.
 *
 * @param aInitParams  Initialisation options.  Ownership of these passes to the library.
 *
 * @return 0 if initialisation succeeded; non-zero otherwise
 */
DllExport int32_t ZappLibraryInitialise(ZappHandleInitParams aInitParams);

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
DllExport int32_t ZappLibraryInitialiseMinimal(ZappHandleInitParams aInitParams);

/**
 * Start the library as a UPnP control point stack
 *
 * Must be called after ZappLibraryInitialise but before any function from other headers
 */
DllExport void ZappLibraryStartCp();

/**
 * Start the library as a UPnP device stack
 *
 * Must be called after ZappLibraryInitialise but before any function from other headers
 */
DllExport void ZappLibraryStartDv();

/**
 * Start the library as both UPnP control point and device stacks
 *
 * Must be called after ZappLibraryInitialise but before any function from other headers
 */
DllExport void ZappLibraryStartCombined();

/**
 * Close the UPnP library.
 *
 * Will not fail.  No more library functions should be called after this.
 */
DllExport void ZappLibraryClose();

/**
 * Free memory returned by the library.
 * Use of this function is optional.  Calling free() directly is acceptable.
 *
 * @param[in] ptr              Pointer to be freed
 */
DllExport void ZappFree(void* aPtr);

/**
 * Create the initialisation parameters which must be passed to the library's initialiser
 *
 * @return  Handle to initialisation params object.
 */
DllExport ZappHandleInitParams ZappInitParamsCreate();

/**
 * Destroy an object previously created by ZappInitParamsCreate()
 *
 * @param[in] aParams          Initialisation params
 */
DllExport void ZappInitParamsDestroy(ZappHandleInitParams aParams);

/**
 * Set a callback to run for any logging output
 * Note that this can only be called before ZappLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run when the library has
 *                             data to be logged
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetLogOutput(ZappHandleInitParams aParams, ZappCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will be run if the library encounters an error it
 * cannot recover from.
 *
 * Suggested action if this is called is to exit the process and restart the
 * library and its owning application. Note that the string passed to the callback
 * is an error message so would be useful to log.
 * Note that this can only be called before ZappLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if a fatal error occurs
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetFatalErrorHandler(ZappHandleInitParams aParams, ZappCallbackMsg aCallback, void* aPtr);

/**
 * Set a callback which will run at the start of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the start of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetAsyncBeginHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run at the end of every async opertion
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run at the end of every async opertion
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetAsyncEndHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr);

/**
 * Set a callback which will run if an async opertion fails
 * Note that The library supplies a default implementation which logs these errors.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if an async opertion fails
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetAsyncErrorHandler(ZappHandleInitParams aParams, ZappCallbackAsync aCallback, void* aPtr);

/**
 * Set which subnet to use on startup
 * The OS layer will select the most appropriate subnet if this is not called.
 * Note that this can only be called before ZappLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aSubnet          The subnet to use on startup
 */
DllExport void ZappInitParamsSetDefaultSubnet(ZappHandleInitParams aParams, TIpAddress aSubnet);

/**
 * Set a listener for changes in the subnet being used
 *
 * This will run if the active subnet becomes unavailable or a seemingly more
 * appropriate subnet becomes available.
 * Note that this can only be called before ZappLibraryInitialise
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aCallback        Callback which will be run if the active subnet changes
 * @param[in] aPtr             Data which will be passed to aCallback
 */
DllExport void ZappInitParamsSetSubnetChangedListener(ZappHandleInitParams aParams, ZappCallback aCallback, void* aPtr);

/**
 * Set a custom timeout for TCP connections.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater that zero
 */
DllExport void ZappInitParamsSetTcpConnectTimeout(ZappHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a custom time that msearch responses should be spread out over.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aSecs            Time in seconds.  Must be between 1 and 5 (inclusive)
 */
DllExport void ZappInitParamsSetMsearchTime(ZappHandleInitParams aParams, uint32_t aSecs);

/**
 * Set a custom time-to-live value for msearches.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTtl             Time to live
 */
DllExport void ZappInitParamsSetMsearchTtl(ZappHandleInitParams aParams, uint32_t aTtl);

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
DllExport void ZappInitParamsSetNumEventSessionThreads(ZappHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to fetching device/service XML.
 *
 * A higher number of threads will allow faster population of device lists but
 * will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void ZappInitParamsSetNumXmlFetcherThreads(ZappHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Set the number of threads which should be dedicated to invoking actions on devices.
 *
 * A higher number of threads will allow faster population of device lists
 * but will also require more system resources.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aNumThreads      Number of threads.  Must be greater than zero.
 */
DllExport void ZappInitParamsSetNumActionInvokerThreads(ZappHandleInitParams aParams, uint32_t aNumThreads);

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
DllExport void ZappInitParamsSetNumInvocations(ZappHandleInitParams aParams, uint32_t aNumInvocations);

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
DllExport void ZappInitParamsSetNumSubscriberThreads(ZappHandleInitParams aParams, uint32_t aNumThreads);

/**
 * It is possible for initial information on state variables to arrive before
 * a subscription is noted as complete.
 * Set the maximim time to wait before rejecting an event update from an unknown source.
 *
 * @param[in] aParams          Initialisation params
 * @param[in] aTimeoutMs       Timeout in milliseconds.  Must be greater than zero.
 */
DllExport void ZappInitParamsSetPendingSubscriptionTimeout(ZappHandleInitParams aParams, uint32_t aTimeoutMs);

/**
 * Set a callback which will be used to free memory that is allocated outside the library
 * This is intended for C# wrappers and can be ignored by most (all?) other clients
 */
DllExport void ZappInitParamsSetFreeExternalCallback(ZappHandleInitParams aParams, ZappCallbackFreeExternal aCallback);

/**
 * Set the maximum time between device announcements for the device stack
 */
DllExport void ZappInitParamsSetDvMaxUpdateTime(ZappHandleInitParams aParams, uint32_t aSecs);

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
DllExport void ZappInitParamsSetDvNumPublisherThreads(ZappHandleInitParams aParams, uint32_t aNumThreads);

/**
 * Query the tcp connection timeout
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  timeout (in milliseconds)
 */
DllExport uint32_t ZappInitParamsTcpConnectTimeoutMs(ZappHandleInitParams aParams);

/**
 * Query the time msearch responses are requested to be spread over
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  time (in seconds)
 */
DllExport uint32_t ZappInitParamsMsearchTimeSecs(ZappHandleInitParams aParams);

/**
 * Query the time to live value for multicast queries
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  ttl value
 */
DllExport uint32_t ZappInitParamsMsearchTtl(ZappHandleInitParams aParams);

/**
 * Query the number of event session threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t ZappInitParamsNumEventSessionThreads(ZappHandleInitParams aParams);

/**
 * Query the number of XML fetcher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t ZappInitParamsNumXmlFetcherThreads(ZappHandleInitParams aParams);

/**
 * Query the number of invocation threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t ZappInitParamsNumActionInvokerThreads(ZappHandleInitParams aParams);

/**
 * Query the number of pre-allocated invocations
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of invocations
 */
DllExport uint32_t ZappInitParamsNumInvocations(ZappHandleInitParams aParams);

/**
 * Query the number of subscriber threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t ZappInitParamsNumSubscriberThreads(ZappHandleInitParams aParams);

/**
 * Query the maximum delay allowed between initial values of state variables
 * being delivered and a subscription identifier being provided
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in milliseconds)
 */
DllExport uint32_t ZappInitParamsPendingSubscriptionTimeoutMs(ZappHandleInitParams aParams);

/**
 * Query the maximum delay between device announcements (for the device stack only)
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  maximum delay (in seconds)
 */
DllExport uint32_t ZappInitParamsDvMaxUpdateTimeSecs(ZappHandleInitParams aParams);

/**
 * Query the number of device stack publisher threads
 *
 * @param[in] aParams          Initialisation params
 *
 * @return  number of threads
 */
DllExport uint32_t ZappInitParamsDvNumPublisherThreads(ZappHandleInitParams aParams);

/**
 * Query the address of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress ZappNetworkInterfaceAddress(ZappHandleNetworkInterface aNif);

/**
 * Query the subnet of a network interface is available on
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport TIpAddress ZappNetworkInterfaceSubnet(ZappHandleNetworkInterface aNif);

/**
 * Query the name of a network interface
 *
 * @param[in] aNif             Network interface handle
 *
 * @return  IpV4 address as network order uint32
 */
DllExport const char* ZappNetworkInterfaceName(ZappHandleNetworkInterface aNif);

/**
 * Create a list of all available subnets
 *
 * @return  Handle to list of subnets.  Ownership transfers to caller.
 */
DllExport ZappHandleNetworkInterfaceList ZappSubnetListCreate();

/**
 * Query the number of elements in a subnet list
 *
 * @param[in] aList            Handle returned by ZappSubnetListCreate()
 *
 * @return  number of elements (subnets) in the list
 */
DllExport uint32_t ZappSubnetListSize(ZappHandleNetworkInterfaceList aList);

/**
 * Get a handle to the subnet at a specified position in a subnet list.
 *
 * @param[in] aList            Handle returned by ZappSubnetListCreate()
 *
 * @return  subnet handle
 */
DllExport ZappHandleNetworkInterface ZappSubnetAt(ZappHandleNetworkInterfaceList aList, uint32_t aIndex);

/**
 * Destroy a subnet list
 *
 * @param[in] aList            Handle returned by ZappSubnetListCreate()
 */
DllExport void ZappSubnetListDestroy(ZappHandleNetworkInterfaceList aList);

/**
 * Set which subnet the library should use.
 *
 * This override any value set via ZappInitParamsSetDefaultSubnet().
 * Device lists and subscriptions will be automatically updated.
 * No other subnet will be selected if aSubnet is not available
 *
 * @param aSubnet              The subnet to use
 */
DllExport void ZappSetCurrentSubnet(ZappHandleNetworkInterface aSubnet);

/**
 * Clear any subnet previously specified using ZappSetCurrentSubnet() or
 * ZappInitParamsSetDefaultSubnet().  OS-specified defaults will be used instead.
 *
 * Device lists and subscriptions will be automatically updated if necessary.
 */
DllExport void ZappSetDefaultSubnet();

/**
 * Free memory which was allocated by the client
 *
 * @param[in] aPtr             Memory to be freed
 */
DllExport void ZappFreeExternal(void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPC
