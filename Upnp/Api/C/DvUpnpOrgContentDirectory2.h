#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY2_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackContentDirectory2GetSearchCapabilities)(void* aPtr, uint32_t aVersion, char** aSearchCaps);
typedef int32_t (*CallbackContentDirectory2GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps);
typedef int32_t (*CallbackContentDirectory2GetSortExtensionCapabilities)(void* aPtr, uint32_t aVersion, char** aSortExtensionCaps);
typedef int32_t (*CallbackContentDirectory2GetFeatureList)(void* aPtr, uint32_t aVersion, char** aFeatureList);
typedef int32_t (*CallbackContentDirectory2GetSystemUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
typedef int32_t (*CallbackContentDirectory2Browse)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory2Search)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory2CreateObject)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
typedef int32_t (*CallbackContentDirectory2DestroyObject)(void* aPtr, uint32_t aVersion, const char* aObjectID);
typedef int32_t (*CallbackContentDirectory2UpdateObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
typedef int32_t (*CallbackContentDirectory2MoveObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aNewParentID, char** aNewObjectID);
typedef int32_t (*CallbackContentDirectory2ImportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory2ExportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory2DeleteResource)(void* aPtr, uint32_t aVersion, const char* aResourceURI);
typedef int32_t (*CallbackContentDirectory2StopTransferResource)(void* aPtr, uint32_t aVersion, uint32_t aTransferID);
typedef int32_t (*CallbackContentDirectory2GetTransferProgress)(void* aPtr, uint32_t aVersion, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
typedef int32_t (*CallbackContentDirectory2CreateReference)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aObjectID, char** aNewID);

DllExport THandle DvServiceUpnpOrgContentDirectory2Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgContentDirectory2Destroy(THandle aService);

DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aService, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aService, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aService, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aService, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aService, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionBrowse(THandle aService, CallbackContentDirectory2Browse aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionSearch(THandle aService, CallbackContentDirectory2Search aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionCreateObject(THandle aService, CallbackContentDirectory2CreateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aService, CallbackContentDirectory2DestroyObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aService, CallbackContentDirectory2UpdateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionMoveObject(THandle aService, CallbackContentDirectory2MoveObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionImportResource(THandle aService, CallbackContentDirectory2ImportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionExportResource(THandle aService, CallbackContentDirectory2ExportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aService, CallbackContentDirectory2DeleteResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aService, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aService, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory2EnableActionCreateReference(THandle aService, CallbackContentDirectory2CreateReference aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2_C

