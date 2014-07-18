/**
 * Provider for the upnp.org:ConnectionManager:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1_C
#define HEADER_DVUPNPORGCONNECTIONMANAGER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgConnectionManager1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetProtocolInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSource
 * @param[out] aSink
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager1GetProtocolInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSource, char** aSink);
/**
 * Callback which runs when the PrepareForConnection action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRemoteProtocolInfo
 * @param[in]  aPeerConnectionManager
 * @param[in]  aPeerConnectionID
 * @param[in]  aDirection
 * @param[out] aConnectionID
 * @param[out] aAVTransportID
 * @param[out] aRcsID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager1PrepareForConnection)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
/**
 * Callback which runs when the ConnectionComplete action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aConnectionID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager1ConnectionComplete)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aConnectionID);
/**
 * Callback which runs when the GetCurrentConnectionIDs action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aConnectionIDs
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager1GetCurrentConnectionIDs)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aConnectionIDs);
/**
 * Callback which runs when the GetCurrentConnectionInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aConnectionID
 * @param[out] aRcsID
 * @param[out] aAVTransportID
 * @param[out] aProtocolInfo
 * @param[out] aPeerConnectionManager
 * @param[out] aPeerConnectionID
 * @param[out] aDirection
 * @param[out] aStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager1GetCurrentConnectionInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgConnectionManager1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1Destroy(THandle aProvider);

/**
 * Enable the SourceProtocolInfo property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnablePropertySourceProtocolInfo(THandle aProvider);
/**
 * Enable the SinkProtocolInfo property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnablePropertySinkProtocolInfo(THandle aProvider);
/**
 * Enable the CurrentConnectionIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnablePropertyCurrentConnectionIDs(THandle aProvider);

/**
 * Register a callback for the action GetProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr);
/**
 * Register a callback for the action PrepareForConnection
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr);
/**
 * Register a callback for the action ConnectionComplete
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentConnectionIDs
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentConnectionInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr);

/**
 * Set the value of the SourceProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertySourceProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertySourceProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the SinkProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertySinkProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SinkProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertySinkProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the CurrentConnectionIDs property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertyCurrentConnectionIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CurrentConnectionIDs property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager1EnablePropertyCurrentConnectionIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1_C

