/**
 * Provider for the upnp.org:ScheduledRecording:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2_C
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetSortCapabilities)(void* aPtr, uint32_t aVersion, char** aSortCaps, uint32_t* aSortLevelCap);
/**
 * Callback which runs when the GetPropertyList action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aDataTypeID
 * @param[out] aPropertyList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetPropertyList)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, char** aPropertyList);
/**
 * Callback which runs when the GetAllowedValues action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[out] aPropertyInfo
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetAllowedValues)(void* aPtr, uint32_t aVersion, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
/**
 * Callback which runs when the GetStateUpdateID action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetStateUpdateID)(void* aPtr, uint32_t aVersion, uint32_t* aId);
/**
 * Callback which runs when the BrowseRecordSchedules action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
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
typedef int32_t (*CallbackScheduledRecording2BrowseRecordSchedules)(void* aPtr, uint32_t aVersion, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the BrowseRecordTasks action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
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
typedef int32_t (*CallbackScheduledRecording2BrowseRecordTasks)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateRecordSchedule action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aElements
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2CreateRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the DeleteRecordSchedule action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2DeleteRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
/**
 * Callback which runs when the GetRecordSchedule action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordSchedule action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2EnableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
/**
 * Callback which runs when the DisableRecordSchedule action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2DisableRecordSchedule)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID);
/**
 * Callback which runs when the DeleteRecordTask action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2DeleteRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordTask action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordTask action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2EnableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
/**
 * Callback which runs when the DisableRecordTask action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2DisableRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
/**
 * Callback which runs when the ResetRecordTask action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2ResetRecordTask)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordScheduleConflicts action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordScheduleID
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetRecordScheduleConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
/**
 * Callback which runs when the GetRecordTaskConflicts action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRecordTaskID
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackScheduledRecording2GetRecordTaskConflicts)(void* aPtr, uint32_t aVersion, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderUpnpOrgScheduledRecording2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 */
DllExport void DvProviderUpnpOrgScheduledRecording2Destroy(THandle aProvider);

/**
 * Register a callback for the action GetSortCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetPropertyList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr);
/**
 * Register a callback for the action GetAllowedValues
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr);
/**
 * Register a callback for the action GetStateUpdateID
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr);
/**
 * Register a callback for the action BrowseRecordSchedules
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr);
/**
 * Register a callback for the action BrowseRecordTasks
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr);
/**
 * Register a callback for the action CreateRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action EnableRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DisableRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action EnableRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action DisableRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action ResetRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordScheduleConflicts
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordTaskConflicts
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aProvider, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

