/**
 * Provider for the upnp.org:ConnectionManager:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2_C
#define HEADER_DVUPNPORGCONNECTIONMANAGER2_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgConnectionManager2
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetProtocolInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager2EnableActionGetProtocolInfo
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSource
 * @param[out] aSink
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager2GetProtocolInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSource, char** aSink);
/**
 * Callback which runs when the PrepareForConnection action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager2EnableActionPrepareForConnection
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
typedef int32_t (STDCALL *CallbackConnectionManager2PrepareForConnection)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
/**
 * Callback which runs when the ConnectionComplete action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager2EnableActionConnectionComplete
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aConnectionID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager2ConnectionComplete)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aConnectionID);
/**
 * Callback which runs when the GetCurrentConnectionIDs action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aConnectionIDs
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackConnectionManager2GetCurrentConnectionIDs)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aConnectionIDs);
/**
 * Callback which runs when the GetCurrentConnectionInfo action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo
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
typedef int32_t (STDCALL *CallbackConnectionManager2GetCurrentConnectionInfo)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgConnectionManager2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2Destroy(THandle aProvider);

/**
 * Enable the SourceProtocolInfo property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertySourceProtocolInfo(THandle aProvider);
/**
 * Enable the SinkProtocolInfo property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertySinkProtocolInfo(THandle aProvider);
/**
 * Enable the CurrentConnectionIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnablePropertyCurrentConnectionIDs(THandle aProvider);

/**
 * Register a callback for the action GetProtocolInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
/**
 * Register a callback for the action PrepareForConnection
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
/**
 * Register a callback for the action ConnectionComplete
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentConnectionIDs
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
/**
 * Register a callback for the action GetCurrentConnectionInfo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);

/**
 * Set the value of the SourceProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertySourceProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertySourceProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the SinkProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertySinkProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SinkProtocolInfo property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertySinkProtocolInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the CurrentConnectionIDs property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertyCurrentConnectionIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CurrentConnectionIDs property
 *
 * Can only be called if DvProviderUpnpOrgConnectionManager2EnablePropertyCurrentConnectionIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2_C

