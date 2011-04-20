using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPreamp4 : ICpProxy, IDisposable
    {
        void SyncVolumeInc();
        void BeginVolumeInc(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeInc(IntPtr aAsyncHandle);
        void SyncVolumeDec();
        void BeginVolumeDec(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeDec(IntPtr aAsyncHandle);
        void SyncSetVolume(uint aVolume);
        void BeginSetVolume(uint aVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolume(IntPtr aAsyncHandle);
        void SyncVolume(out uint aVolume);
        void BeginVolume(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolume(IntPtr aAsyncHandle, out uint aVolume);
        void SyncSetMute(bool aMute);
        void BeginSetMute(bool aMute, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMute(IntPtr aAsyncHandle);
        void SyncMute(out bool aMute);
        void BeginMute(CpProxy.CallbackAsyncComplete aCallback);
        void EndMute(IntPtr aAsyncHandle, out bool aMute);
        void SyncSetBalance(int aBalance);
        void BeginSetBalance(int aBalance, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBalance(IntPtr aAsyncHandle);
        void SyncBalance(out int aBalance);
        void BeginBalance(CpProxy.CallbackAsyncComplete aCallback);
        void EndBalance(IntPtr aAsyncHandle, out int aBalance);
        void SyncSetVolumeLimit(uint aVolumeLimit);
        void BeginSetVolumeLimit(uint aVolumeLimit, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolumeLimit(IntPtr aAsyncHandle);
        void SyncVolumeLimit(out uint aVolumeLimit);
        void BeginVolumeLimit(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeLimit(IntPtr aAsyncHandle, out uint aVolumeLimit);
        void SyncSetStartupVolume(uint aStartupVolume);
        void BeginSetStartupVolume(uint aStartupVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupVolume(IntPtr aAsyncHandle);
        void SyncStartupVolume(out uint aStartupVolume);
        void BeginStartupVolume(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupVolume(IntPtr aAsyncHandle, out uint aStartupVolume);
        void SyncSetStartupVolumeEnabled(bool aStartupVolumeEnabled);
        void BeginSetStartupVolumeEnabled(bool aStartupVolumeEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupVolumeEnabled(IntPtr aAsyncHandle);
        void SyncStartupVolumeEnabled(out bool aStartupVolumeEnabled);
        void BeginStartupVolumeEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupVolumeEnabled(IntPtr aAsyncHandle, out bool aStartupVolumeEnabled);
        void SetPropertyVolumeChanged(System.Action aVolumeChanged);
        uint PropertyVolume();
        void SetPropertyMuteChanged(System.Action aMuteChanged);
        bool PropertyMute();
        void SetPropertyBalanceChanged(System.Action aBalanceChanged);
        int PropertyBalance();
        void SetPropertyVolumeLimitChanged(System.Action aVolumeLimitChanged);
        uint PropertyVolumeLimit();
        void SetPropertyStartupVolumeChanged(System.Action aStartupVolumeChanged);
        uint PropertyStartupVolume();
        void SetPropertyStartupVolumeEnabledChanged(System.Action aStartupVolumeEnabledChanged);
        bool PropertyStartupVolumeEnabled();
    }

    internal class SyncVolumeIncLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncVolumeIncLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeInc(aAsyncHandle);
        }
    };

    internal class SyncVolumeDecLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncVolumeDecLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeDec(aAsyncHandle);
        }
    };

    internal class SyncSetVolumeLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolume(aAsyncHandle);
        }
    };

    internal class SyncVolumeLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private uint iVolume;

        public SyncVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public uint Volume()
        {
            return iVolume;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolume(aAsyncHandle, out iVolume);
        }
    };

    internal class SyncSetMuteLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetMute(aAsyncHandle);
        }
    };

    internal class SyncMuteLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private bool iMute;

        public SyncMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public bool Mute()
        {
            return iMute;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndMute(aAsyncHandle, out iMute);
        }
    };

    internal class SyncSetBalanceLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBalance(aAsyncHandle);
        }
    };

    internal class SyncBalanceLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private int iBalance;

        public SyncBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public int Balance()
        {
            return iBalance;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBalance(aAsyncHandle, out iBalance);
        }
    };

    internal class SyncSetVolumeLimitLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolumeLimit(aAsyncHandle);
        }
    };

    internal class SyncVolumeLimitLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private uint iVolumeLimit;

        public SyncVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public uint VolumeLimit()
        {
            return iVolumeLimit;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeLimit(aAsyncHandle, out iVolumeLimit);
        }
    };

    internal class SyncSetStartupVolumeLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStartupVolume(aAsyncHandle);
        }
    };

    internal class SyncStartupVolumeLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private uint iStartupVolume;

        public SyncStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public uint StartupVolume()
        {
            return iStartupVolume;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartupVolume(aAsyncHandle, out iStartupVolume);
        }
    };

    internal class SyncSetStartupVolumeEnabledLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;

        public SyncSetStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStartupVolumeEnabled(aAsyncHandle);
        }
    };

    internal class SyncStartupVolumeEnabledLinnCoUkPreamp4 : SyncProxyAction
    {
        private CpProxyLinnCoUkPreamp4 iService;
        private bool iStartupVolumeEnabled;

        public SyncStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4 aProxy)
        {
            iService = aProxy;
        }
        public bool StartupVolumeEnabled()
        {
            return iStartupVolumeEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartupVolumeEnabled(aAsyncHandle, out iStartupVolumeEnabled);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Preamp:4 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkPreamp4 : CpProxy, IDisposable, ICpProxyLinnCoUkPreamp4
    {
        private Zapp.Core.Action iActionVolumeInc;
        private Zapp.Core.Action iActionVolumeDec;
        private Zapp.Core.Action iActionSetVolume;
        private Zapp.Core.Action iActionVolume;
        private Zapp.Core.Action iActionSetMute;
        private Zapp.Core.Action iActionMute;
        private Zapp.Core.Action iActionSetBalance;
        private Zapp.Core.Action iActionBalance;
        private Zapp.Core.Action iActionSetVolumeLimit;
        private Zapp.Core.Action iActionVolumeLimit;
        private Zapp.Core.Action iActionSetStartupVolume;
        private Zapp.Core.Action iActionStartupVolume;
        private Zapp.Core.Action iActionSetStartupVolumeEnabled;
        private Zapp.Core.Action iActionStartupVolumeEnabled;
        private PropertyUint iVolume;
        private PropertyBool iMute;
        private PropertyInt iBalance;
        private PropertyUint iVolumeLimit;
        private PropertyUint iStartupVolume;
        private PropertyBool iStartupVolumeEnabled;
        private System.Action iVolumeChanged;
        private System.Action iMuteChanged;
        private System.Action iBalanceChanged;
        private System.Action iVolumeLimitChanged;
        private System.Action iStartupVolumeChanged;
        private System.Action iStartupVolumeEnabledChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPreamp4(CpDevice aDevice)
            : base("linn-co-uk", "Preamp", 4, aDevice)
        {
            Zapp.Core.Parameter param;
            

            iActionVolumeInc = new Zapp.Core.Action("VolumeInc");

            iActionVolumeDec = new Zapp.Core.Action("VolumeDec");

            iActionSetVolume = new Zapp.Core.Action("SetVolume");
            param = new ParameterUint("aVolume");
            iActionSetVolume.AddInputParameter(param);

            iActionVolume = new Zapp.Core.Action("Volume");
            param = new ParameterUint("aVolume");
            iActionVolume.AddOutputParameter(param);

            iActionSetMute = new Zapp.Core.Action("SetMute");
            param = new ParameterBool("aMute");
            iActionSetMute.AddInputParameter(param);

            iActionMute = new Zapp.Core.Action("Mute");
            param = new ParameterBool("aMute");
            iActionMute.AddOutputParameter(param);

            iActionSetBalance = new Zapp.Core.Action("SetBalance");
            param = new ParameterInt("aBalance");
            iActionSetBalance.AddInputParameter(param);

            iActionBalance = new Zapp.Core.Action("Balance");
            param = new ParameterInt("aBalance");
            iActionBalance.AddOutputParameter(param);

            iActionSetVolumeLimit = new Zapp.Core.Action("SetVolumeLimit");
            param = new ParameterUint("aVolumeLimit");
            iActionSetVolumeLimit.AddInputParameter(param);

            iActionVolumeLimit = new Zapp.Core.Action("VolumeLimit");
            param = new ParameterUint("aVolumeLimit");
            iActionVolumeLimit.AddOutputParameter(param);

            iActionSetStartupVolume = new Zapp.Core.Action("SetStartupVolume");
            param = new ParameterUint("aStartupVolume");
            iActionSetStartupVolume.AddInputParameter(param);

            iActionStartupVolume = new Zapp.Core.Action("StartupVolume");
            param = new ParameterUint("aStartupVolume");
            iActionStartupVolume.AddOutputParameter(param);

            iActionSetStartupVolumeEnabled = new Zapp.Core.Action("SetStartupVolumeEnabled");
            param = new ParameterBool("aStartupVolumeEnabled");
            iActionSetStartupVolumeEnabled.AddInputParameter(param);

            iActionStartupVolumeEnabled = new Zapp.Core.Action("StartupVolumeEnabled");
            param = new ParameterBool("aStartupVolumeEnabled");
            iActionStartupVolumeEnabled.AddOutputParameter(param);

            iVolume = new PropertyUint("Volume", VolumePropertyChanged);
            AddProperty(iVolume);
            iMute = new PropertyBool("Mute", MutePropertyChanged);
            AddProperty(iMute);
            iBalance = new PropertyInt("Balance", BalancePropertyChanged);
            AddProperty(iBalance);
            iVolumeLimit = new PropertyUint("VolumeLimit", VolumeLimitPropertyChanged);
            AddProperty(iVolumeLimit);
            iStartupVolume = new PropertyUint("StartupVolume", StartupVolumePropertyChanged);
            AddProperty(iStartupVolume);
            iStartupVolumeEnabled = new PropertyBool("StartupVolumeEnabled", StartupVolumeEnabledPropertyChanged);
            AddProperty(iStartupVolumeEnabled);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncVolumeInc()
        {
            SyncVolumeIncLinnCoUkPreamp4 sync = new SyncVolumeIncLinnCoUkPreamp4(this);
            BeginVolumeInc(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeInc().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginVolumeInc(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionVolumeInc, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndVolumeInc(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncVolumeDec()
        {
            SyncVolumeDecLinnCoUkPreamp4 sync = new SyncVolumeDecLinnCoUkPreamp4(this);
            BeginVolumeDec(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeDec().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginVolumeDec(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionVolumeDec, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndVolumeDec(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaVolume"></param>
        public void SyncSetVolume(uint aVolume)
        {
            SyncSetVolumeLinnCoUkPreamp4 sync = new SyncSetVolumeLinnCoUkPreamp4(this);
            BeginSetVolume(aVolume, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolume().</remarks>
        /// <param name="aaVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolume(uint aVolume, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolume, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolume.InputParameter(inIndex++), aVolume));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolume(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaVolume"></param>
        public void SyncVolume(out uint aVolume)
        {
            SyncVolumeLinnCoUkPreamp4 sync = new SyncVolumeLinnCoUkPreamp4(this);
            BeginVolume(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aVolume = sync.Volume();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolume().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginVolume(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionVolume, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionVolume.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaVolume"></param>
        public void EndVolume(IntPtr aAsyncHandle, out uint aVolume)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aVolume = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMute"></param>
        public void SyncSetMute(bool aMute)
        {
            SyncSetMuteLinnCoUkPreamp4 sync = new SyncSetMuteLinnCoUkPreamp4(this);
            BeginSetMute(aMute, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMute().</remarks>
        /// <param name="aaMute"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetMute(bool aMute, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetMute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetMute.InputParameter(inIndex++), aMute));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetMute(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMute"></param>
        public void SyncMute(out bool aMute)
        {
            SyncMuteLinnCoUkPreamp4 sync = new SyncMuteLinnCoUkPreamp4(this);
            BeginMute(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMute = sync.Mute();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMute().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginMute(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionMute, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionMute.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMute"></param>
        public void EndMute(IntPtr aAsyncHandle, out bool aMute)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aMute = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBalance"></param>
        public void SyncSetBalance(int aBalance)
        {
            SyncSetBalanceLinnCoUkPreamp4 sync = new SyncSetBalanceLinnCoUkPreamp4(this);
            BeginSetBalance(aBalance, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBalance().</remarks>
        /// <param name="aaBalance"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBalance(int aBalance, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBalance, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetBalance.InputParameter(inIndex++), aBalance));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBalance(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaBalance"></param>
        public void SyncBalance(out int aBalance)
        {
            SyncBalanceLinnCoUkPreamp4 sync = new SyncBalanceLinnCoUkPreamp4(this);
            BeginBalance(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aBalance = sync.Balance();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBalance().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBalance(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBalance, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionBalance.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBalance"></param>
        public void EndBalance(IntPtr aAsyncHandle, out int aBalance)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aBalance = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaVolumeLimit"></param>
        public void SyncSetVolumeLimit(uint aVolumeLimit)
        {
            SyncSetVolumeLimitLinnCoUkPreamp4 sync = new SyncSetVolumeLimitLinnCoUkPreamp4(this);
            BeginSetVolumeLimit(aVolumeLimit, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolumeLimit().</remarks>
        /// <param name="aaVolumeLimit"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolumeLimit(uint aVolumeLimit, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolumeLimit, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolumeLimit.InputParameter(inIndex++), aVolumeLimit));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolumeLimit(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaVolumeLimit"></param>
        public void SyncVolumeLimit(out uint aVolumeLimit)
        {
            SyncVolumeLimitLinnCoUkPreamp4 sync = new SyncVolumeLimitLinnCoUkPreamp4(this);
            BeginVolumeLimit(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aVolumeLimit = sync.VolumeLimit();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeLimit().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginVolumeLimit(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionVolumeLimit, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionVolumeLimit.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaVolumeLimit"></param>
        public void EndVolumeLimit(IntPtr aAsyncHandle, out uint aVolumeLimit)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aVolumeLimit = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupVolume"></param>
        public void SyncSetStartupVolume(uint aStartupVolume)
        {
            SyncSetStartupVolumeLinnCoUkPreamp4 sync = new SyncSetStartupVolumeLinnCoUkPreamp4(this);
            BeginSetStartupVolume(aStartupVolume, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupVolume().</remarks>
        /// <param name="aaStartupVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStartupVolume(uint aStartupVolume, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStartupVolume, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStartupVolume.InputParameter(inIndex++), aStartupVolume));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStartupVolume(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupVolume"></param>
        public void SyncStartupVolume(out uint aStartupVolume)
        {
            SyncStartupVolumeLinnCoUkPreamp4 sync = new SyncStartupVolumeLinnCoUkPreamp4(this);
            BeginStartupVolume(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStartupVolume = sync.StartupVolume();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupVolume().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartupVolume(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartupVolume, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionStartupVolume.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupVolume"></param>
        public void EndStartupVolume(IntPtr aAsyncHandle, out uint aStartupVolume)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aStartupVolume = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupVolumeEnabled"></param>
        public void SyncSetStartupVolumeEnabled(bool aStartupVolumeEnabled)
        {
            SyncSetStartupVolumeEnabledLinnCoUkPreamp4 sync = new SyncSetStartupVolumeEnabledLinnCoUkPreamp4(this);
            BeginSetStartupVolumeEnabled(aStartupVolumeEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupVolumeEnabled().</remarks>
        /// <param name="aaStartupVolumeEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStartupVolumeEnabled(bool aStartupVolumeEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStartupVolumeEnabled, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetStartupVolumeEnabled.InputParameter(inIndex++), aStartupVolumeEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStartupVolumeEnabled(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupVolumeEnabled"></param>
        public void SyncStartupVolumeEnabled(out bool aStartupVolumeEnabled)
        {
            SyncStartupVolumeEnabledLinnCoUkPreamp4 sync = new SyncStartupVolumeEnabledLinnCoUkPreamp4(this);
            BeginStartupVolumeEnabled(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStartupVolumeEnabled = sync.StartupVolumeEnabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupVolumeEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartupVolumeEnabled(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartupVolumeEnabled, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionStartupVolumeEnabled.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupVolumeEnabled"></param>
        public void EndStartupVolumeEnabled(IntPtr aAsyncHandle, out bool aStartupVolumeEnabled)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aStartupVolumeEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Volume state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aVolumeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeChanged(System.Action aVolumeChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeChanged = aVolumeChanged;
            }
        }

        private void VolumePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Mute state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aMuteChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyMuteChanged(System.Action aMuteChanged)
        {
            lock (iPropertyLock)
            {
                iMuteChanged = aMuteChanged;
            }
        }

        private void MutePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iMuteChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Balance state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aBalanceChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBalanceChanged(System.Action aBalanceChanged)
        {
            lock (iPropertyLock)
            {
                iBalanceChanged = aBalanceChanged;
            }
        }

        private void BalancePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iBalanceChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeLimit state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aVolumeLimitChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeLimitChanged(System.Action aVolumeLimitChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeLimitChanged = aVolumeLimitChanged;
            }
        }

        private void VolumeLimitPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeLimitChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StartupVolume state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aStartupVolumeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupVolumeChanged(System.Action aStartupVolumeChanged)
        {
            lock (iPropertyLock)
            {
                iStartupVolumeChanged = aStartupVolumeChanged;
            }
        }

        private void StartupVolumePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStartupVolumeChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StartupVolumeEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPreamp4 instance will not overlap.</remarks>
        /// <param name="aStartupVolumeEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupVolumeEnabledChanged(System.Action aStartupVolumeEnabledChanged)
        {
            lock (iPropertyLock)
            {
                iStartupVolumeEnabledChanged = aStartupVolumeEnabledChanged;
            }
        }

        private void StartupVolumeEnabledPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStartupVolumeEnabledChanged);
            }
        }

        /// <summary>
        /// Query the value of the Volume property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVolume">Will be set to the value of the property</param>
        public uint PropertyVolume()
        {
            PropertyReadLock();
            uint val = iVolume.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Mute property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aMute">Will be set to the value of the property</param>
        public bool PropertyMute()
        {
            PropertyReadLock();
            bool val = iMute.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Balance property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aBalance">Will be set to the value of the property</param>
        public int PropertyBalance()
        {
            PropertyReadLock();
            int val = iBalance.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeLimit property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aVolumeLimit">Will be set to the value of the property</param>
        public uint PropertyVolumeLimit()
        {
            PropertyReadLock();
            uint val = iVolumeLimit.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the StartupVolume property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupVolume">Will be set to the value of the property</param>
        public uint PropertyStartupVolume()
        {
            PropertyReadLock();
            uint val = iStartupVolume.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the StartupVolumeEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupVolumeEnabled">Will be set to the value of the property</param>
        public bool PropertyStartupVolumeEnabled()
        {
            PropertyReadLock();
            bool val = iStartupVolumeEnabled.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkPreamp4()
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
                iActionVolumeInc.Dispose();
                iActionVolumeDec.Dispose();
                iActionSetVolume.Dispose();
                iActionVolume.Dispose();
                iActionSetMute.Dispose();
                iActionMute.Dispose();
                iActionSetBalance.Dispose();
                iActionBalance.Dispose();
                iActionSetVolumeLimit.Dispose();
                iActionVolumeLimit.Dispose();
                iActionSetStartupVolume.Dispose();
                iActionStartupVolume.Dispose();
                iActionSetStartupVolumeEnabled.Dispose();
                iActionStartupVolumeEnabled.Dispose();
                iVolume.Dispose();
                iMute.Dispose();
                iBalance.Dispose();
                iVolumeLimit.Dispose();
                iStartupVolume.Dispose();
                iStartupVolumeEnabled.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

