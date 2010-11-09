#ifndef HEADER_DVZAPPORGTESTBASIC1_C
#define HEADER_DVZAPPORGTESTBASIC1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestBasic1Increment)(void* aPtr, uint32_t aVersion, uint32_t aValue, uint32_t* aResult);
typedef int32_t (*CallbackTestBasic1Decrement)(void* aPtr, uint32_t aVersion, int32_t aValue, int32_t* aResult);
typedef int32_t (*CallbackTestBasic1Toggle)(void* aPtr, uint32_t aVersion, uint32_t aValue, uint32_t* aResult);
typedef int32_t (*CallbackTestBasic1EchoString)(void* aPtr, uint32_t aVersion, const char* aValue, char** aResult);
typedef int32_t (*CallbackTestBasic1EchoBinary)(void* aPtr, uint32_t aVersion, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen);
typedef int32_t (*CallbackTestBasic1SetUint)(void* aPtr, uint32_t aVersion, uint32_t aValueUint);
typedef int32_t (*CallbackTestBasic1GetUint)(void* aPtr, uint32_t aVersion, uint32_t* aValueUint);
typedef int32_t (*CallbackTestBasic1SetInt)(void* aPtr, uint32_t aVersion, int32_t aValueInt);
typedef int32_t (*CallbackTestBasic1GetInt)(void* aPtr, uint32_t aVersion, int32_t* aValueInt);
typedef int32_t (*CallbackTestBasic1SetBool)(void* aPtr, uint32_t aVersion, uint32_t aValueBool);
typedef int32_t (*CallbackTestBasic1GetBool)(void* aPtr, uint32_t aVersion, uint32_t* aValueBool);
typedef int32_t (*CallbackTestBasic1SetMultiple)(void* aPtr, uint32_t aVersion, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool);
typedef int32_t (*CallbackTestBasic1SetString)(void* aPtr, uint32_t aVersion, const char* aValueStr);
typedef int32_t (*CallbackTestBasic1GetString)(void* aPtr, uint32_t aVersion, char** aValueStr);
typedef int32_t (*CallbackTestBasic1SetBinary)(void* aPtr, uint32_t aVersion, const char* aValueBin, uint32_t aValueBinLen);
typedef int32_t (*CallbackTestBasic1GetBinary)(void* aPtr, uint32_t aVersion, char** aValueBin, uint32_t* aValueBinLen);
typedef int32_t (*CallbackTestBasic1ToggleBool)(void* aPtr, uint32_t aVersion);

DllExport THandle DvProviderZappOrgTestBasic1Create(DvDeviceC aDevice);
DllExport void DvProviderZappOrgTestBasic1Destroy(THandle aProvider);

DllExport void DvProviderZappOrgTestBasic1EnableActionIncrement(THandle aProvider, CallbackTestBasic1Increment aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionDecrement(THandle aProvider, CallbackTestBasic1Decrement aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionToggle(THandle aProvider, CallbackTestBasic1Toggle aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionEchoString(THandle aProvider, CallbackTestBasic1EchoString aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionEchoBinary(THandle aProvider, CallbackTestBasic1EchoBinary aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetUint(THandle aProvider, CallbackTestBasic1SetUint aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionGetUint(THandle aProvider, CallbackTestBasic1GetUint aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetInt(THandle aProvider, CallbackTestBasic1SetInt aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionGetInt(THandle aProvider, CallbackTestBasic1GetInt aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetBool(THandle aProvider, CallbackTestBasic1SetBool aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionGetBool(THandle aProvider, CallbackTestBasic1GetBool aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetMultiple(THandle aProvider, CallbackTestBasic1SetMultiple aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetString(THandle aProvider, CallbackTestBasic1SetString aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionGetString(THandle aProvider, CallbackTestBasic1GetString aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionSetBinary(THandle aProvider, CallbackTestBasic1SetBinary aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionGetBinary(THandle aProvider, CallbackTestBasic1GetBinary aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestBasic1EnableActionToggleBool(THandle aProvider, CallbackTestBasic1ToggleBool aCallback, void* aPtr);

DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarUint(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarUint(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarInt(THandle aProvider, int32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarInt(THandle aProvider, int32_t* aValue);
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarBool(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarBool(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarStr(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarStr(THandle aProvider, char** aValue);
DllExport int32_t DvProviderZappOrgTestBasic1SetPropertyVarBin(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestBasic1GetPropertyVarBin(THandle aProvider, char** aValue, uint32_t* aValueLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTBASIC1_C

