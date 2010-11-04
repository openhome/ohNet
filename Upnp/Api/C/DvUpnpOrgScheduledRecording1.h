#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING1_C
#define HEADER_DVUPNPORGSCHEDULEDRECORDING1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackScheduledRecording1GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps, uint32_t* aSortLevelCap);
typedef int32_t (*CallbackScheduledRecording1GetPropertyList)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, char** aPropertyList);
typedef int32_t (*CallbackScheduledRecording1GetAllowedValues)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
typedef int32_t (*CallbackScheduledRecording1GetStateUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
typedef int32_t (*CallbackScheduledRecording1BrowseRecordSchedules)(void* aPtr, uint32_t aVersion, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1BrowseRecordTasks)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1CreateRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1DeleteRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording1GetRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1EnableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording1DisableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording1DeleteRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording1GetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1EnableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording1DisableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording1ResetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording1GetRecordScheduleConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording1GetRecordTaskConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);

DllExport THandle DvProviderUpnpOrgScheduledRecording1Create(DvDeviceC aDevice);
DllExport void DvProviderUpnpOrgScheduledRecording1Destroy(THandle aService);

DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetSortCapabilities(THandle aService, CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetPropertyList(THandle aService, CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetAllowedValues(THandle aService, CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetStateUpdateID(THandle aService, CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordSchedules(THandle aService, CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordTasks(THandle aService, CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionCreateRecordSchedule(THandle aService, CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordSchedule(THandle aService, CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordSchedule(THandle aService, CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordSchedule(THandle aService, CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordSchedule(THandle aService, CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordTask(THandle aService, CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTask(THandle aService, CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordTask(THandle aService, CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordTask(THandle aService, CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionResetRecordTask(THandle aService, CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordScheduleConflicts(THandle aService, CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr);
DllExport void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTaskConflicts(THandle aService, CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr);

DllExport int32_t DvProviderUpnpOrgScheduledRecording1SetPropertyLastChange(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderUpnpOrgScheduledRecording1GetPropertyLastChange(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING1_C

