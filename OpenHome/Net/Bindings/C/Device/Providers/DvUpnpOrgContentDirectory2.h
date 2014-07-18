/**
 * Provider for the upnp.org:ContentDirectory:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY2_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY2_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgContentDirectory2
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetSearchCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSearchCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetSearchCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSearchCaps);
/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetSortCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortCaps);
/**
 * Callback which runs when the GetSortExtensionCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortExtensionCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetSortExtensionCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortExtensionCaps);
/**
 * Callback which runs when the GetFeatureList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aFeatureList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetFeatureList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aFeatureList);
/**
 * Callback which runs when the GetSystemUpdateID action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetSystemUpdateID)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aId);
/**
 * Callback which runs when the Browse action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionBrowse
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
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
typedef int32_t (STDCALL *CallbackContentDirectory2Browse)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the Search action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionSearch
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
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
typedef int32_t (STDCALL *CallbackContentDirectory2Search)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionCreateObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aContainerID
 * @param[in]  aElements
 * @param[out] aObjectID
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2CreateObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
/**
 * Callback which runs when the DestroyObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2DestroyObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID);
/**
 * Callback which runs when the UpdateObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 * @param[in]  aCurrentTagValue
 * @param[in]  aNewTagValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2UpdateObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
/**
 * Callback which runs when the MoveObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionMoveObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 * @param[in]  aNewParentID
 * @param[out] aNewObjectID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2MoveObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aNewParentID, char** aNewObjectID);
/**
 * Callback which runs when the ImportResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionImportResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2ImportResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the ExportResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionExportResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2ExportResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the DeleteResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aResourceURI
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2DeleteResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aResourceURI);
/**
 * Callback which runs when the StopTransferResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2StopTransferResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aTransferID);
/**
 * Callback which runs when the GetTransferProgress action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aTransferID
 * @param[out] aTransferStatus
 * @param[out] aTransferLength
 * @param[out] aTransferTotal
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2GetTransferProgress)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
/**
 * Callback which runs when the CreateReference action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory2EnableActionCreateReference
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aContainerID
 * @param[in]  aObjectID
 * @param[out] aNewID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory2CreateReference)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aObjectID, char** aNewID);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgContentDirectory2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2Destroy(THandle aProvider);

/**
 * Enable the SystemUpdateID property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertySystemUpdateID(THandle aProvider);
/**
 * Enable the ContainerUpdateIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertyContainerUpdateIDs(THandle aProvider);
/**
 * Enable the TransferIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertyTransferIDs(THandle aProvider);

/**
 * Register a callback for the action GetSearchCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSortCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSortExtensionCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetFeatureList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr);
/**
 * Register a callback for the action GetSystemUpdateID
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr);
/**
 * Register a callback for the action Browse
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionBrowse(THandle aProvider, CallbackContentDirectory2Browse aCallback, void* aPtr);
/**
 * Register a callback for the action Search
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionSearch(THandle aProvider, CallbackContentDirectory2Search aCallback, void* aPtr);
/**
 * Register a callback for the action CreateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionCreateObject(THandle aProvider, CallbackContentDirectory2CreateObject aCallback, void* aPtr);
/**
 * Register a callback for the action DestroyObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory2DestroyObject aCallback, void* aPtr);
/**
 * Register a callback for the action UpdateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory2UpdateObject aCallback, void* aPtr);
/**
 * Register a callback for the action MoveObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionMoveObject(THandle aProvider, CallbackContentDirectory2MoveObject aCallback, void* aPtr);
/**
 * Register a callback for the action ImportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionImportResource(THandle aProvider, CallbackContentDirectory2ImportResource aCallback, void* aPtr);
/**
 * Register a callback for the action ExportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionExportResource(THandle aProvider, CallbackContentDirectory2ExportResource aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory2DeleteResource aCallback, void* aPtr);
/**
 * Register a callback for the action StopTransferResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransferProgress
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr);
/**
 * Register a callback for the action CreateReference
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionCreateReference(THandle aProvider, CallbackContentDirectory2CreateReference aCallback, void* aPtr);

/**
 * Set the value of the SystemUpdateID property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertySystemUpdateID has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SystemUpdateID property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertySystemUpdateID has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ContainerUpdateIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertyContainerUpdateIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ContainerUpdateIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertyContainerUpdateIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue);
/**
 * Set the value of the TransferIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertyTransferIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransferIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory2EnablePropertyTransferIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2_C

