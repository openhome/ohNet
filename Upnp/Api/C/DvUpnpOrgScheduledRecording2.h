#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2_C
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackScheduledRecording2GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps, uint32_t* aSortLevelCap);
typedef int32_t (*CallbackScheduledRecording2GetPropertyList)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, char** aPropertyList);
typedef int32_t (*CallbackScheduledRecording2GetAllowedValues)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
typedef int32_t (*CallbackScheduledRecording2GetStateUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
typedef int32_t (*CallbackScheduledRecording2BrowseRecordSchedules)(void* aPtr, uint32_t aVersion, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2BrowseRecordTasks)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2CreateRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2DeleteRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording2GetRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2EnableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording2DisableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
typedef int32_t (*CallbackScheduledRecording2DeleteRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording2GetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2EnableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording2DisableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording2ResetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
typedef int32_t (*CallbackScheduledRecording2GetRecordScheduleConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
typedef int32_t (*CallbackScheduledRecording2GetRecordTaskConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);

DllExport THandle DvServiceUpnpOrgScheduledRecording2Create(DvDeviceC aDevice);
DllExport void DvServiceUpnpOrgScheduledRecording2Destroy(THandle aService);

DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aService, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aService, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aService, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aService, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aService, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aService, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aService, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aService, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aService, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aService, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aService, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aService, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aService, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aService, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aService, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aService, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aService, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr);
DllExport void DvServiceUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aService, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr);

DllExport int32_t DvServiceUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aService, const char* aValue);
DllExport void DvServiceUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

