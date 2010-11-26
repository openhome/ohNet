/**
 * Provider for the linn.co.uk:Ds:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKDS1_C
#define HEADER_DVLINNCOUKDS1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkDs1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionPlay
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1Play)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionPause
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1Pause)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionStop
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1Stop)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SeekSecondAbsolute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSecond
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1SeekSecondAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aaSecond);
/**
 * Callback which runs when the SeekSecondRelative action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionSeekSecondRelative
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSecond
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1SeekSecondRelative)(void* aPtr, uint32_t aVersion, int32_t aaSecond);
/**
 * Callback which runs when the SeekTrackId action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionSeekTrackId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaTrackId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1SeekTrackId)(void* aPtr, uint32_t aVersion, uint32_t aaTrackId);
/**
 * Callback which runs when the SeekTrackAbsolute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaTrack
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1SeekTrackAbsolute)(void* aPtr, uint32_t aVersion, uint32_t aaTrack);
/**
 * Callback which runs when the SeekTrackRelative action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionSeekTrackRelative
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaTrack
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1SeekTrackRelative)(void* aPtr, uint32_t aVersion, int32_t aaTrack);
/**
 * Callback which runs when the State action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionState
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaTransportState
 * @param[out] aaTrackDuration
 * @param[out] aaTrackBitRate
 * @param[out] aaTrackLossless
 * @param[out] aaTrackBitDepth
 * @param[out] aaTrackSampleRate
 * @param[out] aaTrackCodecName
 * @param[out] aaTrackId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1State)(void* aPtr, uint32_t aVersion, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId);
/**
 * Callback which runs when the ProtocolInfo action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDs1EnableActionProtocolInfo
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSupportedProtocols
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDs1ProtocolInfo)(void* aPtr, uint32_t aVersion, char** aaSupportedProtocols);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkDs1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 */
DllExport void DvProviderLinnCoUkDs1Destroy(THandle aProvider);

/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionPlay(THandle aProvider, CallbackDs1Play aCallback, void* aPtr);
/**
 * Register a callback for the action Pause
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionPause(THandle aProvider, CallbackDs1Pause aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionStop(THandle aProvider, CallbackDs1Stop aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondAbsolute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackDs1SeekSecondAbsolute aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondRelative
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionSeekSecondRelative(THandle aProvider, CallbackDs1SeekSecondRelative aCallback, void* aPtr);
/**
 * Register a callback for the action SeekTrackId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackId(THandle aProvider, CallbackDs1SeekTrackId aCallback, void* aPtr);
/**
 * Register a callback for the action SeekTrackAbsolute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackAbsolute(THandle aProvider, CallbackDs1SeekTrackAbsolute aCallback, void* aPtr);
/**
 * Register a callback for the action SeekTrackRelative
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionSeekTrackRelative(THandle aProvider, CallbackDs1SeekTrackRelative aCallback, void* aPtr);
/**
 * Register a callback for the action State
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionState(THandle aProvider, CallbackDs1State aCallback, void* aPtr);
/**
 * Register a callback for the action ProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDs1EnableActionProtocolInfo(THandle aProvider, CallbackDs1ProtocolInfo aCallback, void* aPtr);

/**
 * Set the value of the SupportedProtocols property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertySupportedProtocols(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SupportedProtocols property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkDs1GetPropertySupportedProtocols(THandle aProvider, char** aValue);
/**
 * Set the value of the TrackDuration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackDuration(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackDuration property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackDuration(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TrackBitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackBitRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TrackLossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackLossless(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackLossless property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackLossless(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TrackBitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackBitDepth(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackBitDepth property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackBitDepth(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TrackSampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackSampleRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackSampleRate property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackSampleRate(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TrackCodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackCodecName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackCodecName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackCodecName(THandle aProvider, char** aValue);
/**
 * Set the value of the TrackId property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTrackId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TrackId property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTrackId(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the TransportState property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDs1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransportState property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDs1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkDs1GetPropertyTransportState(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDS1_C

