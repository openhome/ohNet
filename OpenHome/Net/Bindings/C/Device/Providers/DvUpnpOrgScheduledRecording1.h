/**
 * Provider for the upnp.org:ScheduledRecording:1 UPnP service
 */
#ifndef HEADER_DVUPNPORGSCHEDULEDRECORDING1_C
#define HEADER_DVUPNPORGSCHEDULEDRECORDING1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgScheduledRecording1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetSortCapabilities action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetSortCapabilities
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aSortCaps
 * @param[out] aSortLevelCap
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetSortCapabilities)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aSortCaps, uint32_t* aSortLevelCap);
/**
 * Callback which runs when the GetPropertyList action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetPropertyList
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aDataTypeID
 * @param[out] aPropertyList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetPropertyList)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aDataTypeID, char** aPropertyList);
/**
 * Callback which runs when the GetAllowedValues action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetAllowedValues
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aDataTypeID
 * @param[in]  aFilter
 * @param[out] aPropertyInfo
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetAllowedValues)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo);
/**
 * Callback which runs when the GetStateUpdateID action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetStateUpdateID
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aId
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetStateUpdateID)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aId);
/**
 * Callback which runs when the BrowseRecordSchedules action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordSchedules
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
typedef int32_t (STDCALL *CallbackScheduledRecording1BrowseRecordSchedules)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the BrowseRecordTasks action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordTasks
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
typedef int32_t (STDCALL *CallbackScheduledRecording1BrowseRecordTasks)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID);
/**
 * Callback which runs when the CreateRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionCreateRecordSchedule
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
typedef int32_t (STDCALL *CallbackScheduledRecording1CreateRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the DeleteRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1DeleteRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the GetRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordSchedule
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
typedef int32_t (STDCALL *CallbackScheduledRecording1GetRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1EnableRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the DisableRecordSchedule action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordSchedule
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1DisableRecordSchedule)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID);
/**
 * Callback which runs when the DeleteRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1DeleteRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTask
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
typedef int32_t (STDCALL *CallbackScheduledRecording1GetRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID);
/**
 * Callback which runs when the EnableRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1EnableRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the DisableRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1DisableRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the ResetRecordTask action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionResetRecordTask
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1ResetRecordTask)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID);
/**
 * Callback which runs when the GetRecordScheduleConflicts action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordScheduleConflicts
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordScheduleID
 * @param[out] aRecordScheduleConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetRecordScheduleConflicts)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID);
/**
 * Callback which runs when the GetRecordTaskConflicts action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTaskConflicts
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aRecordTaskID
 * @param[out] aRecordTaskConflictIDList
 * @param[out] aUpdateID
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackScheduledRecording1GetRecordTaskConflicts)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgScheduledRecording1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1Destroy(THandle aProvider);

/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnablePropertyLastChange(THandle aProvider);

/**
 * Register a callback for the action GetSortCapabilities
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr);
/**
 * Register a callback for the action GetPropertyList
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr);
/**
 * Register a callback for the action GetAllowedValues
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr);
/**
 * Register a callback for the action GetStateUpdateID
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr);
/**
 * Register a callback for the action BrowseRecordSchedules
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr);
/**
 * Register a callback for the action BrowseRecordTasks
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr);
/**
 * Register a callback for the action CreateRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action EnableRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DisableRecordSchedule
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr);
/**
 * Register a callback for the action DeleteRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action EnableRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action DisableRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action ResetRecordTask
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordScheduleConflicts
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr);
/**
 * Register a callback for the action GetRecordTaskConflicts
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgScheduledRecording1EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgScheduledRecording1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgScheduledRecording1EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgScheduledRecording1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgScheduledRecording1GetPropertyLastChange(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGSCHEDULEDRECORDING1_C

