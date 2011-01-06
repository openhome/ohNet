using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkComponent1 : ICpProxy, IDisposable
    {
        void SyncAmplifierEnabled(out bool aEnabled);
        void BeginAmplifierEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierEnabled(IntPtr aAsyncHandle, out bool aEnabled);
        void SyncSetAmplifierEnabled(bool aEnabled);
        void BeginSetAmplifierEnabled(bool aEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAmplifierEnabled(IntPtr aAsyncHandle);
        void SyncAmplifierAttenuation(out String aAttenuation);
        void BeginAmplifierAttenuation(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierAttenuation(IntPtr aAsyncHandle, out String aAttenuation);
        void SyncSetAmplifierAttenuation(String aAttenuation);
        void BeginSetAmplifierAttenuation(String aAttenuation, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAmplifierAttenuation(IntPtr aAsyncHandle);
        void SyncSetVolumeControlEnabled(bool aEnabled);
        void BeginSetVolumeControlEnabled(bool aEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolumeControlEnabled(IntPtr aAsyncHandle);
        void SyncVolumeControlEnabled(out bool aEnabled);
        void BeginVolumeControlEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeControlEnabled(IntPtr aAsyncHandle, out bool aEnabled);
        void SyncSetDigitalAudioOutputRaw(bool aRaw);
        void BeginSetDigitalAudioOutputRaw(bool aRaw, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDigitalAudioOutputRaw(IntPtr aAsyncHandle);
        void SyncDigitalAudioOutputRaw(out bool aRaw);
        void BeginDigitalAudioOutputRaw(CpProxy.CallbackAsyncComplete aCallback);
        void EndDigitalAudioOutputRaw(IntPtr aAsyncHandle, out bool aRaw);
        void SyncAmplifierOverTemperature(out bool aOverTemperature);
        void BeginAmplifierOverTemperature(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierOverTemperature(IntPtr aAsyncHandle, out bool aOverTemperature);
        void SyncEthernetLinkConnected(out bool aLinkConnected);
        void BeginEthernetLinkConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndEthernetLinkConnected(IntPtr aAsyncHandle, out bool aLinkConnected);
        void SyncLocate();
        void BeginLocate(CpProxy.CallbackAsyncComplete aCallback);
        void EndLocate(IntPtr aAsyncHandle);
        void SetPropertyAmplifierEnabledChanged(CpProxy.CallbackPropertyChanged aAmplifierEnabledChanged);
        bool PropertyAmplifierEnabled();
        void SetPropertyAmplifierAttenuationChanged(CpProxy.CallbackPropertyChanged aAmplifierAttenuationChanged);
        String PropertyAmplifierAttenuation();
        void SetPropertyVolumeControlEnabledChanged(CpProxy.CallbackPropertyChanged aVolumeControlEnabledChanged);
        bool PropertyVolumeControlEnabled();
        void SetPropertyDigitalAudioOutputRawChanged(CpProxy.CallbackPropertyChanged aDigitalAudioOutputRawChanged);
        bool PropertyDigitalAudioOutputRaw();
    }

    internal class SyncAmplifierEnabledLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private bool iEnabled;

        public SyncAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public bool Enabled()
        {
            return iEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndAmplifierEnabled(aAsyncHandle, out iEnabled);
        }
    };

    internal class SyncSetAmplifierEnabledLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;

        public SyncSetAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetAmplifierEnabled(aAsyncHandle);
        }
    };

    internal class SyncAmplifierAttenuationLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private String iAttenuation;

        public SyncAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public String Attenuation()
        {
            return iAttenuation;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndAmplifierAttenuation(aAsyncHandle, out iAttenuation);
        }
    };

    internal class SyncSetAmplifierAttenuationLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;

        public SyncSetAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetAmplifierAttenuation(aAsyncHandle);
        }
    };

    internal class SyncSetVolumeControlEnabledLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;

        public SyncSetVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolumeControlEnabled(aAsyncHandle);
        }
    };

    internal class SyncVolumeControlEnabledLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private bool iEnabled;

        public SyncVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public bool Enabled()
        {
            return iEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeControlEnabled(aAsyncHandle, out iEnabled);
        }
    };

    internal class SyncSetDigitalAudioOutputRawLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;

        public SyncSetDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDigitalAudioOutputRaw(aAsyncHandle);
        }
    };

    internal class SyncDigitalAudioOutputRawLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private bool iRaw;

        public SyncDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public bool Raw()
        {
            return iRaw;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDigitalAudioOutputRaw(aAsyncHandle, out iRaw);
        }
    };

    internal class SyncAmplifierOverTemperatureLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private bool iOverTemperature;

        public SyncAmplifierOverTemperatureLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public bool OverTemperature()
        {
            return iOverTemperature;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndAmplifierOverTemperature(aAsyncHandle, out iOverTemperature);
        }
    };

    internal class SyncEthernetLinkConnectedLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;
        private bool iLinkConnected;

        public SyncEthernetLinkConnectedLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        public bool LinkConnected()
        {
            return iLinkConnected;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndEthernetLinkConnected(aAsyncHandle, out iLinkConnected);
        }
    };

    internal class SyncLocateLinnCoUkComponent1 : SyncProxyAction
    {
        private CpProxyLinnCoUkComponent1 iService;

        public SyncLocateLinnCoUkComponent1(CpProxyLinnCoUkComponent1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndLocate(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Component:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkComponent1 : CpProxy, IDisposable, ICpProxyLinnCoUkComponent1
    {
        private Zapp.Core.Action iActionAmplifierEnabled;
        private Zapp.Core.Action iActionSetAmplifierEnabled;
        private Zapp.Core.Action iActionAmplifierAttenuation;
        private Zapp.Core.Action iActionSetAmplifierAttenuation;
        private Zapp.Core.Action iActionSetVolumeControlEnabled;
        private Zapp.Core.Action iActionVolumeControlEnabled;
        private Zapp.Core.Action iActionSetDigitalAudioOutputRaw;
        private Zapp.Core.Action iActionDigitalAudioOutputRaw;
        private Zapp.Core.Action iActionAmplifierOverTemperature;
        private Zapp.Core.Action iActionEthernetLinkConnected;
        private Zapp.Core.Action iActionLocate;
        private PropertyBool iAmplifierEnabled;
        private PropertyString iAmplifierAttenuation;
        private PropertyBool iVolumeControlEnabled;
        private PropertyBool iDigitalAudioOutputRaw;
        private CallbackPropertyChanged iAmplifierEnabledChanged;
        private CallbackPropertyChanged iAmplifierAttenuationChanged;
        private CallbackPropertyChanged iVolumeControlEnabledChanged;
        private CallbackPropertyChanged iDigitalAudioOutputRawChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkComponent1(CpDevice aDevice)
            : base("linn-co-uk", "Component", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionAmplifierEnabled = new Zapp.Core.Action("AmplifierEnabled");
            param = new ParameterBool("aEnabled");
            iActionAmplifierEnabled.AddOutputParameter(param);

            iActionSetAmplifierEnabled = new Zapp.Core.Action("SetAmplifierEnabled");
            param = new ParameterBool("aEnabled");
            iActionSetAmplifierEnabled.AddInputParameter(param);

            iActionAmplifierAttenuation = new Zapp.Core.Action("AmplifierAttenuation");
            allowedValues.Add("-12dB");
            allowedValues.Add("-9dB");
            allowedValues.Add("-6dB");
            allowedValues.Add("0dB");
            param = new ParameterString("aAttenuation", allowedValues);
            iActionAmplifierAttenuation.AddOutputParameter(param);
            allowedValues.Clear();

            iActionSetAmplifierAttenuation = new Zapp.Core.Action("SetAmplifierAttenuation");
            allowedValues.Add("-12dB");
            allowedValues.Add("-9dB");
            allowedValues.Add("-6dB");
            allowedValues.Add("0dB");
            param = new ParameterString("aAttenuation", allowedValues);
            iActionSetAmplifierAttenuation.AddInputParameter(param);
            allowedValues.Clear();

            iActionSetVolumeControlEnabled = new Zapp.Core.Action("SetVolumeControlEnabled");
            param = new ParameterBool("aEnabled");
            iActionSetVolumeControlEnabled.AddInputParameter(param);

            iActionVolumeControlEnabled = new Zapp.Core.Action("VolumeControlEnabled");
            param = new ParameterBool("aEnabled");
            iActionVolumeControlEnabled.AddOutputParameter(param);

            iActionSetDigitalAudioOutputRaw = new Zapp.Core.Action("SetDigitalAudioOutputRaw");
            param = new ParameterBool("aRaw");
            iActionSetDigitalAudioOutputRaw.AddInputParameter(param);

            iActionDigitalAudioOutputRaw = new Zapp.Core.Action("DigitalAudioOutputRaw");
            param = new ParameterBool("aRaw");
            iActionDigitalAudioOutputRaw.AddOutputParameter(param);

            iActionAmplifierOverTemperature = new Zapp.Core.Action("AmplifierOverTemperature");
            param = new ParameterBool("aOverTemperature");
            iActionAmplifierOverTemperature.AddOutputParameter(param);

            iActionEthernetLinkConnected = new Zapp.Core.Action("EthernetLinkConnected");
            param = new ParameterBool("aLinkConnected");
            iActionEthernetLinkConnected.AddOutputParameter(param);

            iActionLocate = new Zapp.Core.Action("Locate");

            iAmplifierEnabled = new PropertyBool("AmplifierEnabled", AmplifierEnabledPropertyChanged);
            AddProperty(iAmplifierEnabled);
            iAmplifierAttenuation = new PropertyString("AmplifierAttenuation", AmplifierAttenuationPropertyChanged);
            AddProperty(iAmplifierAttenuation);
            iVolumeControlEnabled = new PropertyBool("VolumeControlEnabled", VolumeControlEnabledPropertyChanged);
            AddProperty(iVolumeControlEnabled);
            iDigitalAudioOutputRaw = new PropertyBool("DigitalAudioOutputRaw", DigitalAudioOutputRawPropertyChanged);
            AddProperty(iDigitalAudioOutputRaw);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncAmplifierEnabled(out bool aEnabled)
        {
            SyncAmplifierEnabledLinnCoUkComponent1 sync = new SyncAmplifierEnabledLinnCoUkComponent1(this);
            BeginAmplifierEnabled(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aEnabled = sync.Enabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginAmplifierEnabled(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionAmplifierEnabled, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionAmplifierEnabled.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
        public void EndAmplifierEnabled(IntPtr aAsyncHandle, out bool aEnabled)
        {
            uint index = 0;
            aEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncSetAmplifierEnabled(bool aEnabled)
        {
            SyncSetAmplifierEnabledLinnCoUkComponent1 sync = new SyncSetAmplifierEnabledLinnCoUkComponent1(this);
            BeginSetAmplifierEnabled(aEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAmplifierEnabled().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetAmplifierEnabled(bool aEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetAmplifierEnabled, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetAmplifierEnabled.InputParameter(inIndex++), aEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetAmplifierEnabled(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAttenuation"></param>
        public void SyncAmplifierAttenuation(out String aAttenuation)
        {
            SyncAmplifierAttenuationLinnCoUkComponent1 sync = new SyncAmplifierAttenuationLinnCoUkComponent1(this);
            BeginAmplifierAttenuation(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aAttenuation = sync.Attenuation();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierAttenuation().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginAmplifierAttenuation(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionAmplifierAttenuation, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionAmplifierAttenuation.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaAttenuation"></param>
        public void EndAmplifierAttenuation(IntPtr aAsyncHandle, out String aAttenuation)
        {
            uint index = 0;
            aAttenuation = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAttenuation"></param>
        public void SyncSetAmplifierAttenuation(String aAttenuation)
        {
            SyncSetAmplifierAttenuationLinnCoUkComponent1 sync = new SyncSetAmplifierAttenuationLinnCoUkComponent1(this);
            BeginSetAmplifierAttenuation(aAttenuation, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAmplifierAttenuation().</remarks>
        /// <param name="aaAttenuation"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetAmplifierAttenuation(String aAttenuation, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetAmplifierAttenuation, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetAmplifierAttenuation.InputParameter(inIndex++), aAttenuation));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetAmplifierAttenuation(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncSetVolumeControlEnabled(bool aEnabled)
        {
            SyncSetVolumeControlEnabledLinnCoUkComponent1 sync = new SyncSetVolumeControlEnabledLinnCoUkComponent1(this);
            BeginSetVolumeControlEnabled(aEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolumeControlEnabled().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolumeControlEnabled(bool aEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolumeControlEnabled, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetVolumeControlEnabled.InputParameter(inIndex++), aEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolumeControlEnabled(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public void SyncVolumeControlEnabled(out bool aEnabled)
        {
            SyncVolumeControlEnabledLinnCoUkComponent1 sync = new SyncVolumeControlEnabledLinnCoUkComponent1(this);
            BeginVolumeControlEnabled(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aEnabled = sync.Enabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeControlEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginVolumeControlEnabled(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionVolumeControlEnabled, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionVolumeControlEnabled.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
        public void EndVolumeControlEnabled(IntPtr aAsyncHandle, out bool aEnabled)
        {
            uint index = 0;
            aEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRaw"></param>
        public void SyncSetDigitalAudioOutputRaw(bool aRaw)
        {
            SyncSetDigitalAudioOutputRawLinnCoUkComponent1 sync = new SyncSetDigitalAudioOutputRawLinnCoUkComponent1(this);
            BeginSetDigitalAudioOutputRaw(aRaw, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDigitalAudioOutputRaw().</remarks>
        /// <param name="aaRaw"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetDigitalAudioOutputRaw(bool aRaw, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDigitalAudioOutputRaw, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetDigitalAudioOutputRaw.InputParameter(inIndex++), aRaw));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDigitalAudioOutputRaw(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRaw"></param>
        public void SyncDigitalAudioOutputRaw(out bool aRaw)
        {
            SyncDigitalAudioOutputRawLinnCoUkComponent1 sync = new SyncDigitalAudioOutputRawLinnCoUkComponent1(this);
            BeginDigitalAudioOutputRaw(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRaw = sync.Raw();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDigitalAudioOutputRaw().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDigitalAudioOutputRaw(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDigitalAudioOutputRaw, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDigitalAudioOutputRaw.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRaw"></param>
        public void EndDigitalAudioOutputRaw(IntPtr aAsyncHandle, out bool aRaw)
        {
            uint index = 0;
            aRaw = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOverTemperature"></param>
        public void SyncAmplifierOverTemperature(out bool aOverTemperature)
        {
            SyncAmplifierOverTemperatureLinnCoUkComponent1 sync = new SyncAmplifierOverTemperatureLinnCoUkComponent1(this);
            BeginAmplifierOverTemperature(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aOverTemperature = sync.OverTemperature();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierOverTemperature().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginAmplifierOverTemperature(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionAmplifierOverTemperature, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionAmplifierOverTemperature.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOverTemperature"></param>
        public void EndAmplifierOverTemperature(IntPtr aAsyncHandle, out bool aOverTemperature)
        {
            uint index = 0;
            aOverTemperature = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLinkConnected"></param>
        public void SyncEthernetLinkConnected(out bool aLinkConnected)
        {
            SyncEthernetLinkConnectedLinnCoUkComponent1 sync = new SyncEthernetLinkConnectedLinnCoUkComponent1(this);
            BeginEthernetLinkConnected(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aLinkConnected = sync.LinkConnected();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEthernetLinkConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginEthernetLinkConnected(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionEthernetLinkConnected, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionEthernetLinkConnected.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaLinkConnected"></param>
        public void EndEthernetLinkConnected(IntPtr aAsyncHandle, out bool aLinkConnected)
        {
            uint index = 0;
            aLinkConnected = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncLocate()
        {
            SyncLocateLinnCoUkComponent1 sync = new SyncLocateLinnCoUkComponent1(this);
            BeginLocate(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLocate().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginLocate(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionLocate, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndLocate(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Set a delegate to be run when the AmplifierEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aAmplifierEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAmplifierEnabledChanged(CallbackPropertyChanged aAmplifierEnabledChanged)
        {
            lock (this)
            {
                iAmplifierEnabledChanged = aAmplifierEnabledChanged;
            }
        }

        private void AmplifierEnabledPropertyChanged()
        {
            lock (this)
            {
                if (iAmplifierEnabledChanged != null)
                {
                    iAmplifierEnabledChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the AmplifierAttenuation state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aAmplifierAttenuationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAmplifierAttenuationChanged(CallbackPropertyChanged aAmplifierAttenuationChanged)
        {
            lock (this)
            {
                iAmplifierAttenuationChanged = aAmplifierAttenuationChanged;
            }
        }

        private void AmplifierAttenuationPropertyChanged()
        {
            lock (this)
            {
                if (iAmplifierAttenuationChanged != null)
                {
                    iAmplifierAttenuationChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeControlEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aVolumeControlEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeControlEnabledChanged(CallbackPropertyChanged aVolumeControlEnabledChanged)
        {
            lock (this)
            {
                iVolumeControlEnabledChanged = aVolumeControlEnabledChanged;
            }
        }

        private void VolumeControlEnabledPropertyChanged()
        {
            lock (this)
            {
                if (iVolumeControlEnabledChanged != null)
                {
                    iVolumeControlEnabledChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DigitalAudioOutputRaw state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aDigitalAudioOutputRawChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDigitalAudioOutputRawChanged(CallbackPropertyChanged aDigitalAudioOutputRawChanged)
        {
            lock (this)
            {
                iDigitalAudioOutputRawChanged = aDigitalAudioOutputRawChanged;
            }
        }

        private void DigitalAudioOutputRawPropertyChanged()
        {
            lock (this)
            {
                if (iDigitalAudioOutputRawChanged != null)
                {
                    iDigitalAudioOutputRawChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the AmplifierEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aAmplifierEnabled">Will be set to the value of the property</param>
        public bool PropertyAmplifierEnabled()
        {
            return iAmplifierEnabled.Value();
        }

        /// <summary>
        /// Query the value of the AmplifierAttenuation property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aAmplifierAttenuation">Will be set to the value of the property</param>
        public String PropertyAmplifierAttenuation()
        {
            return iAmplifierAttenuation.Value();
        }

        /// <summary>
        /// Query the value of the VolumeControlEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVolumeControlEnabled">Will be set to the value of the property</param>
        public bool PropertyVolumeControlEnabled()
        {
            return iVolumeControlEnabled.Value();
        }

        /// <summary>
        /// Query the value of the DigitalAudioOutputRaw property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDigitalAudioOutputRaw">Will be set to the value of the property</param>
        public bool PropertyDigitalAudioOutputRaw()
        {
            return iDigitalAudioOutputRaw.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkComponent1()
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
                iActionAmplifierEnabled.Dispose();
                iActionSetAmplifierEnabled.Dispose();
                iActionAmplifierAttenuation.Dispose();
                iActionSetAmplifierAttenuation.Dispose();
                iActionSetVolumeControlEnabled.Dispose();
                iActionVolumeControlEnabled.Dispose();
                iActionSetDigitalAudioOutputRaw.Dispose();
                iActionDigitalAudioOutputRaw.Dispose();
                iActionAmplifierOverTemperature.Dispose();
                iActionEthernetLinkConnected.Dispose();
                iActionLocate.Dispose();
                iAmplifierEnabled.Dispose();
                iAmplifierAttenuation.Dispose();
                iVolumeControlEnabled.Dispose();
                iDigitalAudioOutputRaw.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

