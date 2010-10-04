#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY3_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY3_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackContentDirectory3GetSearchCapabilities)(void* aPtr, uint32_t aVersion, char** aSearchCaps);
typedef int32_t (*CallbackContentDirectory3GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps);
typedef int32_t (*CallbackContentDirectory3GetSortExtensionCapabilities)(void* aPtr, uint32_t aVersion, char** aSortExtensionCaps);
typedef int32_t (*CallbackContentDirectory3GetFeatureList)(void* aPtr, uint32_t aVersion, char** aFeatureList);
typedef int32_t (*CallbackContentDirectory3GetSystemUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
typedef int32_t (*CallbackContentDirectory3GetServiceResetToken)(void* aPtr, uint32_t aVersion, char** aResetToken);
typedef int32_t (*CallbackContentDirectory3Browse)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory3Search)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory3CreateObject)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
typedef int32_t (*CallbackContentDirectory3DestroyObject)(void* aPtr, uint32_t aVersion, const char* aObjectID);
typedef int32_t (*CallbackContentDirectory3UpdateObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
typedef int32_t (*CallbackContentDirectory3MoveObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aNewParentID, char** aNewObjectID);
typedef int32_t (*CallbackContentDirectory3ImportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory3ExportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory3DeleteResource)(void* aPtr, uint32_t aVersion, const char* aResourceURI);
typedef int32_t (*CallbackContentDirectory3StopTransferResource)(void* aPtr, uint32_t aVersion, uint32_t aTransferID);
typedef int32_t (*CallbackContentDirectory3GetTransferProgress)(void* aPtr, uint32_t aVersion, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
typedef int32_t (*CallbackContentDirectory3CreateReference)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aObjectID, char** aNewID);
typedef int32_t (*CallbackContentDirectory3FreeFormQuery)(void* aPtr, uint32_t aVersion, const char* aContainerID, uint32_t aCDSView, const char* aQueryRequest, char** aQueryResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory3GetFreeFormQueryCapabilities)(void* aPtr, uint32_t aVersion, char** aFFQCapabilities);

DllExport THandle DvServiceUpnpOrgContentDirectory3Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgContentDirectory3Destroy(THandle aService);

DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(THandle aService, CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetSortCapabilities(THandle aService, CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(THandle aService, CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetFeatureList(THandle aService, CallbackContentDirectory3GetFeatureList aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(THandle aService, CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetServiceResetToken(THandle aService, CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionBrowse(THandle aService, CallbackContentDirectory3Browse aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionSearch(THandle aService, CallbackContentDirectory3Search aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionCreateObject(THandle aService, CallbackContentDirectory3CreateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionDestroyObject(THandle aService, CallbackContentDirectory3DestroyObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionUpdateObject(THandle aService, CallbackContentDirectory3UpdateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionMoveObject(THandle aService, CallbackContentDirectory3MoveObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionImportResource(THandle aService, CallbackContentDirectory3ImportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionExportResource(THandle aService, CallbackContentDirectory3ExportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionDeleteResource(THandle aService, CallbackContentDirectory3DeleteResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionStopTransferResource(THandle aService, CallbackContentDirectory3StopTransferResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetTransferProgress(THandle aService, CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionCreateReference(THandle aService, CallbackContentDirectory3CreateReference aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionFreeFormQuery(THandle aService, CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(THandle aService, CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgContentDirectory3SetPropertySystemUpdateID(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgContentDirectory3GetPropertySystemUpdateID(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory3SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory3GetPropertyLastChange(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory3SetPropertyTransferIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory3GetPropertyTransferIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY3_C

