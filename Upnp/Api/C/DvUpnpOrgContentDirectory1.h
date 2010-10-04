#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY1_C
#define HEADER_DVUPNPORGCONTENTDIRECTORY1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackContentDirectory1GetSearchCapabilities)(void* aPtr, uint32_t aVersion, char** aSearchCaps);
typedef int32_t (*CallbackContentDirectory1GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps);
typedef int32_t (*CallbackContentDirectory1GetSystemUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
typedef int32_t (*CallbackContentDirectory1Browse)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory1Search)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackContentDirectory1CreateObject)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult);
typedef int32_t (*CallbackContentDirectory1DestroyObject)(void* aPtr, uint32_t aVersion, const char* aObjectID);
typedef int32_t (*CallbackContentDirectory1UpdateObject)(void* aPtr, uint32_t aVersion, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue);
typedef int32_t (*CallbackContentDirectory1ImportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory1ExportResource)(void* aPtr, uint32_t aVersion, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID);
typedef int32_t (*CallbackContentDirectory1StopTransferResource)(void* aPtr, uint32_t aVersion, uint32_t aTransferID);
typedef int32_t (*CallbackContentDirectory1GetTransferProgress)(void* aPtr, uint32_t aVersion, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal);
typedef int32_t (*CallbackContentDirectory1DeleteResource)(void* aPtr, uint32_t aVersion, const char* aResourceURI);
typedef int32_t (*CallbackContentDirectory1CreateReference)(void* aPtr, uint32_t aVersion, const char* aContainerID, const char* aObjectID, char** aNewID);

DllExport THandle DvServiceUpnpOrgContentDirectory1Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgContentDirectory1Destroy(THandle aService);

DllExport void DvServiceUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aService, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aService, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aService, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionBrowse(THandle aService, CallbackContentDirectory1Browse aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionSearch(THandle aService, CallbackContentDirectory1Search aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionCreateObject(THandle aService, CallbackContentDirectory1CreateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aService, CallbackContentDirectory1DestroyObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aService, CallbackContentDirectory1UpdateObject aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionImportResource(THandle aService, CallbackContentDirectory1ImportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionExportResource(THandle aService, CallbackContentDirectory1ExportResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aService, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aService, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aService, CallbackContentDirectory1DeleteResource aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgContentDirectory1EnableActionCreateReference(THandle aService, CallbackContentDirectory1CreateReference aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aService, char** aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aService, uint32_t aValue);
DllExport void DvServiceUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY1_C

