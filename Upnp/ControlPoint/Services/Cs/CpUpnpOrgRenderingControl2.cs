using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgRenderingControl2 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern IntPtr CpProxyUpnpOrgRenderingControl2Create(IntPtr aDeviceHandle);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern void CpProxyUpnpOrgRenderingControl2Destroy(IntPtr aHandle);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncListPresets(IntPtr aHandle, uint aInstanceID, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginListPresets(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndListPresets(IntPtr aHandle, IntPtr aAsync, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSelectPreset(IntPtr aHandle, uint aInstanceID, char* aPresetName);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSelectPreset(IntPtr aHandle, uint aInstanceID, char* aPresetName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSelectPreset(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBrightness(IntPtr aHandle, uint aInstanceID, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBrightness(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBrightness(IntPtr aHandle, IntPtr aAsync, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBrightness(IntPtr aHandle, uint aInstanceID, uint aDesiredBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBrightness(IntPtr aHandle, uint aInstanceID, uint aDesiredBrightness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBrightness(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetContrast(IntPtr aHandle, uint aInstanceID, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetContrast(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetContrast(IntPtr aHandle, IntPtr aAsync, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetContrast(IntPtr aHandle, uint aInstanceID, uint aDesiredContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetContrast(IntPtr aHandle, uint aInstanceID, uint aDesiredContrast, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetContrast(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetSharpness(IntPtr aHandle, uint aInstanceID, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetSharpness(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetSharpness(IntPtr aHandle, IntPtr aAsync, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetSharpness(IntPtr aHandle, uint aInstanceID, uint aDesiredSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetSharpness(IntPtr aHandle, uint aInstanceID, uint aDesiredSharpness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetSharpness(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(IntPtr aHandle, uint aInstanceID, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(IntPtr aHandle, IntPtr aAsync, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredRedVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(IntPtr aHandle, uint aInstanceID, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(IntPtr aHandle, IntPtr aAsync, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredGreenVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(IntPtr aHandle, uint aInstanceID, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(IntPtr aHandle, IntPtr aAsync, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(IntPtr aHandle, uint aInstanceID, uint aDesiredBlueVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(IntPtr aHandle, IntPtr aAsync, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(IntPtr aHandle, IntPtr aAsync, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(IntPtr aHandle, IntPtr aAsync, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(IntPtr aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(IntPtr aHandle, uint aInstanceID, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(IntPtr aHandle, IntPtr aAsync, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(IntPtr aHandle, uint aInstanceID, uint aDesiredColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(IntPtr aHandle, uint aInstanceID, uint aDesiredColorTemperature, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(IntPtr aHandle, uint aInstanceID, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(IntPtr aHandle, IntPtr aAsync, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(IntPtr aHandle, uint aInstanceID, int aDesiredHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(IntPtr aHandle, uint aInstanceID, int aDesiredHorizontalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(IntPtr aHandle, uint aInstanceID, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(IntPtr aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(IntPtr aHandle, IntPtr aAsync, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(IntPtr aHandle, uint aInstanceID, int aDesiredVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(IntPtr aHandle, uint aInstanceID, int aDesiredVerticalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetMute(IntPtr aHandle, uint aInstanceID, char* aChannel, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetMute(IntPtr aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetMute(IntPtr aHandle, IntPtr aAsync, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetMute(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetMute(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetMute(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolume(IntPtr aHandle, uint aInstanceID, char* aChannel, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolume(IntPtr aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolume(IntPtr aHandle, IntPtr aAsync, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVolume(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVolume(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVolume(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(IntPtr aHandle, uint aInstanceID, char* aChannel, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(IntPtr aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(IntPtr aHandle, IntPtr aAsync, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(IntPtr aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(IntPtr aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(IntPtr aHandle, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(IntPtr aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(IntPtr aHandle, IntPtr aAsync, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetLoudness(IntPtr aHandle, uint aInstanceID, char* aChannel, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetLoudness(IntPtr aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetLoudness(IntPtr aHandle, IntPtr aAsync, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetLoudness(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetLoudness(IntPtr aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetLoudness(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(IntPtr aHandle, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(IntPtr aHandle, uint aInstanceID, char* aStateVariableList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetStateVariables(IntPtr aHandle, IntPtr aAsync, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(IntPtr aHandle, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(IntPtr aHandle, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetStateVariables(IntPtr aHandle, IntPtr aAsync, char** aStateVariableList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern void CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2PropertyLastChange(IntPtr aHandle, char** aLastChange);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private Callback iCallbackLastChangeChanged;

        public CpProxyUpnpOrgRenderingControl2(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgRenderingControl2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncListPresets(uint aInstanceID, out string aCurrentPresetNameList)
        {
			char* currentPresetNameList;
			{
				CpProxyUpnpOrgRenderingControl2SyncListPresets(iHandle, aInstanceID, &currentPresetNameList);
			}
            aCurrentPresetNameList = Marshal.PtrToStringAnsi((IntPtr)currentPresetNameList);
            ZappFree(currentPresetNameList);
        }

        public unsafe void BeginListPresets(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginListPresets(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndListPresets(IntPtr aAsyncHandle, out string aCurrentPresetNameList)
        {
			char* currentPresetNameList;
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndListPresets(iHandle, aAsyncHandle, &currentPresetNameList))
				{
					throw(new ProxyError());
				}
			}
            aCurrentPresetNameList = Marshal.PtrToStringAnsi((IntPtr)currentPresetNameList);
            ZappFree(currentPresetNameList);
        }

        public unsafe void SyncSelectPreset(uint aInstanceID, string aPresetName)
        {
			char* presetName = (char*)Marshal.StringToHGlobalAnsi(aPresetName);
			{
				CpProxyUpnpOrgRenderingControl2SyncSelectPreset(iHandle, aInstanceID, presetName);
			}
			Marshal.FreeHGlobal((IntPtr)presetName);
        }

        public unsafe void BeginSelectPreset(uint aInstanceID, string aPresetName, CallbackAsyncComplete aCallback)
        {
			char* presetName = (char*)Marshal.StringToHGlobalAnsi(aPresetName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSelectPreset(iHandle, aInstanceID, presetName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)presetName);
        }

        public unsafe void EndSelectPreset(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSelectPreset(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBrightness(uint aInstanceID, out uint aCurrentBrightness)
        {
			fixed (uint* currentBrightness = &aCurrentBrightness)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetBrightness(iHandle, aInstanceID, currentBrightness);
			}
        }

        public unsafe void BeginGetBrightness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetBrightness(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBrightness(IntPtr aAsyncHandle, out uint aCurrentBrightness)
        {
			fixed (uint* currentBrightness = &aCurrentBrightness)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetBrightness(iHandle, aAsyncHandle, currentBrightness))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBrightness(uint aInstanceID, uint aDesiredBrightness)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetBrightness(iHandle, aInstanceID, aDesiredBrightness);
			}
        }

        public unsafe void BeginSetBrightness(uint aInstanceID, uint aDesiredBrightness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetBrightness(iHandle, aInstanceID, aDesiredBrightness, iActionComplete, ptr);
        }

        public unsafe void EndSetBrightness(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetBrightness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetContrast(uint aInstanceID, out uint aCurrentContrast)
        {
			fixed (uint* currentContrast = &aCurrentContrast)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetContrast(iHandle, aInstanceID, currentContrast);
			}
        }

        public unsafe void BeginGetContrast(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetContrast(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetContrast(IntPtr aAsyncHandle, out uint aCurrentContrast)
        {
			fixed (uint* currentContrast = &aCurrentContrast)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetContrast(iHandle, aAsyncHandle, currentContrast))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetContrast(uint aInstanceID, uint aDesiredContrast)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetContrast(iHandle, aInstanceID, aDesiredContrast);
			}
        }

        public unsafe void BeginSetContrast(uint aInstanceID, uint aDesiredContrast, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetContrast(iHandle, aInstanceID, aDesiredContrast, iActionComplete, ptr);
        }

        public unsafe void EndSetContrast(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetContrast(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetSharpness(uint aInstanceID, out uint aCurrentSharpness)
        {
			fixed (uint* currentSharpness = &aCurrentSharpness)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetSharpness(iHandle, aInstanceID, currentSharpness);
			}
        }

        public unsafe void BeginGetSharpness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetSharpness(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetSharpness(IntPtr aAsyncHandle, out uint aCurrentSharpness)
        {
			fixed (uint* currentSharpness = &aCurrentSharpness)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetSharpness(iHandle, aAsyncHandle, currentSharpness))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetSharpness(uint aInstanceID, uint aDesiredSharpness)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetSharpness(iHandle, aInstanceID, aDesiredSharpness);
			}
        }

        public unsafe void BeginSetSharpness(uint aInstanceID, uint aDesiredSharpness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetSharpness(iHandle, aInstanceID, aDesiredSharpness, iActionComplete, ptr);
        }

        public unsafe void EndSetSharpness(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetSharpness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRedVideoGain(uint aInstanceID, out uint aCurrentRedVideoGain)
        {
			fixed (uint* currentRedVideoGain = &aCurrentRedVideoGain)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(iHandle, aInstanceID, currentRedVideoGain);
			}
        }

        public unsafe void BeginGetRedVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetRedVideoGain(IntPtr aAsyncHandle, out uint aCurrentRedVideoGain)
        {
			fixed (uint* currentRedVideoGain = &aCurrentRedVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(iHandle, aAsyncHandle, currentRedVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(iHandle, aInstanceID, aDesiredRedVideoGain);
			}
        }

        public unsafe void BeginSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(iHandle, aInstanceID, aDesiredRedVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetRedVideoGain(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetGreenVideoGain(uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
			fixed (uint* currentGreenVideoGain = &aCurrentGreenVideoGain)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(iHandle, aInstanceID, currentGreenVideoGain);
			}
        }

        public unsafe void BeginGetGreenVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetGreenVideoGain(IntPtr aAsyncHandle, out uint aCurrentGreenVideoGain)
        {
			fixed (uint* currentGreenVideoGain = &aCurrentGreenVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(iHandle, aAsyncHandle, currentGreenVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(iHandle, aInstanceID, aDesiredGreenVideoGain);
			}
        }

        public unsafe void BeginSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(iHandle, aInstanceID, aDesiredGreenVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetGreenVideoGain(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBlueVideoGain(uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
			fixed (uint* currentBlueVideoGain = &aCurrentBlueVideoGain)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(iHandle, aInstanceID, currentBlueVideoGain);
			}
        }

        public unsafe void BeginGetBlueVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBlueVideoGain(IntPtr aAsyncHandle, out uint aCurrentBlueVideoGain)
        {
			fixed (uint* currentBlueVideoGain = &aCurrentBlueVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(iHandle, aAsyncHandle, currentBlueVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(iHandle, aInstanceID, aDesiredBlueVideoGain);
			}
        }

        public unsafe void BeginSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(iHandle, aInstanceID, aDesiredBlueVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetBlueVideoGain(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRedVideoBlackLevel(uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
			fixed (uint* currentRedVideoBlackLevel = &aCurrentRedVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(iHandle, aInstanceID, currentRedVideoBlackLevel);
			}
        }

        public unsafe void BeginGetRedVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetRedVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentRedVideoBlackLevel)
        {
			fixed (uint* currentRedVideoBlackLevel = &aCurrentRedVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(iHandle, aAsyncHandle, currentRedVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(iHandle, aInstanceID, aDesiredRedVideoBlackLevel);
			}
        }

        public unsafe void BeginSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(iHandle, aInstanceID, aDesiredRedVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetRedVideoBlackLevel(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetGreenVideoBlackLevel(uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
			fixed (uint* currentGreenVideoBlackLevel = &aCurrentGreenVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(iHandle, aInstanceID, currentGreenVideoBlackLevel);
			}
        }

        public unsafe void BeginGetGreenVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetGreenVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentGreenVideoBlackLevel)
        {
			fixed (uint* currentGreenVideoBlackLevel = &aCurrentGreenVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(iHandle, aAsyncHandle, currentGreenVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(iHandle, aInstanceID, aDesiredGreenVideoBlackLevel);
			}
        }

        public unsafe void BeginSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(iHandle, aInstanceID, aDesiredGreenVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetGreenVideoBlackLevel(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBlueVideoBlackLevel(uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
			fixed (uint* currentBlueVideoBlackLevel = &aCurrentBlueVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(iHandle, aInstanceID, currentBlueVideoBlackLevel);
			}
        }

        public unsafe void BeginGetBlueVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBlueVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentBlueVideoBlackLevel)
        {
			fixed (uint* currentBlueVideoBlackLevel = &aCurrentBlueVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(iHandle, aAsyncHandle, currentBlueVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(iHandle, aInstanceID, aDesiredBlueVideoBlackLevel);
			}
        }

        public unsafe void BeginSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(iHandle, aInstanceID, aDesiredBlueVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetBlueVideoBlackLevel(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetColorTemperature(uint aInstanceID, out uint aCurrentColorTemperature)
        {
			fixed (uint* currentColorTemperature = &aCurrentColorTemperature)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(iHandle, aInstanceID, currentColorTemperature);
			}
        }

        public unsafe void BeginGetColorTemperature(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetColorTemperature(IntPtr aAsyncHandle, out uint aCurrentColorTemperature)
        {
			fixed (uint* currentColorTemperature = &aCurrentColorTemperature)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(iHandle, aAsyncHandle, currentColorTemperature))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(iHandle, aInstanceID, aDesiredColorTemperature);
			}
        }

        public unsafe void BeginSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(iHandle, aInstanceID, aDesiredColorTemperature, iActionComplete, ptr);
        }

        public unsafe void EndSetColorTemperature(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetHorizontalKeystone(uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
			fixed (int* currentHorizontalKeystone = &aCurrentHorizontalKeystone)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(iHandle, aInstanceID, currentHorizontalKeystone);
			}
        }

        public unsafe void BeginGetHorizontalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetHorizontalKeystone(IntPtr aAsyncHandle, out int aCurrentHorizontalKeystone)
        {
			fixed (int* currentHorizontalKeystone = &aCurrentHorizontalKeystone)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(iHandle, aAsyncHandle, currentHorizontalKeystone))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(iHandle, aInstanceID, aDesiredHorizontalKeystone);
			}
        }

        public unsafe void BeginSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(iHandle, aInstanceID, aDesiredHorizontalKeystone, iActionComplete, ptr);
        }

        public unsafe void EndSetHorizontalKeystone(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetVerticalKeystone(uint aInstanceID, out int aCurrentVerticalKeystone)
        {
			fixed (int* currentVerticalKeystone = &aCurrentVerticalKeystone)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(iHandle, aInstanceID, currentVerticalKeystone);
			}
        }

        public unsafe void BeginGetVerticalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetVerticalKeystone(IntPtr aAsyncHandle, out int aCurrentVerticalKeystone)
        {
			fixed (int* currentVerticalKeystone = &aCurrentVerticalKeystone)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(iHandle, aAsyncHandle, currentVerticalKeystone))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone)
        {
			{
				CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(iHandle, aInstanceID, aDesiredVerticalKeystone);
			}
        }

        public unsafe void BeginSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(iHandle, aInstanceID, aDesiredVerticalKeystone, iActionComplete, ptr);
        }

        public unsafe void EndSetVerticalKeystone(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetMute(uint aInstanceID, string aChannel, out bool aCurrentMute)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint currentMute;
			{
				CpProxyUpnpOrgRenderingControl2SyncGetMute(iHandle, aInstanceID, channel, &currentMute);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
			aCurrentMute = (currentMute != 0);
        }

        public unsafe void BeginGetMute(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetMute(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetMute(IntPtr aAsyncHandle, out bool aCurrentMute)
        {
			uint currentMute;
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetMute(iHandle, aAsyncHandle, &currentMute))
				{
					throw(new ProxyError());
				}
			}
			aCurrentMute = (currentMute != 0);
        }

        public unsafe void SyncSetMute(uint aInstanceID, string aChannel, bool aDesiredMute)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredMute = (aDesiredMute? 1u : 0u);
			{
				CpProxyUpnpOrgRenderingControl2SyncSetMute(iHandle, aInstanceID, channel, desiredMute);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetMute(uint aInstanceID, string aChannel, bool aDesiredMute, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredMute = (aDesiredMute? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetMute(iHandle, aInstanceID, channel, desiredMute, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetMute(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetMute(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetVolume(uint aInstanceID, string aChannel, out uint aCurrentVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			fixed (uint* currentVolume = &aCurrentVolume)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetVolume(iHandle, aInstanceID, channel, currentVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolume(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetVolume(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolume(IntPtr aAsyncHandle, out uint aCurrentVolume)
        {
			fixed (uint* currentVolume = &aCurrentVolume)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetVolume(iHandle, aAsyncHandle, currentVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolume(uint aInstanceID, string aChannel, uint aDesiredVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			{
				CpProxyUpnpOrgRenderingControl2SyncSetVolume(iHandle, aInstanceID, channel, aDesiredVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetVolume(uint aInstanceID, string aChannel, uint aDesiredVolume, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetVolume(iHandle, aInstanceID, channel, aDesiredVolume, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetVolume(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetVolume(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetVolumeDB(uint aInstanceID, string aChannel, out int aCurrentVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			fixed (int* currentVolume = &aCurrentVolume)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(iHandle, aInstanceID, channel, currentVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolumeDB(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolumeDB(IntPtr aAsyncHandle, out int aCurrentVolume)
        {
			fixed (int* currentVolume = &aCurrentVolume)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(iHandle, aAsyncHandle, currentVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolumeDB(uint aInstanceID, string aChannel, int aDesiredVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			{
				CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(iHandle, aInstanceID, channel, aDesiredVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetVolumeDB(uint aInstanceID, string aChannel, int aDesiredVolume, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(iHandle, aInstanceID, channel, aDesiredVolume, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetVolumeDB(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetVolumeDBRange(uint aInstanceID, string aChannel, out int aMinValue, out int aMaxValue)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			fixed (int* minValue = &aMinValue)
			fixed (int* maxValue = &aMaxValue)
			{
				CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(iHandle, aInstanceID, channel, minValue, maxValue);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolumeDBRange(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolumeDBRange(IntPtr aAsyncHandle, out int aMinValue, out int aMaxValue)
        {
			fixed (int* minValue = &aMinValue)
			fixed (int* maxValue = &aMaxValue)
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(iHandle, aAsyncHandle, minValue, maxValue))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetLoudness(uint aInstanceID, string aChannel, out bool aCurrentLoudness)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint currentLoudness;
			{
				CpProxyUpnpOrgRenderingControl2SyncGetLoudness(iHandle, aInstanceID, channel, &currentLoudness);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
			aCurrentLoudness = (currentLoudness != 0);
        }

        public unsafe void BeginGetLoudness(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetLoudness(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetLoudness(IntPtr aAsyncHandle, out bool aCurrentLoudness)
        {
			uint currentLoudness;
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetLoudness(iHandle, aAsyncHandle, &currentLoudness))
				{
					throw(new ProxyError());
				}
			}
			aCurrentLoudness = (currentLoudness != 0);
        }

        public unsafe void SyncSetLoudness(uint aInstanceID, string aChannel, bool aDesiredLoudness)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredLoudness = (aDesiredLoudness? 1u : 0u);
			{
				CpProxyUpnpOrgRenderingControl2SyncSetLoudness(iHandle, aInstanceID, channel, desiredLoudness);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetLoudness(uint aInstanceID, string aChannel, bool aDesiredLoudness, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredLoudness = (aDesiredLoudness? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetLoudness(iHandle, aInstanceID, channel, desiredLoudness, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetLoudness(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetLoudness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetStateVariables(uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
        {
			char* stateVariableList = (char*)Marshal.StringToHGlobalAnsi(aStateVariableList);
			char* stateVariableValuePairs;
			{
				CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(iHandle, aInstanceID, stateVariableList, &stateVariableValuePairs);
			}
			Marshal.FreeHGlobal((IntPtr)stateVariableList);
            aStateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)stateVariableValuePairs);
            ZappFree(stateVariableValuePairs);
        }

        public unsafe void BeginGetStateVariables(uint aInstanceID, string aStateVariableList, CallbackAsyncComplete aCallback)
        {
			char* stateVariableList = (char*)Marshal.StringToHGlobalAnsi(aStateVariableList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(iHandle, aInstanceID, stateVariableList, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)stateVariableList);
        }

        public unsafe void EndGetStateVariables(IntPtr aAsyncHandle, out string aStateVariableValuePairs)
        {
			char* stateVariableValuePairs;
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndGetStateVariables(iHandle, aAsyncHandle, &stateVariableValuePairs))
				{
					throw(new ProxyError());
				}
			}
            aStateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)stateVariableValuePairs);
            ZappFree(stateVariableValuePairs);
        }

        public unsafe void SyncSetStateVariables(uint aInstanceID, string aRenderingControlUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
			char* renderingControlUDN = (char*)Marshal.StringToHGlobalAnsi(aRenderingControlUDN);
			char* serviceType = (char*)Marshal.StringToHGlobalAnsi(aServiceType);
			char* serviceId = (char*)Marshal.StringToHGlobalAnsi(aServiceId);
			char* stateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(aStateVariableValuePairs);
			char* stateVariableList;
			{
				CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(iHandle, aInstanceID, renderingControlUDN, serviceType, serviceId, stateVariableValuePairs, &stateVariableList);
			}
			Marshal.FreeHGlobal((IntPtr)renderingControlUDN);
			Marshal.FreeHGlobal((IntPtr)serviceType);
			Marshal.FreeHGlobal((IntPtr)serviceId);
			Marshal.FreeHGlobal((IntPtr)stateVariableValuePairs);
            aStateVariableList = Marshal.PtrToStringAnsi((IntPtr)stateVariableList);
            ZappFree(stateVariableList);
        }

        public unsafe void BeginSetStateVariables(uint aInstanceID, string aRenderingControlUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, CallbackAsyncComplete aCallback)
        {
			char* renderingControlUDN = (char*)Marshal.StringToHGlobalAnsi(aRenderingControlUDN);
			char* serviceType = (char*)Marshal.StringToHGlobalAnsi(aServiceType);
			char* serviceId = (char*)Marshal.StringToHGlobalAnsi(aServiceId);
			char* stateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(aStateVariableValuePairs);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(iHandle, aInstanceID, renderingControlUDN, serviceType, serviceId, stateVariableValuePairs, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)renderingControlUDN);
			Marshal.FreeHGlobal((IntPtr)serviceType);
			Marshal.FreeHGlobal((IntPtr)serviceId);
			Marshal.FreeHGlobal((IntPtr)stateVariableValuePairs);
        }

        public unsafe void EndSetStateVariables(IntPtr aAsyncHandle, out string aStateVariableList)
        {
			char* stateVariableList;
			{
				if (0 != CpProxyUpnpOrgRenderingControl2EndSetStateVariables(iHandle, aAsyncHandle, &stateVariableList))
				{
					throw(new ProxyError());
				}
			}
            aStateVariableList = Marshal.PtrToStringAnsi((IntPtr)stateVariableList);
            ZappFree(stateVariableList);
        }

        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgRenderingControl2 self = (CpProxyUpnpOrgRenderingControl2)gch.Target;
            self.iLastChangeChanged();
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgRenderingControl2PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgRenderingControl2()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            CpProxyUpnpOrgRenderingControl2Destroy(handle);
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

