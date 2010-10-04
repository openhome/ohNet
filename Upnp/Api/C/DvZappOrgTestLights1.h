#ifndef HEADER_DVZAPPORGTESTLIGHTS1_C
#define HEADER_DVZAPPORGTESTLIGHTS1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackTestLights1GetCount)(void* aPtr, uint32_t aVersion, uint32_t* aCount);
typedef int32_t (*CallbackTestLights1GetRoom)(void* aPtr, uint32_t aVersion, uint32_t aIndex, char** aRoomName);
typedef int32_t (*CallbackTestLights1GetName)(void* aPtr, uint32_t aVersion, uint32_t aIndex, char** aFriendlyName);
typedef int32_t (*CallbackTestLights1GetPosition)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ);
typedef int32_t (*CallbackTestLights1SetColor)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t aColor);
typedef int32_t (*CallbackTestLights1GetColor)(void* aPtr, uint32_t aVersion, uint32_t aIndex, uint32_t* aColor);
typedef int32_t (*CallbackTestLights1GetColorComponents)(void* aPtr, uint32_t aVersion, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue);

DllExport THandle DvServiceZappOrgTestLights1Create(DvDeviceC aDevice);
DllExport void DvServiceZappOrgTestLights1Destroy(THandle aService);

DllExport void DvServiceZappOrgTestLights1EnableActionGetCount(THandle aService, CallbackTestLights1GetCount aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionGetRoom(THandle aService, CallbackTestLights1GetRoom aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionGetName(THandle aService, CallbackTestLights1GetName aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionGetPosition(THandle aService, CallbackTestLights1GetPosition aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionSetColor(THandle aService, CallbackTestLights1SetColor aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionGetColor(THandle aService, CallbackTestLights1GetColor aCallback, void* aPtr);
DllExport void DvServiceZappOrgTestLights1EnableActionGetColorComponents(THandle aService, CallbackTestLights1GetColorComponents aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTLIGHTS1_C

