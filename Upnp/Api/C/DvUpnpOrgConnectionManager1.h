/**
 * Provider for the upnp.org:ConnectionManager:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1_C
#define HEADER_DVUPNPORGCONNECTIONMANAGER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the GetProtocolInfo action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aSource
 * @param[out] aSink
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackConnectionManager1GetProtocolInfo)(void* aPtr, uint32_t aVersion, char** aSource, char** aSink);
/**
 * Callback which runs when the PrepareForConnection action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
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
typedef int32_t (*CallbackConnectionManager1PrepareForConnection)(void* aPtr, uint32_t aVersion, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID);
/**
 * Callback which runs when the ConnectionComplete action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aConnectionID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackConnectionManager1ConnectionComplete)(void* aPtr, uint32_t aVersion, int32_t aConnectionID);
/**
 * Callback which runs when the GetCurrentConnectionIDs action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aConnectionIDs
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackConnectionManager1GetCurrentConnectionIDs)(void* aPtr, uint32_t aVersion, char** aConnectionIDs);
/**
 * Callback which runs when the GetCurrentConnectionInfo action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
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
typedef int32_t (*CallbackConnectionManager1GetCurrentConnectionInfo)(void* aPtr, uint32_t aVersion, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderUpnpOrgConnectionManager1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 */
DllExport void DvProviderUpnpOrgConnectionManager1Destroy(THandle aProvider);

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
DllExport void DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr);
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
DllExport void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr);

/**
 * Set the value of the SourceProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the SinkProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SinkProtocolInfo property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the CurrentConnectionIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the CurrentConnectionIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgConnectionManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1_C

