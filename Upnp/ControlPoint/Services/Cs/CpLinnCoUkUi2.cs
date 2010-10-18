using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkUi2 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkUi2")]
        static extern IntPtr CpProxyLinnCoUkUi2Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayTestPattern(IntPtr aHandle, int aaTestPattern);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayTestPattern(IntPtr aHandle, int aaTestPattern, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayTestPattern(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayFill(IntPtr aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayFill(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayFill(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayClear(IntPtr aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayClear(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayClear(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetTestModeEnabled(IntPtr aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetTestModeEnabled(IntPtr aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetTestModeEnabled(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateInfraredInput(IntPtr aHandle, uint aaCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateInfraredInput(IntPtr aHandle, uint aaCode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateInfraredInput(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateButtonInput(IntPtr aHandle, uint aaCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateButtonInput(IntPtr aHandle, uint aaCode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateButtonInput(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateLightSensor(IntPtr aHandle, uint aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateLightSensor(IntPtr aHandle, uint aaLightLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateLightSensor(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncGetLightSensorData(IntPtr aHandle, uint* aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginGetLightSensorData(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndGetLightSensorData(IntPtr aHandle, IntPtr aAsync, uint* aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayBrightness(IntPtr aHandle, uint aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayBrightness(IntPtr aHandle, uint aaBrightness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayBrightness(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(IntPtr aHandle, uint aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(IntPtr aHandle, uint aaBrightnessAuto, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetInfraredCommands(IntPtr aHandle, char* aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetInfraredCommands(IntPtr aHandle, char* aaCommands, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetInfraredCommands(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncInfraredCommands(IntPtr aHandle, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginInfraredCommands(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndInfraredCommands(IntPtr aHandle, IntPtr aAsync, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(IntPtr aHandle, char* aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(IntPtr aHandle, char* aaCommands, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(IntPtr aHandle, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndInfraredTerminalCommands(IntPtr aHandle, IntPtr aAsync, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayBrightness(IntPtr aHandle, uint* aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayBrightness(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayBrightness(IntPtr aHandle, IntPtr aAsync, uint* aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(IntPtr aHandle, uint* aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayBrightnessAuto(IntPtr aHandle, IntPtr aAsync, uint* aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayUpsideDown(IntPtr aHandle, uint* aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayUpsideDown(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayUpsideDown(IntPtr aHandle, IntPtr aAsync, uint* aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(IntPtr aHandle, uint aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(IntPtr aHandle, uint aaUpsideDown, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayScrollText(IntPtr aHandle, uint aaDisplayScrollText);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayScrollText(IntPtr aHandle, uint aaDisplayScrollText, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayScrollText(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayScrollText(IntPtr aHandle, uint* aaDisplayScrollTextEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayScrollText(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayScrollText(IntPtr aHandle, IntPtr aAsync, uint* aaDisplayScrollTextEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplaySleep(IntPtr aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplaySleep(IntPtr aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplaySleep(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplaySleep(IntPtr aHandle, uint* aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplaySleep(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplaySleep(IntPtr aHandle, IntPtr aAsync, uint* aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayLedOff(IntPtr aHandle, uint aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayLedOff(IntPtr aHandle, uint aaOff, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayLedOff(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayLedOff(IntPtr aHandle, uint* aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayLedOff(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayLedOff(IntPtr aHandle, IntPtr aAsync, uint* aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessAutoChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyInfraredCommandsChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyInfraredTerminalCommandsChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayUpsideDownChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayScrollTextChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplaySleepChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayLedOffChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyTerminalInputCodeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyTerminalInputNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayPixelsChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayBrightness(IntPtr aHandle, uint* aDisplayBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(IntPtr aHandle, uint* aDisplayBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyInfraredCommands(IntPtr aHandle, char** aInfraredCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(IntPtr aHandle, char** aInfraredTerminalCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(IntPtr aHandle, uint* aDisplayUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayScrollText(IntPtr aHandle, uint* aDisplayScrollText);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplaySleep(IntPtr aHandle, uint* aDisplaySleep);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayLedOff(IntPtr aHandle, uint* aDisplayLedOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyTerminalInputCode(IntPtr aHandle, uint* aTerminalInputCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyTerminalInputName(IntPtr aHandle, char** aTerminalInputName);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayPixels(IntPtr aHandle, char** aDisplayPixels, uint* aLen);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iDisplayBrightnessChanged;
        private CallbackPropertyChanged iDisplayBrightnessAutoChanged;
        private CallbackPropertyChanged iInfraredCommandsChanged;
        private CallbackPropertyChanged iInfraredTerminalCommandsChanged;
        private CallbackPropertyChanged iDisplayUpsideDownChanged;
        private CallbackPropertyChanged iDisplayScrollTextChanged;
        private CallbackPropertyChanged iDisplaySleepChanged;
        private CallbackPropertyChanged iDisplayLedOffChanged;
        private CallbackPropertyChanged iTerminalInputCodeChanged;
        private CallbackPropertyChanged iTerminalInputNameChanged;
        private CallbackPropertyChanged iDisplayPixelsChanged;
        private Callback iCallbackDisplayBrightnessChanged;
        private Callback iCallbackDisplayBrightnessAutoChanged;
        private Callback iCallbackInfraredCommandsChanged;
        private Callback iCallbackInfraredTerminalCommandsChanged;
        private Callback iCallbackDisplayUpsideDownChanged;
        private Callback iCallbackDisplayScrollTextChanged;
        private Callback iCallbackDisplaySleepChanged;
        private Callback iCallbackDisplayLedOffChanged;
        private Callback iCallbackTerminalInputCodeChanged;
        private Callback iCallbackTerminalInputNameChanged;
        private Callback iCallbackDisplayPixelsChanged;

        public CpProxyLinnCoUkUi2(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkUi2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncDisplayTestPattern(int aaTestPattern)
        {
			{
				CpProxyLinnCoUkUi2SyncDisplayTestPattern(iHandle, aaTestPattern);
			}
        }

        public unsafe void BeginDisplayTestPattern(int aaTestPattern, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayTestPattern(iHandle, aaTestPattern, iActionComplete, ptr);
        }

        public unsafe void EndDisplayTestPattern(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayTestPattern(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplayFill()
        {
			{
				CpProxyLinnCoUkUi2SyncDisplayFill(iHandle);
			}
        }

        public unsafe void BeginDisplayFill(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayFill(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayFill(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayFill(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplayClear()
        {
			{
				CpProxyLinnCoUkUi2SyncDisplayClear(iHandle);
			}
        }

        public unsafe void BeginDisplayClear(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayClear(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayClear(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayClear(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetTestModeEnabled(bool aaEnabled)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetTestModeEnabled(iHandle, aEnabled);
			}
        }

        public unsafe void BeginSetTestModeEnabled(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetTestModeEnabled(iHandle, aEnabled, iActionComplete, ptr);
        }

        public unsafe void EndSetTestModeEnabled(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetTestModeEnabled(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSimulateInfraredInput(uint aaCode)
        {
			{
				CpProxyLinnCoUkUi2SyncSimulateInfraredInput(iHandle, aaCode);
			}
        }

        public unsafe void BeginSimulateInfraredInput(uint aaCode, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateInfraredInput(iHandle, aaCode, iActionComplete, ptr);
        }

        public unsafe void EndSimulateInfraredInput(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSimulateInfraredInput(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSimulateButtonInput(uint aaCode)
        {
			{
				CpProxyLinnCoUkUi2SyncSimulateButtonInput(iHandle, aaCode);
			}
        }

        public unsafe void BeginSimulateButtonInput(uint aaCode, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateButtonInput(iHandle, aaCode, iActionComplete, ptr);
        }

        public unsafe void EndSimulateButtonInput(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSimulateButtonInput(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSimulateLightSensor(uint aaLightLevel)
        {
			{
				CpProxyLinnCoUkUi2SyncSimulateLightSensor(iHandle, aaLightLevel);
			}
        }

        public unsafe void BeginSimulateLightSensor(uint aaLightLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateLightSensor(iHandle, aaLightLevel, iActionComplete, ptr);
        }

        public unsafe void EndSimulateLightSensor(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSimulateLightSensor(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetLightSensorData(out uint aaLightLevel)
        {
			fixed (uint* aLightLevel = &aaLightLevel)
			{
				CpProxyLinnCoUkUi2SyncGetLightSensorData(iHandle, aLightLevel);
			}
        }

        public unsafe void BeginGetLightSensorData(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginGetLightSensorData(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetLightSensorData(IntPtr aAsyncHandle, out uint aaLightLevel)
        {
			fixed (uint* aLightLevel = &aaLightLevel)
			{
				if (0 != CpProxyLinnCoUkUi2EndGetLightSensorData(iHandle, aAsyncHandle, aLightLevel))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetDisplayBrightness(uint aaBrightness)
        {
			{
				CpProxyLinnCoUkUi2SyncSetDisplayBrightness(iHandle, aaBrightness);
			}
        }

        public unsafe void BeginSetDisplayBrightness(uint aaBrightness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayBrightness(iHandle, aaBrightness, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplayBrightness(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplayBrightness(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetDisplayBrightnessAuto(bool aaBrightnessAuto)
        {
			uint aBrightnessAuto = (aaBrightnessAuto? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(iHandle, aBrightnessAuto);
			}
        }

        public unsafe void BeginSetDisplayBrightnessAuto(bool aaBrightnessAuto, CallbackAsyncComplete aCallback)
        {
			uint aBrightnessAuto = (aaBrightnessAuto? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(iHandle, aBrightnessAuto, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplayBrightnessAuto(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetInfraredCommands(string aaCommands)
        {
			char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
			{
				CpProxyLinnCoUkUi2SyncSetInfraredCommands(iHandle, aCommands);
			}
			Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        public unsafe void BeginSetInfraredCommands(string aaCommands, CallbackAsyncComplete aCallback)
        {
			char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetInfraredCommands(iHandle, aCommands, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        public unsafe void EndSetInfraredCommands(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetInfraredCommands(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncInfraredCommands(out string aaCommands)
        {
			char* aCommands;
			{
				CpProxyLinnCoUkUi2SyncInfraredCommands(iHandle, &aCommands);
			}
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        public unsafe void BeginInfraredCommands(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginInfraredCommands(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndInfraredCommands(IntPtr aAsyncHandle, out string aaCommands)
        {
			char* aCommands;
			{
				if (0 != CpProxyLinnCoUkUi2EndInfraredCommands(iHandle, aAsyncHandle, &aCommands))
				{
					throw(new ProxyError());
				}
			}
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        public unsafe void SyncSetInfraredTerminalCommands(string aaCommands)
        {
			char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
			{
				CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(iHandle, aCommands);
			}
			Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        public unsafe void BeginSetInfraredTerminalCommands(string aaCommands, CallbackAsyncComplete aCallback)
        {
			char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(iHandle, aCommands, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        public unsafe void EndSetInfraredTerminalCommands(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncInfraredTerminalCommands(out string aaCommands)
        {
			char* aCommands;
			{
				CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(iHandle, &aCommands);
			}
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        public unsafe void BeginInfraredTerminalCommands(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndInfraredTerminalCommands(IntPtr aAsyncHandle, out string aaCommands)
        {
			char* aCommands;
			{
				if (0 != CpProxyLinnCoUkUi2EndInfraredTerminalCommands(iHandle, aAsyncHandle, &aCommands))
				{
					throw(new ProxyError());
				}
			}
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        public unsafe void SyncDisplayBrightness(out uint aaBrightness)
        {
			fixed (uint* aBrightness = &aaBrightness)
			{
				CpProxyLinnCoUkUi2SyncDisplayBrightness(iHandle, aBrightness);
			}
        }

        public unsafe void BeginDisplayBrightness(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayBrightness(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayBrightness(IntPtr aAsyncHandle, out uint aaBrightness)
        {
			fixed (uint* aBrightness = &aaBrightness)
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayBrightness(iHandle, aAsyncHandle, aBrightness))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplayBrightnessAuto(out bool aaBrightnessAuto)
        {
			uint aBrightnessAuto;
			{
				CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(iHandle, &aBrightnessAuto);
			}
			aaBrightnessAuto = (aBrightnessAuto != 0);
        }

        public unsafe void BeginDisplayBrightnessAuto(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayBrightnessAuto(IntPtr aAsyncHandle, out bool aaBrightnessAuto)
        {
			uint aBrightnessAuto;
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayBrightnessAuto(iHandle, aAsyncHandle, &aBrightnessAuto))
				{
					throw(new ProxyError());
				}
			}
			aaBrightnessAuto = (aBrightnessAuto != 0);
        }

        public unsafe void SyncDisplayUpsideDown(out bool aaUpsideDown)
        {
			uint aUpsideDown;
			{
				CpProxyLinnCoUkUi2SyncDisplayUpsideDown(iHandle, &aUpsideDown);
			}
			aaUpsideDown = (aUpsideDown != 0);
        }

        public unsafe void BeginDisplayUpsideDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayUpsideDown(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayUpsideDown(IntPtr aAsyncHandle, out bool aaUpsideDown)
        {
			uint aUpsideDown;
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayUpsideDown(iHandle, aAsyncHandle, &aUpsideDown))
				{
					throw(new ProxyError());
				}
			}
			aaUpsideDown = (aUpsideDown != 0);
        }

        public unsafe void SyncSetDisplayUpsideDown(bool aaUpsideDown)
        {
			uint aUpsideDown = (aaUpsideDown? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(iHandle, aUpsideDown);
			}
        }

        public unsafe void BeginSetDisplayUpsideDown(bool aaUpsideDown, CallbackAsyncComplete aCallback)
        {
			uint aUpsideDown = (aaUpsideDown? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(iHandle, aUpsideDown, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplayUpsideDown(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetDisplayScrollText(bool aaDisplayScrollText)
        {
			uint aDisplayScrollText = (aaDisplayScrollText? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetDisplayScrollText(iHandle, aDisplayScrollText);
			}
        }

        public unsafe void BeginSetDisplayScrollText(bool aaDisplayScrollText, CallbackAsyncComplete aCallback)
        {
			uint aDisplayScrollText = (aaDisplayScrollText? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayScrollText(iHandle, aDisplayScrollText, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplayScrollText(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplayScrollText(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplayScrollText(out bool aaDisplayScrollTextEnabled)
        {
			uint aDisplayScrollTextEnabled;
			{
				CpProxyLinnCoUkUi2SyncDisplayScrollText(iHandle, &aDisplayScrollTextEnabled);
			}
			aaDisplayScrollTextEnabled = (aDisplayScrollTextEnabled != 0);
        }

        public unsafe void BeginDisplayScrollText(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayScrollText(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayScrollText(IntPtr aAsyncHandle, out bool aaDisplayScrollTextEnabled)
        {
			uint aDisplayScrollTextEnabled;
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayScrollText(iHandle, aAsyncHandle, &aDisplayScrollTextEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaDisplayScrollTextEnabled = (aDisplayScrollTextEnabled != 0);
        }

        public unsafe void SyncSetDisplaySleep(bool aaEnabled)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetDisplaySleep(iHandle, aEnabled);
			}
        }

        public unsafe void BeginSetDisplaySleep(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplaySleep(iHandle, aEnabled, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplaySleep(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplaySleep(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplaySleep(out bool aaEnabled)
        {
			uint aEnabled;
			{
				CpProxyLinnCoUkUi2SyncDisplaySleep(iHandle, &aEnabled);
			}
			aaEnabled = (aEnabled != 0);
        }

        public unsafe void BeginDisplaySleep(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplaySleep(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplaySleep(IntPtr aAsyncHandle, out bool aaEnabled)
        {
			uint aEnabled;
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplaySleep(iHandle, aAsyncHandle, &aEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaEnabled = (aEnabled != 0);
        }

        public unsafe void SyncSetDisplayLedOff(bool aaOff)
        {
			uint aOff = (aaOff? 1u : 0u);
			{
				CpProxyLinnCoUkUi2SyncSetDisplayLedOff(iHandle, aOff);
			}
        }

        public unsafe void BeginSetDisplayLedOff(bool aaOff, CallbackAsyncComplete aCallback)
        {
			uint aOff = (aaOff? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayLedOff(iHandle, aOff, iActionComplete, ptr);
        }

        public unsafe void EndSetDisplayLedOff(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkUi2EndSetDisplayLedOff(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDisplayLedOff(out bool aaOff)
        {
			uint aOff;
			{
				CpProxyLinnCoUkUi2SyncDisplayLedOff(iHandle, &aOff);
			}
			aaOff = (aOff != 0);
        }

        public unsafe void BeginDisplayLedOff(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayLedOff(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndDisplayLedOff(IntPtr aAsyncHandle, out bool aaOff)
        {
			uint aOff;
			{
				if (0 != CpProxyLinnCoUkUi2EndDisplayLedOff(iHandle, aAsyncHandle, &aOff))
				{
					throw(new ProxyError());
				}
			}
			aaOff = (aOff != 0);
        }

        public void SetPropertyDisplayBrightnessChanged(CallbackPropertyChanged aDisplayBrightnessChanged)
        {
            iDisplayBrightnessChanged = aDisplayBrightnessChanged;
            iCallbackDisplayBrightnessChanged = new Callback(PropertyDisplayBrightnessChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessChanged(iHandle, iCallbackDisplayBrightnessChanged, ptr);
        }

        private void PropertyDisplayBrightnessChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayBrightnessChanged();
        }

        public void SetPropertyDisplayBrightnessAutoChanged(CallbackPropertyChanged aDisplayBrightnessAutoChanged)
        {
            iDisplayBrightnessAutoChanged = aDisplayBrightnessAutoChanged;
            iCallbackDisplayBrightnessAutoChanged = new Callback(PropertyDisplayBrightnessAutoChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessAutoChanged(iHandle, iCallbackDisplayBrightnessAutoChanged, ptr);
        }

        private void PropertyDisplayBrightnessAutoChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayBrightnessAutoChanged();
        }

        public void SetPropertyInfraredCommandsChanged(CallbackPropertyChanged aInfraredCommandsChanged)
        {
            iInfraredCommandsChanged = aInfraredCommandsChanged;
            iCallbackInfraredCommandsChanged = new Callback(PropertyInfraredCommandsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyInfraredCommandsChanged(iHandle, iCallbackInfraredCommandsChanged, ptr);
        }

        private void PropertyInfraredCommandsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iInfraredCommandsChanged();
        }

        public void SetPropertyInfraredTerminalCommandsChanged(CallbackPropertyChanged aInfraredTerminalCommandsChanged)
        {
            iInfraredTerminalCommandsChanged = aInfraredTerminalCommandsChanged;
            iCallbackInfraredTerminalCommandsChanged = new Callback(PropertyInfraredTerminalCommandsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyInfraredTerminalCommandsChanged(iHandle, iCallbackInfraredTerminalCommandsChanged, ptr);
        }

        private void PropertyInfraredTerminalCommandsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iInfraredTerminalCommandsChanged();
        }

        public void SetPropertyDisplayUpsideDownChanged(CallbackPropertyChanged aDisplayUpsideDownChanged)
        {
            iDisplayUpsideDownChanged = aDisplayUpsideDownChanged;
            iCallbackDisplayUpsideDownChanged = new Callback(PropertyDisplayUpsideDownChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayUpsideDownChanged(iHandle, iCallbackDisplayUpsideDownChanged, ptr);
        }

        private void PropertyDisplayUpsideDownChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayUpsideDownChanged();
        }

        public void SetPropertyDisplayScrollTextChanged(CallbackPropertyChanged aDisplayScrollTextChanged)
        {
            iDisplayScrollTextChanged = aDisplayScrollTextChanged;
            iCallbackDisplayScrollTextChanged = new Callback(PropertyDisplayScrollTextChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayScrollTextChanged(iHandle, iCallbackDisplayScrollTextChanged, ptr);
        }

        private void PropertyDisplayScrollTextChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayScrollTextChanged();
        }

        public void SetPropertyDisplaySleepChanged(CallbackPropertyChanged aDisplaySleepChanged)
        {
            iDisplaySleepChanged = aDisplaySleepChanged;
            iCallbackDisplaySleepChanged = new Callback(PropertyDisplaySleepChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplaySleepChanged(iHandle, iCallbackDisplaySleepChanged, ptr);
        }

        private void PropertyDisplaySleepChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplaySleepChanged();
        }

        public void SetPropertyDisplayLedOffChanged(CallbackPropertyChanged aDisplayLedOffChanged)
        {
            iDisplayLedOffChanged = aDisplayLedOffChanged;
            iCallbackDisplayLedOffChanged = new Callback(PropertyDisplayLedOffChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayLedOffChanged(iHandle, iCallbackDisplayLedOffChanged, ptr);
        }

        private void PropertyDisplayLedOffChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayLedOffChanged();
        }

        public void SetPropertyTerminalInputCodeChanged(CallbackPropertyChanged aTerminalInputCodeChanged)
        {
            iTerminalInputCodeChanged = aTerminalInputCodeChanged;
            iCallbackTerminalInputCodeChanged = new Callback(PropertyTerminalInputCodeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyTerminalInputCodeChanged(iHandle, iCallbackTerminalInputCodeChanged, ptr);
        }

        private void PropertyTerminalInputCodeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iTerminalInputCodeChanged();
        }

        public void SetPropertyTerminalInputNameChanged(CallbackPropertyChanged aTerminalInputNameChanged)
        {
            iTerminalInputNameChanged = aTerminalInputNameChanged;
            iCallbackTerminalInputNameChanged = new Callback(PropertyTerminalInputNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyTerminalInputNameChanged(iHandle, iCallbackTerminalInputNameChanged, ptr);
        }

        private void PropertyTerminalInputNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iTerminalInputNameChanged();
        }

        public void SetPropertyDisplayPixelsChanged(CallbackPropertyChanged aDisplayPixelsChanged)
        {
            iDisplayPixelsChanged = aDisplayPixelsChanged;
            iCallbackDisplayPixelsChanged = new Callback(PropertyDisplayPixelsChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkUi2SetPropertyDisplayPixelsChanged(iHandle, iCallbackDisplayPixelsChanged, ptr);
        }

        private void PropertyDisplayPixelsChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkUi2 self = (CpProxyLinnCoUkUi2)gch.Target;
            self.iDisplayPixelsChanged();
        }

        public unsafe void PropertyDisplayBrightness(out uint aDisplayBrightness)
        {
			fixed (uint* displayBrightness = &aDisplayBrightness)
			{
	            CpProxyLinnCoUkUi2PropertyDisplayBrightness(iHandle, displayBrightness);
			}
        }

        public unsafe void PropertyDisplayBrightnessAuto(out bool aDisplayBrightnessAuto)
        {
			uint displayBrightnessAuto;
	        CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(iHandle, &displayBrightnessAuto);
			aDisplayBrightnessAuto = (displayBrightnessAuto != 0);
        }

        public unsafe void PropertyInfraredCommands(out string aInfraredCommands)
        {
			char* ptr;
            CpProxyLinnCoUkUi2PropertyInfraredCommands(iHandle, &ptr);
            aInfraredCommands = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyInfraredTerminalCommands(out string aInfraredTerminalCommands)
        {
			char* ptr;
            CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(iHandle, &ptr);
            aInfraredTerminalCommands = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyDisplayUpsideDown(out bool aDisplayUpsideDown)
        {
			uint displayUpsideDown;
	        CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(iHandle, &displayUpsideDown);
			aDisplayUpsideDown = (displayUpsideDown != 0);
        }

        public unsafe void PropertyDisplayScrollText(out bool aDisplayScrollText)
        {
			uint displayScrollText;
	        CpProxyLinnCoUkUi2PropertyDisplayScrollText(iHandle, &displayScrollText);
			aDisplayScrollText = (displayScrollText != 0);
        }

        public unsafe void PropertyDisplaySleep(out bool aDisplaySleep)
        {
			uint displaySleep;
	        CpProxyLinnCoUkUi2PropertyDisplaySleep(iHandle, &displaySleep);
			aDisplaySleep = (displaySleep != 0);
        }

        public unsafe void PropertyDisplayLedOff(out bool aDisplayLedOff)
        {
			uint displayLedOff;
	        CpProxyLinnCoUkUi2PropertyDisplayLedOff(iHandle, &displayLedOff);
			aDisplayLedOff = (displayLedOff != 0);
        }

        public unsafe void PropertyTerminalInputCode(out uint aTerminalInputCode)
        {
			fixed (uint* terminalInputCode = &aTerminalInputCode)
			{
	            CpProxyLinnCoUkUi2PropertyTerminalInputCode(iHandle, terminalInputCode);
			}
        }

        public unsafe void PropertyTerminalInputName(out string aTerminalInputName)
        {
			char* ptr;
            CpProxyLinnCoUkUi2PropertyTerminalInputName(iHandle, &ptr);
            aTerminalInputName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyDisplayPixels(out string aDisplayPixels)
        {
			char* ptr;
			uint len;
	        CpProxyLinnCoUkUi2PropertyDisplayPixels(iHandle, &ptr, &len);
            aDisplayPixels = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkUi2()
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
            CpProxyLinnCoUkUi2Destroy(handle);
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

