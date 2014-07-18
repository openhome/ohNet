/**
 * Provider for the av.openhome.org:Radio:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGRADIO1_C
#define HEADER_DVAVOPENHOMEORGRADIO1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgRadio1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionPlay
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Play)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Pause action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionPause
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Pause)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionStop
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Stop)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the SeekSecondAbsolute action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondAbsolute
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1SeekSecondAbsolute)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the SeekSecondRelative action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondRelative
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1SeekSecondRelative)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aValue);
/**
 * Callback which runs when the Channel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionChannel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Channel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aUri, char** aMetadata);
/**
 * Callback which runs when the SetChannel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionSetChannel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aUri
 * @param[in]  aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1SetChannel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aUri, const char* aMetadata);
/**
 * Callback which runs when the TransportState action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionTransportState
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1TransportState)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the Id action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Id)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SetId action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionSetId
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[in]  aUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1SetId)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue, const char* aUri);
/**
 * Callback which runs when the Read action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionRead
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aId
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1Read)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aId, char** aMetadata);
/**
 * Callback which runs when the ReadList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionReadList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIdList
 * @param[out] aChannelList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1ReadList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aIdList, char** aChannelList);
/**
 * Callback which runs when the IdArray action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionIdArray
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aToken
 * @param[out] aArray
 * @param[out] aArrayLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1IdArray)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aToken, char** aArray, uint32_t* aArrayLen);
/**
 * Callback which runs when the IdArrayChanged action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionIdArrayChanged
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aToken
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1IdArrayChanged)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aToken, uint32_t* aValue);
/**
 * Callback which runs when the ChannelsMax action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionChannelsMax
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1ChannelsMax)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the ProtocolInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgRadio1EnableActionProtocolInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRadio1ProtocolInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgRadio1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1Destroy(THandle aProvider);

/**
 * Enable the Uri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyUri(THandle aProvider);
/**
 * Enable the Metadata property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyMetadata(THandle aProvider);
/**
 * Enable the TransportState property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyTransportState(THandle aProvider);
/**
 * Enable the Id property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyId(THandle aProvider);
/**
 * Enable the IdArray property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyIdArray(THandle aProvider);
/**
 * Enable the ChannelsMax property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyChannelsMax(THandle aProvider);
/**
 * Enable the ProtocolInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnablePropertyProtocolInfo(THandle aProvider);

/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionPlay(THandle aProvider, CallbackRadio1Play aCallback, void* aPtr);
/**
 * Register a callback for the action Pause
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionPause(THandle aProvider, CallbackRadio1Pause aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionStop(THandle aProvider, CallbackRadio1Stop aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondAbsolute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondAbsolute(THandle aProvider, CallbackRadio1SeekSecondAbsolute aCallback, void* aPtr);
/**
 * Register a callback for the action SeekSecondRelative
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSeekSecondRelative(THandle aProvider, CallbackRadio1SeekSecondRelative aCallback, void* aPtr);
/**
 * Register a callback for the action Channel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionChannel(THandle aProvider, CallbackRadio1Channel aCallback, void* aPtr);
/**
 * Register a callback for the action SetChannel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSetChannel(THandle aProvider, CallbackRadio1SetChannel aCallback, void* aPtr);
/**
 * Register a callback for the action TransportState
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionTransportState(THandle aProvider, CallbackRadio1TransportState aCallback, void* aPtr);
/**
 * Register a callback for the action Id
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionId(THandle aProvider, CallbackRadio1Id aCallback, void* aPtr);
/**
 * Register a callback for the action SetId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionSetId(THandle aProvider, CallbackRadio1SetId aCallback, void* aPtr);
/**
 * Register a callback for the action Read
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionRead(THandle aProvider, CallbackRadio1Read aCallback, void* aPtr);
/**
 * Register a callback for the action ReadList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionReadList(THandle aProvider, CallbackRadio1ReadList aCallback, void* aPtr);
/**
 * Register a callback for the action IdArray
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionIdArray(THandle aProvider, CallbackRadio1IdArray aCallback, void* aPtr);
/**
 * Register a callback for the action IdArrayChanged
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionIdArrayChanged(THandle aProvider, CallbackRadio1IdArrayChanged aCallback, void* aPtr);
/**
 * Register a callback for the action ChannelsMax
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionChannelsMax(THandle aProvider, CallbackRadio1ChannelsMax aCallback, void* aPtr);
/**
 * Register a callback for the action ProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1EnableActionProtocolInfo(THandle aProvider, CallbackRadio1ProtocolInfo aCallback, void* aPtr);

/**
 * Set the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyTransportState(THandle aProvider, char** aValue);
/**
 * Set the value of the Id property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyId has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyId(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Id property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyId has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyId(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the IdArray property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyIdArray has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen);
/**
 * Set the value of the ChannelsMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyChannelsMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyChannelsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ChannelsMax property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyChannelsMax has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyChannelsMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgRadio1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgRadio1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgRadio1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgRadio1GetPropertyProtocolInfo(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGRADIO1_C

