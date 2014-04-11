using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgVolume1 : ICpProxy, IDisposable
    {
        void SyncCharacteristics(out uint aVolumeMax, out uint aVolumeUnity, out uint aVolumeSteps, out uint aVolumeMilliDbPerStep, out uint aBalanceMax, out uint aFadeMax);
        void BeginCharacteristics(CpProxy.CallbackAsyncComplete aCallback);
        void EndCharacteristics(IntPtr aAsyncHandle, out uint aVolumeMax, out uint aVolumeUnity, out uint aVolumeSteps, out uint aVolumeMilliDbPerStep, out uint aBalanceMax, out uint aFadeMax);
        void SyncSetVolume(uint aValue);
        void BeginSetVolume(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolume(IntPtr aAsyncHandle);
        void SyncVolumeInc();
        void BeginVolumeInc(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeInc(IntPtr aAsyncHandle);
        void SyncVolumeDec();
        void BeginVolumeDec(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeDec(IntPtr aAsyncHandle);
        void SyncVolume(out uint aValue);
        void BeginVolume(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolume(IntPtr aAsyncHandle, out uint aValue);
        void SyncSetBalance(int aValue);
        void BeginSetBalance(int aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBalance(IntPtr aAsyncHandle);
        void SyncBalanceInc();
        void BeginBalanceInc(CpProxy.CallbackAsyncComplete aCallback);
        void EndBalanceInc(IntPtr aAsyncHandle);
        void SyncBalanceDec();
        void BeginBalanceDec(CpProxy.CallbackAsyncComplete aCallback);
        void EndBalanceDec(IntPtr aAsyncHandle);
        void SyncBalance(out int aValue);
        void BeginBalance(CpProxy.CallbackAsyncComplete aCallback);
        void EndBalance(IntPtr aAsyncHandle, out int aValue);
        void SyncSetFade(int aValue);
        void BeginSetFade(int aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetFade(IntPtr aAsyncHandle);
        void SyncFadeInc();
        void BeginFadeInc(CpProxy.CallbackAsyncComplete aCallback);
        void EndFadeInc(IntPtr aAsyncHandle);
        void SyncFadeDec();
        void BeginFadeDec(CpProxy.CallbackAsyncComplete aCallback);
        void EndFadeDec(IntPtr aAsyncHandle);
        void SyncFade(out int aValue);
        void BeginFade(CpProxy.CallbackAsyncComplete aCallback);
        void EndFade(IntPtr aAsyncHandle, out int aValue);
        void SyncSetMute(bool aValue);
        void BeginSetMute(bool aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMute(IntPtr aAsyncHandle);
        void SyncMute(out bool aValue);
        void BeginMute(CpProxy.CallbackAsyncComplete aCallback);
        void EndMute(IntPtr aAsyncHandle, out bool aValue);
        void SyncVolumeLimit(out uint aValue);
        void BeginVolumeLimit(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeLimit(IntPtr aAsyncHandle, out uint aValue);
        void SetPropertyVolumeChanged(System.Action aVolumeChanged);
        uint PropertyVolume();
        void SetPropertyMuteChanged(System.Action aMuteChanged);
        bool PropertyMute();
        void SetPropertyBalanceChanged(System.Action aBalanceChanged);
        int PropertyBalance();
        void SetPropertyFadeChanged(System.Action aFadeChanged);
        int PropertyFade();
        void SetPropertyVolumeLimitChanged(System.Action aVolumeLimitChanged);
        uint PropertyVolumeLimit();
        void SetPropertyVolumeMaxChanged(System.Action aVolumeMaxChanged);
        uint PropertyVolumeMax();
        void SetPropertyVolumeUnityChanged(System.Action aVolumeUnityChanged);
        uint PropertyVolumeUnity();
        void SetPropertyVolumeStepsChanged(System.Action aVolumeStepsChanged);
        uint PropertyVolumeSteps();
        void SetPropertyVolumeMilliDbPerStepChanged(System.Action aVolumeMilliDbPerStepChanged);
        uint PropertyVolumeMilliDbPerStep();
        void SetPropertyBalanceMaxChanged(System.Action aBalanceMaxChanged);
        uint PropertyBalanceMax();
        void SetPropertyFadeMaxChanged(System.Action aFadeMaxChanged);
        uint PropertyFadeMax();
    }

    internal class SyncCharacteristicsAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private uint iVolumeMax;
        private uint iVolumeUnity;
        private uint iVolumeSteps;
        private uint iVolumeMilliDbPerStep;
        private uint iBalanceMax;
        private uint iFadeMax;

        public SyncCharacteristicsAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public uint VolumeMax()
        {
            return iVolumeMax;
        }
        public uint VolumeUnity()
        {
            return iVolumeUnity;
        }
        public uint VolumeSteps()
        {
            return iVolumeSteps;
        }
        public uint VolumeMilliDbPerStep()
        {
            return iVolumeMilliDbPerStep;
        }
        public uint BalanceMax()
        {
            return iBalanceMax;
        }
        public uint FadeMax()
        {
            return iFadeMax;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCharacteristics(aAsyncHandle, out iVolumeMax, out iVolumeUnity, out iVolumeSteps, out iVolumeMilliDbPerStep, out iBalanceMax, out iFadeMax);
        }
    };

    internal class SyncSetVolumeAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncSetVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolume(aAsyncHandle);
        }
    };

    internal class SyncVolumeIncAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncVolumeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeInc(aAsyncHandle);
        }
    };

    internal class SyncVolumeDecAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncVolumeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeDec(aAsyncHandle);
        }
    };

    internal class SyncVolumeAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private uint iValue;

        public SyncVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolume(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSetBalanceAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncSetBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBalance(aAsyncHandle);
        }
    };

    internal class SyncBalanceIncAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncBalanceIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBalanceInc(aAsyncHandle);
        }
    };

    internal class SyncBalanceDecAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncBalanceDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBalanceDec(aAsyncHandle);
        }
    };

    internal class SyncBalanceAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private int iValue;

        public SyncBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public int Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBalance(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSetFadeAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncSetFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetFade(aAsyncHandle);
        }
    };

    internal class SyncFadeIncAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncFadeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndFadeInc(aAsyncHandle);
        }
    };

    internal class SyncFadeDecAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncFadeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndFadeDec(aAsyncHandle);
        }
    };

    internal class SyncFadeAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private int iValue;

        public SyncFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public int Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndFade(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSetMuteAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;

        public SyncSetMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetMute(aAsyncHandle);
        }
    };

    internal class SyncMuteAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private bool iValue;

        public SyncMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public bool Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndMute(aAsyncHandle, out iValue);
        }
    };

    internal class SyncVolumeLimitAvOpenhomeOrgVolume1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgVolume1 iService;
        private uint iValue;

        public SyncVolumeLimitAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndVolumeLimit(aAsyncHandle, out iValue);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:Volume:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgVolume1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgVolume1
    {
        private OpenHome.Net.Core.Action iActionCharacteristics;
        private OpenHome.Net.Core.Action iActionSetVolume;
        private OpenHome.Net.Core.Action iActionVolumeInc;
        private OpenHome.Net.Core.Action iActionVolumeDec;
        private OpenHome.Net.Core.Action iActionVolume;
        private OpenHome.Net.Core.Action iActionSetBalance;
        private OpenHome.Net.Core.Action iActionBalanceInc;
        private OpenHome.Net.Core.Action iActionBalanceDec;
        private OpenHome.Net.Core.Action iActionBalance;
        private OpenHome.Net.Core.Action iActionSetFade;
        private OpenHome.Net.Core.Action iActionFadeInc;
        private OpenHome.Net.Core.Action iActionFadeDec;
        private OpenHome.Net.Core.Action iActionFade;
        private OpenHome.Net.Core.Action iActionSetMute;
        private OpenHome.Net.Core.Action iActionMute;
        private OpenHome.Net.Core.Action iActionVolumeLimit;
        private PropertyUint iVolume;
        private PropertyBool iMute;
        private PropertyInt iBalance;
        private PropertyInt iFade;
        private PropertyUint iVolumeLimit;
        private PropertyUint iVolumeMax;
        private PropertyUint iVolumeUnity;
        private PropertyUint iVolumeSteps;
        private PropertyUint iVolumeMilliDbPerStep;
        private PropertyUint iBalanceMax;
        private PropertyUint iFadeMax;
        private System.Action iVolumeChanged;
        private System.Action iMuteChanged;
        private System.Action iBalanceChanged;
        private System.Action iFadeChanged;
        private System.Action iVolumeLimitChanged;
        private System.Action iVolumeMaxChanged;
        private System.Action iVolumeUnityChanged;
        private System.Action iVolumeStepsChanged;
        private System.Action iVolumeMilliDbPerStepChanged;
        private System.Action iBalanceMaxChanged;
        private System.Action iFadeMaxChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgVolume1(CpDevice aDevice)
            : base("av-openhome-org", "Volume", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            

            iActionCharacteristics = new OpenHome.Net.Core.Action("Characteristics");
            param = new ParameterUint("VolumeMax");
            iActionCharacteristics.AddOutputParameter(param);
            param = new ParameterUint("VolumeUnity");
            iActionCharacteristics.AddOutputParameter(param);
            param = new ParameterUint("VolumeSteps");
            iActionCharacteristics.AddOutputParameter(param);
            param = new ParameterUint("VolumeMilliDbPerStep");
            iActionCharacteristics.AddOutputParameter(param);
            param = new ParameterUint("BalanceMax");
            iActionCharacteristics.AddOutputParameter(param);
            param = new ParameterUint("FadeMax");
            iActionCharacteristics.AddOutputParameter(param);

            iActionSetVolume = new OpenHome.Net.Core.Action("SetVolume");
            param = new ParameterUint("Value");
            iActionSetVolume.AddInputParameter(param);

            iActionVolumeInc = new OpenHome.Net.Core.Action("VolumeInc");

            iActionVolumeDec = new OpenHome.Net.Core.Action("VolumeDec");

            iActionVolume = new OpenHome.Net.Core.Action("Volume");
            param = new ParameterUint("Value");
            iActionVolume.AddOutputParameter(param);

            iActionSetBalance = new OpenHome.Net.Core.Action("SetBalance");
            param = new ParameterInt("Value");
            iActionSetBalance.AddInputParameter(param);

            iActionBalanceInc = new OpenHome.Net.Core.Action("BalanceInc");

            iActionBalanceDec = new OpenHome.Net.Core.Action("BalanceDec");

            iActionBalance = new OpenHome.Net.Core.Action("Balance");
            param = new ParameterInt("Value");
            iActionBalance.AddOutputParameter(param);

            iActionSetFade = new OpenHome.Net.Core.Action("SetFade");
            param = new ParameterInt("Value");
            iActionSetFade.AddInputParameter(param);

            iActionFadeInc = new OpenHome.Net.Core.Action("FadeInc");

            iActionFadeDec = new OpenHome.Net.Core.Action("FadeDec");

            iActionFade = new OpenHome.Net.Core.Action("Fade");
            param = new ParameterInt("Value");
            iActionFade.AddOutputParameter(param);

            iActionSetMute = new OpenHome.Net.Core.Action("SetMute");
            param = new ParameterBool("Value");
            iActionSetMute.AddInputParameter(param);

            iActionMute = new OpenHome.Net.Core.Action("Mute");
            param = new ParameterBool("Value");
            iActionMute.AddOutputParameter(param);

            iActionVolumeLimit = new OpenHome.Net.Core.Action("VolumeLimit");
            param = new ParameterUint("Value");
            iActionVolumeLimit.AddOutputParameter(param);

            iVolume = new PropertyUint("Volume", VolumePropertyChanged);
            AddProperty(iVolume);
            iMute = new PropertyBool("Mute", MutePropertyChanged);
            AddProperty(iMute);
            iBalance = new PropertyInt("Balance", BalancePropertyChanged);
            AddProperty(iBalance);
            iFade = new PropertyInt("Fade", FadePropertyChanged);
            AddProperty(iFade);
            iVolumeLimit = new PropertyUint("VolumeLimit", VolumeLimitPropertyChanged);
            AddProperty(iVolumeLimit);
            iVolumeMax = new PropertyUint("VolumeMax", VolumeMaxPropertyChanged);
            AddProperty(iVolumeMax);
            iVolumeUnity = new PropertyUint("VolumeUnity", VolumeUnityPropertyChanged);
            AddProperty(iVolumeUnity);
            iVolumeSteps = new PropertyUint("VolumeSteps", VolumeStepsPropertyChanged);
            AddProperty(iVolumeSteps);
            iVolumeMilliDbPerStep = new PropertyUint("VolumeMilliDbPerStep", VolumeMilliDbPerStepPropertyChanged);
            AddProperty(iVolumeMilliDbPerStep);
            iBalanceMax = new PropertyUint("BalanceMax", BalanceMaxPropertyChanged);
            AddProperty(iBalanceMax);
            iFadeMax = new PropertyUint("FadeMax", FadeMaxPropertyChanged);
            AddProperty(iFadeMax);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aVolumeMax"></param>
        /// <param name="aVolumeUnity"></param>
        /// <param name="aVolumeSteps"></param>
        /// <param name="aVolumeMilliDbPerStep"></param>
        /// <param name="aBalanceMax"></param>
        /// <param name="aFadeMax"></param>
        public void SyncCharacteristics(out uint aVolumeMax, out uint aVolumeUnity, out uint aVolumeSteps, out uint aVolumeMilliDbPerStep, out uint aBalanceMax, out uint aFadeMax)
        {
            SyncCharacteristicsAvOpenhomeOrgVolume1 sync = new SyncCharacteristicsAvOpenhomeOrgVolume1(this);
            BeginCharacteristics(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aVolumeMax = sync.VolumeMax();
            aVolumeUnity = sync.VolumeUnity();
            aVolumeSteps = sync.VolumeSteps();
            aVolumeMilliDbPerStep = sync.VolumeMilliDbPerStep();
            aBalanceMax = sync.BalanceMax();
            aFadeMax = sync.FadeMax();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCharacteristics().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCharacteristics(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCharacteristics, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCharacteristics.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aVolumeMax"></param>
        /// <param name="aVolumeUnity"></param>
        /// <param name="aVolumeSteps"></param>
        /// <param name="aVolumeMilliDbPerStep"></param>
        /// <param name="aBalanceMax"></param>
        /// <param name="aFadeMax"></param>
        public void EndCharacteristics(IntPtr aAsyncHandle, out uint aVolumeMax, out uint aVolumeUnity, out uint aVolumeSteps, out uint aVolumeMilliDbPerStep, out uint aBalanceMax, out uint aFadeMax)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aVolumeMax = Invocation.OutputUint(aAsyncHandle, index++);
            aVolumeUnity = Invocation.OutputUint(aAsyncHandle, index++);
            aVolumeSteps = Invocation.OutputUint(aAsyncHandle, index++);
            aVolumeMilliDbPerStep = Invocation.OutputUint(aAsyncHandle, index++);
            aBalanceMax = Invocation.OutputUint(aAsyncHandle, index++);
            aFadeMax = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetVolume(uint aValue)
        {
            SyncSetVolumeAvOpenhomeOrgVolume1 sync = new SyncSetVolumeAvOpenhomeOrgVolume1(this);
            BeginSetVolume(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolume().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolume(uint aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolume, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolume.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolume(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncVolumeInc()
        {
            SyncVolumeIncAvOpenhomeOrgVolume1 sync = new SyncVolumeIncAvOpenhomeOrgVolume1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncVolumeDec()
        {
            SyncVolumeDecAvOpenhomeOrgVolume1 sync = new SyncVolumeDecAvOpenhomeOrgVolume1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncVolume(out uint aValue)
        {
            SyncVolumeAvOpenhomeOrgVolume1 sync = new SyncVolumeAvOpenhomeOrgVolume1(this);
            BeginVolume(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
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
        /// <param name="aValue"></param>
        public void EndVolume(IntPtr aAsyncHandle, out uint aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetBalance(int aValue)
        {
            SyncSetBalanceAvOpenhomeOrgVolume1 sync = new SyncSetBalanceAvOpenhomeOrgVolume1(this);
            BeginSetBalance(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBalance().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBalance(int aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBalance, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetBalance.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBalance(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncBalanceInc()
        {
            SyncBalanceIncAvOpenhomeOrgVolume1 sync = new SyncBalanceIncAvOpenhomeOrgVolume1(this);
            BeginBalanceInc(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBalanceInc().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBalanceInc(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBalanceInc, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndBalanceInc(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncBalanceDec()
        {
            SyncBalanceDecAvOpenhomeOrgVolume1 sync = new SyncBalanceDecAvOpenhomeOrgVolume1(this);
            BeginBalanceDec(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBalanceDec().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBalanceDec(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBalanceDec, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndBalanceDec(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncBalance(out int aValue)
        {
            SyncBalanceAvOpenhomeOrgVolume1 sync = new SyncBalanceAvOpenhomeOrgVolume1(this);
            BeginBalance(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
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
        /// <param name="aValue"></param>
        public void EndBalance(IntPtr aAsyncHandle, out int aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetFade(int aValue)
        {
            SyncSetFadeAvOpenhomeOrgVolume1 sync = new SyncSetFadeAvOpenhomeOrgVolume1(this);
            BeginSetFade(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetFade().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetFade(int aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetFade, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetFade.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetFade(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncFadeInc()
        {
            SyncFadeIncAvOpenhomeOrgVolume1 sync = new SyncFadeIncAvOpenhomeOrgVolume1(this);
            BeginFadeInc(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndFadeInc().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginFadeInc(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionFadeInc, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndFadeInc(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncFadeDec()
        {
            SyncFadeDecAvOpenhomeOrgVolume1 sync = new SyncFadeDecAvOpenhomeOrgVolume1(this);
            BeginFadeDec(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndFadeDec().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginFadeDec(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionFadeDec, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndFadeDec(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncFade(out int aValue)
        {
            SyncFadeAvOpenhomeOrgVolume1 sync = new SyncFadeAvOpenhomeOrgVolume1(this);
            BeginFade(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndFade().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginFade(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionFade, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionFade.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndFade(IntPtr aAsyncHandle, out int aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetMute(bool aValue)
        {
            SyncSetMuteAvOpenhomeOrgVolume1 sync = new SyncSetMuteAvOpenhomeOrgVolume1(this);
            BeginSetMute(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMute().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetMute(bool aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetMute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetMute.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetMute(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncMute(out bool aValue)
        {
            SyncMuteAvOpenhomeOrgVolume1 sync = new SyncMuteAvOpenhomeOrgVolume1(this);
            BeginMute(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
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
        /// <param name="aValue"></param>
        public void EndMute(IntPtr aAsyncHandle, out bool aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncVolumeLimit(out uint aValue)
        {
            SyncVolumeLimitAvOpenhomeOrgVolume1 sync = new SyncVolumeLimitAvOpenhomeOrgVolume1(this);
            BeginVolumeLimit(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
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
        /// <param name="aValue"></param>
        public void EndVolumeLimit(IntPtr aAsyncHandle, out uint aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Volume state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
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
        /// Set a delegate to be run when the Fade state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aFadeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyFadeChanged(System.Action aFadeChanged)
        {
            lock (iPropertyLock)
            {
                iFadeChanged = aFadeChanged;
            }
        }

        private void FadePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iFadeChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeLimit state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
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
        /// Set a delegate to be run when the VolumeMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aVolumeMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeMaxChanged(System.Action aVolumeMaxChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeMaxChanged = aVolumeMaxChanged;
            }
        }

        private void VolumeMaxPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeMaxChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeUnity state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aVolumeUnityChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeUnityChanged(System.Action aVolumeUnityChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeUnityChanged = aVolumeUnityChanged;
            }
        }

        private void VolumeUnityPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeUnityChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeSteps state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aVolumeStepsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeStepsChanged(System.Action aVolumeStepsChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeStepsChanged = aVolumeStepsChanged;
            }
        }

        private void VolumeStepsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeStepsChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeMilliDbPerStep state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aVolumeMilliDbPerStepChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeMilliDbPerStepChanged(System.Action aVolumeMilliDbPerStepChanged)
        {
            lock (iPropertyLock)
            {
                iVolumeMilliDbPerStepChanged = aVolumeMilliDbPerStepChanged;
            }
        }

        private void VolumeMilliDbPerStepPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iVolumeMilliDbPerStepChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the BalanceMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aBalanceMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBalanceMaxChanged(System.Action aBalanceMaxChanged)
        {
            lock (iPropertyLock)
            {
                iBalanceMaxChanged = aBalanceMaxChanged;
            }
        }

        private void BalanceMaxPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iBalanceMaxChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the FadeMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgVolume1 instance will not overlap.</remarks>
        /// <param name="aFadeMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyFadeMaxChanged(System.Action aFadeMaxChanged)
        {
            lock (iPropertyLock)
            {
                iFadeMaxChanged = aFadeMaxChanged;
            }
        }

        private void FadeMaxPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iFadeMaxChanged);
            }
        }

        /// <summary>
        /// Query the value of the Volume property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Volume property</returns>
        public uint PropertyVolume()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolume.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Mute property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Mute property</returns>
        public bool PropertyMute()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iMute.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Balance property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Balance property</returns>
        public int PropertyBalance()
        {
            PropertyReadLock();
            int val;
            try
            {
                val = iBalance.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Fade property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Fade property</returns>
        public int PropertyFade()
        {
            PropertyReadLock();
            int val;
            try
            {
                val = iFade.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeLimit property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VolumeLimit property</returns>
        public uint PropertyVolumeLimit()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolumeLimit.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VolumeMax property</returns>
        public uint PropertyVolumeMax()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolumeMax.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeUnity property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VolumeUnity property</returns>
        public uint PropertyVolumeUnity()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolumeUnity.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeSteps property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VolumeSteps property</returns>
        public uint PropertyVolumeSteps()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolumeSteps.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the VolumeMilliDbPerStep property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the VolumeMilliDbPerStep property</returns>
        public uint PropertyVolumeMilliDbPerStep()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iVolumeMilliDbPerStep.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the BalanceMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the BalanceMax property</returns>
        public uint PropertyBalanceMax()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iBalanceMax.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the FadeMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the FadeMax property</returns>
        public uint PropertyFadeMax()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iFadeMax.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionCharacteristics.Dispose();
            iActionSetVolume.Dispose();
            iActionVolumeInc.Dispose();
            iActionVolumeDec.Dispose();
            iActionVolume.Dispose();
            iActionSetBalance.Dispose();
            iActionBalanceInc.Dispose();
            iActionBalanceDec.Dispose();
            iActionBalance.Dispose();
            iActionSetFade.Dispose();
            iActionFadeInc.Dispose();
            iActionFadeDec.Dispose();
            iActionFade.Dispose();
            iActionSetMute.Dispose();
            iActionMute.Dispose();
            iActionVolumeLimit.Dispose();
            iVolume.Dispose();
            iMute.Dispose();
            iBalance.Dispose();
            iFade.Dispose();
            iVolumeLimit.Dispose();
            iVolumeMax.Dispose();
            iVolumeUnity.Dispose();
            iVolumeSteps.Dispose();
            iVolumeMilliDbPerStep.Dispose();
            iBalanceMax.Dispose();
            iFadeMax.Dispose();
        }
    }
}

