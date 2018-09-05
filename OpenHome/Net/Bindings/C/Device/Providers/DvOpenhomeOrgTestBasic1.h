/**
 * Provider for the openhome.org:TestBasic:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGTESTBASIC1_C
#define HEADER_DVOPENHOMEORGTESTBASIC1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgTestBasic1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Increment action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionIncrement
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1Increment)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue, uint32_t* aResult);
/**
 * Callback which runs when the EchoAllowedRangeUint action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedRangeUint
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1EchoAllowedRangeUint)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue, uint32_t* aResult);
/**
 * Callback which runs when the Decrement action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionDecrement
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1Decrement)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aValue, int32_t* aResult);
/**
 * Callback which runs when the Toggle action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionToggle
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1Toggle)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue, uint32_t* aResult);
/**
 * Callback which runs when the EchoString action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionEchoString
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1EchoString)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValue, char** aResult);
/**
 * Callback which runs when the EchoAllowedValueString action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedValueString
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1EchoAllowedValueString)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValue, char** aResult);
/**
 * Callback which runs when the EchoBinary action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionEchoBinary
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[out] aResult
 * @param[out] aResultLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1EchoBinary)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen);
/**
 * Callback which runs when the SetUint action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetUint
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueUint
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetUint)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValueUint);
/**
 * Callback which runs when the GetUint action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetUint
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueUint
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetUint)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValueUint);
/**
 * Callback which runs when the SetInt action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetInt
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueInt
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetInt)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t aValueInt);
/**
 * Callback which runs when the GetInt action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetInt
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueInt
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetInt)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, int32_t* aValueInt);
/**
 * Callback which runs when the SetBool action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetBool
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetBool)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValueBool);
/**
 * Callback which runs when the GetBool action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetBool
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetBool)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValueBool);
/**
 * Callback which runs when the SetMultiple action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetMultiple
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetMultiple)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool);
/**
 * Callback which runs when the GetMultiple action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetMultiple
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueUint
 * @param[out] aValueInt
 * @param[out] aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetMultiple)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValueUint, int32_t* aValueInt, uint32_t* aValueBool);
/**
 * Callback which runs when the SetString action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetString
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueStr
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetString)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValueStr);
/**
 * Callback which runs when the GetString action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetString
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueStr
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetString)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValueStr);
/**
 * Callback which runs when the SetBinary action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionSetBinary
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1SetBinary)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValueBin, uint32_t aValueBinLen);
/**
 * Callback which runs when the GetBinary action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionGetBinary
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValueBin
 * @param[out] aValueBinLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1GetBinary)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValueBin, uint32_t* aValueBinLen);
/**
 * Callback which runs when the ToggleBool action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionToggleBool
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1ToggleBool)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the ReportError action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionReportError
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1ReportError)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);
/**
 * Callback which runs when the WriteFile action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionWriteFile
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aData
 * @param[in]  aFileFullName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1WriteFile)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aData, const char* aFileFullName);
/**
 * Callback which runs when the Shutdown action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderOpenhomeOrgTestBasic1EnableActionShutdown
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackTestBasic1Shutdown)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderOpenhomeOrgTestBasic1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1Destroy(THandle aProvider);

/**
 * Enable the VarUint property.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarUint(THandle aProvider);
/**
 * Enable the VarInt property.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarInt(THandle aProvider);
/**
 * Enable the VarBool property.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBool(THandle aProvider);
/**
 * Enable the VarStr property.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarStr(THandle aProvider);
/**
 * Enable the VarBin property.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBin(THandle aProvider);

/**
 * Register a callback for the action Increment
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionIncrement(THandle aProvider, CallbackTestBasic1Increment aCallback, void* aPtr);
/**
 * Register a callback for the action EchoAllowedRangeUint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedRangeUint(THandle aProvider, CallbackTestBasic1EchoAllowedRangeUint aCallback, void* aPtr);
/**
 * Register a callback for the action Decrement
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionDecrement(THandle aProvider, CallbackTestBasic1Decrement aCallback, void* aPtr);
/**
 * Register a callback for the action Toggle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionToggle(THandle aProvider, CallbackTestBasic1Toggle aCallback, void* aPtr);
/**
 * Register a callback for the action EchoString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoString(THandle aProvider, CallbackTestBasic1EchoString aCallback, void* aPtr);
/**
 * Register a callback for the action EchoAllowedValueString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoAllowedValueString(THandle aProvider, CallbackTestBasic1EchoAllowedValueString aCallback, void* aPtr);
/**
 * Register a callback for the action EchoBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionEchoBinary(THandle aProvider, CallbackTestBasic1EchoBinary aCallback, void* aPtr);
/**
 * Register a callback for the action SetUint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetUint(THandle aProvider, CallbackTestBasic1SetUint aCallback, void* aPtr);
/**
 * Register a callback for the action GetUint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetUint(THandle aProvider, CallbackTestBasic1GetUint aCallback, void* aPtr);
/**
 * Register a callback for the action SetInt
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetInt(THandle aProvider, CallbackTestBasic1SetInt aCallback, void* aPtr);
/**
 * Register a callback for the action GetInt
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetInt(THandle aProvider, CallbackTestBasic1GetInt aCallback, void* aPtr);
/**
 * Register a callback for the action SetBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetBool(THandle aProvider, CallbackTestBasic1SetBool aCallback, void* aPtr);
/**
 * Register a callback for the action GetBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetBool(THandle aProvider, CallbackTestBasic1GetBool aCallback, void* aPtr);
/**
 * Register a callback for the action SetMultiple
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetMultiple(THandle aProvider, CallbackTestBasic1SetMultiple aCallback, void* aPtr);
/**
 * Register a callback for the action GetMultiple
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetMultiple(THandle aProvider, CallbackTestBasic1GetMultiple aCallback, void* aPtr);
/**
 * Register a callback for the action SetString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetString(THandle aProvider, CallbackTestBasic1SetString aCallback, void* aPtr);
/**
 * Register a callback for the action GetString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetString(THandle aProvider, CallbackTestBasic1GetString aCallback, void* aPtr);
/**
 * Register a callback for the action SetBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionSetBinary(THandle aProvider, CallbackTestBasic1SetBinary aCallback, void* aPtr);
/**
 * Register a callback for the action GetBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionGetBinary(THandle aProvider, CallbackTestBasic1GetBinary aCallback, void* aPtr);
/**
 * Register a callback for the action ToggleBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionToggleBool(THandle aProvider, CallbackTestBasic1ToggleBool aCallback, void* aPtr);
/**
 * Register a callback for the action ReportError
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionReportError(THandle aProvider, CallbackTestBasic1ReportError aCallback, void* aPtr);
/**
 * Register a callback for the action WriteFile
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionWriteFile(THandle aProvider, CallbackTestBasic1WriteFile aCallback, void* aPtr);
/**
 * Register a callback for the action Shutdown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1EnableActionShutdown(THandle aProvider, CallbackTestBasic1Shutdown aCallback, void* aPtr);

/**
 * Set the value of the VarUint property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarUint has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarUint(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarUint property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarUint has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarUint(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VarInt property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarInt has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarInt(THandle aProvider, int32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarInt property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarInt has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarInt(THandle aProvider, int32_t* aValue);
/**
 * Set the value of the VarBool property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBool has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarBool(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarBool property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBool has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarBool(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VarStr property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarStr has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarStr(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarStr property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarStr has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarStr(THandle aProvider, char** aValue);
/**
 * Set the value of the VarBin property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBin has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderOpenhomeOrgTestBasic1SetPropertyVarBin(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarBin property
 *
 * Can only be called if DvProviderOpenhomeOrgTestBasic1EnablePropertyVarBin has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestBasic1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void STDCALL DvProviderOpenhomeOrgTestBasic1GetPropertyVarBin(THandle aProvider, char** aValue, uint32_t* aValueLen);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGTESTBASIC1_C

