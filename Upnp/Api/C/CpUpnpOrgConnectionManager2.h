/**
 * Proxy for upnp.org:ConnectionManager:2
 */
#ifndef HEADER_UPNPORGCONNECTIONMANAGER2_C
#define HEADER_UPNPORGCONNECTIONMANAGER2_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgConnectionManager2 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgConnectionManager2Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 */
DllExport void CpProxyUpnpOrgConnectionManager2Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[out] aSource
 * @param[out] aSink
 */
DllExport void CpProxyUpnpOrgConnectionManager2SyncGetProtocolInfo(THandle aHandle, char** aSource, char** aSink);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2BeginGetProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aSource
 * @param[out] aSink
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgConnectionManager2EndGetProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aSource, char** aSink);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aRemoteProtocolInfo
 * @param[in]  aPeerConnectionManager
 * @param[in]  aPeerConnectionID
 * @param[in]  aDirection
 * @param[out] aConnectionID
 * @param[out] aAVTransportID
 * @param[out] aRcsID
 */
DllExport void CpProxyUpnpOrgConnectionManager2SyncPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aRemoteProtocolInfo
 * @param[in]  aPeerConnectionManager
 * @param[in]  aPeerConnectionID
 * @param[in]  aDirection
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2BeginPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aConnectionID
 * @param[out] aAVTransportID
 * @param[out] aRcsID
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgConnectionManager2EndPrepareForConnection(THandle aHandle, ZappHandleAsync aAsync, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aConnectionID
 */
DllExport void CpProxyUpnpOrgConnectionManager2SyncConnectionComplete(THandle aHandle, int32_t aConnectionID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aConnectionID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2BeginConnectionComplete(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgConnectionManager2EndConnectionComplete(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[out] aConnectionIDs
 */
DllExport void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionIDs(THandle aHandle, char** aConnectionIDs);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionIDs(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aConnectionIDs
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionIDs(THandle aHandle, ZappHandleAsync aAsync, char** aConnectionIDs);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aConnectionID
 * @param[out] aRcsID
 * @param[out] aAVTransportID
 * @param[out] aProtocolInfo
 * @param[out] aPeerConnectionManager
 * @param[out] aPeerConnectionID
 * @param[out] aDirection
 * @param[out] aStatus
 */
DllExport void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aConnectionID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aRcsID
 * @param[out] aAVTransportID
 * @param[out] aProtocolInfo
 * @param[out] aPeerConnectionManager
 * @param[out] aPeerConnectionID
 * @param[out] aDirection
 * @param[out] aStatus
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionInfo(THandle aHandle, ZappHandleAsync aAsync, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);
/**
 * Set a callback to be run when the SourceProtocolInfo state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgConnectionManager2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2SetPropertySourceProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the SinkProtocolInfo state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgConnectionManager2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2SetPropertySinkProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the CurrentConnectionIDs state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgConnectionManager2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgConnectionManager2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the SourceProtocolInfo property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aSourceProtocolInfo
 */
DllExport void CpProxyUpnpOrgConnectionManager2PropertySourceProtocolInfo(THandle aHandle, char** aSourceProtocolInfo);
/**
 * Query the value of the SinkProtocolInfo property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aSinkProtocolInfo
 */
DllExport void CpProxyUpnpOrgConnectionManager2PropertySinkProtocolInfo(THandle aHandle, char** aSinkProtocolInfo);
/**
 * Query the value of the CurrentConnectionIDs property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aCurrentConnectionIDs
 */
DllExport void CpProxyUpnpOrgConnectionManager2PropertyCurrentConnectionIDs(THandle aHandle, char** aCurrentConnectionIDs);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGCONNECTIONMANAGER2_C

