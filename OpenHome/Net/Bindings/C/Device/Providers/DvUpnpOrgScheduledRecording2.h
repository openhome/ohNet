/**
 * Provider for the upnp.org:ScheduledRecording:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING2_C
#define HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgScheduledRecording2
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetSortCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortCaps, uint32_t* aSortLevelCap);
/**
 * Callback which runs when the GetPropertyList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aDataTypeID
 * @param[out] aPropertyList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetPropertyList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aDataTypeID, char** aPropertyList);
/**
 * Callback which runs when the GetAllowedValues action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[out] aPropertyInfo
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetAllowedValues)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
/**
 * Callback which runs when the GetStateUpdateID action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetStateUpdateID)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aId);
/**
 * Callback which runs when the BrowseRecordSchedules action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
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
typedef int32_t (STDCALL *CallbackScheduledRecording2BrowseRecordSchedules)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the BrowseRecordTasks action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
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
typedef int32_t (STDCALL *CallbackScheduledRecording2BrowseRecordTasks)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aElements
 * @param[out] aRecordScheduleID
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2CreateRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the DeleteRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2DeleteRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the GetRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2EnableRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the DisableRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2DisableRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the DeleteRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2DeleteRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 * @param[in]  aFilter
 * @param[out] aResult
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2EnableRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the DisableRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2DisableRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the ResetRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2ResetRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordScheduleConflicts action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetRecordScheduleConflicts)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
/**
 * Callback which runs when the GetRecordTaskConflicts action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording2GetRecordTaskConflicts)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgScheduledRecording2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2Destroy(THandle aProvider);

/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnablePropertyLastChange(THandle aProvider);

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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgScheduledRecording2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgScheduledRecording2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING2_C

