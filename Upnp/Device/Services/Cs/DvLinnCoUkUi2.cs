using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkUi2 : IDisposable
    {
        [DllImport("DvLinnCoUkUi2")]
        static extern uint DvServiceLinnCoUkUi2Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2Destroy(uint aHandle);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayBrightness(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayBrightness(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayBrightnessAuto(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayBrightnessAuto(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyInfraredCommands(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyInfraredCommands(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyInfraredTerminalCommands(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyInfraredTerminalCommands(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayUpsideDown(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayUpsideDown(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayScrollText(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayScrollText(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplaySleep(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplaySleep(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayLedOff(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayLedOff(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyTerminalInputCode(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyTerminalInputCode(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyTerminalInputName(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyTerminalInputName(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe int DvServiceLinnCoUkUi2SetPropertyDisplayPixels(uint aHandle, char* aValue, int aValueLen);
        [DllImport("DvLinnCoUkUi2")]
        static extern unsafe void DvServiceLinnCoUkUi2GetPropertyDisplayPixels(uint aHandle, char** aValue, int* aValueLen);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayTestPattern(uint aHandle, CallbackDisplayTestPattern aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayFill(uint aHandle, CallbackDisplayFill aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayClear(uint aHandle, CallbackDisplayClear aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetTestModeEnabled(uint aHandle, CallbackSetTestModeEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSimulateInfraredInput(uint aHandle, CallbackSimulateInfraredInput aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSimulateButtonInput(uint aHandle, CallbackSimulateButtonInput aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSimulateLightSensor(uint aHandle, CallbackSimulateLightSensor aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionGetLightSensorData(uint aHandle, CallbackGetLightSensorData aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightness(uint aHandle, CallbackSetDisplayBrightness aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(uint aHandle, CallbackSetDisplayBrightnessAuto aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetInfraredCommands(uint aHandle, CallbackSetInfraredCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionInfraredCommands(uint aHandle, CallbackInfraredCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetInfraredTerminalCommands(uint aHandle, CallbackSetInfraredTerminalCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionInfraredTerminalCommands(uint aHandle, CallbackInfraredTerminalCommands aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayBrightness(uint aHandle, CallbackDisplayBrightness aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayBrightnessAuto(uint aHandle, CallbackDisplayBrightnessAuto aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayUpsideDown(uint aHandle, CallbackDisplayUpsideDown aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplayUpsideDown(uint aHandle, CallbackSetDisplayUpsideDown aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplayScrollText(uint aHandle, CallbackSetDisplayScrollText aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayScrollText(uint aHandle, CallbackDisplayScrollText aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplaySleep(uint aHandle, CallbackSetDisplaySleep aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplaySleep(uint aHandle, CallbackDisplaySleep aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionSetDisplayLedOff(uint aHandle, CallbackSetDisplayLedOff aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkUi2")]
        static extern void DvServiceLinnCoUkUi2EnableActionDisplayLedOff(uint aHandle, CallbackDisplayLedOff aCallback, IntPtr aPtr);
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

        private uint iHandle;
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

        public DvServiceLinnCoUkUi2(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkUi2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyDisplayBrightness(uint aValue)
        {
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplayBrightness(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayBrightness(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkUi2GetPropertyDisplayBrightness(iHandle, value);
            }
        }

        public unsafe void SetPropertyDisplayBrightnessAuto(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplayBrightnessAuto(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayBrightnessAuto(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkUi2GetPropertyDisplayBrightnessAuto(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyInfraredCommands(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkUi2SetPropertyInfraredCommands(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyInfraredCommands(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkUi2GetPropertyInfraredCommands(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyInfraredTerminalCommands(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkUi2SetPropertyInfraredTerminalCommands(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyInfraredTerminalCommands(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkUi2GetPropertyInfraredTerminalCommands(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyDisplayUpsideDown(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplayUpsideDown(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayUpsideDown(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkUi2GetPropertyDisplayUpsideDown(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyDisplayScrollText(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplayScrollText(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayScrollText(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkUi2GetPropertyDisplayScrollText(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyDisplaySleep(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplaySleep(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplaySleep(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkUi2GetPropertyDisplaySleep(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyDisplayLedOff(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkUi2SetPropertyDisplayLedOff(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayLedOff(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkUi2GetPropertyDisplayLedOff(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyTerminalInputCode(uint aValue)
        {
            if (0 != DvServiceLinnCoUkUi2SetPropertyTerminalInputCode(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTerminalInputCode(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkUi2GetPropertyTerminalInputCode(iHandle, value);
            }
        }

        public unsafe void SetPropertyTerminalInputName(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkUi2SetPropertyTerminalInputName(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyTerminalInputName(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkUi2GetPropertyTerminalInputName(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyDisplayPixels(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvServiceLinnCoUkUi2SetPropertyDisplayPixels(iHandle, value, valueLen);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDisplayPixels(out string aValue)
        {
            char* value;
            int valueLen;
             DvServiceLinnCoUkUi2GetPropertyDisplayPixels(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        protected unsafe void EnableActionDisplayTestPattern()
        {
            iCallbackDisplayTestPattern = new CallbackDisplayTestPattern(DoDisplayTestPattern);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayTestPattern(iHandle, iCallbackDisplayTestPattern, ptr);
        }

        protected unsafe void EnableActionDisplayFill()
        {
            iCallbackDisplayFill = new CallbackDisplayFill(DoDisplayFill);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayFill(iHandle, iCallbackDisplayFill, ptr);
        }

        protected unsafe void EnableActionDisplayClear()
        {
            iCallbackDisplayClear = new CallbackDisplayClear(DoDisplayClear);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayClear(iHandle, iCallbackDisplayClear, ptr);
        }

        protected unsafe void EnableActionSetTestModeEnabled()
        {
            iCallbackSetTestModeEnabled = new CallbackSetTestModeEnabled(DoSetTestModeEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetTestModeEnabled(iHandle, iCallbackSetTestModeEnabled, ptr);
        }

        protected unsafe void EnableActionSimulateInfraredInput()
        {
            iCallbackSimulateInfraredInput = new CallbackSimulateInfraredInput(DoSimulateInfraredInput);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSimulateInfraredInput(iHandle, iCallbackSimulateInfraredInput, ptr);
        }

        protected unsafe void EnableActionSimulateButtonInput()
        {
            iCallbackSimulateButtonInput = new CallbackSimulateButtonInput(DoSimulateButtonInput);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSimulateButtonInput(iHandle, iCallbackSimulateButtonInput, ptr);
        }

        protected unsafe void EnableActionSimulateLightSensor()
        {
            iCallbackSimulateLightSensor = new CallbackSimulateLightSensor(DoSimulateLightSensor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSimulateLightSensor(iHandle, iCallbackSimulateLightSensor, ptr);
        }

        protected unsafe void EnableActionGetLightSensorData()
        {
            iCallbackGetLightSensorData = new CallbackGetLightSensorData(DoGetLightSensorData);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionGetLightSensorData(iHandle, iCallbackGetLightSensorData, ptr);
        }

        protected unsafe void EnableActionSetDisplayBrightness()
        {
            iCallbackSetDisplayBrightness = new CallbackSetDisplayBrightness(DoSetDisplayBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplayBrightness(iHandle, iCallbackSetDisplayBrightness, ptr);
        }

        protected unsafe void EnableActionSetDisplayBrightnessAuto()
        {
            iCallbackSetDisplayBrightnessAuto = new CallbackSetDisplayBrightnessAuto(DoSetDisplayBrightnessAuto);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplayBrightnessAuto(iHandle, iCallbackSetDisplayBrightnessAuto, ptr);
        }

        protected unsafe void EnableActionSetInfraredCommands()
        {
            iCallbackSetInfraredCommands = new CallbackSetInfraredCommands(DoSetInfraredCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetInfraredCommands(iHandle, iCallbackSetInfraredCommands, ptr);
        }

        protected unsafe void EnableActionInfraredCommands()
        {
            iCallbackInfraredCommands = new CallbackInfraredCommands(DoInfraredCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionInfraredCommands(iHandle, iCallbackInfraredCommands, ptr);
        }

        protected unsafe void EnableActionSetInfraredTerminalCommands()
        {
            iCallbackSetInfraredTerminalCommands = new CallbackSetInfraredTerminalCommands(DoSetInfraredTerminalCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetInfraredTerminalCommands(iHandle, iCallbackSetInfraredTerminalCommands, ptr);
        }

        protected unsafe void EnableActionInfraredTerminalCommands()
        {
            iCallbackInfraredTerminalCommands = new CallbackInfraredTerminalCommands(DoInfraredTerminalCommands);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionInfraredTerminalCommands(iHandle, iCallbackInfraredTerminalCommands, ptr);
        }

        protected unsafe void EnableActionDisplayBrightness()
        {
            iCallbackDisplayBrightness = new CallbackDisplayBrightness(DoDisplayBrightness);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayBrightness(iHandle, iCallbackDisplayBrightness, ptr);
        }

        protected unsafe void EnableActionDisplayBrightnessAuto()
        {
            iCallbackDisplayBrightnessAuto = new CallbackDisplayBrightnessAuto(DoDisplayBrightnessAuto);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayBrightnessAuto(iHandle, iCallbackDisplayBrightnessAuto, ptr);
        }

        protected unsafe void EnableActionDisplayUpsideDown()
        {
            iCallbackDisplayUpsideDown = new CallbackDisplayUpsideDown(DoDisplayUpsideDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayUpsideDown(iHandle, iCallbackDisplayUpsideDown, ptr);
        }

        protected unsafe void EnableActionSetDisplayUpsideDown()
        {
            iCallbackSetDisplayUpsideDown = new CallbackSetDisplayUpsideDown(DoSetDisplayUpsideDown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplayUpsideDown(iHandle, iCallbackSetDisplayUpsideDown, ptr);
        }

        protected unsafe void EnableActionSetDisplayScrollText()
        {
            iCallbackSetDisplayScrollText = new CallbackSetDisplayScrollText(DoSetDisplayScrollText);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplayScrollText(iHandle, iCallbackSetDisplayScrollText, ptr);
        }

        protected unsafe void EnableActionDisplayScrollText()
        {
            iCallbackDisplayScrollText = new CallbackDisplayScrollText(DoDisplayScrollText);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayScrollText(iHandle, iCallbackDisplayScrollText, ptr);
        }

        protected unsafe void EnableActionSetDisplaySleep()
        {
            iCallbackSetDisplaySleep = new CallbackSetDisplaySleep(DoSetDisplaySleep);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplaySleep(iHandle, iCallbackSetDisplaySleep, ptr);
        }

        protected unsafe void EnableActionDisplaySleep()
        {
            iCallbackDisplaySleep = new CallbackDisplaySleep(DoDisplaySleep);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplaySleep(iHandle, iCallbackDisplaySleep, ptr);
        }

        protected unsafe void EnableActionSetDisplayLedOff()
        {
            iCallbackSetDisplayLedOff = new CallbackSetDisplayLedOff(DoSetDisplayLedOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionSetDisplayLedOff(iHandle, iCallbackSetDisplayLedOff, ptr);
        }

        protected unsafe void EnableActionDisplayLedOff()
        {
            iCallbackDisplayLedOff = new CallbackDisplayLedOff(DoDisplayLedOff);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkUi2EnableActionDisplayLedOff(iHandle, iCallbackDisplayLedOff, ptr);
        }

        protected virtual void DisplayTestPattern(uint aVersion, int aaTestPattern)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayFill(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayClear(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetTestModeEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SimulateInfraredInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SimulateButtonInput(uint aVersion, uint aaCode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SimulateLightSensor(uint aVersion, uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetLightSensorData(uint aVersion, out uint aaLightLevel)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplayBrightness(uint aVersion, uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplayBrightnessAuto(uint aVersion, bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetInfraredCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void InfraredCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetInfraredTerminalCommands(uint aVersion, string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void InfraredTerminalCommands(uint aVersion, out string aaCommands)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayBrightness(uint aVersion, out uint aaBrightness)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayBrightnessAuto(uint aVersion, out bool aaBrightnessAuto)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayUpsideDown(uint aVersion, out bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplayUpsideDown(uint aVersion, bool aaUpsideDown)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplayScrollText(uint aVersion, bool aaDisplayScrollText)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayScrollText(uint aVersion, out bool aaDisplayScrollTextEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplaySleep(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplaySleep(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDisplayLedOff(uint aVersion, bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DisplayLedOff(uint aVersion, out bool aaOff)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoDisplayTestPattern(IntPtr aPtr, uint aVersion, int aaTestPattern)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.DisplayTestPattern(aVersion, aaTestPattern);
            return 0;
        }

        private static unsafe int DoDisplayFill(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.DisplayFill(aVersion);
            return 0;
        }

        private static unsafe int DoDisplayClear(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.DisplayClear(aVersion);
            return 0;
        }

        private static unsafe int DoSetTestModeEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetTestModeEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoSimulateInfraredInput(IntPtr aPtr, uint aVersion, uint aaCode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.SimulateInfraredInput(aVersion, aaCode);
            return 0;
        }

        private static unsafe int DoSimulateButtonInput(IntPtr aPtr, uint aVersion, uint aaCode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.SimulateButtonInput(aVersion, aaCode);
            return 0;
        }

        private static unsafe int DoSimulateLightSensor(IntPtr aPtr, uint aVersion, uint aaLightLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.SimulateLightSensor(aVersion, aaLightLevel);
            return 0;
        }

        private static unsafe int DoGetLightSensorData(IntPtr aPtr, uint aVersion, uint* aaLightLevel)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            uint aLightLevel;
            self.GetLightSensorData(aVersion, out aLightLevel);
            *aaLightLevel = aLightLevel;
            return 0;
        }

        private static unsafe int DoSetDisplayBrightness(IntPtr aPtr, uint aVersion, uint aaBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            self.SetDisplayBrightness(aVersion, aaBrightness);
            return 0;
        }

        private static unsafe int DoSetDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int aaBrightnessAuto)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aBrightnessAuto = (aaBrightnessAuto != 0);
            self.SetDisplayBrightnessAuto(aVersion, aBrightnessAuto);
            return 0;
        }

        private static unsafe int DoSetInfraredCommands(IntPtr aPtr, uint aVersion, char* aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            string aCommands = Marshal.PtrToStringAnsi((IntPtr)aaCommands);
            self.SetInfraredCommands(aVersion, aCommands);
            return 0;
        }

        private static unsafe int DoInfraredCommands(IntPtr aPtr, uint aVersion, char** aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            string aCommands;
            self.InfraredCommands(aVersion, out aCommands);
            *aaCommands = (char*)Marshal.StringToHGlobalAnsi(aCommands).ToPointer();
            return 0;
        }

        private static unsafe int DoSetInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char* aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            string aCommands = Marshal.PtrToStringAnsi((IntPtr)aaCommands);
            self.SetInfraredTerminalCommands(aVersion, aCommands);
            return 0;
        }

        private static unsafe int DoInfraredTerminalCommands(IntPtr aPtr, uint aVersion, char** aaCommands)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            string aCommands;
            self.InfraredTerminalCommands(aVersion, out aCommands);
            *aaCommands = (char*)Marshal.StringToHGlobalAnsi(aCommands).ToPointer();
            return 0;
        }

        private static unsafe int DoDisplayBrightness(IntPtr aPtr, uint aVersion, uint* aaBrightness)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            uint aBrightness;
            self.DisplayBrightness(aVersion, out aBrightness);
            *aaBrightness = aBrightness;
            return 0;
        }

        private static unsafe int DoDisplayBrightnessAuto(IntPtr aPtr, uint aVersion, int* aaBrightnessAuto)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aBrightnessAuto;
            self.DisplayBrightnessAuto(aVersion, out aBrightnessAuto);
            *aaBrightnessAuto = (aBrightnessAuto ? 1 : 0);
            return 0;
        }

        private static unsafe int DoDisplayUpsideDown(IntPtr aPtr, uint aVersion, int* aaUpsideDown)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aUpsideDown;
            self.DisplayUpsideDown(aVersion, out aUpsideDown);
            *aaUpsideDown = (aUpsideDown ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplayUpsideDown(IntPtr aPtr, uint aVersion, int aaUpsideDown)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aUpsideDown = (aaUpsideDown != 0);
            self.SetDisplayUpsideDown(aVersion, aUpsideDown);
            return 0;
        }

        private static unsafe int DoSetDisplayScrollText(IntPtr aPtr, uint aVersion, int aaDisplayScrollText)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aDisplayScrollText = (aaDisplayScrollText != 0);
            self.SetDisplayScrollText(aVersion, aDisplayScrollText);
            return 0;
        }

        private static unsafe int DoDisplayScrollText(IntPtr aPtr, uint aVersion, int* aaDisplayScrollTextEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aDisplayScrollTextEnabled;
            self.DisplayScrollText(aVersion, out aDisplayScrollTextEnabled);
            *aaDisplayScrollTextEnabled = (aDisplayScrollTextEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplaySleep(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetDisplaySleep(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoDisplaySleep(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aEnabled;
            self.DisplaySleep(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDisplayLedOff(IntPtr aPtr, uint aVersion, int aaOff)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aOff = (aaOff != 0);
            self.SetDisplayLedOff(aVersion, aOff);
            return 0;
        }

        private static unsafe int DoDisplayLedOff(IntPtr aPtr, uint aVersion, int* aaOff)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkUi2 self = (DvServiceLinnCoUkUi2)gch.Target;
            bool aOff;
            self.DisplayLedOff(aVersion, out aOff);
            *aaOff = (aOff ? 1 : 0);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkUi2()
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
            DvServiceLinnCoUkUi2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

