#ifndef HEADER_DVLINNCOUKCOMPONENT1_C
#define HEADER_DVLINNCOUKCOMPONENT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*CallbackComponent1AmplifierEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
typedef int32_t (*CallbackComponent1SetAmplifierEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
typedef int32_t (*CallbackComponent1AmplifierAttenuation)(void* aPtr, uint32_t aVersion, char** aaAttenuation);
typedef int32_t (*CallbackComponent1SetAmplifierAttenuation)(void* aPtr, uint32_t aVersion, const char* aaAttenuation);
typedef int32_t (*CallbackComponent1SetVolumeControlEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
typedef int32_t (*CallbackComponent1VolumeControlEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
typedef int32_t (*CallbackComponent1SetDigitalAudioOutputRaw)(void* aPtr, uint32_t aVersion, uint32_t aaRaw);
typedef int32_t (*CallbackComponent1DigitalAudioOutputRaw)(void* aPtr, uint32_t aVersion, uint32_t* aaRaw);
typedef int32_t (*CallbackComponent1AmplifierOverTemperature)(void* aPtr, uint32_t aVersion, uint32_t* aaOverTemperature);
typedef int32_t (*CallbackComponent1EthernetLinkConnected)(void* aPtr, uint32_t aVersion, uint32_t* aaLinkConnected);
typedef int32_t (*CallbackComponent1Locate)(void* aPtr, uint32_t aVersion);

DllExport THandle DvServiceLinnCoUkComponent1Create(DvDeviceC aDevice);
DllExport void DvServiceLinnCoUkComponent1Destroy(THandle aService);

DllExport void DvServiceLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aService, CallbackComponent1AmplifierEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aService, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aService, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aService, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aService, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aService, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aService, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aService, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aService, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aService, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr);
DllExport void DvServiceLinnCoUkComponent1EnableActionLocate(THandle aService, CallbackComponent1Locate aCallback, void* aPtr);

DllExport int32_t DvServiceLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aService, const char* aValue);
DllExport void DvServiceLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aService, char** aValue);
DllExport int32_t DvServiceLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aService, uint32_t* aValue);
DllExport int32_t DvServiceLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aService, uint32_t aValue);
DllExport void DvServiceLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aService, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKCOMPONENT1_C

