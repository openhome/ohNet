using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgRenderingControl2 : IDisposable
    {

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLastChange(string aValue);

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyLastChange(out string aValue);
        
    }
    /// <summary>
    /// Provider for the upnp.org:RenderingControl:2 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgRenderingControl2 : DvProvider, IDisposable, IDvProviderUpnpOrgRenderingControl2
    {
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern uint DvProviderUpnpOrgRenderingControl2Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2Destroy(uint aHandle);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern unsafe int DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern unsafe void DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionListPresets(uint aHandle, CallbackListPresets aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(uint aHandle, CallbackSelectPreset aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(uint aHandle, CallbackGetBrightness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(uint aHandle, CallbackSetBrightness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(uint aHandle, CallbackGetContrast aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(uint aHandle, CallbackSetContrast aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(uint aHandle, CallbackGetSharpness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(uint aHandle, CallbackSetSharpness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(uint aHandle, CallbackGetRedVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(uint aHandle, CallbackSetRedVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(uint aHandle, CallbackGetGreenVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(uint aHandle, CallbackSetGreenVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(uint aHandle, CallbackGetBlueVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(uint aHandle, CallbackSetBlueVideoGain aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(uint aHandle, CallbackGetRedVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(uint aHandle, CallbackSetRedVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(uint aHandle, CallbackGetGreenVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(uint aHandle, CallbackSetGreenVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(uint aHandle, CallbackGetBlueVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(uint aHandle, CallbackSetBlueVideoBlackLevel aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(uint aHandle, CallbackGetColorTemperature aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(uint aHandle, CallbackSetColorTemperature aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(uint aHandle, CallbackGetHorizontalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(uint aHandle, CallbackSetHorizontalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(uint aHandle, CallbackGetVerticalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(uint aHandle, CallbackSetVerticalKeystone aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetMute(uint aHandle, CallbackGetMute aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetMute(uint aHandle, CallbackSetMute aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(uint aHandle, CallbackGetVolume aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(uint aHandle, CallbackSetVolume aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(uint aHandle, CallbackGetVolumeDB aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(uint aHandle, CallbackSetVolumeDB aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(uint aHandle, CallbackGetVolumeDBRange aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(uint aHandle, CallbackGetLoudness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(uint aHandle, CallbackSetLoudness aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(uint aHandle, CallbackGetStateVariables aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgRenderingControl2")]
        static extern void DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(uint aHandle, CallbackSetStateVariables aCallback, IntPtr aPtr);
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
        private unsafe delegate int CallbackGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        private unsafe delegate int CallbackSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);

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
        private CallbackGetStateVariables iCallbackGetStateVariables;
        private CallbackSetStateVariables iCallbackSetStateVariables;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgRenderingControl2(DvDevice aDevice)
        {
            iHandle = DvProviderUpnpOrgRenderingControl2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyLastChange(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action ListPresets is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoListPresets must be overridden if this is called.</remarks>
        protected unsafe void EnableActionListPresets()
        {
            iCallbackListPresets = new CallbackListPresets(DoListPresets);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionListPresets(iHandle, iCallbackListPresets, ptr);
        }

        /// <summary>
        /// Signal that the action SelectPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSelectPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSelectPreset()
        {
            iCallbackSelectPreset = new CallbackSelectPreset(DoSelectPreset);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(iHandle, iCallbackSelectPreset, ptr);
        }

        /// <summary>
        /// Signal that the action GetBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBrightness()
        {
            iCallbackGetBrightness = new CallbackGetBrightness(DoGetBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(iHandle, iCallbackGetBrightness, ptr);
        }

        /// <summary>
        /// Signal that the action SetBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBrightness()
        {
            iCallbackSetBrightness = new CallbackSetBrightness(DoSetBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(iHandle, iCallbackSetBrightness, ptr);
        }

        /// <summary>
        /// Signal that the action GetContrast is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetContrast must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetContrast()
        {
            iCallbackGetContrast = new CallbackGetContrast(DoGetContrast);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(iHandle, iCallbackGetContrast, ptr);
        }

        /// <summary>
        /// Signal that the action SetContrast is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetContrast must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetContrast()
        {
            iCallbackSetContrast = new CallbackSetContrast(DoSetContrast);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(iHandle, iCallbackSetContrast, ptr);
        }

        /// <summary>
        /// Signal that the action GetSharpness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSharpness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSharpness()
        {
            iCallbackGetSharpness = new CallbackGetSharpness(DoGetSharpness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(iHandle, iCallbackGetSharpness, ptr);
        }

        /// <summary>
        /// Signal that the action SetSharpness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSharpness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSharpness()
        {
            iCallbackSetSharpness = new CallbackSetSharpness(DoSetSharpness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(iHandle, iCallbackSetSharpness, ptr);
        }

        /// <summary>
        /// Signal that the action GetRedVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRedVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRedVideoGain()
        {
            iCallbackGetRedVideoGain = new CallbackGetRedVideoGain(DoGetRedVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(iHandle, iCallbackGetRedVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action SetRedVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRedVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRedVideoGain()
        {
            iCallbackSetRedVideoGain = new CallbackSetRedVideoGain(DoSetRedVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(iHandle, iCallbackSetRedVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action GetGreenVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetGreenVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetGreenVideoGain()
        {
            iCallbackGetGreenVideoGain = new CallbackGetGreenVideoGain(DoGetGreenVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(iHandle, iCallbackGetGreenVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action SetGreenVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetGreenVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetGreenVideoGain()
        {
            iCallbackSetGreenVideoGain = new CallbackSetGreenVideoGain(DoSetGreenVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(iHandle, iCallbackSetGreenVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action GetBlueVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBlueVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBlueVideoGain()
        {
            iCallbackGetBlueVideoGain = new CallbackGetBlueVideoGain(DoGetBlueVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(iHandle, iCallbackGetBlueVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action SetBlueVideoGain is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBlueVideoGain must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBlueVideoGain()
        {
            iCallbackSetBlueVideoGain = new CallbackSetBlueVideoGain(DoSetBlueVideoGain);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(iHandle, iCallbackSetBlueVideoGain, ptr);
        }

        /// <summary>
        /// Signal that the action GetRedVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRedVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRedVideoBlackLevel()
        {
            iCallbackGetRedVideoBlackLevel = new CallbackGetRedVideoBlackLevel(DoGetRedVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(iHandle, iCallbackGetRedVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action SetRedVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRedVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRedVideoBlackLevel()
        {
            iCallbackSetRedVideoBlackLevel = new CallbackSetRedVideoBlackLevel(DoSetRedVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(iHandle, iCallbackSetRedVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action GetGreenVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetGreenVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetGreenVideoBlackLevel()
        {
            iCallbackGetGreenVideoBlackLevel = new CallbackGetGreenVideoBlackLevel(DoGetGreenVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(iHandle, iCallbackGetGreenVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action SetGreenVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetGreenVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetGreenVideoBlackLevel()
        {
            iCallbackSetGreenVideoBlackLevel = new CallbackSetGreenVideoBlackLevel(DoSetGreenVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(iHandle, iCallbackSetGreenVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action GetBlueVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBlueVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBlueVideoBlackLevel()
        {
            iCallbackGetBlueVideoBlackLevel = new CallbackGetBlueVideoBlackLevel(DoGetBlueVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(iHandle, iCallbackGetBlueVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action SetBlueVideoBlackLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBlueVideoBlackLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBlueVideoBlackLevel()
        {
            iCallbackSetBlueVideoBlackLevel = new CallbackSetBlueVideoBlackLevel(DoSetBlueVideoBlackLevel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(iHandle, iCallbackSetBlueVideoBlackLevel, ptr);
        }

        /// <summary>
        /// Signal that the action GetColorTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetColorTemperature must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetColorTemperature()
        {
            iCallbackGetColorTemperature = new CallbackGetColorTemperature(DoGetColorTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(iHandle, iCallbackGetColorTemperature, ptr);
        }

        /// <summary>
        /// Signal that the action SetColorTemperature is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetColorTemperature must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetColorTemperature()
        {
            iCallbackSetColorTemperature = new CallbackSetColorTemperature(DoSetColorTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(iHandle, iCallbackSetColorTemperature, ptr);
        }

        /// <summary>
        /// Signal that the action GetHorizontalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetHorizontalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetHorizontalKeystone()
        {
            iCallbackGetHorizontalKeystone = new CallbackGetHorizontalKeystone(DoGetHorizontalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(iHandle, iCallbackGetHorizontalKeystone, ptr);
        }

        /// <summary>
        /// Signal that the action SetHorizontalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetHorizontalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetHorizontalKeystone()
        {
            iCallbackSetHorizontalKeystone = new CallbackSetHorizontalKeystone(DoSetHorizontalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(iHandle, iCallbackSetHorizontalKeystone, ptr);
        }

        /// <summary>
        /// Signal that the action GetVerticalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVerticalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVerticalKeystone()
        {
            iCallbackGetVerticalKeystone = new CallbackGetVerticalKeystone(DoGetVerticalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(iHandle, iCallbackGetVerticalKeystone, ptr);
        }

        /// <summary>
        /// Signal that the action SetVerticalKeystone is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVerticalKeystone must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVerticalKeystone()
        {
            iCallbackSetVerticalKeystone = new CallbackSetVerticalKeystone(DoSetVerticalKeystone);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(iHandle, iCallbackSetVerticalKeystone, ptr);
        }

        /// <summary>
        /// Signal that the action GetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetMute()
        {
            iCallbackGetMute = new CallbackGetMute(DoGetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetMute(iHandle, iCallbackGetMute, ptr);
        }

        /// <summary>
        /// Signal that the action SetMute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetMute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetMute()
        {
            iCallbackSetMute = new CallbackSetMute(DoSetMute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetMute(iHandle, iCallbackSetMute, ptr);
        }

        /// <summary>
        /// Signal that the action GetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolume()
        {
            iCallbackGetVolume = new CallbackGetVolume(DoGetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(iHandle, iCallbackGetVolume, ptr);
        }

        /// <summary>
        /// Signal that the action SetVolume is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolume must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolume()
        {
            iCallbackSetVolume = new CallbackSetVolume(DoSetVolume);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(iHandle, iCallbackSetVolume, ptr);
        }

        /// <summary>
        /// Signal that the action GetVolumeDB is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolumeDB must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolumeDB()
        {
            iCallbackGetVolumeDB = new CallbackGetVolumeDB(DoGetVolumeDB);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(iHandle, iCallbackGetVolumeDB, ptr);
        }

        /// <summary>
        /// Signal that the action SetVolumeDB is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetVolumeDB must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetVolumeDB()
        {
            iCallbackSetVolumeDB = new CallbackSetVolumeDB(DoSetVolumeDB);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(iHandle, iCallbackSetVolumeDB, ptr);
        }

        /// <summary>
        /// Signal that the action GetVolumeDBRange is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetVolumeDBRange must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetVolumeDBRange()
        {
            iCallbackGetVolumeDBRange = new CallbackGetVolumeDBRange(DoGetVolumeDBRange);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(iHandle, iCallbackGetVolumeDBRange, ptr);
        }

        /// <summary>
        /// Signal that the action GetLoudness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetLoudness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetLoudness()
        {
            iCallbackGetLoudness = new CallbackGetLoudness(DoGetLoudness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(iHandle, iCallbackGetLoudness, ptr);
        }

        /// <summary>
        /// Signal that the action SetLoudness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetLoudness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetLoudness()
        {
            iCallbackSetLoudness = new CallbackSetLoudness(DoSetLoudness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(iHandle, iCallbackSetLoudness, ptr);
        }

        /// <summary>
        /// Signal that the action GetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetStateVariables must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetStateVariables()
        {
            iCallbackGetStateVariables = new CallbackGetStateVariables(DoGetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(iHandle, iCallbackGetStateVariables, ptr);
        }

        /// <summary>
        /// Signal that the action SetStateVariables is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStateVariables must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStateVariables()
        {
            iCallbackSetStateVariables = new CallbackSetStateVariables(DoSetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(iHandle, iCallbackSetStateVariables, ptr);
        }

        /// <summary>
        /// ListPresets action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ListPresets action for the owning device.
        ///
        /// Must be implemented iff EnableActionListPresets was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentPresetNameList"></param>
        protected virtual void ListPresets(uint aVersion, uint aInstanceID, out string aCurrentPresetNameList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SelectPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SelectPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionSelectPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aPresetName"></param>
        protected virtual void SelectPreset(uint aVersion, uint aInstanceID, string aPresetName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBrightness"></param>
        protected virtual void GetBrightness(uint aVersion, uint aInstanceID, out uint aCurrentBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBrightness"></param>
        protected virtual void SetBrightness(uint aVersion, uint aInstanceID, uint aDesiredBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetContrast action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetContrast action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetContrast was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentContrast"></param>
        protected virtual void GetContrast(uint aVersion, uint aInstanceID, out uint aCurrentContrast)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetContrast action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetContrast action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetContrast was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredContrast"></param>
        protected virtual void SetContrast(uint aVersion, uint aInstanceID, uint aDesiredContrast)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetSharpness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSharpness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSharpness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentSharpness"></param>
        protected virtual void GetSharpness(uint aVersion, uint aInstanceID, out uint aCurrentSharpness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSharpness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSharpness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSharpness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredSharpness"></param>
        protected virtual void SetSharpness(uint aVersion, uint aInstanceID, uint aDesiredSharpness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRedVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRedVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRedVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoGain"></param>
        protected virtual void GetRedVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRedVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRedVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRedVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoGain"></param>
        protected virtual void SetRedVideoGain(uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetGreenVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetGreenVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetGreenVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoGain"></param>
        protected virtual void GetGreenVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetGreenVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetGreenVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetGreenVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoGain"></param>
        protected virtual void SetGreenVideoGain(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBlueVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBlueVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBlueVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoGain"></param>
        protected virtual void GetBlueVideoGain(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBlueVideoGain action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBlueVideoGain action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBlueVideoGain was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoGain"></param>
        protected virtual void SetBlueVideoGain(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRedVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRedVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRedVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoBlackLevel"></param>
        protected virtual void GetRedVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRedVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRedVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRedVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoBlackLevel"></param>
        protected virtual void SetRedVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetGreenVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetGreenVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetGreenVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoBlackLevel"></param>
        protected virtual void GetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetGreenVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetGreenVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetGreenVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoBlackLevel"></param>
        protected virtual void SetGreenVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBlueVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBlueVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBlueVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoBlackLevel"></param>
        protected virtual void GetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBlueVideoBlackLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBlueVideoBlackLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBlueVideoBlackLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoBlackLevel"></param>
        protected virtual void SetBlueVideoBlackLevel(uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetColorTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetColorTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetColorTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentColorTemperature"></param>
        protected virtual void GetColorTemperature(uint aVersion, uint aInstanceID, out uint aCurrentColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetColorTemperature action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetColorTemperature action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetColorTemperature was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredColorTemperature"></param>
        protected virtual void SetColorTemperature(uint aVersion, uint aInstanceID, uint aDesiredColorTemperature)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetHorizontalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetHorizontalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetHorizontalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentHorizontalKeystone"></param>
        protected virtual void GetHorizontalKeystone(uint aVersion, uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetHorizontalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetHorizontalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetHorizontalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredHorizontalKeystone"></param>
        protected virtual void SetHorizontalKeystone(uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVerticalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVerticalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVerticalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentVerticalKeystone"></param>
        protected virtual void GetVerticalKeystone(uint aVersion, uint aInstanceID, out int aCurrentVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVerticalKeystone action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVerticalKeystone action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVerticalKeystone was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredVerticalKeystone"></param>
        protected virtual void SetVerticalKeystone(uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMute action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentMute"></param>
        protected virtual void GetMute(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetMute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetMute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetMute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredMute"></param>
        protected virtual void SetMute(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredMute)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        protected virtual void GetVolume(uint aVersion, uint aInstanceID, string aChannel, out uint aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolume action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolume action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolume was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        protected virtual void SetVolume(uint aVersion, uint aInstanceID, string aChannel, uint aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolumeDB action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolumeDB action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolumeDB was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        protected virtual void GetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, out int aCurrentVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetVolumeDB action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetVolumeDB action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetVolumeDB was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        protected virtual void SetVolumeDB(uint aVersion, uint aInstanceID, string aChannel, int aDesiredVolume)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetVolumeDBRange action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetVolumeDBRange action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetVolumeDBRange was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aMinValue"></param>
        /// <param name="aMaxValue"></param>
        protected virtual void GetVolumeDBRange(uint aVersion, uint aInstanceID, string aChannel, out int aMinValue, out int aMaxValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLoudness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLoudness action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLoudness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentLoudness"></param>
        protected virtual void GetLoudness(uint aVersion, uint aInstanceID, string aChannel, out bool aCurrentLoudness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetLoudness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetLoudness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetLoudness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredLoudness"></param>
        protected virtual void SetLoudness(uint aVersion, uint aInstanceID, string aChannel, bool aDesiredLoudness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetStateVariables action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetStateVariables action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetStateVariables was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aStateVariableValuePairs"></param>
        protected virtual void GetStateVariables(uint aVersion, uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStateVariables action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStateVariables action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStateVariables was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aInstanceID"></param>
        /// <param name="aRenderingControlUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aStateVariableList"></param>
        protected virtual void SetStateVariables(uint aVersion, uint aInstanceID, string aRenderingControlUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoListPresets(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentPresetNameList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string currentPresetNameList;
            self.ListPresets(aVersion, aInstanceID, out currentPresetNameList);
            *aCurrentPresetNameList = (char*)Marshal.StringToHGlobalAnsi(currentPresetNameList).ToPointer();
            return 0;
        }

        private static unsafe int DoSelectPreset(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aPresetName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string presetName = Marshal.PtrToStringAnsi((IntPtr)aPresetName);
            self.SelectPreset(aVersion, aInstanceID, presetName);
            return 0;
        }

        private static unsafe int DoGetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentBrightness;
            self.GetBrightness(aVersion, aInstanceID, out currentBrightness);
            *aCurrentBrightness = currentBrightness;
            return 0;
        }

        private static unsafe int DoSetBrightness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetBrightness(aVersion, aInstanceID, aDesiredBrightness);
            return 0;
        }

        private static unsafe int DoGetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentContrast)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentContrast;
            self.GetContrast(aVersion, aInstanceID, out currentContrast);
            *aCurrentContrast = currentContrast;
            return 0;
        }

        private static unsafe int DoSetContrast(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredContrast)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetContrast(aVersion, aInstanceID, aDesiredContrast);
            return 0;
        }

        private static unsafe int DoGetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentSharpness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentSharpness;
            self.GetSharpness(aVersion, aInstanceID, out currentSharpness);
            *aCurrentSharpness = currentSharpness;
            return 0;
        }

        private static unsafe int DoSetSharpness(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredSharpness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetSharpness(aVersion, aInstanceID, aDesiredSharpness);
            return 0;
        }

        private static unsafe int DoGetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentRedVideoGain;
            self.GetRedVideoGain(aVersion, aInstanceID, out currentRedVideoGain);
            *aCurrentRedVideoGain = currentRedVideoGain;
            return 0;
        }

        private static unsafe int DoSetRedVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetRedVideoGain(aVersion, aInstanceID, aDesiredRedVideoGain);
            return 0;
        }

        private static unsafe int DoGetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentGreenVideoGain;
            self.GetGreenVideoGain(aVersion, aInstanceID, out currentGreenVideoGain);
            *aCurrentGreenVideoGain = currentGreenVideoGain;
            return 0;
        }

        private static unsafe int DoSetGreenVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetGreenVideoGain(aVersion, aInstanceID, aDesiredGreenVideoGain);
            return 0;
        }

        private static unsafe int DoGetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentBlueVideoGain;
            self.GetBlueVideoGain(aVersion, aInstanceID, out currentBlueVideoGain);
            *aCurrentBlueVideoGain = currentBlueVideoGain;
            return 0;
        }

        private static unsafe int DoSetBlueVideoGain(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetBlueVideoGain(aVersion, aInstanceID, aDesiredBlueVideoGain);
            return 0;
        }

        private static unsafe int DoGetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentRedVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentRedVideoBlackLevel;
            self.GetRedVideoBlackLevel(aVersion, aInstanceID, out currentRedVideoBlackLevel);
            *aCurrentRedVideoBlackLevel = currentRedVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetRedVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetRedVideoBlackLevel(aVersion, aInstanceID, aDesiredRedVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentGreenVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentGreenVideoBlackLevel;
            self.GetGreenVideoBlackLevel(aVersion, aInstanceID, out currentGreenVideoBlackLevel);
            *aCurrentGreenVideoBlackLevel = currentGreenVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetGreenVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetGreenVideoBlackLevel(aVersion, aInstanceID, aDesiredGreenVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentBlueVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentBlueVideoBlackLevel;
            self.GetBlueVideoBlackLevel(aVersion, aInstanceID, out currentBlueVideoBlackLevel);
            *aCurrentBlueVideoBlackLevel = currentBlueVideoBlackLevel;
            return 0;
        }

        private static unsafe int DoSetBlueVideoBlackLevel(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetBlueVideoBlackLevel(aVersion, aInstanceID, aDesiredBlueVideoBlackLevel);
            return 0;
        }

        private static unsafe int DoGetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aCurrentColorTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            uint currentColorTemperature;
            self.GetColorTemperature(aVersion, aInstanceID, out currentColorTemperature);
            *aCurrentColorTemperature = currentColorTemperature;
            return 0;
        }

        private static unsafe int DoSetColorTemperature(IntPtr aPtr, uint aVersion, uint aInstanceID, uint aDesiredColorTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetColorTemperature(aVersion, aInstanceID, aDesiredColorTemperature);
            return 0;
        }

        private static unsafe int DoGetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentHorizontalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            int currentHorizontalKeystone;
            self.GetHorizontalKeystone(aVersion, aInstanceID, out currentHorizontalKeystone);
            *aCurrentHorizontalKeystone = currentHorizontalKeystone;
            return 0;
        }

        private static unsafe int DoSetHorizontalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetHorizontalKeystone(aVersion, aInstanceID, aDesiredHorizontalKeystone);
            return 0;
        }

        private static unsafe int DoGetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int* aCurrentVerticalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            int currentVerticalKeystone;
            self.GetVerticalKeystone(aVersion, aInstanceID, out currentVerticalKeystone);
            *aCurrentVerticalKeystone = currentVerticalKeystone;
            return 0;
        }

        private static unsafe int DoSetVerticalKeystone(IntPtr aPtr, uint aVersion, uint aInstanceID, int aDesiredVerticalKeystone)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            self.SetVerticalKeystone(aVersion, aInstanceID, aDesiredVerticalKeystone);
            return 0;
        }

        private static unsafe int DoGetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool currentMute;
            self.GetMute(aVersion, aInstanceID, channel, out currentMute);
            *aCurrentMute = (currentMute ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetMute(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredMute)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool desiredMute = (aDesiredMute != 0);
            self.SetMute(aVersion, aInstanceID, channel, desiredMute);
            return 0;
        }

        private static unsafe int DoGetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint* aCurrentVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            uint currentVolume;
            self.GetVolume(aVersion, aInstanceID, channel, out currentVolume);
            *aCurrentVolume = currentVolume;
            return 0;
        }

        private static unsafe int DoSetVolume(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, uint aDesiredVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            self.SetVolume(aVersion, aInstanceID, channel, aDesiredVolume);
            return 0;
        }

        private static unsafe int DoGetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aCurrentVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            int currentVolume;
            self.GetVolumeDB(aVersion, aInstanceID, channel, out currentVolume);
            *aCurrentVolume = currentVolume;
            return 0;
        }

        private static unsafe int DoSetVolumeDB(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredVolume)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            self.SetVolumeDB(aVersion, aInstanceID, channel, aDesiredVolume);
            return 0;
        }

        private static unsafe int DoGetVolumeDBRange(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int* aMinValue, int* aMaxValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
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
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool currentLoudness;
            self.GetLoudness(aVersion, aInstanceID, channel, out currentLoudness);
            *aCurrentLoudness = (currentLoudness ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetLoudness(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aChannel, int aDesiredLoudness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string channel = Marshal.PtrToStringAnsi((IntPtr)aChannel);
            bool desiredLoudness = (aDesiredLoudness != 0);
            self.SetLoudness(aVersion, aInstanceID, channel, desiredLoudness);
            return 0;
        }

        private static unsafe int DoGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string stateVariableList = Marshal.PtrToStringAnsi((IntPtr)aStateVariableList);
            string stateVariableValuePairs;
            self.GetStateVariables(aVersion, aInstanceID, stateVariableList, out stateVariableValuePairs);
            *aStateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(stateVariableValuePairs).ToPointer();
            return 0;
        }

        private static unsafe int DoSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aRenderingControlUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgRenderingControl2 self = (DvProviderUpnpOrgRenderingControl2)gch.Target;
            string renderingControlUDN = Marshal.PtrToStringAnsi((IntPtr)aRenderingControlUDN);
            string serviceType = Marshal.PtrToStringAnsi((IntPtr)aServiceType);
            string serviceId = Marshal.PtrToStringAnsi((IntPtr)aServiceId);
            string stateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)aStateVariableValuePairs);
            string stateVariableList;
            self.SetStateVariables(aVersion, aInstanceID, renderingControlUDN, serviceType, serviceId, stateVariableValuePairs, out stateVariableList);
            *aStateVariableList = (char*)Marshal.StringToHGlobalAnsi(stateVariableList).ToPointer();
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderUpnpOrgRenderingControl2()
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
            DvProviderUpnpOrgRenderingControl2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

