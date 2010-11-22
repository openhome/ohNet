#ifndef HEADER_DVZAPPORGTESTWIDGET1_C
#define HEADER_DVZAPPORGTESTWIDGET1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestWidget1SetReadWriteRegister)(void* aPtr, uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);
typedef int32_t (*CallbackTestWidget1GetWidgetClass)(void* aPtr, uint32_t aVersion, uint32_t* aWidgetClass);

DllExport THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice);
DllExport void DvProviderZappOrgTestWidget1Destroy(THandle aProvider);

DllExport void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aProvider, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestWidget1EnableActionGetWidgetClass(THandle aProvider, CallbackTestWidget1GetWidgetClass aCallback, void* aPtr);

DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGET1_C

