/**
 * Provider for the upnp.org:ContentDirectory:3 UPnP service
 */
#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY3_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY3_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgContentDirectory3
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetSearchCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetSearchCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSearchCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetSearchCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSearchCaps);
/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetSortCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetSortCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortCaps);
/**
 * Callback which runs when the GetSortExtensionCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortExtensionCaps
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetSortExtensionCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortExtensionCaps);
/**
 * Callback which runs when the GetFeatureList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetFeatureList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aFeatureList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetFeatureList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aFeatureList);
/**
 * Callback which runs when the GetSystemUpdateID action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetSystemUpdateID
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetSystemUpdateID)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aId);
/**
 * Callback which runs when the GetServiceResetToken action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetServiceResetToken
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aResetToken
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetServiceResetToken)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aResetToken);
/**
 * Callback which runs when the Browse action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionBrowse
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
typedef int32_t (STDCALL *CallbackContentDirectory3Browse)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the Search action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionSearch
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
typedef int32_t (STDCALL *CallbackContentDirectory3Search)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionCreateObject
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
typedef int32_t (STDCALL *CallbackContentDirectory3CreateObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
/**
 * Callback which runs when the DestroyObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionDestroyObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3DestroyObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID);
/**
 * Callback which runs when the UpdateObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionUpdateObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 * @param[in]  aCurrentTagValue
 * @param[in]  aNewTagValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3UpdateObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
/**
 * Callback which runs when the MoveObject action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionMoveObject
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aObjectID
 * @param[in]  aNewParentID
 * @param[out] aNewObjectID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3MoveObject)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aObjectID, const char* aNewParentID, char** aNewObjectID);
/**
 * Callback which runs when the ImportResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionImportResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3ImportResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the ExportResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionExportResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aSourceURI
 * @param[in]  aDestinationURI
 * @param[out] aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3ExportResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
/**
 * Callback which runs when the DeleteResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionDeleteResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aResourceURI
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3DeleteResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aResourceURI);
/**
 * Callback which runs when the StopTransferResource action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionStopTransferResource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aTransferID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3StopTransferResource)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aTransferID);
/**
 * Callback which runs when the GetTransferProgress action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetTransferProgress
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
typedef int32_t (STDCALL *CallbackContentDirectory3GetTransferProgress)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
/**
 * Callback which runs when the CreateReference action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionCreateReference
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aContainerID
 * @param[in]  aObjectID
 * @param[out] aNewID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3CreateReference)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, const char* aObjectID, char** aNewID);
/**
 * Callback which runs when the FreeFormQuery action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionFreeFormQuery
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aContainerID
 * @param[in]  aCDSView
 * @param[in]  aQueryRequest
 * @param[out] aQueryResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3FreeFormQuery)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aContainerID, uint32_t aCDSView, const char* aQueryRequest, char** aQueryResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the GetFreeFormQueryCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aFFQCapabilities
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackContentDirectory3GetFreeFormQueryCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aFFQCapabilities);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgContentDirectory3Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3Destroy(THandle aProvider);

/**
 * Enable the SystemUpdateID property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertySystemUpdateID(THandle aProvider);
/**
 * Enable the ContainerUpdateIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyContainerUpdateIDs(THandle aProvider);
/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyLastChange(THandle aProvider);
/**
 * Enable the TransferIDs property.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyTransferIDs(THandle aProvider);

/**
 * Register a callback for the action GetSearchCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSortCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetSortExtensionCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetFeatureList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory3GetFeatureList aCallback, void* aPtr);
/**
 * Register a callback for the action GetSystemUpdateID
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr);
/**
 * Register a callback for the action GetServiceResetToken
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetServiceResetToken(THandle aProvider, CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr);
/**
 * Register a callback for the action Browse
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionBrowse(THandle aProvider, CallbackContentDirectory3Browse aCallback, void* aPtr);
/**
 * Register a callback for the action Search
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionSearch(THandle aProvider, CallbackContentDirectory3Search aCallback, void* aPtr);
/**
 * Register a callback for the action CreateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionCreateObject(THandle aProvider, CallbackContentDirectory3CreateObject aCallback, void* aPtr);
/**
 * Register a callback for the action DestroyObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory3DestroyObject aCallback, void* aPtr);
/**
 * Register a callback for the action UpdateObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory3UpdateObject aCallback, void* aPtr);
/**
 * Register a callback for the action MoveObject
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionMoveObject(THandle aProvider, CallbackContentDirectory3MoveObject aCallback, void* aPtr);
/**
 * Register a callback for the action ImportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionImportResource(THandle aProvider, CallbackContentDirectory3ImportResource aCallback, void* aPtr);
/**
 * Register a callback for the action ExportResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionExportResource(THandle aProvider, CallbackContentDirectory3ExportResource aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory3DeleteResource aCallback, void* aPtr);
/**
 * Register a callback for the action StopTransferResource
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory3StopTransferResource aCallback, void* aPtr);
/**
 * Register a callback for the action GetTransferProgress
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr);
/**
 * Register a callback for the action CreateReference
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionCreateReference(THandle aProvider, CallbackContentDirectory3CreateReference aCallback, void* aPtr);
/**
 * Register a callback for the action FreeFormQuery
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionFreeFormQuery(THandle aProvider, CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr);
/**
 * Register a callback for the action GetFreeFormQueryCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(THandle aProvider, CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr);

/**
 * Set the value of the SystemUpdateID property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertySystemUpdateID has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SystemUpdateID property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertySystemUpdateID has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ContainerUpdateIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyContainerUpdateIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ContainerUpdateIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyContainerUpdateIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue);
/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyLastChange(THandle aProvider, char** aValue);
/**
 * Set the value of the TransferIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyTransferIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the TransferIDs property
 *
 * Can only be called if DvProviderUpnpOrgContentDirectory3EnablePropertyTransferIDs has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgContentDirectory3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyTransferIDs(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY3_C

