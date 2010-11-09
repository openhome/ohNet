#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestDimmableLight1GetLevel)(void* aPtr, uint32_t aVersion, uint32_t* aLevel);
typedef int32_t (*CallbackTestDimmableLight1SetLevel)(void* aPtr, uint32_t aVersion, uint32_t aLevel);

DllExport THandle DvProviderZappOrgTestDimmableLight1Create(DvDeviceC aDevice);
DllExport void DvProviderZappOrgTestDimmableLight1Destroy(THandle aProvider);

DllExport void DvProviderZappOrgTestDimmableLight1EnableActionGetLevel(THandle aProvider, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestDimmableLight1EnableActionSetLevel(THandle aProvider, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr);

DllExport int32_t DvProviderZappOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C

