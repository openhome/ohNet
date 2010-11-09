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

DllExport THandle DvProviderLinnCoUkComponent1Create(DvDeviceC aDevice);
DllExport void DvProviderLinnCoUkComponent1Destroy(THandle aProvider);

DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aProvider, CallbackComponent1AmplifierEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aProvider, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aProvider, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aProvider, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aProvider, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aProvider, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aProvider, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aProvider, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr);
DllExport void DvProviderLinnCoUkComponent1EnableActionLocate(THandle aProvider, CallbackComponent1Locate aCallback, void* aPtr);

DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aProvider, const char* aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aProvider, char** aValue);
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aProvider, uint32_t* aValue);
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
DllExport void DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKCOMPONENT1_C

