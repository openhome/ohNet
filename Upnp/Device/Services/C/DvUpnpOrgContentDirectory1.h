/**
 * Provider for the upnp.org:ContentDirectory:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY1_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY1_C

#include <OhNetDefines.h>
#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgContentDirectory1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetSearchCapabilities action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionGetSearchCapabilities
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aSearchCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1GetSearchCapabilities)(void* aPtr, uint32_t aVersion, char** aSearchCaps);
/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionGetSortCapabilities
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aSortCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps);
/**
 * Callback which runs when the GetSystemUpdateID action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionGetSystemUpdateID
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1GetSystemUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
/**
 * Callback which runs when the Browse action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionBrowse
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aObjectID
 * @param[in]  aBrowseFlag
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1Browse)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the Search action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionSearch
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aContainerID
 * @param[in]  aSearchCriteria
 * @param[in]  aFilter
 * @param[in]  aStartingIndex
 * @param[in]  aRequestedCount
 * @param[in]  aSortCriteria
 * @param[out] aResult
 * @param[out] aNumberReturned
 * @param[out] aTotalMatches
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1Search)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateObject action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionCreateObject
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aContainerID
 * @param[in]  aElements
 * @param[out] aObjectID
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1CreateObject)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
/**
 * Callback which runs when the DestroyObject action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionDestroyObject
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aObjectID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1DestroyObject)(void* aPtr, uint32_t aVersion, const char* aObjectID);
/**
 * Callback which runs when the UpdateObject action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionUpdateObject
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aObjectID
 * @param[in]  aCurrentTagValue
 * @param[in]  aNewTagValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1UpdateObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
/**
 * Callback which runs when the ImportResource action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionImportResource
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1ImportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the ExportResource action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionExportResource
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1ExportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the StopTransferResource action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionStopTransferResource
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1StopTransferResource)(void* aPtr, uint32_t aVersion, uint32_t aTransferID);
/**
 * Callback which runs when the GetTransferProgress action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionGetTransferProgress
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aTransferID
 * @param[out] aTransferStatus
 * @param[out] aTransferLength
 * @param[out] aTransferTotal
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1GetTransferProgress)(void* aPtr, uint32_t aVersion, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
/**
 * Callback which runs when the DeleteResource action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionDeleteResource
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aResourceURI
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1DeleteResource)(void* aPtr, uint32_t aVersion, const char* aResourceURI);
/**
 * Callback which runs when the CreateReference action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgContentDirectory1EnableActionCreateReference
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aContainerID
 * @param[in]  aObjectID
 * @param[out] aNewID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory1CreateReference)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aObjectID, char** aNewID);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgContentDirectory1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1Destroy(THandle aProvider);

/**
 * Register a callback for the action GetSearchCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSortCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSystemUpdateID
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr);
/**
 * Register a callback for the action Browse
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionBrowse(THandle aProvider, CallbackContentDirectory1Browse aCallback, void* aPtr);
/**
 * Register a callback for the action Search
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionSearch(THandle aProvider, CallbackContentDirectory1Search aCallback, void* aPtr);
/**
 * Register a callback for the action CreateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionCreateObject(THandle aProvider, CallbackContentDirectory1CreateObject aCallback, void* aPtr);
/**
 * Register a callback for the action DestroyObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory1DestroyObject aCallback, void* aPtr);
/**
 * Register a callback for the action UpdateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory1UpdateObject aCallback, void* aPtr);
/**
 * Register a callback for the action ImportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionImportResource(THandle aProvider, CallbackContentDirectory1ImportResource aCallback, void* aPtr);
/**
 * Register a callback for the action ExportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionExportResource(THandle aProvider, CallbackContentDirectory1ExportResource aCallback, void* aPtr);
/**
 * Register a callback for the action StopTransferResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransferProgress
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory1DeleteResource aCallback, void* aPtr);
/**
 * Register a callback for the action CreateReference
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionCreateReference(THandle aProvider, CallbackContentDirectory1CreateReference aCallback, void* aPtr);

/**
 * Set the value of the TransferIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransferIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aProvider, char** aValue);
/**
 * Set the value of the SystemUpdateID property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SystemUpdateID property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ContainerUpdateIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ContainerUpdateIDs property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY1_C

