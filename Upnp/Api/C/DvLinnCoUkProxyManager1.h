#ifndef HEADER_DVLINNCOUKPROXYMANAGER1_C
#define HEADER_DVLINNCOUKPROXYMANAGER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackProxyManager1KontrolProductConnected)(void* aPtr, uint32_t aVersion, char** aaConnected);
typedef int32_t (*CallbackProxyManager1SetKontrolProductConnected)(void* aPtr, uint32_t aVersion, const char* aaConnected);
typedef int32_t (*CallbackProxyManager1KontrolProductComPort)(void* aPtr, uint32_t aVersion, uint32_t* aaPort);
typedef int32_t (*CallbackProxyManager1SetKontrolProductComPort)(void* aPtr, uint32_t aVersion, uint32_t aaConnected);
typedef int32_t (*CallbackProxyManager1DiscPlayerConnected)(void* aPtr, uint32_t aVersion, char** aaConnected);
typedef int32_t (*CallbackProxyManager1SetDiscPlayerConnected)(void* aPtr, uint32_t aVersion, const char* aaConnected);
typedef int32_t (*CallbackProxyManager1DiscPlayerComPort)(void* aPtr, uint32_t aVersion, uint32_t* aaPort);
typedef int32_t (*CallbackProxyManager1SetDiscPlayerComPort)(void* aPtr, uint32_t aVersion, uint32_t aaConnected);
typedef int32_t (*CallbackProxyManager1TestKontrolProductConnection)(void* aPtr, uint32_t aVersion, uint32_t* aaResult);
typedef int32_t (*CallbackProxyManager1TestDiscPlayerConnection)(void* aPtr, uint32_t aVersion, uint32_t* aaResult);

DllExport THandle DvServiceLinnCoUkProxyManager1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkProxyManager1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aService, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aService, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aService, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aService, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aService, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aService, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aService, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aService, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aService, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aService, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPROXYMANAGER1_C

