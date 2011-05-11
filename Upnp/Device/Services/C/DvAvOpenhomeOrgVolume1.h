/**
 * Provider for the av.openhome.org:Volume:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGVOLUME1_C
#define HEADER_DVAVOPENHOMEORGVOLUME1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgVolume1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Characteristics action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionCharacteristics
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aVolumeMax
 * @param[out] aVolumeUnity
 * @param[out] aVolumeSteps
 * @param[out] aVolumeMilliDbPerStep
 * @param[out] aBalanceMax
 * @param[out] aFadeMax
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1Characteristics)(void* aPtr, uint32_t aVersion, uint32_t* aVolumeMax, uint32_t* aVolumeUnity, uint32_t* aVolumeSteps, uint32_t* aVolumeMilliDbPerStep, uint32_t* aBalanceMax, uint32_t* aFadeMax);
/**
 * Callback which runs when the SetVolume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionSetVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1SetVolume)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the VolumeInc action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionVolumeInc
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1VolumeInc)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the VolumeDec action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionVolumeDec
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1VolumeDec)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Volume action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionVolume
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1Volume)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the SetBalance action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionSetBalance
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1SetBalance)(void* aPtr, uint32_t aVersion, int32_t aValue);
/**
 * Callback which runs when the BalanceInc action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionBalanceInc
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1BalanceInc)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the BalanceDec action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionBalanceDec
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1BalanceDec)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Balance action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionBalance
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1Balance)(void* aPtr, uint32_t aVersion, int32_t* aValue);
/**
 * Callback which runs when the SetFade action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionSetFade
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1SetFade)(void* aPtr, uint32_t aVersion, int32_t aValue);
/**
 * Callback which runs when the FadeInc action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionFadeInc
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1FadeInc)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the FadeDec action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionFadeDec
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1FadeDec)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the Fade action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionFade
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1Fade)(void* aPtr, uint32_t aVersion, int32_t* aValue);
/**
 * Callback which runs when the SetMute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionSetMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1SetMute)(void* aPtr, uint32_t aVersion, uint32_t aValue);
/**
 * Callback which runs when the Mute action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionMute
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1Mute)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the VolumeLimit action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgVolume1EnableActionVolumeLimit
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolume1VolumeLimit)(void* aPtr, uint32_t aVersion, uint32_t* aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderAvOpenhomeOrgVolume1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 */
DllExport void DvProviderAvOpenhomeOrgVolume1Destroy(THandle aProvider);

/**
 * Register a callback for the action Characteristics
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionCharacteristics(THandle aProvider, CallbackVolume1Characteristics aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionSetVolume(THandle aProvider, CallbackVolume1SetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeInc
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionVolumeInc(THandle aProvider, CallbackVolume1VolumeInc aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeDec
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionVolumeDec(THandle aProvider, CallbackVolume1VolumeDec aCallback, void* aPtr);
/**
 * Register a callback for the action Volume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionVolume(THandle aProvider, CallbackVolume1Volume aCallback, void* aPtr);
/**
 * Register a callback for the action SetBalance
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionSetBalance(THandle aProvider, CallbackVolume1SetBalance aCallback, void* aPtr);
/**
 * Register a callback for the action BalanceInc
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionBalanceInc(THandle aProvider, CallbackVolume1BalanceInc aCallback, void* aPtr);
/**
 * Register a callback for the action BalanceDec
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionBalanceDec(THandle aProvider, CallbackVolume1BalanceDec aCallback, void* aPtr);
/**
 * Register a callback for the action Balance
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionBalance(THandle aProvider, CallbackVolume1Balance aCallback, void* aPtr);
/**
 * Register a callback for the action SetFade
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionSetFade(THandle aProvider, CallbackVolume1SetFade aCallback, void* aPtr);
/**
 * Register a callback for the action FadeInc
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionFadeInc(THandle aProvider, CallbackVolume1FadeInc aCallback, void* aPtr);
/**
 * Register a callback for the action FadeDec
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionFadeDec(THandle aProvider, CallbackVolume1FadeDec aCallback, void* aPtr);
/**
 * Register a callback for the action Fade
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionFade(THandle aProvider, CallbackVolume1Fade aCallback, void* aPtr);
/**
 * Register a callback for the action SetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionSetMute(THandle aProvider, CallbackVolume1SetMute aCallback, void* aPtr);
/**
 * Register a callback for the action Mute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionMute(THandle aProvider, CallbackVolume1Mute aCallback, void* aPtr);
/**
 * Register a callback for the action VolumeLimit
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgVolume1EnableActionVolumeLimit(THandle aProvider, CallbackVolume1VolumeLimit aCallback, void* aPtr);

/**
 * Set the value of the Volume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Volume property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolume(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Mute property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Mute property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyMute(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Balance property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Balance property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyBalance(THandle aProvider, int32_t* aValue);
/**
 * Set the value of the Fade property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyFade(THandle aProvider, int32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Fade property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyFade(THandle aProvider, int32_t* aValue);
/**
 * Set the value of the VolumeLimit property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeLimit property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VolumeMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VolumeUnity property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeUnity(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeUnity property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeUnity(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VolumeSteps property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeSteps(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeSteps property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeSteps(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the VolumeMilliDbPerStep property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeMilliDbPerStep(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the VolumeMilliDbPerStep property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeMilliDbPerStep(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BalanceMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyBalanceMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BalanceMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyBalanceMax(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the FadeMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgVolume1SetPropertyFadeMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the FadeMax property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgVolume1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgVolume1GetPropertyFadeMax(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGVOLUME1_C

