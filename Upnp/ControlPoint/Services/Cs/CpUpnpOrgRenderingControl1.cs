using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgRenderingControl1 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern uint CpProxyUpnpOrgRenderingControl1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern void CpProxyUpnpOrgRenderingControl1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncListPresets(uint aHandle, uint aInstanceID, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginListPresets(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndListPresets(uint aHandle, uint aAsync, char** aCurrentPresetNameList);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSelectPreset(uint aHandle, uint aInstanceID, char* aPresetName);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSelectPreset(uint aHandle, uint aInstanceID, char* aPresetName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSelectPreset(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetBrightness(uint aHandle, uint aInstanceID, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetBrightness(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetBrightness(uint aHandle, uint aAsync, uint* aCurrentBrightness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetBrightness(uint aHandle, uint aInstanceID, uint aDesiredBrightness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetBrightness(uint aHandle, uint aInstanceID, uint aDesiredBrightness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetBrightness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetContrast(uint aHandle, uint aInstanceID, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetContrast(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetContrast(uint aHandle, uint aAsync, uint* aCurrentContrast);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetContrast(uint aHandle, uint aInstanceID, uint aDesiredContrast);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetContrast(uint aHandle, uint aInstanceID, uint aDesiredContrast, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetContrast(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetSharpness(uint aHandle, uint aInstanceID, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetSharpness(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetSharpness(uint aHandle, uint aAsync, uint* aCurrentSharpness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetSharpness(uint aHandle, uint aInstanceID, uint aDesiredSharpness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetSharpness(uint aHandle, uint aInstanceID, uint aDesiredSharpness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetSharpness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetRedVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetRedVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetRedVideoGain(uint aHandle, uint aAsync, uint* aCurrentRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetRedVideoGain(uint aHandle, uint aInstanceID, uint aDesiredRedVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetRedVideoGain(uint aHandle, uint aInstanceID, uint aDesiredRedVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetRedVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetGreenVideoGain(uint aHandle, uint aAsync, uint* aCurrentGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoGain(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoGain(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetGreenVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoGain(uint aHandle, uint aInstanceID, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoGain(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetBlueVideoGain(uint aHandle, uint aAsync, uint* aCurrentBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoGain(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoGain);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoGain(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoGain, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetBlueVideoGain(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetRedVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetRedVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetRedVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetRedVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetGreenVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetGreenVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetBlueVideoBlackLevel(uint aHandle, uint aAsync, uint* aCurrentBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoBlackLevel(uint aHandle, uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetBlueVideoBlackLevel(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetColorTemperature(uint aHandle, uint aInstanceID, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetColorTemperature(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetColorTemperature(uint aHandle, uint aAsync, uint* aCurrentColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetColorTemperature(uint aHandle, uint aInstanceID, uint aDesiredColorTemperature);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetColorTemperature(uint aHandle, uint aInstanceID, uint aDesiredColorTemperature, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetColorTemperature(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetHorizontalKeystone(uint aHandle, uint aInstanceID, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetHorizontalKeystone(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetHorizontalKeystone(uint aHandle, uint aAsync, int* aCurrentHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetHorizontalKeystone(uint aHandle, uint aInstanceID, int aDesiredHorizontalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetHorizontalKeystone(uint aHandle, uint aInstanceID, int aDesiredHorizontalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetHorizontalKeystone(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetVerticalKeystone(uint aHandle, uint aInstanceID, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetVerticalKeystone(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetVerticalKeystone(uint aHandle, uint aAsync, int* aCurrentVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetVerticalKeystone(uint aHandle, uint aInstanceID, int aDesiredVerticalKeystone);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetVerticalKeystone(uint aHandle, uint aInstanceID, int aDesiredVerticalKeystone, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetVerticalKeystone(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetMute(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetMute(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetMute(uint aHandle, uint aAsync, uint* aCurrentMute);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetMute(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetMute(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredMute, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetMute(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetVolume(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetVolume(uint aHandle, uint aAsync, uint* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetVolume(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetVolume(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetVolumeDB(uint aHandle, uint aAsync, int* aCurrentVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetVolumeDB(uint aHandle, uint aInstanceID, char* aChannel, int aDesiredVolume, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetVolumeDB(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetVolumeDBRange(uint aHandle, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetVolumeDBRange(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetVolumeDBRange(uint aHandle, uint aAsync, int* aMinValue, int* aMaxValue);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncGetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginGetLoudness(uint aHandle, uint aInstanceID, char* aChannel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndGetLoudness(uint aHandle, uint aAsync, uint* aCurrentLoudness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1SyncSetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1BeginSetLoudness(uint aHandle, uint aInstanceID, char* aChannel, uint aDesiredLoudness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe int CpProxyUpnpOrgRenderingControl1EndSetLoudness(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern void CpProxyUpnpOrgRenderingControl1SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgRenderingControl1")]
        static extern unsafe void CpProxyUpnpOrgRenderingControl1PropertyLastChange(uint aHandle, char** aLastChange);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private Callback iCallbackLastChangeChanged;

        public CpProxyUpnpOrgRenderingControl1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgRenderingControl1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncListPresets(uint aInstanceID, out string aCurrentPresetNameList)
        {
			char* currentPresetNameList;
			{
				CpProxyUpnpOrgRenderingControl1SyncListPresets(iHandle, aInstanceID, &currentPresetNameList);
			}
            aCurrentPresetNameList = Marshal.PtrToStringAnsi((IntPtr)currentPresetNameList);
            ZappFree(currentPresetNameList);
        }

        public unsafe void BeginListPresets(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginListPresets(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndListPresets(uint aAsyncHandle, out string aCurrentPresetNameList)
        {
			char* currentPresetNameList;
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndListPresets(iHandle, aAsyncHandle, &currentPresetNameList))
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
				CpProxyUpnpOrgRenderingControl1SyncSelectPreset(iHandle, aInstanceID, presetName);
			}
			Marshal.FreeHGlobal((IntPtr)presetName);
        }

        public unsafe void BeginSelectPreset(uint aInstanceID, string aPresetName, CallbackAsyncComplete aCallback)
        {
			char* presetName = (char*)Marshal.StringToHGlobalAnsi(aPresetName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSelectPreset(iHandle, aInstanceID, presetName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)presetName);
        }

        public unsafe void EndSelectPreset(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSelectPreset(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBrightness(uint aInstanceID, out uint aCurrentBrightness)
        {
			fixed (uint* currentBrightness = &aCurrentBrightness)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetBrightness(iHandle, aInstanceID, currentBrightness);
			}
        }

        public unsafe void BeginGetBrightness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetBrightness(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBrightness(uint aAsyncHandle, out uint aCurrentBrightness)
        {
			fixed (uint* currentBrightness = &aCurrentBrightness)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetBrightness(iHandle, aAsyncHandle, currentBrightness))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBrightness(uint aInstanceID, uint aDesiredBrightness)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetBrightness(iHandle, aInstanceID, aDesiredBrightness);
			}
        }

        public unsafe void BeginSetBrightness(uint aInstanceID, uint aDesiredBrightness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetBrightness(iHandle, aInstanceID, aDesiredBrightness, iActionComplete, ptr);
        }

        public unsafe void EndSetBrightness(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetBrightness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetContrast(uint aInstanceID, out uint aCurrentContrast)
        {
			fixed (uint* currentContrast = &aCurrentContrast)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetContrast(iHandle, aInstanceID, currentContrast);
			}
        }

        public unsafe void BeginGetContrast(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetContrast(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetContrast(uint aAsyncHandle, out uint aCurrentContrast)
        {
			fixed (uint* currentContrast = &aCurrentContrast)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetContrast(iHandle, aAsyncHandle, currentContrast))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetContrast(uint aInstanceID, uint aDesiredContrast)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetContrast(iHandle, aInstanceID, aDesiredContrast);
			}
        }

        public unsafe void BeginSetContrast(uint aInstanceID, uint aDesiredContrast, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetContrast(iHandle, aInstanceID, aDesiredContrast, iActionComplete, ptr);
        }

        public unsafe void EndSetContrast(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetContrast(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetSharpness(uint aInstanceID, out uint aCurrentSharpness)
        {
			fixed (uint* currentSharpness = &aCurrentSharpness)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetSharpness(iHandle, aInstanceID, currentSharpness);
			}
        }

        public unsafe void BeginGetSharpness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetSharpness(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetSharpness(uint aAsyncHandle, out uint aCurrentSharpness)
        {
			fixed (uint* currentSharpness = &aCurrentSharpness)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetSharpness(iHandle, aAsyncHandle, currentSharpness))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetSharpness(uint aInstanceID, uint aDesiredSharpness)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetSharpness(iHandle, aInstanceID, aDesiredSharpness);
			}
        }

        public unsafe void BeginSetSharpness(uint aInstanceID, uint aDesiredSharpness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetSharpness(iHandle, aInstanceID, aDesiredSharpness, iActionComplete, ptr);
        }

        public unsafe void EndSetSharpness(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetSharpness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRedVideoGain(uint aInstanceID, out uint aCurrentRedVideoGain)
        {
			fixed (uint* currentRedVideoGain = &aCurrentRedVideoGain)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetRedVideoGain(iHandle, aInstanceID, currentRedVideoGain);
			}
        }

        public unsafe void BeginGetRedVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetRedVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetRedVideoGain(uint aAsyncHandle, out uint aCurrentRedVideoGain)
        {
			fixed (uint* currentRedVideoGain = &aCurrentRedVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetRedVideoGain(iHandle, aAsyncHandle, currentRedVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetRedVideoGain(iHandle, aInstanceID, aDesiredRedVideoGain);
			}
        }

        public unsafe void BeginSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetRedVideoGain(iHandle, aInstanceID, aDesiredRedVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetRedVideoGain(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetRedVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetGreenVideoGain(uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
			fixed (uint* currentGreenVideoGain = &aCurrentGreenVideoGain)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoGain(iHandle, aInstanceID, currentGreenVideoGain);
			}
        }

        public unsafe void BeginGetGreenVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetGreenVideoGain(uint aAsyncHandle, out uint aCurrentGreenVideoGain)
        {
			fixed (uint* currentGreenVideoGain = &aCurrentGreenVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetGreenVideoGain(iHandle, aAsyncHandle, currentGreenVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoGain(iHandle, aInstanceID, aDesiredGreenVideoGain);
			}
        }

        public unsafe void BeginSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoGain(iHandle, aInstanceID, aDesiredGreenVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetGreenVideoGain(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetGreenVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBlueVideoGain(uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
			fixed (uint* currentBlueVideoGain = &aCurrentBlueVideoGain)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoGain(iHandle, aInstanceID, currentBlueVideoGain);
			}
        }

        public unsafe void BeginGetBlueVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoGain(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBlueVideoGain(uint aAsyncHandle, out uint aCurrentBlueVideoGain)
        {
			fixed (uint* currentBlueVideoGain = &aCurrentBlueVideoGain)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetBlueVideoGain(iHandle, aAsyncHandle, currentBlueVideoGain))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoGain(iHandle, aInstanceID, aDesiredBlueVideoGain);
			}
        }

        public unsafe void BeginSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoGain(iHandle, aInstanceID, aDesiredBlueVideoGain, iActionComplete, ptr);
        }

        public unsafe void EndSetBlueVideoGain(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetBlueVideoGain(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetRedVideoBlackLevel(uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
			fixed (uint* currentRedVideoBlackLevel = &aCurrentRedVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetRedVideoBlackLevel(iHandle, aInstanceID, currentRedVideoBlackLevel);
			}
        }

        public unsafe void BeginGetRedVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetRedVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetRedVideoBlackLevel(uint aAsyncHandle, out uint aCurrentRedVideoBlackLevel)
        {
			fixed (uint* currentRedVideoBlackLevel = &aCurrentRedVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetRedVideoBlackLevel(iHandle, aAsyncHandle, currentRedVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetRedVideoBlackLevel(iHandle, aInstanceID, aDesiredRedVideoBlackLevel);
			}
        }

        public unsafe void BeginSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetRedVideoBlackLevel(iHandle, aInstanceID, aDesiredRedVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetRedVideoBlackLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetRedVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetGreenVideoBlackLevel(uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
			fixed (uint* currentGreenVideoBlackLevel = &aCurrentGreenVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetGreenVideoBlackLevel(iHandle, aInstanceID, currentGreenVideoBlackLevel);
			}
        }

        public unsafe void BeginGetGreenVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetGreenVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetGreenVideoBlackLevel(uint aAsyncHandle, out uint aCurrentGreenVideoBlackLevel)
        {
			fixed (uint* currentGreenVideoBlackLevel = &aCurrentGreenVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetGreenVideoBlackLevel(iHandle, aAsyncHandle, currentGreenVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetGreenVideoBlackLevel(iHandle, aInstanceID, aDesiredGreenVideoBlackLevel);
			}
        }

        public unsafe void BeginSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetGreenVideoBlackLevel(iHandle, aInstanceID, aDesiredGreenVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetGreenVideoBlackLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetGreenVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBlueVideoBlackLevel(uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
			fixed (uint* currentBlueVideoBlackLevel = &aCurrentBlueVideoBlackLevel)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetBlueVideoBlackLevel(iHandle, aInstanceID, currentBlueVideoBlackLevel);
			}
        }

        public unsafe void BeginGetBlueVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetBlueVideoBlackLevel(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetBlueVideoBlackLevel(uint aAsyncHandle, out uint aCurrentBlueVideoBlackLevel)
        {
			fixed (uint* currentBlueVideoBlackLevel = &aCurrentBlueVideoBlackLevel)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetBlueVideoBlackLevel(iHandle, aAsyncHandle, currentBlueVideoBlackLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetBlueVideoBlackLevel(iHandle, aInstanceID, aDesiredBlueVideoBlackLevel);
			}
        }

        public unsafe void BeginSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetBlueVideoBlackLevel(iHandle, aInstanceID, aDesiredBlueVideoBlackLevel, iActionComplete, ptr);
        }

        public unsafe void EndSetBlueVideoBlackLevel(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetBlueVideoBlackLevel(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetColorTemperature(uint aInstanceID, out uint aCurrentColorTemperature)
        {
			fixed (uint* currentColorTemperature = &aCurrentColorTemperature)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetColorTemperature(iHandle, aInstanceID, currentColorTemperature);
			}
        }

        public unsafe void BeginGetColorTemperature(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetColorTemperature(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetColorTemperature(uint aAsyncHandle, out uint aCurrentColorTemperature)
        {
			fixed (uint* currentColorTemperature = &aCurrentColorTemperature)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetColorTemperature(iHandle, aAsyncHandle, currentColorTemperature))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetColorTemperature(iHandle, aInstanceID, aDesiredColorTemperature);
			}
        }

        public unsafe void BeginSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetColorTemperature(iHandle, aInstanceID, aDesiredColorTemperature, iActionComplete, ptr);
        }

        public unsafe void EndSetColorTemperature(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetColorTemperature(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetHorizontalKeystone(uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
			fixed (int* currentHorizontalKeystone = &aCurrentHorizontalKeystone)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetHorizontalKeystone(iHandle, aInstanceID, currentHorizontalKeystone);
			}
        }

        public unsafe void BeginGetHorizontalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetHorizontalKeystone(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetHorizontalKeystone(uint aAsyncHandle, out int aCurrentHorizontalKeystone)
        {
			fixed (int* currentHorizontalKeystone = &aCurrentHorizontalKeystone)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetHorizontalKeystone(iHandle, aAsyncHandle, currentHorizontalKeystone))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetHorizontalKeystone(iHandle, aInstanceID, aDesiredHorizontalKeystone);
			}
        }

        public unsafe void BeginSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetHorizontalKeystone(iHandle, aInstanceID, aDesiredHorizontalKeystone, iActionComplete, ptr);
        }

        public unsafe void EndSetHorizontalKeystone(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetHorizontalKeystone(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetVerticalKeystone(uint aInstanceID, out int aCurrentVerticalKeystone)
        {
			fixed (int* currentVerticalKeystone = &aCurrentVerticalKeystone)
			{
				CpProxyUpnpOrgRenderingControl1SyncGetVerticalKeystone(iHandle, aInstanceID, currentVerticalKeystone);
			}
        }

        public unsafe void BeginGetVerticalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetVerticalKeystone(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetVerticalKeystone(uint aAsyncHandle, out int aCurrentVerticalKeystone)
        {
			fixed (int* currentVerticalKeystone = &aCurrentVerticalKeystone)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetVerticalKeystone(iHandle, aAsyncHandle, currentVerticalKeystone))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone)
        {
			{
				CpProxyUpnpOrgRenderingControl1SyncSetVerticalKeystone(iHandle, aInstanceID, aDesiredVerticalKeystone);
			}
        }

        public unsafe void BeginSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetVerticalKeystone(iHandle, aInstanceID, aDesiredVerticalKeystone, iActionComplete, ptr);
        }

        public unsafe void EndSetVerticalKeystone(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetVerticalKeystone(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgRenderingControl1SyncGetMute(iHandle, aInstanceID, channel, &currentMute);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
			aCurrentMute = (currentMute != 0);
        }

        public unsafe void BeginGetMute(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetMute(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetMute(uint aAsyncHandle, out bool aCurrentMute)
        {
			uint currentMute;
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetMute(iHandle, aAsyncHandle, &currentMute))
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
				CpProxyUpnpOrgRenderingControl1SyncSetMute(iHandle, aInstanceID, channel, desiredMute);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetMute(uint aInstanceID, string aChannel, bool aDesiredMute, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredMute = (aDesiredMute? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetMute(iHandle, aInstanceID, channel, desiredMute, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetMute(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetMute(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgRenderingControl1SyncGetVolume(iHandle, aInstanceID, channel, currentVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolume(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetVolume(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolume(uint aAsyncHandle, out uint aCurrentVolume)
        {
			fixed (uint* currentVolume = &aCurrentVolume)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetVolume(iHandle, aAsyncHandle, currentVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolume(uint aInstanceID, string aChannel, uint aDesiredVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			{
				CpProxyUpnpOrgRenderingControl1SyncSetVolume(iHandle, aInstanceID, channel, aDesiredVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetVolume(uint aInstanceID, string aChannel, uint aDesiredVolume, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetVolume(iHandle, aInstanceID, channel, aDesiredVolume, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetVolume(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetVolume(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgRenderingControl1SyncGetVolumeDB(iHandle, aInstanceID, channel, currentVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolumeDB(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetVolumeDB(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolumeDB(uint aAsyncHandle, out int aCurrentVolume)
        {
			fixed (int* currentVolume = &aCurrentVolume)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetVolumeDB(iHandle, aAsyncHandle, currentVolume))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetVolumeDB(uint aInstanceID, string aChannel, int aDesiredVolume)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			{
				CpProxyUpnpOrgRenderingControl1SyncSetVolumeDB(iHandle, aInstanceID, channel, aDesiredVolume);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetVolumeDB(uint aInstanceID, string aChannel, int aDesiredVolume, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetVolumeDB(iHandle, aInstanceID, channel, aDesiredVolume, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetVolumeDB(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetVolumeDB(iHandle, aAsyncHandle))
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
				CpProxyUpnpOrgRenderingControl1SyncGetVolumeDBRange(iHandle, aInstanceID, channel, minValue, maxValue);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginGetVolumeDBRange(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetVolumeDBRange(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetVolumeDBRange(uint aAsyncHandle, out int aMinValue, out int aMaxValue)
        {
			fixed (int* minValue = &aMinValue)
			fixed (int* maxValue = &aMaxValue)
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetVolumeDBRange(iHandle, aAsyncHandle, minValue, maxValue))
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
				CpProxyUpnpOrgRenderingControl1SyncGetLoudness(iHandle, aInstanceID, channel, &currentLoudness);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
			aCurrentLoudness = (currentLoudness != 0);
        }

        public unsafe void BeginGetLoudness(uint aInstanceID, string aChannel, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginGetLoudness(iHandle, aInstanceID, channel, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndGetLoudness(uint aAsyncHandle, out bool aCurrentLoudness)
        {
			uint currentLoudness;
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndGetLoudness(iHandle, aAsyncHandle, &currentLoudness))
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
				CpProxyUpnpOrgRenderingControl1SyncSetLoudness(iHandle, aInstanceID, channel, desiredLoudness);
			}
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void BeginSetLoudness(uint aInstanceID, string aChannel, bool aDesiredLoudness, CallbackAsyncComplete aCallback)
        {
			char* channel = (char*)Marshal.StringToHGlobalAnsi(aChannel);
			uint desiredLoudness = (aDesiredLoudness? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgRenderingControl1BeginSetLoudness(iHandle, aInstanceID, channel, desiredLoudness, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)channel);
        }

        public unsafe void EndSetLoudness(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgRenderingControl1EndSetLoudness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgRenderingControl1SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgRenderingControl1 self = (CpProxyUpnpOrgRenderingControl1)gch.Target;
            self.iLastChangeChanged();
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgRenderingControl1PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgRenderingControl1()
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
            CpProxyUpnpOrgRenderingControl1Destroy(handle);
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

