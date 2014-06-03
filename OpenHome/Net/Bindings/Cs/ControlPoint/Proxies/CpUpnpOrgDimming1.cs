using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgDimming1 : ICpProxy, IDisposable
    {
        void SyncSetLoadLevelTarget(uint aNewLoadlevelTarget);
        void BeginSetLoadLevelTarget(uint aNewLoadlevelTarget, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLoadLevelTarget(IntPtr aAsyncHandle);
        void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget);
        void BeginGetLoadLevelTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget);
        void SyncGetLoadLevelStatus(out uint aRetLoadlevelStatus);
        void BeginGetLoadLevelStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aRetLoadlevelStatus);
        void SyncSetOnEffectLevel(uint aNewOnEffectLevel);
        void BeginSetOnEffectLevel(uint aNewOnEffectLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffectLevel(IntPtr aAsyncHandle);
        void SyncSetOnEffect(String aNewOnEffect);
        void BeginSetOnEffect(String aNewOnEffect, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffect(IntPtr aAsyncHandle);
        void SyncGetOnEffectParameters(out String aRetOnEffect, out uint aRetOnEffectLevel);
        void BeginGetOnEffectParameters(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetOnEffectParameters(IntPtr aAsyncHandle, out String aRetOnEffect, out uint aRetOnEffectLevel);
        void SyncStepUp();
        void BeginStepUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepUp(IntPtr aAsyncHandle);
        void SyncStepDown();
        void BeginStepDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepDown(IntPtr aAsyncHandle);
        void SyncStartRampUp();
        void BeginStartRampUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampUp(IntPtr aAsyncHandle);
        void SyncStartRampDown();
        void BeginStartRampDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampDown(IntPtr aAsyncHandle);
        void SyncStopRamp();
        void BeginStopRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStopRamp(IntPtr aAsyncHandle);
        void SyncStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime);
        void BeginStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime, CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampToLevel(IntPtr aAsyncHandle);
        void SyncSetStepDelta(uint aNewStepDelta);
        void BeginSetStepDelta(uint aNewStepDelta, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStepDelta(IntPtr aAsyncHandle);
        void SyncGetStepDelta(out uint aRetStepDelta);
        void BeginGetStepDelta(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStepDelta(IntPtr aAsyncHandle, out uint aRetStepDelta);
        void SyncSetRampRate(uint aNewRampRate);
        void BeginSetRampRate(uint aNewRampRate, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRampRate(IntPtr aAsyncHandle);
        void SyncGetRampRate(out uint aRetRampRate);
        void BeginGetRampRate(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampRate(IntPtr aAsyncHandle, out uint aRetRampRate);
        void SyncPauseRamp();
        void BeginPauseRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndPauseRamp(IntPtr aAsyncHandle);
        void SyncResumeRamp();
        void BeginResumeRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndResumeRamp(IntPtr aAsyncHandle);
        void SyncGetIsRamping(out bool aRetIsRamping);
        void BeginGetIsRamping(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetIsRamping(IntPtr aAsyncHandle, out bool aRetIsRamping);
        void SyncGetRampPaused(out bool aRetRampPaused);
        void BeginGetRampPaused(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampPaused(IntPtr aAsyncHandle, out bool aRetRampPaused);
        void SyncGetRampTime(out uint aRetRampTime);
        void BeginGetRampTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampTime(IntPtr aAsyncHandle, out uint aRetRampTime);
        void SetPropertyLoadLevelStatusChanged(System.Action aLoadLevelStatusChanged);
        uint PropertyLoadLevelStatus();
        void SetPropertyStepDeltaChanged(System.Action aStepDeltaChanged);
        uint PropertyStepDelta();
        void SetPropertyRampRateChanged(System.Action aRampRateChanged);
        uint PropertyRampRate();
        void SetPropertyIsRampingChanged(System.Action aIsRampingChanged);
        bool PropertyIsRamping();
        void SetPropertyRampPausedChanged(System.Action aRampPausedChanged);
        bool PropertyRampPaused();
    }

    internal class SyncSetLoadLevelTargetUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetLoadLevelTarget(aAsyncHandle);
        }
    };

    internal class SyncGetLoadLevelTargetUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iGetLoadlevelTarget;

        public SyncGetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint GetLoadlevelTarget()
        {
            return iGetLoadlevelTarget;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLoadLevelTarget(aAsyncHandle, out iGetLoadlevelTarget);
        }
    };

    internal class SyncGetLoadLevelStatusUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetLoadlevelStatus;

        public SyncGetLoadLevelStatusUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetLoadlevelStatus()
        {
            return iRetLoadlevelStatus;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLoadLevelStatus(aAsyncHandle, out iRetLoadlevelStatus);
        }
    };

    internal class SyncSetOnEffectLevelUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetOnEffectLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetOnEffectLevel(aAsyncHandle);
        }
    };

    internal class SyncSetOnEffectUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetOnEffectUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetOnEffect(aAsyncHandle);
        }
    };

    internal class SyncGetOnEffectParametersUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private String iRetOnEffect;
        private uint iRetOnEffectLevel;

        public SyncGetOnEffectParametersUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public String RetOnEffect()
        {
            return iRetOnEffect;
        }
        public uint RetOnEffectLevel()
        {
            return iRetOnEffectLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetOnEffectParameters(aAsyncHandle, out iRetOnEffect, out iRetOnEffectLevel);
        }
    };

    internal class SyncStepUpUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStepUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStepUp(aAsyncHandle);
        }
    };

    internal class SyncStepDownUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStepDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStepDown(aAsyncHandle);
        }
    };

    internal class SyncStartRampUpUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampUp(aAsyncHandle);
        }
    };

    internal class SyncStartRampDownUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampDown(aAsyncHandle);
        }
    };

    internal class SyncStopRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStopRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStopRamp(aAsyncHandle);
        }
    };

    internal class SyncStartRampToLevelUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampToLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampToLevel(aAsyncHandle);
        }
    };

    internal class SyncSetStepDeltaUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStepDelta(aAsyncHandle);
        }
    };

    internal class SyncGetStepDeltaUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetStepDelta;

        public SyncGetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetStepDelta()
        {
            return iRetStepDelta;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetStepDelta(aAsyncHandle, out iRetStepDelta);
        }
    };

    internal class SyncSetRampRateUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRampRate(aAsyncHandle);
        }
    };

    internal class SyncGetRampRateUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetRampRate;

        public SyncGetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetRampRate()
        {
            return iRetRampRate;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampRate(aAsyncHandle, out iRetRampRate);
        }
    };

    internal class SyncPauseRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncPauseRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPauseRamp(aAsyncHandle);
        }
    };

    internal class SyncResumeRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncResumeRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndResumeRamp(aAsyncHandle);
        }
    };

    internal class SyncGetIsRampingUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private bool iRetIsRamping;

        public SyncGetIsRampingUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public bool RetIsRamping()
        {
            return iRetIsRamping;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetIsRamping(aAsyncHandle, out iRetIsRamping);
        }
    };

    internal class SyncGetRampPausedUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private bool iRetRampPaused;

        public SyncGetRampPausedUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public bool RetRampPaused()
        {
            return iRetRampPaused;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampPaused(aAsyncHandle, out iRetRampPaused);
        }
    };

    internal class SyncGetRampTimeUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetRampTime;

        public SyncGetRampTimeUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetRampTime()
        {
            return iRetRampTime;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampTime(aAsyncHandle, out iRetRampTime);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:Dimming:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgDimming1 : CpProxy, IDisposable, ICpProxyUpnpOrgDimming1
    {
        private OpenHome.Net.Core.Action iActionSetLoadLevelTarget;
        private OpenHome.Net.Core.Action iActionGetLoadLevelTarget;
        private OpenHome.Net.Core.Action iActionGetLoadLevelStatus;
        private OpenHome.Net.Core.Action iActionSetOnEffectLevel;
        private OpenHome.Net.Core.Action iActionSetOnEffect;
        private OpenHome.Net.Core.Action iActionGetOnEffectParameters;
        private OpenHome.Net.Core.Action iActionStepUp;
        private OpenHome.Net.Core.Action iActionStepDown;
        private OpenHome.Net.Core.Action iActionStartRampUp;
        private OpenHome.Net.Core.Action iActionStartRampDown;
        private OpenHome.Net.Core.Action iActionStopRamp;
        private OpenHome.Net.Core.Action iActionStartRampToLevel;
        private OpenHome.Net.Core.Action iActionSetStepDelta;
        private OpenHome.Net.Core.Action iActionGetStepDelta;
        private OpenHome.Net.Core.Action iActionSetRampRate;
        private OpenHome.Net.Core.Action iActionGetRampRate;
        private OpenHome.Net.Core.Action iActionPauseRamp;
        private OpenHome.Net.Core.Action iActionResumeRamp;
        private OpenHome.Net.Core.Action iActionGetIsRamping;
        private OpenHome.Net.Core.Action iActionGetRampPaused;
        private OpenHome.Net.Core.Action iActionGetRampTime;
        private PropertyUint iLoadLevelStatus;
        private PropertyUint iStepDelta;
        private PropertyUint iRampRate;
        private PropertyBool iIsRamping;
        private PropertyBool iRampPaused;
        private System.Action iLoadLevelStatusChanged;
        private System.Action iStepDeltaChanged;
        private System.Action iRampRateChanged;
        private System.Action iIsRampingChanged;
        private System.Action iRampPausedChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgDimming1(CpDevice aDevice)
            : base("schemas-upnp-org", "Dimming", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionSetLoadLevelTarget = new OpenHome.Net.Core.Action("SetLoadLevelTarget");
            param = new ParameterUint("newLoadlevelTarget", 0, 100);
            iActionSetLoadLevelTarget.AddInputParameter(param);

            iActionGetLoadLevelTarget = new OpenHome.Net.Core.Action("GetLoadLevelTarget");
            param = new ParameterUint("GetLoadlevelTarget", 0, 100);
            iActionGetLoadLevelTarget.AddOutputParameter(param);

            iActionGetLoadLevelStatus = new OpenHome.Net.Core.Action("GetLoadLevelStatus");
            param = new ParameterUint("retLoadlevelStatus", 0, 100);
            iActionGetLoadLevelStatus.AddOutputParameter(param);

            iActionSetOnEffectLevel = new OpenHome.Net.Core.Action("SetOnEffectLevel");
            param = new ParameterUint("newOnEffectLevel", 0, 100);
            iActionSetOnEffectLevel.AddInputParameter(param);

            iActionSetOnEffect = new OpenHome.Net.Core.Action("SetOnEffect");
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            param = new ParameterString("newOnEffect", allowedValues);
            iActionSetOnEffect.AddInputParameter(param);
            allowedValues.Clear();

            iActionGetOnEffectParameters = new OpenHome.Net.Core.Action("GetOnEffectParameters");
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            param = new ParameterString("retOnEffect", allowedValues);
            iActionGetOnEffectParameters.AddOutputParameter(param);
            allowedValues.Clear();
            param = new ParameterUint("retOnEffectLevel", 0, 100);
            iActionGetOnEffectParameters.AddOutputParameter(param);

            iActionStepUp = new OpenHome.Net.Core.Action("StepUp");

            iActionStepDown = new OpenHome.Net.Core.Action("StepDown");

            iActionStartRampUp = new OpenHome.Net.Core.Action("StartRampUp");

            iActionStartRampDown = new OpenHome.Net.Core.Action("StartRampDown");

            iActionStopRamp = new OpenHome.Net.Core.Action("StopRamp");

            iActionStartRampToLevel = new OpenHome.Net.Core.Action("StartRampToLevel");
            param = new ParameterUint("newLoadLevelTarget", 0, 100);
            iActionStartRampToLevel.AddInputParameter(param);
            param = new ParameterUint("newRampTime");
            iActionStartRampToLevel.AddInputParameter(param);

            iActionSetStepDelta = new OpenHome.Net.Core.Action("SetStepDelta");
            param = new ParameterUint("newStepDelta", 1, 100);
            iActionSetStepDelta.AddInputParameter(param);

            iActionGetStepDelta = new OpenHome.Net.Core.Action("GetStepDelta");
            param = new ParameterUint("retStepDelta", 1, 100);
            iActionGetStepDelta.AddOutputParameter(param);

            iActionSetRampRate = new OpenHome.Net.Core.Action("SetRampRate");
            param = new ParameterUint("newRampRate", 0, 100);
            iActionSetRampRate.AddInputParameter(param);

            iActionGetRampRate = new OpenHome.Net.Core.Action("GetRampRate");
            param = new ParameterUint("retRampRate", 0, 100);
            iActionGetRampRate.AddOutputParameter(param);

            iActionPauseRamp = new OpenHome.Net.Core.Action("PauseRamp");

            iActionResumeRamp = new OpenHome.Net.Core.Action("ResumeRamp");

            iActionGetIsRamping = new OpenHome.Net.Core.Action("GetIsRamping");
            param = new ParameterBool("retIsRamping");
            iActionGetIsRamping.AddOutputParameter(param);

            iActionGetRampPaused = new OpenHome.Net.Core.Action("GetRampPaused");
            param = new ParameterBool("retRampPaused");
            iActionGetRampPaused.AddOutputParameter(param);

            iActionGetRampTime = new OpenHome.Net.Core.Action("GetRampTime");
            param = new ParameterUint("retRampTime");
            iActionGetRampTime.AddOutputParameter(param);

            iLoadLevelStatus = new PropertyUint("LoadLevelStatus", LoadLevelStatusPropertyChanged);
            AddProperty(iLoadLevelStatus);
            iStepDelta = new PropertyUint("StepDelta", StepDeltaPropertyChanged);
            AddProperty(iStepDelta);
            iRampRate = new PropertyUint("RampRate", RampRatePropertyChanged);
            AddProperty(iRampRate);
            iIsRamping = new PropertyBool("IsRamping", IsRampingPropertyChanged);
            AddProperty(iIsRamping);
            iRampPaused = new PropertyBool("RampPaused", RampPausedPropertyChanged);
            AddProperty(iRampPaused);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aNewLoadlevelTarget"></param>
        public void SyncSetLoadLevelTarget(uint aNewLoadlevelTarget)
        {
            SyncSetLoadLevelTargetUpnpOrgDimming1 sync = new SyncSetLoadLevelTargetUpnpOrgDimming1(this);
            BeginSetLoadLevelTarget(aNewLoadlevelTarget, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLoadLevelTarget().</remarks>
        /// <param name="aNewLoadlevelTarget"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetLoadLevelTarget(uint aNewLoadlevelTarget, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetLoadLevelTarget, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetLoadLevelTarget.InputParameter(inIndex++), aNewLoadlevelTarget));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetLoadLevelTarget(IntPtr aAsyncHandle)
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
        /// <param name="aGetLoadlevelTarget"></param>
        public void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget)
        {
            SyncGetLoadLevelTargetUpnpOrgDimming1 sync = new SyncGetLoadLevelTargetUpnpOrgDimming1(this);
            BeginGetLoadLevelTarget(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aGetLoadlevelTarget = sync.GetLoadlevelTarget();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelTarget().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLoadLevelTarget(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLoadLevelTarget, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelTarget.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aGetLoadlevelTarget"></param>
        public void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aGetLoadlevelTarget = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRetLoadlevelStatus"></param>
        public void SyncGetLoadLevelStatus(out uint aRetLoadlevelStatus)
        {
            SyncGetLoadLevelStatusUpnpOrgDimming1 sync = new SyncGetLoadLevelStatusUpnpOrgDimming1(this);
            BeginGetLoadLevelStatus(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetLoadlevelStatus = sync.RetLoadlevelStatus();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLoadLevelStatus(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLoadLevelStatus, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelStatus.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetLoadlevelStatus"></param>
        public void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aRetLoadlevelStatus)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetLoadlevelStatus = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aNewOnEffectLevel"></param>
        public void SyncSetOnEffectLevel(uint aNewOnEffectLevel)
        {
            SyncSetOnEffectLevelUpnpOrgDimming1 sync = new SyncSetOnEffectLevelUpnpOrgDimming1(this);
            BeginSetOnEffectLevel(aNewOnEffectLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffectLevel().</remarks>
        /// <param name="aNewOnEffectLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetOnEffectLevel(uint aNewOnEffectLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetOnEffectLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetOnEffectLevel.InputParameter(inIndex++), aNewOnEffectLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetOnEffectLevel(IntPtr aAsyncHandle)
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
        /// <param name="aNewOnEffect"></param>
        public void SyncSetOnEffect(String aNewOnEffect)
        {
            SyncSetOnEffectUpnpOrgDimming1 sync = new SyncSetOnEffectUpnpOrgDimming1(this);
            BeginSetOnEffect(aNewOnEffect, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffect().</remarks>
        /// <param name="aNewOnEffect"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetOnEffect(String aNewOnEffect, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetOnEffect, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetOnEffect.InputParameter(inIndex++), aNewOnEffect));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetOnEffect(IntPtr aAsyncHandle)
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
        /// <param name="aRetOnEffect"></param>
        /// <param name="aRetOnEffectLevel"></param>
        public void SyncGetOnEffectParameters(out String aRetOnEffect, out uint aRetOnEffectLevel)
        {
            SyncGetOnEffectParametersUpnpOrgDimming1 sync = new SyncGetOnEffectParametersUpnpOrgDimming1(this);
            BeginGetOnEffectParameters(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetOnEffect = sync.RetOnEffect();
            aRetOnEffectLevel = sync.RetOnEffectLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetOnEffectParameters().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetOnEffectParameters(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetOnEffectParameters, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetOnEffectParameters.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetOnEffectParameters.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetOnEffect"></param>
        /// <param name="aRetOnEffectLevel"></param>
        public void EndGetOnEffectParameters(IntPtr aAsyncHandle, out String aRetOnEffect, out uint aRetOnEffectLevel)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetOnEffect = Invocation.OutputString(aAsyncHandle, index++);
            aRetOnEffectLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStepUp()
        {
            SyncStepUpUpnpOrgDimming1 sync = new SyncStepUpUpnpOrgDimming1(this);
            BeginStepUp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStepUp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStepUp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStepUp(IntPtr aAsyncHandle)
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
        public void SyncStepDown()
        {
            SyncStepDownUpnpOrgDimming1 sync = new SyncStepDownUpnpOrgDimming1(this);
            BeginStepDown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStepDown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStepDown, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStepDown(IntPtr aAsyncHandle)
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
        public void SyncStartRampUp()
        {
            SyncStartRampUpUpnpOrgDimming1 sync = new SyncStartRampUpUpnpOrgDimming1(this);
            BeginStartRampUp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampUp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampUp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampUp(IntPtr aAsyncHandle)
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
        public void SyncStartRampDown()
        {
            SyncStartRampDownUpnpOrgDimming1 sync = new SyncStartRampDownUpnpOrgDimming1(this);
            BeginStartRampDown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampDown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampDown, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampDown(IntPtr aAsyncHandle)
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
        public void SyncStopRamp()
        {
            SyncStopRampUpnpOrgDimming1 sync = new SyncStopRampUpnpOrgDimming1(this);
            BeginStopRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStopRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStopRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStopRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStopRamp(IntPtr aAsyncHandle)
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
        /// <param name="aNewLoadLevelTarget"></param>
        /// <param name="aNewRampTime"></param>
        public void SyncStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime)
        {
            SyncStartRampToLevelUpnpOrgDimming1 sync = new SyncStartRampToLevelUpnpOrgDimming1(this);
            BeginStartRampToLevel(aNewLoadLevelTarget, aNewRampTime, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampToLevel().</remarks>
        /// <param name="aNewLoadLevelTarget"></param>
        /// <param name="aNewRampTime"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampToLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.InputParameter(inIndex++), aNewLoadLevelTarget));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.InputParameter(inIndex++), aNewRampTime));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampToLevel(IntPtr aAsyncHandle)
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
        /// <param name="aNewStepDelta"></param>
        public void SyncSetStepDelta(uint aNewStepDelta)
        {
            SyncSetStepDeltaUpnpOrgDimming1 sync = new SyncSetStepDeltaUpnpOrgDimming1(this);
            BeginSetStepDelta(aNewStepDelta, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStepDelta().</remarks>
        /// <param name="aNewStepDelta"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStepDelta(uint aNewStepDelta, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStepDelta, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStepDelta.InputParameter(inIndex++), aNewStepDelta));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStepDelta(IntPtr aAsyncHandle)
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
        /// <param name="aRetStepDelta"></param>
        public void SyncGetStepDelta(out uint aRetStepDelta)
        {
            SyncGetStepDeltaUpnpOrgDimming1 sync = new SyncGetStepDeltaUpnpOrgDimming1(this);
            BeginGetStepDelta(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetStepDelta = sync.RetStepDelta();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStepDelta().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetStepDelta(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetStepDelta, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetStepDelta.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetStepDelta"></param>
        public void EndGetStepDelta(IntPtr aAsyncHandle, out uint aRetStepDelta)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetStepDelta = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aNewRampRate"></param>
        public void SyncSetRampRate(uint aNewRampRate)
        {
            SyncSetRampRateUpnpOrgDimming1 sync = new SyncSetRampRateUpnpOrgDimming1(this);
            BeginSetRampRate(aNewRampRate, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRampRate().</remarks>
        /// <param name="aNewRampRate"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRampRate(uint aNewRampRate, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRampRate, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRampRate.InputParameter(inIndex++), aNewRampRate));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRampRate(IntPtr aAsyncHandle)
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
        /// <param name="aRetRampRate"></param>
        public void SyncGetRampRate(out uint aRetRampRate)
        {
            SyncGetRampRateUpnpOrgDimming1 sync = new SyncGetRampRateUpnpOrgDimming1(this);
            BeginGetRampRate(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampRate = sync.RetRampRate();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampRate().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampRate(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampRate, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRampRate.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetRampRate"></param>
        public void EndGetRampRate(IntPtr aAsyncHandle, out uint aRetRampRate)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetRampRate = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncPauseRamp()
        {
            SyncPauseRampUpnpOrgDimming1 sync = new SyncPauseRampUpnpOrgDimming1(this);
            BeginPauseRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPauseRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPauseRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPauseRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndPauseRamp(IntPtr aAsyncHandle)
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
        public void SyncResumeRamp()
        {
            SyncResumeRampUpnpOrgDimming1 sync = new SyncResumeRampUpnpOrgDimming1(this);
            BeginResumeRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndResumeRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginResumeRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionResumeRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndResumeRamp(IntPtr aAsyncHandle)
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
        /// <param name="aRetIsRamping"></param>
        public void SyncGetIsRamping(out bool aRetIsRamping)
        {
            SyncGetIsRampingUpnpOrgDimming1 sync = new SyncGetIsRampingUpnpOrgDimming1(this);
            BeginGetIsRamping(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetIsRamping = sync.RetIsRamping();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetIsRamping().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetIsRamping(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetIsRamping, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetIsRamping.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetIsRamping"></param>
        public void EndGetIsRamping(IntPtr aAsyncHandle, out bool aRetIsRamping)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetIsRamping = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRetRampPaused"></param>
        public void SyncGetRampPaused(out bool aRetRampPaused)
        {
            SyncGetRampPausedUpnpOrgDimming1 sync = new SyncGetRampPausedUpnpOrgDimming1(this);
            BeginGetRampPaused(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampPaused = sync.RetRampPaused();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampPaused().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampPaused(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampPaused, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetRampPaused.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetRampPaused"></param>
        public void EndGetRampPaused(IntPtr aAsyncHandle, out bool aRetRampPaused)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetRampPaused = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRetRampTime"></param>
        public void SyncGetRampTime(out uint aRetRampTime)
        {
            SyncGetRampTimeUpnpOrgDimming1 sync = new SyncGetRampTimeUpnpOrgDimming1(this);
            BeginGetRampTime(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampTime = sync.RetRampTime();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampTime().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampTime(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampTime, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRampTime.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRetRampTime"></param>
        public void EndGetRampTime(IntPtr aAsyncHandle, out uint aRetRampTime)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRetRampTime = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the LoadLevelStatus state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aLoadLevelStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLoadLevelStatusChanged(System.Action aLoadLevelStatusChanged)
        {
            lock (iPropertyLock)
            {
                iLoadLevelStatusChanged = aLoadLevelStatusChanged;
            }
        }

        private void LoadLevelStatusPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iLoadLevelStatusChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StepDelta state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aStepDeltaChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStepDeltaChanged(System.Action aStepDeltaChanged)
        {
            lock (iPropertyLock)
            {
                iStepDeltaChanged = aStepDeltaChanged;
            }
        }

        private void StepDeltaPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStepDeltaChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the RampRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampRateChanged(System.Action aRampRateChanged)
        {
            lock (iPropertyLock)
            {
                iRampRateChanged = aRampRateChanged;
            }
        }

        private void RampRatePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iRampRateChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the IsRamping state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aIsRampingChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIsRampingChanged(System.Action aIsRampingChanged)
        {
            lock (iPropertyLock)
            {
                iIsRampingChanged = aIsRampingChanged;
            }
        }

        private void IsRampingPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iIsRampingChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the RampPaused state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampPausedChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampPausedChanged(System.Action aRampPausedChanged)
        {
            lock (iPropertyLock)
            {
                iRampPausedChanged = aRampPausedChanged;
            }
        }

        private void RampPausedPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iRampPausedChanged);
            }
        }

        /// <summary>
        /// Query the value of the LoadLevelStatus property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the LoadLevelStatus property</returns>
        public uint PropertyLoadLevelStatus()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iLoadLevelStatus.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the StepDelta property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the StepDelta property</returns>
        public uint PropertyStepDelta()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iStepDelta.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the RampRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the RampRate property</returns>
        public uint PropertyRampRate()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iRampRate.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the IsRamping property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the IsRamping property</returns>
        public bool PropertyIsRamping()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iIsRamping.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the RampPaused property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the RampPaused property</returns>
        public bool PropertyRampPaused()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iRampPaused.Value();
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
            iActionSetLoadLevelTarget.Dispose();
            iActionGetLoadLevelTarget.Dispose();
            iActionGetLoadLevelStatus.Dispose();
            iActionSetOnEffectLevel.Dispose();
            iActionSetOnEffect.Dispose();
            iActionGetOnEffectParameters.Dispose();
            iActionStepUp.Dispose();
            iActionStepDown.Dispose();
            iActionStartRampUp.Dispose();
            iActionStartRampDown.Dispose();
            iActionStopRamp.Dispose();
            iActionStartRampToLevel.Dispose();
            iActionSetStepDelta.Dispose();
            iActionGetStepDelta.Dispose();
            iActionSetRampRate.Dispose();
            iActionGetRampRate.Dispose();
            iActionPauseRamp.Dispose();
            iActionResumeRamp.Dispose();
            iActionGetIsRamping.Dispose();
            iActionGetRampPaused.Dispose();
            iActionGetRampTime.Dispose();
            iLoadLevelStatus.Dispose();
            iStepDelta.Dispose();
            iRampRate.Dispose();
            iIsRamping.Dispose();
            iRampPaused.Dispose();
        }
    }
}

