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

DllExport THandle DvServiceZappOrgTestBasic1Create(DvDeviceC aDevice);
DllExport void DvServiceZappOrgTestBasic1Destroy(THandle aService);

DllExport void DvServiceZappOrgTestBasic1EnableActionIncrement(THandle aService, CallbackTestBasic1Increment aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionDecrement(THandle aService, CallbackTestBasic1Decrement aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionToggle(THandle aService, CallbackTestBasic1Toggle aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionEchoString(THandle aService, CallbackTestBasic1EchoString aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionEchoBinary(THandle aService, CallbackTestBasic1EchoBinary aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetUint(THandle aService, CallbackTestBasic1SetUint aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionGetUint(THandle aService, CallbackTestBasic1GetUint aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetInt(THandle aService, CallbackTestBasic1SetInt aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionGetInt(THandle aService, CallbackTestBasic1GetInt aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetBool(THandle aService, CallbackTestBasic1SetBool aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionGetBool(THandle aService, CallbackTestBasic1GetBool aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetMultiple(THandle aService, CallbackTestBasic1SetMultiple aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetString(THandle aService, CallbackTestBasic1SetString aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionGetString(THandle aService, CallbackTestBasic1GetString aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionSetBinary(THandle aService, CallbackTestBasic1SetBinary aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestBasic1EnableActionGetBinary(THandle aService, CallbackTestBasic1GetBinary aCallback, void* aPtr);

DllExport int32_t DvServiceZappOrgTestBasic1SetPropertyVarUint(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestBasic1GetPropertyVarUint(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestBasic1SetPropertyVarInt(THandle aService, int32_t aValue);
DllExport void DvServiceZappOrgTestBasic1GetPropertyVarInt(THandle aService, int32_t* aValue);
DllExport int32_t DvServiceZappOrgTestBasic1SetPropertyVarBool(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestBasic1GetPropertyVarBool(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestBasic1SetPropertyVarStr(THandle aService, const char* aValue);
DllExport void DvServiceZappOrgTestBasic1GetPropertyVarStr(THandle aService, char** aValue);
DllExport int32_t DvServiceZappOrgTestBasic1SetPropertyVarBin(THandle aService, const char* aValue, uint32_t aValueLen);
DllExport void DvServiceZappOrgTestBasic1GetPropertyVarBin(THandle aService, char** aValue, uint32_t* aValueLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTBASIC1_C

