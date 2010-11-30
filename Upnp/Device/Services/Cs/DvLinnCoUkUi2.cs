using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkUi2 : IDisposable
    {

        /// <summary>
        /// Set the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayBrightness(uint aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayBrightness(out uint aValue);

        /// <summary>
        /// Set the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayBrightnessAuto(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayBrightnessAuto(out bool aValue);

        /// <summary>
        /// Set the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyInfraredCommands(string aValue);

        /// <summary>
        /// Get a copy of the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyInfraredCommands(out string aValue);

        /// <summary>
        /// Set the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyInfraredTerminalCommands(string aValue);

        /// <summary>
        /// Get a copy of the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyInfraredTerminalCommands(out string aValue);

        /// <summary>
        /// Set the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayUpsideDown(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayUpsideDown(out bool aValue);

        /// <summary>
        /// Set the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayScrollText(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayScrollText(out bool aValue);

        /// <summary>
        /// Set the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplaySleep(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplaySleep(out bool aValue);

        /// <summary>
        /// Set the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayLedOff(bool aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayLedOff(out bool aValue);

        /// <summary>
        /// Set the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTerminalInputCode(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyTerminalInputCode(out uint aValue);

        /// <summary>
        /// Set the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTerminalInputName(string aValue);

        /// <summary>
        /// Get a copy of the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyTerminalInputName(out string aValue);

        /// <summary>
        /// Set the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDisplayPixels(string aValue);

        /// <summary>
        /// Get a copy of the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyDisplayPixels(out string aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Ui:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkUi2 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkUi2")]
        static extern uint DvProviderLinnCoUkUi2Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2Destroy(uint aHandle);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyInfraredCommands(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyInfraredCommands(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplaySleep(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplaySleep(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyTerminalInputName(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyTerminalInputName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvProviderLinnCoUkUi2SetPropertyDisplayPixels(uint aHandle, char* aValue, int aValueLen, uint* aChanged);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvProviderLinnCoUkUi2GetPropertyDisplayPixels(uint aHandle, char** aValue, int* aValueLen);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(uint aHandle, CallbackDisplayTestPattern aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayFill(uint aHandle, CallbackDisplayFill aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayClear(uint aHandle, CallbackDisplayClear aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(uint aHandle, CallbackSetTestModeEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(uint aHandle, CallbackSimulateInfraredInput aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(uint aHandle, CallbackSimulateButtonInput aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(uint aHandle, CallbackSimulateLightSensor aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionGetLightSensorData(uint aHandle, CallbackGetLightSensorData aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(uint aHandle, CallbackSetDisplayBrightness aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(uint aHandle, CallbackSetDisplayBrightnessAuto aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(uint aHandle, CallbackSetInfraredCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionInfraredCommands(uint aHandle, CallbackInfraredCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(uint aHandle, CallbackSetInfraredTerminalCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(uint aHandle, CallbackInfraredTerminalCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayBrightness(uint aHandle, CallbackDisplayBrightness aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(uint aHandle, CallbackDisplayBrightnessAuto aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(uint aHandle, CallbackDisplayUpsideDown aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(uint aHandle, CallbackSetDisplayUpsideDown aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(uint aHandle, CallbackSetDisplayScrollText aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayScrollText(uint aHandle, CallbackDisplayScrollText aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(uint aHandle, CallbackSetDisplaySleep aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplaySleep(uint aHandle, CallbackDisplaySleep aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(uint aHandle, CallbackSetDisplayLedOff aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvProviderLinnCoUkUi2EnableActionDisplayLedOff(uint aHandle, CallbackDisplayLedOff aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackDisplayTestPattern(IntPtr aPtr, uint aVersion, int aaTestPattern);
        private unsafe delegate int CallbackDisplayFill(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackDisplayClear(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSetTestModeEnabled(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackSimulateInfraredInput(IntPtr aPtr, uint aVersion, uint aaCode);
        private unsafe delegate int CallbackSimulateButtonInput(IntPtr aPtr, uint aVersion, uint aaCode);
        private unsafe delegate int CallbackSimulateLightSensor(IntPtr aPtr, uint aVersion, uint aaLightLevel);
        private unsafe delegate int CallbackGetLightSensorData(IntPtr aPtr, uint aVersion, uint* aaLightLevel);
        private unsafe delegate int CallbackSetDisplayBrightness(IntPtr aPtr, uint aVersion, uint aaBrightness);
        private unsafe delegate int CallbackSetDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int aaBrightnessAuto);
        private unsafe delegate int CallbackSetInfraredCommands(IntPtr aPtr, uint aVersion, char* aaCommands);
        private unsafe delegate int CallbackInfraredCommands(IntPtr aPtr, uint aVersion, char** aaCommands);
        private unsafe delegate int CallbackSetInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char* aaCommands);
        private unsafe delegate int CallbackInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char** aaCommands);
        private unsafe delegate int CallbackDisplayBrightness(IntPtr aPtr, uint aVersion, uint* aaBrightness);
        private unsafe delegate int CallbackDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int* aaBrightnessAuto);
        private unsafe delegate int CallbackDisplayUpsideDown(IntPtr aPtr, uint aVersion, int* aaUpsideDown);
        private unsafe delegate int CallbackSetDisplayUpsideDown(IntPtr aPtr, uint aVersion, int aaUpsideDown);
        private unsafe delegate int CallbackSetDisplayScrollText(IntPtr aPtr, uint aVersion, int aaDisplayScrollText);
        private unsafe delegate int CallbackDisplayScrollText(IntPtr aPtr, uint aVersion, int* aaDisplayScrollTextEnabled);
        private unsafe delegate int CallbackSetDisplaySleep(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackDisplaySleep(IntPtr aPtr, uint aVersion, int* aaEnabled);
        private unsafe delegate int CallbackSetDisplayLedOff(IntPtr aPtr, uint aVersion, int aaOff);
        private unsafe delegate int CallbackDisplayLedOff(IntPtr aPtr, uint aVersion, int* aaOff);

        private GCHandle iGch;
        private CallbackDisplayTestPattern iCallbackDisplayTestPattern;
        private CallbackDisplayFill iCallbackDisplayFill;
        private CallbackDisplayClear iCallbackDisplayClear;
        private CallbackSetTestModeEnabled iCallbackSetTestModeEnabled;
        private CallbackSimulateInfraredInput iCallbackSimulateInfraredInput;
        private CallbackSimulateButtonInput iCallbackSimulateButtonInput;
        private CallbackSimulateLightSensor iCallbackSimulateLightSensor;
        private CallbackGetLightSensorData iCallbackGetLightSensorData;
        private CallbackSetDisplayBrightness iCallbackSetDisplayBrightness;
        private CallbackSetDisplayBrightnessAuto iCallbackSetDisplayBrightnessAuto;
        private CallbackSetInfraredCommands iCallbackSetInfraredCommands;
        private CallbackInfraredCommands iCallbackInfraredCommands;
        private CallbackSetInfraredTerminalCommands iCallbackSetInfraredTerminalCommands;
        private CallbackInfraredTerminalCommands iCallbackInfraredTerminalCommands;
        private CallbackDisplayBrightness iCallbackDisplayBrightness;
        private CallbackDisplayBrightnessAuto iCallbackDisplayBrightnessAuto;
        private CallbackDisplayUpsideDown iCallbackDisplayUpsideDown;
        private CallbackSetDisplayUpsideDown iCallbackSetDisplayUpsideDown;
        private CallbackSetDisplayScrollText iCallbackSetDisplayScrollText;
        private CallbackDisplayScrollText iCallbackDisplayScrollText;
        private CallbackSetDisplaySleep iCallbackSetDisplaySleep;
        private CallbackDisplaySleep iCallbackDisplaySleep;
        private CallbackSetDisplayLedOff iCallbackSetDisplayLedOff;
        private CallbackDisplayLedOff iCallbackDisplayLedOff;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkUi2(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkUi2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayBrightness(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplayBrightness(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayBrightness property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayBrightness(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkUi2GetPropertyDisplayBrightness(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayBrightnessAuto(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplayBrightnessAuto(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayBrightnessAuto property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayBrightnessAuto(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkUi2GetPropertyDisplayBrightnessAuto(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyInfraredCommands(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkUi2SetPropertyInfraredCommands(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the InfraredCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyInfraredCommands(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkUi2GetPropertyInfraredCommands(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyInfraredTerminalCommands(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkUi2SetPropertyInfraredTerminalCommands(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the InfraredTerminalCommands property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyInfraredTerminalCommands(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkUi2GetPropertyInfraredTerminalCommands(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayUpsideDown(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplayUpsideDown(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayUpsideDown property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayUpsideDown(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkUi2GetPropertyDisplayUpsideDown(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayScrollText(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplayScrollText(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayScrollText property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayScrollText(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkUi2GetPropertyDisplayScrollText(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplaySleep(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplaySleep(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplaySleep property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplaySleep(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkUi2GetPropertyDisplaySleep(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayLedOff(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderLinnCoUkUi2SetPropertyDisplayLedOff(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayLedOff property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayLedOff(out bool aValue)
        {
            int value;
            DvProviderLinnCoUkUi2GetPropertyDisplayLedOff(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTerminalInputCode(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkUi2SetPropertyTerminalInputCode(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TerminalInputCode property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTerminalInputCode(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkUi2GetPropertyTerminalInputCode(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTerminalInputName(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkUi2SetPropertyTerminalInputName(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TerminalInputName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTerminalInputName(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkUi2GetPropertyTerminalInputName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyDisplayPixels(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvProviderLinnCoUkUi2SetPropertyDisplayPixels(iHandle, value, valueLen, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the DisplayPixels property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyDisplayPixels(out string aValue)
        {
            char* value;
            int valueLen;
             DvProviderLinnCoUkUi2GetPropertyDisplayPixels(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action DisplayTestPattern is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayTestPattern must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayTestPattern()
        {
            iCallbackDisplayTestPattern = new CallbackDisplayTestPattern(DoDisplayTestPattern);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayTestPattern(iHandle, iCallbackDisplayTestPattern, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayFill is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayFill must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayFill()
        {
            iCallbackDisplayFill = new CallbackDisplayFill(DoDisplayFill);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayFill(iHandle, iCallbackDisplayFill, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayClear is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayClear must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayClear()
        {
            iCallbackDisplayClear = new CallbackDisplayClear(DoDisplayClear);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayClear(iHandle, iCallbackDisplayClear, ptr);
        }

        /// <summary>
        /// Signal that the action SetTestModeEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetTestModeEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetTestModeEnabled()
        {
            iCallbackSetTestModeEnabled = new CallbackSetTestModeEnabled(DoSetTestModeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetTestModeEnabled(iHandle, iCallbackSetTestModeEnabled, ptr);
        }

        /// <summary>
        /// Signal that the action SimulateInfraredInput is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSimulateInfraredInput must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSimulateInfraredInput()
        {
            iCallbackSimulateInfraredInput = new CallbackSimulateInfraredInput(DoSimulateInfraredInput);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSimulateInfraredInput(iHandle, iCallbackSimulateInfraredInput, ptr);
        }

        /// <summary>
        /// Signal that the action SimulateButtonInput is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSimulateButtonInput must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSimulateButtonInput()
        {
            iCallbackSimulateButtonInput = new CallbackSimulateButtonInput(DoSimulateButtonInput);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSimulateButtonInput(iHandle, iCallbackSimulateButtonInput, ptr);
        }

        /// <summary>
        /// Signal that the action SimulateLightSensor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSimulateLightSensor must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSimulateLightSensor()
        {
            iCallbackSimulateLightSensor = new CallbackSimulateLightSensor(DoSimulateLightSensor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSimulateLightSensor(iHandle, iCallbackSimulateLightSensor, ptr);
        }

        /// <summary>
        /// Signal that the action GetLightSensorData is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetLightSensorData must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetLightSensorData()
        {
            iCallbackGetLightSensorData = new CallbackGetLightSensorData(DoGetLightSensorData);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionGetLightSensorData(iHandle, iCallbackGetLightSensorData, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplayBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplayBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplayBrightness()
        {
            iCallbackSetDisplayBrightness = new CallbackSetDisplayBrightness(DoSetDisplayBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplayBrightness(iHandle, iCallbackSetDisplayBrightness, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplayBrightnessAuto is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplayBrightnessAuto must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplayBrightnessAuto()
        {
            iCallbackSetDisplayBrightnessAuto = new CallbackSetDisplayBrightnessAuto(DoSetDisplayBrightnessAuto);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(iHandle, iCallbackSetDisplayBrightnessAuto, ptr);
        }

        /// <summary>
        /// Signal that the action SetInfraredCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetInfraredCommands must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetInfraredCommands()
        {
            iCallbackSetInfraredCommands = new CallbackSetInfraredCommands(DoSetInfraredCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetInfraredCommands(iHandle, iCallbackSetInfraredCommands, ptr);
        }

        /// <summary>
        /// Signal that the action InfraredCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoInfraredCommands must be overridden if this is called.</remarks>
        protected unsafe void EnableActionInfraredCommands()
        {
            iCallbackInfraredCommands = new CallbackInfraredCommands(DoInfraredCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionInfraredCommands(iHandle, iCallbackInfraredCommands, ptr);
        }

        /// <summary>
        /// Signal that the action SetInfraredTerminalCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetInfraredTerminalCommands must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetInfraredTerminalCommands()
        {
            iCallbackSetInfraredTerminalCommands = new CallbackSetInfraredTerminalCommands(DoSetInfraredTerminalCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetInfraredTerminalCommands(iHandle, iCallbackSetInfraredTerminalCommands, ptr);
        }

        /// <summary>
        /// Signal that the action InfraredTerminalCommands is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoInfraredTerminalCommands must be overridden if this is called.</remarks>
        protected unsafe void EnableActionInfraredTerminalCommands()
        {
            iCallbackInfraredTerminalCommands = new CallbackInfraredTerminalCommands(DoInfraredTerminalCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionInfraredTerminalCommands(iHandle, iCallbackInfraredTerminalCommands, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayBrightness is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayBrightness must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayBrightness()
        {
            iCallbackDisplayBrightness = new CallbackDisplayBrightness(DoDisplayBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayBrightness(iHandle, iCallbackDisplayBrightness, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayBrightnessAuto is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayBrightnessAuto must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayBrightnessAuto()
        {
            iCallbackDisplayBrightnessAuto = new CallbackDisplayBrightnessAuto(DoDisplayBrightnessAuto);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayBrightnessAuto(iHandle, iCallbackDisplayBrightnessAuto, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayUpsideDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayUpsideDown must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayUpsideDown()
        {
            iCallbackDisplayUpsideDown = new CallbackDisplayUpsideDown(DoDisplayUpsideDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayUpsideDown(iHandle, iCallbackDisplayUpsideDown, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplayUpsideDown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplayUpsideDown must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplayUpsideDown()
        {
            iCallbackSetDisplayUpsideDown = new CallbackSetDisplayUpsideDown(DoSetDisplayUpsideDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplayUpsideDown(iHandle, iCallbackSetDisplayUpsideDown, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplayScrollText is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplayScrollText must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplayScrollText()
        {
            iCallbackSetDisplayScrollText = new CallbackSetDisplayScrollText(DoSetDisplayScrollText);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplayScrollText(iHandle, iCallbackSetDisplayScrollText, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayScrollText is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayScrollText must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayScrollText()
        {
            iCallbackDisplayScrollText = new CallbackDisplayScrollText(DoDisplayScrollText);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayScrollText(iHandle, iCallbackDisplayScrollText, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplaySleep is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplaySleep must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplaySleep()
        {
            iCallbackSetDisplaySleep = new CallbackSetDisplaySleep(DoSetDisplaySleep);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplaySleep(iHandle, iCallbackSetDisplaySleep, ptr);
        }

        /// <summary>
        /// Signal that the action DisplaySleep is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplaySleep must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplaySleep()
        {
            iCallbackDisplaySleep = new CallbackDisplaySleep(DoDisplaySleep);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplaySleep(iHandle, iCallbackDisplaySleep, ptr);
        }

        /// <summary>
        /// Signal that the action SetDisplayLedOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDisplayLedOff must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDisplayLedOff()
        {
            iCallbackSetDisplayLedOff = new CallbackSetDisplayLedOff(DoSetDisplayLedOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionSetDisplayLedOff(iHandle, iCallbackSetDisplayLedOff, ptr);
        }

        /// <summary>
        /// Signal that the action DisplayLedOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDisplayLedOff must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDisplayLedOff()
        {
            iCallbackDisplayLedOff = new CallbackDisplayLedOff(DoDisplayLedOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkUi2EnableActionDisplayLedOff(iHandle, iCallbackDisplayLedOff, ptr);
        }

        /// <summary>
        /// DisplayTestPattern action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayTestPattern action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayTestPattern was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTestPattern"></param>
        protected virtual void DisplayTestPattern(uint aVersion, int aaTestPattern)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayFill action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayFill action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayFill was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void DisplayFill(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayClear action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayClear action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayClear was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void DisplayClear(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetTestModeEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetTestModeEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetTestModeEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetTestModeEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateInfraredInput action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateInfraredInput action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateInfraredInput was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCode"></param>
        protected virtual void SimulateInfraredInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateButtonInput action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateButtonInput action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateButtonInput was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCode"></param>
        protected virtual void SimulateButtonInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SimulateLightSensor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SimulateLightSensor action for the owning device.
        ///
        /// Must be implemented iff EnableActionSimulateLightSensor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLightLevel"></param>
        protected virtual void SimulateLightSensor(uint aVersion, uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetLightSensorData action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLightSensorData action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLightSensorData was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaLightLevel"></param>
        protected virtual void GetLightSensorData(uint aVersion, out uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightness"></param>
        protected virtual void SetDisplayBrightness(uint aVersion, uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayBrightnessAuto action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayBrightnessAuto action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayBrightnessAuto was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightnessAuto"></param>
        protected virtual void SetDisplayBrightnessAuto(uint aVersion, bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInfraredCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInfraredCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInfraredCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void SetInfraredCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// InfraredCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// InfraredCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionInfraredCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void InfraredCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInfraredTerminalCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInfraredTerminalCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInfraredTerminalCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void SetInfraredTerminalCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// InfraredTerminalCommands action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// InfraredTerminalCommands action for the owning device.
        ///
        /// Must be implemented iff EnableActionInfraredTerminalCommands was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaCommands"></param>
        protected virtual void InfraredTerminalCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayBrightness action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayBrightness action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayBrightness was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightness"></param>
        protected virtual void DisplayBrightness(uint aVersion, out uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayBrightnessAuto action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayBrightnessAuto action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayBrightnessAuto was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBrightnessAuto"></param>
        protected virtual void DisplayBrightnessAuto(uint aVersion, out bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayUpsideDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayUpsideDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayUpsideDown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUpsideDown"></param>
        protected virtual void DisplayUpsideDown(uint aVersion, out bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayUpsideDown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayUpsideDown action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayUpsideDown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUpsideDown"></param>
        protected virtual void SetDisplayUpsideDown(uint aVersion, bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayScrollText action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayScrollText action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayScrollText was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDisplayScrollText"></param>
        protected virtual void SetDisplayScrollText(uint aVersion, bool aaDisplayScrollText)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayScrollText action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayScrollText action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayScrollText was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDisplayScrollTextEnabled"></param>
        protected virtual void DisplayScrollText(uint aVersion, out bool aaDisplayScrollTextEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplaySleep action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplaySleep action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplaySleep was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void SetDisplaySleep(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplaySleep action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplaySleep action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplaySleep was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaEnabled"></param>
        protected virtual void DisplaySleep(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetDisplayLedOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDisplayLedOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDisplayLedOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOff"></param>
        protected virtual void SetDisplayLedOff(uint aVersion, bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DisplayLedOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DisplayLedOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionDisplayLedOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaOff"></param>
        protected virtual void DisplayLedOff(uint aVersion, out bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoDisplayTestPattern(IntPtr aPtr, uint aVersion, int aaTestPattern)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.DisplayTestPattern(aVersion, aaTestPattern);
            return 0;
        }

        private static unsafe int DoDisplayFill(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.DisplayFill(aVersion);
            return 0;
        }

        private static unsafe int DoDisplayClear(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.DisplayClear(aVersion);
            return 0;
        }

        private static unsafe int DoSetTestModeEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetTestModeEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoSimulateInfraredInput(IntPtr aPtr, uint aVersion, uint aaCode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.SimulateInfraredInput(aVersion, aaCode);
            return 0;
        }

        private static unsafe int DoSimulateButtonInput(IntPtr aPtr, uint aVersion, uint aaCode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.SimulateButtonInput(aVersion, aaCode);
            return 0;
        }

        private static unsafe int DoSimulateLightSensor(IntPtr aPtr, uint aVersion, uint aaLightLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.SimulateLightSensor(aVersion, aaLightLevel);
            return 0;
        }

        private static unsafe int DoGetLightSensorData(IntPtr aPtr, uint aVersion, uint* aaLightLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            uint aLightLevel;
            self.GetLightSensorData(aVersion, out aLightLevel);
            *aaLightLevel = aLightLevel;
            return 0;
        }

        private static unsafe int DoSetDisplayBrightness(IntPtr aPtr, uint aVersion, uint aaBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            self.SetDisplayBrightness(aVersion, aaBrightness);
            return 0;
        }

        private static unsafe int DoSetDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int aaBrightnessAuto)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aBrightnessAuto = (aaBrightnessAuto != 0);
            self.SetDisplayBrightnessAuto(aVersion, aBrightnessAuto);
            return 0;
        }

        private static unsafe int DoSetInfraredCommands(IntPtr aPtr, uint aVersion, char* aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            string aCommands = Marshal.PtrToStringAnsi((IntPtr)aaCommands);
            self.SetInfraredCommands(aVersion, aCommands);
            return 0;
        }

        private static unsafe int DoInfraredCommands(IntPtr aPtr, uint aVersion, char** aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            string aCommands;
            self.InfraredCommands(aVersion, out aCommands);
            *aaCommands = (char*)Marshal.StringToHGlobalAnsi(aCommands).ToPointer();
            return 0;
        }

        private static unsafe int DoSetInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char* aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            string aCommands = Marshal.PtrToStringAnsi((IntPtr)aaCommands);
            self.SetInfraredTerminalCommands(aVersion, aCommands);
            return 0;
        }

        private static unsafe int DoInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char** aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            string aCommands;
            self.InfraredTerminalCommands(aVersion, out aCommands);
            *aaCommands = (char*)Marshal.StringToHGlobalAnsi(aCommands).ToPointer();
            return 0;
        }

        private static unsafe int DoDisplayBrightness(IntPtr aPtr, uint aVersion, uint* aaBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            uint aBrightness;
            self.DisplayBrightness(aVersion, out aBrightness);
            *aaBrightness = aBrightness;
            return 0;
        }

        private static unsafe int DoDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int* aaBrightnessAuto)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aBrightnessAuto;
            self.DisplayBrightnessAuto(aVersion, out aBrightnessAuto);
            *aaBrightnessAuto = (aBrightnessAuto ? 1 : 0);
            return 0;
        }

        private static unsafe int DoDisplayUpsideDown(IntPtr aPtr, uint aVersion, int* aaUpsideDown)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aUpsideDown;
            self.DisplayUpsideDown(aVersion, out aUpsideDown);
            *aaUpsideDown = (aUpsideDown ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplayUpsideDown(IntPtr aPtr, uint aVersion, int aaUpsideDown)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aUpsideDown = (aaUpsideDown != 0);
            self.SetDisplayUpsideDown(aVersion, aUpsideDown);
            return 0;
        }

        private static unsafe int DoSetDisplayScrollText(IntPtr aPtr, uint aVersion, int aaDisplayScrollText)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aDisplayScrollText = (aaDisplayScrollText != 0);
            self.SetDisplayScrollText(aVersion, aDisplayScrollText);
            return 0;
        }

        private static unsafe int DoDisplayScrollText(IntPtr aPtr, uint aVersion, int* aaDisplayScrollTextEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aDisplayScrollTextEnabled;
            self.DisplayScrollText(aVersion, out aDisplayScrollTextEnabled);
            *aaDisplayScrollTextEnabled = (aDisplayScrollTextEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplaySleep(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetDisplaySleep(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoDisplaySleep(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aEnabled;
            self.DisplaySleep(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplayLedOff(IntPtr aPtr, uint aVersion, int aaOff)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aOff = (aaOff != 0);
            self.SetDisplayLedOff(aVersion, aOff);
            return 0;
        }

        private static unsafe int DoDisplayLedOff(IntPtr aPtr, uint aVersion, int* aaOff)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkUi2 self = (DvProviderLinnCoUkUi2)gch.Target;
            bool aOff;
            self.DisplayLedOff(aVersion, out aOff);
            *aaOff = (aOff ? 1 : 0);
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

        ~DvProviderLinnCoUkUi2()
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
            DvProviderLinnCoUkUi2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

