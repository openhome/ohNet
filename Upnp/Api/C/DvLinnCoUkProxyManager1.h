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

DllExport THandle DvProviderLinnCoUkProxyManager1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkProxyManager1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aProvider, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aProvider, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aProvider, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aProvider, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aProvider, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aProvider, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aProvider, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aProvider, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aProvider, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aProvider, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPROXYMANAGER1_C

