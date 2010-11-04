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

DllExport THandle DvProviderUpnpOrgContentDirectory2Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgContentDirectory2Destroy(THandle aProvider);

DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionBrowse(THandle aProvider, CallbackContentDirectory2Browse aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionSearch(THandle aProvider, CallbackContentDirectory2Search aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionCreateObject(THandle aProvider, CallbackContentDirectory2CreateObject aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory2DestroyObject aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory2UpdateObject aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionMoveObject(THandle aProvider, CallbackContentDirectory2MoveObject aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionImportResource(THandle aProvider, CallbackContentDirectory2ImportResource aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionExportResource(THandle aProvider, CallbackContentDirectory2ExportResource aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory2DeleteResource aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgContentDirectory2EnableActionCreateReference(THandle aProvider, CallbackContentDirectory2CreateReference aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue);
DllExport int32_t DvProviderUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2_C

