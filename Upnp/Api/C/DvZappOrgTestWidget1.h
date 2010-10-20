#ifndef HEADER_DVZAPPORGTESTWIDGET1_C
#define HEADER_DVZAPPORGTESTWIDGET1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestWidget1SetReadWriteRegister)(void* aPtr, uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);

DllExport THandle DvServiceZappOrgTestWidget1Create(DvDeviceC aDevice);
DllExport void DvServiceZappOrgTestWidget1Destroy(THandle aService);

DllExport void DvServiceZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aService, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);

DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aService, uint32_t aValue);
DllExport void DvServiceZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGET1_C

