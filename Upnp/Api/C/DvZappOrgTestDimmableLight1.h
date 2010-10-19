#ifndef HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C
#define HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestDimmableLight1GetLevel)(void* aPtr, uint32_t aVersion, uint32_t* aLevel);
typedef int32_t (*CallbackTestDimmableLight1SetLevel)(void* aPtr, uint32_t aVersion, uint32_t aLevel);

DllExport THandle DvServiceZappOrgTestDimmableLight1Create(DvDeviceC aDevice);
DllExport void DvServiceZappOrgTestDimmableLight1Destroy(THandle aService);

DllExport void DvServiceZappOrgTestDimmableLight1EnableActionGetLevel(THandle aService, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestDimmableLight1EnableActionSetLevel(THandle aService, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr);

DllExport int32_t DvServiceZappOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTDIMMABLELIGHT1_C

