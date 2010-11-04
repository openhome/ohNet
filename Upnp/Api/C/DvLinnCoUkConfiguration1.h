#ifndef HEADER_DVLINNCOUKCONFIGURATION1_C
#define HEADER_DVLINNCOUKCONFIGURATION1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackConfiguration1ConfigurationXml)(void* aPtr, uint32_t aVersion, char** aaConfigurationXml);
typedef int32_t (*CallbackConfiguration1ParameterXml)(void* aPtr, uint32_t aVersion, char** aaParameterXml);
typedef int32_t (*CallbackConfiguration1SetParameter)(void* aPtr, uint32_t aVersion, const char* aaTarget, const char* aaName, const char* aaValue);

DllExport THandle DvProviderLinnCoUkConfiguration1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkConfiguration1Destroy(THandle aService);

DllExport void DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(THandle aService, CallbackConfiguration1ConfigurationXml aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkConfiguration1EnableActionParameterXml(THandle aService, CallbackConfiguration1ParameterXml aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkConfiguration1EnableActionSetParameter(THandle aService, CallbackConfiguration1SetParameter aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(THandle aService, char** aValue);
DllExport int32_t DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(THandle aService, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKCONFIGURATION1_C

