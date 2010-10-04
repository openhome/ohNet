#ifndef HEADER_DVLINNCOUKVOLKANO1_C
#define HEADER_DVLINNCOUKVOLKANO1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackVolkano1Reboot)(void* aPtr, uint32_t aVersion);
typedef int32_t (*CallbackVolkano1BootMode)(void* aPtr, uint32_t aVersion, char** aaMode);
typedef int32_t (*CallbackVolkano1SetBootMode)(void* aPtr, uint32_t aVersion, const char* aaMode);
typedef int32_t (*CallbackVolkano1BspType)(void* aPtr, uint32_t aVersion, char** aaBspType);
typedef int32_t (*CallbackVolkano1UglyName)(void* aPtr, uint32_t aVersion, char** aaUglyName);
typedef int32_t (*CallbackVolkano1MacAddress)(void* aPtr, uint32_t aVersion, char** aaMacAddress);
typedef int32_t (*CallbackVolkano1ProductId)(void* aPtr, uint32_t aVersion, char** aaProductNumber);
typedef int32_t (*CallbackVolkano1BoardId)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, char** aaBoardNumber);
typedef int32_t (*CallbackVolkano1BoardType)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, char** aaBoardNumber);
typedef int32_t (*CallbackVolkano1MaxBoards)(void* aPtr, uint32_t aVersion, uint32_t* aaMaxBoards);
typedef int32_t (*CallbackVolkano1SoftwareVersion)(void* aPtr, uint32_t aVersion, char** aaSoftwareVersion);

DllExport THandle DvServiceLinnCoUkVolkano1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkVolkano1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkVolkano1EnableActionReboot(THandle aService, CallbackVolkano1Reboot aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionBootMode(THandle aService, CallbackVolkano1BootMode aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionSetBootMode(THandle aService, CallbackVolkano1SetBootMode aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionBspType(THandle aService, CallbackVolkano1BspType aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionUglyName(THandle aService, CallbackVolkano1UglyName aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionMacAddress(THandle aService, CallbackVolkano1MacAddress aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionProductId(THandle aService, CallbackVolkano1ProductId aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionBoardId(THandle aService, CallbackVolkano1BoardId aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionBoardType(THandle aService, CallbackVolkano1BoardType aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionMaxBoards(THandle aService, CallbackVolkano1MaxBoards aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkVolkano1EnableActionSoftwareVersion(THandle aService, CallbackVolkano1SoftwareVersion aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKVOLKANO1_C

