using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgRenderingControl1 : IDisposable
    {
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern uint DvServiceUpnpOrgRenderingControl1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern unsafe int DvServiceUpnpOrgRenderingControl1SetPropertyLastChange(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern unsafe void DvServiceUpnpOrgRenderingControl1GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionListPresets(uint aHandle, CallbackListPresets aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSelectPreset(uint aHandle, CallbackSelectPreset aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetBrightness(uint aHandle, CallbackGetBrightness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetBrightness(uint aHandle, CallbackSetBrightness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetContrast(uint aHandle, CallbackGetContrast aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetContrast(uint aHandle, CallbackSetContrast aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetSharpness(uint aHandle, CallbackGetSharpness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetSharpness(uint aHandle, CallbackSetSharpness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoGain(uint aHandle, CallbackGetRedVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoGain(uint aHandle, CallbackSetRedVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(uint aHandle, CallbackGetGreenVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(uint aHandle, CallbackSetGreenVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(uint aHandle, CallbackGetBlueVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(uint aHandle, CallbackSetBlueVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(uint aHandle, CallbackGetRedVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(uint aHandle, CallbackSetRedVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(uint aHandle, CallbackGetGreenVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(uint aHandle, CallbackSetGreenVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(uint aHandle, CallbackGetBlueVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(uint aHandle, CallbackSetBlueVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetColorTemperature(uint aHandle, CallbackGetColorTemperature aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetColorTemperature(uint aHandle, CallbackSetColorTemperature aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(uint aHandle, CallbackGetHorizontalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(uint aHandle, CallbackSetHorizontalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(uint aHandle, CallbackGetVerticalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(uint aHandle, CallbackSetVerticalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetMute(uint aHandle, CallbackGetMute aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetMute(uint aHandle, CallbackSetMute aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetVolume(uint aHandle, CallbackGetVolume aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetVolume(uint aHandle, CallbackSetVolume aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDB(uint aHandle, CallbackGetVolumeDB aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetVolumeDB(uint aHandle, CallbackSetVolumeDB aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(uint aHandle, CallbackGetVolumeDBRange aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionGetLoudness(uint aHandle, CallbackGetLoudness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl1")]
        static extern void DvServiceUpnpOrgRenderingControl1EnableActionSetLoudness(uint aHandle, CallbackSetLoudness aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackListPresets(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentPresetNameList);
        private unsafe delegate int CallbackSelectPreset(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aPresetName);
        private unsafe delegate int CallbackGetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBrightness);
        private unsafe delegate int CallbackSetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBrightness);
        private unsafe delegate int CallbackGetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentContrast);
        private unsafe delegate int CallbackSetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredContrast);
        private unsafe delegate int CallbackGetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentSharpness);
        private unsafe delegate int CallbackSetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredSharpness);
        private unsafe delegate int CallbackGetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoGain);
        private unsafe delegate int CallbackSetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain);
        private unsafe delegate int CallbackGetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoGain);
        private unsafe delegate int CallbackSetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain);
        private unsafe delegate int CallbackGetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoGain);
        private unsafe delegate int CallbackSetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain);
        private unsafe delegate int CallbackGetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoBlackLevel);
        private unsafe delegate int CallbackSetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel);
        private unsafe delegate int CallbackGetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel);
        private unsafe delegate int CallbackSetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel);
        private unsafe delegate int CallbackGetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel);
        private unsafe delegate int CallbackSetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel);
        private unsafe delegate int CallbackGetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentColorTemperature);
        private unsafe delegate int CallbackSetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredColorTemperature);
        private unsafe delegate int CallbackGetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentHorizontalKeystone);
        private unsafe delegate int CallbackSetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone);
        private unsafe delegate int CallbackGetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentVerticalKeystone);
        private unsafe delegate int CallbackSetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone);
        private unsafe delegate int CallbackGetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentMute);
        private unsafe delegate int CallbackSetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredMute);
        private unsafe delegate int CallbackGetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint* aCurrentVolume);
        private unsafe delegate int CallbackSetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint aDesiredVolume);
        private unsafe delegate int CallbackGetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentVolume);
        private unsafe delegate int CallbackSetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredVolume);
        private unsafe delegate int CallbackGetVolumeDBRange(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue);
        private unsafe delegate int CallbackGetLoudness(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentLoudness);
        private unsafe delegate int CallbackSetLoudness(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredLoudness);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackListPresets iCallbackListPresets;
        private CallbackSelectPreset iCallbackSelectPreset;
        private CallbackGetBrightness iCallbackGetBrightness;
        private CallbackSetBrightness iCallbackSetBrightness;
        private CallbackGetContrast iCallbackGetContrast;
        private CallbackSetContrast iCallbackSetContrast;
        private CallbackGetSharpness iCallbackGetSharpness;
        private CallbackSetSharpness iCallbackSetSharpness;
        private CallbackGetRedVideoGain iCallbackGetRedVideoGain;
        private CallbackSetRedVideoGain iCallbackSetRedVideoGain;
        private CallbackGetGreenVideoGain iCallbackGetGreenVideoGain;
        private CallbackSetGreenVideoGain iCallbackSetGreenVideoGain;
        private CallbackGetBlueVideoGain iCallbackGetBlueVideoGain;
        private CallbackSetBlueVideoGain iCallbackSetBlueVideoGain;
        private CallbackGetRedVideoBlackLevel iCallbackGetRedVideoBlackLevel;
        private CallbackSetRedVideoBlackLevel iCallbackSetRedVideoBlackLevel;
        private CallbackGetGreenVideoBlackLevel iCallbackGetGreenVideoBlackLevel;
        private CallbackSetGreenVideoBlackLevel iCallbackSetGreenVideoBlackLevel;
        private CallbackGetBlueVideoBlackLevel iCallbackGetBlueVideoBlackLevel;
        private CallbackSetBlueVideoBlackLevel iCallbackSetBlueVideoBlackLevel;
        private CallbackGetColorTemperature iCallbackGetColorTemperature;
        private CallbackSetColorTemperature iCallbackSetColorTemperature;
        private CallbackGetHorizontalKeystone iCallbackGetHorizontalKeystone;
        private CallbackSetHorizontalKeystone iCallbackSetHorizontalKeystone;
        private CallbackGetVerticalKeystone iCallbackGetVerticalKeystone;
        private CallbackSetVerticalKeystone iCallbackSetVerticalKeystone;
        private CallbackGetMute iCallbackGetMute;
        private CallbackSetMute iCallbackSetMute;
        private CallbackGetVolume iCallbackGetVolume;
        private CallbackSetVolume iCallbackSetVolume;
        private CallbackGetVolumeDB iCallbackGetVolumeDB;
        private CallbackSetVolumeDB iCallbackSetVolumeDB;
        private CallbackGetVolumeDBRange iCallbackGetVolumeDBRange;
        private CallbackGetLoudness iCallbackGetLoudness;
        private CallbackSetLoudness iCallbackSetLoudness;

        public DvServiceUpnpOrgRenderingControl1(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgRenderingControl1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyLastChange(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgRenderingControl1SetPropertyLastChange(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgRenderingControl1GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionListPresets()
        {
            iCallbackListPresets = new CallbackListPresets(DoListPresets);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionListPresets(iHandle, iCallbackListPresets, ptr);
        }

        protected unsafe void EnableActionSelectPreset()
        {
            iCallbackSelectPreset = new CallbackSelectPreset(DoSelectPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSelectPreset(iHandle, iCallbackSelectPreset, ptr);
        }

        protected unsafe void EnableActionGetBrightness()
        {
            iCallbackGetBrightness = new CallbackGetBrightness(DoGetBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetBrightness(iHandle, iCallbackGetBrightness, ptr);
        }

        protected unsafe void EnableActionSetBrightness()
        {
            iCallbackSetBrightness = new CallbackSetBrightness(DoSetBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetBrightness(iHandle, iCallbackSetBrightness, ptr);
        }

        protected unsafe void EnableActionGetContrast()
        {
            iCallbackGetContrast = new CallbackGetContrast(DoGetContrast);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetContrast(iHandle, iCallbackGetContrast, ptr);
        }

        protected unsafe void EnableActionSetContrast()
        {
            iCallbackSetContrast = new CallbackSetContrast(DoSetContrast);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetContrast(iHandle, iCallbackSetContrast, ptr);
        }

        protected unsafe void EnableActionGetSharpness()
        {
            iCallbackGetSharpness = new CallbackGetSharpness(DoGetSharpness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetSharpness(iHandle, iCallbackGetSharpness, ptr);
        }

        protected unsafe void EnableActionSetSharpness()
        {
            iCallbackSetSharpness = new CallbackSetSharpness(DoSetSharpness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetSharpness(iHandle, iCallbackSetSharpness, ptr);
        }

        protected unsafe void EnableActionGetRedVideoGain()
        {
            iCallbackGetRedVideoGain = new CallbackGetRedVideoGain(DoGetRedVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoGain(iHandle, iCallbackGetRedVideoGain, ptr);
        }

        protected unsafe void EnableActionSetRedVideoGain()
        {
            iCallbackSetRedVideoGain = new CallbackSetRedVideoGain(DoSetRedVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoGain(iHandle, iCallbackSetRedVideoGain, ptr);
        }

        protected unsafe void EnableActionGetGreenVideoGain()
        {
            iCallbackGetGreenVideoGain = new CallbackGetGreenVideoGain(DoGetGreenVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(iHandle, iCallbackGetGreenVideoGain, ptr);
        }

        protected unsafe void EnableActionSetGreenVideoGain()
        {
            iCallbackSetGreenVideoGain = new CallbackSetGreenVideoGain(DoSetGreenVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(iHandle, iCallbackSetGreenVideoGain, ptr);
        }

        protected unsafe void EnableActionGetBlueVideoGain()
        {
            iCallbackGetBlueVideoGain = new CallbackGetBlueVideoGain(DoGetBlueVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(iHandle, iCallbackGetBlueVideoGain, ptr);
        }

        protected unsafe void EnableActionSetBlueVideoGain()
        {
            iCallbackSetBlueVideoGain = new CallbackSetBlueVideoGain(DoSetBlueVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(iHandle, iCallbackSetBlueVideoGain, ptr);
        }

        protected unsafe void EnableActionGetRedVideoBlackLevel()
        {
            iCallbackGetRedVideoBlackLevel = new CallbackGetRedVideoBlackLevel(DoGetRedVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(iHandle, iCallbackGetRedVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionSetRedVideoBlackLevel()
        {
            iCallbackSetRedVideoBlackLevel = new CallbackSetRedVideoBlackLevel(DoSetRedVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(iHandle, iCallbackSetRedVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionGetGreenVideoBlackLevel()
        {
            iCallbackGetGreenVideoBlackLevel = new CallbackGetGreenVideoBlackLevel(DoGetGreenVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(iHandle, iCallbackGetGreenVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionSetGreenVideoBlackLevel()
        {
            iCallbackSetGreenVideoBlackLevel = new CallbackSetGreenVideoBlackLevel(DoSetGreenVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(iHandle, iCallbackSetGreenVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionGetBlueVideoBlackLevel()
        {
            iCallbackGetBlueVideoBlackLevel = new CallbackGetBlueVideoBlackLevel(DoGetBlueVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(iHandle, iCallbackGetBlueVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionSetBlueVideoBlackLevel()
        {
            iCallbackSetBlueVideoBlackLevel = new CallbackSetBlueVideoBlackLevel(DoSetBlueVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(iHandle, iCallbackSetBlueVideoBlackLevel, ptr);
        }

        protected unsafe void EnableActionGetColorTemperature()
        {
            iCallbackGetColorTemperature = new CallbackGetColorTemperature(DoGetColorTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetColorTemperature(iHandle, iCallbackGetColorTemperature, ptr);
        }

        protected unsafe void EnableActionSetColorTemperature()
        {
            iCallbackSetColorTemperature = new CallbackSetColorTemperature(DoSetColorTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetColorTemperature(iHandle, iCallbackSetColorTemperature, ptr);
        }

        protected unsafe void EnableActionGetHorizontalKeystone()
        {
            iCallbackGetHorizontalKeystone = new CallbackGetHorizontalKeystone(DoGetHorizontalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(iHandle, iCallbackGetHorizontalKeystone, ptr);
        }

        protected unsafe void EnableActionSetHorizontalKeystone()
        {
            iCallbackSetHorizontalKeystone = new CallbackSetHorizontalKeystone(DoSetHorizontalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(iHandle, iCallbackSetHorizontalKeystone, ptr);
        }

        protected unsafe void EnableActionGetVerticalKeystone()
        {
            iCallbackGetVerticalKeystone = new CallbackGetVerticalKeystone(DoGetVerticalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(iHandle, iCallbackGetVerticalKeystone, ptr);
        }

        protected unsafe void EnableActionSetVerticalKeystone()
        {
            iCallbackSetVerticalKeystone = new CallbackSetVerticalKeystone(DoSetVerticalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(iHandle, iCallbackSetVerticalKeystone, ptr);
        }

        protected unsafe void EnableActionGetMute()
        {
            iCallbackGetMute = new CallbackGetMute(DoGetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetMute(iHandle, iCallbackGetMute, ptr);
        }

        protected unsafe void EnableActionSetMute()
        {
            iCallbackSetMute = new CallbackSetMute(DoSetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetMute(iHandle, iCallbackSetMute, ptr);
        }

        protected unsafe void EnableActionGetVolume()
        {
            iCallbackGetVolume = new CallbackGetVolume(DoGetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetVolume(iHandle, iCallbackGetVolume, ptr);
        }

        protected unsafe void EnableActionSetVolume()
        {
            iCallbackSetVolume = new CallbackSetVolume(DoSetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetVolume(iHandle, iCallbackSetVolume, ptr);
        }

        protected unsafe void EnableActionGetVolumeDB()
        {
            iCallbackGetVolumeDB = new CallbackGetVolumeDB(DoGetVolumeDB);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDB(iHandle, iCallbackGetVolumeDB, ptr);
        }

        protected unsafe void EnableActionSetVolumeDB()
        {
            iCallbackSetVolumeDB = new CallbackSetVolumeDB(DoSetVolumeDB);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetVolumeDB(iHandle, iCallbackSetVolumeDB, ptr);
        }

        protected unsafe void EnableActionGetVolumeDBRange()
        {
            iCallbackGetVolumeDBRange = new CallbackGetVolumeDBRange(DoGetVolumeDBRange);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(iHandle, iCallbackGetVolumeDBRange, ptr);
        }

        protected unsafe void EnableActionGetLoudness()
        {
            iCallbackGetLoudness = new CallbackGetLoudness(DoGetLoudness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionGetLoudness(iHandle, iCallbackGetLoudness, ptr);
        }

        protected unsafe void EnableActionSetLoudness()
        {
            iCallbackSetLoudness = new CallbackSetLoudness(DoSetLoudness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgRenderingControl1EnableActionSetLoudness(iHandle, iCallbackSetLoudness, ptr);
        }

        protected virtual void ListPresets(uint aVersion, uint aInstanceID, out string aCurrentPresetNameList)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SelectPreset(uint aVersion, uint aInstanceID, string aPresetName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetBrightness(uint aVersion, uint aInstanceID, out uint aCurrentBrightness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBrightness(uint aVersion, uint aInstanceID, uint aDesiredBrightness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetContrast(uint aVersion, uint aInstanceID, out uint aCurrentContrast)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetContrast(uint aVersion, uint aInstanceID, uint aDesiredContrast)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetSharpness(uint aVersion, uint aInstanceID, out uint aCurrentSharpness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetSharpness(uint aVersion, uint aInstanceID, uint aDesiredSharpness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRedVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRedVideoGain(uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetGreenVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetGreenVideoGain(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetBlueVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBlueVideoGain(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRedVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRedVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetColorTemperature(uint aVersion, uint aInstanceID, out uint aCurrentColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetColorTemperature(uint aVersion, uint aInstanceID, uint aDesiredColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetHorizontalKeystone(uint aVersion, uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetHorizontalKeystone(uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetVerticalKeystone(uint aVersion, uint aInstanceID, out int aCurrentVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVerticalKeystone(uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetMute(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentMute)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetMute(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredMute)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetVolume(uint aVersion, uint aInstanceID, string aChannel, out uint aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVolume(uint aVersion, uint aInstanceID, string aChannel, uint aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, out int aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, int aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetVolumeDBRange(uint aVersion, uint aInstanceID, string aChannel, out int aMinValue, out int aMaxValue)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetLoudness(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentLoudness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetLoudness(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredLoudness)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoListPresets(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentPresetNameList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string currentPresetNameList;
            self.ListPresets(aVersion, aInstanceID, out currentPresetNameList);
            *aCurrentPresetNameList = (char*)Marshal.StringToHGlobalAnsi(currentPresetNameList).ToPointer();
            return 0;
        }

        private static unsafe int DoSelectPreset(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aPresetName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string presetName = Marshal.PtrToStringAnsi((IntPtr)aPresetName);
            self.SelectPreset(aVersion, aInstanceID, presetName);
            return 0;
        }

        private static unsafe int DoGetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentBrightness;
            self.GetBrightness(aVersion, aInstanceID, out currentBrightness);
            *aCurrentBrightness = currentBrightness;
            return 0;
        }

        private static unsafe int DoSetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetBrightness(aVersion, aInstanceID, aDesiredBrightness);
            return 0;
        }

        private static unsafe int DoGetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentContrast)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentContrast;
            self.GetContrast(aVersion, aInstanceID, out currentContrast);
            *aCurrentContrast = currentContrast;
            return 0;
        }

        private static unsafe int DoSetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredContrast)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetContrast(aVersion, aInstanceID, aDesiredContrast);
            return 0;
        }

        private static unsafe int DoGetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentSharpness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentSharpness;
            self.GetSharpness(aVersion, aInstanceID, out currentSharpness);
            *aCurrentSharpness = currentSharpness;
            return 0;
        }

        private static unsafe int DoSetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredSharpness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetSharpness(aVersion, aInstanceID, aDesiredSharpness);
            return 0;
        }

        private static unsafe int DoGetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentRedVideoGain;
            self.GetRedVideoGain(aVersion, aInstanceID, out currentRedVideoGain);
            *aCurrentRedVideoGain = currentRedVideoGain;
            return 0;
        }

        private static unsafe int DoSetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetRedVideoGain(aVersion, aInstanceID, aDesiredRedVideoGain);
            return 0;
        }

        private static unsafe int DoGetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentGreenVideoGain;
            self.GetGreenVideoGain(aVersion, aInstanceID, out currentGreenVideoGain);
            *aCurrentGreenVideoGain = currentGreenVideoGain;
            return 0;
        }

        private static unsafe int DoSetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetGreenVideoGain(aVersion, aInstanceID, aDesiredGreenVideoGain);
            return 0;
        }

        private static unsafe int DoGetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentBlueVideoGain;
            self.GetBlueVideoGain(aVersion, aInstanceID, out currentBlueVideoGain);
            *aCurrentBlueVideoGain = currentBlueVideoGain;
            return 0;
        }

        private static unsafe int DoSetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetBlueVideoGain(aVersion, aInstanceID, aDesiredBlueVideoGain);
            return 0;
        }

        private static unsafe int DoGetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentRedVideoBlackLevel;
            self.GetRedVideoBlackLevel(aVersion, aInstanceID, out currentRedVideoBlackLevel);
            *aCurrentRedVideoBlackLevel = currentRedVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetRedVideoBlackLevel(aVersion, aInstanceID, aDesiredRedVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentGreenVideoBlackLevel;
            self.GetGreenVideoBlackLevel(aVersion, aInstanceID, out currentGreenVideoBlackLevel);
            *aCurrentGreenVideoBlackLevel = currentGreenVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetGreenVideoBlackLevel(aVersion, aInstanceID, aDesiredGreenVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentBlueVideoBlackLevel;
            self.GetBlueVideoBlackLevel(aVersion, aInstanceID, out currentBlueVideoBlackLevel);
            *aCurrentBlueVideoBlackLevel = currentBlueVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetBlueVideoBlackLevel(aVersion, aInstanceID, aDesiredBlueVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentColorTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            uint currentColorTemperature;
            self.GetColorTemperature(aVersion, aInstanceID, out currentColorTemperature);
            *aCurrentColorTemperature = currentColorTemperature;
            return 0;
        }

        private static unsafe int DoSetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredColorTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetColorTemperature(aVersion, aInstanceID, aDesiredColorTemperature);
            return 0;
        }

        private static unsafe int DoGetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentHorizontalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            int currentHorizontalKeystone;
            self.GetHorizontalKeystone(aVersion, aInstanceID, out currentHorizontalKeystone);
            *aCurrentHorizontalKeystone = currentHorizontalKeystone;
            return 0;
        }

        private static unsafe int DoSetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetHorizontalKeystone(aVersion, aInstanceID, aDesiredHorizontalKeystone);
            return 0;
        }

        private static unsafe int DoGetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentVerticalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            int currentVerticalKeystone;
            self.GetVerticalKeystone(aVersion, aInstanceID, out currentVerticalKeystone);
            *aCurrentVerticalKeystone = currentVerticalKeystone;
            return 0;
        }

        private static unsafe int DoSetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            self.SetVerticalKeystone(aVersion, aInstanceID, aDesiredVerticalKeystone);
            return 0;
        }

        private static unsafe int DoGetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool currentMute;
            self.GetMute(aVersion, aInstanceID, channel, out currentMute);
            *aCurrentMute = (currentMute ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool desiredMute = (aDesiredMute != 0);
            self.SetMute(aVersion, aInstanceID, channel, desiredMute);
            return 0;
        }

        private static unsafe int DoGetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint* aCurrentVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            uint currentVolume;
            self.GetVolume(aVersion, aInstanceID, channel, out currentVolume);
            *aCurrentVolume = currentVolume;
            return 0;
        }

        private static unsafe int DoSetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint aDesiredVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            self.SetVolume(aVersion, aInstanceID, channel, aDesiredVolume);
            return 0;
        }

        private static unsafe int DoGetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            int currentVolume;
            self.GetVolumeDB(aVersion, aInstanceID, channel, out currentVolume);
            *aCurrentVolume = currentVolume;
            return 0;
        }

        private static unsafe int DoSetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            self.SetVolumeDB(aVersion, aInstanceID, channel, aDesiredVolume);
            return 0;
        }

        private static unsafe int DoGetVolumeDBRange(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            int minValue;
            int maxValue;
            self.GetVolumeDBRange(aVersion, aInstanceID, channel, out minValue, out maxValue);
            *aMinValue = minValue;
            *aMaxValue = maxValue;
            return 0;
        }

        private static unsafe int DoGetLoudness(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentLoudness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool currentLoudness;
            self.GetLoudness(aVersion, aInstanceID, channel, out currentLoudness);
            *aCurrentLoudness = (currentLoudness ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetLoudness(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredLoudness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgRenderingControl1 self = (DvServiceUpnpOrgRenderingControl1)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool desiredLoudness = (aDesiredLoudness != 0);
            self.SetLoudness(aVersion, aInstanceID, channel, desiredLoudness);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgRenderingControl1()
        {
            DoDispose();
        }

        private void DoDispose()
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
            DvServiceUpnpOrgRenderingControl1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

