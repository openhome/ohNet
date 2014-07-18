/**
 * Provider for the av.openhome.org:Receiver:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGRECEIVER1_C
#define HEADER_DVAVOPENHOMEORGRECEIVER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgReceiver1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Play action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionPlay
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1Play)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the Stop action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionStop
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1Stop)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the SetSender action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionSetSender
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aUri
 * @param[in]  aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1SetSender)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aUri, const char* aMetadata);
/**
 * Callback which runs when the Sender action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionSender
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aUri
 * @param[out] aMetadata
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1Sender)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aUri, char** aMetadata);
/**
 * Callback which runs when the ProtocolInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionProtocolInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1ProtocolInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the TransportState action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgReceiver1EnableActionTransportState
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackReceiver1TransportState)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgReceiver1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1Destroy(THandle aProvider);

/**
 * Enable the Uri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyUri(THandle aProvider);
/**
 * Enable the Metadata property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyMetadata(THandle aProvider);
/**
 * Enable the TransportState property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyTransportState(THandle aProvider);
/**
 * Enable the ProtocolInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnablePropertyProtocolInfo(THandle aProvider);

/**
 * Register a callback for the action Play
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionPlay(THandle aProvider, CallbackReceiver1Play aCallback, void* aPtr);
/**
 * Register a callback for the action Stop
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionStop(THandle aProvider, CallbackReceiver1Stop aCallback, void* aPtr);
/**
 * Register a callback for the action SetSender
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionSetSender(THandle aProvider, CallbackReceiver1SetSender aCallback, void* aPtr);
/**
 * Register a callback for the action Sender
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionSender(THandle aProvider, CallbackReceiver1Sender aCallback, void* aPtr);
/**
 * Register a callback for the action ProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionProtocolInfo(THandle aProvider, CallbackReceiver1ProtocolInfo aCallback, void* aPtr);
/**
 * Register a callback for the action TransportState
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1EnableActionTransportState(THandle aProvider, CallbackReceiver1TransportState aCallback, void* aPtr);

/**
 * Set the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Uri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyTransportState(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransportState property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyTransportState has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyTransportState(THandle aProvider, char** aValue);
/**
 * Set the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgReceiver1SetPropertyProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProtocolInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgReceiver1EnablePropertyProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgReceiver1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgReceiver1GetPropertyProtocolInfo(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGRECEIVER1_C

