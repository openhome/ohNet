/**
 * Provider for the zapp.org:TestBasic:1 UPnP service
 */
#ifndef HEADER_DVZAPPORGTESTBASIC1_C
#define HEADER_DVZAPPORGTESTBASIC1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderZappOrgTestBasic1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Increment action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionIncrement
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1Increment)(void* aPtr, uint32_t aVersion, uint32_t aValue, uint32_t* aResult);
/**
 * Callback which runs when the Decrement action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionDecrement
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1Decrement)(void* aPtr, uint32_t aVersion, int32_t aValue, int32_t* aResult);
/**
 * Callback which runs when the Toggle action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionToggle
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1Toggle)(void* aPtr, uint32_t aVersion, uint32_t aValue, uint32_t* aResult);
/**
 * Callback which runs when the EchoString action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionEchoString
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 * @param[out] aResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1EchoString)(void* aPtr, uint32_t aVersion, const char* aValue, char** aResult);
/**
 * Callback which runs when the EchoBinary action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionEchoBinary
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 * @param[in]  aValueLen
 * @param[out] aResult
 * @param[out] aResultLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1EchoBinary)(void* aPtr, uint32_t aVersion, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen);
/**
 * Callback which runs when the SetUint action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetUint
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueUint
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetUint)(void* aPtr, uint32_t aVersion, uint32_t aValueUint);
/**
 * Callback which runs when the GetUint action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionGetUint
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValueUint
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1GetUint)(void* aPtr, uint32_t aVersion, uint32_t* aValueUint);
/**
 * Callback which runs when the SetInt action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetInt
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueInt
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetInt)(void* aPtr, uint32_t aVersion, int32_t aValueInt);
/**
 * Callback which runs when the GetInt action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionGetInt
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValueInt
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1GetInt)(void* aPtr, uint32_t aVersion, int32_t* aValueInt);
/**
 * Callback which runs when the SetBool action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetBool
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetBool)(void* aPtr, uint32_t aVersion, uint32_t aValueBool);
/**
 * Callback which runs when the GetBool action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionGetBool
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1GetBool)(void* aPtr, uint32_t aVersion, uint32_t* aValueBool);
/**
 * Callback which runs when the SetMultiple action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetMultiple
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueUint
 * @param[in]  aValueInt
 * @param[in]  aValueBool
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetMultiple)(void* aPtr, uint32_t aVersion, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool);
/**
 * Callback which runs when the SetString action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetString
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueStr
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetString)(void* aPtr, uint32_t aVersion, const char* aValueStr);
/**
 * Callback which runs when the GetString action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionGetString
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValueStr
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1GetString)(void* aPtr, uint32_t aVersion, char** aValueStr);
/**
 * Callback which runs when the SetBinary action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionSetBinary
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValueBin
 * @param[in]  aValueBinLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1SetBinary)(void* aPtr, uint32_t aVersion, const char* aValueBin, uint32_t aValueBinLen);
/**
 * Callback which runs when the GetBinary action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionGetBinary
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValueBin
 * @param[out] aValueBinLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1GetBinary)(void* aPtr, uint32_t aVersion, char** aValueBin, uint32_t* aValueBinLen);
/**
 * Callback which runs when the ToggleBool action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionToggleBool
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1ToggleBool)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the WriteFile action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionWriteFile
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aData
 * @param[in]  aFileFullName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1WriteFile)(void* aPtr, uint32_t aVersion, const char* aData, const char* aFileFullName);
/**
 * Callback which runs when the Shutdown action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestBasic1EnableActionShutdown
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestBasic1Shutdown)(void* aPtr, uint32_t aVersion);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderZappOrgTestBasic1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 */
DllExport void DvProviderZappOrgTestBasic1Destroy(THandle aProvider);

/**
 * Register a callback for the action Increment
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionIncrement(THandle aProvider, CallbackTestBasic1Increment aCallback, void* aPtr);
/**
 * Register a callback for the action Decrement
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionDecrement(THandle aProvider, CallbackTestBasic1Decrement aCallback, void* aPtr);
/**
 * Register a callback for the action Toggle
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionToggle(THandle aProvider, CallbackTestBasic1Toggle aCallback, void* aPtr);
/**
 * Register a callback for the action EchoString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionEchoString(THandle aProvider, CallbackTestBasic1EchoString aCallback, void* aPtr);
/**
 * Register a callback for the action EchoBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionEchoBinary(THandle aProvider, CallbackTestBasic1EchoBinary aCallback, void* aPtr);
/**
 * Register a callback for the action SetUint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetUint(THandle aProvider, CallbackTestBasic1SetUint aCallback, void* aPtr);
/**
 * Register a callback for the action GetUint
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionGetUint(THandle aProvider, CallbackTestBasic1GetUint aCallback, void* aPtr);
/**
 * Register a callback for the action SetInt
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetInt(THandle aProvider, CallbackTestBasic1SetInt aCallback, void* aPtr);
/**
 * Register a callback for the action GetInt
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionGetInt(THandle aProvider, CallbackTestBasic1GetInt aCallback, void* aPtr);
/**
 * Register a callback for the action SetBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetBool(THandle aProvider, CallbackTestBasic1SetBool aCallback, void* aPtr);
/**
 * Register a callback for the action GetBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionGetBool(THandle aProvider, CallbackTestBasic1GetBool aCallback, void* aPtr);
/**
 * Register a callback for the action SetMultiple
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetMultiple(THandle aProvider, CallbackTestBasic1SetMultiple aCallback, void* aPtr);
/**
 * Register a callback for the action SetString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetString(THandle aProvider, CallbackTestBasic1SetString aCallback, void* aPtr);
/**
 * Register a callback for the action GetString
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionGetString(THandle aProvider, CallbackTestBasic1GetString aCallback, void* aPtr);
/**
 * Register a callback for the action SetBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionSetBinary(THandle aProvider, CallbackTestBasic1SetBinary aCallback, void* aPtr);
/**
 * Register a callback for the action GetBinary
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionGetBinary(THandle aProvider, CallbackTestBasic1GetBinary aCallback, void* aPtr);
/**
 * Register a callback for the action ToggleBool
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionToggleBool(THandle aProvider, CallbackTestBasic1ToggleBool aCallback, void* aPtr);
/**
 * Register a callback for the action WriteFile
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionWriteFile(THandle aProvider, CallbackTestBasic1WriteFile aCallback, void* aPtr);
/**
 * Register a callback for the action Shutdown
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestBasic1EnableActionShutdown(THandle aProvider, CallbackTestBasic1Shutdown aCallback, void* aPtr);

/**
 * Set the value of the VarUint property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarUint(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarUint property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarUint(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VarInt property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarInt(THandle aProvider, int32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarInt property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarInt(THandle aProvider, int32_t* aValue);
/**
 * Set the value of the VarBool property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarBool(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarBool property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarBool(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VarStr property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarStr(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarStr property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarStr(THandle aProvider, char** aValue);
/**
 * Set the value of the VarBin property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[in]  aValueLen  Size in bytes pointed to by aValue
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarBin(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
/**
 * Get a copy of the value of the VarBin property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestBasic1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 * @param[out] aValueLen  Size in bytes pointed to by aValue
 */
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarBin(THandle aProvider, char** aValue, uint32_t* aValueLen);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTBASIC1_C

