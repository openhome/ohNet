/**
 * Proxy for upnp.org:AVTransport:2
 */
#ifndef HEADER_UPNPORGAVTRANSPORT2_C
#define HEADER_UPNPORGAVTRANSPORT2_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyUpnpOrgAVTransport2 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyUpnpOrgAVTransport2Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 */
DllExport void CpProxyUpnpOrgAVTransport2Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCurrentURI
 * @param[in]  aCurrentURIMetaData
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCurrentURI
 * @param[in]  aCurrentURIMetaData
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSetAVTransportURI(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNextURI
 * @param[in]  aNextURIMetaData
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNextURI
 * @param[in]  aNextURIMetaData
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSetNextAVTransportURI(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetMediaInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentType
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentType
 * @param[out] aNrTracks
 * @param[out] aMediaDuration
 * @param[out] aCurrentURI
 * @param[out] aCurrentURIMetaData
 * @param[out] aNextURI
 * @param[out] aNextURIMetaData
 * @param[out] aPlayMedium
 * @param[out] aRecordMedium
 * @param[out] aWriteStatus
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetMediaInfo_Ext(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentTransportState
 * @param[out] aCurrentTransportStatus
 * @param[out] aCurrentSpeed
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetTransportInfo(THandle aHandle, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetTransportInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentTransportState
 * @param[out] aCurrentTransportStatus
 * @param[out] aCurrentSpeed
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetTransportInfo(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aTrack
 * @param[out] aTrackDuration
 * @param[out] aTrackMetaData
 * @param[out] aTrackURI
 * @param[out] aRelTime
 * @param[out] aAbsTime
 * @param[out] aRelCount
 * @param[out] aAbsCount
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetPositionInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetPositionInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aTrack
 * @param[out] aTrackDuration
 * @param[out] aTrackMetaData
 * @param[out] aTrackURI
 * @param[out] aRelTime
 * @param[out] aAbsTime
 * @param[out] aRelCount
 * @param[out] aAbsCount
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetPositionInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aPlayMedia
 * @param[out] aRecMedia
 * @param[out] aRecQualityModes
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPlayMedia
 * @param[out] aRecMedia
 * @param[out] aRecQualityModes
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetDeviceCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aPlayMode
 * @param[out] aRecQualityMode
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetTransportSettings(THandle aHandle, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetTransportSettings(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aPlayMode
 * @param[out] aRecQualityMode
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetTransportSettings(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMode, char** aRecQualityMode);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncStop(THandle aHandle, uint32_t aInstanceID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginStop(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndStop(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aSpeed
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aSpeed
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndPlay(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncPause(THandle aHandle, uint32_t aInstanceID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginPause(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndPause(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncRecord(THandle aHandle, uint32_t aInstanceID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginRecord(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndRecord(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aUnit
 * @param[in]  aTarget
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aUnit
 * @param[in]  aTarget
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSeek(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncNext(THandle aHandle, uint32_t aInstanceID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginNext(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndNext(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncPrevious(THandle aHandle, uint32_t aInstanceID);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginPrevious(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndPrevious(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNewPlayMode
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNewPlayMode
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSetPlayMode(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNewRecordQualityMode
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aNewRecordQualityMode
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSetRecordQualityMode(THandle aHandle, ZappHandleAsync aAsync);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aActions
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, char** aActions);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aActions
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetCurrentTransportActions(THandle aHandle, ZappHandleAsync aAsync, char** aActions);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[out] aCurrentDRMState
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetDRMState(THandle aHandle, uint32_t aInstanceID, char** aCurrentDRMState);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetDRMState(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aCurrentDRMState
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetDRMState(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentDRMState);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[out] aStateVariableValuePairs
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aStateVariableValuePairs
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndGetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableValuePairs);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aAVTransportUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[out] aStateVariableList
 */
DllExport void CpProxyUpnpOrgAVTransport2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aInstanceID
 * @param[in]  aAVTransportUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aStateVariableList
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyUpnpOrgAVTransport2EndSetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableList);
/**
 * Set a callback to be run when the LastChange state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgAVTransport2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the DRMState state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyUpnpOrgAVTransport2 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyUpnpOrgAVTransport2Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyUpnpOrgAVTransport2SetPropertyDRMStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the LastChange property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aLastChange
 */
DllExport void CpProxyUpnpOrgAVTransport2PropertyLastChange(THandle aHandle, char** aLastChange);
/**
 * Query the value of the DRMState property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDRMState
 */
DllExport void CpProxyUpnpOrgAVTransport2PropertyDRMState(THandle aHandle, char** aDRMState);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_UPNPORGAVTRANSPORT2_C

