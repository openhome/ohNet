#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestWidgetController1CreateWidget)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn);
typedef int32_t (*CallbackTestWidgetController1RemoveWidget)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn);
typedef int32_t (*CallbackTestWidgetController1SetWidgetRegister)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue);

DllExport THandle DvProviderZappOrgTestWidgetController1Create(DvDeviceC aDevice);
DllExport void DvProviderZappOrgTestWidgetController1Destroy(THandle aService);

DllExport void DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(THandle aService, CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(THandle aService, CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
DllExport void DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(THandle aService, CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C

