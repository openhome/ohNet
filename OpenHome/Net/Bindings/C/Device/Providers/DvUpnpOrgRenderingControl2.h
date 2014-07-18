/**
 * Provider for the upnp.org:RenderingControl:2 UPnP service
 */
#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2_C
#define HEADER_DVUPNPORGRENDERINGCONTROL2_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderUpnpOrgRenderingControl2
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the ListPresets action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionListPresets
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentPresetNameList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2ListPresets)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, char** aCurrentPresetNameList);
/**
 * Callback which runs when the SelectPreset action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aPresetName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SelectPreset)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aPresetName);
/**
 * Callback which runs when the GetBrightness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetBrightness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentBrightness);
/**
 * Callback which runs when the SetBrightness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBrightness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetBrightness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredBrightness);
/**
 * Callback which runs when the GetContrast action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetContrast
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentContrast
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetContrast)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentContrast);
/**
 * Callback which runs when the SetContrast action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetContrast
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredContrast
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetContrast)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredContrast);
/**
 * Callback which runs when the GetSharpness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentSharpness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetSharpness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentSharpness);
/**
 * Callback which runs when the SetSharpness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredSharpness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetSharpness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredSharpness);
/**
 * Callback which runs when the GetRedVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetRedVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentRedVideoGain);
/**
 * Callback which runs when the SetRedVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetRedVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
/**
 * Callback which runs when the GetGreenVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetGreenVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoGain);
/**
 * Callback which runs when the SetGreenVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetGreenVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
/**
 * Callback which runs when the GetBlueVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetBlueVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoGain);
/**
 * Callback which runs when the SetBlueVideoGain action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoGain
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetBlueVideoGain)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
/**
 * Callback which runs when the GetRedVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentRedVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetRedVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentRedVideoBlackLevel);
/**
 * Callback which runs when the SetRedVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredRedVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetRedVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
/**
 * Callback which runs when the GetGreenVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentGreenVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetGreenVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentGreenVideoBlackLevel);
/**
 * Callback which runs when the SetGreenVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredGreenVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetGreenVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
/**
 * Callback which runs when the GetBlueVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentBlueVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetBlueVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentBlueVideoBlackLevel);
/**
 * Callback which runs when the SetBlueVideoBlackLevel action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredBlueVideoBlackLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetBlueVideoBlackLevel)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
/**
 * Callback which runs when the GetColorTemperature action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentColorTemperature
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetColorTemperature)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t* aCurrentColorTemperature);
/**
 * Callback which runs when the SetColorTemperature action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredColorTemperature
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetColorTemperature)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
/**
 * Callback which runs when the GetHorizontalKeystone action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentHorizontalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetHorizontalKeystone)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, int32_t* aCurrentHorizontalKeystone);
/**
 * Callback which runs when the SetHorizontalKeystone action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredHorizontalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetHorizontalKeystone)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
/**
 * Callback which runs when the GetVerticalKeystone action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[out] aCurrentVerticalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetVerticalKeystone)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, int32_t* aCurrentVerticalKeystone);
/**
 * Callback which runs when the SetVerticalKeystone action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aDesiredVerticalKeystone
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetVerticalKeystone)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
/**
 * Callback which runs when the GetMute action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetMute
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetMute)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentMute);
/**
 * Callback which runs when the SetMute action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetMute
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredMute
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetMute)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredMute);
/**
 * Callback which runs when the GetVolume action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetVolume
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetVolume)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentVolume);
/**
 * Callback which runs when the SetVolume action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetVolume
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetVolume)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredVolume);
/**
 * Callback which runs when the GetVolumeDB action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetVolumeDB)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, int32_t* aCurrentVolume);
/**
 * Callback which runs when the SetVolumeDB action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredVolume
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetVolumeDB)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, int32_t aDesiredVolume);
/**
 * Callback which runs when the GetVolumeDBRange action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aMinValue
 * @param[out] aMaxValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetVolumeDBRange)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, int32_t* aMinValue, int32_t* aMaxValue);
/**
 * Callback which runs when the GetLoudness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[out] aCurrentLoudness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetLoudness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t* aCurrentLoudness);
/**
 * Callback which runs when the SetLoudness action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aChannel
 * @param[in]  aDesiredLoudness
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetLoudness)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aChannel, uint32_t aDesiredLoudness);
/**
 * Callback which runs when the GetStateVariables action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aStateVariableList
 * @param[out] aStateVariableValuePairs
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2GetStateVariables)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs);
/**
 * Callback which runs when the SetStateVariables action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aInstanceID
 * @param[in]  aRenderingControlUDN
 * @param[in]  aServiceType
 * @param[in]  aServiceId
 * @param[in]  aStateVariableValuePairs
 * @param[out] aStateVariableList
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackRenderingControl2SetStateVariables)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aInstanceID, const char* aRenderingControlUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderUpnpOrgRenderingControl2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2Destroy(THandle aProvider);

/**
 * Enable the LastChange property.
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnablePropertyLastChange(THandle aProvider);

/**
 * Register a callback for the action ListPresets
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionListPresets(THandle aProvider, CallbackRenderingControl2ListPresets aCallback, void* aPtr);
/**
 * Register a callback for the action SelectPreset
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl2SelectPreset aCallback, void* aPtr);
/**
 * Register a callback for the action GetBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl2GetBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action SetBrightness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl2SetBrightness aCallback, void* aPtr);
/**
 * Register a callback for the action GetContrast
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(THandle aProvider, CallbackRenderingControl2GetContrast aCallback, void* aPtr);
/**
 * Register a callback for the action SetContrast
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(THandle aProvider, CallbackRenderingControl2SetContrast aCallback, void* aPtr);
/**
 * Register a callback for the action GetSharpness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl2GetSharpness aCallback, void* aPtr);
/**
 * Register a callback for the action SetSharpness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl2SetSharpness aCallback, void* aPtr);
/**
 * Register a callback for the action GetRedVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetRedVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetGreenVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetGreenVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetBlueVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action SetBlueVideoGain
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr);
/**
 * Register a callback for the action GetRedVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetRedVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetGreenVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetGreenVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetBlueVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetBlueVideoBlackLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr);
/**
 * Register a callback for the action GetColorTemperature
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr);
/**
 * Register a callback for the action SetColorTemperature
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr);
/**
 * Register a callback for the action GetHorizontalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action SetHorizontalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action GetVerticalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action SetVerticalKeystone
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr);
/**
 * Register a callback for the action GetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetMute(THandle aProvider, CallbackRenderingControl2GetMute aCallback, void* aPtr);
/**
 * Register a callback for the action SetMute
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetMute(THandle aProvider, CallbackRenderingControl2SetMute aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(THandle aProvider, CallbackRenderingControl2GetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolume
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(THandle aProvider, CallbackRenderingControl2SetVolume aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolumeDB
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr);
/**
 * Register a callback for the action SetVolumeDB
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr);
/**
 * Register a callback for the action GetVolumeDBRange
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr);
/**
 * Register a callback for the action GetLoudness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl2GetLoudness aCallback, void* aPtr);
/**
 * Register a callback for the action SetLoudness
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl2SetLoudness aCallback, void* aPtr);
/**
 * Register a callback for the action GetStateVariables
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aProvider, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr);
/**
 * Register a callback for the action SetStateVariables
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aProvider, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr);

/**
 * Set the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgRenderingControl2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the LastChange property
 *
 * Can only be called if DvProviderUpnpOrgRenderingControl2EnablePropertyLastChange has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderUpnpOrgRenderingControl2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2_C

