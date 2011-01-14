using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkUi2 : ICpProxy, IDisposable
    {
        void SyncDisplayTestPattern(int aTestPattern);
        void BeginDisplayTestPattern(int aTestPattern, CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayTestPattern(IntPtr aAsyncHandle);
        void SyncDisplayFill();
        void BeginDisplayFill(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayFill(IntPtr aAsyncHandle);
        void SyncDisplayClear();
        void BeginDisplayClear(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayClear(IntPtr aAsyncHandle);
        void SyncSetTestModeEnabled(bool aEnabled);
        void BeginSetTestModeEnabled(bool aEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetTestModeEnabled(IntPtr aAsyncHandle);
        void SyncSimulateInfraredInput(uint aCode);
        void BeginSimulateInfraredInput(uint aCode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateInfraredInput(IntPtr aAsyncHandle);
        void SyncSimulateButtonInput(uint aCode);
        void BeginSimulateButtonInput(uint aCode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateButtonInput(IntPtr aAsyncHandle);
        void SyncSimulateLightSensor(uint aLightLevel);
        void BeginSimulateLightSensor(uint aLightLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSimulateLightSensor(IntPtr aAsyncHandle);
        void SyncGetLightSensorData(out uint aLightLevel);
        void BeginGetLightSensorData(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLightSensorData(IntPtr aAsyncHandle, out uint aLightLevel);
        void SyncSetDisplayBrightness(uint aBrightness);
        void BeginSetDisplayBrightness(uint aBrightness, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayBrightness(IntPtr aAsyncHandle);
        void SyncSetDisplayBrightnessAuto(bool aBrightnessAuto);
        void BeginSetDisplayBrightnessAuto(bool aBrightnessAuto, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayBrightnessAuto(IntPtr aAsyncHandle);
        void SyncSetInfraredCommands(String aCommands);
        void BeginSetInfraredCommands(String aCommands, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInfraredCommands(IntPtr aAsyncHandle);
        void SyncInfraredCommands(out String aCommands);
        void BeginInfraredCommands(CpProxy.CallbackAsyncComplete aCallback);
        void EndInfraredCommands(IntPtr aAsyncHandle, out String aCommands);
        void SyncSetInfraredTerminalCommands(String aCommands);
        void BeginSetInfraredTerminalCommands(String aCommands, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInfraredTerminalCommands(IntPtr aAsyncHandle);
        void SyncInfraredTerminalCommands(out String aCommands);
        void BeginInfraredTerminalCommands(CpProxy.CallbackAsyncComplete aCallback);
        void EndInfraredTerminalCommands(IntPtr aAsyncHandle, out String aCommands);
        void SyncDisplayBrightness(out uint aBrightness);
        void BeginDisplayBrightness(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayBrightness(IntPtr aAsyncHandle, out uint aBrightness);
        void SyncDisplayBrightnessAuto(out bool aBrightnessAuto);
        void BeginDisplayBrightnessAuto(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayBrightnessAuto(IntPtr aAsyncHandle, out bool aBrightnessAuto);
        void SyncDisplayUpsideDown(out bool aUpsideDown);
        void BeginDisplayUpsideDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayUpsideDown(IntPtr aAsyncHandle, out bool aUpsideDown);
        void SyncSetDisplayUpsideDown(bool aUpsideDown);
        void BeginSetDisplayUpsideDown(bool aUpsideDown, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayUpsideDown(IntPtr aAsyncHandle);
        void SyncSetDisplayScrollText(bool aDisplayScrollText);
        void BeginSetDisplayScrollText(bool aDisplayScrollText, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayScrollText(IntPtr aAsyncHandle);
        void SyncDisplayScrollText(out bool aDisplayScrollTextEnabled);
        void BeginDisplayScrollText(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayScrollText(IntPtr aAsyncHandle, out bool aDisplayScrollTextEnabled);
        void SyncSetDisplaySleep(bool aEnabled);
        void BeginSetDisplaySleep(bool aEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplaySleep(IntPtr aAsyncHandle);
        void SyncDisplaySleep(out bool aEnabled);
        void BeginDisplaySleep(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplaySleep(IntPtr aAsyncHandle, out bool aEnabled);
        void SyncSetDisplayLedOff(bool aOff);
        void BeginSetDisplayLedOff(bool aOff, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDisplayLedOff(IntPtr aAsyncHandle);
        void SyncDisplayLedOff(out bool aOff);
        void BeginDisplayLedOff(CpProxy.CallbackAsyncComplete aCallback);
        void EndDisplayLedOff(IntPtr aAsyncHandle, out bool aOff);
        void SetPropertyDisplayBrightnessChanged(CpProxy.CallbackPropertyChanged aDisplayBrightnessChanged);
        uint PropertyDisplayBrightness();
        void SetPropertyDisplayBrightnessAutoChanged(CpProxy.CallbackPropertyChanged aDisplayBrightnessAutoChanged);
        bool PropertyDisplayBrightnessAuto();
        void SetPropertyInfraredCommandsChanged(CpProxy.CallbackPropertyChanged aInfraredCommandsChanged);
        String PropertyInfraredCommands();
        void SetPropertyInfraredTerminalCommandsChanged(CpProxy.CallbackPropertyChanged aInfraredTerminalCommandsChanged);
        String PropertyInfraredTerminalCommands();
        void SetPropertyDisplayUpsideDownChanged(CpProxy.CallbackPropertyChanged aDisplayUpsideDownChanged);
        bool PropertyDisplayUpsideDown();
        void SetPropertyDisplayScrollTextChanged(CpProxy.CallbackPropertyChanged aDisplayScrollTextChanged);
        bool PropertyDisplayScrollText();
        void SetPropertyDisplaySleepChanged(CpProxy.CallbackPropertyChanged aDisplaySleepChanged);
        bool PropertyDisplaySleep();
        void SetPropertyDisplayLedOffChanged(CpProxy.CallbackPropertyChanged aDisplayLedOffChanged);
        bool PropertyDisplayLedOff();
        void SetPropertyTerminalInputCodeChanged(CpProxy.CallbackPropertyChanged aTerminalInputCodeChanged);
        uint PropertyTerminalInputCode();
        void SetPropertyTerminalInputNameChanged(CpProxy.CallbackPropertyChanged aTerminalInputNameChanged);
        String PropertyTerminalInputName();
        void SetPropertyDisplayPixelsChanged(CpProxy.CallbackPropertyChanged aDisplayPixelsChanged);
        String PropertyDisplayPixels();
    }

    internal class SyncDisplayTestPatternLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncDisplayTestPatternLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayTestPattern(aAsyncHandle);
        }
    };

    internal class SyncDisplayFillLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncDisplayFillLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayFill(aAsyncHandle);
        }
    };

    internal class SyncDisplayClearLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncDisplayClearLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayClear(aAsyncHandle);
        }
    };

    internal class SyncSetTestModeEnabledLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetTestModeEnabledLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetTestModeEnabled(aAsyncHandle);
        }
    };

    internal class SyncSimulateInfraredInputLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSimulateInfraredInputLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSimulateInfraredInput(aAsyncHandle);
        }
    };

    internal class SyncSimulateButtonInputLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSimulateButtonInputLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSimulateButtonInput(aAsyncHandle);
        }
    };

    internal class SyncSimulateLightSensorLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSimulateLightSensorLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSimulateLightSensor(aAsyncHandle);
        }
    };

    internal class SyncGetLightSensorDataLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private uint iLightLevel;

        public SyncGetLightSensorDataLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public uint LightLevel()
        {
            return iLightLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLightSensorData(aAsyncHandle, out iLightLevel);
        }
    };

    internal class SyncSetDisplayBrightnessLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplayBrightness(aAsyncHandle);
        }
    };

    internal class SyncSetDisplayBrightnessAutoLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplayBrightnessAuto(aAsyncHandle);
        }
    };

    internal class SyncSetInfraredCommandsLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetInfraredCommands(aAsyncHandle);
        }
    };

    internal class SyncInfraredCommandsLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private String iCommands;

        public SyncInfraredCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public String Commands()
        {
            return iCommands;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndInfraredCommands(aAsyncHandle, out iCommands);
        }
    };

    internal class SyncSetInfraredTerminalCommandsLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetInfraredTerminalCommands(aAsyncHandle);
        }
    };

    internal class SyncInfraredTerminalCommandsLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private String iCommands;

        public SyncInfraredTerminalCommandsLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public String Commands()
        {
            return iCommands;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndInfraredTerminalCommands(aAsyncHandle, out iCommands);
        }
    };

    internal class SyncDisplayBrightnessLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private uint iBrightness;

        public SyncDisplayBrightnessLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public uint Brightness()
        {
            return iBrightness;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayBrightness(aAsyncHandle, out iBrightness);
        }
    };

    internal class SyncDisplayBrightnessAutoLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private bool iBrightnessAuto;

        public SyncDisplayBrightnessAutoLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public bool BrightnessAuto()
        {
            return iBrightnessAuto;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayBrightnessAuto(aAsyncHandle, out iBrightnessAuto);
        }
    };

    internal class SyncDisplayUpsideDownLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private bool iUpsideDown;

        public SyncDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public bool UpsideDown()
        {
            return iUpsideDown;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayUpsideDown(aAsyncHandle, out iUpsideDown);
        }
    };

    internal class SyncSetDisplayUpsideDownLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplayUpsideDownLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplayUpsideDown(aAsyncHandle);
        }
    };

    internal class SyncSetDisplayScrollTextLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplayScrollText(aAsyncHandle);
        }
    };

    internal class SyncDisplayScrollTextLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private bool iDisplayScrollTextEnabled;

        public SyncDisplayScrollTextLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public bool DisplayScrollTextEnabled()
        {
            return iDisplayScrollTextEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayScrollText(aAsyncHandle, out iDisplayScrollTextEnabled);
        }
    };

    internal class SyncSetDisplaySleepLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplaySleep(aAsyncHandle);
        }
    };

    internal class SyncDisplaySleepLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private bool iEnabled;

        public SyncDisplaySleepLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public bool Enabled()
        {
            return iEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplaySleep(aAsyncHandle, out iEnabled);
        }
    };

    internal class SyncSetDisplayLedOffLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;

        public SyncSetDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDisplayLedOff(aAsyncHandle);
        }
    };

    internal class SyncDisplayLedOffLinnCoUkUi2 : SyncProxyAction
    {
        private CpProxyLinnCoUkUi2 iService;
        private bool iOff;

        public SyncDisplayLedOffLinnCoUkUi2(CpProxyLinnCoUkUi2 aProxy)
        {
            iService = aProxy;
        }
        public bool Off()
        {
            return iOff;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDisplayLedOff(aAsyncHandle, out iOff);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Ui:2 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkUi2 : CpProxy, IDisposable, ICpProxyLinnCoUkUi2
    {
        private Zapp.Core.Action iActionDisplayTestPattern;
        private Zapp.Core.Action iActionDisplayFill;
        private Zapp.Core.Action iActionDisplayClear;
        private Zapp.Core.Action iActionSetTestModeEnabled;
        private Zapp.Core.Action iActionSimulateInfraredInput;
        private Zapp.Core.Action iActionSimulateButtonInput;
        private Zapp.Core.Action iActionSimulateLightSensor;
        private Zapp.Core.Action iActionGetLightSensorData;
        private Zapp.Core.Action iActionSetDisplayBrightness;
        private Zapp.Core.Action iActionSetDisplayBrightnessAuto;
        private Zapp.Core.Action iActionSetInfraredCommands;
        private Zapp.Core.Action iActionInfraredCommands;
        private Zapp.Core.Action iActionSetInfraredTerminalCommands;
        private Zapp.Core.Action iActionInfraredTerminalCommands;
        private Zapp.Core.Action iActionDisplayBrightness;
        private Zapp.Core.Action iActionDisplayBrightnessAuto;
        private Zapp.Core.Action iActionDisplayUpsideDown;
        private Zapp.Core.Action iActionSetDisplayUpsideDown;
        private Zapp.Core.Action iActionSetDisplayScrollText;
        private Zapp.Core.Action iActionDisplayScrollText;
        private Zapp.Core.Action iActionSetDisplaySleep;
        private Zapp.Core.Action iActionDisplaySleep;
        private Zapp.Core.Action iActionSetDisplayLedOff;
        private Zapp.Core.Action iActionDisplayLedOff;
        private PropertyUint iDisplayBrightness;
        private PropertyBool iDisplayBrightnessAuto;
        private PropertyString iInfraredCommands;
        private PropertyString iInfraredTerminalCommands;
        private PropertyBool iDisplayUpsideDown;
        private PropertyBool iDisplayScrollText;
        private PropertyBool iDisplaySleep;
        private PropertyBool iDisplayLedOff;
        private PropertyUint iTerminalInputCode;
        private PropertyString iTerminalInputName;
        private PropertyBinary iDisplayPixels;
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
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkUi2(CpDevice aDevice)
            : base("linn-co-uk", "Ui", 2, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionDisplayTestPattern = new Zapp.Core.Action("DisplayTestPattern");
            param = new ParameterInt("aTestPattern", 0, 6);
            iActionDisplayTestPattern.AddInputParameter(param);

            iActionDisplayFill = new Zapp.Core.Action("DisplayFill");

            iActionDisplayClear = new Zapp.Core.Action("DisplayClear");

            iActionSetTestModeEnabled = new Zapp.Core.Action("SetTestModeEnabled");
            param = new ParameterBool("aEnabled");
            iActionSetTestModeEnabled.AddInputParameter(param);

            iActionSimulateInfraredInput = new Zapp.Core.Action("SimulateInfraredInput");
            param = new ParameterUint("aCode");
            iActionSimulateInfraredInput.AddInputParameter(param);

            iActionSimulateButtonInput = new Zapp.Core.Action("SimulateButtonInput");
            param = new ParameterUint("aCode");
            iActionSimulateButtonInput.AddInputParameter(param);

            iActionSimulateLightSensor = new Zapp.Core.Action("SimulateLightSensor");
            param = new ParameterUint("aLightLevel");
            iActionSimulateLightSensor.AddInputParameter(param);

            iActionGetLightSensorData = new Zapp.Core.Action("GetLightSensorData");
            param = new ParameterUint("aLightLevel");
            iActionGetLightSensorData.AddOutputParameter(param);

            iActionSetDisplayBrightness = new Zapp.Core.Action("SetDisplayBrightness");
            param = new ParameterUint("aBrightness");
            iActionSetDisplayBrightness.AddInputParameter(param);

            iActionSetDisplayBrightnessAuto = new Zapp.Core.Action("SetDisplayBrightnessAuto");
            param = new ParameterBool("aBrightnessAuto");
            iActionSetDisplayBrightnessAuto.AddInputParameter(param);

            iActionSetInfraredCommands = new Zapp.Core.Action("SetInfraredCommands");
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            param = new ParameterString("aCommands", allowedValues);
            iActionSetInfraredCommands.AddInputParameter(param);
            allowedValues.Clear();

            iActionInfraredCommands = new Zapp.Core.Action("InfraredCommands");
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            param = new ParameterString("aCommands", allowedValues);
            iActionInfraredCommands.AddOutputParameter(param);
            allowedValues.Clear();

            iActionSetInfraredTerminalCommands = new Zapp.Core.Action("SetInfraredTerminalCommands");
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            param = new ParameterString("aCommands", allowedValues);
            iActionSetInfraredTerminalCommands.AddInputParameter(param);
            allowedValues.Clear();

            iActionInfraredTerminalCommands = new Zapp.Core.Action("InfraredTerminalCommands");
            allowedValues.Add("None");
            allowedValues.Add("All");
            allowedValues.Add("Cd");
            allowedValues.Add("Dvd");
            param = new ParameterString("aCommands", allowedValues);
            iActionInfraredTerminalCommands.AddOutputParameter(param);
            allowedValues.Clear();

            iActionDisplayBrightness = new Zapp.Core.Action("DisplayBrightness");
            param = new ParameterUint("aBrightness");
            iActionDisplayBrightness.AddOutputParameter(param);

            iActionDisplayBrightnessAuto = new Zapp.Core.Action("DisplayBrightnessAuto");
            param = new ParameterBool("aBrightnessAuto");
            iActionDisplayBrightnessAuto.AddOutputParameter(param);

            iActionDisplayUpsideDown = new Zapp.Core.Action("DisplayUpsideDown");
            param = new ParameterBool("aUpsideDown");
            iActionDisplayUpsideDown.AddOutputParameter(param);

            iActionSetDisplayUpsideDown = new Zapp.Core.Action("SetDisplayUpsideDown");
            param = new ParameterBool("aUpsideDown");
            iActionSetDisplayUpsideDown.AddInputParameter(param);

            iActionSetDisplayScrollText = new Zapp.Core.Action("SetDisplayScrollText");
            param = new ParameterBool("aDisplayScrollText");
            iActionSetDisplayScrollText.AddInputParameter(param);

            iActionDisplayScrollText = new Zapp.Core.Action("DisplayScrollText");
            param = new ParameterBool("aDisplayScrollTextEnabled");
            iActionDisplayScrollText.AddOutputParameter(param);

            iActionSetDisplaySleep = new Zapp.Core.Action("SetDisplaySleep");
            param = new ParameterBool("aEnabled");
            iActionSetDisplaySleep.AddInputParameter(param);

            iActionDisplaySleep = new Zapp.Core.Action("DisplaySleep");
            param = new ParameterBool("aEnabled");
            iActionDisplaySleep.AddOutputParameter(param);

            iActionSetDisplayLedOff = new Zapp.Core.Action("SetDisplayLedOff");
            param = new ParameterBool("aOff");
            iActionSetDisplayLedOff.AddInputParameter(param);

            iActionDisplayLedOff = new Zapp.Core.Action("DisplayLedOff");
            param = new ParameterBool("aOff");
            iActionDisplayLedOff.AddOutputParameter(param);

            iDisplayBrightness = new PropertyUint("DisplayBrightness", DisplayBrightnessPropertyChanged);
            AddProperty(iDisplayBrightness);
            iDisplayBrightnessAuto = new PropertyBool("DisplayBrightnessAuto", DisplayBrightnessAutoPropertyChanged);
            AddProperty(iDisplayBrightnessAuto);
            iInfraredCommands = new PropertyString("InfraredCommands", InfraredCommandsPropertyChanged);
            AddProperty(iInfraredCommands);
            iInfraredTerminalCommands = new PropertyString("InfraredTerminalCommands", InfraredTerminalCommandsPropertyChanged);
            AddProperty(iInfraredTerminalCommands);
            iDisplayUpsideDown = new PropertyBool("DisplayUpsideDown", DisplayUpsideDownPropertyChanged);
            AddProperty(iDisplayUpsideDown);
            iDisplayScrollText = new PropertyBool("DisplayScrollText", DisplayScrollTextPropertyChanged);
            AddProperty(iDisplayScrollText);
            iDisplaySleep = new PropertyBool("DisplaySleep", DisplaySleepPropertyChanged);
            AddProperty(iDisplaySleep);
            iDisplayLedOff = new PropertyBool("DisplayLedOff", DisplayLedOffPropertyChanged);
            AddProperty(iDisplayLedOff);
            iTerminalInputCode = new PropertyUint("TerminalInputCode", TerminalInputCodePropertyChanged);
            AddProperty(iTerminalInputCode);
            iTerminalInputName = new PropertyString("TerminalInputName", TerminalInputNamePropertyChanged);
            AddProperty(iTerminalInputName);
            iDisplayPixels = new PropertyBinary("DisplayPixels", DisplayPixelsPropertyChanged);
            AddProperty(iDisplayPixels);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTestPattern"></param>
        public void SyncDisplayTestPattern(int aTestPattern)
        {
            SyncDisplayTestPatternLinnCoUkUi2 sync = new SyncDisplayTestPatternLinnCoUkUi2(this);
            BeginDisplayTestPattern(aTestPattern, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginDisplayTestPattern(int aTestPattern, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayTestPattern, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionDisplayTestPattern.InputParameter(inIndex++), aTestPattern));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDisplayTestPattern(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncDisplayFill()
        {
            SyncDisplayFillLinnCoUkUi2 sync = new SyncDisplayFillLinnCoUkUi2(this);
            BeginDisplayFill(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayFill().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayFill(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayFill, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDisplayFill(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncDisplayClear()
        {
            SyncDisplayClearLinnCoUkUi2 sync = new SyncDisplayClearLinnCoUkUi2(this);
            BeginDisplayClear(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayClear().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayClear(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayClear, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDisplayClear(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncSetTestModeEnabled(bool aEnabled)
        {
            SyncSetTestModeEnabledLinnCoUkUi2 sync = new SyncSetTestModeEnabledLinnCoUkUi2(this);
            BeginSetTestModeEnabled(aEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetTestModeEnabled(bool aEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetTestModeEnabled, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetTestModeEnabled.InputParameter(inIndex++), aEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetTestModeEnabled(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCode"></param>
        public void SyncSimulateInfraredInput(uint aCode)
        {
            SyncSimulateInfraredInputLinnCoUkUi2 sync = new SyncSimulateInfraredInputLinnCoUkUi2(this);
            BeginSimulateInfraredInput(aCode, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSimulateInfraredInput(uint aCode, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSimulateInfraredInput, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSimulateInfraredInput.InputParameter(inIndex++), aCode));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSimulateInfraredInput(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCode"></param>
        public void SyncSimulateButtonInput(uint aCode)
        {
            SyncSimulateButtonInputLinnCoUkUi2 sync = new SyncSimulateButtonInputLinnCoUkUi2(this);
            BeginSimulateButtonInput(aCode, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSimulateButtonInput(uint aCode, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSimulateButtonInput, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSimulateButtonInput.InputParameter(inIndex++), aCode));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSimulateButtonInput(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLightLevel"></param>
        public void SyncSimulateLightSensor(uint aLightLevel)
        {
            SyncSimulateLightSensorLinnCoUkUi2 sync = new SyncSimulateLightSensorLinnCoUkUi2(this);
            BeginSimulateLightSensor(aLightLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSimulateLightSensor(uint aLightLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSimulateLightSensor, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSimulateLightSensor.InputParameter(inIndex++), aLightLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSimulateLightSensor(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLightLevel"></param>
        public void SyncGetLightSensorData(out uint aLightLevel)
        {
            SyncGetLightSensorDataLinnCoUkUi2 sync = new SyncGetLightSensorDataLinnCoUkUi2(this);
            BeginGetLightSensorData(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aLightLevel = sync.LightLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLightSensorData().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLightSensorData(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLightSensorData, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLightSensorData.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaLightLevel"></param>
        public void EndGetLightSensorData(IntPtr aAsyncHandle, out uint aLightLevel)
        {
            uint index = 0;
            aLightLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightness"></param>
        public void SyncSetDisplayBrightness(uint aBrightness)
        {
            SyncSetDisplayBrightnessLinnCoUkUi2 sync = new SyncSetDisplayBrightnessLinnCoUkUi2(this);
            BeginSetDisplayBrightness(aBrightness, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplayBrightness(uint aBrightness, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplayBrightness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetDisplayBrightness.InputParameter(inIndex++), aBrightness));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplayBrightness(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightnessAuto"></param>
        public void SyncSetDisplayBrightnessAuto(bool aBrightnessAuto)
        {
            SyncSetDisplayBrightnessAutoLinnCoUkUi2 sync = new SyncSetDisplayBrightnessAutoLinnCoUkUi2(this);
            BeginSetDisplayBrightnessAuto(aBrightnessAuto, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplayBrightnessAuto(bool aBrightnessAuto, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplayBrightnessAuto, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDisplayBrightnessAuto.InputParameter(inIndex++), aBrightnessAuto));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplayBrightnessAuto(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public void SyncSetInfraredCommands(String aCommands)
        {
            SyncSetInfraredCommandsLinnCoUkUi2 sync = new SyncSetInfraredCommandsLinnCoUkUi2(this);
            BeginSetInfraredCommands(aCommands, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetInfraredCommands(String aCommands, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetInfraredCommands, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetInfraredCommands.InputParameter(inIndex++), aCommands));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetInfraredCommands(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public void SyncInfraredCommands(out String aCommands)
        {
            SyncInfraredCommandsLinnCoUkUi2 sync = new SyncInfraredCommandsLinnCoUkUi2(this);
            BeginInfraredCommands(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCommands = sync.Commands();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInfraredCommands().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginInfraredCommands(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionInfraredCommands, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionInfraredCommands.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCommands"></param>
        public void EndInfraredCommands(IntPtr aAsyncHandle, out String aCommands)
        {
            uint index = 0;
            aCommands = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public void SyncSetInfraredTerminalCommands(String aCommands)
        {
            SyncSetInfraredTerminalCommandsLinnCoUkUi2 sync = new SyncSetInfraredTerminalCommandsLinnCoUkUi2(this);
            BeginSetInfraredTerminalCommands(aCommands, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetInfraredTerminalCommands(String aCommands, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetInfraredTerminalCommands, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetInfraredTerminalCommands.InputParameter(inIndex++), aCommands));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetInfraredTerminalCommands(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCommands"></param>
        public void SyncInfraredTerminalCommands(out String aCommands)
        {
            SyncInfraredTerminalCommandsLinnCoUkUi2 sync = new SyncInfraredTerminalCommandsLinnCoUkUi2(this);
            BeginInfraredTerminalCommands(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCommands = sync.Commands();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInfraredTerminalCommands().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginInfraredTerminalCommands(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionInfraredTerminalCommands, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionInfraredTerminalCommands.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCommands"></param>
        public void EndInfraredTerminalCommands(IntPtr aAsyncHandle, out String aCommands)
        {
            uint index = 0;
            aCommands = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightness"></param>
        public void SyncDisplayBrightness(out uint aBrightness)
        {
            SyncDisplayBrightnessLinnCoUkUi2 sync = new SyncDisplayBrightnessLinnCoUkUi2(this);
            BeginDisplayBrightness(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aBrightness = sync.Brightness();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayBrightness().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayBrightness(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayBrightness, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDisplayBrightness.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBrightness"></param>
        public void EndDisplayBrightness(IntPtr aAsyncHandle, out uint aBrightness)
        {
            uint index = 0;
            aBrightness = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBrightnessAuto"></param>
        public void SyncDisplayBrightnessAuto(out bool aBrightnessAuto)
        {
            SyncDisplayBrightnessAutoLinnCoUkUi2 sync = new SyncDisplayBrightnessAutoLinnCoUkUi2(this);
            BeginDisplayBrightnessAuto(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aBrightnessAuto = sync.BrightnessAuto();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayBrightnessAuto().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayBrightnessAuto(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayBrightnessAuto, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDisplayBrightnessAuto.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBrightnessAuto"></param>
        public void EndDisplayBrightnessAuto(IntPtr aAsyncHandle, out bool aBrightnessAuto)
        {
            uint index = 0;
            aBrightnessAuto = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUpsideDown"></param>
        public void SyncDisplayUpsideDown(out bool aUpsideDown)
        {
            SyncDisplayUpsideDownLinnCoUkUi2 sync = new SyncDisplayUpsideDownLinnCoUkUi2(this);
            BeginDisplayUpsideDown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aUpsideDown = sync.UpsideDown();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayUpsideDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayUpsideDown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayUpsideDown, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDisplayUpsideDown.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUpsideDown"></param>
        public void EndDisplayUpsideDown(IntPtr aAsyncHandle, out bool aUpsideDown)
        {
            uint index = 0;
            aUpsideDown = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUpsideDown"></param>
        public void SyncSetDisplayUpsideDown(bool aUpsideDown)
        {
            SyncSetDisplayUpsideDownLinnCoUkUi2 sync = new SyncSetDisplayUpsideDownLinnCoUkUi2(this);
            BeginSetDisplayUpsideDown(aUpsideDown, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplayUpsideDown(bool aUpsideDown, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplayUpsideDown, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDisplayUpsideDown.InputParameter(inIndex++), aUpsideDown));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplayUpsideDown(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDisplayScrollText"></param>
        public void SyncSetDisplayScrollText(bool aDisplayScrollText)
        {
            SyncSetDisplayScrollTextLinnCoUkUi2 sync = new SyncSetDisplayScrollTextLinnCoUkUi2(this);
            BeginSetDisplayScrollText(aDisplayScrollText, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplayScrollText(bool aDisplayScrollText, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplayScrollText, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDisplayScrollText.InputParameter(inIndex++), aDisplayScrollText));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplayScrollText(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDisplayScrollTextEnabled"></param>
        public void SyncDisplayScrollText(out bool aDisplayScrollTextEnabled)
        {
            SyncDisplayScrollTextLinnCoUkUi2 sync = new SyncDisplayScrollTextLinnCoUkUi2(this);
            BeginDisplayScrollText(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDisplayScrollTextEnabled = sync.DisplayScrollTextEnabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayScrollText().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayScrollText(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayScrollText, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDisplayScrollText.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDisplayScrollTextEnabled"></param>
        public void EndDisplayScrollText(IntPtr aAsyncHandle, out bool aDisplayScrollTextEnabled)
        {
            uint index = 0;
            aDisplayScrollTextEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncSetDisplaySleep(bool aEnabled)
        {
            SyncSetDisplaySleepLinnCoUkUi2 sync = new SyncSetDisplaySleepLinnCoUkUi2(this);
            BeginSetDisplaySleep(aEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplaySleep(bool aEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplaySleep, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDisplaySleep.InputParameter(inIndex++), aEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplaySleep(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncDisplaySleep(out bool aEnabled)
        {
            SyncDisplaySleepLinnCoUkUi2 sync = new SyncDisplaySleepLinnCoUkUi2(this);
            BeginDisplaySleep(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aEnabled = sync.Enabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplaySleep().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplaySleep(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplaySleep, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDisplaySleep.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
        public void EndDisplaySleep(IntPtr aAsyncHandle, out bool aEnabled)
        {
            uint index = 0;
            aEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOff"></param>
        public void SyncSetDisplayLedOff(bool aOff)
        {
            SyncSetDisplayLedOffLinnCoUkUi2 sync = new SyncSetDisplayLedOffLinnCoUkUi2(this);
            BeginSetDisplayLedOff(aOff, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
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
        public void BeginSetDisplayLedOff(bool aOff, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDisplayLedOff, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDisplayLedOff.InputParameter(inIndex++), aOff));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDisplayLedOff(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOff"></param>
        public void SyncDisplayLedOff(out bool aOff)
        {
            SyncDisplayLedOffLinnCoUkUi2 sync = new SyncDisplayLedOffLinnCoUkUi2(this);
            BeginDisplayLedOff(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aOff = sync.Off();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDisplayLedOff().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDisplayLedOff(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDisplayLedOff, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDisplayLedOff.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOff"></param>
        public void EndDisplayLedOff(IntPtr aAsyncHandle, out bool aOff)
        {
            uint index = 0;
            aOff = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayBrightness state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayBrightnessChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayBrightnessChanged(CallbackPropertyChanged aDisplayBrightnessChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayBrightnessChanged = aDisplayBrightnessChanged;
            }
        }

        private void DisplayBrightnessPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayBrightnessChanged != null)
                {
                    iDisplayBrightnessChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayBrightnessAuto state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayBrightnessAutoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayBrightnessAutoChanged(CallbackPropertyChanged aDisplayBrightnessAutoChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayBrightnessAutoChanged = aDisplayBrightnessAutoChanged;
            }
        }

        private void DisplayBrightnessAutoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayBrightnessAutoChanged != null)
                {
                    iDisplayBrightnessAutoChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the InfraredCommands state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aInfraredCommandsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyInfraredCommandsChanged(CallbackPropertyChanged aInfraredCommandsChanged)
        {
            lock (iPropertyLock)
            {
                iInfraredCommandsChanged = aInfraredCommandsChanged;
            }
        }

        private void InfraredCommandsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iInfraredCommandsChanged != null)
                {
                    iInfraredCommandsChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the InfraredTerminalCommands state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aInfraredTerminalCommandsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyInfraredTerminalCommandsChanged(CallbackPropertyChanged aInfraredTerminalCommandsChanged)
        {
            lock (iPropertyLock)
            {
                iInfraredTerminalCommandsChanged = aInfraredTerminalCommandsChanged;
            }
        }

        private void InfraredTerminalCommandsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iInfraredTerminalCommandsChanged != null)
                {
                    iInfraredTerminalCommandsChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayUpsideDown state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayUpsideDownChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayUpsideDownChanged(CallbackPropertyChanged aDisplayUpsideDownChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayUpsideDownChanged = aDisplayUpsideDownChanged;
            }
        }

        private void DisplayUpsideDownPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayUpsideDownChanged != null)
                {
                    iDisplayUpsideDownChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayScrollText state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayScrollTextChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayScrollTextChanged(CallbackPropertyChanged aDisplayScrollTextChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayScrollTextChanged = aDisplayScrollTextChanged;
            }
        }

        private void DisplayScrollTextPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayScrollTextChanged != null)
                {
                    iDisplayScrollTextChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplaySleep state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplaySleepChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplaySleepChanged(CallbackPropertyChanged aDisplaySleepChanged)
        {
            lock (iPropertyLock)
            {
                iDisplaySleepChanged = aDisplaySleepChanged;
            }
        }

        private void DisplaySleepPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplaySleepChanged != null)
                {
                    iDisplaySleepChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayLedOff state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayLedOffChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayLedOffChanged(CallbackPropertyChanged aDisplayLedOffChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayLedOffChanged = aDisplayLedOffChanged;
            }
        }

        private void DisplayLedOffPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayLedOffChanged != null)
                {
                    iDisplayLedOffChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TerminalInputCode state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aTerminalInputCodeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTerminalInputCodeChanged(CallbackPropertyChanged aTerminalInputCodeChanged)
        {
            lock (iPropertyLock)
            {
                iTerminalInputCodeChanged = aTerminalInputCodeChanged;
            }
        }

        private void TerminalInputCodePropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iTerminalInputCodeChanged != null)
                {
                    iTerminalInputCodeChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TerminalInputName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aTerminalInputNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTerminalInputNameChanged(CallbackPropertyChanged aTerminalInputNameChanged)
        {
            lock (iPropertyLock)
            {
                iTerminalInputNameChanged = aTerminalInputNameChanged;
            }
        }

        private void TerminalInputNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iTerminalInputNameChanged != null)
                {
                    iTerminalInputNameChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DisplayPixels state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkUi2 instance will not overlap.</remarks>
        /// <param name="aDisplayPixelsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDisplayPixelsChanged(CallbackPropertyChanged aDisplayPixelsChanged)
        {
            lock (iPropertyLock)
            {
                iDisplayPixelsChanged = aDisplayPixelsChanged;
            }
        }

        private void DisplayPixelsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iDisplayPixelsChanged != null)
                {
                    iDisplayPixelsChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the DisplayBrightness property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayBrightness">Will be set to the value of the property</param>
        public uint PropertyDisplayBrightness()
        {
            return iDisplayBrightness.Value();
        }

        /// <summary>
        /// Query the value of the DisplayBrightnessAuto property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayBrightnessAuto">Will be set to the value of the property</param>
        public bool PropertyDisplayBrightnessAuto()
        {
            return iDisplayBrightnessAuto.Value();
        }

        /// <summary>
        /// Query the value of the InfraredCommands property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aInfraredCommands">Will be set to the value of the property</param>
        public String PropertyInfraredCommands()
        {
            return iInfraredCommands.Value();
        }

        /// <summary>
        /// Query the value of the InfraredTerminalCommands property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aInfraredTerminalCommands">Will be set to the value of the property</param>
        public String PropertyInfraredTerminalCommands()
        {
            return iInfraredTerminalCommands.Value();
        }

        /// <summary>
        /// Query the value of the DisplayUpsideDown property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayUpsideDown">Will be set to the value of the property</param>
        public bool PropertyDisplayUpsideDown()
        {
            return iDisplayUpsideDown.Value();
        }

        /// <summary>
        /// Query the value of the DisplayScrollText property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayScrollText">Will be set to the value of the property</param>
        public bool PropertyDisplayScrollText()
        {
            return iDisplayScrollText.Value();
        }

        /// <summary>
        /// Query the value of the DisplaySleep property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplaySleep">Will be set to the value of the property</param>
        public bool PropertyDisplaySleep()
        {
            return iDisplaySleep.Value();
        }

        /// <summary>
        /// Query the value of the DisplayLedOff property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayLedOff">Will be set to the value of the property</param>
        public bool PropertyDisplayLedOff()
        {
            return iDisplayLedOff.Value();
        }

        /// <summary>
        /// Query the value of the TerminalInputCode property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTerminalInputCode">Will be set to the value of the property</param>
        public uint PropertyTerminalInputCode()
        {
            return iTerminalInputCode.Value();
        }

        /// <summary>
        /// Query the value of the TerminalInputName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTerminalInputName">Will be set to the value of the property</param>
        public String PropertyTerminalInputName()
        {
            return iTerminalInputName.Value();
        }

        /// <summary>
        /// Query the value of the DisplayPixels property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDisplayPixels">Will be set to the value of the property</param>
        public String PropertyDisplayPixels()
        {
            return iDisplayPixels.Value();
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
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionDisplayTestPattern.Dispose();
                iActionDisplayFill.Dispose();
                iActionDisplayClear.Dispose();
                iActionSetTestModeEnabled.Dispose();
                iActionSimulateInfraredInput.Dispose();
                iActionSimulateButtonInput.Dispose();
                iActionSimulateLightSensor.Dispose();
                iActionGetLightSensorData.Dispose();
                iActionSetDisplayBrightness.Dispose();
                iActionSetDisplayBrightnessAuto.Dispose();
                iActionSetInfraredCommands.Dispose();
                iActionInfraredCommands.Dispose();
                iActionSetInfraredTerminalCommands.Dispose();
                iActionInfraredTerminalCommands.Dispose();
                iActionDisplayBrightness.Dispose();
                iActionDisplayBrightnessAuto.Dispose();
                iActionDisplayUpsideDown.Dispose();
                iActionSetDisplayUpsideDown.Dispose();
                iActionSetDisplayScrollText.Dispose();
                iActionDisplayScrollText.Dispose();
                iActionSetDisplaySleep.Dispose();
                iActionDisplaySleep.Dispose();
                iActionSetDisplayLedOff.Dispose();
                iActionDisplayLedOff.Dispose();
                iDisplayBrightness.Dispose();
                iDisplayBrightnessAuto.Dispose();
                iInfraredCommands.Dispose();
                iInfraredTerminalCommands.Dispose();
                iDisplayUpsideDown.Dispose();
                iDisplayScrollText.Dispose();
                iDisplaySleep.Dispose();
                iDisplayLedOff.Dispose();
                iTerminalInputCode.Dispose();
                iTerminalInputName.Dispose();
                iDisplayPixels.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

