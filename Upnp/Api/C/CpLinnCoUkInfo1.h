/**
 * Proxy for linn.co.uk:Info:1
 */
#ifndef HEADER_LINNCOUKINFO1_C
#define HEADER_LINNCOUKINFO1_C

#include <OsTypes.h>
#include <C/Async.h>
#include <C/Zapp.h>
#include <C/CpDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor.
 * Creates an instance of CpProxyLinnCoUkInfo1 without support for eventing.
 * Use CpProxyC[Un]Subscribe() to enable/disable querying of state variable and
 * reporting of their changes.
 *
 * @param[in]  aDevice   The device to use
 *
 * @return  Handle which should be used with all other functions in this header
 */
DllExport THandle CpProxyLinnCoUkInfo1Create(CpDeviceC aDevice);
/**
 * Destructor.
 * If any asynchronous method is in progress, this will block until they complete.
 * [Note that any methods still in progress are likely to complete with an error.]
 * Clients who have called CpProxyCSubscribe() do not need to call CpProxyCSubscribe()
 * before calling delete.  An unsubscribe will be triggered automatically when required.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 */
DllExport void CpProxyLinnCoUkInfo1Destroy(THandle aHandle);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[out] aaTrackCount
 * @param[out] aaDetailsCount
 * @param[out] aaMetatextCount
 */
DllExport void CpProxyLinnCoUkInfo1SyncCounters(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1BeginCounters(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaTrackCount
 * @param[out] aaDetailsCount
 * @param[out] aaMetatextCount
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkInfo1EndCounters(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[out] aaUri
 * @param[out] aaMetadata
 */
DllExport void CpProxyLinnCoUkInfo1SyncTrack(THandle aHandle, char** aaUri, char** aaMetadata);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1BeginTrack(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaUri
 * @param[out] aaMetadata
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkInfo1EndTrack(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetadata);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[out] aaDuration
 * @param[out] aaBitRate
 * @param[out] aaBitDepth
 * @param[out] aaSampleRate
 * @param[out] aaLossless
 * @param[out] aaCodecName
 */
DllExport void CpProxyLinnCoUkInfo1SyncDetails(THandle aHandle, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1BeginDetails(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaDuration
 * @param[out] aaBitRate
 * @param[out] aaBitDepth
 * @param[out] aaSampleRate
 * @param[out] aaLossless
 * @param[out] aaCodecName
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkInfo1EndDetails(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName);

/**
 * Invoke the action synchronously.  Blocks until the action has been processed
 * on the device and sets any output arguments.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[out] aaMetatext
 */
DllExport void CpProxyLinnCoUkInfo1SyncMetatext(THandle aHandle, char** aaMetatext);
/**
 * Invoke the action asynchronously.
 * Returns immediately and will run the client-specified callback when the action
 * later completes.  Any output arguments can then be retrieved by calling
 * EndGetProtocolInfo().
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback Callback to run when the action completes.
 *                       This is guaranteed to be run but may indicate an error
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1BeginMetatext(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr);
/**
 * Retrieve the output arguments from an asynchronously invoked action.
 * This may only be called from the callback set in the above Begin function.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aAsync    Argument passed to the callback set in the above Begin function
 * @param[out] aaMetatext
 *
 * @return  0 if the function succedded; non-zero if it failed.  State of output
 *          arguments is not guaranteed in the case of failure
 */
DllExport int32_t CpProxyLinnCoUkInfo1EndMetatext(THandle aHandle, ZappHandleAsync aAsync, char** aaMetatext);
/**
 * Set a callback to be run when the TrackCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the DetailsCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the MetatextCount state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Uri state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyUriChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Metadata state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Duration state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the BitRate state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the BitDepth state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the SampleRate state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Lossless state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the CodecName state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);
/**
 * Set a callback to be run when the Metatext state variable changes.
 *
 * Callbacks may be run in different threads but callbacks for a
 * CpProxyLinnCoUkInfo1 instance will not overlap.
 *
 * @param[in]  aHandle   Handle returned by CpProxyLinnCoUkInfo1Create
 * @param[in]  aCallback The callback to run when the state variable changes
 * @param[in]  aPtr      Data to be passed to the callback
 */
DllExport void CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(THandle aHandle, ZappCallback aCallback, void* aPtr);

/**
 * Query the value of the TrackCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aTrackCount
 */
DllExport void CpProxyLinnCoUkInfo1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount);
/**
 * Query the value of the DetailsCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDetailsCount
 */
DllExport void CpProxyLinnCoUkInfo1PropertyDetailsCount(THandle aHandle, uint32_t* aDetailsCount);
/**
 * Query the value of the MetatextCount property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aMetatextCount
 */
DllExport void CpProxyLinnCoUkInfo1PropertyMetatextCount(THandle aHandle, uint32_t* aMetatextCount);
/**
 * Query the value of the Uri property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aUri
 */
DllExport void CpProxyLinnCoUkInfo1PropertyUri(THandle aHandle, char** aUri);
/**
 * Query the value of the Metadata property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aMetadata
 */
DllExport void CpProxyLinnCoUkInfo1PropertyMetadata(THandle aHandle, char** aMetadata);
/**
 * Query the value of the Duration property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aDuration
 */
DllExport void CpProxyLinnCoUkInfo1PropertyDuration(THandle aHandle, uint32_t* aDuration);
/**
 * Query the value of the BitRate property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aBitRate
 */
DllExport void CpProxyLinnCoUkInfo1PropertyBitRate(THandle aHandle, uint32_t* aBitRate);
/**
 * Query the value of the BitDepth property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aBitDepth
 */
DllExport void CpProxyLinnCoUkInfo1PropertyBitDepth(THandle aHandle, uint32_t* aBitDepth);
/**
 * Query the value of the SampleRate property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aSampleRate
 */
DllExport void CpProxyLinnCoUkInfo1PropertySampleRate(THandle aHandle, uint32_t* aSampleRate);
/**
 * Query the value of the Lossless property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aLossless
 */
DllExport void CpProxyLinnCoUkInfo1PropertyLossless(THandle aHandle, uint32_t* aLossless);
/**
 * Query the value of the CodecName property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aCodecName
 */
DllExport void CpProxyLinnCoUkInfo1PropertyCodecName(THandle aHandle, char** aCodecName);
/**
 * Query the value of the Metatext property.
 *
 * This function is threadsafe and can only be called after the first callback
 * following a call to CpProxyCSubscribe() and before CpProxyCUnsubscribe().
 *
 * @param[out] aMetatext
 */
DllExport void CpProxyLinnCoUkInfo1PropertyMetatext(THandle aHandle, char** aMetatext);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_LINNCOUKINFO1_C

