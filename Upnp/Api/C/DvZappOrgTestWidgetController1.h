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

DllExport THandle DvServiceZappOrgTestWidgetController1Create(DvDeviceC aDevice);
DllExport void DvServiceZappOrgTestWidgetController1Destroy(THandle aService);

DllExport void DvServiceZappOrgTestWidgetController1EnableActionCreateWidget(THandle aService, CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestWidgetController1EnableActionRemoveWidget(THandle aService, CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestWidgetController1EnableActionSetWidgetRegister(THandle aService, CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C

