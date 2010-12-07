/**
 * Provider for the linn.co.uk:Diagnostics:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKDIAGNOSTICS1_C
#define HEADER_DVLINNCOUKDIAGNOSTICS1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkDiagnostics1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Echo action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionEcho
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIn
 * @param[out] aaOut
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1Echo)(void* aPtr, uint32_t aVersion, const char* aaIn, char** aaOut);
/**
 * Callback which runs when the ElfFile action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionElfFile
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaElfFile
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1ElfFile)(void* aPtr, uint32_t aVersion, char** aaElfFile);
/**
 * Callback which runs when the ElfFingerprint action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaElfFileFingerprint
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1ElfFingerprint)(void* aPtr, uint32_t aVersion, char** aaElfFileFingerprint);
/**
 * Callback which runs when the CrashDataStatus action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaCrashDataStatus
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1CrashDataStatus)(void* aPtr, uint32_t aVersion, char** aaCrashDataStatus);
/**
 * Callback which runs when the CrashDataFetch action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaCrashData
 * @param[out] aaCrashDataLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1CrashDataFetch)(void* aPtr, uint32_t aVersion, char** aaCrashData, uint32_t* aaCrashDataLen);
/**
 * Callback which runs when the CrashDataClear action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1CrashDataClear)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the SysLog action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionSysLog
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSysLog
 * @param[out] aaSysLogLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1SysLog)(void* aPtr, uint32_t aVersion, char** aaSysLog, uint32_t* aaSysLogLen);
/**
 * Callback which runs when the Diagnostic action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaDiagnosticType
 * @param[out] aaDiagnosticInfo
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1Diagnostic)(void* aPtr, uint32_t aVersion, const char* aaDiagnosticType, char** aaDiagnosticInfo);
/**
 * Callback which runs when the StateVariable action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionStateVariable
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStateVariable
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1StateVariable)(void* aPtr, uint32_t aVersion, uint32_t* aaStateVariable);
/**
 * Callback which runs when the SetStateVariable action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStateVariable
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1SetStateVariable)(void* aPtr, uint32_t aVersion, uint32_t aaStateVariable);
/**
 * Callback which runs when the StateVariablePeriod action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaPeriod
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1StateVariablePeriod)(void* aPtr, uint32_t aVersion, uint32_t* aaPeriod);
/**
 * Callback which runs when the SetStateVariablePeriod action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaPeriod
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1SetStateVariablePeriod)(void* aPtr, uint32_t aVersion, uint32_t aaPeriod);
/**
 * Callback which runs when the Reboot action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDiagnostics1EnableActionReboot
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaDelay
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDiagnostics1Reboot)(void* aPtr, uint32_t aVersion, uint32_t aaDelay);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkDiagnostics1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 */
DllExport void DvProviderLinnCoUkDiagnostics1Destroy(THandle aProvider);

/**
 * Register a callback for the action Echo
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionEcho(THandle aProvider, CallbackDiagnostics1Echo aCallback, void* aPtr);
/**
 * Register a callback for the action ElfFile
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionElfFile(THandle aProvider, CallbackDiagnostics1ElfFile aCallback, void* aPtr);
/**
 * Register a callback for the action ElfFingerprint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint(THandle aProvider, CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr);
/**
 * Register a callback for the action CrashDataStatus
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus(THandle aProvider, CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr);
/**
 * Register a callback for the action CrashDataFetch
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch(THandle aProvider, CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr);
/**
 * Register a callback for the action CrashDataClear
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear(THandle aProvider, CallbackDiagnostics1CrashDataClear aCallback, void* aPtr);
/**
 * Register a callback for the action SysLog
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionSysLog(THandle aProvider, CallbackDiagnostics1SysLog aCallback, void* aPtr);
/**
 * Register a callback for the action Diagnostic
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic(THandle aProvider, CallbackDiagnostics1Diagnostic aCallback, void* aPtr);
/**
 * Register a callback for the action StateVariable
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionStateVariable(THandle aProvider, CallbackDiagnostics1StateVariable aCallback, void* aPtr);
/**
 * Register a callback for the action SetStateVariable
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable(THandle aProvider, CallbackDiagnostics1SetStateVariable aCallback, void* aPtr);
/**
 * Register a callback for the action StateVariablePeriod
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod(THandle aProvider, CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr);
/**
 * Register a callback for the action SetStateVariablePeriod
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(THandle aProvider, CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr);
/**
 * Register a callback for the action Reboot
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDiagnostics1EnableActionReboot(THandle aProvider, CallbackDiagnostics1Reboot aCallback, void* aPtr);

/**
 * Set the value of the aStateVariable property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkDiagnostics1SetPropertyaStateVariable(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the aStateVariable property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkDiagnostics1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkDiagnostics1GetPropertyaStateVariable(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDIAGNOSTICS1_C

