using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgRenderingControl2 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern uint CpProxyUpnpOrgRenderingControl2Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern void CpProxyUpnpOrgRenderingControl2Destroy(uint aHandle);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncListPresets(uint aHandle, uint aInstanceID, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginListPresets(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndListPresets(uint aHandle, uint aAsync, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSelectPreset(uint aHandle, uint aInstanceID, char* aPresetName);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSelectPreset(uint aHandle, uint aInstanceID, char* aPresetName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSelectPreset(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBrightness(uint aHandle, uint aInstanceID, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBrightness(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBrightness(uint aHandle, uint aAsync, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBrightness(uint aHandle, uint aInstanceID, uint aDesiredBrightness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBrightness(uint aHandle, uint aInstanceID, uint aDesiredBrightness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBrightness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetContrast(uint aHandle, uint aInstanceID, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetContrast(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetContrast(uint aHandle, uint aAsync, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetContrast(uint aHandle, uint aInstanceID, uint aDesiredContrast);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetContrast(uint aHandle, uint aInstanceID, uint aDesiredContrast, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetContrast(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetSharpness(uint aHandle, uint aInstanceID, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetSharpness(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetSharpness(uint aHandle, uint aAsync, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetSharpness(uint aHandle, uint aInstanceID, uint aDesiredSharpness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetSharpness(uint aHandle, uint aInstanceID, uint aDesiredSharpness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetSharpness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetRedVideoGain(uint aHandle, uint aAsync, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoGain(uint aHandle, uint aInstanceID, uint aDesiredRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoGain(uint aHandle, uint aInstanceID, uint aDesiredRedVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetRedVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetGreenVideoGain(uint aHandle, uint aAsync, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoGain(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoGain(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetGreenVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBlueVideoGain(uint aHandle, uint aAsync, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoGain(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoGain(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBlueVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetRedVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetRedVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetRedVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetGreenVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetGreenVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetBlueVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetBlueVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetColorTemperature(uint aHandle, uint aInstanceID, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetColorTemperature(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetColorTemperature(uint aHandle, uint aAsync, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetColorTemperature(uint aHandle, uint aInstanceID, uint aDesiredColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetColorTemperature(uint aHandle, uint aInstanceID, uint aDesiredColorTemperature, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetColorTemperature(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetHorizontalKeystone(uint aHandle, uint aInstanceID, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetHorizontalKeystone(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetHorizontalKeystone(uint aHandle, uint aAsync, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetHorizontalKeystone(uint aHandle, uint aInstanceID, int aDesiredHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetHorizontalKeystone(uint aHandle, uint aInstanceID, int aDesiredHorizontalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetHorizontalKeystone(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVerticalKeystone(uint aHandle, uint aInstanceID, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVerticalKeystone(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVerticalKeystone(uint aHandle, uint aAsync, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVerticalKeystone(uint aHandle, uint aInstanceID, int aDesiredVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVerticalKeystone(uint aHandle, uint aInstanceID, int aDesiredVerticalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVerticalKeystone(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetMute(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetMute(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetMute(uint aHandle, uint aAsync, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetMute(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetMute(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetMute(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolume(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolume(uint aHandle, uint aAsync, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVolume(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolumeDB(uint aHandle, uint aAsync, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetVolumeDB(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetVolumeDBRange(uint aHandle, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetVolumeDBRange(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetVolumeDBRange(uint aHandle, uint aAsync, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetLoudness(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetLoudness(uint aHandle, uint aAsync, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetLoudness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncGetStateVariables(uint aHandle, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginGetStateVariables(uint aHandle, uint aInstanceID, char* aStateVariableList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndGetStateVariables(uint aHandle, uint aAsync, char** aStateVariableValuePairs);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2SyncSetStateVariables(uint aHandle, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2BeginSetStateVariables(uint aHandle, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl2EndSetStateVariables(uint aHandle, uint aAsync, char** aStateVariableList);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern void CpProxyUpnpOrgRenderingControl2SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl2")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl2PropertyLastChange(uint aHandle, char** aLastChange);
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

        public unsafe void EndListPresets(uint aAsyncHandle, out string aCurrentPresetNameList)
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

        public unsafe void EndSelectPreset(uint aAsyncHandle)
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

        public unsafe void EndGetBrightness(uint aAsyncHandle, out uint aCurrentBrightness)
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

        public unsafe void EndSetBrightness(uint aAsyncHandle)
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

        public unsafe void EndGetContrast(uint aAsyncHandle, out uint aCurrentContrast)
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

        public unsafe void EndSetContrast(uint aAsyncHandle)
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

        public unsafe void EndGetSharpness(uint aAsyncHandle, out uint aCurrentSharpness)
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

        public unsafe void EndSetSharpness(uint aAsyncHandle)
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

        public unsafe void EndGetRedVideoGain(uint aAsyncHandle, out uint aCurrentRedVideoGain)
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

        public unsafe void EndSetRedVideoGain(uint aAsyncHandle)
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

        public unsafe void EndGetGreenVideoGain(uint aAsyncHandle, out uint aCurrentGreenVideoGain)
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

        public unsafe void EndSetGreenVideoGain(uint aAsyncHandle)
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

        public unsafe void EndGetBlueVideoGain(uint aAsyncHandle, out uint aCurrentBlueVideoGain)
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

        public unsafe void EndSetBlueVideoGain(uint aAsyncHandle)
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

        public unsafe void EndGetRedVideoBlackLevel(uint aAsyncHandle, out uint aCurrentRedVideoBlackLevel)
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

        public unsafe void EndSetRedVideoBlackLevel(uint aAsyncHandle)
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

        public unsafe void EndGetGreenVideoBlackLevel(uint aAsyncHandle, out uint aCurrentGreenVideoBlackLevel)
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

        public unsafe void EndSetGreenVideoBlackLevel(uint aAsyncHandle)
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

        public unsafe void EndGetBlueVideoBlackLevel(uint aAsyncHandle, out uint aCurrentBlueVideoBlackLevel)
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

        public unsafe void EndSetBlueVideoBlackLevel(uint aAsyncHandle)
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

        public unsafe void EndGetColorTemperature(uint aAsyncHandle, out uint aCurrentColorTemperature)
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

        public unsafe void EndSetColorTemperature(uint aAsyncHandle)
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

        public unsafe void EndGetHorizontalKeystone(uint aAsyncHandle, out int aCurrentHorizontalKeystone)
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

        public unsafe void EndSetHorizontalKeystone(uint aAsyncHandle)
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

        public unsafe void EndGetVerticalKeystone(uint aAsyncHandle, out int aCurrentVerticalKeystone)
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

        public unsafe void EndSetVerticalKeystone(uint aAsyncHandle)
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

        public unsafe void EndGetMute(uint aAsyncHandle, out bool aCurrentMute)
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

        public unsafe void EndSetMute(uint aAsyncHandle)
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

        public unsafe void EndGetVolume(uint aAsyncHandle, out uint aCurrentVolume)
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

        public unsafe void EndSetVolume(uint aAsyncHandle)
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

        public unsafe void EndGetVolumeDB(uint aAsyncHandle, out int aCurrentVolume)
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

        public unsafe void EndSetVolumeDB(uint aAsyncHandle)
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

        public unsafe void EndGetVolumeDBRange(uint aAsyncHandle, out int aMinValue, out int aMaxValue)
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

        public unsafe void EndGetLoudness(uint aAsyncHandle, out bool aCurrentLoudness)
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

        public unsafe void EndSetLoudness(uint aAsyncHandle)
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

        public unsafe void EndGetStateVariables(uint aAsyncHandle, out string aStateVariableValuePairs)
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

        public unsafe void EndSetStateVariables(uint aAsyncHandle, out string aStateVariableList)
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
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
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

