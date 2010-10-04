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

DllExport THandle DvServiceLinnCoUkConfiguration1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkConfiguration1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkConfiguration1EnableActionConfigurationXml(THandle aService, CallbackConfiguration1ConfigurationXml aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkConfiguration1EnableActionParameterXml(THandle aService, CallbackConfiguration1ParameterXml aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkConfiguration1EnableActionSetParameter(THandle aService, CallbackConfiguration1SetParameter aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkConfiguration1SetPropertyConfigurationXml(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkConfiguration1GetPropertyConfigurationXml(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkConfiguration1SetPropertyParameterXml(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkConfiguration1GetPropertyParameterXml(THandle aService, char** aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKCONFIGURATION1_C

