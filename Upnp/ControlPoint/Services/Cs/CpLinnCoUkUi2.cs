using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkUi2 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkUi2")]
        static extern uint CpProxyLinnCoUkUi2Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2Destroy(uint aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayTestPattern(uint aHandle, int aaTestPattern);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayTestPattern(uint aHandle, int aaTestPattern, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayTestPattern(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayFill(uint aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayFill(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayFill(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayClear(uint aHandle);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayClear(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayClear(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetTestModeEnabled(uint aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetTestModeEnabled(uint aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetTestModeEnabled(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateInfraredInput(uint aHandle, uint aaCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateInfraredInput(uint aHandle, uint aaCode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateInfraredInput(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateButtonInput(uint aHandle, uint aaCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateButtonInput(uint aHandle, uint aaCode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateButtonInput(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSimulateLightSensor(uint aHandle, uint aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSimulateLightSensor(uint aHandle, uint aaLightLevel, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSimulateLightSensor(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncGetLightSensorData(uint aHandle, uint* aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginGetLightSensorData(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndGetLightSensorData(uint aHandle, uint aAsync, uint* aaLightLevel);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayBrightness(uint aHandle, uint aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayBrightness(uint aHandle, uint aaBrightness, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayBrightness(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(uint aHandle, uint aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(uint aHandle, uint aaBrightnessAuto, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetInfraredCommands(uint aHandle, char* aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetInfraredCommands(uint aHandle, char* aaCommands, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetInfraredCommands(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncInfraredCommands(uint aHandle, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginInfraredCommands(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndInfraredCommands(uint aHandle, uint aAsync, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(uint aHandle, char* aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(uint aHandle, char* aaCommands, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(uint aHandle, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndInfraredTerminalCommands(uint aHandle, uint aAsync, char** aaCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayBrightness(uint aHandle, uint* aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayBrightness(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayBrightness(uint aHandle, uint aAsync, uint* aaBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(uint aHandle, uint* aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayBrightnessAuto(uint aHandle, uint aAsync, uint* aaBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayUpsideDown(uint aHandle, uint* aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayUpsideDown(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayUpsideDown(uint aHandle, uint aAsync, uint* aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(uint aHandle, uint aaUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(uint aHandle, uint aaUpsideDown, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayScrollText(uint aHandle, uint aaDisplayScrollText);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayScrollText(uint aHandle, uint aaDisplayScrollText, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayScrollText(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayScrollText(uint aHandle, uint* aaDisplayScrollTextEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayScrollText(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayScrollText(uint aHandle, uint aAsync, uint* aaDisplayScrollTextEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplaySleep(uint aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplaySleep(uint aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplaySleep(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplaySleep(uint aHandle, uint* aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplaySleep(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplaySleep(uint aHandle, uint aAsync, uint* aaEnabled);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncSetDisplayLedOff(uint aHandle, uint aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginSetDisplayLedOff(uint aHandle, uint aaOff, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndSetDisplayLedOff(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2SyncDisplayLedOff(uint aHandle, uint* aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2BeginDisplayLedOff(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe int CpProxyLinnCoUkUi2EndDisplayLedOff(uint aHandle, uint aAsync, uint* aaOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessAutoChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyInfraredCommandsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyInfraredTerminalCommandsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayUpsideDownChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayScrollTextChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplaySleepChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayLedOffChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyTerminalInputCodeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyTerminalInputNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern void CpProxyLinnCoUkUi2SetPropertyDisplayPixelsChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayBrightness(uint aHandle, uint* aDisplayBrightness);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(uint aHandle, uint* aDisplayBrightnessAuto);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyInfraredCommands(uint aHandle, char** aInfraredCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(uint aHandle, char** aInfraredTerminalCommands);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(uint aHandle, uint* aDisplayUpsideDown);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayScrollText(uint aHandle, uint* aDisplayScrollText);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplaySleep(uint aHandle, uint* aDisplaySleep);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayLedOff(uint aHandle, uint* aDisplayLedOff);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyTerminalInputCode(uint aHandle, uint* aTerminalInputCode);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyTerminalInputName(uint aHandle, char** aTerminalInputName);
        [DllImport("CpLinnCoUkUi2")]
        static extern unsafe void CpProxyLinnCoUkUi2PropertyDisplayPixels(uint aHandle, char** aDisplayPixels, uint* aLen);
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

        public unsafe void EndDisplayTestPattern(uint aAsyncHandle)
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

        public unsafe void EndDisplayFill(uint aAsyncHandle)
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

        public unsafe void EndDisplayClear(uint aAsyncHandle)
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

        public unsafe void EndSetTestModeEnabled(uint aAsyncHandle)
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

        public unsafe void EndSimulateInfraredInput(uint aAsyncHandle)
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

        public unsafe void EndSimulateButtonInput(uint aAsyncHandle)
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

        public unsafe void EndSimulateLightSensor(uint aAsyncHandle)
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

        public unsafe void EndGetLightSensorData(uint aAsyncHandle, out uint aaLightLevel)
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

        public unsafe void EndSetDisplayBrightness(uint aAsyncHandle)
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

        public unsafe void EndSetDisplayBrightnessAuto(uint aAsyncHandle)
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

        public unsafe void EndSetInfraredCommands(uint aAsyncHandle)
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

        public unsafe void EndInfraredCommands(uint aAsyncHandle, out string aaCommands)
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

        public unsafe void EndSetInfraredTerminalCommands(uint aAsyncHandle)
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

        public unsafe void EndInfraredTerminalCommands(uint aAsyncHandle, out string aaCommands)
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

        public unsafe void EndDisplayBrightness(uint aAsyncHandle, out uint aaBrightness)
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

        public unsafe void EndDisplayBrightnessAuto(uint aAsyncHandle, out bool aaBrightnessAuto)
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

        public unsafe void EndDisplayUpsideDown(uint aAsyncHandle, out bool aaUpsideDown)
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

        public unsafe void EndSetDisplayUpsideDown(uint aAsyncHandle)
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

        public unsafe void EndSetDisplayScrollText(uint aAsyncHandle)
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

        public unsafe void EndDisplayScrollText(uint aAsyncHandle, out bool aaDisplayScrollTextEnabled)
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

        public unsafe void EndSetDisplaySleep(uint aAsyncHandle)
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

        public unsafe void EndDisplaySleep(uint aAsyncHandle, out bool aaEnabled)
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

        public unsafe void EndSetDisplayLedOff(uint aAsyncHandle)
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

        public unsafe void EndDisplayLedOff(uint aAsyncHandle, out bool aaOff)
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

