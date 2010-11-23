/**
 * Provider for the linn.co.uk:Component:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKCOMPONENT1_C
#define HEADER_DVLINNCOUKCOMPONENT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the AmplifierEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1AmplifierEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
/**
 * Callback which runs when the SetAmplifierEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1SetAmplifierEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
/**
 * Callback which runs when the AmplifierAttenuation action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaAttenuation
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1AmplifierAttenuation)(void* aPtr, uint32_t aVersion, char** aaAttenuation);
/**
 * Callback which runs when the SetAmplifierAttenuation action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaAttenuation
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1SetAmplifierAttenuation)(void* aPtr, uint32_t aVersion, const char* aaAttenuation);
/**
 * Callback which runs when the SetVolumeControlEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1SetVolumeControlEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaEnabled);
/**
 * Callback which runs when the VolumeControlEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1VolumeControlEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaEnabled);
/**
 * Callback which runs when the SetDigitalAudioOutputRaw action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaRaw
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1SetDigitalAudioOutputRaw)(void* aPtr, uint32_t aVersion, uint32_t aaRaw);
/**
 * Callback which runs when the DigitalAudioOutputRaw action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaRaw
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1DigitalAudioOutputRaw)(void* aPtr, uint32_t aVersion, uint32_t* aaRaw);
/**
 * Callback which runs when the AmplifierOverTemperature action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaOverTemperature
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1AmplifierOverTemperature)(void* aPtr, uint32_t aVersion, uint32_t* aaOverTemperature);
/**
 * Callback which runs when the EthernetLinkConnected action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaLinkConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1EthernetLinkConnected)(void* aPtr, uint32_t aVersion, uint32_t* aaLinkConnected);
/**
 * Callback which runs when the Locate action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkComponent1EnableActionLocate
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackComponent1Locate)(void* aPtr, uint32_t aVersion);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkComponent1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 */
DllExport void DvProviderLinnCoUkComponent1Destroy(THandle aProvider);

/**
 * Register a callback for the action AmplifierEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aProvider, CallbackComponent1AmplifierEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action SetAmplifierEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aProvider, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action AmplifierAttenuation
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aProvider, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr);
/**
 * Register a callback for the action SetAmplifierAttenuation
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aProvider, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolumeControlEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aProvider, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeControlEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aProvider, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action SetDigitalAudioOutputRaw
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr);
/**
 * Register a callback for the action DigitalAudioOutputRaw
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr);
/**
 * Register a callback for the action AmplifierOverTemperature
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aProvider, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr);
/**
 * Register a callback for the action EthernetLinkConnected
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aProvider, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr);
/**
 * Register a callback for the action Locate
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkComponent1EnableActionLocate(THandle aProvider, CallbackComponent1Locate aCallback, void* aPtr);

/**
 * Set the value of the AmplifierEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the AmplifierEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the AmplifierAttenuation property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the AmplifierAttenuation property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aProvider, char** aValue);
/**
 * Set the value of the VolumeControlEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeControlEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DigitalAudioOutputRaw property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DigitalAudioOutputRaw property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkComponent1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKCOMPONENT1_C

