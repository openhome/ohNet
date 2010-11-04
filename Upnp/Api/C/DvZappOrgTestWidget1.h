#ifndef HEADER_DVZAPPORGTESTWIDGET1_C
#define HEADER_DVZAPPORGTESTWIDGET1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestWidget1SetReadWriteRegister)(void* aPtr, uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);

DllExport THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice);
DllExport void DvProviderZappOrgTestWidget1Destroy(THandle aService);

DllExport void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aService, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);

DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aService, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aService, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGET1_C

