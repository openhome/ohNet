using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkUi2 : ICpProxy, IDisposable
    {
        void SyncDisplayTestPattern(int aaTestPattern);
        void BeginDisplayTestPattern(int aaTestPattern, CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayTestPattern(IntPtr aAsyncHandle);
        void SyncDisplayFill();
        void BeginDisplayFill(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayFill(IntPtr aAsyncHandle);
        void SyncDisplayClear();
        void BeginDisplayClear(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayClear(IntPtr aAsyncHandle);
        void SyncSetTestModeEnabled(bool aaEnabled);
        void BeginSetTestModeEnabled(bool aaEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetTestModeEnabled(IntPtr aAsyncHandle);
        void SyncSimulateInfraredInput(uint aaCode);
        void BeginSimulateInfraredInput(uint aaCode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateInfraredInput(IntPtr aAsyncHandle);
        void SyncSimulateButtonInput(uint aaCode);
        void BeginSimulateButtonInput(uint aaCode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateButtonInput(IntPtr aAsyncHandle);
        void SyncSimulateLightSensor(uint aaLightLevel);
        void BeginSimulateLightSensor(uint aaLightLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateLightSensor(IntPtr aAsyncHandle);
        void SyncGetLightSensorData(out uint aaLightLevel);
        void BeginGetLightSensorData(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLightSensorData(IntPtr aAsyncHandle, out uint aaLightLevel);
        void SyncSetDisplayBrightness(uint aaBrightness);
        void BeginSetDisplayBrightness(uint aaBrightness, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayBrightness(IntPtr aAsyncHandle);
        void SyncSetDisplayBrightnessAuto(bool aaBrightnessAuto);
        void BeginSetDisplayBrightnessAuto(bool aaBrightnessAuto, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayBrightnessAuto(IntPtr aAsyncHandle);
        void SyncSetInfraredCommands(string aaCommands);
        void BeginSetInfraredCommands(string aaCommands, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInfraredCommands(IntPtr aAsyncHandle);
        void SyncInfraredCommands(out string aaCommands);
        void BeginInfraredCommands(CpProxy.CallbackAsyncComplete aCallback);
        void EndInfraredCommands(IntPtr aAsyncHandle, out string aaCommands);
        void SyncSetInfraredTerminalCommands(string aaCommands);
        void BeginSetInfraredTerminalCommands(string aaCommands, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInfraredTerminalCommands(IntPtr aAsyncHandle);
        void SyncInfraredTerminalCommands(out string aaCommands);
        void BeginInfraredTerminalCommands(CpProxy.CallbackAsyncComplete aCallback);
        void EndInfraredTerminalCommands(IntPtr aAsyncHandle, out string aaCommands);
        void SyncDisplayBrightness(out uint aaBrightness);
        void BeginDisplayBrightness(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayBrightness(IntPtr aAsyncHandle, out uint aaBrightness);
        void SyncDisplayBrightnessAuto(out bool aaBrightnessAuto);
        void BeginDisplayBrightnessAuto(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayBrightnessAuto(IntPtr aAsyncHandle, out bool aaBrightnessAuto);
        void SyncDisplayUpsideDown(out bool aaUpsideDown);
        void BeginDisplayUpsideDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayUpsideDown(IntPtr aAsyncHandle, out bool aaUpsideDown);
        void SyncSetDisplayUpsideDown(bool aaUpsideDown);
        void BeginSetDisplayUpsideDown(bool aaUpsideDown, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayUpsideDown(IntPtr aAsyncHandle);
        void SyncSetDisplayScrollText(bool aaDisplayScrollText);
        void BeginSetDisplayScrollText(bool aaDisplayScrollText, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayScrollText(IntPtr aAsyncHandle);
        void SyncDisplayScrollText(out bool aaDisplayScrollTextEnabled);
        void BeginDisplayScrollText(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayScrollText(IntPtr aAsyncHandle, out bool aaDisplayScrollTextEnabled);
        void SyncSetDisplaySleep(bool aaEnabled);
        void BeginSetDisplaySleep(bool aaEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplaySleep(IntPtr aAsyncHandle);
        void SyncDisplaySleep(out bool aaEnabled);
        void BeginDisplaySleep(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplaySleep(IntPtr aAsyncHandle, out bool aaEnabled);
        void SyncSetDisplayLedOff(bool aaOff);
        void BeginSetDisplayLedOff(bool aaOff, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayLedOff(IntPtr aAsyncHandle);
        void SyncDisplayLedOff(out bool aaOff);
        void BeginDisplayLedOff(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayLedOff(IntPtr aAsyncHandle, out bool aaOff);

        void SetPropertyDisplayBrightnessChanged(CpProxy.CallbackPropertyChanged aDisplayBrightnessChanged);
        void PropertyDisplayBrightness(out uint aDisplayBrightness);
        void SetPropertyDisplayBrightnessAutoChanged(CpProxy.CallbackPropertyChanged aDisplayBrightnessAutoChanged);
        void PropertyDisplayBrightnessAuto(out bool aDisplayBrightnessAuto);
        void SetPropertyInfraredCommandsChanged(CpProxy.CallbackPropertyChanged aInfraredCommandsChanged);
        void PropertyInfraredCommands(out string aInfraredCommands);
        void SetPropertyInfraredTerminalCommandsChanged(CpProxy.CallbackPropertyChanged aInfraredTerminalCommandsChanged);
        void PropertyInfraredTerminalCommands(out string aInfraredTerminalCommands);
        void SetPropertyDisplayUpsideDownChanged(CpProxy.CallbackPropertyChanged aDisplayUpsideDownChanged);
        void PropertyDisplayUpsideDown(out bool aDisplayUpsideDown);
        void SetPropertyDisplayScrollTextChanged(CpProxy.CallbackPropertyChanged aDisplayScrollTextChanged);
        void PropertyDisplayScrollText(out bool aDisplayScrollText);
        void SetPropertyDisplaySleepChanged(CpProxy.CallbackPropertyChanged aDisplaySleepChanged);
        void PropertyDisplaySleep(out bool aDisplaySleep);
        void SetPropertyDisplayLedOffChanged(CpProxy.CallbackPropertyChanged aDisplayLedOffChanged);
        void PropertyDisplayLedOff(out bool aDisplayLedOff);
        void SetPropertyTerminalInputCodeChanged(CpProxy.CallbackPropertyChanged aTerminalInputCodeChanged);
        void PropertyTerminalInputCode(out uint aTerminalInputCode);
        void SetPropertyTerminalInputNameChanged(CpProxy.CallbackPropertyChanged aTerminalInputNameChanged);
        void PropertyTerminalInputName(out string aTerminalInputName);
        void SetPropertyDisplayPixelsChanged(CpProxy.CallbackPropertyChanged aDisplayPixelsChanged);
        void PropertyDisplayPixels(out string aDisplayPixels);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Ui:2 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkUi2 : CpProxy, IDisposable, ICpProxyLinnCoUkUi2
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkUi2(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkUi2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTestPattern"></param>
        public unsafe void SyncDisplayTestPattern(int aaTestPattern)
        {
            {
                CpProxyLinnCoUkUi2SyncDisplayTestPattern(iHandle, aaTestPattern);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayTestPattern().</remarks>
        /// <param name="aaTestPattern"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayTestPattern(int aaTestPattern, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayTestPattern(iHandle, aaTestPattern, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndDisplayTestPattern(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndDisplayTestPattern(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncDisplayFill()
        {
            {
                CpProxyLinnCoUkUi2SyncDisplayFill(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayFill().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayFill(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayFill(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndDisplayFill(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndDisplayFill(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncDisplayClear()
        {
            {
                CpProxyLinnCoUkUi2SyncDisplayClear(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayClear().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayClear(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayClear(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndDisplayClear(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndDisplayClear(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncSetTestModeEnabled(bool aaEnabled)
        {
            uint aEnabled = (aaEnabled? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetTestModeEnabled(iHandle, aEnabled);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetTestModeEnabled().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetTestModeEnabled(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
            uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetTestModeEnabled(iHandle, aEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetTestModeEnabled(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetTestModeEnabled(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCode"></param>
        public unsafe void SyncSimulateInfraredInput(uint aaCode)
        {
            {
                CpProxyLinnCoUkUi2SyncSimulateInfraredInput(iHandle, aaCode);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSimulateInfraredInput().</remarks>
        /// <param name="aaCode"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSimulateInfraredInput(uint aaCode, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateInfraredInput(iHandle, aaCode, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSimulateInfraredInput(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSimulateInfraredInput(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCode"></param>
        public unsafe void SyncSimulateButtonInput(uint aaCode)
        {
            {
                CpProxyLinnCoUkUi2SyncSimulateButtonInput(iHandle, aaCode);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSimulateButtonInput().</remarks>
        /// <param name="aaCode"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSimulateButtonInput(uint aaCode, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateButtonInput(iHandle, aaCode, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSimulateButtonInput(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSimulateButtonInput(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLightLevel"></param>
        public unsafe void SyncSimulateLightSensor(uint aaLightLevel)
        {
            {
                CpProxyLinnCoUkUi2SyncSimulateLightSensor(iHandle, aaLightLevel);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSimulateLightSensor().</remarks>
        /// <param name="aaLightLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSimulateLightSensor(uint aaLightLevel, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSimulateLightSensor(iHandle, aaLightLevel, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSimulateLightSensor(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSimulateLightSensor(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLightLevel"></param>
        public unsafe void SyncGetLightSensorData(out uint aaLightLevel)
        {
            fixed (uint* aLightLevel = &aaLightLevel)
            {
                CpProxyLinnCoUkUi2SyncGetLightSensorData(iHandle, aLightLevel);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLightSensorData().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetLightSensorData(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginGetLightSensorData(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaLightLevel"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightness"></param>
        public unsafe void SyncSetDisplayBrightness(uint aaBrightness)
        {
            {
                CpProxyLinnCoUkUi2SyncSetDisplayBrightness(iHandle, aaBrightness);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplayBrightness().</remarks>
        /// <param name="aaBrightness"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplayBrightness(uint aaBrightness, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayBrightness(iHandle, aaBrightness, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplayBrightness(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplayBrightness(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightnessAuto"></param>
        public unsafe void SyncSetDisplayBrightnessAuto(bool aaBrightnessAuto)
        {
            uint aBrightnessAuto = (aaBrightnessAuto? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(iHandle, aBrightnessAuto);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplayBrightnessAuto().</remarks>
        /// <param name="aaBrightnessAuto"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplayBrightnessAuto(bool aaBrightnessAuto, CallbackAsyncComplete aCallback)
        {
            uint aBrightnessAuto = (aaBrightnessAuto? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(iHandle, aBrightnessAuto, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplayBrightnessAuto(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public unsafe void SyncSetInfraredCommands(string aaCommands)
        {
            char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            {
                CpProxyLinnCoUkUi2SyncSetInfraredCommands(iHandle, aCommands);
            }
            Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetInfraredCommands().</remarks>
        /// <param name="aaCommands"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetInfraredCommands(string aaCommands, CallbackAsyncComplete aCallback)
        {
            char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetInfraredCommands(iHandle, aCommands, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetInfraredCommands(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetInfraredCommands(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public unsafe void SyncInfraredCommands(out string aaCommands)
        {
            char* aCommands;
            {
                CpProxyLinnCoUkUi2SyncInfraredCommands(iHandle, &aCommands);
            }
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInfraredCommands().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginInfraredCommands(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginInfraredCommands(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCommands"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public unsafe void SyncSetInfraredTerminalCommands(string aaCommands)
        {
            char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            {
                CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(iHandle, aCommands);
            }
            Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetInfraredTerminalCommands().</remarks>
        /// <param name="aaCommands"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetInfraredTerminalCommands(string aaCommands, CallbackAsyncComplete aCallback)
        {
            char* aCommands = (char*)Marshal.StringToHGlobalAnsi(aaCommands);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(iHandle, aCommands, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aCommands);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetInfraredTerminalCommands(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public unsafe void SyncInfraredTerminalCommands(out string aaCommands)
        {
            char* aCommands;
            {
                CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(iHandle, &aCommands);
            }
            aaCommands = Marshal.PtrToStringAnsi((IntPtr)aCommands);
            ZappFree(aCommands);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInfraredTerminalCommands().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginInfraredTerminalCommands(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCommands"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightness"></param>
        public unsafe void SyncDisplayBrightness(out uint aaBrightness)
        {
            fixed (uint* aBrightness = &aaBrightness)
            {
                CpProxyLinnCoUkUi2SyncDisplayBrightness(iHandle, aBrightness);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayBrightness().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayBrightness(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayBrightness(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBrightness"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightnessAuto"></param>
        public unsafe void SyncDisplayBrightnessAuto(out bool aaBrightnessAuto)
        {
            uint aBrightnessAuto;
            {
                CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(iHandle, &aBrightnessAuto);
            }
            aaBrightnessAuto = (aBrightnessAuto != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayBrightnessAuto().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayBrightnessAuto(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBrightnessAuto"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUpsideDown"></param>
        public unsafe void SyncDisplayUpsideDown(out bool aaUpsideDown)
        {
            uint aUpsideDown;
            {
                CpProxyLinnCoUkUi2SyncDisplayUpsideDown(iHandle, &aUpsideDown);
            }
            aaUpsideDown = (aUpsideDown != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayUpsideDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayUpsideDown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayUpsideDown(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUpsideDown"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUpsideDown"></param>
        public unsafe void SyncSetDisplayUpsideDown(bool aaUpsideDown)
        {
            uint aUpsideDown = (aaUpsideDown? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(iHandle, aUpsideDown);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplayUpsideDown().</remarks>
        /// <param name="aaUpsideDown"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplayUpsideDown(bool aaUpsideDown, CallbackAsyncComplete aCallback)
        {
            uint aUpsideDown = (aaUpsideDown? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(iHandle, aUpsideDown, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplayUpsideDown(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDisplayScrollText"></param>
        public unsafe void SyncSetDisplayScrollText(bool aaDisplayScrollText)
        {
            uint aDisplayScrollText = (aaDisplayScrollText? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetDisplayScrollText(iHandle, aDisplayScrollText);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplayScrollText().</remarks>
        /// <param name="aaDisplayScrollText"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplayScrollText(bool aaDisplayScrollText, CallbackAsyncComplete aCallback)
        {
            uint aDisplayScrollText = (aaDisplayScrollText? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayScrollText(iHandle, aDisplayScrollText, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplayScrollText(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplayScrollText(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDisplayScrollTextEnabled"></param>
        public unsafe void SyncDisplayScrollText(out bool aaDisplayScrollTextEnabled)
        {
            uint aDisplayScrollTextEnabled;
            {
                CpProxyLinnCoUkUi2SyncDisplayScrollText(iHandle, &aDisplayScrollTextEnabled);
            }
            aaDisplayScrollTextEnabled = (aDisplayScrollTextEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayScrollText().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayScrollText(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayScrollText(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDisplayScrollTextEnabled"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncSetDisplaySleep(bool aaEnabled)
        {
            uint aEnabled = (aaEnabled? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetDisplaySleep(iHandle, aEnabled);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplaySleep().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplaySleep(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
            uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplaySleep(iHandle, aEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplaySleep(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplaySleep(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncDisplaySleep(out bool aaEnabled)
        {
            uint aEnabled;
            {
                CpProxyLinnCoUkUi2SyncDisplaySleep(iHandle, &aEnabled);
            }
            aaEnabled = (aEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplaySleep().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplaySleep(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplaySleep(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOff"></param>
        public unsafe void SyncSetDisplayLedOff(bool aaOff)
        {
            uint aOff = (aaOff? 1u : 0u);
            {
                CpProxyLinnCoUkUi2SyncSetDisplayLedOff(iHandle, aOff);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDisplayLedOff().</remarks>
        /// <param name="aaOff"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDisplayLedOff(bool aaOff, CallbackAsyncComplete aCallback)
        {
            uint aOff = (aaOff? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginSetDisplayLedOff(iHandle, aOff, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDisplayLedOff(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkUi2EndSetDisplayLedOff(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOff"></param>
        public unsafe void SyncDisplayLedOff(out bool aaOff)
        {
            uint aOff;
            {
                CpProxyLinnCoUkUi2SyncDisplayLedOff(iHandle, &aOff);
            }
            aaOff = (aOff != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayLedOff().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDisplayLedOff(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkUi2BeginDisplayLedOff(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOff"></param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayBrightness state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayBrightnessChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayBrightnessAuto state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayBrightnessAutoChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the InfraredCommands state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aInfraredCommandsChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the InfraredTerminalCommands state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aInfraredTerminalCommandsChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayUpsideDown state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayUpsideDownChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayScrollText state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayScrollTextChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplaySleep state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplaySleepChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayLedOff state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayLedOffChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TerminalInputCode state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aTerminalInputCodeChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the TerminalInputName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aTerminalInputNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the DisplayPixels state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayPixelsChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the DisplayBrightness property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayBrightness">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayBrightness(out uint aDisplayBrightness)
        {
            fixed (uint* displayBrightness = &aDisplayBrightness)
            {
                CpProxyLinnCoUkUi2PropertyDisplayBrightness(iHandle, displayBrightness);
            }
        }

        /// <summary>
        /// Query the value of the DisplayBrightnessAuto property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayBrightnessAuto">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayBrightnessAuto(out bool aDisplayBrightnessAuto)
        {
            uint displayBrightnessAuto;
            CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(iHandle, &displayBrightnessAuto);
            aDisplayBrightnessAuto = (displayBrightnessAuto != 0);
        }

        /// <summary>
        /// Query the value of the InfraredCommands property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aInfraredCommands">Will be set to the value of the property</param>
        public unsafe void PropertyInfraredCommands(out string aInfraredCommands)
        {
            char* ptr;
            CpProxyLinnCoUkUi2PropertyInfraredCommands(iHandle, &ptr);
            aInfraredCommands = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the InfraredTerminalCommands property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aInfraredTerminalCommands">Will be set to the value of the property</param>
        public unsafe void PropertyInfraredTerminalCommands(out string aInfraredTerminalCommands)
        {
            char* ptr;
            CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(iHandle, &ptr);
            aInfraredTerminalCommands = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the DisplayUpsideDown property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayUpsideDown">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayUpsideDown(out bool aDisplayUpsideDown)
        {
            uint displayUpsideDown;
            CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(iHandle, &displayUpsideDown);
            aDisplayUpsideDown = (displayUpsideDown != 0);
        }

        /// <summary>
        /// Query the value of the DisplayScrollText property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayScrollText">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayScrollText(out bool aDisplayScrollText)
        {
            uint displayScrollText;
            CpProxyLinnCoUkUi2PropertyDisplayScrollText(iHandle, &displayScrollText);
            aDisplayScrollText = (displayScrollText != 0);
        }

        /// <summary>
        /// Query the value of the DisplaySleep property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplaySleep">Will be set to the value of the property</param>
        public unsafe void PropertyDisplaySleep(out bool aDisplaySleep)
        {
            uint displaySleep;
            CpProxyLinnCoUkUi2PropertyDisplaySleep(iHandle, &displaySleep);
            aDisplaySleep = (displaySleep != 0);
        }

        /// <summary>
        /// Query the value of the DisplayLedOff property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayLedOff">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayLedOff(out bool aDisplayLedOff)
        {
            uint displayLedOff;
            CpProxyLinnCoUkUi2PropertyDisplayLedOff(iHandle, &displayLedOff);
            aDisplayLedOff = (displayLedOff != 0);
        }

        /// <summary>
        /// Query the value of the TerminalInputCode property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTerminalInputCode">Will be set to the value of the property</param>
        public unsafe void PropertyTerminalInputCode(out uint aTerminalInputCode)
        {
            fixed (uint* terminalInputCode = &aTerminalInputCode)
            {
                CpProxyLinnCoUkUi2PropertyTerminalInputCode(iHandle, terminalInputCode);
            }
        }

        /// <summary>
        /// Query the value of the TerminalInputName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTerminalInputName">Will be set to the value of the property</param>
        public unsafe void PropertyTerminalInputName(out string aTerminalInputName)
        {
            char* ptr;
            CpProxyLinnCoUkUi2PropertyTerminalInputName(iHandle, &ptr);
            aTerminalInputName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the DisplayPixels property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayPixels">Will be set to the value of the property</param>
        public unsafe void PropertyDisplayPixels(out string aDisplayPixels)
        {
            char* ptr;
            uint len;
            CpProxyLinnCoUkUi2PropertyDisplayPixels(iHandle, &ptr, &len);
            aDisplayPixels = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyLinnCoUkUi2Destroy(iHandle);
                iHandle = IntPtr.Zero;
            }
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

